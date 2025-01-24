//===========================================================================================================
//
//キャラクターの各パーツの処理[character.cpp]
//Auther: Haruki Chiba
//
//===========================================================================================================


//=============================
//インクルード
#include "character.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
//=====================~
CCharacter::CCharacter(int nPriority) : CObjectX(nPriority)
{
	//プレイヤーのパーツ数分回す
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		m_pModelPrts[nCount] = nullptr;                         //プレイヤーのパーツの初期化
		SaveMotionPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //各パーツの場所の保管場所の初期化
		m_pSaveModelPrtInfo[nCount] = {};                       //モデルパーツの保管情報の初期化
	}

	//ボスのパーツ数分回す
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		m_pModelPrtsBoss[nCount1] = nullptr;                         //ボスのパーツの初期化
		SaveMotionPosBoss[nCount1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 //各パーツの場所の保管場所の初期化
		m_pSaveModelPrtInfoBoss[nCount1] = {};						 //モデルパーツの保管情報の初期化
	}

	m_nMotionFrameBoss = 0;              //ボスのモーション時のフレームを初期化
	MotionCount = 0;                     //プレイヤーのモーションカウントの初期化
	MotionCountBoss = 0;                 //ボスのモーションカウントの初期化
	m_bMotionType = false;               //プレイヤーのモーション判定の初期化
	m_bMotionBossType = false;           //ボスのモーション判定の初期化
	m_MotionState = NEUTRAL;             //プレイヤーのモーションの状態の初期化
	m_MotionStateBoss = BOSSNEUTRAL;     //ボスのモーション状態の初期化
}


//======================
//デストラクタ
//======================
CCharacter::~CCharacter()
{

}


//=======================
//初期化処理
//=======================
HRESULT CCharacter::Init()
{
	//初期化に成功するかどうか
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功返す
}


//========================
//破棄処理
//========================
void CCharacter::Uninit()
{
	CObjectX::Uninit(); //破棄処理を呼ぶ

	//プレイヤーのパーツ分回す
	for (int nCount = 0; nCount < MAX_PRTS; nCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Uninit();  //破棄処理を呼ぶ
			delete m_pModelPrts[nCount];     //情報を削除する
			m_pModelPrts[nCount] = nullptr;  //情報を無くす
		}
	}

	//ボスのパーツ分回す
	for (int nCount1 = 0; nCount1 < MAX_BOSSPARTS; nCount1++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsBoss[nCount1] != nullptr)
		{
			m_pModelPrtsBoss[nCount1]->Uninit();  //破棄処理
			delete m_pModelPrtsBoss[nCount1];     //情報を削除する
			m_pModelPrtsBoss[nCount1] = nullptr;  //情報を無くす
		}
	}
}

//========================
//プレイヤー更新処理
//========================
void CCharacter::UpdatePlayer()
{
	MotionInfo(); //モーションを行う処理を呼ぶ

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount = 0; nCount < MAX_PRTS-1; nCount++)
	{
		GetPosPrts(nCount) = D3DXVECTOR3(SaveMotionPos[nCount].x +CManager::GetScene()->GetPlayerX()->GetPos().x, SaveMotionPos[nCount].y + CManager::GetScene()->GetPlayerX()->GetPos().y, SaveMotionPos[nCount].z + CManager::GetScene()->GetPlayerX()->GetPos().z);            //各パーツを保管値＋現在の値で修正
	}
	
	//武器の更新
	for (int nCount1 = 1; nCount1 < 4; nCount1++)
	{
		GetPosPrts(17) = D3DXVECTOR3(SaveMotionPos[nCount1 + 2].x + GetPos().x, SaveMotionPos[nCount1 + 2].y + GetPos().y, SaveMotionPos[nCount1 + 2].z + GetPos().z); //各パーツを保管値＋現在の値で修正
	}
}


