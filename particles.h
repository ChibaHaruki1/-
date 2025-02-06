//=============================================
//
//パーティクルのクラス管理[particles.h]
//Author:chiba haruki
//
//=============================================


#pragma once


//=============================================
//インクルード
#include "object3D.h"


//====================================================================
//パーティクル001のクラス
class CParticles001 : public CObject3D
{
public:
	CParticles001(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CParticles001()override;						  //デストラクタ
	HRESULT Init()override;							  //初期化処理
	void Uninit()override;							  //破棄処理
	void Update()override;							  //更新処理
	void Draw()override;							  //描画処理

	static CParticles001* Create(D3DXVECTOR3 pos);    //生成処理

private:
	//マクロ定義
	static constexpr  int MAX_PARTICLES001_LIFE = 60;  //パーティクル001のライフ
	static constexpr int CREATE_PRIORITY = 2;          //生成時のプライオリティの番号

	static constexpr  float SIZEX = 10.0f;             //X軸の大きさ
	static constexpr  float SIZEY = 10.0f;             //X軸の大きさ
	static constexpr  float SIZEZ = 10.0f;             //X軸の大きさ
	static constexpr  float PLUS_POSY = 2.0f;          //Y軸の増減値
};
