#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyScroll");

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
	while (GetMessage(&Message, hWnd, 0, 0) > 0) { // 메세지 큐에 있는 메세지들을 확인
		TranslateMessage(&Message); // 키보드에 입력된 메세지를 인스턴스가 이해하기 쉬운 형태로 해석
		DispatchMessage(&Message); // WndProc으로 해석시킨 메세지를 전달한다.
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hr, hg, hb;
	switch (iMessage) {
	case WM_CREATE:
		hr = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE
			| SBS_HORZ, 10, 10, 400, 20, hWnd, (HMENU)0, g_hInst, NULL);
		hg = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE
			| SBS_HORZ, 10, 40, 400, 20, hWnd, (HMENU)0, g_hInst, NULL);
		hb = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE
			| SBS_HORZ, 10, 70, 400, 20, hWnd, (HMENU)0, g_hInst, NULL);
		SetScrollRange(hr, SB_CTL, 0, 255, TRUE); // 스크롤의 범위를 설정
		SetScrollPos(hr, SB_CTL, 0, TRUE); // 스크롤 바의 위치를 결정
		SetScrollRange(hg, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hg, SB_CTL, 0, TRUE);
		SetScrollRange(hb, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hb, SB_CTL, 0, TRUE);
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
