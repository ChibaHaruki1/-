//=======================================================================
//
//オブジェクトのインスタンスをまとめるクラス管理[instance.h]
//Auther:HARUKI CHIBA
//
//=======================================================================


#pragma once


#ifndef _INSTANCE_H_  //このマグロ定義がされていなかったから
#define _INSTANCE_H_  //二重インクルード防止のマクロ定義


//=======================================================================
//インクルード
#include "main.h" 
#include "field.h"
#include "block.h"
#include "bullet.h"
#include "2d_ui.h"
#include "stage_obj.h"
#include "particles.h"
#include "efect.h"
#include "direction_obj.h"
#include "bg.h"
#include "enemy.h"
#include "enemyinmotion.h"
#include <vector>
#include "boss.h"
#include "bosseffect.h"
#include "gage.h"
#include "score.h"

class CInstance
{
public:
	CInstance();
	~CInstance();
	HRESULT Init();
	void Uninit();

	void DesignationUninitX(CObjectX::TYPE type, int nNumber);           //３Dモデルでnullptrにしたい物をnullptrにする処理
	void DesignationUninitXEnemy(CObjectX::TYPE type, int nNumber);     //敵でnullptrにしたい物をnullptrにする処理
	void DesignationUninit2D(CObject2D::TYPE type);                     //2Dでnullptrにしたい物をnullptrにする処理
	void DesignationUninit3D(CObject3D::TYPE type, int nNumber);         //3Dでnullptrにしたい物をnullptrにする処理

