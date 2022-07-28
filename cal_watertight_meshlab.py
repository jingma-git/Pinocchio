# https://pymeshlab.readthedocs.io/en/latest/
import numpy as np
import os
import pymeshlab

if __name__ == "__main__":
    # pymeshlab.print_filter_list()
    # pymeshlab.print_filter_parameter_list('conditional_vertex_selection')

    # data_dir = "F:/Dataset/RigNetv1"
    data_dir = "D:/Dataset/AutoRS"
    model_list = np.loadtxt(os.path.join(data_dir, "test_final.txt"), dtype=np.int)
    model_list = [80, 508, 1215, 2495]
    for model_id in model_list:
        out_path = os.path.join(data_dir, f"watertight/{model_id}.obj")
        if os.path.exists(out_path):
            continue
        print(model_id)
        ms = pymeshlab.MeshSet()
        ms.load_new_mesh(os.path.join(data_dir, f"obj/{model_id}.obj"))
        ms.re_compute_vertex_normals()
        ms.poisson_disk_sampling(samplenum=4000)
        ms.apply_filter('conditional_vertex_selection', condselect='(nx==0)&&(ny==0)&&(nz==0)')
        ms.delete_selected_vertices()
        ms.surface_reconstruction_screened_poisson(pre_clean=True)
        ms.save_current_mesh(out_path)

    # for model_id in model_list:
    #     ms = pymeshlab.MeshSet()
    #     out_path = os.path.join(data_dir, f"watertight/{model_id}.obj")
    #     ms.load_new_mesh(out_path)
    #     ms.split_in_connected_components()
    #     if ms.number_meshes() > 2:
    #         idx_max, num_verts_max = 0, ms.current_mesh().vertex_number()
    #         for i in range(1, ms.number_meshes()):
    #             ms.set_current_mesh(i)
    #             if ms.current_mesh().vertex_number() > num_verts_max:
    #                 num_verts_max = ms.current_mesh().vertex_number()
    #                 idx_max = i
    #         ms.set_current_mesh(idx_max)
    #         print(model_id, ms.number_meshes(), idx_max, ms.current_mesh().vertex_number())  # 3685, 8335, 3642, 14029, 425, 1333
    #         ms.save_current_mesh(out_path)