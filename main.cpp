#include <windows.h>
static	LRESULT CALLBACK WinProc( HWND hWnd, UINT uMsg, WPARAM	wParam, LPARAM	lParam )
{
	static	HDC		hdcBackbuffer;
	static	RECT	rc;

	switch( uMsg ) 
	{
		case WM_CREATE:	
			{
			    HDC hDc = GetDC(hWnd); 
				GetClientRect( hWnd, &rc );

				//バックバッファの作成
				HBITMAP hBitmap = CreateCompatibleBitmap( hDc, rc.right, rc.bottom );
			    hdcBackbuffer = CreateCompatibleDC( NULL );
			    SelectObject( hdcBackbuffer, hBitmap );
				ReleaseDC( hWnd, hDc );
			}	
			return 0;
			

		case WM_PAINT:
			{
				//バックバッファをクリア
				HBRUSH hBrush  = CreateSolidBrush(0);
				SelectObject( hdcBackbuffer , hBrush);
				PatBlt( hdcBackbuffer , 0 , 0 ,rc.right, rc.bottom , PATCOPY);
				DeleteObject( hBrush );
			}
			{
				//バックバッファを転送
				PAINTSTRUCT ps;
				HDC hDc = BeginPaint( hWnd, &ps );
				BitBlt(hDc, 0, 0, rc.right, rc.bottom, hdcBackbuffer, 0, 0, SRCCOPY);
				EndPaint(hWnd, &ps);
			}
			return 0;

		case WM_KEYDOWN:
			if ( wParam == 27 ) SendMessage(hWnd , WM_DESTROY , 0 , 0);	
			return 0;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

int WINAPI WinMain( HINSTANCE hInstance,  HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nCmdShow )
{
	WNDCLASSEX		wdc;
	wdc.cbSize			= sizeof( WNDCLASSEX );
	wdc.style			= CS_HREDRAW | CS_VREDRAW;
	wdc.lpfnWndProc		= WinProc;
	wdc.cbClsExtra		= 0;
	wdc.cbWndExtra		= 0;
	wdc.hInstance		= hInstance;
	wdc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wdc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wdc.hbrBackground 	= (HBRUSH)( COLOR_WINDOW + 1 );
	wdc.lpszMenuName	= MAKEINTRESOURCE( NULL );
	wdc.lpszClassName 	= "MainWindowClass";
	wdc.hIconSm			= NULL;
	RegisterClassEx( &wdc ) ;
	HWND hWnd = CreateWindowEx( 0 , wdc.lpszClassName , "test"  , WS_OVERLAPPEDWINDOW , 100 , 100 , 500 , 500 , NULL, NULL, hInstance, 0);
	ShowWindow( hWnd, SW_SHOW );

	MSG				tMsg;
	while(1)
	{
		// WM_PAINTをリクエスト
		InvalidateRect(hWnd , NULL , TRUE);

		while ( PeekMessage( &tMsg, NULL, 0, 0, PM_REMOVE) )
		{
			DispatchMessage( &tMsg );
			TranslateMessage( &tMsg );
			if ( tMsg.message == WM_QUIT ) exit(0); 
		}
	}

}
