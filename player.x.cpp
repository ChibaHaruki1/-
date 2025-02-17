//===================================
//
//プレイヤーの設定をする処理[player.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "main.h"
#include "player.x.h"
#include "rendererh.h"
#include "manager.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"
#include <time.h>
#include "DxLib.h"


//===================
//コンストラクタ
//===================
CPlayerX::CPlayerX(int nPriority) : CCharacter(nPriority)
{
	SetJumpFlag(false);                                            //飛んでいないに設定
	SetGravity(CObjectX::F_INIT_NUMBER);                           //重力の初期化

	//テキストファイルに登録する時の葉配列番号の初期化
	m_nFiledCount = INIT_NUMBER;                                   //地面の生成数の初期化
	m_nTelephonCount = INIT_NUMBER;                                //電柱の生成数の初期化

	//テキストファイルに登録するした全ての配列番号の初期化
	m_nAllTelephonPoleCount = INIT_NUMBER;
	m_nAllFiledCount = INIT_NUMBER;

	m_ObjectNumber = CObjectX::N_INIT_NUMBER;                      //現在のオブジェクトの番号の初期化
							                              		   
	m_nFrameParticle = CObjectX::N_INIT_NUMBER;                    //パーティクルのフレームの初期化
	m_nPraticlesCount = CObjectX::N_INIT_NUMBER;                   //パーティクルの配列カウントの初期化
	m_nRandomCol = CObjectX::N_INIT_NUMBER;                        //乱数を保管する為の変数
							                              
	m_pMenyu = nullptr;                                            //メニューポインターの初期化
	m_pLaserUI = nullptr;                                          //レーザーUIの初期化
	m_pTalkText = nullptr;                                         //話すUIの初期化
	m_pBuyText = nullptr;                                          //買うテキストの初期化
	m_nSelectShopCount = CObjectX::N_INIT_NUMBER;                  //SHOPで選んでいる物
	m_nBuyOrSendCount = CObjectX::N_INIT_NUMBER;                   //買い物時の選択カウントの初期化
	m_pSelectGage = nullptr;                                       //選択ゲージの初期化
	m_pSelectGage001 = nullptr;                                    //選択ゲージ001の初期化 
	SpecialAttack = false;                                         //必殺技を使っているかどうかの初期化
	m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;           //現在のプレイヤーの状態の設定
	m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;              //現在のフラグの設定
	m_nAlpha = CObjectX::INIT_ALPHA;                               //パーティクルのアルファ値の設定

	m_nMotionFrame = CObjectX::N_INIT_NUMBER;                      //銃を撃つ時のフレームの初期化
	m_nMotionFrame001 = CObjectX::N_INIT_NUMBER;                   //銃001を撃つ時のフレームの初期化
	m_bPlayerMoveNext = false;                                     //次のステージへ行く時のプレイヤーの動きの判定用の変数の初期化
	m_bNextStage = false;                                          //次のステージに行くかどうかの変数の初期化

	//吹っ飛ぶ処理の初期化
	m_nFlayFrame = CObjectX::N_INIT_NUMBER;                        //飛ぶフレームの初期化
	m_bFly = false;                                                //飛んでない

	m_nDieRandom = CObjectX::N_INIT_NUMBER;                        //死亡時の方向乱数の初期化
	m_nRotNumber = CObjectX::N_INIT_NUMBER;                        //向き番号の初期化
	m_nSpecialAttackCount = CObjectX::N_INIT_NUMBER;               //必殺技のカウントの初期化

	m_nNextStageFrame = CObjectX::N_INIT_NUMBER;                   //次のステージに行くまでのフレームの初期化
	m_bLandingFlag = false;                                        //着地してない
	m_nLandingFrame = CObjectX::N_INIT_NUMBER;                     //着地時の次の動きへのフレームの初期化

	m_pNowCreateUI = CManager2DUI::Create(CObject::TYPE_UI::NOWCREATE); //現在の配置オブジェクトのUIの生成

	//生成数の保管用変数の初期化
	m_nFieldBlock = CObjectX::N_INIT_NUMBER;
	m_nGoUpBlock = CObjectX::N_INIT_NUMBER;
	m_nRoadBlock = CObjectX::N_INIT_NUMBER;
	m_nWallRoadBlock = CObjectX::N_INIT_NUMBER;
	m_nWallRoadBlock001 = CObjectX::N_INIT_NUMBER;
	m_nSmalBlock = CObjectX::N_INIT_NUMBER;
	m_nLaserCount = CObjectX::N_INIT_NUMBER;
	m_nSmalBlock001 = CObjectX::N_INIT_NUMBER;
}


//===================
//デストラクタ
//===================
CPlayerX::~CPlayerX()
{
	//mciSendStringA("close BGM", NULL, CObjectX::N_INIT_NUMBER, NULL);
}


//====================
//初期化処理
//====================
HRESULT CPlayerX::Init()
{
	CCharacter::Init();                                                                             //初期化処理を呼ぶ
	CCharacter::Lood();                                                                             //テキストファイルを読み込む処理
	SetRot(D3DXVECTOR3(CObjectX::F_INIT_NUMBER, -CObjectX::D3DX_PI_ORI, CObjectX::F_INIT_NUMBER));  //向きの調整（右向き）
	SetPos(D3DXVECTOR3(CObjectX::F_INIT_NUMBER,CObjectX::F_INIT_NUMBER,CObjectX::F_INIT_NUMBER));   //位置の調整
	SetLife(LIFE);                                                                                  //自身のライフ
	m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(false);                                       //パーツの銃部分を非表示に設定
	return S_OK;                                                                                    //成功を返す
}

//==================
//終了処理
//=================
void CPlayerX::Uninit()
{
	//instance情報を消す
	InstanceMakeNull();

	CCharacter::Uninit(); //パーツごとの破棄処理
}

//===============================================================================================================================================================================
//instanceをnullptrにする
//===============================================================================================================================================================================
void CPlayerX::InstanceMakeNull()
{
	m_pTalkText = nullptr;      //話すテキストの情報を無くす
						        
	m_pMenyu = nullptr;         //武器の選択メニューの情報を無くす
						        
	m_pBuyText = nullptr;       //買う売るテキストの情報を無くす
							    
	m_pSelectGage = nullptr;    //選択ゲージの情報を無くす

	m_pSelectGage001 = nullptr; //選択ゲージ001の情報をなくす
}

