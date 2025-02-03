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
	static constexpr  int MAX_RAND = 100;           //乱数の最大数
	static constexpr  int PROCESS_FRAME = 50;       //処理を行うフレーム数
	static constexpr  int ADJUSTMENT_FRAME = 20;    //調整を行うフレーム数

	static constexpr  int FIRST_NUMBER = 1;         //最初の番号

	static constexpr int ALPHA_0 = 155;             //０番目のアルファ値の値
	static constexpr int ALPHA_1 = 55;              //１番目のアルファ値の値

	static constexpr double ONE_QUARTER = 0.25;     //４（QUARTER）分の１（ONE）
	static constexpr double TWO_QUARTER = 0.5;      //４（QUARTER）分の２（TWO）
	static constexpr double THREE_QUARTER = 0.75;   //４（QUARTER）分の３（THREE）
	static constexpr double NEXT_PLUS = 1;          //次の数字へ移行する為の値

	static constexpr float FIRST_SIZE_Y = 100.0f;                //第一行動の１つ目のY軸の値
	static constexpr float FIRST_PLUS_SIZE1_Y = 100.0f;          //第一行動の２つ目のY軸の値を加算する値
	static constexpr float SECOND_SIZE1_Y = 100.0f;              //第二行動の１つ目のY軸の値
	static constexpr float SECOND_MINUS_SIZE1_Y = 100.0f;        //第二行動の２つ目のY軸の値を減算する値
	static constexpr float THIRD_SIZE_X = 200.0f;                //第三行動の１つ目のX軸の値
	static constexpr float THIRD_MINUS_SIZE1_X = 200.0f;         //第三行動の２つ目のX軸の値を減算する値
	static constexpr float FOURTH_SIZE_X = 200.0f;               //第四行動の１つ目のX軸の値
	static constexpr float FOURTH_THIRD_PLUS_SIZE1_X = 200.0f;   //第四行動の２つ目のX軸の値を加算する値
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
	static constexpr  int RED = 255;          //赤色
	static constexpr  int GREEN = 255;        //緑色
	static constexpr  int BLUE = 255;         //青色
	static constexpr  int ALPHA = 50;         //アルファ値
};