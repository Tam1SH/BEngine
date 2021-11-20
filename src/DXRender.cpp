#include "stdafx.h"
#include "DirectWindow.hpp"
#if defined(_WIN64)
#include "RenderBuffer.hpp"
#include "RenderObject.hpp"
#include "Vertex.hpp"
#include "Camera.hpp"
#include "DXRender.hpp"
#include "Camera.hpp"
#include "DXRenderObjectFactory.hpp"
namespace BEbraEngine {

    struct DXRender::DXBuffer : public RenderBuffer {
        ID3D11DeviceContext* g_pImmediateContext;
        ID3D11Buffer* buf;
        size_t size;

        void setData(void* data, size_t size, size_t offset) override {
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
            g_pImmediateContext->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
            memcpy(mappedResource.pData, data, size);
            g_pImmediateContext->Unmap(buf, 0);
            //g_pImmediateContext->UpdateSubresource(buf, 0, NULL, data, 0, 0);
        }
        void Destroy() override {
            throw std::exception("sasi zalypy");
        }
    };

    void DXRender::Create(BaseWindow* window) {
        auto win = dynamic_cast<DXWindow*>(window);
        g_hWnd = win->getHWND();
        InitDevice(win);
        InitResource();

        factory = std::make_unique<DXRenderObjectFactory>();
    }
    void DXRender::addObject(std::shared_ptr<RenderObject> object)
    {
        objects.push_back(object);
    }

    void DXRender::addLight(std::shared_ptr<PointLight> light)
    {
    }

    void DXRender::removeObject(std::shared_ptr<RenderObject> object)
    {
    }

    void DXRender::removeLight(std::shared_ptr<PointLight> light)
    {
    }

    void DXRender::addGlobalLight(std::shared_ptr<DirectionLight> globalLight)
    {
    }

    void DXRender::InitCamera(Camera* camera)
    {
        auto view = new RenderBufferView();
        view->availableRange = sizeof(Matrix4) * 2 + sizeof(Vector4);
        view->buffer = std::shared_ptr<RenderBuffer>(createStorageBuffer(view->availableRange));

        camera->cameraData = view;
        this->camera = camera;
    }
    RenderBuffer* DXRender::createIndexBuffer(std::vector<uint32_t> indices)
    {

        return createBuffer(indices.data(), sizeof(indices[0]) * indices.size(), D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER);
        /*
        auto buff = new DXBuffer();
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(indices[0]) * indices.size();
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        buff->size = bd.ByteWidth;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = indices.data();
        //g_pd3dDevice->Crreate
        g_pd3dDevice->CreateBuffer(&bd, &InitData, &buff->buf);
        buff->g_pImmediateContext = g_pImmediateContext;

        return buff;
        */
    }
    RenderBuffer* DXRender::createUniformBuffer(size_t size) {

        return createBuffer(0, size, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER);
        /*
        auto buff = new DXBuffer();
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = size;
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bd.MiscFlags = 0;
        g_pd3dDevice->CreateBuffer(&bd, NULL, &buff->buf);
        buff->g_pImmediateContext = g_pImmediateContext;
        return buff;
        */
    }
    RenderBuffer* DXRender::createBuffer(void* data, size_t size, D3D11_USAGE usage, D3D11_BIND_FLAG type) {
        auto buff = new DXBuffer();
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = usage;
        bd.ByteWidth = size;
        bd.BindFlags = type;
        if (type == D3D11_BIND_INDEX_BUFFER || type == D3D11_BIND_VERTEX_BUFFER)
            bd.CPUAccessFlags = 0;
        else
            bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        buff->size = bd.ByteWidth;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = data;
        if(!data)
            g_pd3dDevice->CreateBuffer(&bd, NULL, &buff->buf);
        else 
            g_pd3dDevice->CreateBuffer(&bd, &InitData, &buff->buf);
        buff->g_pImmediateContext = g_pImmediateContext;
        buff->size = size;
        return buff;
    }
    RenderBuffer* DXRender::createStorageBuffer(size_t size) {

        return createBuffer(0, size, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER);
        /*
        auto buff = new DXBuffer();
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = size;
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bd.MiscFlags = 0;
        g_pd3dDevice->CreateBuffer(&bd, NULL, &buff->buf);
        buff->g_pImmediateContext = g_pImmediateContext;
        return buff;
        */
    }
    void DXRender::DestroyBuffer(RenderBuffer* buffer)
    {
    }
    IRenderObjectFactory* DXRender::getRenderObjectFactory()
    {
        return factory.get();
    }
    size_t DXRender::alignmentBuffer(size_t originalSize, AbstractRender::TypeBuffer type)
    {
        return originalSize;
    }
    void DXRender::drawFrame()
    {
        // Clear the back buffer 
        float ClearColor[4] = { 1, 215 / 255.f, 230 / 255.f, 1.0f }; // red,green,blue,alpha
        g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
        g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
        // g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
         // Render a triangle
        camera->Update();
        auto buf = static_cast<DXBuffer*>(camera->cameraData->buffer.get());



        
        for (auto object : objects) {
            object->update();
            const auto data = static_cast<const DXBuffer*>(object->matrix.lock()->buffer.get());
            g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
            g_pImmediateContext->VSSetConstantBuffers(1, 1, &data->buf);
            g_pImmediateContext->VSSetConstantBuffers(2, 1, &buf->buf);
            g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
            auto EBO = static_cast<const DXBuffer*>(object->model->meshes[0].indices_view->buffer.get());
            auto VBO = static_cast<const DXBuffer*>(object->model->meshes[0].vertices_view->buffer.get());

            //g_pImmediateContext->UpdateSubresource()
            UINT stride = sizeof(Vertex);
            UINT offset = 0;
            g_pImmediateContext->IASetVertexBuffers(0, 1, &VBO->buf, &stride, &offset);
            g_pImmediateContext->IASetIndexBuffer(EBO->buf, DXGI_FORMAT_R32_UINT, 0);

            g_pImmediateContext->DrawIndexed(object->model->meshes[0].indices.size(), 0, 0);
        }


        // Present the information rendered to the back buffer to the front buffer (the screen)
        g_pSwapChain->Present(0, 0);
    }
    AbstractRender::Type DXRender::getType()
    {
        return AbstractRender::Type::DirectX;
    }
    RenderBuffer* DXRender::createVertexBuffer(std::vector<Vertex> vertices) {

        return createBuffer(vertices.data(), sizeof(vertices[0]) * vertices.size(), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER);
        /*
        
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(vertices[0]) * vertices.size();
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        buff->size = bd.ByteWidth;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = vertices.data();
        g_pd3dDevice->CreateBuffer(&bd, &InitData, &buff->buf);
        
        // Set vertex buffer
        UINT stride = sizeof(vertices[0]);
        UINT offset = 0;
        g_pImmediateContext->IASetVertexBuffers(0, 1, &buff->buf, &stride, &offset);
        buff->g_pImmediateContext = g_pImmediateContext;
        return buff;
        */

    }
    HRESULT DXRender::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
    HRESULT DXRender::InitDevice(DXWindow* window)
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

