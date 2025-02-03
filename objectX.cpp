//=========================================
//
//Xオブジェクトの処理[objectX.cpp]
//Auther:Chiba Haruki
//
//=========================================


//============================
//インクルード
#include "objectX.h"
#include "rendererh.h"
#include "manager.h"


//=============================
//引数付きコンストラクタ
//=============================
CObjectX::CObjectX(int nPriority) : CObjectManagerX(nPriority)
{
	//テクスチャの最大数分回す
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		m_pTexture[nCount] = nullptr;
	}

	//プレイヤーのパーツ数分回す
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_minParts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        //パーツの大きさの最小値
		m_maxParts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        //パーツの大きさの最大値
		m_ModelSizeParts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //パーツの大きさ
		m_posParts[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //パーツの位置
	}

	//ボスのパーツ数分回す
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_ModelSizePartsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //パーツの大きさ
		m_posPartsBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //パーツの位置
	}

	for (int nCount2 = 0; nCount2 < MAX_ENEMYPARTS; nCount2++)
	{
		m_ModelSizePartsEnemy[nCount2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //パーツの大きさ
		m_posPartsEnemy[nCount2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //パーツの位置
	}

	m_pMesh = nullptr;                      //メッシュポインターの初期化
	m_pBuffMat = nullptr;                   //バッファポインターの初期化
	m_dwNumMat = 0;                         //マテリアル数の初期化
	m_pMat = nullptr;                       //マテリアルポインターの初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置を初期化(位置を調整できる）
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化(移動速度を調整できる）
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //向きを初期化する
	m_col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //色の初期化

	m_nLife = 0;                            //ライフの初期化
	m_nRandom = 0;                          //乱数の初期化
	m_nFrame = 0;                           //フレームの初期化
	m_nDieFrame = 0;                        //死亡フレームの初期化
	m_fGravity = 0.0f;                      //重力加速度の初期化
	m_fAngle = 0.0f;                        //角度から長さを求める値の初期化
	m_pCollision = nullptr;                 //当たり判定のポインターの初期化
	m_aFileName = nullptr;                  //ファイルパスの初期化
	m_bGravityFlag = true;                  //重力フラグの初期化
	m_bJumpFlag = false;                    //飛んでいるかの判定用の初期化
	m_bOneFlag = false;                     //一度だけ処理を通したいフラグの初期化
	pUI = nullptr;                          //UIポインターの初期化
}


//=====================
//デストラクタ
//=====================
CObjectX::~CObjectX()
{
	//当たり判定の情報がある時
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;     //情報を消す
		m_pCollision = nullptr;  //情報を無くす
	}
}


//=====================
//初期化処理
//=====================
HRESULT CObjectX::Init()
{
	m_pCollision = new CCollision(); //当たり判定の情報を取得する
	return S_OK;                     //成功を返す
}


//=====================
//終了処理
//=====================
void CObjectX::Uninit()
{
	//メッシュの情報がある時
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release(); //情報を消す
		m_pMesh = nullptr;  //情報を無くす
	}

	//バッファの情報がある時
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release(); //情報を消す
		m_pBuffMat = nullptr;  //情報を無くす
	}

	//マテリアルの情報がある時
	if (m_pMat != nullptr)
	{
		m_pMat = nullptr;      //情報を無くす
	}

	//テクスチャの最大数分回す
	for (int nCntMat = 0; nCntMat < MAX_TEXTURE; nCntMat++)
	{
		//テクスチャの情報がある時
		if (m_pTexture[nCntMat] != nullptr)
		{
			m_pTexture[nCntMat]->Release(); //情報を消す
			m_pTexture[nCntMat] = nullptr;  //情報を無くす
		}
	}
}


//=======================
//更新処理
//=======================
void CObjectX::Update()
{
	//位置を更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//移動量を更新（減衰させる）
	m_move.x += (0.0f - m_move.x) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_move.y += (0.0f - m_move.y) * 0.5f; //少ないほうが早く、ぬるぬる動く
	m_move.z += (0.0f - m_move.z) * 0.5f; //少ないほうが早く、ぬるぬる動く
}


//=======================
//描画処理
//=======================
void CObjectX::Draw()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef;         //現在のマテリアルの保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを収得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを収得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//マテリアルの分回す
	for (int nCntMat1 = 0; nCntMat1 < (int)m_dwNumMat; nCntMat1++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&m_pMat[nCntMat1].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat1]);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat1);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===============================================================================================================================================================================
