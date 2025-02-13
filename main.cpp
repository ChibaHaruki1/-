//============================
//
//メイン処理[main.cpp]
//Auther:Chiba Haruki
//
//============================


//============================
//インクルード
#include"main.h"      
#include "manager.h"  
#include "objectX.h"
#include "DxLib.h"   //外部ファイルの読み込み


//============================
//マクロ定義
#define CLASS_NAME	 "WindowClass"      //ウィンドウクラスの名前
#define WINDOWS_NAME "狂戦士ケルベロス" //ウィンドウの名前


//============================
//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//============================
//グローバル宣言
CManager* g_pMnager = nullptr;


//=========================
//コンストラクタ
//=========================
CMain::CMain()
{
	m_nFPS = CObjectX::N_INIT_NUMBER; //FPSの値を初期化
}


//=========================
//デストラクタ
//=========================
CMain::~CMain()
{
	
}


//=========================
//メイン関数
//=========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstanceprev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//// ウインドウモードに変更
	//ChangeWindowMode(TRUE);

	//SetGraphMode(m_nScren_Width, m_nScren_Heght, m_nBit);			// 画面サイズ設定
	//GetDefaultState(&m_nScren_Width, &m_nScren_Heght, &m_nBit);		// デフォルトウィンドウ値を得る
	//SetWindowSize(m_nScren_Width ,m_nScren_Heght);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更

	//if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	//{
	//	return -1;    // エラーが起きたら直ちに終了
	//}

	//printfDx("Hello world\n"); // 表示される

	//WaitKey();

	//DxLib_End();

	int nInitNumber = CObjectX::N_INIT_NUMBER; //初期値


	//ウィンドウクラスの設定
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),                              //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                                      //ウィンドウのスタイル
		WindowProc,                                      //ウィンドウプロージャ
		nInitNumber,                                     //０にする（通常は使用しない）
		nInitNumber,                                     //０にする（通常は使用しない）
		hInstance,                                       //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),                  //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),                      //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + CMain::CLIENT_COL_PLUS), //クライアント領域の背景色
		NULL,                                            //メニューバー
		CLASS_NAME,                                      //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)                   //ファイルのアイコン
	};									                 
										                 
	HWND hWnd;                                           //ウィンドウハンドル
	MSG msg;                                             //メッセージ受信ハンドル

	RECT rect = { nInitNumber,nInitNumber,CMain::SCREEN_WIDTH,CMain::SCREEN_HEIGHT }; //ウィンドウの大きさ設定

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(nInitNumber, //拡張ウィンドウスタイル
		CLASS_NAME,                    //ウィンドウクラスの名前
		WINDOWS_NAME,                  //ウィンドウの名前
		WS_OVERLAPPEDWINDOW,           //ウィンドウのスタイル
		CW_USEDEFAULT,                 //ウィンドウの左上X座標
		CW_USEDEFAULT,                 //ウィンドウの左上Y座標
		(rect.right - rect.left),      //ウィンドウの幅
		(rect.bottom - rect.top),      //ウィンドウの高さ
		NULL,                          //親ウィンドウのハンドル
		NULL,                          //メニューハンドルまたは子ウィンドウID
		hInstance,                     //インスタンスハンドル
		NULL);                         //ウィンドウ作成データ

	//生成＆初期化
	g_pMnager = new CManager(); //マネージャーの生成

	//初期化処理
	if (FAILED(g_pMnager->Init(hInstance, hWnd, TRUE)))
	{//初期化処理を失敗した場合
		return CMain::RETURN_NUMBER;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow); //ウィンドウの表示状態を設定
	UpdateWindow(hWnd);         //クライアント領域を更新

	//時間の取得
	DWORD dwCurrentTime;  //現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻
	DWORD dwFrameCount;   //フレームカウント
	DWORD dwFPSLastTime;  //最後にFPSを計測した時刻

	//分解能を設定
	timeBeginPeriod(CMain::PERIOD);  //定期的なタイマーの最小解像度を要求する関数 (禁断APIから安心APIへ変更済み)
	dwCurrentTime = nInitNumber;     //現在時刻の初期化
	dwFrameCount = nInitNumber;      //フレームの初期化
	dwExecLastTime = timeGetTime();  //最後に処理した時刻の設定(ミリ秒)
	dwFPSLastTime = timeGetTime();   //最後にFPSを観測した時刻の設定(ミリ秒)

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//メッセージループ
	while (CObjectX::WHILE_NUMBER)
	{
		//msgにあるhwndの情報がある時
		if (PeekMessage(&msg, NULL, nInitNumber, nInitNumber, PM_REMOVE) != nInitNumber)
		{//Windowの処理

			//終了メッセージを受け取った時
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg); //MSG構造体のポインター関数
				DispatchMessage(&msg);  //メッセージを含む構造体へのポインター関数
			}
		}
		else
		{//DirectXの処理

			dwCurrentTime = timeGetTime(); //現在時刻

			//現在時刻ー最後に観測したFPSが0.5秒より高き時
			if ((dwCurrentTime - dwFPSLastTime) >= CMain::FPS_HALF_TIME)
			{//0.5秒経過

				//FPSを観測
				CManager::GetMain()->GetFPS() = (dwFrameCount * CMain::DIVISION) / (dwCurrentTime - dwFPSLastTime); //FPSの値を設定
				dwFPSLastTime = dwCurrentTime;                                                                      //FPSを測定した時刻を保存
				dwFrameCount = nInitNumber;                                                                         //フレイムカウントをクリア
			}

			//１フレーム経過
			if ((dwCurrentTime - dwExecLastTime) >= CMain::ONE_FRAME)
			{//６０分の１秒経過

				dwExecLastTime = dwCurrentTime; //処理開始の時刻（現在時刻）を保存

				//更新処理
				g_pMnager->Update();

				//描画処理
				g_pMnager->Draw();

				dwFrameCount++; //フレイムカウントを加速
			}
		}
	}

	//終了処理を呼ぶ
	CManager::GetMain()->Uninit();

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam; //メッセージをint型で返す
}

