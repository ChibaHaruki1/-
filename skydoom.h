//========================================
//
//空の背景用クラス管理[skydoom.h]
//Auther:HARUKI CHIBA
//
//========================================


#pragma once


//========================================
//インクルード
#include "main.h"
#include "objectX.h"


class CSkyDoom : public CObjectX
{
private:
	CSkyDoom(int nPriority = DEFAULT_PRIORITY1);           //コンストラクタ
	~CSkyDoom()override;						           //デストラクタ
	HRESULT Init()override;						           //初期化処理
	void Uninit()override;						           //破棄処理
	void Update() override;						           //更新処理
	void Draw()override;						           //描画処理

public:
	//マクロ定義
	static constexpr int CRETAE_PRIORITY = 1;              //生成時のプライオリティの番号
	static constexpr int CREATE_NUMBER_0 = 0;              //生成番号０番
	static constexpr int CREATE_NUMBER_1 = 1;              //生成番号１番

	static constexpr float ADJUST_ROT_Y = 0.0005f;         //向きの調整値

	static CSkyDoom* Create(D3DXVECTOR3 pos, int nNumber); //生成処理
};