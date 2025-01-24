//=========================================================================
//
//モーション付きの敵の処理[enemyinmotion.cpp]
//Auther;Haruki Chiba
//
//=========================================================================


//==============================
//インクルード
#include "enemyinmotion.h"
#include "manager.h"
#include <time.h>


//=============================
//コンストラクタ
//=============================
CManagerEnemyInMotion::CManagerEnemyInMotion(int nPriority) : CEnemyCharacter(nPriority)
{
	m_nJumpFrame = 0;   //飛ぶまでの時間の初期化
	JumpNumber = 0;     //飛ぶ番号の初期化
	JumpRecastTime = 0; //飛ぶまでのリキャストタイムの初期化
}

//=============================
//デストラクタ
//=============================
CManagerEnemyInMotion::~CManagerEnemyInMotion()
{

}

//=============================
//初期化処理
//=============================
HRESULT CManagerEnemyInMotion::Init()
{
	//初期化に成功した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;                           //失敗を返す
	}

	CEnemyCharacter::LoodEnemy(GetFileName());   //読み込むファイルパスを設定
	CEnemyCharacter::SetMotionEnemy(ENEMYWALK);  //モーションの初期化

	return S_OK;                                 //成功を返す
}

//==============================
//破棄処理
//==============================
void CManagerEnemyInMotion::Uninit()
{
	CEnemyCharacter::Uninit(); //各パーツの破棄処理
}

//==============================
//更新処理
//==============================
void CManagerEnemyInMotion::Update()
{
	
}

//==============================
//描画処理
//==============================
void CManagerEnemyInMotion::Draw()
{
	CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //描画処理
}

//==============================
//生成処理
//==============================
CManagerEnemyInMotion* CManagerEnemyInMotion::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemyInMotion* pEnemyInMotion = nullptr; //基底クラスのポインター

	//タイプがモーション付きの敵の時
	if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		pEnemyInMotion = new CEnemyInMotion();   //動的確保
		pEnemyInMotion->SetFileName("Enemy000"); //ファイルパスの設定
	}

	//タイプがモーション付きの敵001の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		pEnemyInMotion = new CEnemyInMotion001(); //動的確保
		pEnemyInMotion->SetFileName("Enemy001");  //ファイルパスの設定
	}

	//情報がある時
	if (pEnemyInMotion != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pEnemyInMotion->Init()))
		{
			pEnemyInMotion->SetPos(pos); //位置の同期
			return pEnemyInMotion;       //情報を返す
		}
	}

	return nullptr; //無を返す
}


//====================================================================================================================================
//敵の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion::CEnemyInMotion(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetAddjustRot().y -= D3DX_PI_ORI; //向きの設定
}

//=============================
//デストラクタ
//=============================
CEnemyInMotion::~CEnemyInMotion()
{

}

//==============================
//更新処理
//==============================
void CEnemyInMotion::Update()
{
	CEnemyCharacter::UpdateEnemy001();                                                       //モーションの情報を更新する

	//プレイヤーと当たっている時
	if (CObjectX::CollisionPlayerInEnemy(this,4.0f)==true)
	{
		CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);     //モーションの種類を設定

		SetAddjustFrame()++; //フレームを増やす

		//フレームが規定値より高い時	
		if (GetFrame()>= MAX_FRAME_BUULET)
		{
			//弾の生成
			CManagerBullet::Create(D3DXVECTOR3(this->GetPosPrtsEnemy(0).x, this->GetPosPrtsEnemy(0).y, this->GetPosPrtsEnemy(0).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED),
				CManagerBullet:: SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

			SetFrame(0); //フレームを０にする
		}
	}

	//当たっていない時
	else
	{
		//飛んでいない時
		if (GetJumpFlag() == false)
		{
			CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定
			TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //プレイヤーに向かうように設定
		}
	}

	Junp(TYPE::ENEMYINMOTION, 15.0f);                          //ジャンプと重力処理関数を呼ぶ

	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//地面用ブロックの情報がある時
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			//飛ぶ
			if (JumpNumber == -1)
			{
				//自機と地面用ブロックが当たったら
				if (GetCollision() ->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, GetMove()) == true)
				{
					//飛ぶ時のリキャストタイムが０以下の時
					if (JumpRecastTime <= 0)
					{
						m_nJumpFrame++; //飛ぶまでの時間を増やす

						//飛ぶまでの時間が規定値より高い時
						if (m_nJumpFrame >= MAX_FRAME_JUMP)
						{
							SetJumpFlag(true); //飛ぶフラグをOnにする

							m_nJumpFrame = 0;  //飛ぶまでの時間の初期化
							JumpNumber++;      //飛ぶ番号の増加
							return;            //処理を抜ける
						}
					}

					//飛ぶ時間のリキャストタイムが０以上の時
					else if (JumpRecastTime >= 0)
					{
						JumpRecastTime--; //減らす
					}

				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						GravityTogether(); //重力を同期させる

						//y軸の位置を設定
						SetAddjustPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
					}
				}
			}

			//飛ばない
			else if (JumpNumber == 0)
			{
				//自機と地面用ブロックが当たったら
				if (GetCollision() ->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, GetMove()) == true)
				{
					JumpRecastTime = 5; //リキャストタイムの設定
					JumpNumber = -1;    //飛ぶ番号の次は飛ぶに設定
					return;             //処理を抜ける
				}
				else
				{
					//地面用ブロックの上に乗っている時
					if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						GravityTogether(); //重力を同期させる

						//y軸の位置を設定
						SetAddjustPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
							CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
					}
				}
			}

		}
	}

	CObjectX::Update(); //位置の更新
}


