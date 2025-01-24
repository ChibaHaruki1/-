//=======================================
//
//光源クラス管理[light.h]
//Auther:Haruki Chiba
//
//=======================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

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
	static const int MAX_LIGHT = 4; //光源の最大数
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //光源の情報
};

#endif // !_LIGHT_H_

