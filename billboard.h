//============================================
//
//ビルボードクラス管理[billboard.h]
//Auther:Haruki Chiba
//
//============================================

#pragma once

//============================================
//インクルード
#include "object3D.h"

//==================================================================
//ビルボード処理
class CBillboard : public CObject3D
{
public:
	CBillboard(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CBillboard()override;						   //デストラクタ
	HRESULT Init()override;						   //初期化処理
	void Uninit()override;						   //破棄処理
	void Update()override;						   //更新処理
	void Draw()override;						   //描画処理

	static CBillboard* Create();                   //生成処理

private:
	//マクロ定義
	 static constexpr  float MAX_BILLBOARD_SIZE_X = 40.0f; //X軸の大きさ
	 static constexpr  float MAX_BILLBOARD_SIZE_Y = 40.0f; //Y軸の大きさ
};

