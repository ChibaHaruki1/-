//=====================================
//
//画面遷移のクラス管理[scene.h]
//Auther:Haruki Chiba
//
//=====================================


#pragma once


//=====================================
//インクルード
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "ui.h"
#include "player.x.h"
#include "object_set.h"
#include "block.h"
#include "fade.h"
#include "skydoom.h"


//=====================================
//基底クラス
class CScene
{
public:

	//画面の種類
	enum class MODE
	{
		MODE_TITLE = 0,                 //タイトル
		MODE_GAME01,                    //ステージ１
		MODE_GAME02,                    //ステージ２
		MODE_HIDEGAME,                  //裏ステージ
		MODE_RESULT,                    //リザルト
		MODE_GAMEOVER,                  //ゲームオーバー
		MODE_MAX                        //最大数
	};						            
							            
	CScene();                           //コンストラクタ
	virtual ~CScene();                  //デストラクタ
	virtual HRESULT Init();             //初期化処理
	virtual void Uninit();              //終了処理
	virtual void Update();              //継承クラス更新処理
	void AnyUpdate();                   //このクラスだけの処理の更新処理

	static CScene* Create(MODE mode);   //modeに合わせて生成をする


	//==================================
	//情報の取得
	inline MODE& GetMode() { return m_Mode; }               //現在モードの取得
	inline CCamera* GetCamera() { return m_pCamera; }       //カメラの情報を取得
	inline CLight* GetLight() { return m_pLight; }          //光源の情報を取得
	inline CPlayerX*& GetPlayerX() { return m_pPlayerX; }   //プレイヤーの情報を取得する

	inline int& GetFrame() { return m_nFrame; }


	//==================================
	//情報の設定
	inline void SetFrame(int nFrame) { m_nFrame = nFrame; } //フレームの設定
	inline int& SetAdjustFrame() { return m_nFrame; }       //フレームの調整


	//===========================================================
	//情報の取得
	inline bool& GetOneSound() { return m_bOneSound; }      //音源が再生されているかどうかの判定を取得
	inline bool& GetOneScene() { return m_bOneScene; }      //シーンの移動するかどうかの情報を取得
	inline bool& GetPlay() { return m_bPlay; }              //遊べるかどうかの情報を取得


	//===========================================================
	//情報の設定
	inline void SetOneSound(bool bOneSound) { m_bOneSound = bOneSound; } //音源を生成するかどうかを設定
	inline void SetOneScene(bool bOneScene) { m_bOneScene = bOneScene; } //シーンを移動するかどうかを設定	
	inline void SetPlay(bool bPlay) { m_bPlay = bPlay; }                 //遊べるか設定する


	//===========================================================
	//マクロ定義
	static constexpr int BATTLESHIP_NUMBER = 0;            //シーン用のバトルシップの番号

private:
	CCamera* m_pCamera;        //カメラの情報
	CLight* m_pLight;          //光源の情報
	CPlayerX* m_pPlayerX;      //プレイヤーのポインター
	MODE m_Mode;               //現在のモードの管理変数

	int m_nFrame;              //フレームを保管する用の変数

	bool m_bOneSound;          //１回だけ音源を流す為の変数
	bool m_bOneScene;          //１回だけシーン移動する為の変数
	bool m_bPlay;              //遊べるかどうかの判定用変数
};


//=====================================
//ステージ１のクラス管理
class CGame01 : public CScene
{
public:
	CGame01();               //コンストラクタ
	~CGame01()override;      //デストラクタ
	HRESULT Init()override;  //初期化処理
	void Uninit()override;   //破棄処理
	void Update()override;   //更新処理
	void InitCreate();       //初期化時に生成したい物をまとめる関数
	void CompileCreate();    //create関数をまとめる関数

private:
	//マクロ定義
	static constexpr int INIT_CAMERA_ADJUST_POS_Z = 500;   //カメラのZ軸の位置を設定
	static constexpr int UPDATE_CAMERA_ADJUST_POS_Z = 800; //カメラのZ軸の位置を設定
	static constexpr int MAX_FRAME = 180;                  //フレームの最大数

