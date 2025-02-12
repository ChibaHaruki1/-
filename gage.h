//=====================================
//
//ゲージに関するクラス管理[gage.h]
//Auther:Haruki Chiba
//
//=====================================

#pragma once


//=====================================
//インクルード
#include "object2D.h"
#include "object3D.h"


//==================================================
//燃料ゲージ
class CFuelGage : public CObject3D
{
public:
	CFuelGage(int nPriority = DEFAULT_PRIORITY);          //コンストラクタ;
	~CFuelGage();                                         //コンストラクタ;
	HRESULT Init()override;                               //初期化処理
	void Uninit()override;                                //破棄処理
	void Update()override;                                //更新処理
	void Draw()override;                                  //描画処理

	static CFuelGage* Create();                           //生成処理

	inline bool& GetUse() { return m_bUse; }              //使われているかどうかの判定を取得する
	inline bool& GetChage() { return m_bCharge; }         //チャージが完了しているどうかの判定を取得する

private:
	//マクロ定義
	 static constexpr  int RED = 255;          //赤色
	 static constexpr  int GREEN = 255;        //緑色
	 static constexpr  int BLUE = 255;         //青色
	 static constexpr  int MAX_ALPHA = 255;    //アルファ値の最大数
	 static constexpr  int MIN_ALPHA = 10;     //アルファ値の最小数
	 static constexpr  int MINUS_ALPHA = 5;    //アルファ値の減算値

	 static constexpr  float MAX_SIZEX = 15.0f;             //Xのの大きさ
	 static constexpr  float MAX_SIZEY = 100.0f;            //Y軸の大きさ
	 static constexpr  float MAX_SIZEZ = 20.0f;             //Z軸の大きさ
	 static constexpr  float MIN_SIZEY = 10.0f;             //Y軸の最小値
	 static constexpr  float ADJUST_POSX = 50.0f;           //X軸の位置の調整値
	 static constexpr  float ADJUST_POSY = 80.0f;           //Y軸の位置の調整値
	 static constexpr  float MAX_MAINAS_GAGESPEED = 0.5f;   //ゲージの減る速さ
	 static constexpr  float MAX_PLUS_GAGESPEED = 0.5f;     //ゲージの増える速さ
	 static constexpr  float MAX_PLUS_PLAYER_MOVE = 1.0f;   //プレイヤー移動量の増える速さ
	 static constexpr  float MAX_PLAYER_GRAVITY = 1.0f;     //プレイヤーの重力の限界値


	bool m_bUse;                                          //ゲージを減らすかどうか判定するための変数
	bool m_bCharge;
};


//==================================================
//ゲージの管理クラス
//==================================================
class CManagerGage : public CObject2D
{
public:  //アクセス可能
	CManagerGage(int nPriority = DEFAULT_PRIORITY);           //コンストラクタ;
	~CManagerGage()override;                                  //デストラクタ
	HRESULT Init()override;                                   //初期化処理
	void Uninit()override;                                    //破棄処理
	void  Update()override;                                   //更新処理
	void Draw()override;                                      //描画処理
	static CManagerGage* Create(CObject2D::TYPE type);        //ゲージの生成
	static CManagerGage* CreateLeave(CObject2D::TYPE type);   //残すゲージの生成


	//===================================
	//情報の取得
	//（bullet.cppなどで減らす）
	float& GetPlayerHPSizeX() { return m_fHPSizeX; }          //プレイヤーのHPゲージを取得
	float& GetBossHPSizeX() { return m_fBossHPSizeX; }        //ボスのHPゲージを取得
	float& GetSaveSizeX() { return m_fSaveSizeX; }            //ゲージの保管を取得


	//========================
	//マクロ定義
	static constexpr float MAX_PLAYER_HP_SIZE = 400.0f;       //プレイヤーのゲージ最大数


protected://継承クラスのみアクセス可能
	float m_fSaveSizeX;


	//===================================
	//マクロ定義
	static constexpr float MAX_PLAYERGAGE_SIZE_Y = 40.0f; //プレイヤーのゲージのY軸の大きさ
	static constexpr float MAX_PLAYERGAGE_SIZE_Z = 70.0f; //プレイヤーのゲージのZ軸の大きさ

private:  //アクセス不可能
	//マクロ定義
	static constexpr int CRETAE_PRIORITY = 1;       //生成時のプライオリティの番号
	static constexpr int CRETAE_LEAVE_PRIORITY = 0; //残すゲージの生成時のプライオリティの番号

	float m_fHPSizeX;                               //プレイヤーのHPゲージの大きさを管理する用の変数
	float m_fBossHPSizeX;                           //ボスのHPゲージの大きさを管理する用の変数
};


//==================================================
//プレイヤーのHPゲージ
class CPlayerHPGage : public CManagerGage
{
public:
	CPlayerHPGage(int nPriority = DEFAULT_PRIORITY);   //コンストラクタ
	~CPlayerHPGage()override;                          //デストラクタ
	HRESULT Init()override;                            //初期化処理
	void Update()override;                             //更新処理

private:
	//マクロ定義
	static  constexpr float SIZE_Y = 40.0f;            //Y軸の１番目の大きさを設定
	static  constexpr float SIZE_Y1 = 70.0f;           //Y軸の２番目の大きさを設定
	static constexpr float MINUS_HPSIZEX = 1.8f;       //HPゲージの減算値
};
	

//==================================================
//ボスのHPゲージ
class CBossHPGage : public CManagerGage
{
public:
	CBossHPGage(int nPriority = DEFAULT_PRIORITY);     //コンストラクタ
	~CBossHPGage()override;                            //デストラクタ
	HRESULT Init()override;                            //初期化処理
	void Update()override;                             //更新処理


	//========================
	//マクロ定義
	static constexpr float MINUS_SIZE_X1 = -40.0f;     //X軸の２番目の大きさの減算調整値

private:
	//マクロ定義
	static constexpr float ADJUST_POSY = 40.0f;        //Y軸の位置の調整値
	static constexpr float MINUS_HPSIZEX = 1.3f;       //HPゲージの減算値
};


//==================================================
//プレイヤーのHPゲージを残す
class CPlayerHPGageLeave : public CManagerGage
{
public:
	CPlayerHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CPlayerHPGageLeave()override;                         //デストラクタ
	HRESULT Init()override;                                //初期化処理
};


//==================================================
//ボスのHPゲージを残す
class CBossHPGageLeave : public CManagerGage
{
public:
	CBossHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CBossHPGageLeave()override;                         //デストラクタ
	HRESULT Init()override;                              //初期化処理
};