//====================================================================================================================================
//敵001の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	GetRot().y = -D3DX_PI_ORI; //向きを設定（右向き）
	SetLife(MAX_LIFE);         //ライフの設定
	m_nHitFrame = 0;           //当たった時にフレームの初期化
	m_bHit = false;            //当たっていないに設定
}

//=============================
//デストラクタ
//=============================
CEnemyInMotion001::~CEnemyInMotion001()
{

}


//==============================
//更新処理
//==============================
void CEnemyInMotion001::Update()
{
	//プレイヤーが判定の範囲内に来たら更新処理を実行する
	if (CObjectX::CollisionPlayerInEnemy(this, 10.0f) == true)
	{
		//生きている時
		if (GetLife() > 0)
		{
			CEnemyCharacter::UpdateEnemy001();                                                    //モーションの情報を更新する

			//プレイヤーと当たっている時
			if (CObjectX::CollisionPlayerInEnemy(this, 4.0f) == true)
			{
				CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //モーションの種類を設定

				SetAddjustFrame()++;     //弾を撃つ際のフレームを増やす

				//フレームが規定数に達した時
				if (GetFrame()>= 60)
				{
					//弾の生成
					CManagerBullet::Create(D3DXVECTOR3(this->GetPosPrtsEnemy(4).x + 100.0f, this->GetPosPrtsEnemy(4).y + 30.0f, this->GetPosPrtsEnemy(4).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, 0.0f, -cosf(GetRot().y) * MAX_BUULET_SPEED),
						CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

					SetFrame(0); //フレームを０にする
				}

				//プレイヤーが敵に接触したら
				if (CObjectX::CollisionPlayerInEnemy(this, 1.5f) == true)
				{
					m_bHit = true; //当たった判定をOnにする
				}
			}

			//プレイヤーと当たってない時
			else
			{
				//向きの初期化
				m_pModelPrtsEnemy[0]->GetRot().x = 0.0f;                  //パーツの向きの初期化
				CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY);  //弾の向きの初期化

				//飛んでいないとき
				if (GetJumpFlag() == false)
				{
					CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定

					//ジャンプのリキャストタイムが切れた時
					if (m_nJumpFrame == 0)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);        //プレイヤーに向かうように設定
					}
				}
			}

			//プレイヤーが敵に当たった時
			if (m_bHit == true)
			{
				PlayerBloWwaway();               //プレイヤーの吹き飛び処理を呼ぶ
			}

			Junp(TYPE::ENEMYINMOTION001, 15.0f); //ジャンプと重力処理関数を呼ぶ
			WhenCollisionBlock();                //地面用のブロックに触れている時の処理
			CObjectX::Update();                  //move値の更新
		}

		//死んだ時
		else if (GetLife() <= 0)
		{
			SetAddjustDieFrame()++; //死亡フレームを増やす

			//srand((unsigned)time(NULL));  //乱数系列を初期化

			//第一行動
			if (GetDieFrame() <= 1)
			{
				//爆発エフェクトを呼ぶ
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f)); 
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//爆発エフェクトの大きさを設定
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);                                 
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);      


				//爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion()->SetEffect(GetPos());         
				CManager::GetInstance()->GetExplosion001()->SetEffect(GetPos());      
			}

			//第二行動
			else if (GetDieFrame() <= 20)
			{

			}

			//第三行動
			else if (GetDieFrame() <= 21)
			{
				SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //乱数の生成

				//爆発エフェクトを呼ぶ
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//爆発エフェクトの大きさを設定
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);


				//爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//第四行動
			else if (GetDieFrame() <= 40)
			{

			}

			//第五行動
			else if (GetDieFrame() <= 41)
			{
				SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //乱数の生成

				//爆発エフェクトを呼ぶ
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//爆発エフェクトの大きさを設定
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, 0.0);

				//爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//第六行動
			else if (GetDieFrame() <= 60)
			{

			}

			//第七行動
			else if (GetDieFrame() <= 61)
			{

				SetRandom(-MIN_RANDOM2 + rand() % MAX_RANDOM2); //乱数の生成

				//爆発エフェクトを呼ぶ
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));


				//爆発エフェクトの大きさを設定
				CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, 0.0f);
				CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, 0.0);

				//爆発エフェクトの位置を設定
				CManager::GetInstance()->GetExplosion()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));    
				CManager::GetInstance()->GetExplosion001()->SetEffect(D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z)); 
			}

			//終了
			else
			{
				CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);  //スコアを加算
				CObjectX::Release();                                            //自身を削除
				return;                                                         //処理を抜ける
			}
		}
	}
}

