#include "TicketHolder.h"


//Initialization
bananaCatsup::TicketHolder::TicketHolder()
{
}

bananaCatsup::TicketHolder::~TicketHolder()
{
}

HRESULT bananaCatsup::TicketHolder::Initialize(HWND hwndParent)
{
    WNDCLASSEX wcex;

    //get the dpi information
    HDC screen = GetDC(0);
    dpiScaleX_ = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
    dpiScaleY_ = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
    ReleaseDC(0, screen);

    HRESULT hr = S_OK;

    ATOM atom;

    // Register window class.
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = bananaCatsup::TicketHolder::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hIcon = LoadIcon(
        NULL,
        IDI_APPLICATION);
    wcex.hCursor = LoadCursor(
        NULL,
        IDC_ARROW);
    wcex.lpszClassName = TEXT("D2DSimpleText");
    wcex.hIconSm = LoadIcon(
        NULL,
        IDI_APPLICATION
    );

    atom = RegisterClassEx(
        &wcex
    );

    hr = atom ? S_OK : E_FAIL;

    // Create window.
    hwnd_ = CreateWindow(
        TEXT("D2DSimpleText"),
        TEXT(""),
        WS_CHILD,
        0,
        0,
        static_cast<int>(640.0f / dpiScaleX_),
        static_cast<int>(480.0f / dpiScaleY_),
        hwndParent,
        NULL,
        HINST_THISCOMPONENT,
        this
    );

    if (SUCCEEDED(hr))
    {
        hr = hwnd_ ? S_OK : E_FAIL;
    }

    if (SUCCEEDED(hr))
    {
        hr = CreateDeviceIndependentResources(
        );
    }


    if (SUCCEEDED(hr))
    {
        ShowWindow(
            hwnd_,
            SW_SHOWNORMAL
        );


        UpdateWindow(
            hwnd_
        );
    }

    if (SUCCEEDED(hr))
    {
        DrawD2DContent();
    }

    return hr;
}


HRESULT bananaCatsup::TicketHolder::CreateDeviceIndependentResources()
{
    HRESULT hr;
    // the root factory interface for all Direct2D objects.
     hr = D2D1CreateFactory(
         D2D1_FACTORY_TYPE_SINGLE_THREADED,
         pD2DFactory_.GetAddressOf()
    );

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            &pDWriteFactory_//reinterpret_cast<IUnknown**>(&pDWriteFactory_)
        );
    }

    wszText_ = L"Hello World using  DirectWrite!";
    cTextLength_ = (UINT32)wcslen(wszText_);

    if (SUCCEEDED(hr))
    {
        hr = pDWriteFactory_->CreateTextFormat(
            L"Gabriola",                // Font family name.
            NULL,                       // Font collection (NULL sets it to use the system font collection).
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            72.0f,
            L"en-us",
            &pTextFormat_
        );
    }

    // Center align (horizontally) the text.
    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    return hr;
}

HRESULT bananaCatsup::TicketHolder::CreateDeviceResources()
{
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hwnd_, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    if (!pRT_)
    {
        // Create a Direct2D render target.
        hr = pD2DFactory_->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                hwnd_,
                size
            ),
            &pRT_
        );

        // Create a black brush.
        if (SUCCEEDED(hr))
        {
            hr = pRT_->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &pBlackBrush_
            );
        }
    }

    return hr;
}

void bananaCatsup::TicketHolder::DiscardDeviceResources()
{
    //Will print prompts here
    //SafeRelease(&pRT_);
    //SafeRelease(&pBlackBrush_);
}

HRESULT bananaCatsup::TicketHolder::drawText()
{
    RECT rc;

    GetClientRect(
        hwnd_,
        &rc
    );

    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<FLOAT>(rc.left) / dpiScaleX_,
        static_cast<FLOAT>(rc.top)  / dpiScaleY_,
        static_cast<FLOAT>(rc.right - rc.left) / dpiScaleX_,
        static_cast<FLOAT>(rc.bottom - rc.top) / dpiScaleY_
    );

    // Use the DrawText method of the D2D render target interface to draw.

    pRT_->DrawText(
        wszText_,        // The string to render.
        cTextLength_,    // The string's length.
        pTextFormat_.Get(),    // The text format.
        layoutRect,       // The region of the window where the text will be rendered.
        pBlackBrush_.Get()     // The brush used to draw the text.
    );


    return S_OK;
}


HRESULT bananaCatsup::TicketHolder::DrawD2DContent()
{
    HRESULT hr;


    hr = CreateDeviceResources();

    if (!(pRT_->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        pRT_->BeginDraw();

        pRT_->SetTransform(D2D1::IdentityMatrix());

        pRT_->Clear(D2D1::ColorF(D2D1::ColorF::White));

        // Call the DrawText method of this class.
        hr = drawText();

        if (SUCCEEDED(hr))
        {
            hr = pRT_->EndDraw(
            );
        }
    }

    if (FAILED(hr))
    {
        DiscardDeviceResources();
    }


    return hr;
}


void bananaCatsup::TicketHolder::OnResize(UINT width, UINT height)
{
    if (pRT_)
    {
        D2D1_SIZE_U size;
        size.width = width;
        size.height = height;
        pRT_->Resize(size);
    }
}

LRESULT CALLBACK bananaCatsup::TicketHolder::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        TicketHolder* pSimpleText = (TicketHolder*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pSimpleText));

        return 1;
    }

    TicketHolder* pSimpleText = reinterpret_cast<TicketHolder*>(
        ::GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (pSimpleText)
    {
        switch (message)
        {
        case WM_SIZE:
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            pSimpleText->OnResize(width, height);
        }
        return 0;

        case WM_PAINT:
        case WM_DISPLAYCHANGE:
        {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            pSimpleText->DrawD2DContent();
            EndPaint(
                hwnd,
                &ps
            );
        }
        return 0;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        return 1;
        }
    }
    return DefWindowProc(
        hwnd,
        message,
        wParam,
        lParam
    );
}

