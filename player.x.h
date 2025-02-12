//========================================
//
//プレイヤーのクラス管理[player.h]
//Author:chiba haruki
//
//========================================


#pragma once


//========================================
//インクルード
#include "main.h"
#include "input.h"
#include "camera.h"
#include "collision.h"
#include "field.h"
#include "ui.h"
#include "2d_ui.h"
#include "character.h"


class CPlayerX : public CCharacter
{
public: //アクセス可能

	CPlayerX(int nPriority = DEFAULT_PRIORITY1);                                    //コンストラクタ
	~CPlayerX()override;                                                            //デストラクタ
	HRESULT Init()override;                                                         //初期化処理
	void Uninit()override;                                                          //破棄処理
	void Update()override;                                                          //更新処理
	void Draw()override;                                                            //描画処理
	//void ObjectArrangement();                                                     //オブジェクトの配置処理（生成＆情報をファイルに書き込む）
	void KeySet();                                                                  //キーごとの処理をまとめる関数
	void ShopKeySet();                                                              //モードがSHOP時のキーごとの処理をまとめる関数
	void BlockJudgement();                                                          //ブロックとの判定
	void UIJudgement();                                                             //UIとの判定
	void Random();                                                                  //ランダム処理
	void Praticles();                                                               //パーティクルを出す処理
	void NormalStateSummarizeFunction();                                            //通常時の関数をまとめる関数
	void ShopStateSummarizeFunction();                                              //店に訪問時の関数をまとめる関数
	void CreateGun();                                                               //銃の生成インスタンスを呼ぶ
	void InstanceMakeNull();                                                        //instanceをnullptrにする処理
	void ShopInstanceMakeNullptr();                                                 //ショップで使用するインスタンスをnullptrにする
	void SelectGageUISize(float SIzeX, float SIze1X);                                //選択ゲージの大きさを設定する関数
	void SelectGageUISizeCalculation(const char* aSelect, float SIzeX, float SIze1X);  //選択ゲージの大きさを計算（加算や減算など）する関数
	void BlowAway();
	void HitAttack();                                                               //特定の攻撃を受けたときの処理
	void SceneMode(int nType);                                                      //sceneの分岐
	void NextStageMotion();                                                         //次のステージに行くと時のモーション処理		                    
	void NowCreateObjectUI();                                                       //現在作っているオブジェクトのUIを出す処理
	void NowCreateNumberObj();                                                      //番号で作るオブジェクトを指定する処理

	static CPlayerX* Create();                                                      //生成する


	//=====================================
	//CObjectXで使用する用の取得
	int& GetTelephonPoleCount() { return m_nTelephonCount; }                        //電柱の配列を取得
	int& GetAllTelephonPoleCount() { return m_nAllTelephonPoleCount; }              //全ての電柱の配列を取得
	int& GetRotNumber() { return m_nRotNumber; }                                    //プレイヤーの向きの番号を取得


	//=====================================
	//生成数を何度も取得しなくていいように保管する用の変数の設定
	void SetFieldBlockCount(int nFieldBlockCount) { m_nFieldBlock = nFieldBlockCount; }                 //地面用ブロックの生成数の設定
	void SetGoUpBlockCount(int nGoUpBlock) { m_nGoUpBlock = nGoUpBlock; }                              //地面用ブロックの生成数の設定
	void SetRoadBlockCount(int nRoadBlock) { m_nRoadBlock = nRoadBlock; }                              //道用ブロックの生成数の設定
	void SetWallRoadBlockCount(int nWallRoadBlock) { m_nWallRoadBlock = nWallRoadBlock; }              //壁兼道用ブロックの生成数の設定
	void SetWallRoadBlock001Count(int nWallRoadBlock001) { m_nWallRoadBlock001 = nWallRoadBlock001; }  //壁兼道用ブロック001の生成数の設定
	void SetSmalBlockCount(int nSmalBlock) { m_nSmalBlock = nSmalBlock; }                              //小さいブロックの生成数の設定
	void SetSmalBlock001Count(int nSmalBlock001) { m_nSmalBlock001 = nSmalBlock001; }                  //小さいブロック001の生成数の設定