//============================
//ボスの更新処理
//============================
void CCharacter::UpdateBoss()
{
	MotionInfoBoss(); //モーションを行う処理を呼ぶ

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount = 0; nCount < MAX_BOSSPARTS; nCount++)
	{
		if (nCount <= 9)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y, SaveMotionPosBoss[nCount].z + GetPos().z);           //各パーツを保管値＋現在の値で修正
		}
		if (nCount >= 10)
		{
			GetPosPrtsBoss(nCount) = D3DXVECTOR3(SaveMotionPosBoss[nCount].x + GetPos().x, SaveMotionPosBoss[nCount].y + GetPos().y + 200.0f, SaveMotionPosBoss[nCount].z + GetPos().z);  //各パーツを保管値＋現在の値で修正
		}
	}

	//武器の更新
	for (int nCount1 = 0; nCount1 < 4; nCount1++)
	{
		GetPosPrtsBoss(17) = D3DXVECTOR3(SaveMotionPosBoss[nCount1 + 2].x + GetPos().x, SaveMotionPosBoss[nCount1 + 2].y + GetPos().y, SaveMotionPosBoss[nCount1 + 2].z + GetPos().z);     //武器パーツを保管値＋現在の値で修正
	}
}

//========================
//プレイヤーの描画処理
//========================
void CCharacter::DrawPlayer(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;      //計算用マトリックス
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld(); //マトリックスを取得する
	D3DXVECTOR3 pos, rot;                      //位置と向きを取得する為の変数

	pos = GetPos(); //位置を取得する
	rot = GetRot(); //向きを取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pMtx);

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//パーツ数分回す
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrts[nCount] != nullptr)
		{
			m_pModelPrts[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//========================
//ボスの描画処理
//========================
void CCharacter::DrawBoss(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //計算用マトリックス
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();  //マトリックスを取得する
	D3DXVECTOR3 pos, rot;                       //位置と向きを取得する為の変数

	pos = GetPos(); //位置を取得する
	rot = GetRot(); //向きを取得する

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pMtx);

	//-----向きを反映-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----位置を反映-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//マトリックスに代入
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//パーツ数分回す
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsBoss[nCount] != nullptr)
		{
			m_pModelPrtsBoss[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}


//======================
//ロード処理
//======================
void CCharacter::Lood()
{
	int nCount = 0;              //最初のパーツ数をカウントするための変数
	int nKeyCount = 0;           //モーションのキーをカウントするための変数
	int nModelPrtsCount = 0;     //生成するパーツ数のカウントするための変数
	char aPrtsPass[100];         //各パーツを読み取る際のパスを読み込むための変数
	char m_aDataSearch[2024];    //必要な情報を読み取る際の文字列を読みむための変数

	int nMotionCount = 0;        //モーションの数をカウントするための変数
	int nKeySetCount = 0;        //モーションのキーセットの数をカウントするための変数

	FILE* m_pFile=nullptr;       //ファイルポインター

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normal.txt", "r"); //ファイルを開く

	//開けなかった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}


	//ループ
	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

		//この文字を読み取った時
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//ループ
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

				//ｘファイル読み込み
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //パーツ数取得

					//モデルパーツカウントが最大数より小さい時
					if (nModelPrtsCount < MAX_PRTS)
					{
						if (m_pModelPrts[nModelPrtsCount] == nullptr)
						{
							m_pModelPrts[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //パーツの生成
							m_pModelPrts[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrts(nModelPrtsCount));                                                             //情報を同期させる
						}
						nModelPrtsCount++; //配列を進める
					}
				}

				//終了条件
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //処理を抜ける
				}

				//キャラクタパーツの情報を読み取る
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//ループ
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

						//終了条件
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //処理を抜ける
						}

						//処理を続行させる条件
						if (m_aDataSearch[0] == '#')
						{
							continue; //続行
						}

						//パーツの情報の読み込み
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//ループ
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

								//終了条件
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //処理を抜ける
								}

								//インデックスを読み取る条件
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexPrts()); //パーツのインデックスを読み取る
								}

								//親パーツかどうかを読み取る条件
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrts[nCount]->GetIndexModelPrts()); //親パーツかを読み取る

									//読み込んだ値がー１の時
									if (m_pModelPrts[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrts[nCount]->SetParent(nullptr); //情報無し
									}

									//その他
									else
									{
										m_pModelPrts[nCount]->SetParent(m_pModelPrts[m_pModelPrts[nCount]->GetIndexModelPrts()]); //親である情報を入れる
									}
								}

								//位置の読み込み条件
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetPos().x, &m_pModelPrts[nCount]->GetPos().y, &m_pModelPrts[nCount]->GetPos().z); //位置の同期
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrts[nCount]->GetPos();                     //位置を保管する
									//m_pSaveModelPrtInfo[nCount].pos += MotionSetPlayer[0].KeySet[0].aKey[nCount].pos;  
								}

								//向きの読み込み条件
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrts[nCount]->GetRot().x, &m_pModelPrts[nCount]->GetRot().y, &m_pModelPrts[nCount]->GetRot().z); //位置の同期
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrts[nCount]->GetRot();                     //向きを保管する
									//m_pSaveModelPrtInfo[nCount].rot += MotionSetPlayer[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //読み取るパーツの番号を増やす
						}

					}
				}

				//モーションの情報を読み込む処理
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0; //ループするかどうかの判定用変数

					//ループ
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

						//処理を続行する条件
						if (m_aDataSearch[0] == '#')
						{
							continue;                           //続行
							fgets(m_aDataSearch, 40, m_pFile);  //ファイルから文字列を読み込む
						}

						//終了条件
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //処理を抜ける
						}

						//ループかどうか判定する条件
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //検索
							(void)fscanf(m_pFile, "%d", &LoopType);     //ループするかどうか検索

							//読み込んだ値が０の時
							if (LoopType == 0)
							{
								MotionSetPlayer[nMotionCount].Loop = false; //ループしない
							}

							//その他
							else
							{
								MotionSetPlayer[nMotionCount].Loop = true;  //ループする
							}
						} 

						//キーの読み込み条件
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                         //検索
							(void)fscanf(m_pFile, "%d", &MotionSetPlayer[nMotionCount].NumKey);  //キーの数を検索
						}

						//パーツごとの位置関係を読み取る
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//ループ
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

								//コメントを読み込んだ時
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile); //ファイルから文字列を読み込む
									continue;                          //処理を続ける
								}

								//モーションの読み込み終了
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //処理を抜ける
								}

								//フレームを読み取る条件
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].Frame); //フレーム数を検索
								}
									
								//キーの中身の情報を読み取る条件
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//ループ
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

										//コメントを読み込んだ時
										if (m_aDataSearch[0] == '#')
										{
											continue;                           //処理を続ける
											fgets(m_aDataSearch, 40, m_pFile);  //ファイルから文字列を読み込む
										}

										//位置の情報を読み取る条件
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
											//GetPos() = MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nCount].pos;
										}

										//向きの情報を読み取る条件
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												                                       &MotionSetPlayer[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
										}

										//終了条件
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //処理を抜ける
										}
									}
									nKeyCount++; //キーカウントの加算
								}
							}
							nKeyCount = 0;   //キーカウントを初期化
							nKeySetCount++;  //データの加算
						}
					}
					nKeySetCount = 0; //カウントの初期化
					nMotionCount++;   //データの加算
				}
			}
			fclose(m_pFile); //ファイルを閉じる
			break;           //処理を抜ける
		}
	}

	//=================================================================================================================================================================
	//各パーツの位置の取得
	//=================================================================================================================================================================

	//上半身の位置を取得する
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//現在のパーツの次のパーツ分回す
		for (int Next = 0; Next < nCount + 1; Next++)
		{
			SaveMotionPos[nCount + 2] += m_pModelPrts[Next + 2]->GetPos();  //左側のパーツ数
			SaveMotionPos[nCount + 6] += m_pModelPrts[Next + 6]->GetPos();  //右側のパーツ数
		}

		SaveMotionPos[nCount + 6] += m_pModelPrts[0]->GetPos(); //位置を加算
		SaveMotionPos[nCount + 2] += m_pModelPrts[0]->GetPos(); //位置を加算
	}

	//下半身のpartsの位置を取得
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPos[nCount1 + 11] += m_pModelPrts[nCount1 + 11]->GetPos(); //下半身の各パーツ
		SaveMotionPos[nCount1 + 11] -= m_pModelPrts[10]->GetPos();           //腰の分引く
	}

	//頭と体の位置を取得する
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPos[nCount2] += m_pModelPrts[nCount2]->GetPos(); //位置を加算
		GetPosPrts(nCount2) = D3DXVECTOR3(SaveMotionPos[nCount2].x + GetPos().x, SaveMotionPos[nCount2].y + GetPos().y + 20.0f, SaveMotionPos[nCount2].z + GetPos().z); //パーツの位置を修正
	}

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount3 = 0; nCount3 < NUM_RIGHTLEFTPRTS*2; nCount3++)
	{
		GetPosPrts(nCount3 + 2) = D3DXVECTOR3(SaveMotionPos[nCount3 + 2].x + GetPos().x, SaveMotionPos[nCount3 + 2].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 2].z + GetPos().z);      //パーツの位置を修正
		GetPosPrts(nCount3 + 10) = D3DXVECTOR3(SaveMotionPos[nCount3 + 10].x + GetPos().x, SaveMotionPos[nCount3 + 10].y + GetPos().y+20.0f , SaveMotionPos[nCount3 + 10].z + GetPos().z);  //パーツの位置を修正
	}
}

