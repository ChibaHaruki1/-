//==========================================
//
//UIのクラス管理宣言をするファイル[ui.h]
//Author:chiba haruki
//
//==========================================

#pragma once

//==========================================
//インクルード
#include "object3D.h"
#include <cstdio>


//======================================================
//UIのマネージャー管理クラス
class CUI : public CObject3D
{
public:
	CUI(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CUI()override;							//デストラクタ
	HRESULT Init()override;					//初期化処理
	void Uninit()override;					//破棄処理
	void Update()override;					//更新処理
	void Draw()override;					//描画処理

	static CUI* Create(CObject3D::TYPE_UI typeui); //生成処理
};


//======================================================
//現在の配置したオブジェクトの場所にUIを出すクラス管理
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CCreateInObject()override;                         //デストラクタ
};


//======================================================
//今作ろうとしているオブジェクトのUIをだすクラス管理
class CTalkText : public CUI
{
public:
	CTalkText(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CTalkText()override;                         //デストラクタ
	HRESULT Init()override;                       //初期化処理
	void Draw()override;                          //描画処理

private:
	//マクロ定義
	constexpr static float SIZEX = 40.0f; //X軸の大きさ
	constexpr static float SIZEY = 40.0f; //Y軸の大きさ
	constexpr static float SIZEZ = 40.0f; //Z軸の大きさ
};


//======================================================
//監視カメラからでるレーザークラス
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CLaserCamare()override;                         //デストラクタ
	HRESULT Init()override;                          //初期化処理
	void Update()override;                           //更新処理
	void Draw()override;                             //描画処理

private:
	//マクロ定義
	constexpr static float SIZEX = 80.0f;                 //X軸の大きさ
	constexpr static float SIZEY = 20.0f;                 //Y軸の大きさ
	constexpr static float SIZEZ = 20.0f;                 //Z軸の大きさ
	constexpr static float ADDJUST_POSY = 20.0f;          //Y軸の位置の調整値
	constexpr static float ADDJUST_POSZ = 35.0f;          //Z軸の位置の調整値
	constexpr static float ADDJUST_ROTY = 0.54f;          //Y軸の向きの調整値
	constexpr static float ADDJUST_ROTZ = 1.54f;          //Z軸の向きの調整値
	constexpr static float ADDJUST_CREATE_POSX = 300.0f;  //X軸の生成位置の調整値
	constexpr static float ADDJUST_CREATE_POSY = 500.0f;  //Y軸の生成位置の調整値
	constexpr static float ADDJUST_ADDJUST_SIZE = 1.3f;   //プレイヤーとの当たり判定時の乗算値
};