//重力処理(引数でもいいかも)
//===============================================================================================================================================================================
void CObjectX::Gravity()
{
	//重力ONの時
	if (m_bGravityFlag == true)
	{
		m_fGravity += MAX_GRAVITY_G; //重力加速度
		m_pos.y -= m_fGravity;       //プレイヤーのｙposに重力加速度をつける
	}
}

//======================================================================================================================================
//位置の同期処理
//======================================================================================================================================
void CObjectX::GravityTogether()
{
	m_fGravity = 0.0f; //重力の初期化

	//一回のみ飛ぶ
	if (m_bJumpFlag == true)
	{
		m_bJumpFlag = false; //フラグをflaseにする
	}
	m_bGravityFlag = true;   //重力をOnにする
}

//======================================================================================================================================
//ジャンプ処理
//======================================================================================================================================
void CObjectX::Junp(TYPE type, float fJumpPwer)
{
	//ジャンプフラグONの時
	if (m_bJumpFlag == true)
	{
		m_pos.y += fJumpPwer;  //pos.y値を加算させる

		//タイプがプレイヤーの時
		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->CCharacter::SetMotion(CCharacter::MOTIONSTATE::JUMP); //ジャンプモーションに設定
			CManager::GetScene()->GetPlayerX()->SetMotionType(true);                                  //モーションタイプの設定（特殊モーション）
		}

		//タイプがモーション付きの敵の時
		else if (type == TYPE::ENEMYINMOTION)
		{
			//ジャンプモーションに設定
			CManager::GetInstance()->GetEnemyInMotion(0)->CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			//CManager::GetInstance()->GetEnemyInMotion(0)->SetMotionType(true); //モーションタイプの設定（特殊モーション）
			m_pos.x += 3.0f;                                                   //X軸の位置を増やす
		}
		else if (type == TYPE::ENEMYINMOTION001)
		{
			//ジャンプモーションに設定
			CManager::GetInstance()->GetEnemyInMotion001(0)->CEnemyCharacter::SetMotionEnemy001(CEnemyCharacter::ENEMYMOTIONSTATE::ENEMYJUMP);
			//CManager::GetInstance()->GetEnemyInMotion001(0)->SetMotionType(true);
			m_pos.x += 3.0f;                                                   //X軸の位置を増やす
		}
	}
	else
	{
		//タイプがプレイヤーの時
		if (type == TYPE::PLAYER)
		{
			CManager::GetScene()->GetPlayerX()->SetMotionType(false); //特殊モーションをOff
		}
	}

	Gravity();  //重力処理を呼ぶ
}

//======================================================================================================================================
//引数で指定した目標に向かう処理
//======================================================================================================================================
void CObjectX::TargetHeadingTowards(CObjectX* pObject, float MAX_SPEED)
{
	//対角線の角度を算出する（目標ー自機）
	m_fAngle = atan2f(pObject->m_pos.x - m_pos.x, pObject->m_pos.z - m_pos.z);

	//移動処理
	m_move.x = sinf(m_fAngle) * MAX_SPEED;
	m_move.z = cosf(m_fAngle) * MAX_SPEED;

	m_rot.y = m_fAngle * -1; //向きをプレイヤーに合わせる
}


//================================================
//プレイヤーとボスの当たり判定
bool CObjectX::CollisionBossPrts()
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_BOSSPARTS - 1; nCount++)
	{
		//当たり判定
		if (m_pCollision->CircleCollisionAll(m_posPartsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetPosParts(nCount), m_ModelSizePartsBoss[nCount], CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount)) == true)
		{
			return true; //当たった
		}
	}

	return false;        //当たっていない
}

//=============================
//継承objの右側の当たり判定
bool CObjectX::CollisionRightSelectPlayer(CObjectX* pObject)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		//右側の当たり判定
		if (m_pCollision->ColiisionBoxRight(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount)) == true)
		{
			return true; //当たった
		}
	}

	return false;        //当たっていない
}

//=============================
//継承objの左側の当たり判定
bool CObjectX::CollisionLeftSelectPlayer(CObjectX* pObject)
{
	//プレイヤーの各パーツ毎の当たり判定処理
	for (int nCount = 0; nCount < MAX_PRTS - 1; nCount++)
	{
		//左側の当たり判定
		if (m_pCollision->ColiisionBoxLeft(pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetPosParts(nCount),
			pObject->m_ModelSize, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(nCount)) == true)
		{
			return true; //当たっている
		}
	}

	return false;        //当たっていない
}