//======================
//ボスのロード処理
//======================
void CCharacter::LoodBoss()
{
	int nCount = 0;              //最初のパーツ数をカウントするための変数
	int nKeyCount = 0;           //モーションのキーをカウントするための変数
	int nModelPrtsCount = 0;     //生成するパーツ数のカウントするための変数
	char aPrtsPass[100];         //各パーツを読み取る際のパスを読み込むための変数
	char m_aDataSearch[2024];    //必要な情報を読み取る際の文字列を読みむための変数

	int nMotionCount = 0;        //モーションの数をカウントするための変数
	int nKeySetCount = 0;        //モーションのキーセットの数をカウントするための変数

	FILE* m_pFile = nullptr;     //ファイルポインター

	m_pFile = fopen("data\\motion\\normal_motion\\motion_normalBoss.txt", "r"); //ファイルを開く

	//開けなかった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}

	//ループ
	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

		//この文字が読み込まれた時
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//ループ
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

				//ｘファイル読み込み
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //パーツ数取得

					//モデルパーツカウントが最大数より小さいとき
					if (nModelPrtsCount < MAX_BOSSPARTS)
					{
						m_pModelPrtsBoss[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //パーツの生成
						m_pModelPrtsBoss[nModelPrtsCount]->BindSize(GetMaxPrts(nModelPrtsCount), GetMinPrts(nModelPrtsCount), GetModelSizePrtsBoss(nModelPrtsCount));														  //情報を同期させる
						nModelPrtsCount++; //配列を進める
					}
				}

				//終了条件
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //処理を抜ける
				}

				//キャラクタパーツの情報を読み取る
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//ループ
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

						//終了条件
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //処理を抜ける
						}

						//コメントを読み込んだ時
						if (m_aDataSearch[0] == '#')
						{
							continue; //続行
						}
						
						//パーツの情報の読み込み
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//ループ
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

								//終了条件
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //処理を抜ける
								}

								//インデックスを読み取る条件
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexPrts()); //パーツのインデックスを読み取る
								}

								//親パーツかどうかを読み取る条件
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetIndexModelPrts()); //親パーツかを読み取る

									//読み込んだ値がー１の時
									if (m_pModelPrtsBoss[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrtsBoss[nCount]->SetParent(nullptr); //情報無し
									}

									//その他
									else
									{
										m_pModelPrtsBoss[nCount]->SetParent(m_pModelPrtsBoss[m_pModelPrtsBoss[nCount]->GetIndexModelPrts()]); //親である情報を入れる
									}
								}

								//位置の読み取る条件
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetPos().x, &m_pModelPrtsBoss[nCount]->GetPos().y, &m_pModelPrtsBoss[nCount]->GetPos().z); //位置の同期
									m_pSaveModelPrtInfoBoss[nCount].pos = m_pModelPrtsBoss[nCount]->GetPos();                //位置を保管する
									//m_pSaveModelPrtInfoBoss[nCount].pos += MotionSetBoss[0].KeySet[0].aKey[nCount].pos;
								}

								//向きの情報を読み取る条件
								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsBoss[nCount]->GetRot().x, &m_pModelPrtsBoss[nCount]->GetRot().y, &m_pModelPrtsBoss[nCount]->GetRot().z); //位置の同期
									m_pSaveModelPrtInfoBoss[nCount].rot = m_pModelPrtsBoss[nCount]->GetRot();                //位置を保管する
									//m_pSaveModelPrtInfoBoss[nCount].rot += MotionSetBoss[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //読み取るパーツの番号を増やす
						}

					}
				}

				//モーションの情報を読み込む処理
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0; //ループするかどうかの判定用変数

					//ループ
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

						//コメントを読み込んだ時
						if (m_aDataSearch[0] == '#')
						{
							continue;                          //続行
							fgets(m_aDataSearch, 40, m_pFile); //ファイルから文字を読み込む
						}

						//終了条件
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //処理を抜ける
						}

						//ループするかどうか読み取る条件
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //検索
							(void)fscanf(m_pFile, "%d", &LoopType);     //ループするかどうか検索

							//読み込んだ値が０の時
							if (LoopType == 0)
							{
								MotionSetBoss[nMotionCount].Loop = false; //ループしない
							}

							//その他
							else
							{
								MotionSetBoss[nMotionCount].Loop = true;  //ループする
							}
						}

						//キーの読み取る条件
						else if (!strcmp(m_aDataSearch, "NUM_KEY"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                       //検索
							(void)fscanf(m_pFile, "%d", &MotionSetBoss[nMotionCount].NumKey);  //キーの数を検索
						}

						//パーツごとの位置関係を読み取る
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{
							//ループ
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

								//コメントを読み込んだ時
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile); //ファイルから文字を読み取る
									continue;                          //処理を続ける
								}

								//モーションの読み込み終了
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //処理を抜ける
								}

								//フレームを読み込む条件
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].Frame); //フレーム数を検索
								}

								//キーの中身の情報を読み取る条件
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//ループ
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

										//コメントを読み込んだ時
										if (m_aDataSearch[0] == '#')
										{
											continue;                          //処理を続ける
											fgets(m_aDataSearch, 40, m_pFile); //ファイルから文字を読み取る
										}

										//位置を読み取る条件
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
										}

										//向きを読み取る条件
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetBoss[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
										}

										//終了条件
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //処理を抜ける
										}
									}
									nKeyCount++; //キーカウントの加算
								}
							}
							nKeyCount = 0;  //キーカウントの初期化
							nKeySetCount++; //データの加算
						}
					}
					nKeySetCount = 0; //カウントの初期化
					nMotionCount++;   //データの加算
				}
			}
			fclose(m_pFile); //ファイルを閉じる
			break;           //処理を抜ける
		}
	}

	//=================================================================================================================================================================
	//各パーツの位置の取得
	//=================================================================================================================================================================
	
	//上半身の位置を取得する
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//現在のパーツの次のパーツ分回す
		for (int nNext = 0; nNext < nCount + 1; nNext++)
		{
			//各パーツの位置を足し合わせる
			SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[nNext + 2]->GetPos();  //左側のパーツ数
			SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[nNext + 6]->GetPos();  //右側のパーツ数
		}

		//体の位置を足し合わせる
		SaveMotionPosBoss[nCount + 2] += m_pModelPrtsBoss[0]->GetPos(); //位置を加算
		SaveMotionPosBoss[nCount + 6] += m_pModelPrtsBoss[0]->GetPos(); //位置を加算
	}

	//下半身のpartsの位置を取得
	for (int nCount1 = 0; nCount1 < 6; nCount1++)
	{
		SaveMotionPosBoss[nCount1 + 11] += m_pModelPrtsBoss[nCount1 + 11]->GetPos(); //下半身の各パーツ
		SaveMotionPosBoss[nCount1 + 11] -= m_pModelPrtsBoss[10]->GetPos();           //腰の分引く
	}

	//頭と体の位置を取得
	for (int nCount2 = 0; nCount2 < 2; nCount2++)
	{
		SaveMotionPosBoss[nCount2] += m_pModelPrtsBoss[nCount2]->GetPos();                                                                  //位置を加算
		GetPosPrtsBoss(nCount2) = D3DXVECTOR3(SaveMotionPosBoss[nCount2].x, SaveMotionPosBoss[nCount2].y, SaveMotionPosBoss[nCount2].z); //位置を修正
	}

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount3 = 0; nCount3 < NUM_RIGHTPRTSBOSS; nCount3++)
	{
		GetPosPrtsBoss(nCount3 + 2) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 2].x + GetPos().x, SaveMotionPosBoss[nCount3 + 2].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 2].z + GetPos().z);      //位置を修正
		GetPosPrtsBoss(nCount3 + 10) = D3DXVECTOR3(SaveMotionPosBoss[nCount3 + 10].x + GetPos().x, SaveMotionPosBoss[nCount3 + 10].y + GetPos().y + 20.0f, SaveMotionPosBoss[nCount3 + 10].z + GetPos().z);  //位置を修正
	}
}


