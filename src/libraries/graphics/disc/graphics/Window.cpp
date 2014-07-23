#include "disc\graphics\Window.h"

#include "disc\graphics\DeviceContext.h"
#include "disc\graphics\GraphicsContext.h"

#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#include <Windows.h>

#include <cassert>
#include <functional>
#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

namespace
{
	std::function<void (uint16_t, uint16_t)> currentWindowResizeHandling;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
			{
				if (currentWindowResizeHandling)
					currentWindowResizeHandling(LOWORD(lParam), HIWORD(lParam));
				break;
			}
		case WM_SIZING:
			{
				if (currentWindowResizeHandling)
				{
					RECT* windowSize = reinterpret_cast<RECT*>(lParam);
					currentWindowResizeHandling(windowSize->right - windowSize->left, windowSize->bottom - windowSize->top);
				}
				break;
			}
			// don't handle WM_WINDOWPOSCHANGED message, the WINDOWPOS struct contains the whole window size
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	struct AssignResizeMessageHandling
	{
		explicit AssignResizeMessageHandling(GraphicsContext* graphicsContext)
			: graphicsContext_(graphicsContext)
		{
			using namespace std::placeholders;
			assert(! currentWindowResizeHandling);
			if (graphicsContext_)
				currentWindowResizeHandling = std::bind(&AssignResizeMessageHandling::handleResize, this, _1, _2);
		}
		~AssignResizeMessageHandling()
		{
			currentWindowResizeHandling = nullptr;
		}
		void handleResize(uint16_t width, uint16_t height)
		{
			graphicsContext_->resize(width, height);
		}
		GraphicsContext* graphicsContext_;
	};
}

struct Window::PImpl
{
	PImpl()
		: shouldClose_(false)
	{
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASSEX windowClass;
		memset(&windowClass, 0, sizeof(windowClass));
		windowClass.cbSize = sizeof(windowClass);
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = &WndProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = "MainWindowClass";

		if (! RegisterClassEx(&windowClass))
			throw std::runtime_error("Cannot register window class:" + std::to_string(GetLastError()));
		hWnd_ = CreateWindowEx(dwExStyle, windowClass.lpszClassName, "Disc window", WS_OVERLAPPEDWINDOW,
		                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	}
	WNDCLASS windowClass_;
	HWND hWnd_;
	std::unique_ptr<DeviceContext> deviceContext_;
	std::unique_ptr<GraphicsContext> graphicsContext_;
	bool shouldClose_;
};

Window::Window()
	: pImpl_(new PImpl())
{
	pImpl_->deviceContext_.reset(new DeviceContext(*this));
	pImpl_->graphicsContext_ = createGraphicsContext();
	Window::Dimensions windowDimensions = getDimensions();
	pImpl_->graphicsContext_->resize(windowDimensions.width, windowDimensions.height);
}

Window::~Window()
{
}

void Window::show()
{
	ShowWindow(pImpl_->hWnd_, SW_SHOW);
	UpdateWindow(pImpl_->hWnd_);
}

Window::Dimensions Window::getDimensions() const
{
	RECT windowDimensions;
	GetWindowRect(pImpl_->hWnd_, &windowDimensions);
	Window::Dimensions dimensions;
	dimensions.top = windowDimensions.top;
	dimensions.left = windowDimensions.left;
	dimensions.height= windowDimensions.bottom - windowDimensions.top;
	dimensions.width = windowDimensions.right - windowDimensions.left;
	return dimensions;
}

bool Window::aboutToClose() const
{
	return pImpl_->shouldClose_;
}

void Window::processMessages()
{
	MSG msg;
	AssignResizeMessageHandling catchResizeEvents(pImpl_->graphicsContext_.get());
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
		case WM_QUIT:
			pImpl_->shouldClose_ = true;
			break;
		default:
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			break;
		}
	}
}

void Window::render()
{
	if (pImpl_->graphicsContext_ && ! pImpl_->shouldClose_)
		pImpl_->graphicsContext_->render();
}

void* Window::getHandle() const
{
	return pImpl_->hWnd_;
}

std::unique_ptr<GraphicsContext> Window::createGraphicsContext()
{
	return std::unique_ptr<GraphicsContext>(new GraphicsContext(*pImpl_->deviceContext_));
}