//=======================================
//ショップ時のポインターの初期化
//=======================================
void CPlayerX::ShopInstanceMakeNullptr()
{
	//選択ゲージの情報がある時
	if (m_pSelectGage != nullptr)
	{
		m_pSelectGage->Release();    //情報を消す
		m_pSelectGage = nullptr;     //情報を無くす
	}

	//選択ゲージ001の情報がある時
	if (m_pSelectGage001 != nullptr)
	{
		m_pSelectGage001->Release(); //情報を消す
		m_pSelectGage001 = nullptr;  //情報を無くす
	}

	//買うテキストの情報がある時
	if (m_pBuyText != nullptr)
	{
		m_pBuyText->Release();       //情報を消す
		m_pBuyText = nullptr;        //情報を無くす
	}

	//メニューの情報がある時
	if (m_pMenyu != nullptr)
	{
		m_pMenyu->Release();         //情報を消す
		m_pMenyu = nullptr;          //情報を無くす
	}

	//ショップ時の背景の情報がある時
	if (CManager::GetInstance()->GetShopScreen() != nullptr)
	{
		CManager::GetInstance()->GetShopScreen()->Release();                   //情報を消す
		CManager::GetInstance()->DesignationUninit2D(CObject2D::TYPE::SCREEN); //情報を無くす
	}

	m_nSelectShopCount = N_INIT_NUMBER;
}


//===============================================================================================================================================================================
//更新処理
//===============================================================================================================================================================================
void CPlayerX::Update()
{
	//生きている時
	if (GetLife() == LIFE)
	{
		CCharacter::UpdatePlayer();           //モーションの更新

		if (GetPos().y <= -DIE_POS_Y)
		{
			SetLife(CObjectX::N_INIT_NUMBER); //ライフの初期化
		}

		//重力値が規定値より高い時
		if (GetGravity() >= MAX_GRAVITY)
		{
			GetGravity() = MAX_GRAVITY;       //重力の設定
		}

		//遊べる状態になっている時
		if (CManager::GetScene()->GetPlay() == true)
		{
			HitAttack();                      //特定の攻撃を受けた時の処理関数を呼ぶ

			//必殺技カウントが規定値より低い時
			if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
			{
				m_nSpecialAttackCount++;      //カウントを進める
			}

			//ゲージのmanagerが生成されていた時
			if (CManager::GetInstance()->GetPlayerHPGage() != nullptr)
			{
				//HPゲージが０以下の時
				if (CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() <= CObjectX::N_INIT_NUMBER)
				{
					CManager::GetInstance()->GetPlayerHPGage()->GetSaveSizeX() = CObjectX::F_INIT_NUMBER;  //HPゲージのサイズを０にする
					SetLife(CObjectX::N_INIT_NUMBER);                                                      //ライフを０に設定で死亡判定にする
				}
			}

			//何もしていない時
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				NormalStateSummarizeFunction(); //専用の処理を呼ぶ
			}

			//SHOPで買い物をしている時
			else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE || m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
			{
				ShopStateSummarizeFunction();   //専用の処理を呼ぶ
			}

			//次のステージへ行くときのプレーヤーの動きがOnの時
			if (m_bPlayerMoveNext == true)
			{
				//SceneMode(1); //sceneの切り替え
				//return;		  //処理を抜ける
				NextStageMotion();
			}

			//次のsceneに行くフラグがOnの時
			if (m_bNextStage == true)
			{
				SceneMode(SCENE_NEXT_STAGE); //sceneの切り替え
				return;		                 //処理を抜ける
			}

			CObjectX::Update();              //基底クラスの基底クラスの更新処理を呼ぶ
		}

		//着地までに必要な処理
		else
		{
			BlockJudgement();                   //地面に触れる事でようやく移動などができるようにするためブロックの当たり判定処理を呼ぶ
			Junp(TYPE::PLAYER, MAX_JUMPPAWER);  //重力処理関数を呼ぶ事で落ちるようにする
		}
	}

	//死んだ時
	else if (GetLife() == CObjectX::N_INIT_NUMBER)
	{
		SetAdjustDieFrame()++;          //死亡フレームを増やす
		//GetPos().y = -50.0f;          //位置を低くする
		srand((unsigned)time(NULL));    //乱数系列を初期化

		//乱数が入ってない時
		if (m_nDieRandom == CObjectX::N_INIT_NUMBER)
		{
			m_nDieRandom = MIN_DIE_RANDOM + rand() % MAX_DIE_RANDOM; //乱数を入れる
		}

		//体の位置を設定
		m_pModelPrts[PLAYER_PARTS_BODY_NUMBER]->GetPos() += D3DXVECTOR3(GetDieFrame() * DIE_FRAME_REDUCTION * m_nDieRandom, CObjectX::F_INIT_NUMBER, GetDieFrame() * DIE_FRAME_REDUCTION * m_nDieRandom);

		CCharacter::Update();  //基底クラスの更新処理を呼ぶ
		SetMotion(DIE);        //モーションを死亡に設定する

		//既定の数値
		if (GetDieFrame() >= MAX_DIE_COUNT)
		{
			SceneMode(SCENE_DIE_STAGE); //シーンの設定
			return;                     //処理を抜ける
		}
	}
	//SceneMode(SCENE_DEBUG_STAGE);         //シーンを選択
}


//==================================================================================================================================================
//吹っ飛び処理
//==================================================================================================================================================
void CPlayerX::BlowAway()
{
	m_nFlayFrame++;                  //飛ぶフレームを進める

	CCharacter::SetMotion(BLOWAWAY); //ぶっ飛びモーションの設定

	//第一行動
	if (m_nFlayFrame <= BLOWAWAY_FRAME_1)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_X; //X軸の位置を増やす
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_Y; //Y軸の位置を増やす
	}

	//第二行動
	else if (m_nFlayFrame <= BLOWAWAY_FRAME_2)
	{
		CManager::GetScene()->GetPlayerX()->GetPos().y += BLOWAWAY_PLUS_POS_X-10.0f; //X軸の位置を増やす
		CManager::GetScene()->GetPlayerX()->GetPos().x += BLOWAWAY_PLUS_POS_Y-10.0f; //Y軸の位置を増やす
	}

	//終了
	else
	{
		m_bFly = false;                         //飛ぶフラグをOffにする
		m_nFlayFrame = CObjectX::N_INIT_NUMBER; //飛ぶフレームの初期化
	}
}


//==================================================================================================================================================
//特定の攻撃を受けた時の処理
//==================================================================================================================================================
void CPlayerX::HitAttack()
{
	//衝撃破エフェクトのインスタンス情報がある時
	if (CManager::GetInstance()->GetImpact() != nullptr)
	{
		//当たったフラグがONの時
		if (CManager::GetInstance()->GetImpact()->GetHitNumber() == CObjectX::N_INIT_NUMBER)
		{
			m_bFly = true; //飛ぶ
		}
	}

	//飛ぶフラグがONの時
	if (m_bFly == true)
	{
		BlowAway();       //吹っ飛び処理を呼ぶ
	}
}


