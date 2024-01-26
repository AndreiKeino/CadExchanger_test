#include <iostream>

#include "include/vec3d.h"
#include "include/curves.h"
#include "include/constants.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>

// #define MEMLEAKS // uncomment this line to check if there are memory leaks

#ifdef MEMLEAKS
// 2. Has neither explicit memory deallocation nor memory leaks.
#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
#endif


int main(int argc, char** argv)
{
#ifdef MEMLEAKS
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld);
    {
#endif

        // 2. Populate a container (e.g. vector or list) of objects of these types created 
        // in random manner with random parameters.
        RandomCurveCreator rcc;
        std::vector<CurvePtr> curve_list;
        const int cnt = 11;
        for (int i = 0; i < cnt; i++)
        {
            curve_list.push_back(rcc.create_random_curve());
        }
        // 3. Print coordinates of points and derivatives of all curves in the container at t=PI/4
        const auto t = pi / 4;
        for (const auto p : curve_list)
        {
            std::cout << *p << " coordinates at: " << t << ": " << p->coordinates(t)
                << " derivatives at " << t << ": " << p->derivatives(t) << std::endl;
        }

        // 4. Populate a second container that would contain only circles from the first container. 
        // Make sure the second container shares (i.e. not clones) circles of the first one, 
        // e.g. via pointers

        std::vector<CurvePtr> filtered_list;

        std::copy_if(curve_list.begin(), curve_list.end(), std::back_inserter(filtered_list),
            [](const CurvePtr p) {return dynamic_cast<Circle*>(p.get()) != nullptr; });

        Float sum = 0.0;

        if (filtered_list.size() > 0)
        {
            // 5. Sort the second container in the ascending order of circles’ radii. That is, the 
            // first element has the smallest radius, the last - the greatest.
            std::sort(filtered_list.begin(), filtered_list.end(), [](
                const CurvePtr a, const CurvePtr b) {return a->parameters()[0] < b->parameters()[0]; });

            // 6. Compute the total sum of radii of all curves in the second container.
            sum = std::accumulate(filtered_list.begin(),
                filtered_list.end(),
                0.0,
                [](Float v, const CurvePtr a) {return v + a->parameters()[0]; });

        }

        std::cout << "total sum of radii of all curves in the second container =  "
            << sum << std::endl;

#ifdef MEMLEAKS
    }
    _CrtMemCheckpoint(&sNew); //take a snapshot 
    if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
    {
        OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
        _CrtMemDumpStatistics(&sDiff);
        OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
        _CrtMemDumpAllObjectsSince(&sOld);
        OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
        _CrtDumpMemoryLeaks();
    }
#endif

    return 0;
}