//===============================================
//プレイヤーが敵に当たった時
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //当たったフレームを増やす

	//当たった瞬間
	if (m_nHitFrame <= 1)
	{
		//プレイヤーのHPを削る
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * MAX_DAMAGE;
	}

	//Hitframeが既定値へいった時
	else if (m_nHitFrame <= 20)
	{

		//左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += 10.0f;  //右に移動
		}

		//右向きの時
		else if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= 10.0f;  //左に移動
		}
	}

	//終了
	else
	{
		m_nHitFrame = 0; //hitframeを初期化
		m_bHit = false;  //当たった判定をoffにする
	}
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//左向きの時
	if (GetRot().y >= D3DX_PI_ORI)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber()==1)
		{
			m_pModelPrtsEnemy[0]->GetRot().x += ADDJUST_PRTAS_ROTX;         //パーツのX軸の向きを加算する
			CEnemyBullet::SetAddjustAdditionPosY() -= ADDJUST_BULLET_ROTY;  //弾のX軸の向きを減算する
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			m_pModelPrtsEnemy[0]->GetRot().x -= ADDJUST_PRTAS_ROTX;        //パーツのX軸の向きを減算する
			CEnemyBullet::SetAddjustAdditionPosY() += ADDJUST_BULLET_ROTY; //弾のX軸の向きを加算する
		}
	}

	//右向きの時
	else if (GetRot().y <= -D3DX_PI_ORI)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 1)
		{
			m_pModelPrtsEnemy[0]->GetRot().x -= ADDJUST_PRTAS_ROTX;        //パーツのX軸の向きを減算する
			CEnemyBullet::SetAddjustAdditionPosY() += ADDJUST_BULLET_ROTY; //弾のX軸の向きを加算する
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == 2)
		{
			m_pModelPrtsEnemy[0]->GetRot().x += ADDJUST_PRTAS_ROTX;        //パーツのX軸の向きを加算する
			CEnemyBullet::SetAddjustAdditionPosY() -= ADDJUST_BULLET_ROTY; //弾のX軸の向きを減算する
		}
	}

	Correctionrot(); //向きを修正する関数を呼ぶ
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	//地面用のブロックの生成数分回す
	for (int nCount = 0; nCount < CManager::GetInstance()->GetFieldBlockCount() + 1; nCount++)
	{
		//敵の最大パーツ数分回す
		for (int nEnemyCount = 0; nEnemyCount < MAX_ENEMYPARTS; nEnemyCount++)
		{
			//地面用ブロックの情報がある時
			if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
			{
				//飛ぶ
				if (JumpNumber == -1)
				{
					//自機と地面用ブロックが当たったら
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.1f, GetMove()) == true)
					{
						//リキャストタイムが０以下の時
						if (JumpRecastTime <= 0)
						{
							m_nJumpFrame++;             //飛ぶフレームを増やす

							SetMotionEnemy(ENEMYJUMP);  //ジャンプモーションの設定

							//ジャンプフレームが規定値より高い時
							if (m_nJumpFrame >= 40)
							{
								SetJumpFlag(true); //飛ぶ
								m_nJumpFrame = 0;  //フレームの初期化
								JumpNumber++;      //ジャンプナンバーを増やす（次は飛ばないに設定）

								return;            //処理を抜ける
							}
						}

						//リキャストタイムが０以上の時
						else if (JumpRecastTime >= 0)
						{
							JumpRecastTime--; //減らす
						}
						return; //処理を抜ける
					}
					else
					{
						//地面用ブロックの上に乗っている時
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //重力を同期させる

							//y軸の位置を設定
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;
						}
					}
				}

				//飛ばない
				else if (JumpNumber == 0)
				{
					//自機と地面用ブロックが当たったら
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.0f, GetMove()) == true)
					{
						JumpRecastTime = 5; //リキャストタイムの設定
						JumpNumber = -1;    //ジャンプナンバーの設定（次は飛ぶに設定）
						return;             //処理を抜ける
					}
					else
					{
						//地面用ブロックの上に乗っている時
						if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
						{
							GravityTogether(); //重力を同期させる

							//y軸の位置を設定
							GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y +
								CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

							SetJumpFlag(false); //飛ばない
						}
					}
				}
			}
		}
	}

	//道用ブロック分回す
	for (int nCount2 = 0; nCount2 < CManager::GetInstance()->GetRoadBlockCount() + 1; nCount2++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//当たっている時
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.01f, GetMove()) == true)
			{

			}
			else
			{
				//上に当たっている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether(); //重力の同期

					//y軸の位置を設定
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					SetJumpFlag(false); //ジャンプフラグをOff
				}
			}
		}
	}

	//壁兼道用ブロック分回す
	for (int nCount3 = 0; nCount3 < CManager::GetInstance()->GetWallRoadBlockCount() + 1; nCount3++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			//当たっている時
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * 1.01f, GetMove()) == true)
			{

			}
			else
			{
				//上に当たっている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether(); //重力の同期

					//y軸の位置を設定
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					SetJumpFlag(false); //フラグをOffにする
				}
			}
		}
	}
	
	//壁兼道001用ブロック分回す
	for (int nCount4 = 0; nCount4 < CManager::GetInstance()->GetWallRoadBlock001Count() + 1; nCount4++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//上に当たっている時
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				GravityTogether(); //重力の同期

				//y軸の位置を設定
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;


				SetJumpFlag(false); //フラグをOffにする
			}
		}
	}
}

