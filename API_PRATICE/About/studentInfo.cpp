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

	// �޼��� ����
	while (GetMessage(&Message, NULL, 0, 0) > 0) { // �޼��� ť�� �ִ� �޼������� Ȯ��
		TranslateMessage(&Message); // Ű���忡 �Էµ� �޼����� �ν��Ͻ��� �����ϱ� ���� ���·� �ؼ�
		DispatchMessage(&Message); // WndProc���� �ؼ���Ų �޼����� �����Ѵ�.
	}

	return (int)Message.wParam;
}


STDINFO student;
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG: // ���̾�α� �ʱ�ȭ �κ�
		CheckDlgButton(hDlg, IDC_M, TRUE);
		CheckRadioButton(hDlg, IDC_GE,IDC_ET,IDC_GE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {  // ��Ʈ�ѿ� ���� ó��
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
			if (IsDlgButtonChecked(hDlg, IDC_GE)) lstrcpy(student.major,TEXT("���Ӱ���"));
			if (IsDlgButtonChecked(hDlg, IDC_CE)) lstrcpy(student.major, TEXT("��ǻ�Ͱ���"));
			if (IsDlgButtonChecked(hDlg, IDC_DS)) lstrcpy(student.major, TEXT("������"));
			if (IsDlgButtonChecked(hDlg, IDC_ET)) lstrcpy(student.major, TEXT("�������"));
			MessageBox(hDlg, TEXT("Register"), TEXT("ȸ�� ���� �Ϸ�"), MB_OK);
			EndDialog(hDlg, IDOK);
			return TRUE; // �޼����� ����� ó���ߴٸ� �� �ƴϸ� ������ ��ȯ.
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
