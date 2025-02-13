//============================================
//
//characterクラス管理[character.h]
//Ajther: Chiba haruki
//
//============================================

#pragma once

//============================================
//インクルード
#include "objectX.h"
#include "model_prts.h"


//======================================================
//キャラクターの各パーツクラス
class CCharacter : public CObjectX
{
public:
	////共通化でもいいかも
	//typedef enum
	//{
	//	NEUTRAL = 0, //待機
	//	WALK,        //歩き
	//	ACTION,      //
	//	JUMP,
	//}COMMON;

	//typedef enum
	//{
	//	BOSSJUMP1=4,
	//}BOSSMOTIONSTATE;

	//typedef enum
	//{
	//	BLOWAWAY=4,
	//}MOTIONSTATE;

	//ボスのモーションの種類
	typedef enum
	{
		BOSSNEUTRAL = 0, //待機
		BOSSWALK,        //歩く
		BOSSACTION,      //撃つ
		BOSSJUMP,        //飛ぶ
		BOSSIMPACT,      //飛ぶ001
		BOSSATTACK,      //攻撃
		BOSSDIE,         //死亡
	}BOSSMOTIONSTATE;

	//プレイヤーのモーションの種類
	typedef enum
	{
		NEUTRAL = 0, //待機
		WALK,        //歩き
		ACTION,      //撃つ
		JUMP,        //飛ぶ
		BLOWAWAY,    //吹っ飛ぶ
		DIE,         //死亡
		SLOWSHOT,    //ゆっくり撃つ
		TITLE_JUMP,  //タイトル時の飛ぶ
		LANDING,     //着地
		LOKING ,     //探す(タイトル時)
	}MOTIONSTATE;

	CCharacter(int nPriority = DEFAULT_PRIORITY1);         //コンストラクタ
	~CCharacter();                                         //デストラクタ
	HRESULT Init();                                        //初期化処理
	void Uninit();                                         //破棄処理

	//プレイヤー
    void Lood();
	void UpdatePlayer();                                   //プレイヤーの更新処理
	void DrawPlayer(int NumPrts);                          //プレイヤーの描画処理
	void MotionInfo();                                     //モーションの情報を扱う処理
	void SetMotion(MOTIONSTATE motiontype);                //モーションごとの処理
	
	//ボス
	void LoodBoss();
	void UpdateBoss();                                     //ボスの更新処理
	void DrawBoss(int NumPrts);                            //描画処理
	void MotionInfoBoss();                                 //ボスモーションの情報を扱う処理
	void SetMotionBoss(BOSSMOTIONSTATE motiontype);        //ボスモーションごとの処理

	MOTIONSTATE m_MotionState;                   //プレイヤーのモーションの種類の情報を持つ
	BOSSMOTIONSTATE m_MotionStateBoss;           //ボスのモーションの種類の情報を持つ
	CModelPrts* m_pModelPrts[MAX_PARTS];          //モデルパーツの情報のポインター
	CModelPrts* m_pModelPrtsBoss[MAX_BOSSPARTS]; //モデルパーツの情報のポインター


	//=====================================
	//情報の取得
	CModelPrts* GetModelPrtasBoss(int nNumber) { return m_pModelPrtsBoss[nNumber]; } //ボスのパーツの情報の取得
	//bool& GetMotionType() { return m_bMotionType; }                                  //プレイヤーのモーションタイプの取得


	//=====================================
	//情報の設定
	void SetMotionType(bool bMotionType) { m_bMotionType = bMotionType; }            //プレイヤーのモーションタイプの設定

	//==========================================
	//マクロ定義
	static constexpr  int MAX_KEYSET = 8;              //モーションに使うキーの数


	//==========================================
	//プレイヤーに関するマクロ
	static constexpr int PLAYER_PARTS_BODY_NUMBER = 0;      //体の番号
	static constexpr int PLAYER_PARTS_RIGHT_SHOLDER = 2;    //右肩の番号
	static constexpr int PLAYER_PARTS_LEFT_SHOLDER = 6;     //左肩の番号
	static constexpr int PLAYER_PARTS_RIGHT_THIGHS = 11;    //右太ももの番号
	static constexpr int PLAYER_PARTS_LEFT_THIGHS = 14;     //左太ももの番号
	static constexpr int PLAYER_PARTS_GUN_NUMBER = 17;      //銃の番号
	static constexpr int PLAYER_PARTS_GUN001_NUMBER = 18;   //銃001の番号
	static constexpr int NUM_MOTION = 11;                   //プレイヤーモーションの総数
	static constexpr int NUM_RIGHTLEFTPRTS = 4;             //プレイヤーの側のパーツ数
	static constexpr int PLAYER_GUN_COUNT = 2;              //銃の数


	 //==========================================
	 //ボスに関するマクロ
	 static constexpr  int NUM_MOTIONBOSS = 10;         //ボスのモーションの総数
	 static constexpr  int NUM_RIGHTPRTSBOSS = 8;       //ボスの側のパーツ数
	static constexpr float BOSS_PLUS_POS_Y = 200.0f;    //ボスのパーツのY軸の位置を上に上げる為の値
	static constexpr int BOSS_PARTS_GUN_NUMBER = 17;    //銃の番号
	static constexpr int BOSS_GUN_COUNT = 1;            //銃の数

private:
	//マクロ定義
	static constexpr int MAX_PARTS_SEARCH = 100;                     //パーツの取得時の配列の最大数
	static constexpr int MAX_DATA_SEARCH = 512;                      //テキストファイルの読み込み時の配列の最大数
	static constexpr int FGET_NUMBER_1 = 40;                         //fgets関数の読み取り値１つ目
	static constexpr int FGET_NUMBER_2 = 20;                         //fgets関数の読み取り値２つ目
	static constexpr int PARENT_NUMBER = -1;                         //親パーツの読み込み値
		