	CObject2D* GetCreateObjectInstnace2D(CObject2D::TYPE type, int nNumber);               //２Dオブジェクト生成
	CObject3D* GetCreateObjectInstnace(CObject3D::TYPE type, int nNumber, D3DXVECTOR3 pos);  //３Dオブジェクト生成
	CObjectX* GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos);  //３Dモデルのオブジェクト生成
	CObjectX* CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos);                   //ブロックの生成
	CObjectX* CreateRubble(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos);                  //がれきの生成

	//ブロックのインスタンスを取得
	CManagerBlock* GetFiledBlock(int nNumber) { return m_pFieldBlock[nNumber]; }                  //地面用ブロックの取得
	CManagerBlock* GetGoUpBlock(int nNumber) { return m_pGoUpBlock[nNumber]; }                    //上がるためのブロックの取得
	CManagerBlock* GetRoadBlock(int nNumber) { return m_pRoadBlock[nNumber]; }                    //道用ブロックの取得
	CManagerBlock* GetWallRoadBlock(int nNumber) { return m_pWallRoadBlock[nNumber]; }            //壁兼道用ブロックの取得
	CManagerBlock* GetWallRoadBlock001(int nNumber) { return m_pWallRoadBlock001[nNumber]; }      //壁兼道用ブロック001の取得
	CManagerBlock* GetSmallBlock(int nNumber) { return m_pSmallBlock[nNumber]; }                 //小さいブロックの取得
	CManagerBlock* GetSmallBlock001(int nNumber) { return m_pSmallBlock001[nNumber]; }           //小さいブロック001の取得
	CManagerBlock* GetUpBlock(int nNumber) { return m_pUpWallBlock[nNumber]; }                   //上壁ブロックの取得
	CManagerBlock* GetWoodenBoard(int nNumber) { return m_pWoodenBoard[nNumber]; }               //木の板群の取得
	CManagerBlock* GetFinalBlock() { return m_pFinalBlosk; }                                     //ボス戦時の地面の取得
	CManagerBlock* GetFinalCeiling() { return m_pFinalCeiling; }                                  //ボス戦時の天井の取得
	CManagerBlock* GetSpeceBattleShip(int nNumber) { return m_pSpeceBattleShip000[nNumber]; }     //次のステージへ行く用のオブジェクトの取得

	CDebrisX* GetDebrisX(int nNumber) { return m_pDebrisX[nNumber]; }                             //瓦礫の取得

	//ステージに配置する用のオブジェクトのインスタンスを取得
	CStageObj* GetTelephonPole(int nNumber) { return m_pTelephonPole[nNumber]; }                  //電柱の取得
	CStageObj* GetSurveillanceCameraUp(int nNUmber) { return m_pSurveillanceCameraUp[nNUmber]; }  //カメラの上部分の取得
	CStageObj* GetShop() { return m_pShop; }                                                      //店の取得

	//パーティクルの取得
	CParticles001* GetPraticles001(int nNumber) { return m_pPraticles001[nNumber]; }              //円状のパーティクルの取得

	//エフェクトの取得
	CEffect* GetEffect() { return m_pEffect; }                                                    //プレイヤーの弾に行くエフェクトの取得
	CManagerEffect* GetExplosion() { return m_pExplosion; }                                       //爆発エフェクトの取得
	CManagerEffect* GetExplosion001() { return m_pExplosion001; }                                 //爆発エフェクト001の取得
	CManagerEffect* GetThander() { return m_pThander; }                                           //雷エフェクトの取得
	CManagerEffect* GetFire() { return m_pFire; }                                                 //炎エフェクトの取得
	CManagerEffect* GetDebris() { return m_pDebris; }                                             //一枚絵の破片エフェクトの取得
	CManagerEffect* GetPillarOfFire() { return m_pPillarOfFire; }                                 //柱状の炎のエフェクトの取得
	CSpecialAttack* GetSpecialAttack() { return m_pSepecialAttack; }                              //必殺技のエフェクトの取得
	CManagerBossEffect* GetBossSpecialAttack() { return m_pBossSpecialAttack; }                   //ボスの必殺技のエフェクトの取得
	CManagerBossEffect* GetImpact() { return m_pImpact; }                                         //衝撃波エフェクトの取得

	//敵系の取得
	CManagerEnemy* GetEnemy000() { return m_pEnemy000; }                                              //通常敵の取得
	CManagerEnemy* GetEnemy001(int nNumber) { return m_pEnemy001[nNumber]; }                          //通常敵001の取得
	CManagerEnemy* GetEnemy002(int nNumber) { return m_pEnemy002[nNumber]; }                          //通常敵001の取得
	CManagerEnemyInMotion* GetEnemyInMotion(int nNumber) { return m_pEnemyInMotion000[nNumber]; }     //モーション付きの敵の取得
	CManagerEnemyInMotion* GetEnemyInMotion001(int nNumber) { return m_pEnemyInMotion001[nNumber]; }  //モーション付きの敵001の取得
	CManagerEnemyInMotion* GetEnemyInMotion002(int nNumber) { return m_pEnemyInMotion002[nNumber]; }  //モーション付きの敵002の取得
	CBoss* GetBoss() { return m_pBoss; }                                                              //ボスの取得

	//2Dのインスタンス
	CShopScreen* GetShopScreen() { return m_pShopScreen; }            //SHOP時の背景の情報を取得
	CManagerGage* GetPlayerHPGage() { return m_pPlayerHPGage; }       //プレイヤーのHPゲージの取得
	CBossHPGage* GetBossHPGage() { return m_pBossHPGage; }            //ボスのHPゲージの取得
	CManagerScore* GetGameScore() { return m_pGameScore; }            //ゲーム中のスコアの取得

	//３Dの取得
	CFuelGage* GetFuelGage() { return m_pFuelGage; }                   //燃料ゲージの取得
	CUI* GetLaser(int nNumber) { return m_pLaser[nNumber]; }          //レーザーの取得

	//作った数を取得する用の関数									     
	int& GetFieldBlockCount() { return  m_nNumFiledBlock; }            //床用のブロックの作った数
	int& GetGoUpBlockCount() { return  m_nNumGoUpBlock; }              //上がる用のブロックの作った数
	int& GetRoadBlockCount() { return  m_nRoadBlock; }                 //道用ブロックの作った数
	int& GetWallRoadBlockCount() { return  m_nWallRoadBlock; }         //壁兼道用ブロックの作った数
	int& GetWallRoadBlock001Count() { return  m_nWallRoadBlock001; }   //壁兼道用ブロック001の作った数
	int& GetSmallBlockCount() { return  m_nSmallBlock; }               //小さいブロックの作った数
	int& GetSmallBlock001Count() { return  m_nSmallBlock001; }         //小さいブロックの作った数
	int& GetUpWallBlockCount() { return  m_nUpWallBlock; }             //上がる用のブロックの作った数
	int& GetWoodenBoardCount() { return m_nWoodenBoard; }             //木の板群の作った数
	int& GetEnemy001Count() { return m_nEnemy001; }                   //敵001の作った数
	int& GetEnemy002Count() { return m_nEnemy002; }                   //敵002の作った数
	int& GetMotionInEnemyCount() { return m_nEnemyInMotion; }         //モーション付きの敵の生成数
	int& GetMotionInEnemy001Count() { return m_nEnemyInMotion001; }   //モーション付きの敵001の生成数
	int& GetLaserCount() { return m_nLaser; }                         //レーザーの数

	//マクロ定義 （constexprでコンパイル時に初期化）
	 static constexpr  int MAX_ENEMYINMOTION = 10;  //モーション付きの敵の最大数
	 static constexpr  int MAX_OBJECT_DATA = 20;    //オブジェクトの最大数
	 static constexpr  int MAX_STAGEOBJECT = 20;    //ステージに置く用の配列の最大数
	 static constexpr  int MAX_BREAKHOUSE = 10;     //ステージに置く用の配列の最大数
	 static constexpr  int MAX_RUBBLE = 40;         //瓦礫の最大数
	 static constexpr  int MAX_ENEMY = 25;          //敵の最大数
	 static constexpr  int MAX_SHIP = 2;           //スペースシップの最大数

	//インライン展開
	/*inline void CreateFuelGage()
	{
		m_pFuelGage = CFuelGage::Create();
	}*/


	 //==========================
	 //マクロ定義
	 static constexpr int N_INIT_CREATE_NUMBER = -1; //生成数の初期値


