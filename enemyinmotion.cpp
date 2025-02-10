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
	m_nJumpFrame = CObjectX::N_INIT_NUMBER;   //飛ぶまでの時間の初期化
	JumpNumber = CObjectX::N_INIT_NUMBER;     //飛ぶ番号の初期化
	JumpRecastTime = CObjectX::N_INIT_NUMBER; //飛ぶまでのリキャストタイムの初期化
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
		return E_FAIL;                             //失敗を返す
	}

	CEnemyCharacter::LoodEnemy(GetFileName());     //読み込むファイルパスを設定
	//CEnemyCharacter::SetMotionEnemy(ENEMYWALK);  //モーションの初期化

	return S_OK;                                   //成功を返す
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
	//CEnemyCharacter::DrawEnemy(MAX_ENEMYPARTS, 1); //描画処理
}

//==============================
//生成処理
//==============================
CManagerEnemyInMotion* CManagerEnemyInMotion::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CManagerEnemyInMotion* pEnemyInMotion = nullptr; //基底クラスのポインター

	if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		pEnemyInMotion = new CEnemyInMotion001(); //動的確保
		pEnemyInMotion->SetFileName("Enemy001");  //ファイルパスの設定
	}

	//タイプがモーション付きの敵002の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION002)
	{
		pEnemyInMotion = new CEnemyInMotion002(); //動的確保
		pEnemyInMotion->SetFileName("Enemy002");  //ファイルパスの設定
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
//敵001の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion001::CEnemyInMotion001(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetRot(D3DXVECTOR3(0.0f, -D3DX_PI_ORI, 0.0f)); //向きを設定（右向き）
	SetLife(MAX_LIFE);                             //ライフの設定
	m_nHitFrame = CObjectX::N_INIT_NUMBER;         //当たった時にフレームの初期化
	m_bHit = false;                                //当たっていないに設定
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
	if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_1) == true)
	{
		//生きている時
		if (GetLife() > CObjectX::N_INIT_NUMBER)
		{
			CEnemyCharacter::UpdateEnemy001();                                                       //モーションの情報を更新する

			//プレイヤーと当たっている時
			if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_2) == true)
			{
				CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYATTACK);  //モーションの種類を設定

				SetAdjustFrame()++;     //弾を撃つ際のフレームを増やす

				//フレームが規定数に達した時
				if (GetFrame() >= MAX_FRAME)
				{
					//弾の生成
					CManagerBullet::Create(D3DXVECTOR3(
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).x + CREATE_BULLET_PLUS_POS_X,
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).y + CREATE_BULLET_PLUS_POS_Y,
						this->GetPosPartsEnemy(CEnemyCharacter::PARTS_RIGHT_SHOLDER_WEAPON_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED),
						CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::ENEMYBULLET);

					SetFrame(CObjectX::N_INIT_NUMBER); //フレームを０にする
				}

				//プレイヤーが敵に接触したら
				if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_3) == true)
				{
					m_bHit = true; //当たった判定をOnにする
				}
			}

			//プレイヤーと当たってない時
			else
			{
				//向きの初期化
				GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x = CObjectX::F_INIT_NUMBER; //パーツの向きの初期化
				CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y);                                          //弾の向きの初期化

				//飛んでいないとき
				if (GetJumpFlag() == false)
				{
					CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定

					//ジャンプのリキャストタイムが切れた時
					if (m_nJumpFrame == CObjectX::N_INIT_NUMBER)
					{
						TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);           //プレイヤーに向かうように設定
					}
				}
			}

			//プレイヤーが敵に当たった時
			if (m_bHit == true)
			{
				PlayerBloWwaway();                        //プレイヤーの吹き飛び処理を呼ぶ
			}

			Junp(TYPE::ENEMYINMOTION001, MAX_JUMP_POWER); //ジャンプと重力処理関数を呼ぶ
			WhenCollisionBlock();                         //地面用のブロックに触れている時の処理
			CObjectX::Update();                           //move値の更新
		}

		//死んだ時
		else if (GetLife() <= CObjectX::N_INIT_NUMBER)
		{
			Die();                                        //死亡時の処理関数を呼ぶ
		}
	}
}

//===============================================
//死亡時の処理
//===============================================
void CEnemyInMotion001::Die()
{
	SetAdjustDieFrame()++; //死亡フレームを増やす

	//srand((unsigned)time(NULL));  //乱数系列を初期化

	//第一行動
	if (GetDieFrame() <= ATTACKPATTEN1_FRAME_1)
	{
		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, GetPos());
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, GetPos());


		//爆発エフェクトの大きさを設定
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//第二行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_2)
	{

	}

	//第三行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_3)
	{
		SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //乱数の生成

		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//爆発エフェクトの大きさを設定
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//第四行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_4)
	{

	}

	//第五行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_5)
	{
		SetRandom(-MIN_RANDOM1 + rand() % MAX_RANDOM1); //乱数の生成

		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//爆発エフェクトの大きさを設定
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE1, MAX_EXPLOSION_SIZE1, CObjectX::F_INIT_NUMBER);
	}

	//第六行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_6)
	{

	}

	//第七行動
	else if (GetDieFrame() <= ATTACKPATTEN1_FRAME_7)
	{

		SetRandom(-MIN_RANDOM2 + rand() % MAX_RANDOM2); //乱数の生成

		//爆発エフェクトを呼ぶ
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::EXPLOSION001, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(GetPos().x + GetRandom(), GetPos().y + GetRandom(), GetPos().z));


		//爆発エフェクトの大きさを設定
		CManager::GetInstance()->GetExplosion()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, CObjectX::F_INIT_NUMBER);
		CManager::GetInstance()->GetExplosion001()->SetSize(MAX_EXPLOSION_SIZE2, MAX_EXPLOSION_SIZE2, CObjectX::F_INIT_NUMBER);
	}

	//終了
	else
	{
		CManager::GetInstance()->GetGameScore()->AddScore(PLUS_SCORE);  //スコアを加算
		CObjectX::Release();                                            //自身を削除
		return;                                                         //処理を抜ける
	}
}

