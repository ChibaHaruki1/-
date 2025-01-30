//===================================
//
//背景のクラス管理[bg.h]
//Author:chiba haruki
//
//===================================


#pragma once


//===================================
//インクルード
#include "object2D.h"
#include "scene.h"


//==================================================================
//背景の管理基底クラス
class CManagerBg : public CObject2D
{
public:
	CManagerBg(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerBg()override;						   //デストラクタ
	HRESULT Init()override;						   //初期化処理
	void Uninit()override;						   //破棄処理
	void  Update()override;						   //更新処理
	void Draw()override;						   //描画処理

	static CManagerBg* Create(CScene::MODE mode);  //生成処理
};


//==================================================================
//タイトル背景
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);    //コンストラクタ
	~CTitleBg()override;                           //デストラクタ
};


//==================================================================
//リザルト背景
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);   //コンストラクタ
	~CResultBg()override;                          //デストラクタ
};


//==================================================================
//ゲームオーバー背景
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CGameOverBg()override;                         //デストラクタ
	void Update()override;                          //更新処理

private:
	constexpr static int MAX_RAND = 100;        //乱数の最大数
	constexpr static int PROCESS_FRAME = 50;    //処理を行うフレーム数
	constexpr static int ADJUSTMENT_FRAME = 20; //調整を行うフレーム数

	constexpr static int RED = 255;          //赤色
	constexpr static int GREEN = 255;        //緑色
	constexpr static int BLUE = 255;         //青色
};


//==================================================================
//ショップ時の背景
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CShopScreen()override;                         //デストラクタ
	HRESULT Init()override;                         //初期化処理
	void Update()override;                          //更新処理

	static CShopScreen* Create();                   //生成処理

private:
	constexpr static int RED = 255;          //赤色
	constexpr static int GREEN = 255;        //緑色
	constexpr static int BLUE = 255;         //青色
	constexpr static int ALPHA = 50;         //アルファ値
};