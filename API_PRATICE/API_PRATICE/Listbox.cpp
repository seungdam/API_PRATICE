#include <windows.h>
#include <vector>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MyListBox");

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

const TCHAR* items[]= { TEXT("oh sd"),TEXT("lee hj"), TEXT("baek jh")};


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hLstbx;
	static TCHAR str[256];
	switch (iMessage) {
	case WM_CREATE:
		// NOTIFY : ����ڰ� ��� �� �ϳ��� �������� �� ���� �޽���(HIWORD(wParam))�� ����
		hLstbx = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER 
			| LBS_NOTIFY, 10, 10, 100, 200, hWnd, (HMENU)0, g_hInst, NULL);
		for (auto i : items) {
			SendMessage(hLstbx, LB_ADDSTRING, 0, (LPARAM)i);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) { // ���õ� ��Ʈ�ѿ� ���� ó��
		case 0:
			switch (HIWORD(wParam)) { // ����Ʈ �ڽ��� ���� �޽���
			case LBN_SELCHANGE: // ����ڿ� ���� ������ ����� ���.
				int idx = SendMessage(hLstbx, LB_GETCURSEL, 0, 0); // ���õ� �ε��� ���� ��ȯ
				SendMessage(hLstbx, LB_GETTEXT, idx, (LPARAM)str); // �ش� �ε����� �ؽ�Ʈ���� ���ڹ迭�� ����
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