//===============================
//プレイヤーモーションを行う
//===============================
void CCharacter::MotionInfo()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrts[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCount != MotionSetPlayer[m_MotionState].NumKey - 1)
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].pos; //現在のモーションの次のモーションから現在のモーションの位置を引く
				Moverot = MotionSetPlayer[m_MotionState].KeySet[MotionCount + 1].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionCount].aKey[nModelCount].rot; //現在のモーションの次のモーションから現在のモーションの向きを引く
			}
			else
			{
				Movepos = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].pos - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].pos; //最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetPlayer[m_MotionState].KeySet[0].aKey[nModelCount].rot - MotionSetPlayer[m_MotionState].KeySet[MotionSetPlayer[m_MotionState].NumKey - 1].aKey[nModelCount].rot; //最初のモーションのキーから現在のモーションの総数ー１を引く
			}

			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //位置を代入した位置からフレームを割る
			rot = Moverot / (float)MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame; //向きを代入した向きからフレームを割る

			//差分の分だけ加算
			m_pModelPrts[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrts[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}
	
	GetFrame()++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (GetFrame() == MotionSetPlayer[m_MotionState].KeySet[MotionCount].Frame)
	{
		SetFrame(0);   //フレームを初期化
		MotionCount++; //モーションのカウントを増加

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCount == MotionSetPlayer[m_MotionState].NumKey)
		{
			MotionCount = 0; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCount + 1 == MotionSetPlayer[m_MotionState].NumKey && MotionSetPlayer[m_MotionState].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionType = false; //モーションの判定をoffにする
			//SetMotion(NEUTRAL);    //モーションの情報の切り替え
		}
	}
}

