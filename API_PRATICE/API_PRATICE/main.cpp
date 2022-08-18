#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

// ****운영체제가 메세지 발생 시 호출하는 함수 (callback 함수)
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst; // 응용프로그램 핸들을 저장하기 위해 전역변수로 선언
LPCTSTR lpszClass = TEXT("KeyBoard_Action"); // 클래스 명을 저장하기 위한 문자열 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpszCmdParam, int nCmdShow) {

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

}