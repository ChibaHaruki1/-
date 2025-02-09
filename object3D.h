//=======================================
//
//3Dオブジェクトクラス管理[object3D.h]
//Auther:Chiba Haruki
//
//=======================================


#pragma once


//=======================================
//インクルード
#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = DEFAULT_PRIORITY);                             //コンストラクタ
	~CObject3D() override;                                                   //デストラクタ
	HRESULT Init() override;                                                 //初期化処理
	HRESULT BillboardInit();                                                 //ビルボード時の初期化設定
	void Uninit() override;                                                  //破棄処理
	void Update()override;                                                   //更新処理
	void Draw() override;                                                    //描画処理
	void DrawBillboard();                                                    //ビルボードの描画処理
	void DrawEffect();                                                       //エフェクト用の描画処理
	void DrawEffect1();                                                      //エフェクト001用の描画処理
	void SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z);                  //サイズを調整する処理
	void SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z);            //エフェクト用polygonのサイズを調整する処理
	void SetAdjustmentSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z);       //Y軸用のサイズを調整する処理
	void SetCol(int Red, int Green, int Blue, int& Alpha);                   //色に関する設定
	void SetTexture(float SizeX, float Size1X);                              //テクスチャのサイズを設定する

	//当たり判定処理(ポリゴンとの当たり判定)
	bool CollisionPrts1Right(float X, float Y, float Z);     //パーツ毎の当たり判定　右側
	bool CollisionPrts1Left(float X, float Y, float Z);      //パーツ毎の当たり判定　左側
	bool CollisionPrtsPlayer(float X, float Y, float Z);     //パーツ毎の当たり判定　全体

	HRESULT Lood();                                          //テクスチャファイルの読み込み


	//==================================================
	//情報の取得
	LPDIRECT3DVERTEXBUFFER9& GetBuffer() { return m_pVtxBuff; } //バッファの取得
	LPDIRECT3DTEXTURE9& GetTexture() { return m_pTexture; }     //テクスチャの取得
	int& GetLife() { return m_nLife; }                          //ライフの取得
	int& GetAlpha() { return m_nAlpha; }                        //アルファ値を取得
	int& GetFrame() { return m_nFrame; }                        //フレームを取得
	int& GetRandom() { return m_nRandom; }                      //乱数を取得
	float& GetSizeX() { return m_fSizeX; }                      //X軸の大きさを取得
	float& GetSizeY() { return m_fSizeY; }                      //Y軸の大きさを取得


	//==================================================
	///三大基本情報の取得
	D3DXVECTOR3& GetPos() { return m_pos; }                     //位置の取得
	D3DXVECTOR3& GetMove() { return m_move; }                   //移動量の取得
	D3DXVECTOR3& GetRot() { return m_rot; }                     //向きの取得


	//==================================================
	//各情報の設定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                             //位置を引数と同期させる
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                             //向きを引数と同期させる
	void SetMove(D3DXVECTOR3 move) { m_move = move; }                         //移動量を引数と同期させる
	void SetLife(int nLife) { m_nLife = nLife; }                              //ライフを引数と同期させる
	void SetAlpha(int nAlpha) { m_nAlpha = nAlpha; }                          //アルファ値を引数と同期させる
	void SetFrame(int nFrame) { m_nFrame = nFrame; }                          //フレームを引数と同期させる
	void SetRandom(int nRandom) { m_nRandom = nRandom; }                      //乱数を引数と同期させる
	void SetSizeX(float fSizeX) { m_fSizeX = fSizeX; }                        //X軸の大きさを引数と同期させる
	void SetSizeY(float fSizeY) { m_fSizeY = fSizeY; }                        //X軸の大きさを引数と同期させる
	void SetFileNamePass(const char* aFileName) { m_aFileName = aFileName; }  //ファイルパスを引数と同期させる
	

	//==================================================
	//情報の値を計して設定
	D3DXVECTOR3& SetAdjustPos() { return m_pos; }                             //位置の値を変更したいときの設定
																	          
	int& SetAdjustLife() { return m_nLife; }                                  //ライフの値を変更したいときの設定
	int& SetAdjustAlpha() { return m_nAlpha; }                                //アルファ値の変更したいときの設定
	int& SetAdjustFrame() { return m_nFrame; }                                //フレームの値を変更したいときの設定
																	          
	float& SetAddjustSizeX() { return m_fSizeX; }                             //X軸の値を変更したいときの設定
	float& SetAddjustSizeY() { return m_fSizeY; }                             //Y軸の値を変更したいときの設定


	//==================================================
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;           //int型の初期化の値
	static constexpr float F_INIT_NUMBER = 0.0f;      //float型の初期化の値

	static constexpr int N_INIT_ALPHA_NUMBER = 255;   //アルファ値の初期値
	static constexpr int RED = 255;                   //赤色
	static constexpr int GREEN = 255;                 //緑色
	static constexpr int BLUE = 255;                  //青色

	static constexpr int PVTX_NUMBER_0 = 0;           //頂点情報のpvtxの番目
	static constexpr int PVTX_NUMBER_1 = 1;           //頂点情報のpvtxの１番目
	static constexpr int PVTX_NUMBER_2 = 2;           //頂点情報のpvtxの２番目
	static constexpr int PVTX_NUMBER_3 = 3;           //頂点情報のpvtxの３番目
	static constexpr int PVTX_NUMBER_OF = 4;          //pvtxの基本数



private:
	LPDIRECT3DTEXTURE9 m_pTexture;                                            //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;                                       //頂点バッファのポインタ
										                                      
	D3DXVECTOR3 m_pos;                                                        //位置
	D3DXVECTOR3 m_move;                                                       //移動量
	D3DXVECTOR3 m_rot;                                                        //向き
	D3DXMATRIX m_mtxWorld;                                                    //マトリックス
						                                                      
	int m_nLife;                                                              //ライフを保管する用の変数
	int m_nAlpha;                                                             //アルファ値を保管する用の変数
	int m_nFrame;                                                             //フレームを保管する用の変数
	int m_nRandom;                                                            //乱数を保管する用の変数
					                                                          
	float m_fSizeX;                                                           //ｘ軸のサイズの調整用変数
	float m_fSizeY;                                                           //ｙ軸のサイズの調整用変数
							                                                  
	const char* m_aFileName;                                                  //ファイルパスを保管する用の変数
};

