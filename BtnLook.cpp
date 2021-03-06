// BtnLook.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "BtnLook.h"


struct
{
	int iStyle;
	const TCHAR * szText;
}
button[] =
{
 BS_PUSHBUTTON, TEXT("PUSHBUTTON"),
 BS_DEFPUSHBUTTON, TEXT("DEFPUSHBUTTON"),
 BS_CHECKBOX, TEXT("CHECKBOX"),
 BS_AUTOCHECKBOX, TEXT("AUTOCHECKBOX"),
 BS_RADIOBUTTON, TEXT("RADIOBUTTON"),
 BS_3STATE, TEXT("3STATE"),
 BS_AUTO3STATE, TEXT("AUTO3STATE"),
 BS_GROUPBOX, TEXT("GROUPBOX"),
 BS_AUTORADIOBUTTON, TEXT("AUTORADIO"),
 BS_OWNERDRAW, TEXT("OWNERDRAW")
};
#define NUM (sizeof button / sizeof button[0])

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BTNLOOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BTNLOOK));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BTNLOOK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BTNLOOK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndButton[NUM];
	static RECT rect;
	static TCHAR szTop[] = TEXT("message wParam lParam"),
		szUnd[] = TEXT("_______ ______ ______"),
		szFormat[] = TEXT("%-16s%04X-%04X %04X-%04X"),
		szBuffer[50];
	static int cxChar, cyChar;
	HDC hdc;
	PAINTSTRUCT ps;
	int i;

    switch (message)
    {
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		for (i = 0; i < NUM; ++i)
		{
			hwndButton[i] = CreateWindow(TEXT("button"), button[i].szText, 
				WS_CHILD | WS_VISIBLE | button[i].iStyle, 
				cxChar, cyChar * (1 + 2 * i), 20 * cxChar, 7 * cyChar / 4, 
				hWnd, (HMENU)i, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		break;
	case WM_SIZE:
		rect.left = 24 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		break;
    case WM_PAINT:
        {
			InvalidateRect(hWnd, &rect, TRUE);
            hdc = BeginPaint(hWnd, &ps);

			SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
			SetBkMode(hdc, TRANSPARENT);

			TextOut(hdc, 24 * cxChar, cyChar, szTop, lstrlen(szTop));
			TextOut(hdc, 24 * cxChar, cyChar, szUnd, lstrlen(szUnd));

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_DRAWITEM:
	case WM_COMMAND:
		ScrollWindow(hWnd, 0, -cyChar, &rect, &rect);
		hdc = GetDC(hWnd);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

		TextOut(hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1), szBuffer,
			wsprintf(szBuffer, szFormat, message == WM_DRAWITEM ? TEXT("WM_DRAWITEM") : TEXT("WM_COMMAND"),
				HIWORD(wParam), LOWORD(wParam), HIWORD(lParam), LOWORD(lParam)));

		ReleaseDC(hWnd, hdc);
		ValidateRect(hWnd, &rect);

		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