//==================================================================================================================================================
//次のscene処理
//==================================================================================================================================================
void CPlayerX::SceneMode(int nType)
{
	//次のステージに行く用（ゲームループ）
	if (nType == SCENE_NEXT_STAGE)
	{
		m_bNextStage = false; //次のステージのフラグをOffにする

		//現在のシーンから参照
		switch (CManager::GetScene()->GetMode())
		{
			//ステージ１の時
		case CScene::MODE::MODE_GAME01:
			CManager::SetMode(CScene::MODE::MODE_GAME02); //ステージ２に遷移
			return;                                       //処理を抜ける

			//ステージ２の時
		case CScene::MODE::MODE_GAME02:
			CManager::SetMode(CScene::MODE::MODE_RESULT); //リザルトに遷移
			return;                                       //処理を抜ける
		}
	}

	//デバック用
	else if (nType == SCENE_DEBUG_STAGE)
	{
		//Enterキーが押された時（デバック用）
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_I) == true)
		{
			m_bNextStage = false; //次のステージのフラグをOffにする

			//現在のシーンから参照
			switch (CManager::GetScene()->GetMode())
			{
				//ステージ１の時
			case CScene::MODE::MODE_GAME01:
				CManager::SetMode(CScene::MODE::MODE_GAME02); //ステージ２に遷移
				return;                                       //処理を抜ける

				//ステージ２の時
			case CScene::MODE::MODE_GAME02:
				CManager::SetMode(CScene::MODE::MODE_RESULT); //リザルトに遷移
				return;                                       //処理を抜ける

				//ステージ３の時
			case CScene::MODE::MODE_RESULT:
				CManager::SetMode(CScene::MODE::MODE_GAME01); //ステージ１に遷移
				return;                                       //処理を抜ける
			}
		}
	}

	//死亡した時用
	else if (nType == SCENE_DIE_STAGE)
	{
		m_bNextStage = false;                                 //次のステージのフラグをOffにする
		CManager::SetMode(CScene::MODE::MODE_GAMEOVER);       //ゲームオーバーに遷移
		return;                                               //処理を抜ける
	}
}


//===============================================================================================================================================================================
//通常状態時の関数をまとめる関数処理
//===============================================================================================================================================================================
void CPlayerX::NormalStateSummarizeFunction()
{
	//必殺技のカウントが規定値より高い時
	if (m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
	{
		Praticles();               //パーティクルの生成処理関数を呼ぶ

		//必殺技もカウントが規定値より低い時
		if (m_nSpecialAttackCount <= MAX_SPECIALATTACKCOUNT)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHARGE); //BDMを流す
		}
	}
	BlockJudgement();              //オブジェクトとの当たり判定処理関数を呼ぶ
	UIJudgement();                 //UIとの当たり判定処理関数を呼ぶ

	NowCreateNumberObj();          //配置オブジェクトのUIを生成する処理関数
	NowCreateObjectUI();           //現在作っているオブジェクトのUIを出す処理

	//必殺技を撃っていない時
	if (SpecialAttack == false)
	{
		KeySet();                  //キーごとの処理関数を呼ぶ
	}
	else
	{
		//銃を撃つフレームが０以上の時
		if (m_nMotionFrame >= CObjectX::N_INIT_NUMBER)
		{
			m_nMotionFrame--;      //フレームを増やす
		}

		//銃を撃つフレーム001が０以上の時
		if (m_nMotionFrame001 >= CObjectX::N_INIT_NUMBER)
		{
			m_nMotionFrame001--;   //フレームを増やす
		}

		//両方のフレームが０以下の時
		else if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			SpecialAttack = false;     //必殺技フラグをOffにする
		}
	}
	Junp(TYPE::PLAYER, MAX_JUMPPAWER); //ジャンプと重力処理関数を呼ぶ
}


//===============================================================================================================================================================================
//買い物時の関数をまとめる関数処理
//===============================================================================================================================================================================
void CPlayerX::ShopStateSummarizeFunction()
{
	BlockJudgement();        //ブロックとの当たり判定処理関数
	ShopKeySet();            //キーごとの処理
}


//===============================================================================================================================================================================
//ランダム処理
//===============================================================================================================================================================================
void CPlayerX::Random()
{
	//最小値＋rand()%最小値から何個分増やすか　（５だったら％６だったら　５、６、７、８、９、１０の合計６個になる）
	//srand((unsigned)time(NULL));  //乱数系列を初期化
	SetRandom(MIN_RANDOM + rand() % MAX_RANDOM);  //（範囲指定）
	m_nRandomCol = rand() % MAX_COL_RANDOM;       //（範囲指定）
}


//===============================================================================================================================================================================
//パーティクルを出す処理
//===============================================================================================================================================================================
void CPlayerX::Praticles()
{
	Random();             //ランダム処理を呼ぶ
	m_nFrameParticle++;   //フレームを加算させていく

	//フレームが既定の数値まで行った時
	if (m_nFrameParticle >= MAX_PARTICLE_FRAME)
	{
		m_nFrameParticle = CObjectX::N_INIT_NUMBER; //フレームを初期化する

		////配列の最大数か最大数より下分回す
		//if (m_nPraticlesCount >= 0 && m_nPraticlesCount <= CInstance::MAX_OBJECT_DATA - 1)
		//{
		//	//パーティクルの生成
		//	CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPos().y+50.0f, CObjectX::F_INIT_NUMBER)); //パーティクルの生成処理
		//	CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, 0, 0, m_nAlpha);//色の設定
		//	m_nPraticlesCount++; //配列を進める
		//}

		////最大数に突入
		//else
		//{
		//	m_nPraticlesCount = 0; //配列カウントを初期化する
		//}

		//パーティクルの生成処理
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::PRTICLES001, m_nPraticlesCount, D3DXVECTOR3((float)GetPos().x + GetRandom(), GetPosParts(PLAYER_PARTS_BODY_NUMBER).y, CObjectX::F_INIT_NUMBER)); 

		//色の設定
		CManager::GetInstance()->GetPraticles001(m_nPraticlesCount)->SetCol(m_nRandomCol, CObjectX::N_INIT_NUMBER, CObjectX::N_INIT_NUMBER, m_nAlpha);
	}
}


