
#include <tbb.h>
#include "Physics.hpp"
#include <variant>
import VulkanWindow;
import Debug;
import ScriptState;
import VulkanRender;
import VulkanWindow;
import VulkanRenderAllocator;
import RenderHelper;
import RenderWorld;
import RenderAllocatorDecl;
import RenderDecl;
import ExecuteQueues;
import CRender;
import Time;
import Input;

using std::unique_ptr;

namespace BEbraEngine {

    struct EngineCreateInfo {
        bool Debug;
        bool Test;
    };

    class Engine {
    public:
        Render render{};
        std::variant<VulkanWindow> window{};
        RenderAllocator allocator{};

        ScriptState gameState{};
        Physics physics{};

        bool multiThreading = true;
    public:
        Engine()
        {

            std::visit([&](CRender auto& render) {
                allocator = BEbraEngine::create::renderAllocator1(render);
                window = BEbraEngine::create::window(render);
            }, render);

            std::visit([&](VulkanWindow& window) {
                window.createWindow(Vector2(1000, 1000), "BEEEBRA!!!");
            }, window);

            //auto a = dynamic_cast<VulkanRender*>(*render1);
           // auto drawer = new DebugDrawer(a);
            //physics->setDebugDrawer(drawer);

            gameState = ScriptState(render, allocator, physics);
            Debug::enableAll();
        }

        void Main(const EngineCreateInfo& info) {
            init(info);
            if(!info.Test)
                start();
        }

        void init(const EngineCreateInfo& info) {
        }
        

        void start() {
            std::visit([&](CRender auto& render, VulkanWindow& window) {

                while (!window.isClose()) {
                    Time::updateTime();
                    if (multiThreading) {

                        window.update();
                        render.prepareDraw();

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
                    }
                    else {


                        //window1->update();

                        //
                        // //physics->update();
                        //
                        //render1->update();
                        //gameState->update();
                        //gameState->updateState();
                        //render1->drawFrame();

                        //render1->prepareDraw();
                    }

                }
            }, render, window);

            //vkDeviceWaitIdle(VulkanRender::device);

        }

        ~Engine() {

        }
    };
}