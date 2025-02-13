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
	void DrawEnemy001(int NumPrts);                            //敵001の描画処理
	void MotionInfoEnemy001();                                 //敵001のモーションの情報を扱う処理

	void UpdateEnemy002();                                     //敵002の更新処理
	void DrawEnemy002(int NumPrts);                            //敵002の描画処理
	void MotionInfoEnemy002();                                 //敵002のモーションの情報を扱う処理

	void LoodEnemy(const char* aSelect);                       //モデルを読み込む処理＋情報を取得する処理


	//===========================
	//情報の取得
	CModelPrts* GetEnemy001ModelParts(int nNumber) { return m_pModelPrtsEnemy001[nNumber]; }
	int& GetEnemy001PartsNumber() { return m_nEnemy001Parts; } //敵001のパーツ数の取得


	//===========================
	//情報の設定
	void SetMotionEnemy001(ENEMYMOTIONSTATE motiontype);                       //敵001モーションごとの処理
	void SetMotionEnemy002(ENEMYMOTIONSTATE motiontype);                       //敵002モーションごとの処理
	void SetMotionType(bool bMotionType) { m_bMotionEnemyType = bMotionType; } //モーションタイプの設定


	//===========================
	//敵001に関するマクロ定義
	static constexpr  int PARTS_BODY_NUMBER = 0;                  //体の番号
	static constexpr  int PARTS_RIGHT_SHOLDER_WEAPON_NUMBER = 4;  //右肩の武器の番号


private:
	//マクロ定義		
	static constexpr int MAX_PARTS_SEARCH = 100;                  //パーツの取得時の配列の最大数
	static constexpr int MAX_DATA_SEARCH = 512;                   //テキストファイルの読み込み時の配列の最大数
	static constexpr int MAX_ENEMYKEYSET = 5;                     //モーションに使うキーの数
	static constexpr int NUM_ENEMYMOTION = 10;                    //モーションの数
	static constexpr int BEFORE_PARTS_COUNT = -1;                 //前のパーツカウント
	static constexpr int HALF = 2;                                //int型の時の半分
	static constexpr int FGET_NUMBER_1 = 40;                      //fgets関数の読み取り値１つ目
	static constexpr int FGET_NUMBER_2 = 20;                      //fgets関数の読み取り値２つ目
	static constexpr int PARENT_NUMBER = -1;                      //親パーツの読み込み値


	//============================================
	//敵001に関するマクロ定義
	static constexpr  int PARTS_RIGHT_SHOLDER_NUMBER = 2;         //右肩の番号
	static constexpr  int PARTS_LEFT_SHOLDER_NUMBER = 5;          //左肩の番号
	static constexpr  int PARTS_LEFT_SHOLDER_WEAPON_NUMBER = 7;   //左肩の武器の番号
	static constexpr  int PARTS_LEFT_WAIST_NUMBER = 8;            //腰の番号
	static constexpr  int PARTS_LEFT_MIDDLELEG_NUMBER = 9;        //足の中間のパーツ番号
	static constexpr  int PARTS_LOWER_BODY_COUNT = 7;             //下半身のパーツ数
	static constexpr  int NEXT_MOTION_COUNT = 1;                  //モーション時の差分を求める時の次のモーションカウント
	static constexpr  int BEFORE_MOTION_COUNT = 1;                //モーション時の差分が同じ時の前のモーションカウント


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


	//==============================================
	//キャラクターの情報を保管する変数
	ENEMYMOTIONSTATE m_MotionStateEnemy001, m_MotionStateEnemy002; //敵のモーションの種類の情報を持つ

	//モデルパーツの情報のポインター
	CModelPrts* m_pLoodModelPrtsEnemy[MAX_ENEMYPARTS], * m_pModelPrtsEnemy001[MAX_ENEMYPARTS], * m_pModelPrtsEnemy002[MAX_ENEMYPARTS];

	//モデルパーツの保管用情報の変数
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo001[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo002[MAX_ENEMYPARTS];

	//各モーションの種類を格納する変数
	MotionSet LoodMotionSetEnemy[NUM_ENEMYMOTION],MotionSetEnemy001[NUM_ENEMYMOTION], MotionSetEnemy002[NUM_ENEMYMOTION];

	int MotionCountEnemy001;    //敵001現在のモーションをカウントするための変数(Keyカウント)
	int m_nEnemy001Parts;       //敵001のパーツ数
	int m_nEnemy001Frame;       //敵001のモーション時のフレーム

	int MotionCountEnemy002;    //敵002現在のモーションをカウントするための変数(Keyカウント)
	int m_nEnemy002Parts;       //敵002のパーツ数
	int m_nEnemy002Frame;       //敵002のモーション時のフレーム

	int m_nNumParts;            //パーツ数
	bool m_bMotionEnemyType;    //特殊なモーションかどうか
};