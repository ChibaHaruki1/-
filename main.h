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


class CMain
{
public:

	//2D頂点情報の構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //頂点情報
		float rhw;       //座標変換用係数（１．０ｆで固定）
		D3DCOLOR col;    //頂点カラー
		D3DXVECTOR2 tex; //テクスチャ座標
	}VERTEX_2D;

	//3D頂点情報の構造体
	typedef struct
	{
		D3DXVECTOR3 pos; //頂点情報
		D3DXVECTOR3 nor; //法線情報
		D3DCOLOR col;    //頂点カラー
		D3DXVECTOR2 tex; //テクスチャ座標
	}VERTEX_3D;

	CMain();                                         //コンストラクタ
	~CMain();                                        //デストラクタ
	void Uninit();                                   //破棄処理
	inline int& GetFPS() {return m_nFPS; }           //FPSの値を取得する


	//=============================
	//マクロ定義
	static constexpr UINT PERIOD = 1U;               //分解能の設定＿タイマーの最小解像度を要求する関数の値
	static constexpr LONG RECT = 0L;                 // ウィンドウの大きさの初期値
	static constexpr LONG POINT_POS = 100L;          //ポイントの位置
													  
	static constexpr  int SCREEN_WIDTH = 1280;       //ウィンドウの幅
	static constexpr  int SCREEN_HEIGHT = 720;       //ウィンドウの高さ
	static constexpr  int CLIENT_COL_PLUS = 1;       //クライアント領域の背景色の値の加算値
	static constexpr  int RETURN_NUMBER = -1;        //返す値
	static constexpr  int FPS_HALF_TIME = 500;       //FPS値の到達秒（０．５秒）
	static constexpr  int DIVISION = 1000;           //分割数(分子で１０００/６０＝１)
	static constexpr  int ONE_FRAME = DIVISION / 60; //１フレーム経過

	static constexpr float RHW = 1.0f;               //座標変換用の固定値
	static constexpr float NOR = 1.0f;               //法線ベクトルの固定値
	static constexpr float MAX_TEXTURE_SIZE = 1.0f;  //テクスチャの最大の大きさ


private:
	int m_nFPS; //FPSの値を保管する用の変数
};