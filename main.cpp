#include<Windows.h>
//ウインドウプロシージャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
	//ウインドウが破棄された
	case WM_DESTROY:
		//ＯＳに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}
	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
//
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//
	OutputDebugStringA("Hello,DirectX!!\n");
	//ウィンドウサイズ
	const int window_width = 1280;//横幅
	const int window_height = 720;//縦幅
	//ウィンドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;
	w.lpszClassName = L"DiirectXGame";
	w.hInstance = GetModuleHandle(nullptr);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	//ウィンドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウィンドウサイズ{ｘ座標　Ｙ座標　横幅　縦幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	//ウィンドウオブジェクトの生成
	HWND hwnd = CreateWindow(w.lpszClassName,
		L"DiirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr
	);
	//ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
	MSG msg{};//メッセージ

	//Directx初期化処理　ここから
	//Directx初期化処理　ここまで

	//ゲームループ
	while (true)
	{
		//メッセージがある？
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);//キー入力メッセージの処理
			DispatchMessage(&msg);//プロシージャにメッセージを送る
		}
		//Ｘボタンで終了メッセージが来たらゲームループを抜ける
		if (msg.message==WM_QUIT)
		{
			break;
		}
		//Directx毎フレーム処理　ここから
		//Directx毎フレーム処理　ここまで
	}
	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}