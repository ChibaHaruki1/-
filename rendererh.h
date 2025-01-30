//==========================================
//
//レンダラークラス管理[renderer.h]
//Auther:Chiba Haruki
//
//==========================================

#pragma once

//==========================================
//インクルード
#include "main.h"
#include "object.h"
#include "objectmanagerX.h"
#include "objectX.h"

class CRenderer
{
public:
	CRenderer();                                                 //コンストラクタ
	~CRenderer();                                                //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //初期化処理
	void Uninit();                                               //破棄処理
	void Update();                                               //更新処理
	void Draw();                                                 //描画処理
	void DrawFPS();                                              //FPSを描画する処理
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }       //３Dデバイスを取得
	bool& GetPause() { return m_bPause; }                        //ポーズ中かどうかの判定を取得
	bool& GetDrawShader() { return m_bDrawShader; }              //シェーダーを使うかどうかの判定を取得

private:
	LPDIRECT3D9 m_pD3D;                                          //Direct3Dの主要情報
	LPDIRECT3DDEVICE9 m_pD3DDevice;                              //Direct3Dデバイス
	LPD3DXFONT m_pFont;                                          //フォントの情報
	bool m_bPause;                                               //ポーズ中かどうかの判定をする用の変数
	bool m_bDrawShader;                                          //シェーダーを描画するかどうか
};

