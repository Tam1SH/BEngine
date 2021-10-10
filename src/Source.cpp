
//TODO: ������� �� ���, ����� ��� �������� ����������� ��� layout ����� ���� �� 
//�� ����� �������� � ������ DescriptorLayout ��� ������ ���� ���������, ������� 
//��������������� �� ������-������ �� layout � ���������� �� ��� 
// TODO: �������� ��� ����������� ������ �������� Draw(), �.� � ������� ���������� ���� �� ����� ���������� ���������� � ����� ������� ������ ��� �������.
// TODO: ������� ���������� ������
// TODO: ���������� ���� ��� �������� �������
//TODO: ������� ��� �������� ��� �������
//TODO: ������� ���������� ��� ������ ������ ������ 
//TODO: ������ ������ ���� �� ���-�� �� ������ 
/* 
TODO: �������� ��� ����������:
****************************************************************************************
 * ���������� � ������, ������� �� ��� ����� ��������� ��� �������� �� �������� � ������
 * �������������� ������ � �������, �.� �� ����� ��� ������� 2 (����� ������� ����?) 
 * ������� ����������� ������ ��� ������� � ���� �.� � ��� ����� ��� � ���� ������ � ������ ����� �� �� ����� GLFW
 * ����� � ��� ������ ��� ��� �������� � ���� � ������ ���. ������ ������������
 * ������� ���� ����� �������� ����� ����� �� ������� � ������� ��������� �� ������ ��� 
 * �� � ����� ��� �������� ������� 
 * �������� ����� ������� ������ ��� ��� ��������(like godot)?
****************************************************************************************
�����: � ����� �������� ��� ���������������� �������� ��������� ������ ��� ��������� ������ �� ����������
*/
//�������:
/*
����� ��������� �� ������ ������ ��� ����� ����,�.� ��� ���� ����� �� ��� ��������?

*/

#include "DebugUI.h"
#include "Physics.hpp"
#include "WorkSpace.h"
#include "RenderWindow.hpp"
#include "VulkanRender.h"
#include "GameLogic.h"
#include "Vector.h"
namespace BEbraEngine {

    class Engine {
    public:

        std::shared_ptr<VulkanRender> render;
        std::unique_ptr<Physics> physics;
      //  std::unique_ptr<DebugUI> UId;
        std::unique_ptr<RenderWindow> window;
        std::unique_ptr<BaseWindow> window1;
        std::shared_ptr<WorkSpace> workspace;
        std::unique_ptr<GameLogic> gameLogic;
    public:
        void Init() {
            window1 = std::unique_ptr<VulkanWindow>(new VulkanWindow());
            window1->SetSurfaceType(BaseWindow::Vulkan);
            window1->CreateWindow(Vector(), Vector(1300, 800));
            static_cast<VulkanWindow*>(window1.get())->InitRender();
            workspace = std::shared_ptr<WorkSpace>(new WorkSpace());

       //     UId = std::make_unique<DebugUI>();
                
            
          //  UId->SetWorkSpace(workspace);
            auto render = static_cast<VulkanWindow*>(window1.get())->GetRender();
         //   UId->Create(render, static_cast<VulkanWindow*>(window1.get()));

            gameLogic = std::unique_ptr<GameLogic>(new GameLogic(render, workspace));

        }
        void Start() {

            bool quit = false;

            while (!quit) {
                SDL_Event event;
                SDL_GetMouseState(Input::mouse_x, Input::mouse_y);
                while (SDL_PollEvent(&event)) {
                //    ImGui_ImplSDL2_ProcessEvent(&event);
                    if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
                        quit = true;
                    }
                    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        window1->ResizeCallback();
                    }
                    if (event.type == SDL_WINDOWEVENT_CLOSE) {

                    }

                }
                Update();

            }

            vkDeviceWaitIdle(VulkanRender::device);

        }
        void Update() {

         //   UId->Prepare();
            gameLogic->Update();
            window1->UpdateFrame();
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
    try {
        engine.Init();
        engine.Start();
    }
    catch(std::exception& e){
        SDL_log(e.what());
    }
    return 0;
}



