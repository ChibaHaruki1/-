//===================================
//
//フェードの処理設定[bg.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "fade.h"
#include "rendererh.h"
#include "manager.h"


//==========================
//引数付きコンストラクタ
//==========================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetAlph(N_INIT_ALPHA_NUMBER);                  //アルファ値の設定
	m_Fade = FADE::FADE_IN;                        //フェードのタイプの初期化
	SetFileNamePass("data\\TEXTURE\\black.jpg");   //ファイルパスを設定
}


//======================
//コンストラクタ
//======================
CFade::~CFade()
{

}


//======================
//初期化処理
//======================
HRESULT CFade::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//======================
//終了処理
//======================
void CFade::Uninit(void)
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}

//=======================
//更新処理
//=======================
void CFade::Update()
{
	//フェードインの時
	if (m_Fade == FADE::FADE_IN)
	{
		//アルファ地が規定値以上の時
		if (GetAlph() >= MAX_FADE_SPEED)
		{
			SetAdjustAlpha() -= MAX_FADE_SPEED;  //アルファ値を減らす
		}

		SetCol(RED, GREEN, BLUE, GetAlph());      //色の設定
	}

	//フェードアウトの時
	else if (m_Fade == FADE::FADE_OUT)
	{
		//アルファ値が規定値以下の時
		if (GetAlph() <= FINISH_FADE_OUT)
		{
			SetAdjustAlpha() += MAX_FADE_SPEED;  //アルファ値を増やす
		}

		SetCol(RED, GREEN, BLUE, GetAlph());      //色の設定
	}
}


//=====================
//描画処理
//=====================
void CFade::Draw()
{
	CObject2D::Draw(); //描画処理を呼ぶ
}


//===================================
//オブジェクト生成
//===================================
CFade* CFade::Create()
{
	CFade* pFade = new CFade(CObject2D::INIT_PRIORITY); //動的確保

    //初期化が成功した時
	if (SUCCEEDED(pFade->Init()))
	{
		pFade->Lood(); //テクスチャの読み込み
		return pFade;  //情報を返す
	}

	return nullptr;    //無を返す
}
