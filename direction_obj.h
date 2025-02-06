//=============================================================
//
//演出用３Dオブジェクトのクラス管理[direction_obj.h]
//Auther:HARUKI CHIBA
//
//=============================================================


#pragma once


//==============================================================
//インクルード
#include "objectX.h"


//=============================================================================
//破片クラス
class CDebrisX : public CObjectX
{
public:
	CDebrisX(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CDebrisX()override;                          //デストラクタ
	HRESULT Init()override;                       //初期化処理
	void Uninit()override;                        //破棄処理
	void Update() override;                       //更新処理
	void Draw()override;                          //描画処理

	static CDebrisX* Create(D3DXVECTOR3 pos);     //生成処理

private:
	 static constexpr  int MAX_LIFE = 30;           //ライフの最大値
};
