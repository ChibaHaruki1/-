//=====================================================
//
//モーション付きの敵のクラス管理[enemyinmotion.h]
//Auther;Haruki Chiba
//
//=====================================================


#pragma once


//=====================================================
//インクルード
#include "enemycharacter.h"


//================================================================================
//モーション敵のマネージャー管理クラス
class CManagerEnemyInMotion : public CEnemyCharacter
{
public: //アクセス可能

	CManagerEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);                     //コンストラクタ
	~CManagerEnemyInMotion()override;                                             //デストラクタ
	HRESULT Init()override;                                                       //初期化処理
	void Uninit()override;                                                        //破棄処理
	void Update() override;                                                       //更新処理
	void Draw()override;                                                          //描画処理

	static CManagerEnemyInMotion* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);    //生成処理

protected:
	int m_nJumpFrame;                            //飛ぶまでの時間
	int JumpNumber;                              //行きだけ飛ぶように番号をつける為の変数
	int JumpRecastTime;                          //飛ぶ為のリキャストタイム（連続で触れている判定になる為その修正）

	//マクロ定義
	 static constexpr  float MAX_SPEED = 2.0f;     //追いかける速度
	 static constexpr  int MAX_BUULET_SPEED = 30;  //弾の速さ

};





//================================================================================
//モーション付きの敵（特殊）
class CEnemyInMotion001 : public CManagerEnemyInMotion
{
public: //アクセス可能
	CEnemyInMotion001(int nPriority = DEFAULT_PRIORITY1);              //コンストラクタ
	~CEnemyInMotion001()override;                                      //デストラクタ
	void Update() override;                                            //更新処理
	void Draw()override;                                               //描画処理
	void AdjustmentBulletAndRot();                                     //プレイヤーに対する機体と弾の調整処理
	void WhenCollisionBlock();                                         //地面用ブロックに触れている時の処理
	void Correctionrot();                                              //向きを修正する関数
	void PlayerBloWwaway();                                            //吹き飛ばす処理
	void Die();                                                        //死亡時の処理

private:
	//マクロ定義
	static constexpr  int MAX_LIFE = 10;                              //ライフの最大値
	static constexpr  int PLUS_SCORE = 2000;                          //スコアの加算値
	static constexpr  int MIN_RANDOM1 = 150;                          //乱数1の最小値
	static constexpr  int MAX_RANDOM1 = MIN_RANDOM1 * 2;              //乱数1の最大値
	static constexpr  int MIN_RANDOM2 = 50;                           //乱数2の最小値
	static constexpr  int MAX_RANDOM2 = MIN_RANDOM2 * 2;              //乱数2の最大値
	static constexpr  int MAX_FRAME = 45;                             //フレームの最大数
	static constexpr  int MAX_JUMPFRAME = 40;                         //飛ぶフレームの最大数
	static constexpr  int MAX_JUMPRECASTTIME = 5;                     //飛んだあとの時間


	//==============================================
	//行動パターン１の時の行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_1 = 1;                           //第一行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_2 = 25;                          //第二行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_3 = ATTACKPATTEN1_FRAME_2 + 1;   //第三行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_4 = 50;                          //第四行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_5 = ATTACKPATTEN1_FRAME_4 + 1;   //第五行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_6 = 75;                          //第六行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_7 = ATTACKPATTEN1_FRAME_6 + 1;   //第七行動時のフレーム
																			   
																			   
	//==============================================						   
	//行動パターン２の時の行動時のフレーム								       
	static constexpr  int ATTACKPATTEN2_FRAME_1 = 1;                   //第一行動時のフレーム
	static constexpr  int ATTACKPATTEN2_FRAME_2 = 20;                  //第二行動時のフレーム

	static constexpr float PLAYER_MOVE = 10.0f;                        //プレイヤーの移動量を増減させる値(この方が１つにまとまるからいい？)
										

	static constexpr  int JUMP_NUMBER_MINUS_1 = -1;                    //飛ぶ番号ー１番
	static constexpr  int JUMP_NUMBER_0 = 0;                           //飛ぶ番号０番
																	
	static constexpr  float COLLISION_RANGE_PLAYER_1 = 10.0f;          //プレイヤーとの当たり範囲を設定１つ目
	static constexpr  float COLLISION_RANGE_PLAYER_2 = 4.0f;           //プレイヤーとの当たり範囲を設定２つ目
	static constexpr  float COLLISION_RANGE_PLAYER_3 = 1.2f;           //プレイヤーとの当たり範囲を設定３つ目

	static constexpr  float CREATE_BULLET_PLUS_POS_X = 100.0f;         //生成した弾のX軸の位置を加算する値
	static constexpr  float CREATE_BULLET_PLUS_POS_Y = 10.0f;          //生成した弾のY軸の位置を加算する値
																	
	static constexpr  float ADJUST_PRTAS_ROTX = 0.01f;                 //パーツのX軸の向きを調整する値
	static constexpr  float ADJUST_BULLET_ROTY = 0.3f;                 //弾のY軸の向きを調整する値
	static constexpr  float MULTIPLICATIOB_ADJUST_BULLET_ROTY = 4.0f;  //弾のY軸の向きを調整する掛け算の値
	static constexpr  float IF_ADJUST_BULLET_ROTY = 3.0f;              //弾のY軸の向きを調整する条件式の掛け算の値
	static constexpr  float ADJUST_FIELD_BLOCK = 1.1f;                 //地面用ブロックとの当たり判定の調整値
	static constexpr  float ADJUST_BLOCK = 1.01f;                      //ブロックとの当たり判定の調整値
																	
	static constexpr  float MAX_JUMP_POWER = 15.0f;                    //ジャンプ力
																	
	static constexpr  float MAX_EXPLOSION_SIZE1 = 200.0f;              //爆発エフェクトの大きさの値１
	static constexpr  float MAX_EXPLOSION_SIZE2 = 300.0f;              //爆発エフェクトの大きさの値２

	static constexpr  float PLUS_ROT_Y = 1.0f;                         //向きの条件式の値を加算する値
																	
	static constexpr  float MAX_DAMAGE = 0.1f;                         //ダメージ数
																	
	int m_nHitFrame;                                                   //プレイヤーと当たった時のリキャストタイム
	bool m_bHit;                                                       //当たったかどうかの判定用変数
};


//================================================================================
//モーション付きの敵（通常）
class CEnemyInMotion002 : public CManagerEnemyInMotion
{
public: //アクセス可能
	CEnemyInMotion002(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CEnemyInMotion002()override;                           //デストラクタ
	void Update() override;                                 //更新処理	
	void Draw()override;                                    //描画処理

private:
	//マクロ定義
	static constexpr  float COLLISION_RANGE_PLAYER_1 = 10.0f;          //プレイヤーとの当たり範囲を設定１つ目
	static constexpr  float COLLISION_RANGE_PLAYER_2 = 1.5f;           //プレイヤーとの当たり範囲を設定２つ目

	static constexpr float DAMAGE = 0.005f;                            //ダメージ数

};
