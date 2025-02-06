//=================================
//
//UIをつける処理[ui.cpp]
//Auther;HARUKI CHIBA
//
//=================================


//=================================
//インクルード
#include "ui.h"
#include "manager.h"
#include <time.h>


//============================
//コンストラクタ
//============================
CUI::CUI(int nPriority) : CObject3D(nPriority)
{

}


//============================
//デストラク
//============================
CUI::~CUI()
{

}


//============================
//初期化処理
//============================
HRESULT CUI::Init()
{
	//初期化が成功した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//============================
//破棄処理
//============================
void CUI::Uninit()
{
	CObject3D::Uninit(); //破棄処理
}


//============================
//更新処理
//============================
void CUI::Update()
{

}


//============================
//描画処理
//============================
void CUI::Draw()
{
	CObject3D::Draw(); //描画処理
}

//============================
//当たり判定処理
//============================
void CUI::Hit()
{

}


//============================
//生成処理
//============================
CUI* CUI::Create(CObject3D::TYPE typeui)
{
	CUI* pUI = nullptr; //基底クラスのポインター

	//タイプがくっつくの時
	if (typeui == CObject3D::TYPE::CLING)
	{
		pUI = new CCreateInObject(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Effect\\effect000.jpg"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                   //テクスチャの読み込み
			return pUI;                                               //情報を返す
		}
	}

	//タイプが話すテキストの時
	else if (typeui == CObject3D::TYPE::TALKTEXTR)
	{
		pUI = new CTalkText(CREATE_PRIORITY); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Text\\Talk.png"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                    //テクスチャの読み込み
			return pUI;                                                //情報を返す
		}
	}

	//タイプがレーザーの時
	else if (typeui == CObject3D::TYPE::LASER)
	{
		pUI = new CLaserCamare(); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Effect\\Laser000.png"); //ファイルパスの設定
			pUI->CObject3D::Lood();                                  //テクスチャの読み込み
			return pUI;                                              //情報を返す
		}
	}

	return nullptr; //無を返す
}


//=============================================================================================================================
//現在textに書き出せるオブジェクトの場所にUIをつける処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CCreateInObject::CCreateInObject(int nPriority) : CUI(nPriority)
{

}


//============================
//デストラク
//============================
CCreateInObject::~CCreateInObject()
{

}


//=============================================================================================================================
//現在textに書き出せるオブジェクトの場所にUIをつける処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CTalkText::CTalkText(int nPriority) : CUI(nPriority)
{

}


//============================
//デストラク
//============================
CTalkText::~CTalkText()
{

}


//============================
//初期化処理
//============================
HRESULT CTalkText::Init()
{
	//初期化に成功した時
	if (FAILED(CUI::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ); //大きさの設定

	return S_OK;       //成功を返す
}


//============================
//描画処理
//============================
void CTalkText::Draw()
{
	CUI::Draw(); //描画処理
}


//=============================================================================================================================
//カメラから出るレーザーの処理
//=============================================================================================================================

//============================
//コンストラクタ
//============================
CLaserCamare::CLaserCamare(int nPriority) : CUI(nPriority)
{

}


//============================
//デストラク
//============================
CLaserCamare::~CLaserCamare()
{

}


//============================
//初期化処理
//============================
HRESULT CLaserCamare::Init()
{
	//初期化に失敗した時
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ);                                 //大きさを設定
	SetRot(D3DXVECTOR3(CObject3D::F_INIT_NUMBER, ADJUST_ROTY, ADJUST_ROTZ)); //向きを設定

	//位置を監視カメラの上部部分に設定する
	SetPos(D3DXVECTOR3(CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y - ADJUST_POSY,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z - ADJUST_POSZ));

	return S_OK;       //成功を返す
}


//============================
//更新処理
//============================
void CLaserCamare::Update()
{
	
}


//============================
//当たり判定処理
//============================
void CLaserCamare::Hit()
{
	//当たり判定
	//if (CObject3D::CollisionPrtsPlayer(SIZEY * ADJUST_ADDJUST_SIZE, SIZEX * ADJUST_ADDJUST_SIZE, SIZEZ * ADJUST_ADDJUST_SIZE) == true)

	srand((unsigned)time(NULL));                     //乱数系列を初期化
	SetRandom(MIN_RANDOM + rand() % MAX_RANDOM);     //乱数の生成(範囲指定1～２）

	//乱数が１の時
	if (GetRandom() == MIN_RANDOM)
	{
		//敵の生成
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, CObject3D::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + ADJUST_CREATE_POSX, GetPos().y + ADJUST_CREATE_POSY, CObject3D::F_INIT_NUMBER));
		//CObject3D::Release();     //自身の削除
		//return;                   //処理を抜ける
	}
	else
	{
		//敵の生成
		CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, CObject3D::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x - ADJUST_CREATE_POSX, GetPos().y + ADJUST_CREATE_POSY, CObject3D::F_INIT_NUMBER));
		//CObject3D::Release();     //自身の削除
		//return;                   //処理を抜ける
	}
}


//============================
//描画処理
//============================
void CLaserCamare::Draw()
{
	CObject3D::DrawBillboard(); //描画処理
}