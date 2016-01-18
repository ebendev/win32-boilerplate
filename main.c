#include <Windows.h>

LRESULT CALLBACK
MessageCallback(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS window_class;
	memset(&window_class, 0, sizeof(window_class));
	window_class.lpfnWndProc = MessageCallback;
	window_class.hInstance = hInstance;
	window_class.hCursor = LoadCursor(hInstance, IDC_ARROW);
	window_class.lpszClassName = L"Win32BoilerplateWindowClass";

	if (!RegisterClass(&window_class)) { return (int) GetLastError(); }

	HWND window_handle = CreateWindow(
		window_class.lpszClassName,
		L"Win32Boilerplate",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) { break; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}
