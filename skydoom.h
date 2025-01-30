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
	static CSkyDoom* Create(D3DXVECTOR3 pos, int nNumber); //生成処理
};