        ID3D11Texture2D* pBackBuffer = NULL;
        hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if (FAILED(hr))
            return hr;

        hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
        pBackBuffer->Release();
        if (FAILED(hr))
            return hr;


        D3D11_TEXTURE2D_DESC descDepth; 
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = width;            
        descDepth.Height = height;    
        descDepth.MipLevels = 1;            
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; 
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;       
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        hr = g_pd3dDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);

        if (FAILED(hr)) return hr;

        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;           
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;

        hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);

        if (FAILED(hr)) return hr;



        g_pImmediateContext->OMSetRenderTargets(2, &g_pRenderTargetView, g_pDepthStencilView);

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
        hr = CompileShaderFromFile(L"Tutorial03.hlsl", "VS", "vs_5_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // ñreate the vertex shader
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
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }
          //  { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector4) + sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
          //  { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Vector4) + sizeof(Vector3) + sizeof(Vector2), D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        UINT numElements = ARRAYSIZE(layout);

        // ñreate the input layout
        hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &g_pVertexLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return hr;

        // Set the input layout
        g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
        // Compile the pixel shader
        ID3DBlob* pPSBlob = NULL;
        hr = CompileShaderFromFile(L"Tutorial03.hlsl", "PS", "ps_5_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(NULL,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // ñreate the pixel shader
        hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;

        g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
       
        return S_OK;
    }



    HRESULT DXRender::InitResource() {
        // ñreate vertex buffer
        HRESULT hr = 0;
       // DirectX::XMFLOAT3 vertices[] =
      //  {
      //      DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
     //       DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
     ///       DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f),
     //   };
        /*
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(Vertex) * vertices.size();
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = vertices.data();
        hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
        if (FAILED(hr))
            return hr;
            */
      //  DXBuffer* vertbuf = dynamic_cast<DXBuffer*>(createVertexBuffer(vertices));
      //  auto indicesbuf = dynamic_cast<DXBuffer*>(createIndexBuffer(indices));
        // Set vertex buffer
       // UINT stride = sizeof(Vertex);
       // UINT offset = 0;
      //  g_pImmediateContext->IASetVertexBuffers(0, 1, &vertbuf->buf, &stride, &offset);
       // g_pImmediateContext->IASetIndexBuffer(indicesbuf->buf, DXGI_FORMAT_R32_UINT, 0);
        // Set primitive topology
        g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        if (FAILED(hr))
            return hr;


        return S_OK;

    }


    //--------------------------------------------------------------------------------------
    // Clean up the objects we've created
    //--------------------------------------------------------------------------------------
    void DXRender::CleanupDevice()
    {
        if (g_pImmediateContext) g_pImmediateContext->ClearState();
        if (g_pVertexLayout) g_pVertexLayout->Release();
        if (g_pVertexShader) g_pVertexShader->Release();
        if (g_pPixelShader) g_pPixelShader->Release();
        if (g_pDepthStencil) g_pDepthStencil->Release();
        if (g_pDepthStencilView) g_pDepthStencilView->Release();
        if (g_pRenderTargetView) g_pRenderTargetView->Release();
        if (g_pSwapChain) g_pSwapChain->Release();
        if (g_pImmediateContext) g_pImmediateContext->Release();
        if (g_pd3dDevice) g_pd3dDevice->Release();
    }
    DXRender::DXRender()
    {
    }
    DXRender::~DXRender()
    {
        CleanupDevice();
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

            // ñreate a render target view
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

            // ñreate the vertex shader
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

            // ñreate the input layout
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

            // ñreate the pixel shader
            hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
            pPSBlob->Release();
            if (FAILED(hr))
                return hr;

            // ñreate vertex buffer
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
            hr = g_pd3dDevice->createBuffer(&bd, &InitData, &g_pVertexBuffer);
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