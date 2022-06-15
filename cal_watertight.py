import open3d as o3d
import numpy as np
import os
import copy

def upsample(obj):
    if len(obj.vertex_normals) == 0:
        obj.compute_vertex_normals()
    obj_upsample = obj.sample_points_poisson_disk(number_of_points=4000)
    # form new mesh with upsampled vertices and original topology info
    pts = np.array(obj.vertices)
    samples = np.asarray(obj_upsample.points)
    samples_normal = np.asarray(obj_upsample.normals)
    dist = np.sum(((samples[np.newaxis, ...] - pts[:, np.newaxis, :]) ** 2), axis=2)  # upsampled points to original points
    sorted_ids = dist.argsort(axis=1)
    # dist_geo = np.sqrt(np.sum((samples[np.newaxis, ...] - samples[:, np.newaxis, :]) ** 2, axis=2))

    tris = obj.triangles
    tris_new = []
    for tri in tris:
        i, j, k = tri[0], tri[1], tri[2]
        tris_new.append([sorted_ids[i, 0], sorted_ids[j, 0], sorted_ids[k, 0]])
        # print(i, j, k)
    tris_new = np.array(tris_new, dtype=np.int)
    # http://www.open3d.org/docs/release/python_api/open3d.geometry.TriangleMesh.html
    pts_vec = o3d.utility.Vector3dVector(samples)
    tris_vec = o3d.utility.Vector3iVector(tris_new)
    mesh_new = o3d.geometry.TriangleMesh(pts_vec, tris_vec)
    mesh_new.vertex_normals = o3d.utility.Vector3dVector(samples_normal)
    return mesh_new

if __name__ == "__main__":
    data_dir = "F:/Dataset/RigNetv1"
    # data_dir = "/home/server/MaJing/Dataset/RigNet/data"
    model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int)

    model_list = [8333]
    for model_id in model_list:
        # if os.path.exists(os.path.join(data_dir, f"watertight/{model_id}.obj")):
        #     continue
        print(model_id)
        obj = o3d.io.read_triangle_mesh(os.path.join(data_dir, f"obj/{model_id}.obj"))
        if len(obj.vertex_normals) == 0:
            obj.compute_vertex_normals()
        pcd = obj.sample_points_poisson_disk(number_of_points=4000)
        mesh, densities = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(pcd, depth=8)

        # mesh = mesh.remove_degenerate_triangles()
        # mesh = mesh.remove_duplicated_triangles()
        # mesh = mesh.remove_duplicated_vertices()
        # mesh = mesh.remove_unreferenced_vertices()

        triangle_clusters, cluster_n_triangles, cluster_area = mesh.cluster_connected_triangles()
        triangle_clusters = np.asarray(triangle_clusters)
        cluster_n_triangles = np.asarray(cluster_n_triangles)
        cluster_area = np.asarray(cluster_area)
        mesh1 = copy.deepcopy(mesh)
        largest_cluster_idx = cluster_n_triangles.argmax()
        triangles_to_remove = triangle_clusters != largest_cluster_idx
        mesh1.remove_triangles_by_mask(triangles_to_remove)

        if not mesh1.is_edge_manifold():
            mesh1.remove_non_manifold_edges()
        mesh1 = mesh1.remove_degenerate_triangles()
        mesh1 = mesh1.remove_duplicated_triangles()
        mesh1 = mesh1.remove_duplicated_vertices()
        mesh1 = mesh1.remove_unreferenced_vertices()

        if not mesh.is_watertight():
            print(model_id)
        o3d.io.write_triangle_mesh(os.path.join(data_dir, f"watertight/{model_id}.obj"), mesh1)
    print("done!")


