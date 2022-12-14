#include <windows.h>
#include "resource.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND g_hWnd;
HWND g_hDlg;
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("SimplePaint");


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
	g_hWnd = hWnd;
	// 메세지 루프
	while (GetMessage(&Message, NULL, 0, 0) > 0 || !IsDialogMessage(g_hDlg,&Message)) { // 메세지 큐에 있는 메세지들을 확인
		TranslateMessage(&Message); // 키보드에 입력된 메세지를 인스턴스가 이해하기 쉬운 형태로 해석
		DispatchMessage(&Message); // WndProc으로 해석시킨 메세지를 전달한다.
	}

	return (int)Message.wParam;
}

void DrawLine(HDC hdc, int& x, int& y, WPARAM wParam, LPARAM lParam) {
	MoveToEx(hdc, x, y, NULL);
	x = LOWORD(lParam);
	y = HIWORD(lParam);
	LineTo(hdc, x, y);
}


int r, g, b;
int width;
LRESULT CALLBACK SimplePainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	g_hDlg = hDlg;
	
	int tempPos;
	switch (iMessage) {
	case WM_INITDIALOG:
		SetScrollRange(GetDlgItem(hDlg, IDC_SCROLL_RED), SB_CTL, 0, 255, TRUE);
		SetScrollRange(GetDlgItem(hDlg, IDC_SCROLL_GREEN), SB_CTL, 0, 255, TRUE);
		SetScrollRange(GetDlgItem(hDlg, IDC_SCROLL_BLUE), SB_CTL, 0, 255, TRUE);
		SetDlgItemInt(hDlg, IDC_EDIT_WIDTH, 0, TRUE);
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLL_RED),SB_CTL,0,TRUE);
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLL_GREEN), SB_CTL, 0, TRUE);
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLL_BLUE), SB_CTL, 0, TRUE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			DestroyWindow(hDlg);
			g_hDlg = NULL;
			return TRUE;
		case IDCANCEL:
			DestroyWindow(hDlg);
			g_hDlg = NULL;
			return TRUE;
		case IDC_BTN_RESET:
			InvalidateRect(g_hWnd, NULL, TRUE);
			return TRUE;
		case IDC_EDIT_WIDTH:
			width = GetDlgItemInt(hDlg, IDC_EDIT_WIDTH, FALSE, TRUE);
			return TRUE;
		}
		return TRUE;
	case WM_HSCROLL:
		if ((HWND)lParam == GetDlgItem(hDlg,IDC_SCROLL_RED)) tempPos = r;
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLL_GREEN)) tempPos = g;
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLL_BLUE)) tempPos = b;
		switch (LOWORD(wParam)) {
		case SB_LINERIGHT:
			tempPos = max(0, tempPos + 1);
			break;
		case SB_PAGERIGHT:
			tempPos = max(0, tempPos + 5);
			break;
		case SB_LINELEFT:
			tempPos = min(255, tempPos - 1);
			break;
		case SB_PAGELEFT:
			tempPos = min(255, tempPos - 5);
			break;
		case SB_THUMBTRACK:
			tempPos = HIWORD(wParam);
			break;
		}
		if((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLL_RED)) r = tempPos;
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLL_GREEN)) g = tempPos;
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLL_BLUE)) b = tempPos;
		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static BOOL bNowDraw;
	static int oldX, oldY;
	HPEN op, mp;
	switch (iMessage) {
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		bNowDraw = TRUE;
		oldX = LOWORD(lParam);
		oldY = HIWORD(lParam);
		break;
	case WM_MOUSEMOVE:
		if (bNowDraw) {
			hdc = GetDC(hWnd);
			mp = CreatePen(PS_DOT, width, RGB(r, g, b));
			op = (HPEN)SelectObject(hdc, mp);
			DrawLine(hdc, oldX, oldY, wParam, lParam);
			SelectObject(hdc, op);
			DeleteObject(mp);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		break;
	case WM_RBUTTONDOWN:
		if (!IsWindow(g_hDlg)) {
			g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)SimplePainDlgProc);
			ShowWindow(g_hDlg, SW_SHOW);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DestroyWindow(g_hDlg);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