//=============================
//プレイヤーと他の当たり判定
//=============================
bool CObjectX::CollisionPlayerSelect(CObjectX* pObject)
{
	//当たり判定
	if (m_pCollision->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->m_pos, CManager::GetScene()->GetPlayerX()->GetModelSizeParts(0), pObject->m_ModelSize) == true)
	{
		return true; //当たった
	}

	return false;    //当たっていない
}

//=============================
//プレイヤーと敵の当たり判定
//=============================
bool CObjectX::CollisionPlayerInEnemy(CObjectX* pObject, float fMagnification)
{
	//プレイヤーと敵の当たり判定
	if (m_pCollision->CircleCollisionAll(CManager::GetScene()->GetPlayerX()->GetPos(),
		pObject->GetPos(), CManager::GetScene()->GetPlayerX()->GetModelSizeParts(0) * fMagnification, pObject->GetModelSizePartsEnemy(0) * fMagnification) == true)
	{
		return true; //当たった
	}

	return false;    //当たっていない
}


//==============================
//Xファイルのサイズの取得
//==============================
void CObjectX::Size()
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

	for (int nCount = 0; nCount < nNumVertex; nCount++)
	{
		//位置を代入するための変数
		D3DXVECTOR3 mtx;

		mtx = *(D3DXVECTOR3*)pVtxByte; //頂点フォーマットをD3DXVECTOR3に変換


		//=================================
		//X軸用
		//================================= 

		//取得した数値が一番大きい時
		if (mtx.x > max.x)
		{
			max.x = mtx.x; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.x < min.x)
		{
			min.x = mtx.x; //代入
		}


		//=================================
		//Y軸用
		//=================================  

		//取得した数値が一番大きい時
		if (mtx.y > max.y)
		{
			max.y = mtx.y; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.y < min.y)
		{
			min.y = mtx.y; //代入
		}


		//=================================
		//Z軸用
		//================================= 

		//取得した数値が一番大きい時
		if (mtx.z > max.z)
		{
			max.z = mtx.z; //代入
		}

		//取得した値が一番小さい時
		else if (mtx.z < min.z)
		{
			min.z = mtx.z; //代入
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxByte += dSIze;
	}

	//Y軸の最小値が０以下の時
	if (min.y < 0)
	{
		//Y軸の最大値が最小値より小さい時
		if (max.y < min.y)
		{
			max.y = min.y * -1.0f; //反転させる
		}
		min.y = 0; //初期化
	}

	//オブジェクトのサイズを計算する
	m_ModelSize = max - min;
}


