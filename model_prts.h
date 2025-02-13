//==========================================================
//
//モーションの各パーツごとのクラス管理[model_prts.h]
//Auther;Chiba Haruki
//
//==========================================================


#pragma once


//==========================================================
//インクルード
#include "main.h"


class CModelPrts
{
public:
	CModelPrts();                    //コンストラクタ
	~CModelPrts();                   //デストラクタ
	HRESULT Init();                  //初期化処理
	void Uninit();                   //破棄処理
	void Update();                   //更新処理
	void Draw(D3DXMATRIX MtxWolrd);  //描画処理
	void Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat);  //テクスチャの読み込みObjectXと同期させるために引数                                  //Xファイルの読み込み
	void BindSize(D3DXVECTOR3&max, D3DXVECTOR3&min, D3DXVECTOR3&ModelSize); //各モデルのパーツの大きさを渡す処理関数（ObjectXと同期の為引数）
	void Size();                                      //各モデルのパーツの大きさを求める処理関数
	static CModelPrts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat); //生成処理

	//=================================================
	//情報の取得
	D3DXVECTOR3& GetPos() { return m_pos; }                  //位置の取得
	D3DXVECTOR3& GetRot() { return m_rot; }                  //向きの取得
	D3DXMATRIX& GetWorldMtx() { return m_mtxWorld; }         //マトリックスの取得

	int& GetIndexPrts() { return m_nIndexPrts; }             //何番目のパーツか取得
	int& GetIndexModelPrts() { return m_nIndexModelPrts; }   //親パーツの取得

	bool& GetDraw() { return m_bDraw; }                      //描画するかどうかを取得


	//=================================================
	//情報の設定
	void SetParent(CModelPrts* pParent) { m_pParentlPrts = pParent; } //親パーツの設定
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }                     //位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }                     //向きの設定
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }                     //描画するかどうかを設定

private:
	//マクロ定義
	static constexpr int N_INIT_NUMBER = 0;            //int型の初期化の値  
	static constexpr float F_INIT_NUMBER = 0.0f;       //float型の初期化の値

	static constexpr int MAX_MODEL_TEXTURE = 32;       //テクスチャの最大数

	static constexpr float ADJUST_ROT_NUMBER = -1;     //向きの調整値

	CModelPrts* m_pParentlPrts;                        //自分のポインター
	D3DXVECTOR3 m_pos;                                 //位置
	D3DXVECTOR3 m_rot;                                 //向き
	D3DXMATRIX m_mtxWorld;                             //マトリックス
	LPD3DXMESH m_pMesh;                                //メッシュのへのポインタ
	LPD3DXBUFFER m_pBuffMat;                           //バッファのポインタ
	DWORD m_nNumMat;                                   //マテリアル数
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE];  //テクスチャへのポインタ

	//モデルサイズの取得
	D3DXVECTOR3 m_min;                                 //頂点の最小値
	D3DXVECTOR3 m_max;                                 //頂点の最大値
	D3DXVECTOR3 m_ModelSize;                           //モデルのサイズを格納

	int m_nIndexPrts;                                  //何番目のパーツ
	int m_nIndexModelPrts;                             //親のパーツ

	bool m_bDraw;                                      //描画するかしないかを判定する用の変数
};
