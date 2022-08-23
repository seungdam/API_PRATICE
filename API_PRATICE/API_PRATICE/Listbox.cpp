#include <windows.h>
#include <vector>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyListBox");

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
	while (GetMessage(&Message, NULL, 0, 0) > 0) { // 메세지 큐에 있는 메세지들을 확인
		TranslateMessage(&Message); // 키보드에 입력된 메세지를 인스턴스가 이해하기 쉬운 형태로 해석
		DispatchMessage(&Message); // WndProc으로 해석시킨 메세지를 전달한다.
	}

	return (int)Message.wParam;
}

const TCHAR* items[]= { TEXT("oh sd"),TEXT("lee hj"), TEXT("baek jh")};


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hLstbx;
	static TCHAR str[256];
	switch (iMessage) {
	case WM_CREATE:
		// NOTIFY : 사용자가 목록 중 하나를 선택했을 때 통지 메시지(HIWORD(wParam))를 전송
		hLstbx = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER 
			| LBS_NOTIFY, 10, 10, 100, 200, hWnd, (HMENU)0, g_hInst, NULL);
		for (auto i : items) {
			SendMessage(hLstbx, LB_ADDSTRING, 0, (LPARAM)i);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // 선택된 컨트롤에 대한 처리
		case 0:
			switch (HIWORD(wParam)) { // 리스트 박스의 통지 메시지
			case LBN_SELCHANGE: // 사용자에 의해 선택이 변경된 경우.
				int idx = SendMessage(hLstbx, LB_GETCURSEL, 0, 0); // 선택된 인덱스 값을 반환
				SendMessage(hLstbx, LB_GETTEXT, idx, (LPARAM)str); // 해당 인덱스의 텍스트값을 문자배열에 저장
				SetWindowText(hWnd, str);
				break;
			}
			break;
		}
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