//==================================
//オブジェクトの配置
//==================================
void CObjectX::ObjectArrangement(CObjectX::TYPE type, CUI* pUI1)
{
	//Oキーが押された時に生成する処理を通す
	if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_O) == true)
	{
		//UIの情報がない時
		if (pUI == nullptr)
		{
			pUI = CCreateInObject::Create(CObject3D::TYPE::CLING); //生成
			pUI->SetSize(50.0f, 0.0f, 50.0f);                         //大きさの設定
		}

		//タイプが電柱の時
		if (type == CObjectX::TYPE::TELEPHONPOLE)
		{
			CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //電柱カウントを進める
			CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //全ての電柱カウントを進める

			//電柱の生成
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), m_pos);

			//監視カメラの生成
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 180.0f, m_pos.z - 50.0f));
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 170.0f, m_pos.z - 50.0f));

			//レーザーUIの生成と位置を同期させる
			pUI1 = CLaserCamare::Create(CObject3D::TYPE::LASER);

			//生成したオブジェクトの位置に同期
			pUI->GetPos() = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos();
		}

		//地面用ブロックの時
		else if (type == CObjectX::TYPE::FIELDBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(m_pos.x + 600.0f, m_pos.y, m_pos.z));
		}

		//上がる用ブロックの時
		else if (type == CObjectX::TYPE::GOUPBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}

		//道用ブロックの時
		else if (type == CObjectX::TYPE::ROADBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y, m_pos.z));
		}

		//壁兼道用ブロックの時
		else if (type == CObjectX::TYPE::WALLROADBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//壁兼道用001ブロックの時
		else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(m_pos.x + 500.0f, m_pos.y, m_pos.z));
		}

		//小さい用ブロックの時
		else if (type == CObjectX::TYPE::SMALLBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}

		//小さい用001ブロックの時
		else if (type == CObjectX::TYPE::SMALLBLOCK_001)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}

		//上に設置する用ブロックの時
		else if (type == CObjectX::TYPE::UPWALLBLOCK)
		{
			//生成する
			CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(m_pos.x + 200.0f, m_pos.y, m_pos.z));
		}
	}

	//タイプが電柱の時
	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		//電柱カウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() < CInstance::MAX_STAGEOBJECT && CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount() > -1 && CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()) != nullptr)
		{
			/*if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y += 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y -= 1.0f;
				pUI->GetPos().y = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x += 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x -= 1.0f;
				pUI->GetPos().x = CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x;
			}*/

			//Mキーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->TextFileWrite(CObjectX::TYPE::TELEPHONPOLE,
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x,
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y,
					CManager::GetInstance()->GetTelephonPole(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z);

				return; //処理を抜ける
			}
		}
	}

	//地面用ブロックの時
	else if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		//地面用ブロックのカウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetInstance()->GetFieldBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetFieldBlockCount() > -1 && CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左に移動
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().x,
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().y,
					CManager::GetInstance()->GetFiledBlock(CManager::GetInstance()->GetFieldBlockCount())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//上がる用ブロックの時
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		//上がる用ブロックのカウントが最大数より低くー１より高く、情報がある時
		if (CManager::GetInstance()->GetGoUpBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetGoUpBlockCount() > -1 && CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左キーが押された時
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().x,
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().y,
					CManager::GetInstance()->GetGoUpBlock(CManager::GetInstance()->GetGoUpBlockCount())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//道用ブロックの時
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		//道用ブロックのカウントが最大数より低く、ー１より高く、情報がある
		if (CManager::GetInstance()->GetRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetRoadBlockCount() > -1 && CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左に移動
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetRoadBlock(CManager::GetInstance()->GetRoadBlockCount())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//壁兼道用ブロックの時
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		//壁兼道用ブロックのカウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetInstance()->GetWallRoadBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlockCount() > -1 && CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock(CManager::GetInstance()->GetWallRoadBlockCount())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//壁兼道用ブロック001の時
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		//壁兼道用ブロック001のカウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetInstance()->GetWallRoadBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetWallRoadBlock001Count() > -1 && CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左に移動
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->TextFileWrite(
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().x,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().y,
					CManager::GetInstance()->GetWallRoadBlock001(CManager::GetInstance()->GetWallRoadBlock001Count())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//小さい用ブロックの時
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		//小さいブロックのカウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetInstance()->GetSmallBlockCount() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlockCount() > -1 && CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左に移動
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->TextFileWrite(
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().x,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().y,
					CManager::GetInstance()->GetSmallBlock(CManager::GetInstance()->GetSmallBlockCount())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}

	//小さい用ブロック001の時
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		//小さいブロック001のカウントが最大数より低く、ー１より高く、情報がある時
		if (CManager::GetInstance()->GetSmallBlock001Count() < CInstance::MAX_OBJECT_DATA && CManager::GetInstance()->GetSmallBlock001Count() > -1 && CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count()) != nullptr)
		{
			//上キーが押された時
			if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_UP) == true)
			{
				//上に移動
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y += OBJECT_SET_PLUS_Y;
			}

			//下キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_DOWN) == true)
			{
				//下に移動
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y -= OBJECT_SET_MINUS_Y;
			}

			//右キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RIGHT) == true)
			{
				//右に移動
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x += OBJECT_SET_PLUS_X;
			}

			//左キーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_LEFT) == true)
			{
				//左に移動
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x -= OBJECT_SET_MINUS_X;
			}

			//Mキーが押された時
			else if (CManager::GetKeyBorad()->GetKeyboardTrigger(DIK_M) == true)
			{
				//テキストファイルに書き込む処理
				CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->TextFileWrite(
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().x,
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().y,
					CManager::GetInstance()->GetSmallBlock001(CManager::GetInstance()->GetSmallBlock001Count())->GetPos().z, type);

				return; //処理を抜ける
			}
		}
	}
}


//==================================
//Xファイルの読み込み
//==================================
HRESULT CObjectX::Lood()
{
	int nNumTexture = 0;                                //テクスチャの配列を進める為の変数
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスの取得

	//ファイルがあるかどうか確かめる
	if (FAILED(D3DXLoadMeshFromX(m_aFileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_dwNumMat, &m_pMesh)))
	{
		return E_FAIL; //失敗を返す
	}

	//マテリアルデータへのポインタを収得
	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//マテリアル（テクスチャ）分回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_pMat[nCntMat].pTextureFilename != nullptr)
		{//テクスチャファイルが存在する

			D3DXCreateTextureFromFile(pDevice, m_pMat[nCntMat].pTextureFilename, &m_pTexture[nNumTexture]);
			nNumTexture++; //配列を進める
		}
	}

	return S_OK; //成功を返す
}