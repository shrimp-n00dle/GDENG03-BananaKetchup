#include "TicketHolder.h"


//Initialization
bananaCatsup::TicketHolder::TicketHolder()
{
}

bananaCatsup::TicketHolder::~TicketHolder()
{
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
        pTextFormat_,    // The text format.
        layoutRect,       // The region of the window where the text will be rendered.
        pBlackBrush_     // The brush used to draw the text.
    );


    return S_OK;
}

