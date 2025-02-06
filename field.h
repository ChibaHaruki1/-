//===================================================
//
//地面のクラス管理[field.h]
//Author:chiba haruki
//
//===================================================


#pragma once


//===================================================
//インクルード
#include "object3D.h"

class CField : public CObject3D
{
public:
	CField(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CField()override;						   //デストラクタ
	HRESULT Init()override;					   //初期化処理
	void Uninit()override;					   //破棄処理
	void Update()override;					   //更新処理
	void Draw()override;					   //描画処理
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ); //テキストファイルに情報を書き込む処理

	static CField* Create(D3DXVECTOR3 pos);    //生成処理

private:
	//マクロ定義
	static constexpr int CREATE_PRIORITY = 2;  //生成時のプライオリティの番号
	static constexpr float SIZEX = 200.0f;     //ｘ軸の大きさ

	static int m_nCountField;                  //生成された地面の数を格納する用の変数
};
