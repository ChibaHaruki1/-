//========================================
//
//Xオブジェクトクラス管理[objectmanagerX.h]
//Auther:Chiba Haruki
//
//========================================


#pragma once


//========================================
//インクルード
#include "main.h"


//全てを管理するので仮想関数（純粋仮想関数）
class CObjectManagerX
{
public:

	//各タイプの設定
	enum class TYPE
	{
		NONE = 0,                    //無し
		ENEMY,                       //敵
		ENEMY001,                    //敵001
		ENEMY002,                    //敵002
		ENEMYINMOTION,               //モーション付きの敵
		ENEMYINMOTION001,            //モーション付きの敵001
		ENEMYINMOTION002,            //モーション付きの敵002

		BOSS,                        //ボス
		PLAYER,                      //プレイヤー
		FIELDBLOCK,                  //地面用ブロック
		GOUPBLOCK,                   //上に上がる用のブロック
		ROADBLOCK,                   //道用ブロック
		WALLROADBLOCK,               //壁兼道用ブロック
		WALLROADBLOCK_001,           //壁兼道用ブロック001
		SMALLBLOCK,                  //小さいブロック
		SMALLBLOCK_001,              //小さいブロック001
		UPWALLBLOCK,                 //上壁のブロック

		TELEPHONPOLE,                //電柱
		SURVEILLANCECAMERAUP,        //監視カメラの上部分
		SURVEILLANCECAMERADOWN,      //監視カメラの下部分
		SHOP,                        //店
		DEBRIS,                      //破片
		BREAKHOUSE,                  //壊れた家
		SPECEBATTLESHIP000,          //TYPE用のスペースシップ
		MAX
	};

	//ストラテジータイプの設定
	enum class STRATEGYTYPE
	{
		NONESTRATEGY = 0,     //無し
		FIELDBLOCK,             //ブロック０番
		GOUPBLOCK,			  //ブロック１番
		ROADBLOCK,			  //ブロック２番
		WALLROADBLOCK,			  //ブロック３番
		WALLROADBLOCK001,		  //ブロック３番の２個目
		SMALLBLOCK,			  //ブロック４番
		SMALLBLOCK001,		  //ブロック４番の２個目
		UPWALLBLOCK,			  //ブロック０番
		BLOCK006,			  //ブロック０番
		SPECEBATTLESHIP000,   //バトルシップの番号
		FINALBLOCK,           //最終ステージ用のブロック
		FINALCEILLING,        //最終ステージ用の天井
		WODDENBORAD,          //木の板群
	};

	CObjectManagerX(int nPriority = DEFAULT_PRIORITY1);                                                           //コンストラクタ
	virtual ~CObjectManagerX();                                                                                   //デストラクタ
	virtual HRESULT Init() = 0;                                                                                   //初期化
	virtual void Uninit() = 0;                                                                                    //終了処理
	virtual void Update() = 0;                                                                                    //更新処理
	virtual void Draw() = 0;                                                                                      //描画処理
	static void ReleaseAll();                                                                                     //全オブジェクトの解放
	static void UpdateAll();                                                                                      //全オブジェクトの更新
	static void DrawAll();                                                                                        //全オブジェクトの描画
	static CObjectManagerX* GetObjectManagerX(int nPri, int nIndex) { return m_apObjectManagerX[nPri][nIndex]; }  //オブジェクト取得
	TYPE GetType() { return m_type; }                                                                             //タイプ取得
	void SetType(TYPE type) { m_type = type; }                                                                    //タイプ設定
	void Release();                                                                                               //自分自身の解放


	//==================================================	                                          
	//マクロ定義					
	static constexpr int N_INIT_NUMBER = 0;                  //int型の初期化の値
	static constexpr int INIT_ALPHA = 255;                   //アルファ値の初期値
	static constexpr float F_INIT_NUMBER = 0.0f;             //float型の初期化の値

	static constexpr  int MAX_PARTS = 19;                    //プレイヤーのパーツ数
	static constexpr  int MAX_BOSSPARTS = 18;                //ボスのパーツ数
	static constexpr  int MAX_ENEMYPARTS = 20;               //敵の最大パーツ数
	static constexpr  int NUM_MOTION_KEY = 5;                //キーの数
	static constexpr  int WHILE_NUMBER = 1;                  //whileの（）の中の数

	static constexpr  float MAX_GRAVITY_G = 0.5f;            //重力の最大値
	static constexpr  float D3DX_PI_ORI = 1.57f;             //半円の角度
	static constexpr  float D3DX_PI_ORI_HALF = 1.57f * 0.5f; //半円の角度の半分(調整用)


protected:
	//マクロ定義
	 static constexpr  int MAX_OBJECTMANAGERX = 200;       //オブジェクトの最大数
	 static constexpr  int DEFAULT_PRIORITY1 = 3;          //デフォルトの描画順
	 static constexpr  int MAX_PRIORITY_MANAGER_OBJ = 4;   //描画順の最大数

private:
	static CObjectManagerX* m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX]; //全オブジェクトの管理
	int m_nPriority;  //自身のプライオリティ    
	int m_nID;        //自分自身のID
	TYPE m_type;      //オブジェクトタイプ

};


