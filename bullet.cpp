//==================================
//
//弾の処理[bullet.h]
//Auther:Chiba Haruki
//
//==================================

//==================================
//インクルード
#include "main.h"
#include "manager.h"
#include "bullet.h"


//==============================================================================================================
//==================================================3D弾の処理==================================================
//==============================================================================================================

//=====================
//コンストラクタ
//=====================
CManagerBullet::CManagerBullet(int nPriority) :CObject3D(nPriority)
{

}

//=====================
//デストラクタ
//=====================
CManagerBullet::~CManagerBullet()
{

}


//=====================
//初期化処理
//=====================
HRESULT CManagerBullet::Init()
{
	//初期化に失敗したとき
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //失敗を返す
	}

	SetRot(D3DXVECTOR3(0.0f, INIT_ROTY, 0.0f));     //向きを設定
	SetSizeX(MAX_BULLET3D_SIZE_X);                  //X軸の大きさの設定
	SetSize(GetSizeX(), MAX_BULLET3D_SIZE_Y, 0.0f); //サイズの調整
	return S_OK;                                    //成功を返す
}


//=====================
//終了処理
//=====================
void CManagerBullet::Uninit()
{
	CObject3D::Uninit();  //基底クラスの破棄処理
}


//=====================
//更新処理
//=====================
void CManagerBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                         //エフェクトのライフの設定
	CManager::GetInstance()->GetEffect()->SetCol(255, 160, 0, GetAlpha());                  //色の設定

	//アルファ値が０より大きい時
	if (GetAlpha() > 0)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //アルファ値を減算する
	}

	SetAdjustLife()--; //ライフを減らす

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		//CallEffect(false);
		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　
}


//=====================
//描画処理
//=====================
void CManagerBullet::Draw()
{
	CObject3D::DrawBillboard(); //描画処理を呼ぶ
}


//====================
//弾の位置の設定処理
//====================
void CManagerBullet::SetInfo(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	SetPos(pos);    //弾の位置を引数と同期する
	SetMove(move);  //弾の移動量を引数と同期する
	SetLife(nLife); //寿命を設定する
}


//=========================
//弾の生成
//=========================
CManagerBullet* CManagerBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject::TYPE type)
{
	CManagerBullet* pBullet3D = nullptr; //基底クラスのポインター

	//タイプが弾の時
	if (type == CObject3D::TYPE::BULLET)
	{
		pBullet3D = new CBullet3D(3); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pBullet3D->Init()))
		{

		}
	}

	//タイプが敵の弾の時
	else if (type == CObject3D::TYPE::ENEMYBULLET)
	{
		pBullet3D = new CEnemyBullet(3); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //サイズの設定
		}
	}

	//タイプが戦艦の弾の時
	else if (type == CObject3D::TYPE::BATTLESHIPBULLET)
	{
		pBullet3D = new CEnemyBulletBattleShip(3); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CEnemyBullet::MAX_ENEMYBULLET_SIZE_X, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Y, CEnemyBullet::MAX_ENEMYBULLET_SIZE_Z); //サイズの設定
		}
	}

	//タイプがボスの弾の時
	else if (type == CObject3D::TYPE::BOSSBULLET)
	{
		pBullet3D = new CBossBullet(3); //動的確保

		//初期化が成功した時
		if (SUCCEEDED(pBullet3D->Init()))
		{
			pBullet3D->SetSize(CBossBullet::MAX_BOSSBULLET_SIZE_X, CBossBullet::MAX_BOSSBULLET_SIZE_Y, CBossBullet::MAX_BOSSBULLET_SIZE_Z);      //サイズの設定
		}
	}

	//情報を無くす
	if (pBullet3D != nullptr)
	{
		pBullet3D->SetFileNamePass("data\\TEXTURE\\bullet001.png"); //ファイルパスを設定
		pBullet3D->SetInfo(pos, move, nLife);                       //弾の情報を引数と同期
		pBullet3D->Lood();                                          //テクスチャの読み込み
		return pBullet3D;                                           //情報を無くす
	}

	return nullptr;                                                 //無を返す
}


