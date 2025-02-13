//=========================================
//
//3Dオブジェクトの処理[object3D.cpp]
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//インクルード
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//引数付きコンストラクタ
//=============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;                                              //テクスチャのポインターの初期化
	m_pVtxBuff = nullptr;                                              //バーテクスのポインターの初期化
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);  //向きを初期化する
	m_nLife = N_INIT_NUMBER;                                           //ライフの初期化
	m_nAlpha = N_INIT_ALPHA_NUMBER;                                    //アルファ値の初期化
	m_nFrame = N_INIT_NUMBER;                                          //フレームの初期化
	m_nRandom = N_INIT_NUMBER;                                         //乱数の初期化
	m_fSizeX = F_INIT_NUMBER;                                          //X軸の大きさの初期化
	m_fSizeY = F_INIT_NUMBER;                                          //Y軸の大きさの初期化
	m_aFileName = nullptr;                                             //ファイルパスの初期化
}


//=====================
//デストラクタ
//=====================
CObject3D::~CObject3D()
{

}


//=====================
//初期化処理
//=====================
HRESULT CObject3D::Init()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスの取得	

	//初期化
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //位置の初期化
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //向きの初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_3D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[PVTX_NUMBER_0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

	//法線ベクトルの設定
	pVtx[PVTX_NUMBER_0].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_1].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_3].nor = D3DXVECTOR3(F_INIT_NUMBER, CMain::NOR, F_INIT_NUMBER);

	//頂点カラーの設定
	pVtx[PVTX_NUMBER_0].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_1].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_2].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);
	pVtx[PVTX_NUMBER_3].col = D3DCOLOR_RGBA(N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER, N_INIT_COL_NUMBER);

	//テクスチャ座標の設定
	pVtx[PVTX_NUMBER_0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV座標に注意（上限１．０ｆ）
	pVtx[PVTX_NUMBER_1].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, F_INIT_NUMBER);
	pVtx[PVTX_NUMBER_2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[PVTX_NUMBER_3].tex = D3DXVECTOR2(CMain::MAX_TEXTURE_SIZE, CMain::MAX_TEXTURE_SIZE);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK; //成功を返す
}


//=====================================
//ビルボード時の初期化設定
//=====================================
HRESULT CObject3D::BillboardInit()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスの取得

	//初期化
	m_pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);//位置の初期化
	m_rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //向きの初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CMain::VERTEX_3D) * PVTX_NUMBER_OF, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[1].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);
	pVtx[3].pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[1].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[2].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);
	pVtx[3].nor = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, -CMain::NOR);

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


//==================
//終了処理
//==================
void CObject3D::Uninit()
{
	//頂点バッファの情報がある時
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release(); //情報を消す
		m_pVtxBuff = nullptr;  //情報を無くす
	}

	//テクスチャの情報がある時
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release(); //情報を消す
		m_pTexture = nullptr;  //情報を無くす
	}
}


//==================
//更新処理
//==================
void CObject3D::Update()
{
	//位置を更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//移動量を更新（減衰させる）
	m_pos.x += (F_INIT_NUMBER - m_move.x) * UPDATE_MOVE; //少ないほうが早く、ぬるぬる動く
	m_pos.y += (F_INIT_NUMBER - m_move.y) * UPDATE_MOVE; //少ないほうが早く、ぬるぬる動く
	m_pos.z += (F_INIT_NUMBER - m_move.z) * UPDATE_MOVE; //少ないほうが早く、ぬるぬる動く
}


