//========================================
//
//ビルボード処理[billboard.cpp]
//Auther:Haruki Chiba
//
//========================================


//========================================
//インクルード
#include "billboard.h"
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=========================
//コンストラクタ
//=========================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{
	
}


//=========================
//デストラクタ
//=========================
CBillboard::~CBillboard()
{

}


//=========================
//初期化処理
//=========================
HRESULT CBillboard::Init()
{
	//初期化に失敗したとき
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	SetPos(D3DXVECTOR3(MAX_BILLBOARD_SIZE_X, MAX_BILLBOARD_SIZE_Y, F_INIT_NUMBER)); //位置の設定

	return S_OK;       //成功を返す
}


//=========================
//終了処理
//=========================
void CBillboard::Uninit()
{
	CObject3D::Uninit(); //破棄処理を呼ぶ
}


//=========================
//更新処理
//=========================
void CBillboard::Update()
{
	
}


//=========================
//描画処理
//=========================
void CBillboard::Draw()
{
   CObject3D::Draw(); //描画処理を呼ぶ
}

//=========================
//ビルボードの生成
//=========================
CBillboard* CBillboard::Create()
{
	CBillboard* pBillboard = new CBillboard(); //動的確保

    //初期化に成功した時
	if (SUCCEEDED(pBillboard->Init()))
	{
		pBillboard->Lood(); //テクスチャの読み込み
		return pBillboard;  //情報を返す
	}

	return nullptr;         //無を返す
}