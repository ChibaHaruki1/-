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
	CRenderer();                                                   //コンストラクタ
	~CRenderer();                                                  //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);    //初期化処理
	void Uninit();                                                 //破棄処理
	void Update();                                                 //更新処理
	void Draw();                                                   //描画処理
	void DrawFPS();                                                //FPSを描画する処理


	//==================================
	//情報の取得
	inline LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }  //３Dデバイスを取得
	inline bool& GetPause() { return m_bPause; }                   //ポーズ中かどうかの判定を取得
	inline bool& GetDrawShader() { return m_bDrawShader; }         //シェーダーを使うかどうかの判定を取得
																   
private:					

	//=====================================
	//FPSに関するマクロ定義
	static constexpr int MAX_STR = 10;                             //FPS表示時の文字列の最大数
	static constexpr int DRAW_LONG_TEXT = -1;                      //描画のテキストのカウント（長さ＝ー１の時nullになり自動化される）


	//=====================================
	//フォントに関するマクロ定義
	static constexpr int FONT_HEIGHT = 18;                         //高さ
	static constexpr int FONT_WIDTH = 0;                           //幅
	static constexpr int FONT_WEIGHT = 0;                          //重さ
	static constexpr int FONT_MIPLEVELS = 0;                       //解像度(低くなっていく)


	//=====================================
	//画面クリアに関するマクロ定義
	static constexpr int CLEAR_STENCIL = 0;                        //ステンシル値

	static constexpr float CLEAR_Z = 1.0f;                         //Z値

	LPDIRECT3D9 m_pD3D;                                            //Direct3Dの主要情報
	LPDIRECT3DDEVICE9 m_pD3DDevice;                                //Direct3Dデバイス
	LPD3DXFONT m_pFont;                                            //フォントの情報
	bool m_bPause;                                                 //ポーズ中かどうかの判定をする用の変数
	bool m_bDrawShader;                                            //シェーダーを描画するかどうか
};