	//========================================================
	//プレイヤーに関するマクロ定義
	static constexpr int PLAYER_PARTS_RIGHTHAND_NUMBER = 5;          //右手の番号
	static constexpr int PLAYER_PARTS_LEFTHAND_NUMBER = 9;           //左手の番号
	static constexpr int PLAYER_PARTS_WAIST_NUMBER = 10;             //腰の番号
	static constexpr int PLAYER_PARTS_SHOULDER_FROM_HAND = 4;        //肩から手のFor文を回す際0,1,2,3の順（肩、上腕、下腕、手）で回す用
	static constexpr int PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;  //右肩から右手のFor文を回したい時の値（０～３の場合、右肩からは２番以上なのでどれくらい離れているかを常に足したい為）
	static constexpr int PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND = 6;   //左肩から右手のFor文を回したい時の値（０～３の場合、左肩からは６番以上なのでどれくらい離れているかを常に足したい為）
	static constexpr int PLAYER_PARTS_LOWER_BODY_COUNT = 6;          //下半身のパーツ数
	static constexpr int PLAYER_PARTS_HEAD_AND_BODY_COUNT = 2;       //頭と体の数
	static constexpr int PLAYER_NEXT_PARTS_COUNT = 1;                //次のパーツカウント
	static constexpr int PLAYER_NEXT_MOTION_COUNT = 1;               //モーション時の差分を求める時の次のモーションカウント
	static constexpr int PLAYER_BEFORE_MOTION_COUNT = 1;             //モーション時の差分が同じ時の前のモーションカウント
	static constexpr int PLAYER_FIRST_KEYSET_NUMBER = 0;             //最初のキーセットの初めの番号
	static constexpr int CREATE_GUN_COUNT = 2;                       //銃の個数
	 

	//========================================================
	//ボスに関するマクロ定義
	static constexpr int BOSS_PARTS_BODY_NUMBER = 0;                 //体の番号
	static constexpr int BOSS_PARTS_RIGHTHAND_NUMBER = 5;            //右手の番号
	static constexpr int BOSS_PARTS_LEFTHAND_NUMBER = 9;             //左手の番号
	static constexpr int BOSS_PARTS_WAIST_NUMBER = 10;               //腰の番号
	static constexpr int BOSS_PARTS_SHOULDER_FROM_HAND = 4;          //肩から手のFor文を回す際0,1,2,3の順（肩、上腕、下腕、手）で回す用
	static constexpr int BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;    //右肩から右手のFor文を回したい時の値（０～３の場合、右肩からは２番以上なのでどれくらい離れているかを常に足したい為）
	static constexpr int BOSS_PARTS_LEFT_SHOULDER_FROM_HAND = 6;     //左肩から右手のFor文を回したい時の値（０～３の場合、左肩からは６番以上なのでどれくらい離れているかを常に足したい為）
	static constexpr int BOSS_PARTS_LOWER_BODY_COUNT = 6;            //下半身のパーツ数
	static constexpr int BOSS_PARTS_HEAD_AND_BODY_COUNT = 2;         //頭と体の数
	static constexpr int BOSS_NEXT_PARTS_COUNT = 1;                  //次のパーツカウント
	static constexpr int BOSS_NEXT_MOTION_COUNT = 1;                 //モーション時の差分を求める時の次のモーションカウント
	static constexpr int BOSS_BEFORE_MOTION_COUNT = 1;               //モーション時の差分が同じ時の前のモーションカウント
	static constexpr int BOSS_FIRST_KEYSET_NUMBER = 0;               //最初のキーセットの初めの番号



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
		Key aKey[MAX_PARTS];        //キー数(パーツ分確保)
	}KeySet;

	//モーションの構造体
	typedef struct
	{
		bool Loop;                  //モーションがループするかどうか判定用
		int NumKey;                 //キーの総数
		KeySet KeySet[MAX_KEYSET];  //モーションのキーセット（モーション時のキーセットの数）
	}MotionSet;

	//モーション情報を確保する構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //向き
	}SAVEMODELINFO;

	//キャラクターの情報を保管する変数
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_PARTS], m_pSaveModelPrtInfoBoss[MAX_BOSSPARTS];   //モデルパーツの情報のポインター
	D3DXVECTOR3 SaveMotionPos[MAX_PARTS], SaveMotionPosBoss[MAX_BOSSPARTS];                 //各パーツの位置情報を確保する変数
	D3DXVECTOR3 SaveMotionRot[MAX_PARTS], SaveMotionRotBoss[MAX_BOSSPARTS];                 //各パーツの向き情報を獲得する変数
	MotionSet MotionSetPlayer[NUM_MOTION], MotionSetBoss[NUM_MOTIONBOSS];                  //各モーションの種類を格納する変数

	int m_nMotionFrameBoss;            //モーション時のフレームをカウントするための変数
	int MotionCount, MotionCountBoss;  //現在のモーションをカウントするための変数(Keyカウント)

	bool m_bMotionType, m_bMotionBossType;       //特殊なモーションかどうかを判定する為の変数
};