//================================================================================================================================================
//プレイヤーの通常弾処理
//================================================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CBullet3D::CBullet3D(int nPriority) : CManagerBullet(nPriority)
{

}

//======================
//コンストラクタ
//======================
CBullet3D::~CBullet3D()
{

}

//===========================
//エフェクトの処理を呼ぶ
//===========================
void CBullet3D::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));         //爆発エフェクトを生成（1つ目）
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //爆発エフェクトを生成（2つ目）
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::THENDER, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));           //雷エフェクトを呼ぶ
	//CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::DEBRIS, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));            //破片エフェクトを呼ぶ


	CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());                                                        //爆発エフェクトの位置を設定
	CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos());                                                     //爆発エフェクトの位置を設定
	//CManager::GetInstance()->GetThander()->SetEffect(GetPos());                                                          //雷エフェクトの位置を設定
	//CManager::GetInstance()->GetDebris()->SetEffect(GetPos());                                                           //破片エフェクトの位置を設定
}

//===============================
//オブジェクトとの当たり判定
//===============================
void CBullet3D::CollisionOnObject()
{
	//敵001の作られた数分回す
	for (int nCount1 = 0; nCount1 < CManager::GetInstance()->GetEnemy001Count() + 1; nCount1++)
	{
		//敵001の情報がある時
		if (CManager::GetInstance()->GetEnemy001(nCount1) != nullptr)
		{
			//当たり判定
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy001(nCount1)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy001(nCount1)->GetModelSize() * 0.5f, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy001(nCount1)->SetAdjustLife() -= MINUS_ENEMY001_LIFE;          //敵のライフを減らす

				//敵のライフが０以下の時
				if (CManager::GetInstance()->GetEnemy001(nCount1)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY001, nCount1);         //ポインターをnullptrにする
				}

				CallEffect(false); //エフェクト処理を呼ぶ
				SetLife(0);        //ライフを０にする
				return;            //処理を抜ける
			}
		}
	}

	//敵002の作られた数分回す
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetEnemy002Count() + 1; nCount2++)
	{
		//敵002の情報がある時
		if (CManager::GetInstance()->GetEnemy002(nCount2) != nullptr)
		{
			//当たり判定
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemy002(nCount2)->GetPos(), MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z, CManager::GetInstance()->GetEnemy002(nCount2)->GetModelSize() * 0.5f, GetSizeX()) == true)
			{
				CManager::GetInstance()->GetEnemy002(nCount2)->SetAdjustLife() -= MINUS_ENEMY001_LIFE;          //敵のライフを減らす

				//敵のライフが０以下の時
				if (CManager::GetInstance()->GetEnemy002(nCount2)->GetLife() <= 0)
				{
					CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMY002, nCount2);         //ポインターをnullptrにする
				}

				CallEffect(false); //エフェクト処理を呼ぶ
				SetLife(0);        //ライフを０にする
				return;            //処理を抜ける
			}
		}
	}

	
	//カメラの上部分の作られた数分回す
	for (int nCamera = 0; nCamera < CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() + 1; nCamera++)
	{
		//カメラの上部分の情報がある時
		if (CManager::GetInstance()->GetSurveillanceCameraUp(nCamera) != nullptr)
		{
			//カメラとの当たり判定
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->GetPos(),
				MAX_BULLET3D_SIZE_X * ADJUST_HIT_CAMERA_UP, MAX_BULLET3D_SIZE_Y * ADJUST_HIT_CAMERA_UP, MAX_BULLET3D_SIZE_Z * ADJUST_HIT_CAMERA_UP,
				CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->GetModelSize()))
			{
				CManager::GetInstance()->GetSurveillanceCameraUp(nCamera)->Release();                        //カメラの上部分の削除
				CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SURVEILLANCECAMERAUP, nCamera);  //カメラポインターをnullptrにする

				SetLife(0); //ライフを０にする
				return;     //処理を抜ける
			}
		}
	}

	
	//モーション付きの敵の001の作られた数分回す
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count() + 1; nMotionInEnemy001++)
	{
		//モーション付きの敵001の情報がある時
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			//パーツ数分回す
			for (int nMotionEnemy001 = 0; nMotionEnemy001 < CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetEnemy001PartsNumber(); nMotionEnemy001++)
			{
				//モーション付きの敵001の当たり判定
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPartsEnemy(nMotionEnemy001),
					GetSizeX(), MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePartsEnemy(nMotionEnemy001) * ADJUST_HIT_MOTIONENENY001))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->SetAdjustLife() -= MINUS_ENEMYMOTION001_LIFE; //ライフを減らす

					//D3DXVECTOR3 Pos = CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPrtsEnemy(nMotionEnemy001);
					 
					//死亡した時
					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //ポインターをnullptrにする
					}

					CallEffect(false); //エフェクト処理を呼ぶ
					SetLife(0);        //ライフを０にする
					return;            //処理を抜ける
				}
			}
		}
	}

	//ボスの情報がある時
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		//ボスの最大パーツ数分回す
		for (int nCount2 = 2; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//パーツの描画がされている時
			if (CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->GetDraw() == true)
			{
				//ボスとの当たり判定
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3DcircleBoss(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPartsBoss(nCount2),
					MAX_BULLET3D_SIZE_X, MAX_BULLET3D_SIZE_Y, MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetBoss()->GetModelSizePartsBoss(nCount2), GetSizeX(), nCount2))
				{
					CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= CMain::SCREEN_WIDTH * MINUS_BOSS_HPGAGE; //ボスのHPゲージを減らす

					//指定のpartsを描画しない＋処理から外す条件にする(右足先般)
					if (nCount2 == 11 || nCount2 == 12 || nCount2 == 13)
					{
						CManager::GetInstance()->GetBoss()->m_pModelPrtsBoss[nCount2]->SetDraw(false); //描画をしないに設定
					}

					CallEffect(false);       //エフェクト処理を呼ぶ
					CObject3D::Release();    //自身の解放
					return;                  //処理を抜ける
				}
			}
		}
	}
}


