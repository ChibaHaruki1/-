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
	m_nSocre = CObject2D::N_INIT_NUMBER;  //初期化
	m_fPosX = CObject2D::F_INIT_NUMBER;   //X軸の位置の初期化
	m_fPosY = CObject2D::F_INIT_NUMBER;   //Y軸の位置の初期化
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
	for (int nCountScore = CObject2D::N_INIT_NUMBER; nCountScore < MAX_SCORE; nCountScore++)
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
	CMain::CMain::VERTEX_2D* pVtx; //バーテクスのポインター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, CObject2D::N_INIT_NUMBER);

	//最大数分回す
	for (int nCutScore = CObject2D::N_INIT_NUMBER; nCutScore < MAX_SCORE; nCutScore++)
	{
		//スコアが使用されていない
		if (m_aScore[nCutScore].bUse == false)
		{
			m_aScore[nCutScore].pos = pos;   //位置を引数と同期させる
			m_aScore[nCutScore].bUse = true; //使用している状態へ

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, CObject2D::F_INIT_NUMBER);
			pVtx[1].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y - MAX_SIZE_Y, CObject2D::F_INIT_NUMBER);
			pVtx[2].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x - MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, CObject2D::F_INIT_NUMBER);
			pVtx[3].pos = D3DXVECTOR3(m_aScore[nCutScore].pos.x + MAX_SIZE_X, m_aScore[nCutScore].pos.y + MAX_SIZE_Y, CObject2D::F_INIT_NUMBER);

			break; //処理を抜ける
		}
		pVtx += MOVE_PVTX; //バーテクスの移動
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
	int nDight = INIT_DIGIT; //桁管理用

	CMain::VERTEX_2D* pVtx;         //バーテクスのポインター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, CObject2D::N_INIT_NUMBER);

	m_nSocre = nScore;       //引数と同期させる

	//最大数分回す
	for (int nCalculationScore = CObject2D::N_INIT_NUMBER; nCalculationScore < MAX_SCORE; nCalculationScore++)
	{
		nDight *= DIGIT;                                                                                 //桁を増やすために１０で乗算していく
		nPosTexU[MAX_SCORE - nCalculationScore - BEFORE_DIGIT] = (nScore % nDight * MAX_SCORE) / nDight; //テクスチャの分割した部分の位置を計算する
	}

	//最大数分回す
	for (int nScoreTexture = CObject2D::N_INIT_NUMBER; nScoreTexture < MAX_SCORE; nScoreTexture++)
	{
		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (ADJUST_TEX_POS_X / FMAX_SCORE)), CObject2D::F_INIT_NUMBER);
		pVtx[1].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (ADJUST_TEX_POS_X / FMAX_SCORE)) + (ADJUST_TEX_POS_X / FMAX_SCORE), CObject2D::F_INIT_NUMBER);
		pVtx[2].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (ADJUST_TEX_POS_X / FMAX_SCORE)), ADJUST_TEX_POS_X);
		pVtx[3].tex = D3DXVECTOR2((nPosTexU[nScoreTexture] * (ADJUST_TEX_POS_X / FMAX_SCORE)) + (ADJUST_TEX_POS_X / FMAX_SCORE), ADJUST_TEX_POS_Y);

		pVtx += MOVE_PVTX; //バーテクスの移動
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
	for (int nCutScore = CObject2D::N_INIT_NUMBER; nCutScore < MAX_SCORE; nCutScore++)
	{
		SetScorepos(D3DXVECTOR3(m_fPosX, SCORE_POSY, CObject2D::F_INIT_NUMBER));   //位置
		m_fPosX += PLUSSCORE_POSX;                                      //ｘ軸の位置を増やす
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
		pScore = new CResultScore();                                         //継承クラスで動的確保
		pScore->SetFileNamePass("data\\TEXTURE\\UI\\Score\\number001.png");  //テクスチャのパス設定
		pScore->m_fPosX = CORE_POSX;                                         //位置を調整
	}

	//リザルトの時
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pScore = new CResultScore();                                         //継承クラスで動的確
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