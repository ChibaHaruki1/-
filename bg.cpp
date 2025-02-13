//===================================
//
//背景の処理設定[bg.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "bg.h"
#include "rendererh.h"
#include "manager.h"
#include <time.h>


//==========================
//引数付きコンストラクタ
//==========================
CManagerBg::CManagerBg(int nPriority) : CObject2D(nPriority)
{
	SetAlph(CObject2D::N_INIT_ALPHA_NUMBER); //アルファ値を設定
}


//======================
//コンストラクタ
//======================
CManagerBg::~CManagerBg()
{

}


//======================
//背景の初期化処理
//======================
HRESULT CManagerBg::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK; //成功を返す
}


//======================
//背景の終了処理
//======================
void CManagerBg::Uninit(void)
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}


//=======================
//背景の更新処理
//=======================
void CManagerBg::Update()
{
	CMain::VERTEX_2D* pVtx; //バーテクスのポインター

	//頂点バッファをロックし、頂点データへのポインタを取得
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[1].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[2].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());
	pVtx[3].col = D3DCOLOR_RGBA(CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, CObject2D::N_INIT_COL_NUMBER, GetAlph());

	//頂点バッファをアンロック
	GetBuffer()->Unlock();
}


//=====================
//背景の描画処理
//=====================
void CManagerBg::Draw()
{
	CObject2D::Draw(); //描画処理を呼ぶ
}


//===================================
//オブジェクト生成
//===================================
CManagerBg* CManagerBg::Create(CScene::MODE mode)
{
	CManagerBg* pBg = nullptr; //基底クラスのポインター

	//タイトル時
	if (mode == CScene::MODE::MODE_TITLE)
	{
		pBg = new CTitleBg(INIT_PRIORITY);                                //動的確保
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Title001.png");   //ファイルパスを設定
	}

	//リザルト時														     
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pBg = new CResultBg();                                            //動的確保
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Result.png");     //ファイルパスを設定
	}

	//死亡時
	else if (mode == CScene::MODE::MODE_GAMEOVER)
	{
		pBg = new CGameOverBg();                                          //動的確保
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\SCREEN\\GameOver.jpg");  //ファイルパスを設定
	}

	//初期化が成功した時
	if (SUCCEEDED(pBg->Init()))
	{
		pBg->Lood(); //テクスチャの読み込み関数を呼ぶ
		return pBg;  //情報を返す
	}

	return nullptr; //無を返す
}


//================================================================================================================================================
//タイトル背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CTitleBg::CTitleBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CTitleBg::~CTitleBg()
{

}


//================================================================================================================================================
//リザルト背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CResultBg::CResultBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CResultBg::~CResultBg()
{

}


//================================================================================================================================================
//ゲームオーバー背景
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CGameOverBg::CGameOverBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CGameOverBg::~CGameOverBg()
{

}

//=================================
//更新処理
//=================================
void CGameOverBg::Update()
{
	SetRandom(FIRST_NUMBER + rand() % MAX_RAND);  //乱数を生成
	GetFrame()++;                                 //フレームを増やす

	//フレームが規定数以上行った時
	if (GetFrame() >= PROCESS_FRAME)
	{
		//===============================================
		//個数で分割（４つあるから４分割の値で計算）
		//===============================================

		if (GetRandom() >= FIRST_NUMBER && GetRandom() <= MAX_RAND* ONE_QUARTER)
		{
			SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, FIRST_SIZE_Y, CMain::SCREEN_HEIGHT + FIRST_PLUS_SIZE1_Y); //大きさの設定
			SetAlph(N_INIT_ALPHA_NUMBER);  //alpha値の初期化
			SetFrame(N_INIT_NUMBER);       //フレームの初期化
		}

		else if (GetRandom() >= MAX_RAND * ONE_QUARTER + NEXT_PLUS && GetRandom() <= MAX_RAND* TWO_QUARTER)
		{
			SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, -SECOND_SIZE1_Y, CMain::SCREEN_HEIGHT - SECOND_MINUS_SIZE1_Y); //大きさの設定
			SetAlph(N_INIT_ALPHA_NUMBER);  //アルファ値の初期化
			SetFrame(N_INIT_NUMBER);       //フレームの初期化
		}

		else if (GetRandom() >= MAX_RAND * TWO_QUARTER + NEXT_PLUS && GetRandom() <= MAX_RAND* THREE_QUARTER)
		{
			SetSIze(-THIRD_SIZE_X, CMain::SCREEN_WIDTH - THIRD_MINUS_SIZE1_X, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);
			SetAlph(ALPHA_0);          //アルファ値を下げる
			SetFrame(N_INIT_NUMBER);   //フレームの初期化
		}

		else
		{
			SetSIze(FOURTH_SIZE_X, CMain::SCREEN_WIDTH + FOURTH_THIRD_PLUS_SIZE1_X, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);
			SetAlph(ALPHA_1);          //アルファ値を下げる
			SetFrame(N_INIT_NUMBER);   //フレームの初期化
		}
	}

	//フレームが規定値以上へ行った時
	else if (GetFrame() >= ADJUSTMENT_FRAME)
	{
		SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, F_INIT_NUMBER, CMain::SCREEN_HEIGHT);  //大きさの設定
	}

	SetCol(CObject2D::RED, CObject2D::GREEN, CObject2D::BLUE,GetAlph());                   //色設定する
}


//===========================================================================================================================================================
//SHOP時の背景の処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CShopScreen::CShopScreen(int nPriority) : CManagerBg(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Screen\\Yellow.png"); //ファイルパスを設定
}


//=======================
//デストラクタ
//=======================
CShopScreen::~CShopScreen()
{

}


//=======================
//初期化処理
//=======================
HRESULT CShopScreen::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(F_INIT_NUMBER, CMain::SCREEN_WIDTH, F_INIT_NUMBER, CMain::SCREEN_HEIGHT); //大きさを設定
	SetCol(RED, GREEN, BLUE, ALPHA);                                                             //色設定する

	return S_OK; //成功を返す
}


//========================
//更新処理
//========================
void CShopScreen::Update()
{
	
}


//========================
//生成処理
//========================
CShopScreen* CShopScreen::Create()
{
	CShopScreen* pText = new CShopScreen(CObject2D::INIT_PRIORITY); //動的確保

    //初期化に成功した時
	if (SUCCEEDED(pText->Init()))
	{
		pText->Lood(); //テクスチャの読み込み
		return pText;  //情報を返す
	}
	return nullptr;    //無を返す
}
