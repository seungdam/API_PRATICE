#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyButton");

enum BTN {B1 = 1000,C1,C2,C3,R1,R2,R3};

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
	while (GetMessage(&Message, hWnd, 0, 0) > 0) { // �޼��� ť�� �ִ� �޼������� Ȯ��
		TranslateMessage(&Message); // Ű���忡 �Էµ� �޼����� �ν��Ͻ��� �����ϱ� ���� ���·� �ؼ�
		DispatchMessage(&Message); // WndProc���� �ؼ���Ų �޼����� �����Ѵ�.
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_CREATE:
		CreateWindow(L"button", L"Reset", WS_CHILD | WS_VISIBLE
			| BS_PUSHBUTTON, 160, 50, 50, 50, hWnd, (HMENU)B1, g_hInst, NULL);
		// ���� ����

		// ���콺 ���� ����
		CreateWindow(L"button", L"Width", WS_CHILD | WS_VISIBLE
			| BS_GROUPBOX, 10, 20, 60, 120, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"button", L"5", WS_CHILD | WS_VISIBLE
			| BS_AUTOCHECKBOX, 20, 40, 30, 30, hWnd, (HMENU)C1, g_hInst, NULL);
		CreateWindow(L"button", L"7", WS_CHILD | WS_VISIBLE
			| BS_AUTOCHECKBOX, 20, 70, 30, 30, hWnd, (HMENU)C2, g_hInst, NULL);
		CreateWindow(L"button", L"9", WS_CHILD | WS_VISIBLE
			| BS_AUTOCHECKBOX, 20, 100, 30, 30, hWnd, (HMENU)C3, g_hInst, NULL);

		CreateWindow(L"button", L"Color", WS_CHILD | WS_VISIBLE
			| BS_GROUPBOX, 100, 20, 50, 120, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(L"button", L"5", WS_CHILD | WS_VISIBLE
			| BS_AUTORADIOBUTTON, 110, 40, 30, 30, hWnd, (HMENU)R1, g_hInst, NULL);
		CreateWindow(L"button", L"7", WS_CHILD | WS_VISIBLE
			| BS_AUTORADIOBUTTON, 110, 70, 30, 30, hWnd, (HMENU)R2, g_hInst, NULL);
		CreateWindow(L"button", L"9", WS_CHILD | WS_VISIBLE
			| BS_AUTORADIOBUTTON, 110, 100, 30, 30, hWnd, (HMENU)R3, g_hInst, NULL);
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