//===============================================================================================================================================================================
//キーごとの処理をまとめる関数
//===============================================================================================================================================================================
void CPlayerX::KeySet()
{

	//=================================================
	//必殺技の発動
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_K) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_RB) == true)
	{
		//武器が買われた時と必殺技カウントが規定値より高い時
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == true && m_nSpecialAttackCount >= MAX_SPECIALATTACKCOUNT)
		{
			SpecialAttack = true;                             //必殺技フラグをOnにする  
			m_nSpecialAttackCount = CObjectX::N_INIT_NUMBER;  //必殺技カウントの初期化

			//右向きの時
			if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
			{
				//必殺技のエフェクトの生成
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

				m_nMotionFrame = CManager::GetInstance()->GetSpecialAttack()->GetLife();                    //モーションのライフを同期させる
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = CSpecialAttack::ROT_NUMBER_1; //サイズの設定用の番号を渡す

				 //エフェクトの出す位置を設定
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + ROT_NUMBER_1_SPECIAL_EFFECT_PLUS_POS_Y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).z));
			}

			//左向きの時
			else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
			{
				//必殺技のエフェクトの生成
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::SPECIALATTACK, CObjectX::N_INIT_NUMBER, D3DXVECTOR3(CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER));

				m_nMotionFrame001 = CManager::GetInstance()->GetSpecialAttack()->GetLife();                 //モーションのライフを同期させる
				CManager::GetInstance()->GetSpecialAttack()->GetRotNumber() = CSpecialAttack::ROT_NUMBER_2; //サイズの設定用の番号を渡す

				  //エフェクトの出す位置を設定
				CManager::GetInstance()->GetSpecialAttack()->SetEffect(D3DXVECTOR3(
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + ROT_NUMBER_2_SPECIAL_EFFECT_MINUS_POS_Y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).y,
					GetPosParts(PLAYER_PARTS_GUN_NUMBER).z));
			}
		}
	}

	//=================================================
	//Aキーが押された時（押され続けた時）
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_LEFT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI;                               //カメラの向きに合わせて向く
		SetAdjustMove().x -= sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X軸の移動量をカメラの向きから減算
		SetAdjustMove().z -= cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z軸の移動量をカメラの向きから減算
		m_nRotNumber = ROT_NUMBER_1;                                                                            //向き番号の設定

		//撃ってない時
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //歩きモーション
		}
	}

	//=================================================
	//Dキーが押された時（押され続けた時）
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_RIGHT) == true)
	{
		GetRot().y = CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI;                         //カメラの向きに合わせて向く
		GetMove().x += sinf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //X軸の移動量をカメラの向きから加算
		GetMove().z += cosf(D3DX_PI_ORI + CManager::GetScene()->GetCamera()->GetRot().y) * MAX_MOVESPEED; //Z軸の移動量をカメラの向きから加算
		m_nRotNumber = ROT_NUMBER_2;                                                                      //向き番号の設定

		//撃ってない時
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER)
		{
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::WALK); //歩きモーション
		}
	}

	//=================================================
	//その他
	else
	{
		//撃ってない時と吹っ飛んでない時
		if (m_nMotionFrame <= CObjectX::N_INIT_NUMBER && m_nMotionFrame001 <= CObjectX::N_INIT_NUMBER && m_bFly == false)
		{
			SpecialAttack = false;                                   //必殺技フラグをOffにする  
			CCharacter::SetMotion(CCharacter::MOTIONSTATE::NEUTRAL); //待機モーション
		}
	}

	//=================================================
	//spaceキーを押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_SPACE) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SHOT); //BDMを流す

		//右向きの時
		if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y - D3DX_PI_ORI)
		{
			m_nMotionFrame = GUN_FRAME_MOTION;    //銃を撃つフレームを設定

			//弾の設定
			CManagerBullet::Create(D3DXVECTOR3(GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + RIGHT_BULLET_PLUS_POS_X, GetPosParts(PLAYER_PARTS_GUN_NUMBER).y, GetPosParts(PLAYER_PARTS_GUN_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, CObjectX::F_INIT_NUMBER), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //正面
		}

		//左向きの時
		else if (GetRot().y == CManager::GetScene()->GetCamera()->GetRot().y + D3DX_PI_ORI)
		{
			m_nMotionFrame001 = GUN_FRAME_MOTION; //銃を撃つフレームを設定

			//弾の設定
			CManagerBullet::Create(D3DXVECTOR3(GetPosParts(PLAYER_PARTS_GUN_NUMBER).x + LEFT_BULLET_MINUS_POS_X, GetPosParts(PLAYER_PARTS_GUN_NUMBER).y, GetPosParts(PLAYER_PARTS_GUN_NUMBER).z), D3DXVECTOR3(-sinf(GetRot().y) * MAX_BUULET_SPEED, CObjectX::F_INIT_NUMBER, -cosf(GetRot().y) * MAX_BUULET_SPEED), CManagerBullet::SET_BULLET_LIFE, CObject3D::TYPE::BULLET); //正面
		}
	}

	//=================================================
	//XキーかAボタンが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_X) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetJumpFlag(true);                                       //飛んでいるに設定
	}

	//=================================================
	//キーが押されてなく、ジャンプをしている時
	else if (GetJumpFlag() == true)
	{
		//燃料ゲージの情報がある時
		if (CManager::GetInstance()->GetFuelGage() != nullptr)
		{
			//Xキーが押された時かJoyキーのAキーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_X) == true || CManager::GetJyoPad()->GetJoypadPress(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
			{
				//チャージが完了している時
				if (CManager::GetInstance()->GetFuelGage()->GetChage() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = true;   //燃料ゲージを使っているに設定
				}
			}
			else
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false;  //燃料ゲージを使っていないに設定
				SetGravityFlag(true);                                      //重力ON
			}
		}
	}

	//=================================================
	//右側の銃に関するフレームの処理
	if (m_nMotionFrame >= CObjectX::N_INIT_NUMBER)
	{
		m_nMotionFrame--;                            //銃を撃つフレームを減らす
		SetMotion(CCharacter::MOTIONSTATE::ACTION);  //撃つアクションの設定
	}

	//=================================================
	//左側の銃に関するフレーム処理
	if (m_nMotionFrame001 >= CObjectX::N_INIT_NUMBER)
	{
		m_nMotionFrame001--;                          //銃を撃つフレーム001を減らす
		SetMotion(CCharacter::MOTIONSTATE::ACTION);	  //撃つアクションの設定
	}
}