	void SetLaserCount(int nLaserCount) { m_nLaserCount = nLaserCount; }                                //レーザーの生成数の設定


	//=====================================
	//マクロ定義
	static constexpr  int ROT_NUMBER_1 = 1; //向き番号１番
	static constexpr  int ROT_NUMBER_2 = 2; //向き番号２番

	static constexpr  float MAX_MOVESPEED = 3.0f;                //感性を減らした分の移動量の増加


private:
	//==========================================
	//マクロ定義
	static constexpr  int   MAX_TEXT_OBJECT = 2;                 //今配置ツールに設定されてるオブジェクトの数ー１（０スタートだから）
	static constexpr  int   MAX_BUULET_SPEED = 30;               //弾の速さ
	static constexpr  int   INIT_NUMBER = -1;                    //初期化の値
	static constexpr  int   LIFE = 1;                            //ライフ

	static constexpr  float   ADJUST_SELECT_SIZEY = 160.0f;      //選択ゲージのY軸の位置を加算する値
	static constexpr  float   MAX_GRAVITY = 50.0f;               //重力の最大値
	static constexpr  float   DIE_POS_Y = 4000.0f;               //死亡位置の設定値
	static constexpr  float   MAX_JUMPPAWER = 10.0f;             //飛ぶ力
	static constexpr  float   MAX_SPECIALATTACKCOUNT = 60 * 0;  //必殺技のリキャストタイム
	static constexpr  float   MAX_POS_NEXTSTAGE = 0.4f;          //次のステージへ行く時の位置の乗算値


	//============================================
	//シーンに関するマクロ定義
	static constexpr  int   SCENE_NEXT_STAGE = 1;                //次のシーンへ行く時の番号(順番通り)
	static constexpr  int   SCENE_DEBUG_STAGE = 2;               //次のシーンへ行く時の番号(あらかじめ決めたシーンへ)
	static constexpr  int   SCENE_DIE_STAGE = 3;                 //次のシーンへ行く時の番号(死亡時に行くシーンへ)


	//============================================
	//パーティクルに関するマクロ定義
	static constexpr int MIN_RANDOM = -50;                       //乱数の最小値
	static constexpr int MAX_RANDOM = 100;                       //乱数の最大値
	static constexpr int MAX_COL_RANDOM = 255;                   //色の乱数の最大値
	static constexpr int MAX_PARTICLE_FRAME = 4;                 //パーティクルフレームの最大値


	//============================================
	//死亡時のマクロ定義
	static constexpr  int   MAX_DIE_COUNT = 180;                 //死亡時のカウント
	static constexpr  int   MIN_DIE_RANDOM = -1;                 //死亡時の乱数の最小値
	static constexpr  int   MAX_DIE_RANDOM = 3;                  //死亡時の乱数の最大値

	static constexpr float DIE_FRAME_REDUCTION = 0.1f;           //死亡時のフレームの縮小値


	//============================================
	//ぶっ飛び処理時マクロ定義
	static constexpr  int   BLOWAWAY_FRAME_1 = 40;               //第一行動時のフレーム
	static constexpr  int   BLOWAWAY_FRAME_2 = 90;               //第二行動時のフレーム

	static constexpr  float   BLOWAWAY_PLUS_POS_X = 20.0f;       //X軸の飛ぶ距離
	static constexpr  float   BLOWAWAY_PLUS_POS_Y = 30.0f;       //Y軸の飛ぶ距離


	//============================================
	//行動時に関するマクロ定義
	static constexpr int GUN_FRAME_MOTION = 60;                               //銃を撃つフレーム

