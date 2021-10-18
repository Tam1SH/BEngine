#pragma once
#if defined(_WIN64) && defined(BEBRA_USE_GLFW)
#include <d3d11.h>
#include <d3dx11.h>
#include <DirectXMath.h>
#include "platform_window.hpp"
#include "AbstractRenderSystem.hpp"
#include <d3dcompiler.h>

#include "RenderBuffer.hpp"
#include "Vertex.h"
namespace BEbraEngine {
	class DirectRender : public AbstractRender {
    public:
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
        ID3D11Buffer* g_pVertexBuffer = NULL;

    public:

		void Create(BaseWindow* window) override;

        HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        HRESULT InitDevice();
        RenderBuffer* CreateIndexBuffer(std::vector<uint32_t> indices) override;
        RenderBuffer* CreateVertexBuffer(std::vector<Vertex> vertices) override;
        RenderBuffer* CreateUniformBuffer(size_t size) override;
        HRESULT InitResource();

        void Render();

        void CleanupDevice();

        DirectRender();
        ~DirectRender();
    private:
        struct Buffer;
	};
}
#endif