#ifdef _WIN64


#include "DirectRender.hpp"
#include "DirectWindow.h"
namespace BEbraEngine {

    void DirectRender::Create(BaseWindow* window) {
        auto win = dynamic_cast<DirectWindow*>(window);
        g_hWnd = win->getHandle();
        InitDevice();
    }
    HRESULT DirectRender::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
    {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ID3DBlob* pErrorBlob;
        hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
            dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
        if (FAILED(hr))
        {
            if (pErrorBlob != NULL)
                OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
            if (pErrorBlob) pErrorBlob->Release();
            return hr;
        }
        if (pErrorBlob) pErrorBlob->Release();

        return S_OK;
    }
    HRESULT DirectRender::InitDevice()
    { 
        HRESULT hr = S_OK;

        RECT rc;
        GetClientRect(g_hWnd, &rc);
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE(driverTypes);

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = g_hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
        {
            g_driverType = driverTypes[driverTypeIndex];
            hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
            if (SUCCEEDED(hr))
                break;
        }
        if (FAILED(hr))
            return hr;

        // Create a render target view
        ID3D11Texture2D* pBackBuffer = NULL;
        hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if (FAILED(hr))
            return hr;

        hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
        pBackBuffer->Release();
        if (FAILED(hr))
            return hr;

        g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

        // Setup the viewport
        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        g_pImmediateContext->RSSetViewports(1, &vp);

        // Compile the vertex shader
        ID3DBlob* pVSBlob = NULL;
        hr = CompileShaderFromFile(L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the vertex shader
        hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE(layout);

        // Create the input layout
        hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &g_pVertexLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Set the input layout
        g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

        // Compile the pixel shader
        ID3DBlob* pPSBlob = NULL;
        hr = CompileShaderFromFile(L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Create vertex buffer
        DirectX::XMFLOAT3 vertices[] =
        {
            DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
            DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
            DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f),
        };
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(DirectX::XMFLOAT3) * 3;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = vertices;
        hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
        if (FAILED(hr))
            return hr;

        // Set vertex buffer
        UINT stride = sizeof(DirectX::XMFLOAT3);
        UINT offset = 0;
        g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

        // Set primitive topology
        g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        return S_OK;
    }
    void DirectRender::Render()
    {
        // Clear the back buffer 
        float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
        g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

        // Render a triangle
        g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
        g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
        g_pImmediateContext->Draw(3, 0);

        // Present the information rendered to the back buffer to the front buffer (the screen)
        g_pSwapChain->Present(0, 0);
    }


    //--------------------------------------------------------------------------------------
    // Clean up the objects we've created
    //--------------------------------------------------------------------------------------
    void DirectRender::CleanupDevice()
    {
        if (g_pImmediateContext) g_pImmediateContext->ClearState();
        if (g_pVertexBuffer) g_pVertexBuffer->Release();
        if (g_pVertexLayout) g_pVertexLayout->Release();
        if (g_pVertexShader) g_pVertexShader->Release();
        if (g_pPixelShader) g_pPixelShader->Release();
        if (g_pRenderTargetView) g_pRenderTargetView->Release();
        if (g_pSwapChain) g_pSwapChain->Release();
        if (g_pImmediateContext) g_pImmediateContext->Release();
        if (g_pd3dDevice) g_pd3dDevice->Release();
    }
    DirectRender::DirectRender()
    {
    }
    DirectRender::~DirectRender()
    {
    }
   // using namespace DirectX;
   // struct SimpleVertex
   // {
   //     XMFLOAT3 Pos;
   // };
        //--------------------------------------------------------------------------------------
        // Global Variables
        //--------------------------------------------------------------------------------------



        //--------------------------------------------------------------------------------------
        // Global Variables
        //--------------------------------------------------------------------------------------



        //--------------------------------------------------------------------------------------
        // Forward declarations
        //--------------------------------------------------------------------------------------


        //--------------------------------------------------------------------------------------
        // Entry point to the program. Initializes everything and goes into a message processing 
        // loop. Idle time is used to render the scene.
        //--------------------------------------------------------------------------------------
        /*
        int main11()
        {
            glfwInit();

            auto win = glfwCreateWindow(800, 600, "pizda", NULL, NULL);
            g_hWnd = glfwGetWin32Window(win);

            if (FAILED(InitDevice()))
            {
                CleanupDevice();
                return 0;
            }

            while (!glfwWindowShouldClose(win))
            {
                glfwPollEvents();
                Render();
            }

            CleanupDevice();

        }
        */
    /*


        HRESULT InitDevice()
        {
            HRESULT hr = S_OK;

            RECT rc;
            GetClientRect(g_hWnd, &rc);
            UINT width = rc.right - rc.left;
            UINT height = rc.bottom - rc.top;

            UINT createDeviceFlags = 0;
#ifdef _DEBUG
            createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            D3D_DRIVER_TYPE driverTypes[] =
            {
                D3D_DRIVER_TYPE_HARDWARE,
                D3D_DRIVER_TYPE_WARP,
                D3D_DRIVER_TYPE_REFERENCE,
            };
            UINT numDriverTypes = ARRAYSIZE(driverTypes);

            D3D_FEATURE_LEVEL featureLevels[] =
            {
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
            };
            UINT numFeatureLevels = ARRAYSIZE(featureLevels);

            DXGI_SWAP_CHAIN_DESC sd;
            ZeroMemory(&sd, sizeof(sd));
            sd.BufferCount = 1;
            sd.BufferDesc.Width = width;
            sd.BufferDesc.Height = height;
            sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            sd.BufferDesc.RefreshRate.Numerator = 60;
            sd.BufferDesc.RefreshRate.Denominator = 1;
            sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            sd.OutputWindow = g_hWnd;
            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;
            sd.Windowed = TRUE;

            for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
            {
                g_driverType = driverTypes[driverTypeIndex];
                hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                    D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
                if (SUCCEEDED(hr))
                    break;
            }
            if (FAILED(hr))
                return hr;

            // Create a render target view
            ID3D11Texture2D* pBackBuffer = NULL;
            hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (FAILED(hr))
                return hr;

            hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
            pBackBuffer->Release();
            if (FAILED(hr))
                return hr;

            g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

            // Setup the viewport
            D3D11_VIEWPORT vp;
            vp.Width = (FLOAT)width;
            vp.Height = (FLOAT)height;
            vp.MinDepth = 0.0f;
            vp.MaxDepth = 1.0f;
            vp.TopLeftX = 0;
            vp.TopLeftY = 0;
            g_pImmediateContext->RSSetViewports(1, &vp);

            // Compile the vertex shader
            ID3DBlob* pVSBlob = NULL;
            hr = CompileShaderFromFile(L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob);
            if (FAILED(hr))
            {
                MessageBox(NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
                return hr;
            }

            // Create the vertex shader
            hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
            if (FAILED(hr))
            {
                pVSBlob->Release();
                return hr;
            }

            // Define the input layout
            D3D11_INPUT_ELEMENT_DESC layout[] =
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            };
            UINT numElements = ARRAYSIZE(layout);

            // Create the input layout
            hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
                pVSBlob->GetBufferSize(), &g_pVertexLayout);
            pVSBlob->Release();
            if (FAILED(hr))
                return hr;

            // Set the input layout
            g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

            // Compile the pixel shader
            ID3DBlob* pPSBlob = NULL;
            hr = CompileShaderFromFile(L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob);
            if (FAILED(hr))
            {
                MessageBox(NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
                return hr;
            }

            // Create the pixel shader
            hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
            pPSBlob->Release();
            if (FAILED(hr))
                return hr;

            // Create vertex buffer
            SimpleVertex vertices[] =
            {
                XMFLOAT3(0.0f, 0.5f, 0.5f),
                XMFLOAT3(0.5f, -0.5f, 0.5f),
                XMFLOAT3(-0.5f, -0.5f, 0.5f),
            };
            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.ByteWidth = sizeof(SimpleVertex) * 3;
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.CPUAccessFlags = 0;
            D3D11_SUBRESOURCE_DATA InitData;
            ZeroMemory(&InitData, sizeof(InitData));
            InitData.pSysMem = vertices;
            hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
            if (FAILED(hr))
                return hr;

            // Set vertex buffer
            UINT stride = sizeof(SimpleVertex);
            UINT offset = 0;
            g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

            // Set primitive topology
            g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            return S_OK;
        }


        //--------------------------------------------------------------------------------------
        // Render the frame
        //--------------------------------------------------------------------------------------
        void Render()
        {
            // Clear the back buffer 
            float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
            g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);

            // Render a triangle
            g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
            g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
            g_pImmediateContext->Draw(3, 0);

            // Present the information rendered to the back buffer to the front buffer (the screen)
            g_pSwapChain->Present(0, 0);
        }


        //--------------------------------------------------------------------------------------
        // Clean up the objects we've created
        //--------------------------------------------------------------------------------------
        void CleanupDevice()
        {
            if (g_pImmediateContext) g_pImmediateContext->ClearState();

            if (g_pVertexBuffer) g_pVertexBuffer->Release();
            if (g_pVertexLayout) g_pVertexLayout->Release();
            if (g_pVertexShader) g_pVertexShader->Release();
            if (g_pPixelShader) g_pPixelShader->Release();
            if (g_pRenderTargetView) g_pRenderTargetView->Release();
            if (g_pSwapChain) g_pSwapChain->Release();
            if (g_pImmediateContext) g_pImmediateContext->Release();
            if (g_pd3dDevice) g_pd3dDevice->Release();
        }
    */
}
#endif