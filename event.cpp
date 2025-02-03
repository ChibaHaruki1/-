//==========================================
//
//ステージ毎のevent処理をする[enent.cpp]
//Auther:Haruki Chiba
//
//==========================================


//==========================================
//インクルード
#include "event.h"
#include "manager.h"
#include <time.h>


//============================
//コンストラクタ
//============================
CEvent::CEvent()
{
	//生成できる最大数分回す
	for (int nCount = N_INIT_NUMBER; nCount < CInstance::MAX_RUBBLE; nCount++)
	{
		m_fDropSpeed[nCount] = F_INIT_NUMBER;                                     //落とすスピードの初期化
		m_fDropPosY[nCount] = (float)(nCount * INIT_DROP_POS);                    //落とす位置をどんどん高くする（積みあがらせる為）
	}															                  
																                  
	m_nCreateWoodenBoradsCounter = N_INIT_NUMBER;                                 //生成した数の初期化
	m_nRandomRotX = N_INIT_NUMBER;                                                //ｘ軸の向きの乱数の初期化
	m_nRandomRotY = N_INIT_NUMBER;                                                //ｙ軸の向きの乱数の初期化
	m_nPosY = CREATE_WOODENBOARD_POSY;                                            //生成するY軸のposの初期化
	m_bOneflag = false;                                                           //一回だけ通すフラグの初期化（使われてない）
	m_bBossDirection = false;                                                     //ボス演出を一回だけするフラグの初期化（使われてない）
	m_bOneCreate = false;                                                         //生成フラグをOffに設定

	mciSendStringA("open data\\BGM\\Bossbgm-Short.wav alias BGM", NULL, N_INIT_NUMBER, NULL); //設定した音源を開く（再生は別）
}


//============================
//デストラクタ
//============================
CEvent::~CEvent()
{
	mciSendStringA("close BGM", NULL, N_INIT_NUMBER, NULL); //設定した音源を閉じる
}


//============================
//更新処理
//============================
void CEvent::Update()
{
	//現在の生成数が最大数よりすくない時
	if (m_nCreateWoodenBoradsCounter < CInstance::MAX_RUBBLE)
	{
		BossDirection();  //ボス線の演出処理を呼ぶ
	}

	//木の板群が生成された時
	if (CManager::GetInstance()->GetWoodenBoardCount() > N_INIT_NUMBER)
	{
		//まだ全て落ち切ってない時
		if (m_bOneflag == false)
		{
			DropObj();  //木の板群を落とす処理を呼ぶ
		}

		//木の板群を生成した数分回す
		for (int WoodenBoardCount = N_INIT_NUMBER; WoodenBoardCount < m_nCreateWoodenBoradsCounter; WoodenBoardCount++)
		{
			//プレイヤーと木の板の当たり判定
			if (CManager::GetScene()->GetPlayerX()->CollisionPlayerSelect(CManager::GetInstance()->GetWoodenBoard(WoodenBoardCount)))
			{
					CManager::GetScene()->GetPlayerX()->GetMove().x += CPlayerX::MAX_MOVESPEED; //プレイヤーを逆側へ押し出す
			}
		}
	}
}


//============================
//ボス戦の演出処理
//============================
void CEvent::BossDirection()
{
	//プレイヤーが生成されていた時
	if (CManager::GetScene()->GetPlayerX() != nullptr)
	{
		//プレイヤーのposが既定の場所へ行った時
		if (CManager::GetScene()->GetPlayerX()->GetPos().x >= EVENT_BOSS_FIGHT_POS)
		{
			//ボスの演出がまだの時
			if (m_bBossDirection == false)
			{
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BOSS, N_INIT_NUMBER,
					D3DXVECTOR3(CREATE_BOSS_POSX, F_INIT_NUMBER, F_INIT_NUMBER));                                             //ボスを生成
				CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);                                  //指定の音源を止める
				mciSendStringA("play BGM", NULL, 0, NULL);                                                                    //開かれた音源を再生する（開かれてないと生成しない）         
				m_bBossDirection = true;                                                                                      //演出フラグをtrueにし、通らなくする
			}

			//カメラの位置を変更
			CManager::GetScene()->GetCamera()->GetAdjustmentPosZ() = CANERA_POSZ;    //カメラのＺ軸の値を設定
			CManager::GetScene()->GetCamera()->GetAdjustmentPosY() = CANERA_POSY;    //カメラのＹ軸の値を設定

			m_nPosY += WOODENBOARD_DROPY;         //落とす位置を増やす
			m_nRandomRotX = rand() % RAND_ROTX;   //Ｘ軸の向きを乱数で調整
			m_nRandomRotY = rand() % RAND_ROTY;   //Ｙ軸の向きを乱数で調整

			CManager::GetInstance()->CreateRubble(CObjectX::STRATEGYTYPE::WODDENBORAD, 
				D3DXVECTOR3(CREATE_WOODENBOARD_POSX, m_nPosY, F_INIT_NUMBER));                                                                //木の板群を出す
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().y = (float)m_nRandomRotY * ADJUST_ROT;   //Ｙ軸の向きを設定
			CManager::GetInstance()->GetWoodenBoard(m_nCreateWoodenBoradsCounter)->GetRot().x = (float)m_nRandomRotX * ADJUST_ROT;   //Ｘ軸の向きを設定
			m_nCreateWoodenBoradsCounter++; //配列カウントを進める
		}
	}
}


//============================
//落とす処理
//============================
void CEvent::DropObj()
{
	//木の板群が生成された数分回す
	for (int nCount = N_INIT_NUMBER; nCount < m_nCreateWoodenBoradsCounter; nCount++)
	{
		//生成した木の板群の位置が設定した位置より大きい（同じ）時
		if (CManager::GetInstance()->GetWoodenBoard(nCount)->GetPos().y >= m_fDropPosY[nCount])
		{
			m_fDropSpeed[nCount] += WOODENBOARD_PLUSY;                                             //落とす速度を増やす
			CManager::GetInstance()->GetWoodenBoard(nCount)->SetAdjustMove().y -= m_fDropSpeed[nCount];  //木の板群を落とす
		}

		//生成した木の板群の位置が設定した位置より小さい時
		else
		{
			//for分のカウントが最大数分行った時
			if (nCount == CInstance::MAX_RUBBLE - BEFORE_NUMBER)
			{
				m_bOneflag = true; //フラグをONにする
			}
		}
	}
}


//============================
//隕石を落とす処理
//============================
void CEvent::DropMeteorite()
{

}


//================================
//モーション付きの敵の生成処理
//================================
void CEvent::CreateEnemy()
{
	//プレイヤーが特定の場所へ行った時
	if (CManager::GetScene()->GetPlayerX()->GetPos().x >= CREATE_MOTIONINENEMY_POSX)
	{
		//生成フラグがOffの時
		if (m_bOneCreate == false)
		{
			//モーション付きの敵の生成
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, N_INIT_NUMBER, D3DXVECTOR3(CREATE_MOTIONINENEMY_POSX, CREATE_MOTIONINENEMY_POSY, F_INIT_NUMBER));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, N_INIT_NUMBER, D3DXVECTOR3(CREATE_MOTIONINENEMY_POSX+ PLUS_POS_X, CREATE_MOTIONINENEMY_POSY, F_INIT_NUMBER));
			m_bOneCreate = true; //Onにさせる
		}
	}
}