//======================================
//
//弾のクラス管理[bullet.h]
//Auther:Chiba Haruki
//
//======================================


#pragma once


//======================================
//インクルード
#include "object3D.h"


//============================================================================
//弾の管理の基底クラス
//============================================================================
class CManagerBullet : public CObject3D
{
public: //外部からアクセス可能
	CManagerBullet(int nPriority = DEFAULT_PRIORITY);               //引数付きコンストラクタ
	~CManagerBullet()override;                                      //デストラクタ
	HRESULT Init()override;                                         //初期化処理
	void Uninit()override;                                          //終了処理
	void Update()override;                                          //更新処理
	void Draw()override;                                            //描画処理
	void SetInfo(D3DXVECTOR3 m_pos, D3DXVECTOR3 m_move, int nLife); //弾の位置に関する設定処理

	//純粋仮想関数にすることで基底クラスの処理をそのまま処理する
	virtual void CallEffect(bool bUse) = 0;  //エフェクト呼ぶ処理
	virtual void CollisionOnObject() = 0; ;  //オブジェクトとの当たり判定

	static CManagerBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, CObject3D::TYPE type); //3D弾の生成処理


	//============================
	//マクロ定義 （constexprでコンパイル時に初期化）
	 static constexpr  float MAX_BULLET3D_SIZE_X = 40.0f; //3D弾のX軸の大きさ
	 static constexpr  float MAX_BULLET3D_SIZE_Y = 40.0f; //3D弾のY軸の大きさ
	 static constexpr  float MAX_BULLET3D_SIZE_Z = 40.0f; //3D弾のZ軸の大きさ
	 static constexpr  int SET_BULLET_LIFE = 60;          //ライフの最大数

private: //アクセス不可能
    //マクロ定義 （constexprでコンパイル時に初期化）
	static constexpr int GREEN = 160;                     //緑色
	 static constexpr  int MINUS_ALPHA = 5;               //アルファ値を減算
	 static constexpr  float INIT_ROTY = 3.14f;           //ｙ軸の向き
};


//============================================================================
//プレイヤー通常弾のクラス
class CBullet3D : public CManagerBullet
{
public: //外部からアクセス可能
	CBullet3D(int nPriority = DEFAULT_PRIORITY);   //引数付きコンストラクタ
	~CBullet3D()override;                          //デストラクタ
	//void Update()override;                       //更新処理
	void CallEffect(bool bUse);                    //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                      //オブジェクトとの当たり判定

private: //アクセス不可能
	 //マクロ定義 （constexprでコンパイル時に初期化）
	static constexpr int MINUS_ENEMY000_LIFE = 1;              //敵000のライフを減らす値
	static constexpr int MINUS_ENEMY001_LIFE = 1;              //敵001のライフを減らす値
	static constexpr int MINUS_ENEMYMOTION001_LIFE = 1;        //モーション付きの敵001のライフを減らす値
	static constexpr int CREATE_PLUS_NUMBER = 1;               //生成数を取得する際の生成数に＋１する為の値

	static constexpr int BOSS_PARTS_RIGHT_THIGHS = 11;         //ボスの右太もものパーツ番号
	static constexpr int BOSS_PARTS_RIGHT_KNEES = 12;          //ボスの右ふくらはぎのパーツ番号
	static constexpr int BOSS_PARTS_RIGHT_FOOT = 13;           //ボスの右足のパーツ番号

	static constexpr float  ADJUST_HIT_MOTIONENENY001 = 0.5f;  //モーション付きの敵001の当たり判定の調整値
	static constexpr float  ADJUST_HIT_CAMERA_UP = 1.5f;       //監視カメラ上部分の当たり判定の調整値
	static constexpr float  MINUS_BOSS_HPGAGE = 0.01f;         //ボスのHPゲージを減らす値
	static constexpr float ADJUST_ENEMY001_HIT = 0.5f;         //敵001の当たり判定の調整値
	static constexpr float ADJUST_ENEMY002_HIT = 0.5f;         //敵002の当たり判定の調整値
};


//============================================================================
//敵の通常弾のクラス
class CEnemyBullet : public CManagerBullet
{
public: //外部からアクセス可能
	CEnemyBullet(int nPriority = DEFAULT_PRIORITY);  //引数付きコンストラクタ
	~CEnemyBullet()override;                         //デストラクタ
	void Update()override;                           //更新処理
	void CallEffect(bool bUse);                      //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                        //オブジェクトとの当たり判定


	//============================
	//情報の取得
	static float& GetAdditionPosY() { return m_fAdditionPosY; }                             //現在のY軸の位置を取得