//===============================
//ボスのモーションを行う
//===============================
void CCharacter::MotionInfoBoss()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsBoss[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCountBoss != MotionSetBoss[m_MotionStateBoss].NumKey - 1)
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].pos; //現在のモーションの次のモーションから現在のモーションの位置を引く
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss + 1].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].aKey[nModelCount].rot; //現在のモーションの次のモーションから現在のモーションの向きを引く
			}
			else
			{
				Movepos = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].pos - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].pos; //最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetBoss[m_MotionStateBoss].KeySet[0].aKey[nModelCount].rot - MotionSetBoss[m_MotionStateBoss].KeySet[MotionSetBoss[m_MotionStateBoss].NumKey - 1].aKey[nModelCount].rot; //最初のモーションのキーから現在のモーションの総数ー１を引く
			}

			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //現在の位置を計算でだした位置と加算させる
			rot = Moverot / (float)MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame; //向きの位置を計算でだした向きと加算させる

			//モーションが歩きでループがオフの時
			if (MotionSetBoss[BOSSWALK].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とモーションカウントが１の時（キーセットが最後の時）
				if (m_MotionStateBoss == BOSSWALK && MotionCountBoss == 1)
				{
					MotionSetBoss[BOSSWALK].KeySet[MotionCountBoss].Frame = 0; //モーションフレームを初期化
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       //位置を初期化
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                       //向きを初期化
				}
			}

			//モーションが死亡でループがオフの時
			if (MotionSetBoss[BOSSDIE].Loop == false)
			{
				//モーションの状態が死亡で設定されている時とモーションカウントが３の時（キーセットが最後の時）
				if (m_MotionStateBoss == BOSSDIE && MotionCountBoss == 3)
				{
					MotionSetBoss[BOSSDIE].KeySet[MotionCountBoss].Frame = 0; //モーションフレームを初期化
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                      //位置を初期化
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                      //向きを初期化
				}
			}

			//差分の分だけ加算
			m_pModelPrtsBoss[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrtsBoss[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}

	m_nMotionFrameBoss++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (m_nMotionFrameBoss == MotionSetBoss[m_MotionStateBoss].KeySet[MotionCountBoss].Frame)
	{
		m_nMotionFrameBoss = 0; //カウントを初期化
		MotionCountBoss++;      //モーションのカウントを増加

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountBoss == MotionSetBoss[m_MotionStateBoss].NumKey)
		{
			MotionCountBoss = 0; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountBoss + 1 == MotionSetBoss[m_MotionStateBoss].NumKey && MotionSetBoss[m_MotionStateBoss].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionBossType = false; //モーションの判定をoffにする
			//SetMotionBoss(BOS);      //モーションの情報の切り替え
		}
	}
}