//===============================================================================================================================================================================
//ショップ時のキーごとの処理をまとめる関数
//===============================================================================================================================================================================
void CPlayerX::ShopKeySet()
{
	//=======================================================================================================================================================
	//通常状態の時
	//=======================================================================================================================================================
	if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
	{
		//F1キーかJoyキーのＹキーが押された時
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			//選択ゲージ１つ目を生成する
			if (m_pSelectGage == nullptr)
			{
				m_pSelectGage = CSelectGage::Create(); //選択ゲージの生成
			}

			//選択ゲージ二つ目を生成する
			if (m_pSelectGage001 == nullptr)
			{
				m_pSelectGage001 = CSelectGage001::Create(); //選択ゲージ001の生成

				//選択ゲージ001の大きさを設定
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y()); //一つ目のゲージの大きさに合わせる
			}

			//背景UIを生成する
			if (CManager::GetInstance()->GetShopScreen() == nullptr)
			{
				CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCREEN, N_INIT_NUMBER); //背景の生成
			}

			//買うか売るかのUIを生成する
			if (m_pBuyText == nullptr)
			{
				m_pBuyText = CBuyText::Create(); //買うテキストの生成
			}

			m_PlayerState = CPlayerX::PLAYER_STATE::SHOP_MODE; //モードを変更する
		}
	}

	//=======================================================================================================================================================
	//SHOP状態の時
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::SHOP_MODE)
	{
		//フラグ状態が通常時の時
		if (m_FlagSate == CPlayerX::PLAYER_STATE::NORMAI_MODE)
		{
			SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP1_SELECT_GAGE_SIXE2_X); //選択ゲージ1つ目の大きさを設定する
			m_FlagSate = CPlayerX::PLAYER_STATE::SHOP_MODE;                                  //フラグ状態を店の状態へ変化させる
		}

		//買うを選択したとき（０からスタートもしくは０に戻る）
		if (m_nBuyOrSendCount == CObjectX::N_INIT_NUMBER)
		{
			//Enterキーを押した時かJoyキーのＢキーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
			{
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP2_SELECT_GAGE_SIXE2_X); //大きさを設定
				m_PlayerState = CPlayerX::PLAYER_STATE::BUY_MODE;                                //モードを買うモードに設定
			}
		}

		//Sキーが押された時かJoyキー下キーが押された時
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			SelectGageUISizeCalculation("Plus", MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X); //サイズを調整する
			m_nBuyOrSendCount++;                                                                                       //カウントを進める

			//選択外の数値になった時
			if (m_nBuyOrSendCount == MODE_SHOP_DOWN_COUNT)
			{
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP1_SELECT_GAGE_SIXE2_X); //大きさを戻す
				m_nBuyOrSendCount = MODE_SHOP_DOWN_COUNT-MODE_SHOP_SELECT_COUNT;                           //カウントを初期化する

			}
		}

		//Wキーが押された時かJoyキーの上キーが押された時
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			SelectGageUISizeCalculation("Minus", MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X); //サイズを調整する
			m_nBuyOrSendCount--;                                                                                        //カウントを減らす

			//選択外の数値になった時
			if (m_nBuyOrSendCount == MODE_SHOP_UP_COUNT)
			{
				//サイズを調整
				SelectGageUISize(MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X+ MODE_SHOP_SELECT_GAGE_SIXE1_X, MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X+ MODE_SHOP1_SELECT_GAGE_SIXE2_X); 

				m_nBuyOrSendCount = MODE_SHOP_UP_COUNT+MODE_SHOP_SELECT_COUNT; //カウントを初期化する

			}
		}

		//キーが押された時
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;  //プレイヤーの状態を通常状態に設定
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;     //フラグ状態を通常の状態に設定
		}
	}

	//=======================================================================================================================================================
	//買う状態の時
	//=======================================================================================================================================================
	else if (m_PlayerState == CPlayerX::PLAYER_STATE::BUY_MODE)
	{
		//買うか売るかのUIを破棄する
		if (m_pBuyText != nullptr)
		{
			m_pBuyText->Release(); //情報を消す
			m_pBuyText = nullptr;  //情報を無くす
			return;                //処理を抜ける
		}

		//メニューを生成する
		if (m_pMenyu == nullptr)
		{
			m_pMenyu = CManager2DUI::Create(CObject::TYPE_UI::SHOPMENU); //メニューの生成
		}

		//F1キーが押された時かJoyキーのＡキーが押された時
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_F1) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_Y) == true)
		{
			ShopInstanceMakeNullptr();                             //ポインターの初期化処理関数を呼ぶ
			m_PlayerState = CPlayerX::PLAYER_STATE::NORMAI_MODE;   //プレイヤーの状態を通常状態に設定
			m_FlagSate = CPlayerX::PLAYER_STATE::NORMAI_MODE;      //フラグ状態を通常の状態に設定
		}

		//Sキーを押したとき
		if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_S) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_DOWN) == true)
		{
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Plus", ADJUST_SELECT_SIZEY, ADJUST_SELECT_SIZEY); //サイズを調整する

				//選択ゲージ001の大きさを設定
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount ++; //選択カウントを増やす

				//選択カウントが既定の値になった時
				if (m_nSelectShopCount >= MODE_BUY_DOWN_COUNT)
				{
					m_pSelectGage->GetSizeY() = MODE_BUY_SELECT_GAGE_SIXE1_Y;   //選択ゲージの１つ目のY軸の大きさを設定
					m_pSelectGage->GetSize1Y() = MODE_BUY_SELECT_GAGE_SIXE2_Y;  //選択ゲージの２つ目のY軸の大きさを設定

					//選択ゲージ001の大きさを設定
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = MODE_BUY_DOWN_COUNT - MODE_BUY_SELECT_COUNT; //選択カウントの初期化
				}
			}
		}

		//Wキーを押したとき
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_W) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_UP) == true)
		{
			//選択ゲージの情報がある時
			if (m_pSelectGage != nullptr)
			{
				SelectGageUISizeCalculation("Minus", ADJUST_SELECT_SIZEY, ADJUST_SELECT_SIZEY); //サイズを調整する

				//選択ゲージ001のサイズを調整
				m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
				m_nSelectShopCount --; //選択カウントを引く

				//選択カウントが既定の値の時
				if (m_nSelectShopCount == MODE_BUY_UP_COUNT)
				{
					int nCount = MODE_BUY_UP_COUNT + MODE_BUY_SELECT_COUNT;                        //項目数の設定（全体の項目数ー規定値）

					 //サイズの設定（あらかじめ設定したサイズ＋調整値*回数）
					float fSizeY = MODE_BUY_SELECT_GAGE_SIXE1_Y + ADJUST_SELECT_SIZEY * nCount;   
					float fSize1Y = MODE_BUY_SELECT_GAGE_SIXE2_Y + ADJUST_SELECT_SIZEY * nCount;

					m_pSelectGage->GetSizeY() = fSizeY;   //選択ゲージの１つ目のY軸の大きさを設定
					m_pSelectGage->GetSize1Y() = fSize1Y; //選択ゲージの２つ目のY軸の大きさを設定

					//選択ゲージ001のサイズを調整
					m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
					m_nSelectShopCount = nCount;         //選択カウントを設定
				}
			}
		}

		//Enterキーを押した時かJoyキーのBキーが押された時
		else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_B) == true)
		{
			CreateGun(); //銃の生成処理関数を呼ぶ
		}
	}
}