//======================================================================================================================================================================
//敵の弾の処理
//======================================================================================================================================================================

//static変数の初期化
float CEnemyBullet::m_fAdditionPosY = MINUS_ROTY; //位置を初期設定

//=====================
//コンストラクタ
//=====================
CEnemyBullet::CEnemyBullet(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//デストラクタ
//=====================
CEnemyBullet::~CEnemyBullet()
{

}


//=====================
//更新処理
//=====================
void CEnemyBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, BLUE, GetAlpha());                   //色の設定
	SetAdjustPos().y -= m_fAdditionPosY;                                                   //Y軸の位置を減らす

	//アルファ値が0より大きい時
	if (GetAlpha() > 0)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //アルファ値を減算
	}

	SetAdjustLife()--; //寿命カウント

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CEnemyBullet::CallEffect(bool bUse)
{

}


//===============================
//オブジェクトとの当たり判定
//===============================
void CEnemyBullet::CollisionOnObject()
{
	//プレイヤーのパーツ数分回す
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//プレイヤーの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosParts(nCount2),
			MAX_BULLET3D_SIZE_X * ADJUST_HIT, MAX_BULLET3D_SIZE_Y * ADJUST_HIT, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount2), 0.0f))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HPゲージを減らす

			CallEffect(true);         //エフェクト処理を呼ぶ
			CObject3D::Release();     //自身の解放
			return;                   //処理を抜ける
		}
	}
}


//======================================================================================================================================================================
//戦艦の弾の処理
//======================================================================================================================================================================

