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
	m_pTexture = nullptr;                                              //テクスチャのポインターの初期化
	m_pVtxBuff = nullptr;                                              //バッファのポインターの初期化
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //向きを初期化する
	m_nRandom = N_INIT_NUMBER;                                         //乱数の初期化
	m_nFrame = N_INIT_NUMBER;                                          //フレームの初期化
	m_nAlpha = N_INIT_NUMBER;                                          //アルファ値の初期化
	m_aFileName = nullptr;                                             //ファイルパスの初期化
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
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_2D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_2D* pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, CMain::SCREEN_HEIGHT, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(CMain::SCREEN_WIDTH, CMain::SCREEN_HEIGHT, F_INIT_NUMBER);

	//rhwの設定
	pVtx[0].rhw = CMain::RHW;
	pVtx[1].rhw = CMain::RHW;
	pVtx[2].rhw = CMain::RHW;
	pVtx[3].rhw = CMain::RHW;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, F_INIT_NUMBER);
	pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[3].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, CMain::MAX_TEXTURE_SIZE);

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
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_2D) * PVTX_NUMBER_OF * nPieces, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetBuffer(), NULL);

	CMain::VERTEX_2D* pVtx;  //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//引数分回す
	for (int nCutScore = N_INIT_NUMBER; nCutScore < nPieces; nCutScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
		pVtx[3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

		//rhwの設定
		pVtx[0].rhw = CMain::RHW;
		pVtx[1].rhw = CMain::RHW;
		pVtx[2].rhw = CMain::RHW;
		pVtx[3].rhw = CMain::RHW;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
		pVtx[3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV座標に注意（上限１．０ｆ）
		pVtx[1].tex = D3DXVECTOR2(nTexture, F_INIT_NUMBER);
		pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
		pVtx[3].tex = D3DXVECTOR2(nTexture, CMain::MAX_TEXTURE_SIZE);

		pVtx += PVTX_NUMBER_OF;                                  //頂点データのポインタを４つ分進める
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
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャに設定
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}

//=====================
//複数描画する処理
//=====================
void CObject2D::MultipleDraw(int nPieces)
{
	CRenderer* pRenderer = CManager::GetRenderer(); //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = nullptr;            //デバイスのポインタ	

	UINT uStartVerTex = nPieces * PVTX_NUMBER_OF;

	//デバイスの取得
	pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャに設定
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, uStartVerTex, PRIMITIVECOUNT);
}



//==================
//サイズの設定
//==================
void CObject2D::SetSIze(float SIZE_X, float SIZE1_X, float SIZE_Y, float SIZE1_Y)
{
	CMain::VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SIZE_X, SIZE_Y, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(SIZE1_X, SIZE_Y, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(SIZE_X, SIZE1_Y, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(SIZE1_X, SIZE1_Y, F_INIT_NUMBER);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================
//サイズの設定
//==================
void CObject2D::SetCol(int Red, int Green, int Blue, int Alph)
{
	CMain::VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

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

	return S_OK;       //成功を返す
}
