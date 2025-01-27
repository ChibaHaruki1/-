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

	CPlayerX(int nPriority = DEFAULT_PRIORITY1);                 //コンストラクタ
	~CPlayerX()override;                                         //デストラクタ
	HRESULT Init()override;                                      //初期化処理
	void Uninit()override;                                       //破棄処理
	void Update()override;                                       //更新処理
	void Draw()override;                                         //描画処理
	//void ObjectArrangement();                                  //オブジェクトの配置処理（生成＆情報をファイルに書き込む）
	void KeySet();                                               //キーごとの処理をまとめる関数
	void ShopKeySet();                                           //モードがSHOP時のキーごとの処理をまとめる関数
	void BlockJudgement();                                       //ブロックとの判定
	void Random();                                               //ランダム処理
	void Praticles();                                            //パーティクルを出す処理
	void NormalStateSummarizeFunction();                         //通常時の関数をまとめる関数
	void ShopStateSummarizeFunction();                           //店に訪問時の関数をまとめる関数
	void CreateGun();                                            //銃の生成インスタンスを呼ぶ
	void InstanceMakeNull();                                     //instanceをnullptrにする処理
	void ShopInstanceMakeNullptr();                              //ショップで使用するインスタンスをnullptrにする
	void SelectGageUISize(float SIzeX,float SIze1X);             //選択ゲージの大きさを設定する関数
	void SelectGageUISizeCalculation(const char*aSelect,float SIzeX,float SIze1X);  //選択ゲージの大きさを計算（加算や減算など）する関数
	void BlowAway();
	void HitAttack();                                            //特定の攻撃を受けたときの処理
	void SceneMode(int nType);                                   //sceneの分岐
	void NextStageMotion();                                      //次のステージに行くと時のモーション処理

	void NowCreateObjectUI();                                    //現在作っているオブジェクトのUIを出す処理
	void NowCreateNumberObj();                                   //番号で作るオブジェクトを指定する処理

	static CPlayerX* Create();                                   //生成する


	//=====================================
	//CObjectXで使用する用の取得
	int& GetTelephonPoleCount() { return m_nTelephonCount; }             //電柱の配列を取得
	int& GetAllTelephonPoleCount() { return m_nAllTelephonPoleCount; }   //全ての電柱の配列を取得
	int& GetRotNumber() { return m_nRotNumber; }                         //プレイヤーの向きの番号を取得


	//=====================================
	//マクロ定義
	constexpr static float MAX_MOVESPEED = 3.0f;              //感性を減らした分の移動量の増加

private:
	//==========================================
	//マクロ定義
	constexpr static int   MAX_TEXT_OBJECT = 2;               //今配置ツールに設定されてるオブジェクトの数ー１（０スタートだから）
	constexpr static int   MAX_BUULET_SPEED = 30;             //弾の速さ
	constexpr static int   MAX_DIE_COUNT = 180;               //死亡時のカウント
	constexpr static float   ADDJUST_SELECT_SIZEY = 160.0f;   //選択ゲージのY軸の位置を加算する値
	constexpr static float   MAX_GRAVITY = 50.0f;             //重力の最大値

	//ぶっ飛び処理時マクロ定義
	constexpr static int   BLOWAWAY_FRAME_1 = 40;             //第一行動時のフレーム
	constexpr static int   BLOWAWAY_FRAME_2 = 90;             //第二行動時のフレーム
	constexpr static float   BLOWAWAY_PLUS_POS_X = 20.0f;     //X軸の飛ぶ距離
	constexpr static float   BLOWAWAY_PLUS_POS_Y = 30.0f;     //Y軸の飛ぶ距離


	constexpr static float MAX_JUMPPAWER = 10.0f;             //飛ぶ力
	constexpr static float MAX_SPECIALATTACKCOUNT = 60 * 60;  //必殺技のリキャストタイム
	constexpr static float MAX_POS_NEXTSTAGE = 0.4f;          //次のステージへ行く時の位置の乗算値

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
	PLAYER_STATE m_FlagSate;             //現在のフラグの状態

	int m_nAlpha;                        //パーティクルの透明度をランダムで決める変数

	//==========================================
	//テキストファイルに登録する時の配列番号
	int m_nFiledCount;           //フィールドの配列を進める為のカウント
	int m_nTelephonCount;        //電柱の配列を進める為のカウント＋textから呼ぶときにインスタンス情報の配列を登録したいから渡す


	//==========================================
	//テキストファイルに登録するした全ての配列番号
	int m_nAllTelephonPoleCount; //電柱の今の作られた数を保管する
	int m_nAllFiledCount;        //フィールドの今の作られた数を保管する


	//==========================================
	//パーティクルに関する変数
	int m_nFrameParticle;        //毎フレームを観測する為の変数
	int m_nPraticlesCount;       //パーティクルの配列をカウントする為の変数
	int m_nRandomCol;            //乱数を保管する為の変数


	//==========================================
	//プレイヤーに関する変数
	int m_nMotionFrame;          //銃を打つ際のカウント
	int m_nMotionFrame001;       //銃を撃つ際のカウント
	int m_ObjectNumber;          //現在のオブジェクトの種類の番号を保管する変数
	bool m_bPlayerMoveNext;      //次のステージへ行く時のプレイヤーの動きの判定用の変数
	bool m_bNextStage;           //次のステージへ行く為の判定を取る用の変数
	bool SpecialAttack;          //必殺技を使っているときは動けない


	//==========================================
	//SHOPに関する変数
	int m_nSelectShopCount;      //何を買うかカウントする為の変数
	int m_nBuyOrSendCount;       //買うか売るかを選択するときに判別するようの変数


	// ==========================================
	//吹っ飛び処理に必要な変数
	int m_nFlayFrame;          //吹っ飛ぶ時間を観測
	int m_nDieRandom;          //死亡時のフレームを保管する変数
	int m_nRotNumber;          //プレイヤーの向きの番号を保管
	int m_nSpecialAttackCount; //必殺技の撃てる時間を観測する用の変数
	bool m_bFly;               //自機が吹っ飛んでいるかどうかの判定の為の変数（モーションの混雑を避けるため）
	bool m_bOneCreate;         //一回だけ作る為の変数

	int m_nNextStageFrame;        //次のステージに行くまでのフレーム
	int m_nLandingFrame;       //着地時のフレーム
	bool m_bLandingFlag;       //着地したかどうかの判定用変数
};

