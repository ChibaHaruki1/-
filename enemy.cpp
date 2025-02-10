//================================
//
//敵の処理[enemy.cpp]
//Auther:Chiba Haruki
//
//================================


//================================
//インクルード
#include "main.h"
#include "manager.h"
#include "enemy.h"
#include "player.x.h"


//=========================
//コンストラクタ
//=========================
CManagerEnemy::CManagerEnemy(int Priority) : CObjectX(Priority)
{

}


//=========================
//デストラクタ
//=========================
CManagerEnemy::~CManagerEnemy()
{

}


//=========================
//初期化処理
//=========================
HRESULT CManagerEnemy::Init()
{
	//初期化に成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//=========================
//終了処理
//=========================
void CManagerEnemy::Uninit()
{
	CObjectX::Uninit(); //破棄処理
}


//=========================
//更新処理
//=========================
void CManagerEnemy::Update()
{
	
}

//==========================
//描画処理
//==========================
void CManagerEnemy::Draw()
{
	CObjectX::Draw(); //描画処理
}

//==========================
//3Dモデルの敵の作成
//==========================
CManagerEnemy* CManagerEnemy::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemy* pManagerEnemy = nullptr; //基底クラスのポインター

	//タイプが敵の時
	if (type == TYPE::ENEMY)
	{
		pManagerEnemy = new CEnemyX(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\BattleShip000.x"); //ファイルパスの設定
		}
	}

	//タイプが敵001の時
	else if (type == TYPE::ENEMY001)
	{
		pManagerEnemy = new CEnemy001X(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy001.x"); //ファイルパスの設定(緑)
			pManagerEnemy->SetLife(CEnemy001X::MAX_ENEMY001_LIFE);        //ライフの設定
		}
	}

	//タイプが敵001の時
	else if (type == TYPE::ENEMY002)
	{
		pManagerEnemy = new CEnemy002X(); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pManagerEnemy->Init()))
		{
			pManagerEnemy->SetFileName("data\\XFILE\\ENEMY\\Enemy002.x"); //ファイルパスの設定(紫)
			pManagerEnemy->SetLife(CEnemy002X::MAX_ENEMY002_LIFE);        //ライフの設定
		}
	}

	//情報がある時
	if (pManagerEnemy != nullptr)
	{
		pManagerEnemy->SetPos(pos); //位置を引数と同期させる
		pManagerEnemy->Lood();      //Xファイルの読み込み
		pManagerEnemy->Size();      //サイズの取得
		return pManagerEnemy;       //情報を返す
	}

	return nullptr;                 //無を返す
}


//=====================================================================================================================================
//敵の処理
//=====================================================================================================================================

//=========================
//コンストラクタ
//=========================
CEnemyX::CEnemyX(int Priority) : CManagerEnemy(Priority)
{
	SetLife(MAX_LIFE);
}

//=========================
//デストラクタ
//=========================
CEnemyX::~CEnemyX()
{

}

//=========================
//更新処理
//=========================
void CEnemyX::Update()
{
	//TargetHeadingTowards(CManager::GetScene()->GetPlayerX(),2.0f);  //プレイヤーに向かう処理関数を呼ぶ

	//プレイヤーと当たった時
	if (CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER) == true)
	{
		SetAdjustFrame()++;         //弾を撃つ際のフレームを増やす

		//フレームが規定値より高い時
		if (GetFrame() >= MAX_FARME)
		{
			CManagerBullet::Create(D3DXVECTOR3(GetPos().x + CREATE_BULLET_0_MINUS_POS_X, GetPos().y + CREATE_BULLET_PLUS_POS_Y, GetPos().z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				SET_BULLET_LIFE, CObject3D::TYPE::BATTLESHIPBULLET);

			CManagerBullet::Create(D3DXVECTOR3(GetPos().x + CREATE_BULLET_1_PLUS_POS_X, GetPos().y + CREATE_BULLET_PLUS_POS_Y, GetPos().z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				SET_BULLET_LIFE, CObject3D::TYPE::BATTLESHIPBULLET);

			SetFrame(N_INIT_NUMBER); //フレームの初期化
		}
	}

	//ライフが尽きた時
	if (GetLife() <= N_INIT_NUMBER)
	{
		//爆発エフェクトを呼ぶ（1つ目）
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		//爆発エフェクトを呼ぶ（2つ目）
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		//スコアを加算
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);       

		CObjectX::Release(); //自身の削除
		return;              //処理を抜ける
	}

	CObjectX::Update();      //更新処理
}


//=====================================================================================================================================
//敵001の処理
//=====================================================================================================================================

//=========================
//コンストラクタ
//=========================
CEnemy001X::CEnemy001X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//デストラクタ
//=========================
CEnemy001X::~CEnemy001X()
{

}

//=========================
//更新処理
//=========================
void CEnemy001X::Update()
{
	SetAdjustRot().y += PLUS_ROT_Y; //Y軸の向きを加算

	//プレイヤーと当たった時
	if (CollisionPlayerSelect(this) == true)
	{
		//プレイヤーのHPを削る
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * CManagerBossEffect::MAX_DAMAGE;
	}

	//ライフが尽きた時
	if (GetLife() <= N_INIT_NUMBER)
	{
		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE); //スコアを加算
		CObjectX::Release();                                           //自身の削除
		return;                                                        //処理を抜ける
	}
}


//=====================================================================================================================================
//敵002の処理
//=====================================================================================================================================

//=========================
//コンストラクタ
//=========================
CEnemy002X::CEnemy002X(int Priority) : CManagerEnemy(Priority)
{

}

//=========================
//デストラクタ
//=========================
CEnemy002X::~CEnemy002X()
{

}

//=========================
//更新処理
//=========================
void CEnemy002X::Update()
{
	SetAdjustRot().x += PLUS_ROT_Y; //Y軸の向きを加算

	Move();                        //行動処理関数を呼ぶ

	//プレイヤーと当たった時
	if (CollisionPlayerSelect(this) == true)
	{
		//プレイヤーのHPを削る
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * CManagerBossEffect::MAX_DAMAGE;
	}

	//ライフが尽きた時
	if (GetLife() <= N_INIT_NUMBER)
	{
		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, N_INIT_NUMBER, D3DXVECTOR3(GetPos().x, GetPos().y + EXPLOSION_EFFECT_PLUS_POS_Y, GetPos().z));

		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE); //スコアを加算
		CObjectX::Release();                                           //自身の削除
		return;                                                        //処理を抜ける
	}
}


//=========================
//行動処理
//=========================
void CEnemy002X::Move()
{
	SetAdjustFrame()++; //フレームを増やす

	//第一行動
	if (GetFrame() <= ATTACKPATTEN_FRAME_1)
	{
		SetAdjustPos().y += ADJUST_POSY; //Y軸の位置を加算
	}

	//第二行動
	else if (GetFrame() <= ATTACKPATTEN_FRAME_2)
	{
		SetAdjustPos().y -= ADJUST_POSY; //Y軸の位置を減算
	}

	//終了
	else
	{
		SetFrame(N_INIT_NUMBER);         //フレームの初期化
	}
}