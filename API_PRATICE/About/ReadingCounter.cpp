#include <windows.h>
#include <chrono>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("ReadingCounter");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_READINGCOUNTER), NULL, (DLGPROC)MainDlgProc); // 윈도우 생성 없이 바로 다이얼로그 출력
	return 0;
}

enum STATUS {RUN,PAUSE,WAIT};

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static int sp, ep, timer, status, tmptimer;
	static TCHAR msg[128];
	switch (iMessage) {
	case WM_INITDIALOG: // 다이얼로그 초기화 부분
		SetDlgItemInt(hDlg, IDC_TIMER, 60, FALSE);
		SetDlgItemInt(hDlg, IDC_STPG, 0, FALSE);
		SetDlgItemInt(hDlg, IDC_EDPG, 0, FALSE);
		status = WAIT;
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {  // 컨트롤에 대한 처리
		case IDOK:
			MessageBox(hDlg, TEXT("Hellow"), TEXT("안녕"), MB_OK);
			return TRUE; // 메세지를 제대로 처리했다면 참 아니면 거짓을 반환.
		case IDCANCEL:
			KillTimer(hDlg, 1);
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		case IDC_START:
			// 예외 처리
			sp = GetDlgItemInt(hDlg, IDC_STPG, NULL, TRUE);
			ep = GetDlgItemInt(hDlg, IDC_EDPG, NULL, TRUE);
			timer = GetDlgItemInt(hDlg, IDC_TIMER, NULL, TRUE);
			tmptimer = timer;
			if (sp > ep || !timer) {
				MessageBox(hDlg, TEXT("적절한 값을 입력하시오"), TEXT("오류"), MB_OK);
				return TRUE;
			}
			status = RUN;
			SetTimer(hDlg, 1, 1000, NULL);
			SendMessage(hDlg, WM_TIMER, 1, NULL);
			
			return TRUE;
		case IDC_PAUSE:
			if (status == RUN) {
				status = PAUSE;
				KillTimer(hDlg, 1);
			}
			else if (status == PAUSE) {
				status = RUN;
				SetTimer(hDlg, 1, 1000, NULL);
			}
			return TRUE;
		}
		return TRUE;
	case WM_TIMER:
		timer -=1;
		if (!timer) {
			if (SendDlgItemMessage(hDlg, IDC_CBEEP, BM_GETCHECK, 0, 0) == BST_CHECKED) MessageBeep(1000);
			timer = tmptimer;
			sp += 1;
			if (sp > ep) {
				status = WAIT;
				wsprintf(msg, TEXT("now on %d page %d second left"), 0, 0);
				SetDlgItemText(hDlg, IDC_MSG, msg);
				KillTimer(hDlg, 1);
				return TRUE;
			}
		}
		wsprintf(msg,TEXT("now on %d page %d second left"), sp, timer);
		SetDlgItemText(hDlg, IDC_MSG, msg);
		return TRUE;
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