//===============================================
//プレイヤーが敵に当たった時
//===============================================
void CEnemyInMotion001::PlayerBloWwaway()
{
	m_nHitFrame++;  //当たったフレームを増やす

	//当たった瞬間
	if (m_nHitFrame <= ATTACKPATTEN2_FRAME_1)
	{
		//プレイヤーのHPを削る
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManagerGage::MAX_PLAYER_HP_SIZE * MAX_DAMAGE;
	}

	//第二行動
	else if (m_nHitFrame <= ATTACKPATTEN2_FRAME_2)
	{

		//左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x += PLAYER_MOVE;  //右に移動
		}

		//右向きの時
		else if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			CManager::GetScene()->GetPlayerX()->GetMove().x -= PLAYER_MOVE;  //左に移動
		}
	}

	//終了
	else
	{
		m_nHitFrame = CObjectX::N_INIT_NUMBER; //hitframeを初期化
		m_bHit = false;                        //当たった判定をoffにする
	}
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::AdjustmentBulletAndRot()
{
	//左向きの時
	if (GetRot().y >= D3DX_PI_ORI_HALF)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x += ADJUST_PRTAS_ROTX; //パーツのX軸の向きを加算する
			CEnemyBullet::SetAddjustAdditionPosY() -= ADJUST_BULLET_ROTY;                               //弾のX軸の向きを減算する
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x -= ADJUST_PRTAS_ROTX; //パーツのX軸の向きを減算する
			CEnemyBullet::SetAddjustAdditionPosY() += ADJUST_BULLET_ROTY;                               //弾のX軸の向きを加算する
		}
	}

	//右向きの時
	else if (GetRot().y <= -D3DX_PI_ORI_HALF)
	{
		//プレイヤーの向きが左向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_1)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x -= ADJUST_PRTAS_ROTX; //パーツのX軸の向きを減算する
			CEnemyBullet::SetAddjustAdditionPosY() += ADJUST_BULLET_ROTY;                               //弾のX軸の向きを加算する
		}

		//プレイヤーの向きが右向きの時
		if (CManager::GetScene()->GetPlayerX()->GetRotNumber() == CPlayerX::ROT_NUMBER_2)
		{
			GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->GetRot().x += ADJUST_PRTAS_ROTX; //パーツのX軸の向きを加算する
			CEnemyBullet::SetAddjustAdditionPosY() -= ADJUST_BULLET_ROTY;                               //弾のX軸の向きを減算する
		}
	}

	Correctionrot(); //向きを修正する関数を呼ぶ
}

