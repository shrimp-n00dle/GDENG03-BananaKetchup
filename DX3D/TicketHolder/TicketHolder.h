#pragma once
#include <dwrite.h>
#include <d2d1.h>
#include <wrl.h>

namespace bananaCatsup
{
	class TicketHolder
	{
	public:
		TicketHolder();
		~TicketHolder();

		HRESULT Initialize(HWND hwndParent);

		HWND GetHwnd() { return hwnd_; }

	private:
		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources();
		void DiscardDeviceResources();
		HRESULT drawText();

		void OnResize(
			UINT width,
			UINT height
		);

		static LRESULT CALLBACK WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

	private:
		//holding the text string
		const wchar_t* wszText_;
		UINT32 cTextLength_ = 0;

	private:
		HWND hwnd_;

		// how much to scale a design that assumes 96-DPI pixels
		float dpiScaleX_;
		float dpiScaleY_;

		Microsoft::WRL::ComPtr <IDWriteFactory> pDWriteFactory_{};
		Microsoft::WRL::ComPtr <IDWriteTextFormat> pTextFormat_{};

		//Direct2D
		Microsoft::WRL::ComPtr <ID2D1Factory> pD2DFactory_{};
		Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> pRT_{};
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBlackBrush_{};

	};
}
