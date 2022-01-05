#include "src/vector.h"
#include "src/rect.h"
#include "src/multilinear.h"
#include "src/indexer.h"
#include "src/vecutils.h"
#include "src/pointprojector.h"
#include "src/utils.h"
#include <cassert>
#include <algorithm>

using namespace std;

void test_vec()
{
    Vector3 v1(1, 2, 3);
    Vector3 v2(4, 5, 6);
    double dot12 = v1 * v2;
    cout << v1 / 2.0 << endl;
    cout << v1.apply(divides<double>(), v2) << endl;
}

void test_rect2()
{
    Vector2 v0(0, 0), v1(1, 1), v2(2, 2);
    Rect2 r1(v0, v1), r2(v0, v2);

    // cout << r1.getSize() << endl;
    // assert(r2.contains(r1) == true);
    // cout << r1.getDiagLength() << endl;
    // cout << r1.distSqTo(r2) << endl;
    // cout << r1.distSqTo(Vector2(0.5, 0.5)) << endl;
    // cout << r1.distSqTo(Vector2(2, 2)) << endl;

    Vector2 p(2, 2);
    r1.distSqTo(p);
}

void test_rec3()
{
    Vector3 v0(0, 0, 0), v1(1, 1, 1);
    Rect3 r(v0, v1 * 0.5);

    for (int i = 0; i < (1 << 3); ++i)
    {
        cout << i << " " << r.getCorner(i) << endl;
    }
}

void test_comp()
{
    std::vector<char> v1{'a', 'b', 'c', 'd'};
    std::vector<char> v2{'e', 'f', 'c', 'd'};
    std::cout << std::lexicographical_compare(v1.begin(), v1.end(),
                                              v2.begin(), v2.end())
              << std::endl;
}

void test_lookup()
{
    Vector3 v0(0, 0, 0), v1(1, 1, 1);
    cout << _lookup(v0) << ", " << _lookup(v1) << endl;
    for (int i = 0; i < 1024; ++i)
    {
        cout << i << " " << interLeave3LookupTable[i] << endl;
    }
}

void test_proj()
{
    Vector3 v0(0, 0, 0), v1(1, 0, 0), v2(0, 1, 0);
    Vector3 p(2, 2, 0);
    Vector3 projP = projToTri(p, v0, v1, v2);
    cout << projP << endl;
}

void test_objproj()
{
    Vector3 v0(0, 0, 0), v1(1, 0, 0), v2(0, 1, 0), v3(0.5, 0.5, 0), v4(0.75, 0.25, 0);
    std::vector<Vec3Object> objs;
    objs.emplace_back(v0);
    objs.emplace_back(v1);
    objs.emplace_back(v2);
    objs.emplace_back(v3);
    objs.emplace_back(v4);

    ObjectProjector<3, Vec3Object> proj(objs);
    auto &rnodes = proj.getRNodes();
    for (int i = 0; i < rnodes.size(); ++i)
    {
        auto &rn = rnodes[i];
        cout << i << " " << rn.rect << " " << rn.child1 << ", " << rn.child2 << endl;
    }

    Vector3 q0(0.1, 0.1, 0);
    Vector3 res = proj.project(q0);
    cout << "q0: " << res << endl;
}

void test_split()
{
    int Dim = 3;
    int i;
    int idx[Dim + 1];
    for (i = 0; i < Dim + 1; ++i)
        idx[i] = 0;
    Vector3 center(0.5, 0.5, 0.5);
    Rect3 rect(Vector3(0, 0, 0), Vector3(1, 1, 1));
    int iter = 0;
    while (idx[Dim] == 0) // have not check the 3rd dimension
    {
        Vector3 cur;
        bool anyMid = false;
        for (i = 0; i < Dim; ++i)
        {
            // i=0: idx[0]==0, cur[0]=lo[0]
            // i=0: idx[0]==1, cur[0]=hi[0]
            // i=0: idx[0]==2, cur[0]=center[0], cur=[cent_x, 0, 0]
            // [0, 1, 0, 0], cur=[low_x, hi_y, 0]
            switch (idx[i])
            {
            case 0:
                cur[i] = rect.getLo()[i];
                break;
            case 1:
                cur[i] = rect.getHi()[i];
                break;
            case 2:
                cur[i] = center[i];
                anyMid = true;
                break;
            }
        }

        cout << "iter" << iter << " cur: " << cur
             << " idx:" << idx[0] << "," << idx[1] << "," << idx[2] << "," << idx[3] << endl;
        // cur: [cent_x, 0, 0]
        // if (anyMid && fabs(evaluate(cur) - eval(cur)) > tol)
        // {
        //     doSplit = true;
        //     break;
        // }

        // iter0: i=0, [0, 0, 0, 0]: idx[0]!=2, idx[0]+=1, [1, 0, 0, 0]
        // iter1: i=0, [1, 0, 0, 0]: idx[0]!=2, idx[0]+=1, [2, 0, 0, 0]
        // iter2: [2, 0, 0, 0]: idx[1]!=2, idx[1]+=1, [0, 1, 0, 0]
        for (i = 0; i < Dim + 1; ++i)
        {
            if (idx[i] != 2)
            {
                idx[i] += 1;
                for (--i; i >= 0; --i)
                    idx[i] = 0;
                break;
            }
        }
        cout << "iter" << iter << " reset idx:" << idx[0] << "," << idx[1] << "," << idx[2] << "," << idx[3] << endl;
        iter++;
    }
}

void test_grid()
{
    // Grid3<2> g1;
    // for (int i = 0; i < 9; ++i)
    // {
    //     cout << g1.bit(i, 0) << ", " << g1.bit(i, 1) << endl;
    // }

    Grid3<3> g2;
    for (int i = 0; i < g2.num_corners; ++i)
    {
        cout << g2.bit(i, 0) << "," << g2.bit(i, 1) << "," << g2.bit(i, 2) << endl;
    }
}

ostream *Debugging::outStream = NULL;

int main()
{
    Debugging::setOutStream(cout);
    // test_vec();
    // test_rect2();
    // test_rec3();
    // test_comp();
    // test_lookup();
    // test_proj();
    // test_objproj();
    // test_split();
    test_grid();
    return 0;
}