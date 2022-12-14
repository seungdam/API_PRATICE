#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"

// ****운영체제가 메세지 발생 시 호출하는 함수 (callback 함수)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // 응용프로그램 핸들을 저장하기 위해 전역변수로 선언
LPCTSTR lpszClass = TEXT("Menu"); // 클래스 명을 저장하기 위한 문자열 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

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
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	
	// 액셀러레이터 핸들
	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// 메세지 루프
	while (GetMessage(&Message, NULL, 0, 0) > 0) {
		if (!TranslateAccelerator(hWnd, hAccel, &Message)) { // 만약 들어온 키입력이 핫키(Accelerator)가 아니라면.. 
			TranslateMessage(&Message); // 키보드 입력을 응용프로그램이 쉽게 이해하게 번역
			DispatchMessage(&Message); // 발생한 메세지를 프로세스로 전달
		}
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // 각 메뉴에 대한 부가 처리정보는 LOWORD(wParam)에 있다. 
		case ID_MENU_MENU1:
			MessageBox(hWnd, L"Menu1 입니다.", L"Menu1", MB_OK);
			break;
		case ID_MENU_MENU2:
			MessageBox(hWnd, L"Menu2 입니다.", L"Menu2", MB_OK);
			break;
		case ID_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}