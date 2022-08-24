#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("studentInfo");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)MainDlgProc); // 윈도우 생성 없이 바로 다이얼로그 출력
	return 0;
}

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG: // 다이얼로그 초기화 부분
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {  // 컨트롤에 대한 처리
		case IDOK:
			MessageBox(hDlg, TEXT("Hellow"), TEXT("안녕"), MB_OK);
			return TRUE; // 메세지를 제대로 처리했다면 참 아니면 거짓을 반환.
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
