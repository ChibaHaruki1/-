//===================================
//
//スコアの処理[score.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
//======================
CManagerScore::CManagerScore(int nPriority) : CObject2D(nPriority)
{
	m_nSocre = 0;     //初期化
	m_fPosX = 0.0f;   //X軸の位置の初期化
	m_fPosY = 0.0f;   //Y軸の位置の初期化
}

//======================
//デストラクタ
//======================
CManagerScore::~CManagerScore()
{

}

//======================
//初期化処理
//======================
HRESULT CManagerScore::Init()
{
	//初期化が失敗した時
	if (FAILED(SelectInit(MAX_SCORE, DIVISION_SCORE)))
	{
		return E_FAIL; //失敗を返す
	}

	PosScore();        //配置処理

	return S_OK;       //成功を返す
}

//======================
//終了処理
//======================
void CManagerScore::Uninit()
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}

//=======================
//更新処理
//=======================
void CManagerScore::Update()
{

}

//=====================
//描画処理
//=====================
void CManagerScore::Draw()
{
	//最大数分回す
	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		//スコアが使用されている
		if (m_aScore[nCountScore].bUse == true)
		{
			CObject2D::MultipleDraw(nCountScore); //描画処理を呼ぶ
		}
	}
}

//=======================
//位置処理
//=======================
void CManagerScore::SetScorepos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx; //バーテクスのポインター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	//最大数分回す
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		//スコアが使用されていない
		if (m_aScore[nCutScore].bUse == false)
		{
			m_aScore[nCutScore].pos = pos;   //位置を引数と同期させる
			m_aScore[nCutScore].bUse = true; //使用している状態へ

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, 0.0f);

			break; //処理を抜ける
		}
		pVtx += 4; //バーテクスの移動
	}

	//頂点バッファをアンロック
	GetBuffer()->Unlock();
}

//=======================
//設定処理
//=======================
void CManagerScore::SetScore(int nScore)
{
	int nPosTexU[MAX_SCORE]; //テクスチャの分割した位置を保管
	int nDight = 1;          //桁管理用

	VERTEX_2D* pVtx;         //バーテクスのポインター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	m_nSocre = nScore;       //引数と同期させる

	//最大数分回す
	for (int nCalculationScore = 0; nCalculationScore < MAX_SCORE; nCalculationScore++)
	{
		nDight *= DIGIT;                                                                      //桁を増やすために１０で乗算していく
		nPosTexU[MAX_SCORE - nCalculationScore - 1] = (nScore % nDight * MAX_SCORE) / nDight; //テクスチャの分割した部分の位置を計算する
	}

	//最大数分回す
	for (int nScoreTexture = 0; nScoreTexture < MAX_SCORE; nScoreTexture++)
	{
		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)) + (1.0f / FMAX_SCORE), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (1.0f / FMAX_SCORE)) + (1.0f / FMAX_SCORE), 1.0f);

		pVtx += 4; //バーテクスの移動
	}

	//頂点バッファをアンロック
	GetBuffer()->Unlock();
}

//==============================
//スコアを減算する処理
//==============================
void CManagerScore::AddScore(int nValue)
{
	//オブジェクトの配置情報がある時
	if (CManager::GetObjectSet() != nullptr)
	{
		CManager::GetObjectSet()->GetClearScore() += nValue; //加算
	}

	SetScore(m_nSocre + nValue);                             //テクスチャのスコアを加算
}

//==============================
//初期化時のスコアを減算する処理
//==============================
void CManagerScore::InitAddScore(int nValue)
{
	SetScore(m_nSocre + nValue);                             //テクスチャのスコアを加算
}

//=====================
//位置設定
//=====================
void CManagerScore::PosScore()
{
	//最大数分回す
	for (int nCutScore = 0; nCutScore < MAX_SCORE; nCutScore++)
	{
		SetScorepos(D3DXVECTOR3(m_fPosX, SCORE_POSY, 0.0f));   //位置
		m_fPosX += PLUSSCORE_POSX;                             //ｘ軸の位置を増やす
	}
}

//================
//生成処理
//================
CManagerScore* CManagerScore::Create(CScene::MODE mode, int Number)
{
	CManagerScore* pScore = nullptr; //基底クラスのポインター

	//ゲーム１の時
	if (mode == CScene::MODE::MODE_GAME01)
	{
		pScore = new CResultScore(3);                                        //継承クラスで動的確保
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number001.png");  //テクスチャのパス設定
		pScore->m_fPosX = CORE_POSX;                                         //位置を調整
	}

	//リザルトの時
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pScore = new CResultScore(3);                                        //継承クラスで動的確
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number002.png");  //テクスチャのパス設
		pScore->m_fPosX = CORE_POS1X;									     //位置を調整
	}

	//情報がある時
	if (pScore != nullptr)
	{
		//初期化が成功した時
		if (SUCCEEDED(pScore->Init()))
		{
			pScore->Lood();                //テクスチャの読み込み
			pScore->InitAddScore(Number);  //スコアの初期値を引数と同期
			return pScore;                 //情報を返す
		}
	}

	return nullptr;                    //無を返す
}


//=======================================================================================================================
//ゲーム中のスコア処理
//=======================================================================================================================

//======================
//コンストラクタ
//======================
CGameScore::CGameScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//デストラクタ
//======================
CGameScore::~CGameScore()
{

}


//=======================================================================================================================
//リザルトのスコア処理
//=======================================================================================================================

//======================
//コンストラクタ
//======================
CResultScore::CResultScore(int nPriority) : CManagerScore(nPriority)
{

}

//======================
//デストラクタ
//======================
CResultScore::~CResultScore()
{

}