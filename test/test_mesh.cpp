#include "src/mesh.h"
#include "src/intersector.h"
#include "src/debugging.h"
#include "src/quaddisttree.h"
#include <list>

ostream *Debugging::outStream = NULL;
typedef DRootNode<DistData<3>, 3, ArrayIndexer> TreeType; // our distance field octree type
typedef typename TreeType::Node DistNode;
static const double defaultTreeTol = 0.003;

void test_intersect(Mesh &mesh)
{
    Intersector mint(mesh, Vector3(1, 0, 0));
    // Vector3 p(-1, 0.5, 0.5);
    Vector3 p(-1, 0.125, 0.25);
    // Vector3 p(-1, 0.6, 0.5);
    std::vector<int> tris;
    std::vector<Vector3> ips = mint.intersect(p, &tris);
    for (int i = 0; i < ips.size(); ++i)
    {
        cout << ips[i] << ", tri " << tris[i] / 3 << endl;
    }
}

TreeType *constructDistanceField(const Mesh &m)
{
    vector<Tri3Object> triobjvec;
    for (int i = 0; i < (int)m.edges.size(); i += 3)
    {
        Vector3 v1 = m.vertices[m.edges[i].vertex].pos;
        Vector3 v2 = m.vertices[m.edges[i + 1].vertex].pos;
        Vector3 v3 = m.vertices[m.edges[i + 2].vertex].pos;

        triobjvec.push_back(Tri3Object(v1, v2, v3));
    }

    ObjectProjector<3, Tri3Object> proj(triobjvec);
    Vector3 p(0.25, 0.25, 0.25);
    Vector3 curP = proj.project(p);
    cout << "project onto surface: " << curP << " dist: " << (p - curP).length() << endl;

    Intersector intersector(m, Vector3(1, 0, 0));
    std::vector<int> tris;
    std::vector<Vector3> isects = intersector.intersect(p, &tris);
    for (int i = 0; i < isects.size(); ++i)
    {
        cout << "intersect with tri " << tris[i] / 3 << ", p=" << isects[i] << endl;
    }

    TreeType *root = OctTreeMaker<TreeType>::make(proj, m, defaultTreeTol);
    return root;
}

// bfs traverse octree
void bfs(TreeType *root)
{
    std::list<DistNode *> queue;
    std::vector<DistNode *> nodes;
    queue.push_back(root);
    while (!queue.empty())
    {
        DistNode *node = queue.front();
        nodes.push_back(node);
        queue.pop_front();

        int numKids = 0;
        for (int i = 0; i < node->numChildren; ++i)
        {
            DistNode *child = node->getChild(i);
            if (child)
            {
                queue.push_back(child);
                numKids++;
            }
        }
        // cout << node->getRect() << " childs: " << numKids << " dist:";
        // for (int i = 0; i < 8; ++i)
        //     cout << node->getValue(i) << " ";
        // cout << endl;
    }
    cout << "total nodes: " << nodes.size() << endl;
    cout << root->countNodes() << " " << root->maxLevel() << endl;
}

void sdf(TreeType *root)
{
    // const int N = 10;
    // double step = 1.0 / (double)N;
    // double min_dist = std::numeric_limits<double>::max();
    // double min_i, min_j, min_k;
    // for (int i = 0; i <= N; ++i)
    // {
    //     for (int j = 0; j <= N; ++j)
    //     {
    //         for (int k = 0; k <= N; ++k)
    //         {
    //             Vector3 p(i * step, j * step, k * step);
    //             double dist = root->evaluate(p);
    //             // cout << p << " dist: " << dist << endl;
    //             if (dist < min_dist)
    //             {
    //                 min_dist = dist;
    //                 min_i = i;
    //                 min_j = j;
    //                 min_k = k;
    //             }
    //         }
    //     }
    // }

    // cout << min_i << " " << min_j << " " << min_k << ": " << min_dist << endl;

    Vector3 p(0.2, 0.2, 0.2);
    double dist = root->evaluate(p);
    cout << "dist: " << dist << endl;
}

int main(int argc, char *argv[])
{
    Debugging::setOutStream(cout);
    Mesh mesh(argv[1]);
    TreeType *root = constructDistanceField(mesh);
    // bfs(root);
    // sdf(root);
    return 0;
}