//===============================================================================================================================================================================
//選択ゲージのUIのサイズを設定する処理
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISize(float fSIzeX,float fSIze1X)
{
	m_pSelectGage->GetSizeY() = fSIzeX;   //選択ゲージの１つ目のY軸の大きさを引数と同期させる
	m_pSelectGage->GetSize1Y() = fSIze1X; //選択ゲージの２つ目のY軸の大きさを引数と同期させる

	//選択ゲージ２つ目の大きさを同期させる
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}

//===============================================================================================================================================================================
//選択ゲージのUIのサイズを設定する処理
//===============================================================================================================================================================================
void CPlayerX::SelectGageUISizeCalculation(const char* aSelect,float fSIzeX, float fSIze1X)
{
	//文字列で判別
	if (aSelect == "Plus")
	{
		m_pSelectGage->SetAddjustSizeY() += fSIzeX;    //選択ゲージの１つ目のY軸の大きさを引数と同期させ加算する
		m_pSelectGage->SetAddjustSize1Y() += fSIze1X;  //選択ゲージの２つ目のY軸の大きさを引数と同期させ加算する
	}
	else if (aSelect == "Minus")
	{
		m_pSelectGage->SetAddjustSizeY() -= fSIzeX;    //選択ゲージの１つ目のY軸の大きさを引数と同期させ減算する
		m_pSelectGage->SetAddjustSize1Y() -= fSIze1X;  //選択ゲージの２つ目のY軸の大きさを引数と同期させ減算する
	}

	//選択ゲージ２つ目の大きさを設定
	m_pSelectGage001->SetSIze(m_pSelectGage->GetSizeX(), m_pSelectGage->GetSize1X(), m_pSelectGage->GetSizeY(), m_pSelectGage->GetSize1Y());
}


//===============================================================================================================================================================================
//武器生成処理
//===============================================================================================================================================================================
void CPlayerX::CreateGun()
{
	//一番目の武器が選ばれた時
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_0)
	{
		//銃が描画されていない時
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //描画する
		}
	}

	//二番目の武器が選ばれた時
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_1)
	{
		//銃が描画されていない時
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //描画する
		}
	}

	//三番目の武器が選ばれた時
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_2)
	{
		//銃が描画されていない時
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //描画する
		}
	}

	//四番目の武器が選ばれた時
	if (m_nSelectShopCount == CREATE_GUN_NUMBER_3)
	{
		//銃が描画されていない時
		if (m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->GetDraw() == false)
		{
			m_pModelPrts[PLAYER_PARTS_GUN001_NUMBER]->SetDraw(true); //描画する
		}
	}

}

//===============================================================================================================================================================================
//描画処理
//===============================================================================================================================================================================
void CPlayerX::Draw()
{
	CCharacter::DrawPlayer(MAX_PARTS); //パーツごとの描画処理
}