	//============================
	//情報の設定
	static void SetAdditionPosY(float fAdditionPosY) { m_fAdditionPosY = fAdditionPosY; }   //現在のY軸の位置を設定
	static float& SetAddjustAdditionPosY() { return m_fAdditionPosY; }                      //値を変更したいときの設定


	//============================
	//マクロ定義
	 static constexpr  float PLUS_ROT_Y = 7.0f;               //Y軸の向きを減算していく
	 static constexpr  float MAX_ENEMYBULLET_SIZE_X = 40.0f;  //X軸の大きさ
	 static constexpr  float MAX_ENEMYBULLET_SIZE_Y = 40.0f;  //Y軸の大きさ
	 static constexpr  float MAX_ENEMYBULLET_SIZE_Z = 40.0f;  //Z軸の大きさ

private: //外部からアクセス不可能
    //マクロ定義
	 static constexpr  int BLUE = 200;                        //青色
	 static constexpr  int MINUS_ALPHA = 5;                   //アルファ値を減算
													         
	 static constexpr  float ADJUST_HIT = 0.5;                //当たり判定の調整値
	 static constexpr  float  MINUS_PLAYER_HPGAGE = 0.05f;    //プレイヤーのHPゲージを減らす値
														     
	static float m_fAdditionPosY;                             //rot.yに値を追加していくための変数
};


//============================================================================
//敵の通常弾のクラス
class CEnemyBulletBattleShip : public CManagerBullet
{
public: //外部からアクセス可能
	CEnemyBulletBattleShip(int nPriority = DEFAULT_PRIORITY);  //引数付きコンストラクタ
	~CEnemyBulletBattleShip()override;                         //デストラクタ
	void Update()override;                                     //更新処理
	void CallEffect(bool bUse);                                //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                                  //オブジェクトとの当たり判定


	//============================
	//マクロ定義
	static constexpr float PLUS_ROT_Y = 7.0f;                  //Y軸の向きを減算していく
	static constexpr float MAX_ENEMYBULLET_SIZE_X = 40.0f;     //X軸の大きさ
	static constexpr float MAX_ENEMYBULLET_SIZE_Y = 40.0f;     //Y軸の大きさ
	static constexpr float MAX_ENEMYBULLET_SIZE_Z = 40.0f;     //Z軸の大きさ

private: //外部からアクセス不可能
	//マクロ定義
	static constexpr  int BLUE = 200;                          //青色
	static constexpr  int MINUS_ALPHA = 5;                     //アルファ値を減算
	static constexpr  int SET_BULLET_LIFE = 90;                //ライフの最大値
	static constexpr int MAX_FRAME = 10;                       //フレームの最大数
														       
	static constexpr  float ADDJUST_HIT = 1.0;                 //当たり判定の調整値
	static constexpr  float  MINUS_PLAYER_HPGAGE = 0.05f;      //プレイヤーのHPゲージを減らす値
	static  constexpr float MINUS_POS_Y = -2.5f;               //Y軸の位置を減算していく値
	
};


//============================================================================
//ボスの通常弾のクラス
class CBossBullet : public CManagerBullet
{
public: //外部からアクセス可能
	CBossBullet(int nPriority = DEFAULT_PRIORITY);        //引数付きコンストラクタ
	~CBossBullet()override;                               //デストラクタ
	void Update()override;                                //更新処理
	void CallEffect(bool bUse);                           //エフェクトの処理を呼ぶ関数 (引数でエフェクトを追加するかどうか判定)
	void CollisionOnObject();                             //オブジェクトとの当たり判定


	//============================
	//マクロ定義
	static constexpr float MAX_BOSSBULLET_SIZE_X = 40.0f; //X軸の大きさ
	static constexpr float MAX_BOSSBULLET_SIZE_Y = 40.0f; //Y軸の大きさ
	static constexpr float MAX_BOSSBULLET_SIZE_Z = 40.0f; //Z軸の大きさ


private: //外部からアクセス不可能
	//マクロ定義
	static constexpr int BLUE = 200;                      //青色
	static constexpr int MINUS_ALPHA = 5;                 //アルファ値を減算
														  
	static constexpr float  MINUS_PLAYER_HPGAGE = 0.05f;  //プレイヤーのHPゲージを減らす値
	static constexpr float  MINUS_POSY = 2.0f;            //Y軸の位置を減算する値
	static constexpr float PLUS_POS_Y = 200.0f;           //エフェクトのY軸の生成位置を加算する値
	static constexpr float ADJUST_HIT = 0.5f;             //当たり判定時の調整値
};