//===============================================
//プレイヤーに対する機体と弾の調整処理
//===============================================
void CEnemyInMotion001::WhenCollisionBlock()
{
	int nFieldCount = CManager::GetInstance()->GetFieldBlockCount() + 1;              //地面用ブロックの生成数
	int nRoadBlock = CManager::GetInstance()->GetRoadBlockCount() + 1;                //道用ブロックの生成数
	int nWallRoadBlock = CManager::GetInstance()->GetWallRoadBlockCount() + 1;        //壁兼道用ブロックの生成数
	int nWallRoadBlock001 = CManager::GetInstance()->GetWallRoadBlock001Count() + 1;  //壁兼道用ブロック001の生成数

	//地面用のブロックの生成数分回す
	for (int nCount = CObjectX::N_INIT_NUMBER; nCount < nFieldCount; nCount++)
	{
		//敵の最大パーツ数分回す
		for (int nEnemyCount = CObjectX::N_INIT_NUMBER; nEnemyCount < MAX_ENEMYPARTS; nEnemyCount++)
		{
			//地面用ブロックの情報がある時
			if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
			{
				//飛ぶ
				if (JumpNumber == JUMP_NUMBER_MINUS_1)
				{
					//自機と地面用ブロックが当たったら
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * ADJUST_FIELD_BLOCK, GetMove()) == true)
					{
						//リキャストタイムが０以下の時
						if (JumpRecastTime <= CObjectX::N_INIT_NUMBER)
						{
							m_nJumpFrame++;                //飛ぶフレームを増やす

							SetMotionEnemy001(ENEMYJUMP);  //ジャンプモーションの設定

							//ジャンプフレームが規定値より高い時
							if (m_nJumpFrame >= MAX_JUMPFRAME)
							{
								SetJumpFlag(true);                       //飛ぶ
								m_nJumpFrame = CObjectX::N_INIT_NUMBER;  //フレームの初期化
								JumpNumber++;                            //ジャンプナンバーを増やす（次は飛ばないに設定）

								return;                                  //処理を抜ける
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
				else if (JumpNumber == JUMP_NUMBER_0)
				{
					//自機と地面用ブロックが当たったら
					if (GetCollision()->ColiisionBox1(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
					{
						JumpRecastTime = MAX_JUMPRECASTTIME; //リキャストタイムの設定
						JumpNumber = JUMP_NUMBER_MINUS_1;    //ジャンプナンバーの設定（次は飛ぶに設定）
						return;                              //処理を抜ける
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
	for (int nCount2 = CObjectX::N_INIT_NUMBER; nCount2 < nRoadBlock; nCount2++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//当たっている時
			if (GetCollision()->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * ADJUST_BLOCK, GetMove()) == true)
			{

			}

			else
			{
				//上に当たっている時
				if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					GravityTogether();  //重力の同期

					//y軸の位置を設定
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					SetJumpFlag(false); //ジャンプフラグをOff
				}
			}
		}
	}

	//壁兼道用ブロック分回す
	for (int nCount3 = CObjectX::N_INIT_NUMBER; nCount3 < nWallRoadBlock; nCount3++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			//当たっている時
			if (GetCollision()->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize() * ADJUST_BLOCK, GetMove()) == true)
			{

			}

			else
			{
				//上に当たっている時
				if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
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
	for (int nCount4 = CObjectX::N_INIT_NUMBER; nCount4 < nWallRoadBlock001; nCount4++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//上に当たっている時
			if (GetCollision()->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				GravityTogether();  //重力の同期

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
	if (CEnemyBullet::GetAdditionPosY() <= -CEnemyBullet::PLUS_ROT_Y && CEnemyBullet::GetAdditionPosY() >= -CEnemyBullet::PLUS_ROT_Y+ PLUS_ROT_Y)
	{
		//GetRot().y = -D3DX_PI_ORI;  //向きを逆に設定
		SetRot(D3DXVECTOR3(GetRot().x, -D3DX_PI_ORI, GetRot().z));

		//向きの初期化
		GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));

		//弾の出る向きを調整
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y * MULTIPLICATIOB_ADJUST_BULLET_ROTY);   
	}

	else if (CEnemyBullet::GetAdditionPosY() >= CEnemyBullet::PLUS_ROT_Y * IF_ADJUST_BULLET_ROTY && CEnemyBullet::GetAdditionPosY() <= CEnemyBullet::PLUS_ROT_Y * IF_ADJUST_BULLET_ROTY+1.0f)
	{
		//GetRot().y = D3DX_PI_ORI; //向きを逆に設定
		SetRot(D3DXVECTOR3(GetRot().x, D3DX_PI_ORI, GetRot().z));

		//向きの初期化
		GetEnemy001ModelParts(CEnemyCharacter::PARTS_BODY_NUMBER)->SetRot(D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

		//弾の出る向きを調整
		CEnemyBullet::SetAdditionPosY(CEnemyBullet::PLUS_ROT_Y * MULTIPLICATIOB_ADJUST_BULLET_ROTY);
	}
}


//==============================
//描画処理
//==============================
void CEnemyInMotion001::Draw()
{
	CEnemyCharacter::DrawEnemy001(MAX_ENEMYPARTS); //描画処理
}


//====================================================================================================================================
//敵002の処理
//====================================================================================================================================

//=============================
//コンストラクタ
//=============================
CEnemyInMotion002::CEnemyInMotion002(int nPriority) : CManagerEnemyInMotion(nPriority)
{
	SetLife(1);         //ライフの設定
}

//=============================
//デストラクタ
//=============================
CEnemyInMotion002::~CEnemyInMotion002()
{

}

//=============================
//更新処理
//=============================
void CEnemyInMotion002::Update()
{
	//プレイヤーが判定の範囲内に来たら更新処理を実行する
	if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_1) == true)
	{
		//生きている時
		if (GetLife() > CObjectX::N_INIT_NUMBER)
		{
			CEnemyCharacter::UpdateEnemy001();                                                 //モーションの情報を更新する

			//プレイヤーと当たっている時
			if (CObjectX::CollisionPlayerInEnemy(this, COLLISION_RANGE_PLAYER_2) == true)
			{
				CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -=
					CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * DAMAGE;   //HPゲージを減らす
			}

			//当たっていない時
			else
			{
				//CEnemyCharacter::SetMotionEnemy(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYWALK);  //モーションの種類を設定

				TargetHeadingTowards(CManager::GetScene()->GetPlayerX(), MAX_SPEED);            //プレイヤーに向かうように設定
			}

			CObjectX::Update();                                                                 //move値の更新
		}
	}
}

//==============================
//描画処理
//==============================
void CEnemyInMotion002::Draw()
{
	CEnemyCharacter::DrawEnemy002(MAX_ENEMYPARTS); //描画処理
}
