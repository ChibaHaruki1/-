//======================================
//
//パーツ毎の処理[model_prts.cpp]
//Auther: Haruki Chiba
//
//======================================


//======================================
//インクルード
#include "model_prts.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
//======================
CModelPrts::CModelPrts()
{
	//テクスチャの最大数分回す
	for (int nCount = N_INIT_NUMBER; nCount < MAX_MODEL_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr;     //テクスチャの初期化
	}

	m_nIndexPrts = N_INIT_NUMBER;         //パーツ番号の初期化
	m_nIndexModelPrts = N_INIT_NUMBER;    //親パーツ番号の初期化
	m_bDraw = true;                       //描画をする
	m_nNumMat = N_INIT_NUMBER;            //マテリアルの数の初期化
	m_pMesh = nullptr;                    //メッシュの初期化
	m_pBuffMat = nullptr;                 //バッファの初期化
	m_pParentlPrts = nullptr;             //自身のポインターの初期化
}

//=======================
//デストラクタ
//=======================
CModelPrts::~CModelPrts()
{

}

//======================
//初期化処理
//======================
HRESULT CModelPrts::Init()
{
	return S_OK; //成功を返す
}

//========================
//破棄処理
//========================
void CModelPrts::Uninit()
{
	//メッシュの情報がある時
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release(); //メッシュの削除
		m_pMesh = nullptr;  //情報を無くす
	}

	//バッファの情報がある時
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release(); //バッファの削除
		m_pBuffMat = nullptr;  //情報を無くす
	}

	//テクスチャの最大数分回す
	for (int nCntMat = N_INIT_NUMBER; nCntMat < MAX_MODEL_TEXTURE; nCntMat++)
	{
		//テクスチャの情報がある時
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release(); //テクスチャの削除
			m_pTexture[nCntMat] = nullptr;  //情報を無くす
		}
	}
}

//========================
//更新処理
//========================
void CModelPrts::Update()
{

}

//========================
//描画処理
//========================
void CModelPrts::Draw(D3DXMATRIX MtxWolrd)
{
	//描画する時
	if (m_bDraw == true)
	{
		CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

		D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent; //計算用マトリックス
		D3DMATERIAL9 matDef;                              //現在のマテリアルの保存用
		D3DXMATERIAL* pMat;                               //マテリアルのポインター

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//-----向きを反映-----
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//-----位置を反映-----
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//自身のポインターの情報がある時
		if (m_pParentlPrts != nullptr)
		{
			mtxParent = m_pParentlPrts->GetWorldMtx(); //マトリックスを自身の物と同期させる
		}
		else
		{
			mtxParent = MtxWolrd;                      //マトリックスを引数の物と同期させる
		}

		//マトリックスに代入
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを収得
		pDevice->GetMaterial(&matDef);

		//materialポインターの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		//マテリアルの数分回す
		for (int nCount = N_INIT_NUMBER; nCount < (int)m_nNumMat; nCount++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCount].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(N_INIT_NUMBER, m_pTexture[nCount]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCount);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//============================================
//パーツの読み込み処理
//============================================
void CModelPrts::Lood(const char* Filepass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL* pMat)
{
	//CRenderer* pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	//HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh);


	CRenderer* pRenderer = CManager::GetRenderer();      //レンダラーの取得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();  //デバイスの取得


	HRESULT result = D3DXLoadMeshFromX(Filepass, D3DXMESH_SYSTEMMEM, pDevice, NULL, &pBufferMat, NULL, &dw_NumMat, &pMesh); //Xファイルの読み込み

	m_pMesh = pMesh;          //メッシュを引数と同期させる
	m_pBuffMat = pBufferMat;  //バッファを引数と同期させる
	m_nNumMat = dw_NumMat;    //マテリアルの数を引数と同期させる

	//マテリアルデータへのポインタを収得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nNumTexture = N_INIT_NUMBER; //テクスチャの数をカウントするための変数

	//マテリアルの数分回す
	for (int nCntMat = N_INIT_NUMBER; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//テクスチャファイルが存在する
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]); //テクスチャファイルを作る
			nNumTexture++;                                                                                //カウントを進める
		}
	}
}

//=========================
//生成
//=========================
CModelPrts* CModelPrts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* m_aPrtsPass, LPD3DXMESH pMesh, LPD3DXBUFFER pBufferMat, DWORD dw_NumMat, D3DXMATERIAL*pMat)
{
	CModelPrts* pModelPrts = new CModelPrts(); //動的確保

	//情報がある時
	if (pModelPrts != nullptr)
	{
		pModelPrts->Init();                                             //初期化処理
		pModelPrts->m_pos = pos;                                        //位置を引数と同期させる
		pModelPrts->m_rot = rot;                                        //向きを引数と同期させる
		pModelPrts->Lood(m_aPrtsPass,pMesh,pBufferMat,dw_NumMat,pMat);  //ｘファイルの読み込み処理(引数で情報を渡す)
		pModelPrts->Size();                                             //サイズの取得

		return pModelPrts; //情報を返す
	}

	return nullptr; //無を返す
}


//==================
//サイズの取得
//==================
void CModelPrts::Size()
{
	int nNumVertex; //頂点数の格納
	DWORD dSIze;    //頂点のフォーマットサイズ取得情報を保管する
	BYTE* pVtxByte; //頂点フォーマットの取得

	//頂点数を取得
	nNumVertex = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズ取得
	dSIze = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点メッシュのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxByte);

	//頂点数分回す
	for (int nCount = N_INIT_NUMBER; nCount < nNumVertex; nCount++)
	{
		//位置を代入するための変数
		D3DXVECTOR3 mtx;

		mtx = *(D3DXVECTOR3*)pVtxByte; //頂点フォーマットをD3DXVECTOR3に変換


		//=================================
		//X軸用
		//=================================

		//取得した数値が一番大きい時
		if (mtx.x > m_max.x)
		{
			m_max.x = mtx.x; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.x < m_min.x)
		{
			m_min.x = mtx.x; //代入
		}


		//=================================
		//Y軸用
		//=================================  

		//取得した数値が一番大きい時
		if (mtx.y > m_max.y)
		{
			m_max.y = mtx.y; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.y < m_min.y)
		{
			m_min.y = mtx.y; //代入
		}


		//=================================
		//Z軸用
		//================================= 
		 
		//取得した数値が一番大きい時
		if (mtx.z > m_max.z)
		{
			m_max.z = mtx.z; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.z < m_min.z)
		{
			m_min.z = mtx.z; //代入
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxByte += dSIze;
	}

	//最小値が０より小さい時
	if (m_min.y < N_INIT_NUMBER)
	{
		//最小値が最大値より大きい時
		if (m_max.y < m_min.y)
		{
			m_max.y = m_min.y * ADJUST_ROT_NUMBER; //最小値のプラス値を代入する
		}
		m_min.y = N_INIT_NUMBER; //最小値の初期化
	}

	//オブジェクトのサイズを計算する
	m_ModelSize = m_max - m_min;
}


//==================================================
//情報を同期させる処理
//==================================================
void CModelPrts::BindSize(D3DXVECTOR3& max, D3DXVECTOR3& min, D3DXVECTOR3& ModelSize)
{
	//引数の値を現在の値と同期させる
	max = m_max;              //モデルの最大値を同期させる
	min = m_min;              //モデルの最小値を同期させる
	ModelSize = m_ModelSize;  //モデルの大きさを同期させる
}