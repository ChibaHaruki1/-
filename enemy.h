//==================================
//
//敵のクラス管理[enemy.h]
//Auther:Chiba Haruki
//
//==================================


#pragma once


//==================================
//インクルード
#include "objectX.h"
#include "enemycharacter.h"


//==========================================================
//敵のマネージャー管理クラス
class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = CObject::DEFAULT_PRIORITY);            //引数付きコンストラクタ
	~CManagerEnemy()override;                                            //デストラクタ
	HRESULT Init()override;                                              //初期化処理
	void Uninit()override;                                               //終了処理
	void Update() override;                                              //更新処理
	void Draw()override;                                                 //描画処理
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type);  //生成処理
};


//==========================================================
//敵のクラス
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX(int nPriority = DEFAULT_PRIORITY1);        //コンストラクタ
	~CEnemyX()override;                                //デストラクタ
	void Update()override;                             //更新処理

private:
	//マクロ定義
	static constexpr  int MAX_LIFE = 1;                             //ライフの最大値
	static constexpr  int PLUS_SCORE = 1000;                        //加算するスコア値
	static constexpr  int MAX_BUULET_SPEED = 30;                    //弾の速さ
	static constexpr  int SET_BULLET_LIFE = 120;                    //ライフの最大数

	static constexpr  float COLLISION_RANGE_PLAYER = 65.0f;         //プレイヤーとの当たり範囲を設定
	static constexpr  float MAX_SPPED = 2.0f;                       //移動速度
	static constexpr  float MAX_ENEMY_DAMAGE = 0.001f;              //ダメージ数
	static constexpr  float MAX_FARME = 60.0f;                      //フレームの最大数
	static constexpr  float CREATE_BULLET_0_MINUS_POS_X = -250.0f;  //初めに生成した弾のX軸の位置を減算する値
	static constexpr  float CREATE_BULLET_1_PLUS_POS_X = 350.0f;    //次に生成した弾のX軸の位置を加算する値
	static constexpr  float CREATE_BULLET_PLUS_POS_Y = 70.0f;       //生成した弾のY軸の位置を加算する値
	static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;    //爆発エフェクトのY軸の位置を加算する値
};


//==========================================================
//敵001のクラス
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CEnemy001X()override; 							//デストラクタ
	void Update()override;							//更新処理


	//=======================
	//マクロ定義
	 static constexpr  int MAX_ENEMY001_LIFE = 3;                  //ライフの最大値
													               
private:											               
	//マクロ定義									                  
	 static constexpr  int PLUS_SCORE = 100;                       //スコアの加算値
													               
	 static constexpr  float MAX_DAMAGE = 0.005f;                  //プレイヤーに与えるダメージ数
	 static constexpr  float PLUS_ROT_Y = 0.1f;                     //Y軸の向きを加算する値
	 static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;  //爆発エフェクトのY軸の位置を加算する値
};


//==========================================================
//敵002のクラス
class CEnemy002X : public CManagerEnemy
{
public:
	CEnemy002X(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CEnemy002X()override; 							//デストラクタ
	void Update()override;							//更新処理
	void Move();                                    //行動処理


	//=======================
	//マクロ定義
	 static constexpr  int MAX_ENEMY002_LIFE = 3;                  //ライフの最大値
													               
													               
private:											               
	//マクロ定義										              
	 static constexpr  int PLUS_SCORE = 200;                       //スコアの加算値

	 static constexpr  float ATTACKPATTEN_FRAME_1 = 30.0f;	                      //第一行動時のフレーム
	 static constexpr  float ATTACKPATTEN_FRAME_2 = ATTACKPATTEN_FRAME_1 * 2.0f;  //第二行動時のフレーム
													               
	 static constexpr  float MAX_DAMAGE = 0.005f;                  //プレイヤーに与えるダメージ数
	 static constexpr  float PLUS_ROT_Y = 0.1f;                     //Y軸の向きを加算する値
	 static constexpr  float ADJUST_POSY = 10.0f;                  //Y軸の位置を加算する値
	 static constexpr  float EXPLOSION_EFFECT_PLUS_POS_Y = 50.0f;  //爆発エフェクトのY軸の位置を加算する値
};
