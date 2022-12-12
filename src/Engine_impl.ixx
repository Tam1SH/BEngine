#include <tbb.h>
#include "Physics.hpp"
#include <variant>
#include "di.hpp"
namespace di = boost::di;

export module Engine_impl;
import Engine;
import VulkanRenderProxy;
import VulkanRender;
import RenderAllocator;
//import VulkanWindow;
//import VulkanRenderAllocator;
//import RenderAllocatorDecl;
import Render;
//import Time;
//import Input;
//import ScriptState;

namespace BEbraEngine {

    /*
    *         std::variant<VulkanWindow> window;
        Render render;
        RenderAllocator allocator;
        ScriptState gameState;
        Physics physics;
        
        bool multiThreading = true;
    */
    int Engine::run()
    {
        Render render = { RenderType::Vulkan };
        RenderAllocator allocator ={ std::move(VulkanRenderAllocator{render.get<VulkanRender>()})};

        Physics physics ={ };
        auto dependency_physics = di::bind<Physics>.to(physics);
        auto dependency_render = di::bind<Render>.to(render);
        auto dependency_allocator = di::bind<RenderAllocator>.to(render);
        const auto injector = di::make_injector(
            dependency_render,
            dependency_allocator,
            dependency_physics
        );


        
        //allocator = BEbraEngine::create::renderAllocator1(render);
        //window = BEbraEngine::create::window(render);
        /*
        std::visit([&](VulkanWindow& window) {
            window.createWindow(Vector2(1000, 1000), "BEEEBRA!!!");
            }, window);

        //auto a = dynamic_cast<VulkanRender*>(*vulkanRender);
       // auto drawer = new DebugDrawer(a);
        //physics->setDebugDrawer(drawer);

        gameState = ScriptState(render, allocator, physics);

        std::visit([&](CRender auto& render, VulkanWindow& window) {

            while (!window.isClose()) {
                Time::updateTime();
                if (multiThreading) {

                    window.update();


                    tbb::flow::graph g;
                    tbb::flow::broadcast_node<tbb::flow::continue_msg> input(g);
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _window(g, [&](const tbb::flow::continue_msg&) {});
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _render(g, [&](const tbb::flow::continue_msg&) {
                        render.update();
                            });

                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _physics(g, [&](const tbb::flow::continue_msg&) {
                        physics.update();
                            });
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _gameLogic(g, [&](const tbb::flow::continue_msg&) { gameState.update(); });


                    tbb::flow::make_edge(input, _physics);
                    tbb::flow::make_edge(input, _render);
                    tbb::flow::make_edge(input, _gameLogic);
                    tbb::flow::make_edge(input, _window);
                    input.try_put(tbb::flow::continue_msg());
                    g.wait_for_all();
                    gameState.updateState();
                    render.drawFrame();
                    render.prepareDraw();
                }
                else {


                    //window1->update();

                    //
                    // //physics->update();
                    //
                    //vulkanRender->update();
                    //gameState->update();
                    //gameState->updateState();
                    //vulkanRender->drawFrame();

                    //vulkanRender->prepareDraw();
                }

            }
            }, render, window);
        */
        return 0;
    }
}