//================================
//プレイヤーのモーションの設定
//================================
void CCharacter::SetMotion(MOTIONSTATE motiontype)
{
	//現在のモーションと違ったら
	if (m_MotionState != motiontype && m_bMotionType == false)
	{
		m_MotionState = motiontype; //モーションを設定
		MotionCount = 0;            //モーションのカウントを初期化
		SetFrame(0);                //フレームを初期化

		//モデルのパーツ分繰り返す
		for (int nModelCount = 0; nModelCount < MAX_PRTS; nModelCount++)
		{
			//モデルパーツの情報がある時
			if (m_pModelPrts[nModelCount] != nullptr)
			{
				m_pModelPrts[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                            //現在の位置を読み取った値にする
				m_pModelPrts[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);                            //現在の向きを読み取った値にする
				m_pModelPrts[nModelCount]->GetPos() += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].pos; //現在の位置を設定したモーションの位置と加算
				m_pModelPrts[nModelCount]->GetRot() += MotionSetPlayer[motiontype].KeySet[0].aKey[nModelCount].rot; //現在の向きを設定したモーションの向きと加算
			}
		}
	}
}


//================================
//ボスのモーションの設定
//================================
void CCharacter::SetMotionBoss(BOSSMOTIONSTATE motiontype)
{
	//現在のモーションと違ったら
	if (m_MotionStateBoss != motiontype && m_bMotionBossType == false)
	{
		m_MotionStateBoss = motiontype; //モーションを設定
		MotionCountBoss = 0;            //モーションのカウントを初期化
		m_nMotionFrameBoss = 0;         //フレームのカウントの初期化
		
		//モデルのパーツ分繰り返す
		for (int nModelCount = 0; nModelCount < MAX_BOSSPARTS; nModelCount++)
		{
			//モデルパーツの情報がある時
			if (m_pModelPrtsBoss[nModelCount] != nullptr)
			{
				m_pModelPrtsBoss[nModelCount]->SetPos(m_pSaveModelPrtInfoBoss[nModelCount].pos);                        //現在の位置を読み取った値にする
				m_pModelPrtsBoss[nModelCount]->SetRot(m_pSaveModelPrtInfoBoss[nModelCount].rot);					    //現在の向きを読み取った値にする
				m_pModelPrtsBoss[nModelCount]->GetPos() += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].pos;	//現在の位置を設定したモーションの位置と加算
				m_pModelPrtsBoss[nModelCount]->GetRot() += MotionSetBoss[motiontype].KeySet[0].aKey[nModelCount].rot;	//現在の向きを設定したモーションの向きと加算
			}
		}
	}
}
