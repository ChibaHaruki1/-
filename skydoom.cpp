//==================================
//
//障害物の処理[block.cpp]
//Auther:Chiba Haruki
//
//==================================


//==================================
//インクルード
#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "skydoom.h"


//============================
//コンストラクタ
//============================
CSkyDoom::CSkyDoom(int nPriority) : CObjectX(nPriority)
{
	
}


//============================
//デストラクタ
//============================
CSkyDoom::~CSkyDoom()
{

}


//============================
//初期化処理
//============================
HRESULT CSkyDoom::Init()
{
	//初期化処理に成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//==========================
//終了処理
//==========================
void CSkyDoom::Uninit()
{
	CObjectX::Uninit(); //破棄処理
}

//========================
//更新処理
//========================
void CSkyDoom::Update()
{
	////向きの更新（動いているように見せる）
    //GetRot().x += 0.0001f;
	//GetRot().z += 0.0001f;

	//Dキーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetRot().y += ADJUST_ROT_Y; //動いた方向と同じ向きに傾く
		SetAdjustMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	//Aキーが押された時
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetRot().y -= ADJUST_ROT_Y; //動いた方向と同じ向きに傾く
		SetAdjustMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPos().y; //プレイヤーのｙ軸と常に同期させる＝落ちた時に自然に見せれる
	GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x; //プレイヤーのｘ軸と常に同期させる

	CObjectX::Update(); //位置の更新処理
}

//======================
//描画処理
//======================
void CSkyDoom::Draw()
{
	CObjectX::Draw(); //描画処理
}


//========================
//建物を生成
//========================
CSkyDoom* CSkyDoom::Create(D3DXVECTOR3 pos, int nNumber)
{
	CSkyDoom* pCBlockX = new CSkyDoom(CRETAE_PRIORITY); //動的確保

	//初期化に成功
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//番号が０の時
		if (nNumber == CREATE_NUMBER_0)
		{
			pCBlockX->SetFileName("data\\XFILE\\StageObj\\SkyDoom.x");      //宇宙
		}

		//番号が１の時
		else if (nNumber == CREATE_NUMBER_1)
		{
			pCBlockX->SetFileName("data\\XFILE\\StageObj\\SkyDoom001.x");  //曇り空
		}

		pCBlockX->GetPos() = pos;   //位置を同期させる
		pCBlockX->CObjectX::Lood(); //Xファイルを読み込む関数を呼ぶ
		return pCBlockX;            //情報を返す
	}

	return nullptr;                 //無を返す
}
