//=========================================
//
//２Ｄオブジェクトの処理[object2D.cpp]
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//インクルード
#include "main.h"
#include "object2D.h"
#include "rendererh.h"
#include "manager.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "collision.h"
#include "score.h"


//=============================
//引数付きコンストラクタ
//=============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;                   //テクスチャのポインターの初期化
	m_pVtxBuff = nullptr;                   //バッファのポインターの初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向きを初期化する
	m_nRandom = 0;                          //乱数の初期化
	m_nFrame = 0;                           //フレームの初期化
	m_aFileName = nullptr;                  //ファイルパスの初期化
	m_nAlpha = 0;                           //アルファ値の初期化
}


//=====================
//デストラクタ
//=====================
CObject2D::~CObject2D()
{

}


//=====================
//初期化処理
//=====================
HRESULT CObject2D:: Init()
{
	CRenderer *pRenderer = CManager::GetRenderer(); //レンダラーの取得

	LPDIRECT3DDEVICE9 pDevice;                      //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D* pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, CMain::SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, CMain::SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK; //成功を返す
}

//=====================
//選択式初期化処理
//=====================
HRESULT CObject2D::SelectInit(int nPieces,float nTexture)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice;                      //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * nPieces, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	VERTEX_2D* pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//引数分回す
	for (int nCutScore = 0; nCutScore < nPieces; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f); //UV座標に注意（上限１．０ｆ）
		pVtx[1].tex = D3DXVECTOR2(nTexture, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nTexture, 1.0f);

		pVtx += 4; //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}


//=====================
//終了処理（破棄）
//=====================
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release(); //情報を消す
		m_pVtxBuff = nullptr;  //情報を無くす
	}
}


//=====================
//更新処理
//=====================
void CObject2D::Update ()
{
	
}

//=====================
//描画処理
//=====================
void CObject2D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer(); //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================
//複数描画する処理
//=====================
void CObject2D::MultipleDraw(int nPieces)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //デバイスのポインタ	

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nPieces*4, 2);
}



//==================
//サイズの設定
//==================
void CObject2D::SetSIze(float SIZE_X, float SIZE1_X, float SIZE_Y, float SIZE1_Y)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SIZE1_X, SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SIZE_X, SIZE1_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SIZE1_X, SIZE1_Y, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================
//サイズの設定
//==================
void CObject2D::SetCol(int Red, int Green, int Blue, int Alph)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alph);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===============================
//テクスチャの読み込み処理
//===============================
HRESULT CObject2D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスの取得

	//テクスチャのファイルがない時
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL; //失敗を返す

	}
	return S_OK; //成功を返す
}
