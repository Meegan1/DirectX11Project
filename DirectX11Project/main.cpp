#include <windows.h>

LPCTSTR WndClassName = L"firstwindow"; // window class name
HWND hwnd = NULL; // window handler

const int Width = 800; // define width of window
const int Height = 600; // define height of window

bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed);

int messageloop();

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	messageloop();
	return 0;
}

/*
int ShowWnd - How the window should be displayed.Some common commands are SW_SHOWMAXIMIZED, SW_SHOW, SW_SHOWMINIMIZED.

int width - Width of the window in pixels

int height - Height of the window in pixels

bool windowed - False if the window is fullscreen and true if the window is windowed
*/

bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(NULL,
		WndClassName,
		L"Project",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);

	return true;
}

int messageloop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) // while a message
	{
		/*
		LPMSG lpMsg - This is the pointer to a our message structure

		HWND hWnd - This is the handle to the window that is sending the message.If this is set to null, it will get messages from any window in the current program.

		UINT wMsgFilterMin - Specifies the value of the first message in the range of messages to be examined.If wMsgFilterMin and wMsgFilterMax are both set to zero, PeekMessage will examine all messages.

		UINT wMsgFilterMax - Specifies the value of the last message in the range of messages to be examined.

		UINT wRemoveMsg - This specifies how the message will be handled.We set to PM_REMOVE so the message will be deleted after we read it.
		*/
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // close if quit message
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// run game code
		}
	}
	return msg.wParam;
}

// Message Processing
LRESULT CALLBACK WndProc(HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			if (MessageBox(0, L"Are you sure you want to exit?",
				L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// default windows procedure function. We call this at the end to take care of 
	// all the messages we recieve but don't take care of ourselves.
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}