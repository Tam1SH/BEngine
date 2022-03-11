#include "stdafx.h"
#include "RenderWorld.hpp"
#include "RenderObject.hpp"
namespace BEbraEngine {


    void RenderWorld::updateRenderData()
    {

        for (auto light = lights.begin(); light != lights.end(); ++light) {
            (*light)->update();
        }
        tbb::parallel_for<size_t>(0, objects.size(), [this](int i) {
            objects[i]->update();
        });



    }

}