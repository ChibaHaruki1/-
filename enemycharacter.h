//==============================================
//
//敵のcharacterクラス管理[enemycharacter.h]
//Ajther: Chiba haruki
//
//==============================================

#pragma once

//==============================================
//インクルード
#include "objectX.h"
#include "model_prts.h"

class CEnemyCharacter : public CObjectX
{
public:

	//敵のモーションの種類
	typedef enum
	{
		ENEMYWALK = 0,  //歩き
		ENEMYJUMP,      //飛ぶ
		ENEMYATTACK,    //攻撃
		ENEMYDIE,       //死亡

	}ENEMYMOTIONSTATE;

	CEnemyCharacter(int nPriority = DEFAULT_PRIORITY1);        //コンストラクタ
	~CEnemyCharacter();                                        //デストラクタ
	HRESULT Init();                                            //初期化処理
	void Uninit();                                             //破棄処理
	void UpdateEnemy001();                                     //敵001の更新処理
	void UpdateEnemy002();                                     //敵002の更新処理
	void DrawEnemy(int NumPrts, int nNumber);                  //描画処理
	void LoodEnemy(const char* aSelect);                       //モデルを読み込む処理＋情報を取得する処理
	void MotionInfoEnemy001();                                 //敵001のモーションの情報を扱う処理
	void MotionInfoEnemy002();                                 //敵002のモーションの情報を扱う処理


	//===========================
	//情報の取得
	int& GetEnemy001PartsNumber() { return m_nEnemy001Parts; } //敵001のパーツ数の取得


	//===========================
	//情報の設定
	void SetMotionEnemy(ENEMYMOTIONSTATE motiontype);                          //ボスモーションごとの処理
	void SetMotionType(bool bMotionType) { m_bMotionEnemyType = bMotionType; } //モーションタイプの設定


	ENEMYMOTIONSTATE m_MotionStateEnemy;                      //ボスのモーションの種類の情報を持つ
	CModelPrts* m_pModelPrtsEnemy[MAX_ENEMYPARTS];            //モデルパーツの情報のポインター

private:
	//マクロ定義
	constexpr static int MAX_ENEMYKEYSET = 5;                 //モーションに使うキーの数
	constexpr static int NUM_ENEMYMOTION = 10;                //モーションの数
	constexpr static int HALF = 2;                            //int型の時の半分


	//キーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //向き
	}Key;

	//キーセットの構造体
	typedef struct
	{
		int Frame;                 //フレーム数
		Key aKey[MAX_ENEMYPARTS];  //キー数(パーツ分確保)
	}KeySet;

	//モーションの構造体
	typedef struct
	{
		bool Loop;                        //モーションがループするかどうか判定用
		int NumKey;						  //キーの総数
		KeySet KeySet[MAX_ENEMYKEYSET];	  //モーションのキーセット（モーション時のキーセットの数）
	}MotionSet;

	//モーション情報を確保する構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //向き
	}SAVEMODELINFO;

	//キャラクターの情報を保管する変数
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo[MAX_ENEMYPARTS]; //モデルパーツの情報のポインター
	D3DXVECTOR3 SaveMotionPos[MAX_ENEMYPARTS];                 //各パーツの位置情報を確保する変数
	D3DXVECTOR3 SaveMotionRot[MAX_ENEMYPARTS];                 //各パーツの向き情報を獲得する変数
	MotionSet MotionSetEnemy[NUM_ENEMYMOTION];                 //各モーションの種類を格納する変数

	int MotionCountEnemy;    //現在のモーションをカウントするための変数(Keyカウント)
	int m_nNumParts;         //パーツ数
	int m_nEnemy001Parts;    //敵001のパーツ数
	int m_nEnemy002Parts;    //敵002のパーツ数
	bool m_bMotionEnemyType; //特殊なモーションかどうか
};