#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
HWND hMainWnd;
LPCTSTR lpszClass = TEXT("DlgInfo");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;   // ������ �ڵ�
	MSG Message; // �޼���
	g_hInst = hInstance; // �ν��Ͻ� �ڵ��� �ٸ� ���μ��������� ����� �� �ֵ��� ���������� ����

	// ������ Ŭ����(�������� �Ӽ��� �����ϴ� ����ü)�� �ʱ�ȭ
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
	RegisterClass(&wc); // �ʱ�ȭ ��Ų ������ Ŭ������ �ü���� ���

	// ������ Ŭ���� �������� ������â�� �����Ѵ�
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // ������â�� ���
	if (hWnd == NULL) return -1;
	hMainWnd = hWnd;

	// �޼��� ����
	while (GetMessage(&Message, NULL, 0, 0) > 0) { // �޼��� ť�� �ִ� �޼������� Ȯ��
		TranslateMessage(&Message); // Ű���忡 �Էµ� �޼����� �ν��Ͻ��� �����ϱ� ���� ���·� �ؼ�
		DispatchMessage(&Message); // WndProc���� �ؼ���Ų �޼����� �����Ѵ�.
	}

	return (int)Message.wParam;
}

int posX, posY;
TCHAR str[256];

// ���̾�α׿� ���� �ݹ� �Լ��� �ۼ�.
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, IDC_X, 0, FALSE);
		SetDlgItemInt(hDlg, IDC_Y, 0, FALSE);
		SetDlgItemText(hDlg, IDC_STR, TEXT("Put String Here"));
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			posX = GetDlgItemInt(hDlg, IDC_X,NULL , FALSE);
			posY = GetDlgItemInt(hDlg, IDC_Y, NULL, FALSE);
			GetDlgItemText(hDlg,IDC_STR,str,256);
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_CREATE:
		lstrcpy(str, TEXT("String"));
		posX = 100;
		posY = 100;
		break;
	case WM_RBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)MainDlgProc)) InvalidateRect(hWnd, NULL, TRUE); // WndProc���� ��ȭ���ڸ� ȣ��
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc,TRANSPARENT);
		TextOut(hdc, posX, posY, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
