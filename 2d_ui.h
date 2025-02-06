//===================================
//
//2D_UIのクラス管理[2d_ui.h]
//Author:chiba haruki
//
//===================================


#pragma once


//======================================
//インクルード
#include "main.h"
#include "object2D.h"


//======================================
//２DUIのマネージャー管理クラス
class CManager2DUI : public CObject2D
{
public:
	CManager2DUI(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManager2DUI();                                 //デストラクタ
	HRESULT Init()override;                          //初期化処理
	void Uninit()override;                           //破棄処理
	void Update()override;                           //更新処理
	void Draw()override;                             //描画処理

	static CManager2DUI* Create(TYPE_UI TypeUI);     //生成処理
	static CManager2DUI* NowCreate(int nNumber);     //現在作られているオブジェクトUIの生成処理

private:
	//マクロ定義
	static constexpr int CRETAE_NUMBER_0 = 0;        //生成する番号０番目
	static constexpr int CRETAE_NUMBER_1 = 1;        //生成する番号１番目
};


//==================================================================
//今作ろうとしているオブジェクトのUIクラス
class CNowCreateUI : public CManager2DUI
{
public:
	CNowCreateUI(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CNowCreateUI()override;                         //デストラクタ
	HRESULT Init()override;                          //初期化処理

private:
	//マクロ定義
	static constexpr  float SIZEX = 100.0f;          //サイズのX軸の大きさ
	static constexpr  float SIZEY = 100.0f;          //サイズのY軸の大きさ
};


//==================================================================
//店のメニュー一覧UIクラス
class CShopMenu : public CManager2DUI
{
public:
	CShopMenu(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CShopMenu()override;						  //デストラクタ
	HRESULT Init()override;						  //初期化処理

private:
	//マクロ定義
	static constexpr  float SIZEX = 600.0f;        //サイズのX軸の大きさ
	static constexpr  float SIZEY = 700.0f;        //サイズのY軸の大きさ
};


//==================================================================
//BuyText表示UIクラス
class CBuyText : public CManager2DUI
{
public:
	CBuyText(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CBuyText()override;						 //デストラクタ
	HRESULT Init()override;						 //初期化処理

	static CBuyText* Create();                   //生成処理

private:
	//マクロ定義
	static constexpr  int ALPHA = 200;             //アルファ値
	static constexpr  float SIZEX = 600.0f;        //サイズのX軸の大きさ
};


//==================================================================
//選ぶ時のUIクラス
class CSelectGage : public CObject2D
{
public:
	CSelectGage(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CSelectGage()override;							//デストラクタ
	HRESULT Init()override;							//初期化処理
	void Uninit()override;							//破棄処理
	void Update()override;							//更新処理
	void Draw()override;							//描画処理


	//========================================
	//情報を取得
	float& GetSizeX() { return m_fSizeX; }          //選択ゲージのX軸の大きさの取得
	float& GetSizeY() { return m_fSizeY; }          //選択ゲージのy軸の大きさを取得
	float& GetSize1X() { return m_fSize1X; }        //選択ゲージ001のx軸の大きさの取得
	float& GetSize1Y() { return m_fSize1Y; }        //選択ゲージ001のy軸の大きさの取得


	//=========================================
	//情報を設定
	float& SetAddjustSizeX() { return m_fSizeX; }     //選択ゲージのX軸の大きさの設定
	float& SetAddjustSize1X() { return m_fSize1X; }   //選択ゲージのy軸の大きさを設定
	float& SetAddjustSizeY() { return m_fSizeY; }     //選択ゲージ001のx軸の大きさの設定
	float& SetAddjustSize1Y(){ return m_fSize1Y; }    //選択ゲージ001のy軸の大きさの設定

	static CSelectGage* Create();                     //生成処理

private:
	//マクロ定義
	 static constexpr  float SIZE1X = 600.0f;        //選択ゲージ２番目のX軸の大きさ
	 static constexpr  float SIZEY = 50.0f;          //選択ゲージ１番目のY軸の大きさ
	 static constexpr  float SIZE1Y = 150.0f;        //選択ゲージ２番目のY軸の大きさ
											       
	 static constexpr  int ALPHA = 100;              //アルファ値

	float m_fSizeX;                                //選択ゲージの１番目X軸の大きさを保管する用の変数
	float m_fSizeY;                                //選択ゲージの１番目y軸の大きさを保管する用の変数
	float m_fSize1X;                               //選択ゲージの２番目x軸の大きさを保管する用の変数
	float m_fSize1Y;                               //選択ゲージの２番目y軸の大きさを保管する用の変数
};


//==================================================================
//選ぶ時のUIクラス
class CSelectGage001 : public CSelectGage
{
public:
	CSelectGage001(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CSelectGage001()override;						   //デストラクタ
	HRESULT Init()override;							   //初期化処理
	void Update()override;							   //更新処理

	static CSelectGage001* Create();                   //生成処理
};