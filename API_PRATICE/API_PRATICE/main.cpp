#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

// ****�ü���� �޼��� �߻� �� ȣ���ϴ� �Լ� (callback �Լ�)
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // �������α׷� �ڵ��� �����ϱ� ���� ���������� ����
LPCTSTR lpszClass = TEXT("KeyBoard_Action"); // Ŭ���� ���� �����ϱ� ���� ���ڿ� 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpszCmdParam, int nCmdShow) {

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

}