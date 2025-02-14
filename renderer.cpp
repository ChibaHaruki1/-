//=======================================
//
//レンダラーの処理[renderer.cpp] 
//Auther:Chiba Haruki
//
//=======================================


//=======================================
//インクルード
#include "main.h"
#include "rendererh.h"
#include "bg.h"
#include "input.h"
#include "sound.h"
#include "manager.h"
#include "scene.h"


//==================
//コンストラクタ
//==================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;        //DirectX9の情報の初期化
	m_pD3DDevice = nullptr;  //DirectX9のデバイスの初期化

	m_pFont = nullptr;       //フォントの初期化
	m_bPause = false;        //ポーズしていないに設定
	m_bDrawShader = false;   //シェーダーを描画しないに設定
}

//==================
//デストラクタ
//==================
CRenderer::~CRenderer()
{

}

//==================
//初期化処理
//==================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//DirectXオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//情報がない時
	if (m_pD3D == nullptr)
	{
		return E_FAIL; //失敗を返す
	}

	//現在のディスプレイモードを収得できない時
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL; //失敗を返す
	}

	//デバイスのプレゼンテーションパラメータ設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));                          //パラメータゼロクリア
	d3dpp.BackBufferWidth = CMain::SCREEN_WIDTH;                //ゲーム画面の幅
	d3dpp.BackBufferHeight = CMain::SCREEN_HEIGHT;              //ゲーム画面の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;                      //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                  //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                   //ダブルバッファの切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;                        //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                  //デプスバッファとして１６ビット使用
	d3dpp.Windowed = bWindow;                                   //ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //インターバル

	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		//Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			//Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				return E_FAIL; //失敗を返す
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーstateの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用のフォントの生成
	D3DXCreateFont(m_pD3DDevice, FONT_HEIGHT, FONT_WIDTH, FONT_WEIGHT, FONT_MIPLEVELS, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	CManager::SetMode(CScene::MODE::MODE_GAME01); //初めのシーンを設定

	return S_OK; //成功を返す
}

//==================
//終了処理
//==================
void CRenderer::Uninit()
{
	//Direct3Dデバイスの情報がある時
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release(); //情報を消す
		m_pD3DDevice = nullptr;  //情報を無くす
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();       //情報を消す
		m_pD3D = nullptr;        //情報を無くす
	}

	//デバック表示用フォントの破壊
	if (m_pFont != nullptr)
	{
		m_pFont->Release();      //情報を消す
		m_pFont = nullptr;       //情報を無くす
	}
}

//==================
//更新処理
//==================
void CRenderer::Update()
{
	//Pキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_P) == true)
	{
		m_bPause = m_bPause ? false : true;
	}

	//pauseしてない
	if (m_bPause == false)
	{
		CObjectManagerX::UpdateAll();  //オブジェクトの更新処理
		CObject::UpdateAll();          //オブジェクトの更新処理
	}

	//pause中
	else if (m_bPause == true)
	{
		//CManager::GetSCene()->GetOverhead_Processing()->GetTutorialUI()->Update(0.0f, 0.0f, 0.0f);
		//CManager::GetSCene()->GetOverhead_Processing()->Tutorial();
	}
}


//==================
//描画処理
//==================
void CRenderer::Draw()
{
	//画面クリア（バックバッファ＆Zバッファのクリア
	m_pD3DDevice->Clear(CObject::N_INIT_NUMBER, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(CObject::RED, CObject::GREEN, CObject::BLUE, CObject::N_INIT_ALPHA_NUMBER), CLEAR_Z, CLEAR_STENCIL);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//描画開始が成功した場合

		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);                //通常描画

		//まだシェーダーを描画してない時
		if (m_bDrawShader == false)
		{
			m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);       //通常シェーダーに設定

			//イベントの情報がある時
			if (CManager::GetEvent() != nullptr)
			{
				//ボスの演出が開始
				if (CManager::GetEvent()->GetBossDirection() == true)
				{
					m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);  //シェーダーを変更（３Dモデルを面表示）
					m_bDrawShader = true;                                          //シェーダーを描画した
				}
			}
		}

		//現在のシーン
		switch (CManager::GetScene()->GetMode())
		{
			//タイトル時
		case CScene::MODE::MODE_TITLE:
			break;

			//リザルト時
		case CScene::MODE::MODE_RESULT:
			break;

			//ゲームオーバー時
		case CScene::MODE::MODE_GAMEOVER:
			break;

			//その他
		default:
			CManager::GetScene()->GetCamera()->SetCamera(); //カメラの設定
			break;
		}

		//全ての描画
		CObjectManagerX::DrawAll();
		CObject::DrawAll();

		//DrawFPS(); //debug描画

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//================
//FPSの表示
//================
void CRenderer::DrawFPS()
{
	//表示用変数
	RECT rect = { CObject::N_INIT_NUMBER, CObject::N_INIT_NUMBER,CMain::SCREEN_WIDTH,CMain::SCREEN_HEIGHT }; //X,Y,大きさ（横、縦）で位置設定

	//文字列を保管する用の変数
	char aStr[MAX_STR];

	//文字列に代入
	wsprintf(&aStr[CObject::N_INIT_NUMBER], "FPS;%d\n", CManager::GetMain()->GetFPS());

	//テキストの描画
	m_pFont->DrawText(NULL, &aStr[CObject::N_INIT_NUMBER], DRAW_LONG_TEXT, &rect, DT_LEFT, D3DCOLOR_RGBA(CObject::RED, CObject::GREEN, CObject::BLUE, CObject::N_INIT_ALPHA_NUMBER));
}