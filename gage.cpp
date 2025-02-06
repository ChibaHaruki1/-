//=======================================
//
//ゲージに関する処理[gage.cpp]
//Ajther:Haruki Chiba
//
//=======================================


//===========================
//インクルード
#include "gage.h"
#include "manager.h"


//=======================================================================================================================================================
//燃料ゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CFuelGage::CFuelGage(int nPriority) : CObject3D(nPriority)
{
	SetSizeY(MAX_SIZEY); //Y軸の大きさの設定
	m_bUse = false;      //使われていないに設定
	m_bCharge = false;   //ゲージが溜まっていないに設定
}

//===========================
//デストラクタ
//===========================
CFuelGage::~CFuelGage()
{
	
}

//===========================
//初期化処理
//===========================
HRESULT CFuelGage::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	
	CObject3D::SetSize(MAX_SIZEX, GetSizeY(), MAX_SIZEZ); //大きさを設定

	return S_OK;										  //成功を返す
}

//============================
//破棄処理
//============================
void CFuelGage::Uninit()
{
	CObject3D::Uninit(); //破棄処理
}

//============================
//更新処理
//============================
void CFuelGage::Update()
{
	//位置を設定
	SetPos(D3DXVECTOR3(CManager::GetScene()->GetPlayerX()->GetPos().x - ADJUST_POSX,
		CManager::GetScene()->GetPlayerX()->GetPos().y + ADJUST_POSY,
		CManager::GetScene()->GetPlayerX()->GetPos().z));


	CObject3D::SetAdjustmentSizeY(MAX_SIZEX, GetSizeY(), MAX_SIZEZ);                  //Y軸用の大きさを設定
	CObject3D::SetCol(CObject3D::RED, CObject3D::GREEN, CObject3D::BLUE, GetAlpha()); //色の設定

	//使われている時とゲージが満タンの時
	if (m_bUse == true && m_bCharge == true)
	{
		CManager::GetScene()->GetPlayerX()->GetMove().y += MAX_PLUS_PLAYER_MOVE;      //プレイヤーのや軸の移動量を増やす

		//プレイヤーの重力が規定値より高い時
		if (CManager::GetScene()->GetPlayerX()->GetGravity() > MAX_PLAYER_GRAVITY)
		{
			CManager::GetScene()->GetPlayerX()->SetGravity(MAX_PLAYER_GRAVITY);       //重力の設定
		}

		CManager::GetScene()->GetPlayerX()->SetGravityFlag(false);                    //重力OFF

		//アルファ値が規定値以外の時
		if (GetAlpha() != MAX_ALPHA)
		{
			SetAlpha(MAX_ALPHA);                       //アルファ値の設定
		}

		//Y軸のサイズが最小値より高い時
		if (GetSizeY() > MIN_SIZEY)
		{
			SetAddjustSizeY() -= MAX_MAINAS_GAGESPEED; //Y軸の大きさを減らす
		}
		else
		{
			SetSizeY(MIN_SIZEY);                       //Y軸の大きさを初期化
			m_bCharge = false;                         //チャージ未完了
			m_bUse = false;                            //未使用
		}
	}

	//使われていない時
	if (m_bUse == false)
	{
		//アルファ値が０以上の時
		if (GetAlpha() > 0)
		{
			SetAdjustAlpha() -= MINUS_ALPHA;          //アルファ値を減らす
		}

		//Y軸のサイズが最大値より低い
		if (GetSizeY() < MAX_SIZEY)
		{
			SetAddjustSizeY() += MAX_PLUS_GAGESPEED;   //Y軸の大きさを増やす
		}
	}

	//チャージ未完了の時
	if (m_bCharge == false)
	{
		CManager::GetScene()->GetPlayerX()->SetGravityFlag(true); //重力ON

		//Y軸の大きさが規定値より小さい時
		if (GetSizeY() < MAX_SIZEY)
		{
			SetAddjustSizeY() += MAX_PLUS_GAGESPEED;              //Y軸の大きさを増やす
		}

		//Y軸の大きさが規定値以上の時
		else if (GetSizeY() >= MAX_SIZEY)
		{
			m_bCharge = true;                                     //チャージ完了
		}
	}

	CObject3D::Update();                                          //更新処理を呼ぶ
}