	static constexpr float RIGHT_BULLET_PLUS_POS_X = 240.0f;                  //弾のX軸の位置を加算する値
	static constexpr float LEFT_BULLET_MINUS_POS_X = -50.0f;                  //弾のX軸の位置を減算する値
	static constexpr float ROT_NUMBER_1_SPECIAL_EFFECT_PLUS_POS_Y = 220.0f;   //向き番号１番の必殺技のエフェクトのY軸の位置を加算する値
	static constexpr float ROT_NUMBER_2_SPECIAL_EFFECT_MINUS_POS_Y = -50.0f;  //向き番号２番の必殺技のエフェクトのY軸の位置を減算する値


	//============================================
	//ショップ時のマクロ定義
	static constexpr int MODE_SHOP_SELECT_COUNT = 2;                           //項目数（買う、売るの２つ何なので２）
	static constexpr int MODE_SHOP_UP_COUNT = -1;                              //選択ゲージが上に行った時戻る時の番号
	static constexpr int MODE_SHOP_DOWN_COUNT = 2;                             //選択ゲージが下に行った時戻る時の番号

	static constexpr float  MODE_SHOP_SELECT_GAGE_SIXE1_X = 50.0f;             //選択ゲージ１つ目のX軸の大きさ
	static constexpr float  MODE_SHOP1_SELECT_GAGE_SIXE2_X = 270.0f;           //１回目の選択ゲージ１つ目のX軸の大きさ
	static constexpr float  MODE_SHOP2_SELECT_GAGE_SIXE2_X = 150.0f;           //２回目の選択ゲージ２つ目のX軸の大きさ

	static constexpr float  MODE_SHOP_SELECT_GAGE_PLUS_SIZE_X = 400.0f;        //ショップ時の選択ゲージのX軸の大きさを増加


	//=============================================
	//買い物時のマクロ定義
	static constexpr int MODE_BUY_SELECT_COUNT = 4;                            //項目数
	static constexpr int MODE_BUY_UP_COUNT = -1;                               //選択ゲージが上に行った時戻る時の番号
	static constexpr int MODE_BUY_DOWN_COUNT = 4;                              //選択ゲージが下に行った時戻る時の番号

	static constexpr float  MODE_BUY_SELECT_GAGE_SIXE1_Y = 50.0f;              //選択ゲージ１つ目のy軸の大きさ
	static constexpr float  MODE_BUY_SELECT_GAGE_SIXE2_Y = 150.0f;             //選択ゲージ２つ目のy軸の大きさ


	//=============================================
	//銃の生成マクロ定義
	static constexpr int CREATE_GUN_NUMBER_0 = 0; //銃の生成番号０番
	static constexpr int CREATE_GUN_NUMBER_1 = 1; //銃の生成番号１番
	static constexpr int CREATE_GUN_NUMBER_2 = 2; //銃の生成番号２番
	static constexpr int CREATE_GUN_NUMBER_3 = 3; //銃の生成番号３番


	//=============================================
	//当たり判定マクロ定義
	static constexpr int MAX_LANDING_FRAME = 60;     //着地時のフレームの最大値
	static constexpr int NEXT_STAGE_BATTLESHIP = 1;  //次のステージへ行く用のバトルシップの番号

	static constexpr float ADJUST_HIT_BATTLE = 1.1f; //バトルシップの当たり判定の調整値


	//=============================================
	//バトルシップのマクロ定義
	static constexpr int ATTACKPATTEN_FRAME_1 = 1;   //第一行動
	static constexpr int ATTACKPATTEN_FRAME_2 = 180; //第二行動

	static constexpr float PLUS_POS_Y = 100.0f;      //自身のY軸の位置の加算値
	static constexpr float MINUS_POS_Z = -250.0f;    //自身のZ軸の位置の減算値


	//=============================================
	//生成オブジェクトのマクロ定義
	static constexpr int CREATE_FIELDBLOCK = 0;      //地面用ブロックの生成番号
	static constexpr int CREATE_TELEPHONPOLE = 1;    //電柱の生成番号
	static constexpr int CREATE_GOUPBLOCK = 2;       //上がる用ブロックの生成番号


	//プレイヤーの状態
	enum class PLAYER_STATE
	{
		NORMAI_MODE,  //通常状態
		SHOP_MODE,    //店で話している状態
		BUY_MODE,     //買う状態
		SEND_MODE,    //売る状態
	};