//===============================================================================================================================================================================
//ブロックの当たり判定
//===============================================================================================================================================================================
void CPlayerX::BlockJudgement()
{
	int nInitNumber = CObjectX::N_INIT_NUMBER; //初期値

	//=================================
	//地面用のブロックの生成数分回す
	for (int nCount = nInitNumber; nCount < m_nFieldBlock; nCount++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetFiledBlock(nCount) != nullptr)
		{
			//当たり判定
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize() * 1.05f, GetMove()) == true)
			{

			}
			else
			{
				//上に乗っている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFiledBlock(nCount)->GetPos(), GetModelSize(), CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize(), GetMove()) == true)
				{
					//燃料ゲージが使われている時
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
					}

					GravityTogether(); //重力の同期

					//位置の同期
					GetPos().y = CManager::GetInstance()->GetFiledBlock(nCount)->GetModelSize().y + CManager::GetInstance()->GetFiledBlock(nCount)->GetPos().y;

					//飛んでいる
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}

					//着地していない時
					if (m_bLandingFlag == false)
					{
						m_nLandingFrame++; //着地フレームを設定

						SetMotion(MOTIONSTATE::LANDING); //着地モーションの設定

						//着地フレームが規定値より高い時
						if (m_nLandingFrame >= MAX_LANDING_FRAME)
						{
							m_bLandingFlag = true;                     //着地しているに設定
							m_nLandingFrame = CObjectX::N_INIT_NUMBER; //着地フレームの初期化
							CManager::GetScene()->SetPlay(true);       //遊べるに設定
						}
					}
				}
			}
		}
	}

	//=================================
	//上がる用のブロックの生成数分回す
	for (int nCount1 = nInitNumber; nCount1 < m_nGoUpBlock; nCount1++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetGoUpBlock(nCount1) != nullptr)
		{
			//当たり判定
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//上に乗っている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos(), GetModelSize(), CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize(), GetMove()) == true)
				{
					//燃料ゲージが使われている時
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
					}

					GravityTogether(); //重力の同期

					//位置の同期
					GetPos().y = CManager::GetInstance()->GetGoUpBlock(nCount1)->GetModelSize().y + CManager::GetInstance()->GetGoUpBlock(nCount1)->GetPos().y;

					//飛んでいる
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//=================================
	//道用ブロック分回す
	for (int nCount2 = nInitNumber; nCount2 < m_nRoadBlock; nCount2++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetRoadBlock(nCount2) != nullptr)
		{
			//当たり判定
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize() * 1.1f, GetMove()) == true)
			{

			}
			else
			{
				//上に乗っている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos(), GetModelSize(), CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize(), GetMove()) == true)
				{
					//燃料ゲージが使われている時
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
					}

					GravityTogether();//重力の同期

					//位置の同期
					GetPos().y = CManager::GetInstance()->GetRoadBlock(nCount2)->GetModelSize().y + CManager::GetInstance()->GetRoadBlock(nCount2)->GetPos().y;

					//飛んでいる
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//=================================
	//壁兼道用ブロック分回す
	for (int nCount3 = nInitNumber; nCount3 < m_nWallRoadBlock; nCount3++)
	{
		if (CManager::GetInstance()->GetWallRoadBlock(nCount3) != nullptr)
		{
			if (GetCollision() ->ColiisionBoxRoadBlock001(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
			{

			}
			else
			{
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize(), GetMove()) == true)
				{
					//燃料ゲージが使われている時
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
					}

					GravityTogether(); //重力の同期

					//位置の同期
					GetPos().y = CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock(nCount3)->GetPos().y;

					//飛んでいる
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//=================================
	//壁兼道001用ブロック分回す
	for (int nCount4 = nInitNumber; nCount4 < m_nWallRoadBlock001; nCount4++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock001(nCount4) != nullptr)
		{
			//上に乗っている時
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos(), GetModelSize(), CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize(), GetMove()) == true)
			{
				//燃料ゲージが使われている時
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
				}

				GravityTogether(); //重力の同期

				//位置の同期
				GetPos().y = CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetModelSize().y + CManager::GetInstance()->GetWallRoadBlock001(nCount4)->GetPos().y;

				//飛んでいる
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //飛んでいないに設定
				}
			}
		}
	}

	//=================================
	//小さいブロック分回す
	for (int nCount5 = nInitNumber; nCount5 < m_nSmalBlock; nCount5++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetSmallBlock(nCount5) != nullptr)
		{
			if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize() * 1.3f, GetMove()) == true)
			{

			}
			else
			{
				//上に乗っている時
				if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize(), GetMove()) == true)
				{
					//燃料ゲージが使われている時
					if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
					{
						CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
					}

					GravityTogether(); //重力の同期

					//位置の同期
					GetPos().y = CManager::GetInstance()->GetSmallBlock(nCount5)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock(nCount5)->GetPos().y;

					//飛んでいる
					if (GetJumpFlag() == true)
					{
						SetJumpFlag(false); //飛んでいないに設定
					}
				}
			}
		}
	}

	//=================================
	//小さいブロック001分回す
	for (int nCount7 = nInitNumber; nCount7 < m_nSmalBlock001; nCount7++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetSmallBlock001(nCount7) != nullptr)
		{
			//上に乗っている時
			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//燃料ゲージが使われている時
				if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
				{
					CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
				}

				GravityTogether(); //重力の同期

				//位置の同期
				GetPos().y = CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize().y + CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos().y;


				//飛んでいる
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //飛んでいないに設定
				}
			}

			//下に当たっている時
			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSmallBlock001(nCount7)->GetModelSize(), GetMove()) == true)
			{
				//飛んでいる
				if (GetJumpFlag() == true)
				{
					SetJumpFlag(false); //飛んでいないに設定
				}
			}
		}
	}

	////上壁ブロック分回す
	//for (int nCount6 = 0; nCount6 < CManager::GetInstance()->GetUpWallBlockCount() + 1; nCount6++)
	//{
	//	if (CManager::GetInstance()->GetUpBlock(nCount6) != nullptr)
	//	{
	//		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//		{
	//			//GetPos().x = 100.0f;
	//		}
	//		else
	//		{
	//			if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				GetPos().y = CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize().y + CManager::GetInstance()->GetUpBlock(nCount6)->GetPos().y;//y軸の位置を設定
	//				if (GetJumpFlag() == true)
	//				{
	//					SetJumpFlag(false); //飛んでいないに設定
	//				}
	//			}
	//			else if (GetCollision() ->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetUpBlock(nCount6)->GetPos(), GetModelSize(), CManager::GetInstance()->GetUpBlock(nCount6)->GetModelSize(), GetMove()) == true)
	//			{
	//				CManager::GetInstance()->GetFuelGage()->GetUse() = false;
	//				GravityTogether();
	//				SetJumpFlag(false); //飛んでいないに設定
	//			}
	//		}
	//	}
	//}

	
	//=================================
	//ボス戦の足場
	if (CManager::GetInstance()->GetFinalBlock() != nullptr)
	{
		//上に乗っている時
		if (GetCollision() ->ColiisionBoxInside(GetPos(), CManager::GetInstance()->GetFinalBlock()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalBlock()->GetModelSize(), GetMove()) == true)
		{
			//燃料ゲージが使われている時
			if (CManager::GetInstance()->GetFuelGage()->GetUse() == true)
			{
				CManager::GetInstance()->GetFuelGage()->GetUse() = false; //燃料ゲージを不使用に設定
			}

			GravityTogether(); //重力の同期

			//位置の同期
			GetPos().y = CManager::GetInstance()->GetFinalBlock()->GetModelSize().y + CManager::GetInstance()->GetFinalBlock()->GetPos().y;

			//飛んでいる
			if (GetJumpFlag() == true)
			{
				SetJumpFlag(false); //飛んでいないに設定
			}
		}
	}

	//=================================
	//ボス戦の天井
	if (CManager::GetInstance()->GetFinalCeiling() != nullptr)
	{
		//下に当たっている時
		if (GetCollision()->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), GetMove()) == true)
		{
			//SetPos(D3DXVECTOR3(GetPos().x,GetPos().y-100.0f,GetPos().z));
			SetGravityFlag(true);//重力ON
			////下に当たっている時
			//if (GetCollision()->ColiisionBoxOutside(GetPos(), CManager::GetInstance()->GetFinalCeiling()->GetPos(), GetModelSize(), CManager::GetInstance()->GetFinalCeiling()->GetModelSize(), GetMove()) == true)
			//{
			//	SetGravityFlag(true);//重力ON
			//	//CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CObjectX::F_INIT_NUMBER;
			//}
			//else
			//{
			//	CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CEvent::CANERA_POSY;    //カメラのＹ軸の値を設定
			//}
		}
		//else
		//{
		//	CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CEvent::CANERA_POSY;    //カメラのＹ軸の値を設定
		//}
	}

	//=================================
	//バトルシップとの当たり判定
	if (CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP) != nullptr)
	{
		//当たり判定
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos(), GetModelSize(), CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetModelSize() * ADJUST_HIT_BATTLE) == true)
		{
			//NextStageMotion();
			m_bPlayerMoveNext = true; //次のsceneへ行くフラフをONにする
		}
	}

	//=================================
	//SHOPとの当たり判定
	if (CManager::GetInstance()->GetShop() != nullptr)
	{
		//当たり判定
		if (GetCollision() ->ColiisionBox(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize(), GetMove()) == true)
		{

		}

		//円の当たり判定
		if (GetCollision() ->CircleCollisionAll(GetPos(), CManager::GetInstance()->GetShop()->GetPos(), GetModelSize(), CManager::GetInstance()->GetShop()->GetModelSize() * 1.5f) == true)
		{
			//話すtextの情報がない時
			if (m_pTalkText == nullptr)
			{
				m_pTalkText = CUI::Create(CObject3D::TYPE::TALKTEXTR); //生成

				//位置の設定
				m_pTalkText->GetPos() = D3DXVECTOR3(CManager::GetInstance()->GetShop()->GetPos().x, CManager::GetInstance()->GetShop()->GetPos().y + 150.0f, CManager::GetInstance()->GetShop()->GetPos().z); //位置の初期化
			}

			//プレイヤーの状態が通常状態の時
			if (m_PlayerState == CPlayerX::PLAYER_STATE::NORMAI_MODE)
			{
				ShopKeySet(); //店用のキーセット処理関数を呼ぶ
			}
		}

		//当たっていない時
		else
		{
			//話すtextの情報がある時
			if (m_pTalkText != nullptr)
			{
				m_pTalkText->Release(); //情報を消す
				m_pTalkText = nullptr;  //情報を無くす
			}
		}
	}
}

