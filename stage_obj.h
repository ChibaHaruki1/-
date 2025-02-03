//============================================================
//
//ステージに置くオブジェクトのクラス管理[statge_obj.h]
//Auther:Chiba Haruki
//
//============================================================

#pragma once

//===========================
//インクルード
#include "objectX.h"

//====================================================
//ステージに置くオブジェクトの基底クラス管理
class CStageObj : public  CObjectX
{
public:
	CStageObj(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CStageObj()override;                         //デストラクタ
	HRESULT Init()override;                       //初期化処理
	void Uninit()override;                        //破棄処理
	void Update() override;                       //更新処理
	void Draw()override;                          //描画処理
	void TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ); //テキストファイルに情報を書く処理
	static CStageObj* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);                       //継承クラスをタイプごとに生成

private:
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0; //int型の初期化の値

	static int m_nTelephonPoleCount;        //電柱の作られた数をカウントする為の変数
};


//====================================================
//電柱のクラス管理
class CTelephonPole : public CStageObj
{
public:
	CTelephonPole(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CTelephonPole()override;                         //デストラクタ
};


//====================================================
//監視カメラの上の部分
class CSurveillanceCameraUP : public CStageObj
{
public:
	CSurveillanceCameraUP(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CSurveillanceCameraUP()override;                         //デストラクタ
	HRESULT Init()override;                                   //初期化処理
	void Uninit()override;                                    //破棄処理
	void Update() override;                                   //更新処理
	void Draw()override;                                      //描画処理
};


//====================================================
//監視カメラの下の部分
class CSurveillanceCameraDown : public CStageObj
{
public:
	CSurveillanceCameraDown(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CSurveillanceCameraDown()override;                         //デストラクタ
};


//====================================================
//監視カメラの下の部分
class CShop : public CStageObj
{
public:
	CShop(int nPriority = DEFAULT_PRIORITY1);                   //コンストラクタ
	~CShop()override;                                           //デストラクタ
};

//====================================================
//壊れた家
class CBreakHouse : public CStageObj
{
public:
	CBreakHouse(int nPriority = DEFAULT_PRIORITY1);             //コンストラクタ
	~CBreakHouse()override;                                     //デストラクタ
	void Update()override;                                      //更新処理

private:
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;                     //int型の初期化の値
	static constexpr float F_INIT_NUMBER = 0.0f;                //float型の初期化の値

	static constexpr int LIFE = 180;                            //ライフの最大値
	static constexpr int ALPHA = 170;                           //アルファ値

	static constexpr float FIRE_EFFECT_SIZE_X = 920.0f;         //炎エフェクトのX軸の大きさ
	static constexpr float FIRE_EFFECT_SIZE_Y = 700.0f;         //炎エフェクトのY軸の大きさ
	static constexpr float FIRE_EFFECT_PLUS_POS_X = 200.0f;     //炎エフェクトのX軸の位置
	static constexpr float FIRE_EFFECT_PLUS_POS_Y = 600.0f;     //炎エフェクトのY軸の位置
};
