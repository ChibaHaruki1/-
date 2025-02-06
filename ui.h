//==========================================
//
//UIのクラス管理[ui.h]
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
	CUI(int nPriority = DEFAULT_PRIORITY);      //コンストラクタ
	~CUI()override;							    //デストラクタ
	HRESULT Init()override;					    //初期化処理
	void Uninit()override;					    //破棄処理
	void Update()override;					    //更新処理
	void Draw()override;					    //描画処理
	virtual void Hit() = 0;                     //当たり判定処理

	static CUI* Create(CObject3D::TYPE typeui); //生成処理

private:
	//マクロ定義
	static constexpr int CREATE_PRIORITY = 0;   //生成時のプライオリティの番号
};


//======================================================
//現在の配置したオブジェクトの場所にUIを出すクラス管理
class CCreateInObject : public CUI
{
public:
	CCreateInObject(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CCreateInObject()override;                         //デストラクタ
	void Hit()override {};                              //当たり判定処理
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
	void Hit()override {};                        //当たり判定処理

private:
	//マクロ定義
	static constexpr  float SIZEX = 40.0f; //X軸の大きさ
	static constexpr  float SIZEY = 40.0f; //Y軸の大きさ
	static constexpr  float SIZEZ = 40.0f; //Z軸の大きさ
};


//======================================================
//監視カメラからでるレーザークラス
class CLaserCamare : public CUI
{
public:
	CLaserCamare(int nPriority = DEFAULT_PRIORITY);       //コンストラクタ
	~CLaserCamare()override;                              //デストラクタ
	HRESULT Init()override;                               //初期化処理
	void Update()override;                                //更新処理
	void Draw()override;                                  //描画処理
	void Hit()override;                                   //当たり判定処理


	//===========================
	//マクロ定義
	static constexpr  float SIZEX = 80.0f;                 //X軸の大きさ
	static constexpr  float SIZEY = 20.0f;                 //Y軸の大きさ
	static constexpr  float SIZEZ = 20.0f;                 //Z軸の大きさ
	static constexpr  float ADJUST_ADDJUST_SIZE = 1.3f;   //プレイヤーとの当たり判定時の乗算値


	static 	constexpr float TOTALVALUE_X = SIZEY * ADJUST_ADDJUST_SIZE; //X軸用の当たり判定用の合計値
	static 	constexpr float TOTALVALUE_Y = SIZEX * ADJUST_ADDJUST_SIZE; //Y軸用の当たり判定用の合計値
	static 	constexpr float TOTALVALUE_Z = SIZEZ * ADJUST_ADDJUST_SIZE; //Z軸用の当たり判定用の合計値

private:
	//マクロ定義
	static constexpr int MIN_RANDOM = 1; //乱数の最小値
	static constexpr int MAX_RANDOM = 2; //乱数の最大値

	static constexpr  float ADJUST_POSY = 20.0f;          //Y軸の位置の調整値
	static constexpr  float ADJUST_POSZ = 35.0f;          //Z軸の位置の調整値
	static constexpr  float ADJUST_ROTY = 0.54f;          //Y軸の向きの調整値
	static constexpr  float ADJUST_ROTZ = 1.54f;          //Z軸の向きの調整値
	static constexpr  float ADJUST_CREATE_POSX = 300.0f;  //X軸の生成位置の調整値
	static constexpr  float ADJUST_CREATE_POSY = 300.0f;  //Y軸の生成位置の調整値
};
