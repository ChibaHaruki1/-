//===============================================
//
//２Ｄオブジェクトのクラス管理[object2D.h]
//Auther:Chiba Haruki
//
//===============================================


#pragma once


//===============================================
//インクルード
#include "object.h"
#include "input.h"


class CObject2D : public CObject
{
public:
	CObject2D(int nPriority=DEFAULT_PRIORITY);                              //コンストラクタ
	~CObject2D() override;                                                  //デストラクタ
	HRESULT Init() override;                                                //初期化処理
	HRESULT SelectInit(int nPieces,float nTexture);                         //個数、テクスチャのサイズの選択式初期化処理
	void Uninit() override;                                                 //破棄処理
	void Update() override;                                                 //更新処理
	void Draw() override;                                                   //描画処理
	void MultipleDraw(int nPieces) ;                                        //複数描画する処理
	void SetSIze(float SIZE_X,float SIZE1_X, float SIZE_Y, float SIZE1_Y);  //polygonのサイズを調整する処理
	void SetCol(int Red,int Green,int Blue,int Alph);                       //色を設定
	HRESULT Lood();	                                                        //テクスチャファイルの読み込み

	//==================================================
	//それぞれの処理に必要な情報を取得する
	LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; } //バッファの取得
	D3DXVECTOR3& GetCol() {return m_col;}                       //色の取得
	int& GetAlph() { return m_nAlpha; }                         //アルファ値を取得
	int& GetRandom() { return m_nRandom; }                      //乱数を取得
	int& GetFrame() { return m_nFrame; }                        //フレームを取得

	//==================================================
	//各情報の設定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }               //位置の設定	
	void SetAlph(int nAlph) { m_nAlpha = nAlph; }                //アルファ値を設定
	void SetRandom(int nRandom) { m_nRandom = nRandom; }        //乱数を設定
	void SetFrame(int nFrame) { m_nFrame = nFrame; }            //フレームを設定
	void SetFileNamePass(const char* aFileName) { m_aFileName = aFileName; } //ファイルパスを設定

	//==================================================
	///三大基本情報の取得
	D3DXVECTOR3& GetPos() { return m_pos; }                     //位置の取得
	D3DXVECTOR3& GetMove() { return m_move; }                   //移動量の取得
	D3DXVECTOR3& GetRot() { return m_rot; }                     //向きの取得


	//==================================================
	//情報の値を計して設定
	int& SetAdjustAlpha() { return m_nAlpha; }                 //アルファ値の変更したいときの設定


	//==================================================
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;                    //int型の初期化の値
	static constexpr float F_INIT_NUMBER = 0.0f;               //float型の初期化の値

	static constexpr int INIT_PRIORITY = 0;                    //プライオリティの初期値
	static constexpr int N_INIT_COL_NUMBER = 255;              //色の初期値

	static constexpr int N_INIT_ALPHA_NUMBER = 255;            //アルファ値の初期値
	 static constexpr  int RED = 255;                            //赤色
	 static constexpr  int GREEN = 255;                          //緑色
	 static constexpr  int BLUE = 255;                           //青色


private:
	LPDIRECT3DTEXTURE9 m_pTexture;                             //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;                        //頂点バッファのポインタ
	D3DXVECTOR3 m_pos;                                         //位置
	D3DXVECTOR3 m_move;                                        //移動量
	D3DXVECTOR3 m_rot;                                         //向き
	D3DXVECTOR3 m_col;                                         //色
									                           
	int m_nAlpha;                                              //アルファ値を保管する用の変数
	int m_nRandom;                                             //乱数を保管する用の変数
	int m_nFrame;                                              //フレームを観測する用の変数
									                           
	const char* m_aFileName;                                   //ファイルパスを保管する用の変数
};
 