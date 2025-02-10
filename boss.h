//================================================
//
//ボスのクラス管理[boss.h]
//Auther:Haruki Chiba
//
//================================================


#pragma once


//================================================
//インクルード
#include "character.h"
#include "enemycharacter.h"
#include<vector>


//==================================================================
//ボスの処理
class CBoss : public CCharacter
{
public: //アクセス可能

	CBoss(int nPriority = DEFAULT_PRIORITY1);   //コンストラクタ
	~CBoss()override;                           //デストラクタ
	HRESULT Init()override;                     //初期化処理
	void Uninit()override;                      //破棄処理
	void Update() override;                     //更新処理
	void Draw()override;                        //描画処理
	void AttackPattern();                       //攻撃の種類ごとの関数
	void AttackPattern001();                    //攻撃の種類ごとの関数
	void StatusInit();                          //内部の変数の初期化処理関数
	void AttackPatternSelect();                 //攻撃の種類を選択する関数
	void Collision();                           //当たり判定処理関数
	void SpecialAttack();                       //必殺技

	float PopX();                               //値を削除
	float PopY();                               //値を削除

	static CBoss* Create(D3DXVECTOR3 pos);

private: //アクセス不可
	//マクロ定義 （constexprでコンパイル時に初期化）
	static constexpr  int MAX_VECTOR_SIZE = 50;                  //vector配列の最大数
	static constexpr  int DIE_FRAME = 180;                       //次のシーンへ行くまでの時間
	static constexpr  int INIT_WICHI_SIDE_NUMBER = -1;           //左右どちらの位置に居るかの初期番号
	static constexpr  int WICHI_SIDE_LEFT_NUMBER = 0;            //左右どちらの位置に居るかの左側の番号
	static constexpr  int WICHI_SIDE_RIGHT_NUMBER = 1;           //左右どちらの位置に居るかの右側の番号

	static constexpr int COOLTIME = 120;                         //攻撃のクールタイムの設定

	static constexpr int DROP_ATTACK_NUMBER = 0;                 //落下攻撃の呼ぶ番号
	static constexpr int FIRE_ATTACK_NUMBER = 1;                 //炎エフェクトの攻撃の呼ぶ番号
	static constexpr int SPECIAL_ATTACK_NUMBER = 2;              //必殺技の呼ぶ番号
	static constexpr int NONE_ATTACK_NUMBER = 3;                 //攻撃を呼ばない番号

   //==============================================
   //攻撃パターン１の時のマクロ定義
	static constexpr  int ATTACKPATTEN1_FRAME_1 = 30;                      //第一行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_2 = 140;                     //第二行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_3 = ATTACKPATTEN1_FRAME_2+1; //第三行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_4 = 162;                     //第四行動時のフレーム
	static constexpr  int ATTACKPATTEN1_FRAME_5 = 170;                     //第五行動時のフレーム

	static constexpr  float MAX_DROP_MOVE_Y_SPEED_1 = 0.35f;               //Y軸のボスの落ちる移動速度を設定
	static constexpr  float MAX_MOVE_SPEED_IN_PLAYER_1 = 12.0f;            //落下攻撃時プレイヤーに向かう速さ
	static constexpr float CREATE_BULLET_PLUS_POS_X = 100.0f;              //弾の生成時のX軸の位置を加算する値


   //==============================================
   //攻撃パターン２の時のマクロ定義
	static constexpr  int ATTACKPATTEN2_FRAME_1 = 40;                      //第一行動時のフレーム
	static constexpr  int ATTACKPATTEN2_FRAME_2 = 120;                     //第二行動時のフレーム
	static constexpr  int ATTACKPATTEN2_FRAME_3 = ATTACKPATTEN2_FRAME_2+1; //第三行動時のフレーム
	static constexpr  int ATTACKPATTEN2_FRAME_4 = 160;                     //第四行動時のフレーム

	static constexpr  float MAX_DROP_MOVE_Y_SPEED_2 = 0.25f;               //Y軸のボスの落ちる移動速度を設定
	static constexpr  float MAX_MOVE_SPEED_IN_PLAYER_2 = 8.0f;             //炎攻撃時プレイヤーに向かう速さ
	static constexpr  float MAX_MOVE_SPEED_SIDE = 0.1f;                    //左右のどちらかにに移動する時の速さ


   //==============================================
   //攻撃パターン３の時のマクロ定義
	static constexpr  int ATTACKPATTEN3_FRAME_1 = 20;                      //第一行動時のフレーム
	static constexpr  int ATTACKPATTEN3_FRAME_2 = 60;                      //第二行動時のフレーム
	static constexpr  int ATTACKPATTEN3_FRAME_3 = ATTACKPATTEN3_FRAME_2+1; //第三行動時のフレーム

	static constexpr  float MAX_MOVE_SPEED_IN_PLAYER_3 = 10.0f;   //必殺技時プレイヤーに向かう速さ
	static constexpr  float SHOT_IN_GUM_PLUS_POS_X = 300.0f;      //必殺技の銃のX軸の位置を加算する値


	static constexpr  int MINUS_SIZE_COUNT = -1;                  //サイズの総数からー１する為の物
	static constexpr  float MAX_MOVE_SPEED = 0.25f;               //ボスの移動速度を設定
	static constexpr  float MAX_TOUCH_DAMAGE = 0.0005f;           //ボスに触れている時のダメージ数


	int m_nCoolTime;                                              //攻撃終了後次の攻撃に行くまでの時間
	int m_nSize;                                                  //vectorの配列数を取得するための変数
	int m_nWhichSideNumber;                                       //左右のどちらに居るかを数字で渡すための変数

	bool m_bOneCreateFlag;                                        //衝撃波を１回のみ呼ぶための

	//vectorに関する変数										    
	std::vector<float> m_nSaveData;                               //配列情報を確保する為の変数
	std::vector<float> m_nDataX;                                  //X軸用のデータを保管する用の変数
	std::vector<float> m_nDataY;                                  //Y軸用のデータを保管する用の変数
};