	//インスタンス
	CUI* m_pTalkText;                    //「話す」textUI
	CUI* m_pLaserUI;                     //レーザーUI
	CManager2DUI* m_pNowCreateUI;        //今置こうとしているオブジェクトのUI
	CManager2DUI* m_pMenyu;              //メニューUI
	CBuyText* m_pBuyText;                //[買う、売る]textUI
	CSelectGage* m_pSelectGage;          //選択時のゲージUI
	CSelectGage001* m_pSelectGage001;    //選択時のゲージUI

	//構造体のインスタンス
	PLAYER_STATE m_PlayerState;          //現在のプレイヤーの状態
	PLAYER_STATE m_FlagSate;             //現在のフラグの

	//==========================================
	//テキストファイルに登録する時の配列番号
	int m_nFiledCount;                   //フィールドの配列を進める為のカウント
	int m_nTelephonCount;                //電柱の配列を進める為のカウント＋textから呼ぶときにインスタンス情報の配列を登録したいから渡す


	//==========================================
	//テキストファイルに登録するした全ての配列番号
	int m_nAllTelephonPoleCount;         //電柱の今の作られた数を保管する
	int m_nAllFiledCount;                //フィールドの今の作られた数を保管する


	//==========================================
	//パーティクルに関する変数
	int m_nAlpha;                        //パーティクルの透明度をランダムで決める変数
	int m_nFrameParticle;                //毎フレームを観測する為の変数
	int m_nPraticlesCount;               //パーティクルの配列をカウントする為の変数
	int m_nRandomCol;                    //乱数を保管する為の変数


	//==========================================
	//プレイヤーに関する変数
	int m_nMotionFrame;                  //銃を打つ際のカウント
	int m_nMotionFrame001;               //銃を撃つ際のカウント
	int m_ObjectNumber;                  //現在のオブジェクトの種類の番号を保管する変数
	bool m_bPlayerMoveNext;              //次のステージへ行く時のプレイヤーの動きの判定用の変数
	bool m_bNextStage;                   //次のステージへ行く為の判定を取る用の変数
	bool SpecialAttack;                  //必殺技を使っているときは動けない


	//==========================================
	//SHOPに関する変数
	int m_nSelectShopCount;              //何を買うかカウントする為の変数
	int m_nBuyOrSendCount;               //買うか売るかを選択するときに判別するようの変数


	//==========================================
	//吹っ飛び処理に必要な変数
	int m_nFlayFrame;                    //吹っ飛ぶ時間を観測
	int m_nDieRandom;                    //死亡時のフレームを保管する変数
	int m_nRotNumber;                    //プレイヤーの向きの番号を保管
	int m_nSpecialAttackCount;           //必殺技の撃てる時間を観測する用の変数
	bool m_bFly;                         //自機が吹っ飛んでいるかどうかの判定の為の変数（モーションの混雑を避けるため）


	//==========================================
	//スペースシップ処理に必要な変数
	int m_nNextStageFrame;               //次のステージに行くまでのフレーム
	int m_nLandingFrame;                 //着地時のフレーム
	bool m_bLandingFlag;                 //着地したかどうかの判定用変数


	//===========================================
	//生成数の取得用
	int m_nFieldBlock;                   //地面用ブロックの生成数を保管する用の変数
	int m_nGoUpBlock;                    //上がる用のブロックの生成数を保管する用の変数
	int m_nRoadBlock;                    //道用ブロックの生成数を保管する用の変数
	int m_nWallRoadBlock;                //壁兼道用ブロックの生成数を保管する用の変数
	int m_nWallRoadBlock001;             //壁兼道用ブロック001の生成数を保管する用の変数
	int m_nSmalBlock;                    //小さいブロックの生成数を保管する用の変数
	int m_nSmalBlock001;                 //小さいブロック001の生成数を保管する用の変数

	int	m_nLaserCount;                   //レーザーの生成数を保管する用の変数
};

