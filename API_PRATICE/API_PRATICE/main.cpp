#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

// ****�ü���� �޼��� �߻� �� ȣ���ϴ� �Լ� (callback �Լ�)
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // �������α׷� �ڵ��� �����ϱ� ���� ���������� ����
LPCTSTR lpszClass = TEXT("KeyBoard_Action"); // Ŭ���� ���� �����ϱ� ���� ���ڿ� 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpszCmdParam, int nCmdShow) {

	// ���������� ��ü���� �Ӽ��� ��Ÿ���� ������ Ŭ���� ����ü�� �ʱ�ȭ.
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

}