//==================
//サイズの設定
//==================
void CObject3D::SetSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, -SIZE_Y, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=========================================
//必殺エフェクト用のサイズの設定(X軸用)
//=========================================
void CObject3D::SetEffectSize(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(F_INIT_NUMBER, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(F_INIT_NUMBER, -SIZE_Y, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, -SIZE_Y, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=======================
//Y軸用のサイズの設定
//=======================
void CObject3D::SetAdjustmentSizeY(float SIZE_X, float SIZE_Y, float SIZE_Z)
{
	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z);
	pVtx[1].pos = D3DXVECTOR3(SIZE_X * HALF, SIZE_Y, -SIZE_Z);
	pVtx[2].pos = D3DXVECTOR3(-SIZE_X, F_INIT_NUMBER, SIZE_Z);
	pVtx[3].pos = D3DXVECTOR3(SIZE_X * HALF, F_INIT_NUMBER, SIZE_Z);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===================================================
//色の設定処理
//===================================================
void CObject3D::SetCol(int Red, int Green, int Blue,int& Alpha)
{
	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(Red, Green, Blue, Alpha);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//===================================================
//テクスチャの大きさを設定させる
//===================================================
void CObject3D::SetTexture(float SizeX, float Size1X)
{
	CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFF_NUMBE, BUFF_NUMBE, (void**)&pVtx, N_INIT_NUMBER);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(F_INIT_NUMBER, F_INIT_NUMBER); //UV座標に注意（上限１．０ｆ）
	pVtx[1].tex = D3DXVECTOR2(SizeX, F_INIT_NUMBER);
	pVtx[2].tex = D3DXVECTOR2(F_INIT_NUMBER, CMain::MAX_TEXTURE_SIZE);
	pVtx[3].tex = D3DXVECTOR2(Size1X, CMain::MAX_TEXTURE_SIZE);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//================================
//各パーツ毎の当たり判定処理（選択）
//================================
bool CObject3D::CollisionPrtsPlayer(float X, float Y, float Z)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = N_INIT_NUMBER; nCount < CObjectX::MAX_PARTS; nCount++)
	{
		//プレイヤーのパーツと引数との当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount)) == true)
		{
			return true; //成功
		}
	}
	return false;        //失敗
}

//================================
//各パーツ毎の当たり判定処理
//================================
bool CObject3D::CollisionPrts1Left(float X, float Y, float Z)
{
	//プレイヤーの左パーツ毎の当たり判定処理
	for (int nCount = N_INIT_NUMBER; nCount < CCharacter::NUM_RIGHTLEFTPRTS; nCount++)
	{
		//左肩～の左パーツの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_LEFT_SHOLDER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_LEFT_SHOLDER)) == true)
		{
			return true; //当たった       
		}

		//左ふともも～の左パーツの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DLeft(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_LEFT_THIGHS), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_LEFT_THIGHS)) == true)
		{
			return true; //当たった        
		}
	}

	//胴体
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(CCharacter::PLAYER_PARTS_BODY_NUMBER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(CCharacter::PLAYER_PARTS_BODY_NUMBER)) == true)
	{
		return true;     //当たった         
	}

	return false;        //当たっていない
}

//================================
//各パーツ毎の当たり判定処理
//================================
bool CObject3D::CollisionPrts1Right(float X, float Y, float Z)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = N_INIT_NUMBER; nCount < CCharacter::NUM_RIGHTLEFTPRTS; nCount++)
	{
		//右肩からの右パーツの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_SHOLDER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_SHOLDER)) == true)
		{
			return true; //当たった
		}

		//右ふともも～の右パーツの当たり判定
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3DRight(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_THIGHS), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount + CCharacter::PLAYER_PARTS_RIGHT_THIGHS)) == true)
		{
			return true; //当たった
		}
	}

	//胴体
	if (CManager::GetScene()->GetPlayerX()->GetCollision()->ColiisionBox3D(m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(CCharacter::PLAYER_PARTS_BODY_NUMBER), X, Y, Z, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(CCharacter::PLAYER_PARTS_BODY_NUMBER)) == true)
	{
		return true;     //当たった
	}

	return false;        //当たっていない
}


//==================
//描画処理
//==================
void CObject3D::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans;                        //計算用マトリックス

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

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}

//===========================
//ビルボード描画処理
//===========================
void CObject3D::DrawBillboard()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans;                        //計算用マトリックス
	D3DXMATRIX mtxView;                                 //ビューマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得取得用;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	//マトリックス行列の調整
	m_mtxWorld._41 = F_INIT_NUMBER;
	m_mtxWorld._42 = F_INIT_NUMBER;
	m_mtxWorld._43 = F_INIT_NUMBER;

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);
}


//===========================
//エフェクト時の描画処理
//===========================
void CObject3D::DrawEffect()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans;                        //計算用マトリックス
	D3DXMATRIX mtxView;                                 //ビューマトリックス

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得取得用;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	//マトリックス行列の調整
	m_mtxWorld._41 = F_INIT_NUMBER;
	m_mtxWorld._42 = F_INIT_NUMBER;
	m_mtxWorld._43 = F_INIT_NUMBER;

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(0, m_pTexture);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, N_INIT_NUMBER);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//aブレンディを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//======================================================
//エフェクト時の描画処理(Zバッファを書き込まない)
//======================================================
void CObject3D::DrawEffect1()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView;          //ビューマトリックス

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

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

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(STREAMNUMBER, m_pVtxBuff, STREAMNUMBER, sizeof(CMain::VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャに設定
	pDevice->SetTexture(N_INIT_NUMBER, m_pTexture);

	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, N_INIT_NUMBER);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, STARTVERTEX, PRIMITIVECOUNT);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//aブレンディを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//===================================
//テクスチャファイルの読み込み
//===================================
HRESULT CObject3D::Lood()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	//テクスチャのファイルがない時
	if (FAILED(D3DXCreateTextureFromFile(pDevice, m_aFileName, &m_pTexture)))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}