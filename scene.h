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
		MODE_TITLE = 0, //タイトル
		MODE_GAME01,    //ステージ１
		MODE_GAME02,    //ステージ２
		MODE_RESULT,    //リザルト
		MODE_GAMEOVER,  //ゲームオーバー
		MODE_MAX        //最大数
	};

	CScene();                  //コンストラクタ
	virtual ~CScene();         //デストラクタ
	virtual HRESULT Init();    //初期化処理
	virtual void Uninit();     //終了処理
	virtual void Update();     //継承クラス更新処理
	void AnyUpdate();          //このクラスだけの処理の更新処理
	MODE& GetMode() { return m_Mode; } //現在モードの取得

	static CScene* Create(MODE mode);  //modeに合わせて生成をする


	//==================================
	//情報の取得
	CCamera* GetCamera() { return m_pCamera; }       //カメラの情報を取得
	CLight* GetLight() { return m_pLight; }          //光源の情報を取得
	CPlayerX*& GetPlayerX() { return m_pPlayerX; }   //プレイヤーの情報を取得する

	int& GetFrame() { return m_nFrame; }


	//==================================
	//情報の設定
	void SetFrame(int nFrame) { m_nFrame = nFrame; } //フレームの設定
	int& SetAddjustFrame() { return m_nFrame; }      //フレームの調整


	//===========================================================
	//情報の取得
	bool& GetOneSound() { return m_bOneSound; }    //音源が再生されているかどうかの判定を取得
	bool& GetOneScene() { return m_bOneScene; }    //シーンの移動するかどうかの情報を取得
	bool& GetPlay() { return m_bPlay; }            //遊べるかどうかの情報を取得


	//===========================================================
	//情報の設定
	void SetOneSound(bool bOneSound) { m_bOneSound = bOneSound; } //音源を生成するかどうかを設定
	void SetOneScene(bool bOneScene) { m_bOneScene = bOneScene; } //シーンを移動するかどうかを設定	
	void SetPlay(bool bPlay) { m_bPlay = bPlay; }                 //遊べるか設定する

private:
	CCamera* m_pCamera;        //カメラの情報
	CLight* m_pLight;          //光源の情報
	CPlayerX* m_pPlayerX;      //プレイヤーのポインター
	MODE m_Mode;               //現在のモードの管理変数

	int m_nFrame;

	bool m_bOneSound;          //１回だけ音源を流す為の変数
	bool m_bOneScene;          //１回だけシーン移動する為の変数
	bool m_bPlay;              //遊べるかどうかの判定用変数
};


//=====================================
//ステージ１のクラス管理
class CGame01 : public CScene
{
public:                      //アクセス可能
	CGame01();               //コンストラクタ
	~CGame01()override;      //デストラクタ
	HRESULT Init()override;  //初期化処理
	void Uninit()override;   //破棄処理
	void Update()override;   //更新処理
	void InitCreate();       //初期化時に生成したい物をまとめる関数
	void CompileCreate();    //create関数をまとめる関数

private:          
	CFade* m_pFade;  //フェードのポインター
};


//=====================================
//ステージ２のクラス管理
class CGame02 : public CScene
{
public:                       //アクセス可能
	CGame02();                //コンストラクタ
	~CGame02()override;       //デストラクタ
	HRESULT Init()override;   //初期化処理
	void Uninit()override;    //破棄処理
	void Update()override;    //更新処理
	void CompileCreate();     //create関数をまとめる関数

private:
	//マクロ定義
	static constexpr float POS_X = 1500.0f;
	static constexpr float PLUS_POS_X = 20.0f;

};


//=====================================
//タイトルのクラス管理
class CTitle : public CScene
{
public:                     //アクセス可能
	CTitle();               //コンストラクタ
	~CTitle()override;      //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override;  //破棄処理
	void Update()override;  //更新処理
	void Game();            //タイトルゲーム画面

private:             //アクセス不可能
	CFade* m_pFade;  //フェードのポインター
};


//=====================================
//リザルトのクラス管理
class CResult : public CScene
{
public:                     //アクセス可能
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
public: //アクセス可能
	CGameOver(); //コンストラクタ
	~CGameOver()override; //デストラクタ
	HRESULT Init()override; //初期化処理
	void Uninit()override; //破棄処理
	void Update()override; //更新処理
};