//=============================
//ウィンドウプロシージャ
//=============================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nInitNumber = CObjectX::N_INIT_NUMBER; //初期値

	//PAINTSTRUCT ps;
	//HPEN hPen, hPenold;
	int nID;                                                                                 //ID
	static POINT pos = { CMain::POINT_POS };                                                 //ポイント（点）のXY軸の設定
	const RECT rect = { CMain::RECT,CMain::RECT,CMain::SCREEN_WIDTH,CMain::SCREEN_HEIGHT };  //ウィンドウの大きさ

	//int型で判定
	switch (uMsg)
	{
	case WM_DESTROY: //ウィンドウ破棄のメッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(nInitNumber);
		break; //処理を抜ける

		//ECS選択時の処理
	case WM_KEYDOWN: //キー押下のメッセージ

		//メッセージコードで判定
		switch (wParam)
		{
		case VK_ESCAPE: //[ECS]キーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION); //メッセージボックスの生成

			//YESが押された時
			if (nID == IDYES)
			{
				//ウィンドウを破棄する（WM_DESTOROYメッセージを送る）
				DestroyWindow(hWnd);
			}
			break; //処理を抜ける
		}

	case VK_RIGHT: //ESCWindoe時のYesNoのどちらかが押された時に反応

		pos.x++; //X軸を増やす

		//無効領域の強制発生
		InvalidateRect(hWnd, &rect, FALSE);

		break; //処理を抜ける

		//×ボタン選択時の処理
	case WM_CLOSE:
		nID = MessageBox(hWnd, "ウィンドウを閉じますか？", "終了メッセージ", MB_YESNO | MB_ICONWARNING); //メッセージボックスの生成

		//YESが押された時
		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return nInitNumber; //ゼロを返さないと終了してしまう
		}

		break; //処理を抜ける


		//マウス左クリックの処理
	case WM_LBUTTONDOWN: //マウス左クリックのメッセージ

		//ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break; //処理を抜ける
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //既定の処理を返す
}

//======================
//終了処理
//======================
void CMain::Uninit()
{
	//マネージャの情報がある時
	if (g_pMnager != nullptr)
	{
		g_pMnager->Uninit();  //破棄処理を呼ぶ
		delete g_pMnager;     //情報を消す
		g_pMnager = nullptr;  //情報を無くす
	}
}

