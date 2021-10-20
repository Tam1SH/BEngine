//TODO: сделать бы так, чтобы при создании дескриптора его layout можно было бы 
//по имени выбирать в классе DescriptorLayout или сувать туда структуру, которая 
//соответствовало бы какому-нибудь из layout и возвращала бы его 
// TODO: подумать над интерфейсом рендер объектов Draw(), т.к в вулкане эффективно было бы через глобальный дескриптор и буфер биндить данные для рендера.
// TODO: сделать кластерный рендер
// TODO: реализация меша для объектов рендера
//TODO: заюзать для лайаутов хеш таблицу
//TODO: сделать неймспейсы для разных частей движка 
//TODO: начать делать хотя бы что-то со звуком 
/*
TODO: подумать над реализацей:
****************************************************************************************
 * воркспейса и вообще, хорошая ли это затея разделять эту сущность на редактор и логику
 * абстрагировать доступ к рендеру, т.к их будет как минимум 2
 * сделать абстрактные классы для окна т.к я хуй знает что я буду делать и вообще охото на пк юзать GLFW (сделано) 
 * также и для физики так как возможно я буду и другой физ. движок прикручивать
 * сделать свой класс векторов чтобы потом не ебаться с разными векторами из разных либ(сделано)
 * ну и также для объектов рендера
 * присобачить Mono
****************************************************************************************
Вывод: В общем подумать над абстрагированием основных элементов движка для возможной замены их реализации
*/





#define NOMINMAX
#include "DebugUI.h"
#include "Physics.hpp"
#include "WorkSpace.h"

#include "VulkanRender.h"
#include "GameLogic.h"
#include "Vector2.h"
#include "VulkanWindow.h"
#include "DirectWindow.h"
#include "DirectRender.hpp"
#include "Input.hpp"
namespace BEbraEngine {

    class Engine {
    public:
        std::shared_ptr<DirectRender> render;
        std::shared_ptr<VulkanRender> render1;
        std::unique_ptr<Physics> physics;

      //  std::unique_ptr<DebugUI> UId;
        
        std::unique_ptr<BaseWindow> window;
        std::unique_ptr<BaseWindow> window1;
        std::shared_ptr<WorkSpace> workspace;
        std::unique_ptr<GameLogic> gameLogic;
        std::unique_ptr<GameLogic> gameLogic1;
        std::unique_ptr<Camera> mainCamera;
        std::unique_ptr<Camera> mainCamera1;

    public:
        void Init() {
            render1 = std::shared_ptr<VulkanRender>(new VulkanRender());
            render = std::shared_ptr<DirectRender>(new DirectRender());
            window1 = std::unique_ptr<VulkanWindow>(new VulkanWindow(render1));
            window = std::unique_ptr<DirectWindow>(new DirectWindow(render));


            mainCamera1 = std::unique_ptr<Camera>(new Camera(glm::vec3(0, 1, 10)));
            mainCamera = std::unique_ptr<Camera>(new Camera(glm::vec3(0, 1, 10)));
            window->CreateWindow(Vector2(800, 600), "BEEEBRA!!!");
            window1->CreateWindow(Vector2(800, 600), "BEEEBRA!!!");
            workspace = std::shared_ptr<WorkSpace>(new WorkSpace());

            //     UId = std::make_unique<DebugUI>();


                //  UId->SetWorkSpace(workspace);
            // auto render = window->getRender();
            render->InitCamera(mainCamera.get());
            render->camera = mainCamera.get();
            render1->InitCamera(mainCamera1.get());
            render1->camera = mainCamera1.get();
            //   UId->Create(render, static_cast<VulkanWindow*>(window1.get()));

            gameLogic = std::unique_ptr<GameLogic>(new GameLogic(render.get(), workspace, mainCamera.get()));
            gameLogic1 = std::unique_ptr<GameLogic>(new GameLogic(render1.get(), workspace, mainCamera1.get()));
            window->attach(gameLogic.get());
            window1->attach(gameLogic1.get());

        }
        void Start() {

            bool quit = false;

            while (!window->isClose() || !window1->isClose()) {
                Update();

            }

            //vkDeviceWaitIdle(VulkanRender::device);

        }
        void Update() {

         //   UId->Prepare();
            window->update();
            window1->update();
           // window1->update();
        }

        ~Engine() {
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
    try {

    }
    catch(std::exception& e){
        SDL_log(e.what());
    }
    return 0;
}

