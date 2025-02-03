//=================================
//
//光源処理[light.cpp]
//Auther:Haruki Chiba
//
//=================================


//=================================
//インクルード
#include "light.h"
#include "rendererh.h"
#include "manager.h"


//=======================
//コンストラクタ
//=======================
CLight::CLight()
{
	//光源の最大数分回す
	for (int Light = N_INIT_NUMBER; Light < MAX_LIGHT; Light++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_aLight[Light], sizeof(D3DLIGHT9));
	}
}


//=======================
//デストラクタ
//=======================
CLight::~CLight()
{

}


//=======================
//初期化処理
//=======================
HRESULT CLight::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice;                      //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//光源の位置を取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//光源の最大数分回す
	for (int LightCount = N_INIT_NUMBER; LightCount < MAX_LIGHT; LightCount++)
	{
		//ライトの種類を設定
		m_aLight[LightCount].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(F_INIT_NUMBER, -ALL_LIGHT_POS_Y, ZERO_LIGHT_POS_Z);
		vecDir[1] = D3DXVECTOR3(F_INIT_NUMBER, -ALL_LIGHT_POS_Y, -ONE_LIGHT_POS_Z);
		vecDir[2] = D3DXVECTOR3(-TWO_LIGHT_POS_X, -ALL_LIGHT_POS_Y, F_INIT_NUMBER);
		vecDir[3] = D3DXVECTOR3(THREE_LIGHT_POS_X, -ALL_LIGHT_POS_Y, F_INIT_NUMBER);

		//ベクトルを正規化する
		D3DXVec3Normalize(&vecDir[LightCount], &vecDir[LightCount]);

		//方向
		m_aLight[LightCount].Direction = vecDir[LightCount];

		//色
		m_aLight[LightCount].Diffuse = D3DXCOLOR(RED, GREEN,BLUE, ALPHA);

		//ライトを設定する
		pDevice->SetLight(LightCount, &m_aLight[LightCount]);

		//ライトを設定する
		pDevice->LightEnable(LightCount, TRUE);
	}
	return S_OK; //成功を返す
}


//=======================
//終了処理
//=======================
void CLight::Uninit()
{

}


//=======================
//更新処理
//=======================
void CLight::Update()
{

}