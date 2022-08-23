#define _CRT_SECURE_NO_WRANINGS
#define ID_CBX 3210
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyCombo");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;   // 윈도우 핸들
	MSG Message; // 메세지
	g_hInst = hInstance; // 인스턴스 핸들을 다른 프로세스에서도 사용할 수 있도록 전역변수에 대입

	// 윈도우 클래스(윈도우의 속성을 정의하는 구조체)를 초기화
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpszClassName = lpszClass;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	RegisterClass(&wc); // 초기화 시킨 윈도우 클래스를 운영체제에 등록

	// 윈도우 클래스 바탕으로 윈도우창을 생성한다
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // 윈도우창을 출력
	if (hWnd == NULL) return -1;

	// 메세지 루프
	while (GetMessage(&Message,NULL, 0, 0) > 0) { // 메세지 큐에 있는 메세지들을 확인
		TranslateMessage(&Message); // 키보드에 입력된 메세지를 인스턴스가 이해하기 쉬운 형태로 해석
		DispatchMessage(&Message); // WndProc으로 해석시킨 메세지를 전달한다.
	}

	return (int)Message.wParam;
}

const TCHAR* items[]{ TEXT("apple"),TEXT("orange"),TEXT("melon"), TEXT("grape") ,TEXT("sex") };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	int idx;
	static HWND hCbx;
	static TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hCbx = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 10, 10,
			100, 300, hWnd, (HMENU)ID_CBX, g_hInst, NULL);
		for (auto i : items) {
			SendMessage(hCbx, CB_ADDSTRING, 0, (LPARAM)i);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case ID_CBX:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				idx = SendMessage(hCbx, CB_GETCURSEL, 0, 0); // 현재 선택한 인덱스 번호를 반환
				SendMessage(hCbx, CB_GETLBTEXT, idx, (LPARAM)str);
				SetWindowText(hWnd, str);
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCbx, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
