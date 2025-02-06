//================================================================
//
//ステージ毎のイベント処理クラス[event.h]
//Auther:Haruki Chiba
//
//================================================================

#pragma once

//=====================
//インクルード
#include <vector>
#include "instance.h"

//=====================================================================================================
//eventの基底クラス
//=====================================================================================================
class CEvent
{
public:
	CEvent();                  //デストラクタ
	~CEvent();                 //コンストラクタ
	void Update();             //更新処理
	void DropObj();            //objの落とす処理
	void BossDirection();      //ボスの演出処理	
	void DropMeteorite();      //隕石を落とす処理
	void CreateEnemy();        //敵の生成


	//==========================
	//情報の取得
	bool& GetBossDirection() { return m_bBossDirection; } //ボスの生成がされているかどうかの情報を取得


	//==========================
	//マクロ定義
	 static constexpr  float CANERA_POSY = 400.0f;                //カメラのY軸の位置

private:
	//マクロ定義
	static constexpr int CANERA_POSZ = 1400;                    //カメラのZ軸の位置
	static constexpr int RAND_ROTX = 15;                        //木の板軍の落とすときの向きのX軸の値
	static constexpr int RAND_ROTY = 31;                        //木の板軍の落とすときの向きのY軸の値
	static constexpr int INIT_DROP_POS = 18;                    //木の板軍の落とす位置をあらかじめ設定するための値
	static constexpr int BEFORE_NUMBER = 1;                     //前の番号

	static constexpr float ADJUST_ROT = 0.1f;                   //整数で出した値を少数に直す為の値
	static constexpr float EVENT_BOSS_FIGHT_POS = 3650.0f;      //ボス戦の始まりになる位置
	static constexpr float CREATE_BOSS_POSX = 4700.0f;          //ボスが生成させるX軸の位置
	static constexpr float CREATE_MOTIONINENEMY_POSX = 9500.0f; //モーション付きの敵が生成させるX軸の位置
	static constexpr float CREATE_MOTIONINENEMY_POSY = 5000.0f; //モーション付きの敵が生成させるY軸の位置
	static constexpr float CREATE_WOODENBOARD_POSX = 3250.0f;   //木の板群が生成させるX軸の位置
	static constexpr float CREATE_WOODENBOARD_POSY = 350.0f;    //木の板群が生成させるY軸の位置
	static constexpr float WOODENBOARD_DROPY = 10.0f;           //木の板群の落とす位置を増やす値
	static constexpr float WOODENBOARD_PLUSY = 0.12f;           //木の板群の落とす速度を増やす値
	static constexpr float PLUS_POS_X = 500.0f;			        //木の板群の落とす速度を増やす値

	static constexpr int N_INIT_NUMBER = 0;                     //int型の初期化の値
	static constexpr float F_INIT_NUMBER = 0.0f;                //float型の初期化の値




	int m_nCreateWoodenBoradsCounter;            //生成する数
	int m_nRandomRotX;                           //向きのランダム数を保管する
	int m_nRandomRotY;                           //向きのランダム数を保管する
	float m_nPosY;                               //生成時のY軸のpos
	float m_fDropSpeed[CInstance::MAX_RUBBLE];   //落とす速度を決める変数
	float m_fDropPosY[CInstance::MAX_RUBBLE];    //落とす位置をあらかじめ決める変数
	bool m_bBossDirection;                       //ボスの演出を1回だけ出すための処理
	bool m_bOneflag;                             //一回だけ処理を通す用の変数
	bool m_bOneCreate;                           //一回だけ生成する用の変数
};
