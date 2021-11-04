//TODO: сделать бы так, чтобы при создании дескриптора его layout можно было бы 
//по имени выбирать в классе DescriptorLayout или сувать туда структуру, которая 
//соответствовало бы какому-нибудь из layout и возвращала бы его(Думаю енам для всей этой поеботы сделать и не ебаться)
// TODO: сделать кластерный рендер
// TODO: реализация меша для объектов рендера
//TODO: заюзать для лайаутов хеш таблицу
//TODO: сделать неймспейсы для разных частей движка 
//TODO: начать делать хотя бы что-то со звуком 
/*
TODO: подумать над реализацей:
****************************************************************************************
 * воркспейса и вообще, хорошая ли это затея разделять эту сущность на редактор и логику
 * абстрагировать доступ к рендеру, т.к их будет как минимум 2(около этого сделано)
 * сделать абстрактные классы для окна т.к я хуй знает что я буду делать и вообще охото на пк юзать GLFW (сделано) 
 * также и для физики так как возможно я буду и другой физ. движок прикручивать(есть смысл?)
 * сделать свой класс векторов чтобы потом не ебаться с разными векторами из разных либ(сделано)
 * ну и также для объектов рендера
 * присобачить Mono
 * как-то вертеть данные с физики до рендера(какая-то хуйня реализована в Transform, но это крайне плохое решение)
 * реализовать каким-то хуем папочку в ведроиде, откуда данные таксать буду
 * сделать разные интерфейсы для выделение объектов из пулов и уникальных объектов,а также для их рендеринга.
****************************************************************************************
Вывод: В общем подумать над абстрагированием основных элементов движка для возможной замены их реализации
*/




#include "stdafx.h"
#define NOMINMAX
//#include "GLWindow.h"
//#include "GLRender.h"
#include "BaseRenderWindow.hpp"
#include "DebugUI.hpp"
#include "Physics.hpp"
#include "WorkSpace.hpp"

#include "VulkanRender.hpp"
#include "GameLogic.hpp"
#include "Vector2.hpp"
#include "VulkanWindow.hpp"
#include "DirectWindow.hpp"
#include "DirectRender.hpp"
#include "Input.hpp"
#include "Time.hpp"

namespace BEbraEngine {

    class Engine {
    public:
        //std::shared_ptr<DirectRender> render;
        std::shared_ptr<VulkanRender> render1;

        std::unique_ptr<BaseWindow> window;
        std::unique_ptr<BaseWindow> window1;
        std::shared_ptr<WorkSpace> workspace;
        std::shared_ptr<WorkSpace> workspace1;
        std::unique_ptr<GameLogic> gameLogic;
        std::unique_ptr<GameLogic> gameLogic1;
        std::unique_ptr<Camera> mainCamera;
        std::unique_ptr<Camera> mainCamera1;

    public:
        void Init(int i) {
            if (i == 2) {

                render1 = std::unique_ptr<VulkanRender>(new VulkanRender());
                window1 = std::unique_ptr<VulkanWindow>(new VulkanWindow(render1.get()));
                window1->CreateWindow(Vector2(800, 600), "BEEEBRA!!!");
                mainCamera1 = std::unique_ptr<Camera>(new Camera(glm::vec3(0, 1, 10)));
                workspace1 = std::shared_ptr<WorkSpace>(new WorkSpace());
                render1->InitCamera(mainCamera1.get());
                render1->camera = mainCamera1.get();
                gameLogic1 = std::unique_ptr<GameLogic>(new GameLogic(render1, workspace1, mainCamera1.get()));
                window1->attach(gameLogic1.get());
                
            }


            
            

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
   // while (true) {
        BEbraEngine::Engine engine;
        engine.Init(2);
  //  }
    engine.Start();

    return 0;
}


