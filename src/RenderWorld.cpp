#include "stdafx.h"
#include "RenderWorld.hpp"
#include "RenderObject.hpp"
namespace BEbraEngine {


    void RenderWorld::updateRenderData()
    {

        for (auto light = lights.begin(); light != lights.end(); ++light) {
            (*light)->update();
        }
        for (auto object = objects.begin(); object != objects.end(); ++object) {
            (*object)->update();
        }


    }

}