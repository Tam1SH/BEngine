#pragma once
#if defined(_WIN64) && defined(BEBRA_USE_GLFW)
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>
#include "platform_window.hpp"
#include "AbstractRenderSystem.hpp"
#include <d3dcompiler.h>
#include <list>
#include "RenderBuffer.hpp"
#include "RenderObject.h"
#include "Vertex.h"
#include "Camera.hpp"
namespace BEbraEngine {
    class DirectWindow;
	class DirectRender : public AbstractRender {
    private:
        HINSTANCE               g_hInst = NULL;
        HWND                    g_hWnd = NULL;
        D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
        D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
        ID3D11Device* g_pd3dDevice = NULL;
        ID3D11DeviceContext* g_pImmediateContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        ID3D11RenderTargetView* g_pRenderTargetView = NULL;
        ID3D11VertexShader* g_pVertexShader = NULL;
        ID3D11PixelShader* g_pPixelShader = NULL;
        ID3D11InputLayout* g_pVertexLayout = NULL;
        ID3D11Texture2D* g_pDepthStencil = NULL;             // Текстура буфера глубин
        ID3D11DepthStencilView* g_pDepthStencilView = NULL;          // Объект вида, буфер глубин

        ID3D11Buffer* g_pVertexBuffer = NULL;
        ID3D11Buffer* indicesBuffer = NULL;
        std::list<std::weak_ptr<RenderObject>> objects;
    private:

        HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        HRESULT InitDevice(DirectWindow* window);
        HRESULT InitResource();
        void CleanupDevice();


    public:
        Camera* camera;
		void Create(BaseWindow* window) override;


        void AddObject(std::weak_ptr<RenderObject> object) override;
        void InitCamera(Camera* alloced_camera) override;
        RenderBuffer* CreateIndexBuffer(std::vector<uint32_t> indices) override;
        RenderBuffer* CreateVertexBuffer(std::vector<Vertex> vertices) override;
        RenderBuffer* CreateUniformBuffer(size_t size) override;

        RenderBuffer* CreateStorageBuffer(size_t size);


        void Render();


        DirectRender();
        ~DirectRender();
    private:
        struct Buffer;
	};
}
#endif