#pragma once
#include "platform_window.hpp"
#if defined(_WIN64)
#include "AbstractRender.hpp"
#include "stdafx.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <list>



namespace BEbraEngine {
    class DXWindow;
    class Camera;
    class RenderBuffer;
    class Vertex;
    class RenderObject;
}
namespace BEbraEngine {
   
	class DXRender : public AbstractRender {
    public:
		void create(BaseWindow* window) override;

        RenderBuffer* createIndexBuffer(std::vector<uint32_t> indices) override;
        RenderBuffer* createVertexBuffer(std::vector<Vertex> vertices) override;
        RenderBuffer* createUniformBuffer(uint32_t size) override;
        RenderBuffer* createStorageBuffer(uint32_t size) override;
        void destroyBuffer(RenderBuffer* buffer) override;

        void selectMainCamera(Camera* camera) override;
        void addObject(std::shared_ptr<RenderObject> object) override;
        void addLight(std::shared_ptr<PointLight> light) override;
        void removeObject(std::shared_ptr<RenderObject> object) override;
        void removeLight(std::shared_ptr<PointLight> light) override;
        void addGlobalLight(std::shared_ptr<DirectionLight> globalLight) override;
        void addCamera(std::shared_ptr<Camera> camera) override;
        void removeCamera(std::shared_ptr<Camera> camera) override;
        IRenderObjectFactory* getRenderObjectFactory() override;
        uint32_t alignmentBuffer(uint32_t originalSize, AbstractRender::TypeBuffer type) override;
        void drawFrame() override;
        Type getType() override;
        DXRender();
        ~DXRender();

    private:
        struct DXBuffer;
    private:

        HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        HRESULT InitDevice(DXWindow* window);
        HRESULT InitResource();
        void CleanupDevice();

        RenderBuffer* createBuffer(void* data, uint32_t size, D3D11_USAGE usage, D3D11_BIND_FLAG type);

    private:
        HINSTANCE               g_hInst = NULL;
        HWND                    g_hWnd = NULL;
        D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
        D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
        ID3D11Device*           g_pd3dDevice = NULL;
        ID3D11DeviceContext*    g_pImmediateContext = NULL;
        IDXGISwapChain*         g_pSwapChain = NULL;
        ID3D11RenderTargetView* g_pRenderTargetView = NULL;
        ID3D11VertexShader*     g_pVertexShader = NULL;
        ID3D11PixelShader*      g_pPixelShader = NULL;
        ID3D11InputLayout*      g_pVertexLayout = NULL;
        ID3D11Texture2D*        g_pDepthStencil = NULL;             // Текстура буфера глубин
        ID3D11DepthStencilView* g_pDepthStencilView = NULL;          // Объект вида, буфер глубин

        std::list<std::shared_ptr<RenderObject>> objects;
        std::list<std::shared_ptr<PointLight>> lights;
        std::unique_ptr<IRenderObjectFactory> factory;
        std::shared_ptr<DirectionLight> globalLight;

    };
}
#endif