//============================
//描画処理
//============================
void CFuelGage::Draw()
{
	CObject3D::Draw(); //描画処理を呼ぶ
}

//============================
//生成処理
//============================
CFuelGage* CFuelGage::Create()
{
	CFuelGage* pFuelGage = new CFuelGage(); //動的確保

	//情報がある時
	if (pFuelGage != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pFuelGage->Init()))
		{
			pFuelGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png"); //ファイルパスの設定
			pFuelGage->Lood();                                                     //テクスチャの読み込み
			return pFuelGage;                                                      //情報を返す
		}
	}

	return nullptr;                                                                //無を返す
}


//=======================================================================================================================================================
//ゲージマネージャー処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CManagerGage::CManagerGage(int nPriority) : CObject2D(nPriority)
{
	m_fHPSizeX = MAX_PLAYER_HP_SIZE;       //プレイヤーのHPの設定
	m_fBossHPSizeX = CMain::SCREEN_WIDTH;  //ボスのHPの設定
	m_fSaveSizeX = CObject3D::F_INIT_NUMBER;          //セーブHPの設定
}

//===========================
//デストラクタ
//===========================
CManagerGage::~CManagerGage()
{

}

//===========================
//初期化処理
//===========================
HRESULT CManagerGage::Init()
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
void CManagerGage::Uninit(void)
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}


//=======================
//更新処理
//=======================
void CManagerGage::Update()
{
	
}


//=====================
//描画処理
//=====================
void CManagerGage::Draw()
{
	CObject2D::Draw(); //描画処理を呼ぶ
}


//===================================
//ゲージの生成
//===================================
CManagerGage* CManagerGage::Create(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr; //基底クラスのポインター

	//タイプがプレイヤーのHPの時
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGage(CRETAE_PRIORITY);                                                       //動的確保
		CreateLeave(type);                                                                                       //残すHPゲージの生成
		CManager::GetInstance()->GetCreateObjectInstnace(TYPE::FUELGAGE, CObject3D::N_INIT_NUMBER, pManagerGage->GetPos());  //燃料ゲージの生成
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage000.png");                                //ファイルパスの設定
	}

	//タイプがボスのHPの時
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGage(CRETAE_PRIORITY);                                                         //動的確保
		CreateLeave(type);                                                                                       //残すHPゲージの生成
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BossHpGage.png");                                //ファイルパスを設定
	}

	//情報がある時
	if (pManagerGage != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pManagerGage->Init()))
		{
			pManagerGage->Lood(); //テクスチャの読み込み
			return pManagerGage;  //情報を返す
		}
	}

	return nullptr;               //無を返す
}

//===================================
//残すゲージの生成
//===================================
CManagerGage* CManagerGage::CreateLeave(CObject2D::TYPE type)
{
	CManagerGage* pManagerGage = nullptr; //基底クラスのポインター

	//タイプがプレイヤーのHPの時
	if (type == CObject2D::TYPE::HP)
	{
		pManagerGage = new CPlayerHPGageLeave(CRETAE_LEAVE_PRIORITY);                //動的確保
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\RedGage001.png");    //ファイルパスの設定
	}

	//タイプがボスのHPの時
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		pManagerGage = new CBossHPGageLeave(CRETAE_LEAVE_PRIORITY);                  //動的確保
		pManagerGage->SetFileNamePass("data\\TEXTURE\\UI\\Gage\\BloackGage000.png"); //ファイルパスの設定
	}

	//情報がある時
	if (pManagerGage != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pManagerGage->Init()))
		{
			pManagerGage->Lood(); //テクスチャの読み込み
			return pManagerGage;  //情報を返す
		}
	}

	return nullptr;               //無を返す
}


