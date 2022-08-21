#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"

// ****�ü���� �޼��� �߻� �� ȣ���ϴ� �Լ� (callback �Լ�)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // �������α׷� �ڵ��� �����ϱ� ���� ���������� ����
LPCTSTR lpszClass = TEXT("Menu"); // Ŭ���� ���� �����ϱ� ���� ���ڿ� 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

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
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ������ �ü���� ��� : ������ �̷� ��Ÿ���� ������â�� ������ ���̴�.
	RegisterClass(&wndClass);

	HWND hWnd;
	MSG Message;
	g_hInst = hInstance; // �۷ι� ���������� �־��ش�.

	// �������� ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	// �������� ���
	ShowWindow(hWnd, nCmdShow);

	// �޼��� ����
	while (GetMessage(&Message, NULL, 0, 0) > 0) {
		TranslateMessage(&Message); // Ű���� �Է��� �������α׷��� ���� �����ϰ� ����
		DispatchMessage(&Message); // �߻��� �޼����� ���μ����� ����
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}