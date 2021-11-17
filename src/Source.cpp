
// TODO: сделать кластерный рендер
//TODO: сделать неймспейсы для разных частей движка
//TODO: начать делать хотя бы что-то со звуком 
/*
TODO: подумать над реализацей:
****************************************************************************************
 * воркспейса и вообще, хорошая ли это затея разделять эту сущность на редактор и логику
 * реализовать каким-то хуем папочку в ведроиде, откуда данные таксать буду
****************************************************************************************

*/

#include "stdafx.h"


#define NOMINMAX
//#include "GLWindow.h"
//#include "GLRender.h"
#include "CreateInfoStructures.hpp"
#include "BaseRenderWindow.hpp"
#include "DebugUI.hpp"
#include "Physics.hpp"
#include "WorkSpace.hpp"

#include "GameLogic.hpp"
#include "Vector2.hpp"
#include "VulkanWindow.hpp"
#include "DirectWindow.hpp"
#include "DirectRender.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Camera.hpp"
namespace BEbraEngine {

    class Engine {
    public:
        //std::shared_ptr<DirectRender> render;
        std::shared_ptr<VulkanRender> render1;
        std::shared_ptr<Physics> physics;
        std::unique_ptr<BaseWindow> window;
        std::unique_ptr<BaseWindow> window1;
        std::shared_ptr<WorkSpace> workspace;
        std::shared_ptr<WorkSpace> workspace1;
        std::unique_ptr<GameLogic> gameLogic;
        std::unique_ptr<GameLogic> gameLogic1;
        std::unique_ptr<Camera> mainCamera;
        std::unique_ptr<Camera> mainCamera1;

    public:
        void Init() {
            physics = std::shared_ptr<Physics>(new Physics());
            render1 = std::unique_ptr<VulkanRender>(new VulkanRender());
            window1 = std::unique_ptr<VulkanWindow>(new VulkanWindow(render1.get()));
            window1->CreateWindow(Vector2(800, 600), "BEEEBRA!!!");
            mainCamera1 = std::unique_ptr<Camera>(new Camera(Vector3(2)));
            workspace1 = std::shared_ptr<WorkSpace>(new WorkSpace());
            render1->InitCamera(mainCamera1.get());
            render1->camera = mainCamera1.get();
            gameLogic1 = std::unique_ptr<GameLogic>(new GameLogic(render1, workspace1, mainCamera1.get(), physics));
            window1->attach(gameLogic1.get());

            
            

            //     UId = std::make_unique<DebugUI>();
            

                //  UId->SetWorkSpace(workspace);
            // auto render = window->getRender();

            //   UId->Create(render, static_cast<VulkanWindow*>(window1.get()));





        }
        void Start() {

            while (window1.get() && !window1->isClose()) {
                Time::UpdateTime();
                Update();

            }


            //vkDeviceWaitIdle(VulkanRender::device);

        }
        void Update() {
            //   UId->Prepare();
            if(window.get())
                window->update();
            if(window1.get())
                window1->update();
            // window1->update();
        }

        ~Engine() {
            render1.reset();
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
int main(int, char** argv)
{
    BEbraEngine::Engine engine;
    engine.Init();
    engine.Start();

    return 0;
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