//TODO: сделать свою векторную матешу
// TODO: скрипт двигло
// TODO: сделать кластерный рендер
//TODO: начать делать хотя бы что-то со звуком 
//TODO: реализовать систему частиц(партикле сустемXD) 
//TODO: привести все фабричные методы к одному виду
/*
TODO: подумать над реализацей:
****************************************************************************************
 * воркспейса и вообще, хорошая ли это затея разделять эту сущность на редактор и логику
 * реализовать каким-то хуем папочку в ведроиде, откуда данные таскать буду
 * передачи данных через потоки.(думаеца создать очередь тасков для каждой подсистемы движка)
****************************************************************************************

*/

#include "stdafx.h"


#define NOMINMAX
#include "CreateInfoStructures.hpp"
#include "BaseRenderWindow.hpp"
#include "DebugUI.hpp"
#include "Physics.hpp"
#include "WorkSpace.hpp"

#include "ScriptState.hpp"
#include "Vector2.hpp"
#include "VulkanWindow.hpp"
#include "VulkanRender.hpp"
#include "VulkanObjects.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "AngelScriptEngine.hpp"
#include "ScriptManager.hpp"
namespace BEbraEngine {


    class Engine {
    public:
        std::shared_ptr<AbstractRender> render1;
        std::shared_ptr<Physics> physics;
        std::unique_ptr<BaseWindow> window1;
        std::shared_ptr<WorkSpace> workspace1;
        std::unique_ptr<ScriptState> gameLogic1;
        bool multiThreading = true;
    public:
        void init() {
            render1 = std::unique_ptr<VulkanRender>(new VulkanRender());
            window1 = std::unique_ptr<VulkanWindow>(new VulkanWindow(render1.get()));
            window1->createWindow(Vector2(1000, 1000), "BEEEBRA!!!");
            physics = std::shared_ptr<Physics>(new Physics());
            workspace1 = std::shared_ptr<WorkSpace>(new WorkSpace());
            gameLogic1 = std::unique_ptr<ScriptState>(new ScriptState(render1, workspace1, physics));
        }
        void start() {

            while (!window1->isClose()) {
                Time::updateTime();
                if (multiThreading) {
                    
                    
                    tbb::flow::graph g;
                    tbb::flow::broadcast_node<tbb::flow::continue_msg> input(g);
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _window(g, [&](const tbb::flow::continue_msg&) { window1->update(); });
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _render(g, [&](const tbb::flow::continue_msg&) { render1->drawFrame(); });
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _physics(g, [&](const tbb::flow::continue_msg&) { physics->update(); });
                    tbb::flow::continue_node<tbb::flow::continue_msg>
                        _gameLogic(g, [&](const tbb::flow::continue_msg&) { gameLogic1->update(); });


                    tbb::flow::make_edge(input, _physics);
                    tbb::flow::make_edge(input, _render);
                    tbb::flow::make_edge(input, _gameLogic);
                    tbb::flow::make_edge(input, _window);
                    input.try_put(tbb::flow::continue_msg());
                    g.wait_for_all();
                    gameLogic1->updateState();

                }
                else {
                    
                    
                    window1->update();
                    render1->drawFrame();
                    physics->update();
                    gameLogic1->update();
                    gameLogic1->updateState();
                }

            }


            //vkDeviceWaitIdle(VulkanRender::device);

        }

        ~Engine() {
          //  gameLogic1.reset();
          //  render1.reset();
          //  UId->Destroy();
        }
    };
}






#ifndef __ANDROID__
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif

int main()
{
    BEbraEngine::Engine engine;
    engine.init();
    engine.start();

    return 1337228;
}



/*
#include <iostream>
#include <mono/jit/jit.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
 #include <exception>
 //#include <direct.h>




#ifdef __cplusplus
extern "C"
#endif
int main()
{
    //std::cout << "Hello World!\n"; 
    //  Print this path
    //std::cout << _getcwd(nullptr, 0);
        
    MonoDomain * domain;
    //const char *csharp_dll = "../csharp/bin/debug/csharp.dll";
    const char* csharp_dll = "C:/.BEbraEngine/src/scripts/BEbraEngine/bin/Debug/BEbraEngine.dll";
    try
    {
        
    //  JIT initialization
        mono_set_dirs("C:/Program Files/Mono/lib", "C:/Program Files/Mono/etc");
        domain = mono_jit_init("BEbraEngine");
    //  Load an assembly
        MonoAssembly * assembly = mono_domain_assembly_open(domain, csharp_dll);
        MonoImage * image = mono_assembly_get_image(assembly);
    //  Get MonoClass
        MonoClass * mono_class = mono_class_from_name(image, "BEbraEngine", "BindingTest");
    //  Acquisition method
        //MonoMethodDesc *method_desc = mono_method_desc_new("csharp.BindingTest:Main()", true);
        MonoMethodDesc * method_desc = mono_method_desc_new("csharp.BindingTest:sayhello()", true);
        MonoMethod * method = mono_method_desc_search_in_class(method_desc, mono_class);
        mono_method_desc_free(method_desc);
    //  Call the method
        //mono_raise_exception(mono_get_exception_index_out_of_range());
        MonoObject* pException = NULL;
        
        // this method will cause an exception in c#, something like null exception
        MonoObject* pResult = mono_runtime_invoke(method, NULL, NULL, &pException);

        char* szResult = NULL;
        if (pException == NULL)
        {
            szResult = mono_string_to_utf8((MonoString*)pResult);
        }
        else
        {
            MonoString * pMsg = mono_object_to_string(pException, NULL);
            szResult = mono_string_to_utf8(pMsg);
            //szResult = "Mono throwed an Exception!";
        }
        if(szResult)
        std::cout << szResult << std::endl;
    //  JIT release
        mono_jit_cleanup(domain);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}
*/