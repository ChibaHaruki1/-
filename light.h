//=======================================
//
//光源クラス管理[light.h]
//Auther:Haruki Chiba
//
//=======================================


#pragma once


//=======================================
//インクルード
#include "main.h"


class CLight
{
public:
	CLight();         //コンストラクタ
	~CLight();        //デストラクタ
	HRESULT Init();   //初期化処理
	void Uninit();    //破棄処理
	void Update();    //更新処理

private:
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;          //int型の初期化の値  
	static constexpr float F_INIT_NUMBER = 0.0f;     //float型の初期化の値

	static constexpr float ZERO_LIGHT_POS_Z = 1.2f;  //０番目のZ軸の位置
	static constexpr float ONE_LIGHT_POS_Z = 0.8f;   //１番目のZ軸の位置
	static constexpr float TWO_LIGHT_POS_X = 1.0f;   //２番目のX軸の位置
	static constexpr float THREE_LIGHT_POS_X = 1.0f; //３番目のX軸の位置
	static constexpr float ALL_LIGHT_POS_Y = 1.0f;   //全てのY軸の位置

	static constexpr float RED = 1.0f;               //赤色
	static constexpr float GREEN = 1.0f;             //緑色
	static constexpr float BLUE = 1.0f;              //青色
	static constexpr float ALPHA = 1.0f;             //アルファ値

	static const int MAX_LIGHT = 4; //光源の最大数
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //光源の情報
};
