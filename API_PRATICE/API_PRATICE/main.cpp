#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

// ****운영체제가 메세지 발생 시 호출하는 함수 (callback 함수)
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // 응용프로그램 핸들을 저장하기 위해 전역변수로 선언
LPCTSTR lpszClass = TEXT("KeyBoard_Action"); // 클래스 명을 저장하기 위한 문자열 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpszCmdParam, int nCmdShow) {

	// 윈도우즈의 구체적인 속성을 나타내는 윈도우 클래스 구조체를 초기화.
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스를 운영체제에 등록 : 앞으로 이런 스타일의 윈도우창을 생성할 것이다.
	RegisterClass(&wndClass);

	HWND hWnd;
	MSG Message;
	g_hInst = hInstance; // 글로벌 전역변수에 넣어준다.

	// 윈도우즈 생성
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	// 윈도우즈 출력
	ShowWindow(hWnd, nCmdShow);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

}