#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyComboBox");

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

const TCHAR* items[] = { TEXT("oh sd"), TEXT("lee hj"), TEXT("beak jh") };
HWND hCmb;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	int idx = 0;
	static TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		//CBS_SIMPLE: ����Ʈ�� ����Ʈ�ڽ��� ������ ����Ʈ �ڽ��� �׻� ��ó����.
		//CBS_DROPDOWN: ����Ʈ�� ����Ʈ�ڽ��� ����
		//CBS_DROPDOWNLIST: ����Ʈ�ڽ��� ������ ����Ʈ�� �׸��� �Է��� ���� ����.
		hCmb = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE |
			CBS_DROPDOWN, 10, 10, 100, 200, hWnd, (HMENU)2310, g_hInst, NULL);
		for (auto i : items) {
			SendMessage(hCmb, CB_ADDSTRING, 0, (LPARAM)i);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 2310:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				idx = SendMessage(hCmb, CB_GETCURSEL, 0, 0);
				SendMessage(hCmb, CB_GETLBTEXT, idx, (LPARAM)str);
				SetWindowText(hWnd, str);
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCmb, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
			break;
		}
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