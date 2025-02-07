//=========================================================
//
//瓦礫の破片オブジェクトの処理[direction_obj.cpp]
//Auther:Haruki Chiba
//
//=========================================================


//============================
//インクルード
#include "main.h"
#include "direction_obj.h"
#include "manager.h"


//============================
//コンストラクタ
//============================
CDebrisX::CDebrisX(int nPriority) : CObjectX(nPriority)
{
	SetFileName("data\\XFILE\\DirectionObj\\Debris.x"); //ファイルパスの設定
}

//============================
//デストラクタ
//============================
CDebrisX::~CDebrisX()
{

}

//============================
//初期化処理
//============================
HRESULT CDebrisX::Init()
{
	//初期化が成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;  //失敗を返す
	}

	SetLife(MAX_LIFE);  //ライフの設定

	return S_OK;        //成功した時
}

//==========================
//終了処理
//==========================
void CDebrisX::Uninit()
{
	CObjectX::Uninit(); //破棄処理
}

//========================
//更新処理
//========================
void CDebrisX::Update()
{
	SetAdjustLife()--; //ライフを減らす

	//ライフが尽きた時
	if (GetLife() <= N_INIT_NUMBER)
	{
		CObjectX::Release(); //自身を削除
		//CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::DEBRIS, m_nDirectionCount);
		return;              //処理を抜ける
	}
}


//======================
//描画処理
//======================
void CDebrisX::Draw()
{
	CObjectX::Draw(); //描画処理
}


//=====================
//生成
//=====================
CDebrisX* CDebrisX::Create(D3DXVECTOR3 pos)
{
	CDebrisX* m_pDebris3D = new CDebrisX(); //動的確保

	//初期化に成功した時
	if (SUCCEEDED(m_pDebris3D->Init()))
	{
		m_pDebris3D->GetPos() = pos;       //位置を同期させる
		m_pDebris3D->Lood();               //Xファイルを読み込む関数を呼ぶ
		return m_pDebris3D;                //情報を返す
	}

	return nullptr;                        //無を返す
}