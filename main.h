//=================================
//
//DirectXメイン処理[main.h]
//Auther:Chiba Haruki
//
//=================================


#pragma once


//=================================
//インクルード
#include <Windows.h>
#define DIRECTINPUT_VERSION   (0x0800) //ビルド時の警告対処用マクロ(順番に注意)

#include "d3dx9.h"                     //DirectX9を使用
#include "dinput.h"                    //入力処理に必要
#include "Xinput.h"                    //ジョイパッド処理に必要
#include "xaudio2.h"                   //音を追加


//=================================
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")        //描画処理に必要
#pragma comment(lib,"d3dx9.lib")       //「ｄ３ｄ９．ｈＬＩＢ」の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")      //ＤＩＲＥＣＴＸコンポーネント（部品）に必要
#pragma comment(lib,"winmm.lib")       //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")     //入力処理に必要
#pragma comment(lib, "xinput.lib")     //ジョイパッド処理に必要


//=================================
//マクロ定義
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)              //2D用VERTWXの情報を設定
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)   //3D用VERTWXの情報を設定

//頂点情報の構造体
typedef struct
{
	D3DXVECTOR3 pos; //頂点情報
	float rhw;       //座標変換用係数（１．０ｆで固定）
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos; //頂点情報
	D3DXVECTOR3 nor; //法線情報
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_3D;


class CMain
{
public:
	CMain();                                  //コンストラクタ
	~CMain();                                 //デストラクタ
	void Uninit();                            //破棄処理
	int& GetFPS() {return m_nFPS; }           //FPSの値を取得する

	//マクロ定義
	constexpr static int SCREEN_WIDTH = 1280; //ウィンドウの幅
	constexpr static int SCREEN_HEIGHT = 720; //ウィンドウの高さ


private:
	int m_nFPS; //FPSの値を保管する用の変数
};