//===============================================================================================================================================================================
//UIの当たり判定
//===============================================================================================================================================================================
void CPlayerX::UIJudgement()
{
	int nInitNumber = CObjectX::N_INIT_NUMBER; //初期値

	//レーザーの数分回す
	for (int nLaser = nInitNumber; nLaser < m_nLaserCount; nLaser++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetLaser(nLaser) != nullptr)
		{
			//プレイヤーの各パーツ毎の当たり判定処理
			for (int nCount = nInitNumber; nCount < CObjectX::MAX_PARTS; nCount++)
			{
				//当たり判定処理
				if (GetCollision()->ColiisionBox3D(CManager::GetInstance()->GetLaser(nLaser)->GetPos(), GetPosParts(nCount),
					CLaserCamare::TOTALVALUE_X, CLaserCamare::TOTALVALUE_Y, CLaserCamare::TOTALVALUE_Z, GetModelSizeParts(nCount)) == true)
				{
					CManager::GetInstance()->GetLaser(nLaser)->Hit();                             //レーザーの当たった時の処理を呼ぶ
					CManager::GetInstance()->GetLaser(nLaser)->Release();                         //レーザーを削除する
					CManager::GetInstance()->DesignationUninit3D(CObject3D::TYPE::LASER, nLaser); //レーザーポインターをnullptrにする
					return;                                                                       //処理を抜ける
				}
			}
		}
	}
}

//=====================================================================
//次のステージに行く時のモーション処理(主にスペースシップの処理)
//=====================================================================
void CPlayerX::NextStageMotion()
{
	m_nNextStageFrame++;        //フレームを増やす

	SetPos(D3DXVECTOR3(
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().x,
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().y + PLUS_POS_Y,
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetPos().z + MINUS_POS_Z));
	//GetPos().y= CManager::GetInstance()->GetSpeceBattleShip(1)->GetPos().y;

	//第一行動
	if (m_nNextStageFrame <= ATTACKPATTEN_FRAME_1)
	{
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->GetRot().y = -D3DX_PI_ORI;  //Y軸の向きを設定
	}

	//第二行動
	else if (m_nNextStageFrame <= ATTACKPATTEN_FRAME_2)
	{
		//X軸の移動
		CManager::GetInstance()->GetSpeceBattleShip(NEXT_STAGE_BATTLESHIP)->SetAdjustPos().x += (float)m_nNextStageFrame * MAX_POS_NEXTSTAGE;
		SetAdjustPos().x += (float)m_nNextStageFrame * MAX_POS_NEXTSTAGE;
	}

	//終了
	else
	{
		m_bNextStage = true; //次のsceneへ行くフラフをONにする
	}
}

//===============================================================================================================================================================================
//モデルの取得
//===============================================================================================================================================================================
CPlayerX* CPlayerX::Create()
{
	CPlayerX* pPlayerX = new CPlayerX(); //動的確保

	//初期化に成功した時
	if (SUCCEEDED(pPlayerX->Init()))
	{
		pPlayerX->SetType(TYPE::PLAYER); //タイプをPLAYERに設定
		return pPlayerX;                 //プレイヤーの情報を返す
	}

	return nullptr; //無を返す
}


//===============================================================================================================================================================================
//現在作っているオブジェクトのUIを出す処理
//===============================================================================================================================================================================
void CPlayerX::NowCreateObjectUI()
{
	//１キーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_1) == true)
	{
		//今の対象のオブジェクトの番号が０以下
		if (m_ObjectNumber <= CObjectX::N_INIT_NUMBER)
		{
			m_ObjectNumber = MAX_TEXT_OBJECT; //今作られている数にする
		}
		else
		{
			m_ObjectNumber--;                 //減らす
		}

		//情報がある時
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //情報を消す
			m_pNowCreateUI = nullptr;  //情報を無くす
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //生成処理
		}

		//情報がない時
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //生成処理
		}
	}

	//２キーが押された時
	else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_2) == true)
	{
		//オブジェクトナンバーが生成されている数以上の時
		if (m_ObjectNumber >= MAX_TEXT_OBJECT)
		{
			m_ObjectNumber = CObjectX::N_INIT_NUMBER; //初期化
		}
		else
		{
			m_ObjectNumber++;   //増やす
		}

		//情報がある時
		if (m_pNowCreateUI != nullptr)
		{
			m_pNowCreateUI->Release(); //情報を消す
			m_pNowCreateUI = nullptr;  //情報を返す
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //生成処理
		}

		//情報がない時
		if (m_pNowCreateUI == nullptr)
		{
			m_pNowCreateUI = CManager2DUI::NowCreate(m_ObjectNumber); //生成処理
		}
	}
}

//===============================================================================================================================================================================
//番号で作るオブジェクトを指定する処理
//===============================================================================================================================================================================
void CPlayerX::NowCreateNumberObj()
{
	//電柱を作る時のみm_pLaserUIが必要

	switch (m_ObjectNumber)
	{
	case CREATE_FIELDBLOCK:
		CObjectX::ObjectArrangement(TYPE::FIELDBLOCK, nullptr);                //地面の配置処理
		break;

	case CREATE_TELEPHONPOLE:
		CObjectX::ObjectArrangement(CObjectX::TYPE::TELEPHONPOLE, m_pLaserUI); //電柱の配置処理
		break;

	case CREATE_GOUPBLOCK:
		CObjectX::ObjectArrangement(TYPE::GOUPBLOCK, nullptr);                 //上がる用ブロックの配置処理
		break;
	}
}