private:
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;          //int型の初期化の値


	//ブロックのインスタンスを生成
	CManagerBlock* m_pFieldBlock[MAX_OBJECT_DATA];       //地面用ブロックのインスタンス
	CManagerBlock* m_pGoUpBlock[MAX_OBJECT_DATA];        //上がるためのブロックのインスタンス
	CManagerBlock* m_pRoadBlock[MAX_OBJECT_DATA];        //道用ブロックのインスタンス
	CManagerBlock* m_pWallRoadBlock[MAX_OBJECT_DATA];    //壁兼道用のブロックのインスタンス
	CManagerBlock* m_pWallRoadBlock001[MAX_OBJECT_DATA]; //壁兼道用ブロックのインスタンス
	CManagerBlock* m_pSmallBlock[MAX_OBJECT_DATA];       //小さいブロックのインスタンス
	CManagerBlock* m_pSmallBlock001[MAX_OBJECT_DATA];    //小さいブロック001のインスタンス
	CManagerBlock* m_pUpWallBlock[MAX_OBJECT_DATA];      //上壁のブロックのインスタンス
	CManagerBlock* m_pWoodenBoard[MAX_RUBBLE];           //木の板群のインスタンス
	CManagerBlock* m_pFinalBlosk;                         //ボス戦時の足場のインスタンス
	CManagerBlock* m_pFinalCeiling;                       //ボス戦時の天井のインスタンス

	CManagerBlock* m_pSpeceBattleShip000[MAX_SHIP];      //次のステージへ行くオブジェクトのインスタンス

	//敵のインスタンス
	CManagerEnemy* m_pEnemy000;                                      //通常敵のインスタンス
	CManagerEnemy* m_pEnemy001[MAX_ENEMY];                           //通常敵001のインスタンス
	CManagerEnemy* m_pEnemy002[MAX_ENEMY];                           //通常敵002のインスタンス

	CManagerEnemyInMotion* m_pEnemyInMotion000[MAX_ENEMYINMOTION];   //モーション付きの敵のインスタンス
	CManagerEnemyInMotion* m_pEnemyInMotion001[MAX_ENEMYINMOTION];   //モーション付きの敵001のインスタンス
	CManagerEnemyInMotion* m_pEnemyInMotion002[MAX_ENEMYINMOTION];   //モーション付きの敵002のインスタンス
	CBoss* m_pBoss;                                                  //ボスのインスタンス

	//演出用のオブジェクトのインスタンス
	CDebrisX* m_pDebrisX[MAX_OBJECT_DATA];             //Xファイル型の破片オブジェクト

	//パーティクルのインスタンスを生成
	CParticles001* m_pPraticles001[MAX_OBJECT_DATA];   //パーティクルの円

	//ステージオブジェクトのインスタンス
	CStageObj* m_pTelephonPole[MAX_STAGEOBJECT];           //電柱
	CStageObj* m_pSurveillanceCameraUp[MAX_STAGEOBJECT];   //監視カメラの上の部分
	CStageObj* m_pSurveillanceCameraDown[MAX_STAGEOBJECT]; //監視カメラの下の部分
	CStageObj* m_pShop;                                    //店
	CStageObj* m_pBreakHouse[MAX_BREAKHOUSE];              //壊れた家

	//エフェクトのインスタンス
	CEffect* m_pEffect;                          //弾につくエフェクトのインスタンス
	CManagerEffect* m_pExplosion;                //爆発エフェクトのインスタンス
	CManagerEffect* m_pThander;                  //雷エフェクトのインスタンス
	CManagerEffect* m_pFire;                     //炎エフェクトのインスタンス
	CManagerEffect* m_pExplosion001;             //爆発１エフェクトのインスタンス
	CManagerEffect* m_pDebris;                   //破片エフェクト
	CManagerEffect* m_pPillarOfFire;             //柱状の炎エフェクト
	CSpecialAttack* m_pSepecialAttack;           //必殺技のエフェクト
	CManagerBossEffect* m_pImpact;               //衝撃波エフェクトのインスタンス
	CManagerBossEffect* m_pBossSpecialAttack;    //ボスの必殺技エフェクトのインスタンス


	//2Dのインスタンス
	CShopScreen* m_pShopScreen;      //ショップ時の背景スクリーンのUI
	CManagerGage* m_pPlayerHPGage;   //プレイヤーのHPゲージ
	CBossHPGage* m_pBossHPGage;      //プレイヤーのHPゲージ
	CManagerScore* m_pGameScore;

	//３Dのインスタンス
	CFuelGage* m_pFuelGage;          //燃料ゲージ
	CUI* m_pLaser[MAX_STAGEOBJECT];  //カメラから出るレーザー

	//作られた数を保管する変数
	int m_nNumFiledBlock;      //地面用のブロックの数
	int m_nNumGoUpBlock;       //上がる用のブロックの数
	int m_nRoadBlock;          //道用のブロックの数
	int m_nWallRoadBlock;      //壁兼道用のブロックの数
	int m_nWallRoadBlock001;   //壁兼道用のブロック001の数
	int m_nSmallBlock;         //小さいブロックの数
	int m_nSmallBlock001;      //小さいブロック001の数
	int m_nUpWallBlock;        //上の壁のブロックの数
	int m_nEnemy001;           //敵の数
	int m_nEnemy002;           //敵の数
	int m_nEnemyInMotion;      //モーション付きの敵の数
	int m_nEnemyInMotion001;   //モーション付きの敵001の数
	int m_nEnemyInMotion002;   //モーション付きの敵002の数
	int m_nWoodenBoard;        //木の板群の数
	int m_nBreakHouse;         //壊れた家の数
	int m_nShip;               //スペースシップの数
	int m_nLaser;              //レーザーの作られた数
};

#endif
