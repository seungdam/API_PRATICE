#include <windows.h>
#include <vector>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("studentInfo");

struct STDINFO {
	bool sex;
	TCHAR major[128];
	TCHAR id[50];
	TCHAR pw[50];
};

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


STDINFO student;
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG: // 다이얼로그 초기화 부분
		CheckDlgButton(hDlg, IDC_M, TRUE);
		CheckRadioButton(hDlg, IDC_GE,IDC_ET,IDC_GE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {  // 컨트롤에 대한 처리
		case IDC_M:
			SendDlgItemMessage(hDlg, IDC_FM, BM_SETCHECK, BST_UNCHECKED, 0);
			return TRUE;
		case IDC_FM:
			SendDlgItemMessage(hDlg, IDC_M, BM_SETCHECK, BST_UNCHECKED, 0);
			return TRUE;
		case IDOK:
			GetDlgItemText(hDlg, IDC_ID, student.id, 50);
			GetDlgItemText(hDlg, IDC_PW, student.pw, 50);
			if (IsDlgButtonChecked(hDlg, IDC_M)) student.sex = true;
			else student.sex = false;
			if (IsDlgButtonChecked(hDlg, IDC_GE)) lstrcpy(student.major,TEXT("게임공학"));
			if (IsDlgButtonChecked(hDlg, IDC_CE)) lstrcpy(student.major, TEXT("컴퓨터공학"));
			if (IsDlgButtonChecked(hDlg, IDC_DS)) lstrcpy(student.major, TEXT("디자인"));
			if (IsDlgButtonChecked(hDlg, IDC_ET)) lstrcpy(student.major, TEXT("전기공학"));
			MessageBox(hDlg, TEXT("Register"), TEXT("회원 가입 완료"), MB_OK);
			EndDialog(hDlg, IDOK);
			return TRUE; // 메세지를 제대로 처리했다면 참 아니면 거짓을 반환.
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
		break;
	case WM_RBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, (DLGPROC)MainDlgProc);
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