//=======================================================================================================================================================
//プレイヤーのゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CPlayerHPGage::CPlayerHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX(); //プレイヤーのHPの大きさの設定
}

//===========================
//デストラクタ
//===========================
CPlayerHPGage::~CPlayerHPGage()
{

}

//===========================
//初期化処理
//===========================
HRESULT CPlayerHPGage::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetPlayerHPSizeX(), SIZE_Y, SIZE_Y1); //大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう

	return S_OK;       //成功を返す
}

//===========================
//更新処理
//===========================
void CPlayerHPGage::Update()
{
	//現在のHPゲージより高い時
	if (m_fSaveSizeX > GetPlayerHPSizeX())
	{
		m_fSaveSizeX -= MINUS_HPSIZEX;       //元々のHPゲージを減らす
	}

	//現在のHPゲージより低い時
	else if (m_fSaveSizeX <= GetPlayerHPSizeX())
	{
		m_fSaveSizeX = GetPlayerHPSizeX();   //現在のHPゲージと同期させる
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, m_fSaveSizeX, MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z); //滑らかに減っているように見せる
}


//=======================================================================================================================================================
//ボスのゲージの処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CBossHPGage::CBossHPGage(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetBossHPSizeX(); //ボスのHPの大きさの設定
}

//===========================
//デストラクタ
//===========================
CBossHPGage::~CBossHPGage()
{

}


//===========================
//初期化処理
//===========================
HRESULT CBossHPGage::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	//大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetBossHPSizeX(), (CMain::SCREEN_HEIGHT - ADJUST_POSY), CMain::SCREEN_HEIGHT);

	return S_OK;       //成功を返す
}

//===========================
//更新処理
//===========================
void CBossHPGage::Update()
{
	//現在のHPゲージより高い時
	if (m_fSaveSizeX > GetBossHPSizeX())
	{//減らされた分だけ減らす
		m_fSaveSizeX -= MINUS_HPSIZEX;   //元々のHPゲージを減らす
	}

	//現在のHPゲージより小さい時
	else if (m_fSaveSizeX <= GetBossHPSizeX())
	{
		m_fSaveSizeX = GetBossHPSizeX(); //現在のHPゲージと同期させる
	}

	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, m_fSaveSizeX, (CMain::SCREEN_HEIGHT + MINUS_SIZE_X1), CMain::SCREEN_HEIGHT); //滑らかに減っているように見せる
}


//=======================================================================================================================================================
//プレイヤーのHPゲージを残す処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CPlayerHPGageLeave::CPlayerHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = GetPlayerHPSizeX(); //プレイヤーのHPの大きさの設定
}

//===========================
//デストラクタ
//===========================
CPlayerHPGageLeave::~CPlayerHPGageLeave()
{

}


//===========================
//初期化処理
//===========================
HRESULT CPlayerHPGageLeave::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	//大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetPlayerHPSizeX(), MAX_PLAYERGAGE_SIZE_Y, MAX_PLAYERGAGE_SIZE_Z);

	return S_OK;       //成功を返す
}


//=======================================================================================================================================================
//ボスのHPゲージを残す処理
//=======================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CBossHPGageLeave::CBossHPGageLeave(int nPriority) : CManagerGage(nPriority)
{
	m_fSaveSizeX = CObject3D::N_INIT_NUMBER; //HPの初期化
}

//===========================
//デストラクタ
//===========================
CBossHPGageLeave::~CBossHPGageLeave()
{

}


//===========================
//初期化処理
//===========================
HRESULT CBossHPGageLeave::Init()
{
	//初期化が失敗するか判定
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	//大きさをあらかじめ決めないと一瞬画面にフルスクリーンで出てしまう
	CObject2D::SetSIze(CObject3D::F_INIT_NUMBER, GetBossHPSizeX(), (CMain::SCREEN_HEIGHT + CBossHPGage::MINUS_SIZE_X1), CMain::SCREEN_HEIGHT);

	return S_OK;       //成功を返す
}