//===============================================
//向きを修正
//===============================================
void CEnemyInMotion001::Correctionrot()
{
	//加減算してきた変数の値が既定の位置の範囲内の時
	if (CEnemyBullet::GetAdditionPosY() <= -CEnemyBullet::MINUS_ROTY && CEnemyBullet::GetAdditionPosY() >= -CEnemyBullet::MINUS_ROTY+1.0f)
	{
		GetRot().y = -D3DX_PI_ORI;                                                                     //向きを逆に設定
		m_pModelPrtsEnemy[0]->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));                                     //向きの初期化
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY * MULTIPLICATIOB_ADDJUST_BULLET_ROTY);  //弾の出る向きを調整
	}
	else if (CEnemyBullet::GetAdditionPosY() >= CEnemyBullet::MINUS_ROTY * IF_ADDJUST_BULLET_ROTY && CEnemyBullet::GetAdditionPosY() <= CEnemyBullet::MINUS_ROTY * IF_ADDJUST_BULLET_ROTY+1.0f)
	{
		GetRot().y = D3DX_PI_ORI;                                                                      //向きを逆に設定
		m_pModelPrtsEnemy[0]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));                                   //向きの初期化
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::MINUS_ROTY * MULTIPLICATIOB_ADDJUST_BULLET_ROTY);  //弾の出る向きを調整
	}
}