//=====================
//コンストラクタ
//=====================
CEnemyBulletBattleShip::CEnemyBulletBattleShip(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//デストラクタ
//=====================
CEnemyBulletBattleShip::~CEnemyBulletBattleShip()
{

}


//=====================
//更新処理
//=====================
void CEnemyBulletBattleShip::Update()
{
	SetAdjustFrame()++; //フレームを増やす

	//フレームが規定値より高い時
	if (GetFrame() >= 10)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
		CManager::GetInstance()->GetEffect()->SetLife(SET_BULLET_LIFE);                         //エフェクトのライフを設定
		CManager::GetInstance()->GetEffect()->SetCol(0, 0, BLUE, GetAlpha());                   //色の設定
		SetFrame(0);                                                                            //フレームの初期化

		//アルファ値が0より大きい時
		if (GetAlpha() > 0)
		{
			SetAdjustAlpha() -= MINUS_ALPHA; //アルファ値を減算
		}
	}

	SetAdjustPos().y -= 2.5f;     //Y軸の位置を減らす

	SetAdjustLife()--;            //寿命カウント

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CEnemyBulletBattleShip::CallEffect(bool bUse)
{

}


//===============================
//オブジェクトとの当たり判定
//===============================
void CEnemyBulletBattleShip::CollisionOnObject()
{
	//体の当たり判定のみで処理を軽くする
	D3DXVECTOR3 pos = CManager::GetScene()->GetPlayerX()->GetPosParts(0);

	//プレイヤーの当たり判定
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), pos,
		MAX_BULLET3D_SIZE_X * ADDJUST_HIT, MAX_BULLET3D_SIZE_Y * ADDJUST_HIT, MAX_BULLET3D_SIZE_Z,
		CManager::GetScene()->GetPlayerX()->GetModelSizeParts(0), 0.0f) == true)
	{
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HPゲージを減らす

		CallEffect(true);         //エフェクト処理を呼ぶ
		CObject3D::Release();     //自身の解放
		return;                   //処理を抜ける
	}
}


//======================================================================================================================================================================
//ボスの弾の処理
//======================================================================================================================================================================

//=====================
//コンストラクタ
//=====================
CBossBullet::CBossBullet(int nPriority) :CManagerBullet(nPriority)
{

}

//=====================
//デストラクタ
//=====================
CBossBullet::~CBossBullet()
{
	
}


//=====================
//更新処理
//=====================
void CBossBullet::Update()
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EFFECT, 0, GetPos()); //エフェクト（軌跡）を生成する
	CManager::GetInstance()->GetEffect()->SetCol(0, 0, 200, GetAlpha());                    //色の設定

	SetAdjustPos().y -= MINUS_POSY;                                                         //Y軸の位置を減算する

	//アルファ値が0より大きい時
	if (GetAlpha() > 0)
	{
		SetAdjustAlpha() -= MINUS_ALPHA; //アルファ値を減算
	}

	SetAdjustLife()--; //ライフを減らす

	//寿命が尽きた
	if (GetLife() <= 0)
	{
		CallEffect(false);         //エフェクト処理を呼ぶ

		CObject3D::Release();      //自身の解放
		return;                    //処理を抜けることによって、バッファのアクセス違反を防ぐ（破棄しているから）
	}

	CObject3D::Update();           //基底クラスの更新処理を呼ぶ
	CollisionOnObject();           //当たり判定処理を呼ぶ　（処理を抜けたいから最後に呼ぶ）
}


//===========================
//エフェクトの処理を呼ぶ
//===========================
void CBossBullet::CallEffect(bool bUse)
{
	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PILLAROFFIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //柱状の炎エフェクトを呼ぶ
	CManager::GetInstance()->GetPillarOfFire()->SetEffect(D3DXVECTOR3(GetPos().x, GetPos().y + 200.0f, GetPos().z));   //柱状の炎エフェクトの位置を設定
}


//===============================
//オブジェクトとの当たり判定
//===============================
void CBossBullet::CollisionOnObject()
{
	//プレイヤーのパーツ数分回す
	for (int nCount2 = 0; nCount2 < CObjectX::MAX_PRTS; nCount2++)
	{
		//プレイヤーの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetScene()->GetPlayerX()->GetPosParts(nCount2),
			MAX_BULLET3D_SIZE_X * 0.5f, MAX_BULLET3D_SIZE_Y * 0.5f, 0.0f,
			CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount2), 0.0f))
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MINUS_PLAYER_HPGAGE; //HPゲージを減らす

			CallEffect(true);         //エフェクト処理を呼ぶ
			CObject3D::Release();     //自身の解放
			return;                   //処理を抜ける
		}
	}
}