	static constexpr float MINUS_ROT = -1.0f;              //向きの値の減算値
	static constexpr float INIT_PLAYER_POS_Y = 2050.0f;    //プレイヤーのY軸の位置を設定


	//==================================================
	//バトルシップに関するマクロ定義
	static constexpr float BATTLESHIP_0_POS_Y = 2000.0f;   //バトルシップ0のY軸の位置
	static constexpr float BATTLESHIP_0_POS_Z = 100.0f;    //バトルシップ0のZ軸の位置

	static constexpr float BATTLESHIP_1_POS_X = 12700.0f;  //バトルシップ1のX軸の位置
	static constexpr float BATTLESHIP_1_POS_Y = 1900.0f;   //バトルシップ1のY軸の位置


	//==================================================
	//空に関するマクロ定義
	static constexpr int SKY_CREATE_NUMBER = 1; //空の生成番号

	static constexpr float SKY_POS_Z = 200.0f;  //空のZ軸の位置

	CFade* m_pFade;          //フェードのポインター
};


//=====================================
//ステージ２のクラス管理
class CGame02 : public CScene
{
public:                    
	CGame02();                                        //コンストラクタ
	~CGame02()override;                               //デストラクタ
	HRESULT Init()override;                           //初期化処理
	void Uninit()override;                            //破棄処理
	void Update()override;                            //更新処理
	void CompileCreate();                             //create関数をまとめる関数

private:
	//マクロ定義
	static constexpr float PLUS_POS_X = 20.0f;        //X軸の加算値
	static constexpr float PLUS_POS_Y = 3.0f;         //Y軸の加算値
	static constexpr float BATTLESHOP_POS_Z = 100.0f; //バトルシップのZ軸の位置


	//==================================================
	//共通マクロ定義
	static constexpr float POS_X = -1500.0f;          //X軸の生成位置
	static constexpr float POS_Y = 200.0f;            //Y軸の生成位置


	//==================================================
	//空に関するマクロ定義
	static constexpr float SKY_POS_Z = 200.0f;        //空のZ軸の位置


	//==================================================
	//足場に関するマクロ定義
	static constexpr float SCAFFOLD_POS_X = 4335.0f;  //足場のX軸の生成位置
	static constexpr float SCAFFOLD_POS_Y = -200.0f;  //足場のY軸の生成位置


	//==================================================
	//店に関するマクロ定義
	static constexpr float SHOP_POS_X = 200.0f; //店のX軸の生成位置
	static constexpr float SHOP_POS_Z = 150.0f; //店のZ軸の生成位置


	//==============================
	//行動時のマクロ定義
	static constexpr int FRAME_1 = 80;           //第一行動
	static constexpr int FRAME_2 = FRAME_1 + 1;  //第二行動
	static constexpr int FRAME_3 = 300;          //第三行動

};


////=====================================
////裏ステージのクラス管理
//class CHideGame : public CScene
//{
//public:
//	CHideGame();              //コンストラクタ
//	~CHideGame()override;     //デストラクタ
//	HRESULT Init()override;   //初期化処理
//	void Uninit()override;    //破棄処理
//	void Update()override;    //更新処理
//	void CompileCreate();     //create関数をまとめる関数
//
//private:
//	//マクロ定義
//	static constexpr float POS_X = 1500.0f;      //X軸の生成位置
//	static constexpr float PLUS_POS_X = 20.0f;   //X軸の加算値
//
//};


//=====================================
//タイトルのクラス管理
class CTitle : public CScene
{
public:                   
	CTitle();               //コンストラクタ
	~CTitle()override;      //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override;  //破棄処理
	void Update()override;  //更新処理
	void Game();            //タイトルゲーム画面

private:           
	CFade* m_pFade;  //フェードのポインター
};


//=====================================
//リザルトのクラス管理
class CResult : public CScene
{
public:                     
	CResult();              //コンストラクタ
	~CResult()override;     //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override;  //破棄処理
	void Update()override;  //更新処理
};


//=====================================
//ゲームオーバークラス管理
class CGameOver : public CScene
{
public: 
	CGameOver();             //コンストラクタ
	~CGameOver()override;    //デストラクタ
	HRESULT Init()override;  //初期化処理
	void Uninit()override;   //破棄処理
	void Update()override;   //更新処理
};
