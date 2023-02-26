#include <Windows.h>
#include "resource.h"
#define MESSAGE_BOX

CONST CHAR gsz_DEFAULT_LOGIN_MESSAGE[] = "¬ведите им€ пользовател€";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstanse, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

	//#ifdef MESSAGE_BOX
	//	MessageBox(NULL, "ѕривет мир!", "Hello", MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL);
	//	/*
	//	NULL-родительское окно, null-отсутсвует
	//	привет мир- сообщение
	//	hello- заголовок окна
	//	MB_OK- флаги, определ€ющие набор кнопок и значок окна
	//	флаги- это биты показывающие что включено, а что нет
	//	*/
	//#endif // MESSAGE_BOX

	DialogBoxParam(hInstanse, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://отрабатывает при запуске окна, и может создавать элементы окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT,0, (LPARAM)gsz_DEFAULT_LOGIN_MESSAGE);
	}
	break;
	/*case EN_SETFOCUS:
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		if (GetFocus() == hEditLogin)
		{
			SendMessage(hEditLogin, WM_SETTEXT, NULL, (LPARAM)"");
		}
		break;
	}
	break;
	case EN_KILLFOCUS:
	{
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		if (GetFocus() != hEditLogin)
		{
			SendMessage(hEditLogin, WM_SETTEXT, NULL, (LPARAM)"¬ведите логин");
		}
		break;
	}
	break;*/
	case WM_COMMAND://отрабатывает сообщени€ при нажатии на кнопки и т.д
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if(strcmp(sz_buffer, gsz_DEFAULT_LOGIN_MESSAGE)==0)
					SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, "") == 0)
					SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)gsz_DEFAULT_LOGIN_MESSAGE);
			}
		}
		break;
		case IDC_BUTTON_COPY:	
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPass = GetDlgItem(hwnd, IDC_EDIT_PASS);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPass, WM_SETTEXT, 0, (LPARAM)"");
		}
		break;
		case IDOK: MessageBox(hwnd, "Ѕыла нажата кнопка ок", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}