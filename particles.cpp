//==========================================
//
//パーティクルの処理[particles.cpp]
//Author:chiba haruki
//
//==========================================


//==========================================
//インクルード
#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//コンストラクタ
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	SetLife(MAX_PARTICLES001_LIFE);                  //ライフの設定
	SetFileNamePass("data\\TEXTURE\\Circle003.png"); //ファイルパスの設定
}


//============================
//デストラクタ
//============================
CParticles001::~CParticles001()
{

}


//============================
//初期化処理
//============================
HRESULT CParticles001::Init()
{
	//初期化が成功した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//==========================
//終了処理
//==========================
void CParticles001::Uninit()
{
	CObject3D::Uninit(); //破棄処理
}


//========================
//更新処理
//========================
void CParticles001::Update()
{
	SetSize(SIZEX, SIZEY, SIZEZ);   //大きさの設定

	SetAdjustLife()--;              //ライフを減らす

	SetAdjustPos().y += PLUS_POSY;  //Y軸の位置を増やす

	//ライフが０より小さい時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CObject3D::Release();       //自身の解放
		return;                     //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}
}


//======================
//描画処理
//======================
void CParticles001::Draw()
{
	CObject3D::DrawEffect(); //描画処理
}


//========================
//生成処理
//========================
CParticles001* CParticles001::Create(D3DXVECTOR3 pos)
{
	CParticles001* pPraticles = new CParticles001(CREATE_PRIORITY); //動的確保

	//情報がある時
	if (pPraticles != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pPraticles->Init()))
		{
			pPraticles->SetPos(pos);        //位置を引数と同期させる
			pPraticles->CObject3D::Lood();  //テクスチャの読み込み
			return pPraticles;              //情報を返す
		}
	}

	return nullptr;                         //無を返す
}