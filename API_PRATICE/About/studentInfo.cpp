#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("studentInfo");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)MainDlgProc); // ������ ���� ���� �ٷ� ���̾�α� ���
	return 0;
}

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG: // ���̾�α� �ʱ�ȭ �κ�
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {  // ��Ʈ�ѿ� ���� ó��
		case IDOK:
			MessageBox(hDlg, TEXT("Hellow"), TEXT("�ȳ�"), MB_OK);
			return TRUE; // �޼����� ����� ó���ߴٸ� �� �ƴϸ� ������ ��ȯ.
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
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
