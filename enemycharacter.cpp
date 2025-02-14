//==================================================
//
//キャラクターの各パーツの処理[enemycharacter.cpp]
//Auther: Haruki Chiba
//
//==================================================


//=============================
//インクルード
#include "enemycharacter.h"
#include "rendererh.h"
#include "manager.h"


//======================
//コンストラクタ
//======================
CEnemyCharacter::CEnemyCharacter(int nPriority) : CObjectX(nPriority)
{
	//敵のパーツ数分回す
	for (int nCount = N_INIT_NUMBER; nCount < MAX_ENEMYPARTS; nCount++)
	{
		m_pLoodModelPrtsEnemy[nCount] = nullptr;               //読み込み用の敵のパーツの初期化
		m_pModelPrtsEnemy001[nCount] = nullptr;                //敵001のパーツの初期化
		m_pModelPrtsEnemy002[nCount] = nullptr;                //敵002のパーツの初期化
		m_pSaveModelPrtInfo[nCount] = {};					   //モデルパーツの保管情報の初期化
		m_pSaveModelPrtUpdateInfo001[nCount] = {};			   //更新用モデルパーツの保管情報の初期化
		m_pSaveModelPrtUpdateInfo002[nCount] = {};			   //更新用モデルパーツの保管情報の初期化
	}

	MotionCountEnemy001 = N_INIT_NUMBER;                       //敵001モーション時のカウントを初期化
	MotionCountEnemy002 = N_INIT_NUMBER;                       //敵002モーション時のカウントを初期化
	m_nNumParts = N_INIT_NUMBER;                               //パーツ数の初期化
	m_nEnemy001Parts = N_INIT_NUMBER;                          //敵001のパーツ数の初期化
	m_nEnemy002Parts = N_INIT_NUMBER;                          //敵002のパーツ数の初期化
	m_nEnemy001Frame = N_INIT_NUMBER;                          //敵001のモーション時のフレーム
	m_nEnemy002Frame = N_INIT_NUMBER;                          //敵002のモーション時のフレーム
	m_bMotionEnemyType = false;                                //モーションタイプの初期化
	m_MotionStateEnemy001 = ENEMYWALK;                         //モーション状態の初期化
	m_MotionStateEnemy002 = ENEMYWALK;                         //モーション状態の初期化
}


//======================
//デストラクタ
//======================
CEnemyCharacter::~CEnemyCharacter()
{

}


//=======================
//初期化処理
//=======================
HRESULT CEnemyCharacter::Init()
{
	//初期化が失敗した時
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//========================
//破棄処理
//========================
void CEnemyCharacter::Uninit()
{
	CObjectX::Uninit(); //破棄処理を呼ぶ
	
	//最大パーツ数分回す
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		//=====================================================================================
		//元がm_pLoodModelPrtsEnemyで読み取り、コピーしただけなのでUninit()&deleteはこれだけ呼ぶ

		//パーツの情報がある時
		if (m_pLoodModelPrtsEnemy[nCount1] != nullptr)
		{
			m_pLoodModelPrtsEnemy[nCount1]->Uninit(); //破棄処理
			delete m_pLoodModelPrtsEnemy[nCount1];    //情報を消す
			m_pLoodModelPrtsEnemy[nCount1] = nullptr; //情報を無くす
		}

		//パーツの情報がある時
		if (m_pModelPrtsEnemy001[nCount1] != nullptr)
		{
			//delete m_pModelPrtsEnemy001[nCount1];    //情報を消す
			m_pModelPrtsEnemy001[nCount1] = nullptr; //情報を無くす
		}

		//パーツの情報がある時
		if (m_pModelPrtsEnemy002[nCount1] != nullptr)
		{
			//delete m_pModelPrtsEnemy002[nCount1];    //情報を消す
			m_pModelPrtsEnemy002[nCount1] = nullptr; //情報を無くす
		}
	}
}

//========================
//敵001の更新処理
//========================
void CEnemyCharacter::UpdateEnemy001()
{
	MotionInfoEnemy001(); //モーションを行う処理を呼ぶ

	//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
	for (int nCount = N_INIT_NUMBER; nCount < m_nEnemy001Parts; nCount++)
	{
		//パーツの位置の更新
		GetPosPartsEnemy(nCount) = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount].pos.x + GetPos().x,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.y + GetPos().y,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.z + GetPos().z); //各パーツを保管値＋現在の位置で修正
	}
}

//========================
//敵002の更新処理
//========================
void CEnemyCharacter::UpdateEnemy002()
{
	MotionInfoEnemy002(); //モーションを行う処理を呼ぶ

	
}

//========================
//敵の描画処理
//========================
void CEnemyCharacter::DrawEnemy001(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;              //計算用マトリックス
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();          //マトリックスを取得する
	D3DXVECTOR3 pos, rot;                               //位置と向きを取得する為の変数

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
	for (int nCount = N_INIT_NUMBER; nCount < NumPrts; nCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy001[nCount] != nullptr)
		{
			m_pModelPrtsEnemy001[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//========================
//敵の描画処理
//========================
void CEnemyCharacter::DrawEnemy002(int NumPrts)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //レンダラーの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスのポインタ	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;              //計算用マトリックス
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();          //マトリックスを取得する
	D3DXVECTOR3 pos, rot;                               //位置と向きを取得する為の変数

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
	for (int nCount = N_INIT_NUMBER; nCount < NumPrts; nCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy002[nCount] != nullptr)
		{
			m_pModelPrtsEnemy002[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//======================
//敵のロード処理
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int nCount = N_INIT_NUMBER;                      //最初のパーツ数をカウントするための変数
	int nKeyCount = N_INIT_NUMBER;                   //モーションのキーをカウントするための変数
	int nModelPrtsCount = N_INIT_NUMBER;             //生成するパーツ数のカウントするための変数
	int nMotionCount = N_INIT_NUMBER;                //モーションの数をカウントするための変数
	int nKeySetCount = N_INIT_NUMBER;                //モーションのキーセットの数をカウントするための変数

	char aPrtsPass[MAX_PARTS_SEARCH];                //各パーツを読み取る際のパスを読み込むための変数
	char m_aDataSearch[MAX_DATA_SEARCH];             //必要な情報を読み取る際の文字列を読みむための変数
								      	             
								                     
	FILE* m_pFile = nullptr;                         //ファイルポインター

	//敵０番目を選択
	if (aSelect == "Enemy000")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy000.txt", "r"); //ファイルを開く
	}

	//敵１番目を選択
	else if (aSelect == "Enemy001")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy001.txt", "r"); //ファイルを開く
	}

	else if (aSelect == "Enemy002")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy002.txt", "r"); //ファイルを開く
	}

	//開けなかった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}

	int nLoopNumber = CObjectX::WHILE_NUMBER;  //ループの初期値

	//ループ
	while (nLoopNumber)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

		//この文字を読み取った時
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//ループ
			while (nLoopNumber)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

				//ｘファイル読み込み
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //パーツ数取得

					//モデルパーツカウントが最大数より小さい時
					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						//パーツの生成
						m_pLoodModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(
							D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER),
							D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER), 
							&aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat()); 

						//情報を同期させる
						m_pLoodModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizePartsEnemy(nModelPrtsCount));	
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
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

						//終了条件
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //処理を抜ける
						}

						//コメントを読み込んだ時
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue; //続行
						}

						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch); //検索
							(void)fscanf(m_pFile,"%d",&m_nNumParts);     //パーツ数の初期化
						}

						//パーツの情報の読み込み
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//ループ
							while (nLoopNumber)
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
									//パーツのインデックスを読み取る
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetIndexPrts());
								}

								//親パーツかどうかを読み取る条件
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									//親パーツかを読み取る
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts());

									//読み込んだ値がー１の時
									if (m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts() == PARENT_NUMBER)
									{
										m_pLoodModelPrtsEnemy[nCount]->SetParent(nullptr); //情報なし
									}

									//その他
									else
									{
										//親である情報を入れる
										m_pLoodModelPrtsEnemy[nCount]->SetParent(m_pLoodModelPrtsEnemy[m_pLoodModelPrtsEnemy[nCount]->GetIndexModelPrts()]);
									}
								}

								//位置を読み取る条件
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									//位置の同期
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetPos().x, &m_pLoodModelPrtsEnemy[nCount]->GetPos().y, &m_pLoodModelPrtsEnemy[nCount]->GetPos().z);
									m_pSaveModelPrtInfo[nCount].pos = m_pLoodModelPrtsEnemy[nCount]->GetPos();                //位置を保管する
									//m_pSaveModelPrtInfo[nCount].pos += LoodMotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									//向きの同期
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pLoodModelPrtsEnemy[nCount]->GetRot().x, &m_pLoodModelPrtsEnemy[nCount]->GetRot().y, &m_pLoodModelPrtsEnemy[nCount]->GetRot().z);
									m_pSaveModelPrtInfo[nCount].rot = m_pLoodModelPrtsEnemy[nCount]->GetRot();                //向きを保管する
									//m_pSaveModelPrtInfo[nCount].rot += LoodMotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //読み取るパーツの番号を増やす
						}
					}
				}

				//モーションの情報を読み込む処理
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = N_INIT_NUMBER; //ループするかどうかの判定用変数

					//ループ
					while (nLoopNumber)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // 検索

						//コメントを読み込んだ時
						if (m_aDataSearch[N_INIT_NUMBER] == '#')
						{
							continue;                                     //続行
							fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile); //ファイルから文字列を読み込む
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
							if (LoopType == N_INIT_NUMBER)
							{
								LoodMotionSetEnemy[nMotionCount].Loop = false; //ループしない
							}

							//その他
							else
							{
								LoodMotionSetEnemy[nMotionCount].Loop = true;  //ループする
							}
						}

						//キーの読み込み条件
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) 
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                            //検索
							(void)fscanf(m_pFile, "%d", &LoodMotionSetEnemy[nMotionCount].NumKey);	//キーの数を検索
						}

						//パーツごとの位置関係を読み取る
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{

							//ループする
							while (nLoopNumber)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //検索

								//コメントを読み込んだ時
								if (m_aDataSearch[N_INIT_NUMBER] == '#')
								{
									fgets(m_aDataSearch, FGET_NUMBER_2, m_pFile); //ファイルから文字を読み取る
									continue;                                     //処理を続ける
								}

								//モーションの読み込み終了
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //処理を抜ける
								}

								//フレームを読み取る条件
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									//フレーム数を検索
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].Frame);
								}

								//キーの中身の情報を読み取る条件
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//ループ
									while (nLoopNumber)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //文字を読み取る

										//コメントを読み込んだ時
										if (m_aDataSearch[N_INIT_NUMBER] == '#')
										{
											continue;                                      //処理を続ける
											fgets(m_aDataSearch, FGET_NUMBER_1, m_pFile);  //ファイルから文字を読み取る
										}

										//位置を読み取る条件
										if (!strcmp(m_aDataSearch, "POS"))
										{
											//位置の同期
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, 
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z);
										}

										//向きを読み取る条件
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											//向きの同期
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, 
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&LoodMotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z);
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
							nKeyCount = N_INIT_NUMBER;  //キーカウントの初期化
							nKeySetCount++;           //データの加算
						}
					}
					nKeySetCount = N_INIT_NUMBER; //カウントの初期化
					nMotionCount++;             //データの加算
				}
			}
			fclose(m_pFile); //ファイルを閉じる
			break;           //処理を抜ける
		}
	}

	//敵1番目を選択している時
	if (aSelect == "Enemy001")
	{
		int RightnCount = N_INIT_NUMBER; //for分用の変数
		int LeftnCount = N_INIT_NUMBER;  //for分用の変数

		m_nEnemy001Parts = m_nNumParts; //パーツ数の取得

		for (int nLoodMotionSetEnemy = N_INIT_NUMBER;nLoodMotionSetEnemy< NUM_ENEMYMOTION; nLoodMotionSetEnemy++)
		{
			MotionSetEnemy001[nLoodMotionSetEnemy] = LoodMotionSetEnemy[nLoodMotionSetEnemy];
		}

		for (int nLoodModelPrtsEnemy = N_INIT_NUMBER; nLoodModelPrtsEnemy < MAX_ENEMYPARTS; nLoodModelPrtsEnemy++)
		{
			m_pModelPrtsEnemy001[nLoodModelPrtsEnemy] = m_pLoodModelPrtsEnemy[nLoodModelPrtsEnemy];
		}

		//最大パーツ数分回す
		for (int nCount = N_INIT_NUMBER; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo001[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //値を複製する
		}

		//右肩の位置を体の位置分加算する
		m_pSaveModelPrtUpdateInfo001[PARTS_RIGHT_SHOLDER_NUMBER].pos += m_pLoodModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//左肩の位置を体の位置分加算する
		m_pSaveModelPrtUpdateInfo001[PARTS_LEFT_SHOLDER_NUMBER].pos += m_pLoodModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//右肩から右肩の武器まで
		for (RightnCount = PARTS_RIGHT_SHOLDER_NUMBER; RightnCount <= PARTS_RIGHT_SHOLDER_WEAPON_NUMBER; RightnCount++)
		{
			//初期値は現在の右パーツ
			for (int nCount1 = RightnCount+ BEFORE_PARTS_COUNT; nCount1 < RightnCount; nCount1++)
			{
				//カウントが右肩からの時
				if (nCount1 >= PARTS_RIGHT_SHOLDER_NUMBER)
				{
					//位置を加算する,
					m_pSaveModelPrtUpdateInfo001[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount1].pos.x, m_pSaveModelPrtUpdateInfo001[nCount1].pos.y, m_pSaveModelPrtUpdateInfo001[nCount1].pos.z);
				}
			}
		}

		//左肩から左肩の武器まで
		for (LeftnCount = PARTS_LEFT_SHOLDER_NUMBER; LeftnCount <= PARTS_LEFT_SHOLDER_WEAPON_NUMBER; LeftnCount++)
		{
			//初期値は現在の左パーツ
			for (int nCount2 = LeftnCount + BEFORE_PARTS_COUNT; nCount2 < LeftnCount; nCount2++)
			{
				//カウントが左肩からの時
				if (nCount2 >= PARTS_LEFT_SHOLDER_NUMBER)
				{
					//位置を加算する
					m_pSaveModelPrtUpdateInfo001[LeftnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount2].pos.x, m_pSaveModelPrtUpdateInfo001[nCount2].pos.y, m_pSaveModelPrtUpdateInfo001[nCount2].pos.z);  
				}
			}
		}

		//下半身分回す（腰から下なので腰の番号＋１番目）
		for (int nLowBody = PARTS_LEFT_MIDDLELEG_NUMBER; nLowBody <= PARTS_LEFT_WAIST_NUMBER + PARTS_LOWER_BODY_COUNT; nLowBody++)
		{
			//m_pSaveModelPrtUpdateInfo[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //値を複製する

			//腰から親パーツ分回す
			for (int nWaist = PARTS_LEFT_WAIST_NUMBER; nWaist < nLowBody; nWaist++)
			{
				m_pSaveModelPrtUpdateInfo001[nLowBody].pos.y += m_pSaveModelPrtInfo[nWaist].pos.y; ////腰の分足す(腰の位置ー親パーツ)
			}
		}
	}

	//敵002が選択された時
	else if (aSelect == "Enemy002")
	{
		m_nEnemy002Parts = m_nNumParts; //パーツ数の取得

		//最大パーツ数分回す
		for (int nCount = N_INIT_NUMBER; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo002[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //値を複製する
		}

		for (int nLoodModelPrtsEnemy = N_INIT_NUMBER; nLoodModelPrtsEnemy < MAX_ENEMYPARTS; nLoodModelPrtsEnemy++)
		{
			m_pModelPrtsEnemy002[nLoodModelPrtsEnemy] = m_pLoodModelPrtsEnemy[nLoodModelPrtsEnemy];
		}

	}
}

//===============================
//敵001のモーションを行う
//===============================
void CEnemyCharacter::MotionInfoEnemy001()
{

	//モデルのパーツ分繰り返す
	for (int nModelCount = N_INIT_NUMBER; nModelCount < m_nEnemy001Parts; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy001[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCountEnemy001 != MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
			{
				//現在のモーションの次のモーションから現在のモーションの位置を引く
				Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001 + NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].pos;

				//現在のモーションの次のモーションから現在のモーションの向きを引く
				Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001 + NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].aKey[nModelCount].rot;
			}
			else
			{
				//最初のモーションのキーから現在のモーションの総数ー１を引く
				Movepos = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetEnemy001[m_MotionStateEnemy001].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot - MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame; //現在の位置を計算でだした位置と加算させる
			rot = Moverot / (float)MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame; //向きの位置を計算でだした向きと加算させる

			//モーションが飛ぶでループがオフの時
			if (MotionSetEnemy001[ENEMYJUMP].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy001 == ENEMYJUMP && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYJUMP].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //モーションフレームを初期化する
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);     //位置を初期化する
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);     //向きを初期化する
				}
			}

			//モーションが攻撃でループがオフの時
			if (MotionSetEnemy001[ENEMYATTACK].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy001 == ENEMYATTACK && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYATTACK].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //モーションフレームを初期化する
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                   //位置を初期化する
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                   //向きを初期化する
				}
			}

			//モーションが死亡でループがオフの時
			if (MotionSetEnemy001[ENEMYDIE].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy001 == ENEMYDIE && MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey - BEFORE_MOTION_COUNT)
				{
					MotionSetEnemy001[ENEMYDIE].KeySet[MotionCountEnemy001].Frame = N_INIT_NUMBER; //モーションフレームを初期化
					pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                //位置を初期化する
					rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER);                //向きを初期化する
				}
			}

			//差分の分だけ加算
			m_pModelPrtsEnemy001[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrtsEnemy001[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}
	
	m_nEnemy001Frame++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (m_nEnemy001Frame == MotionSetEnemy001[m_MotionStateEnemy001].KeySet[MotionCountEnemy001].Frame)
	{
		m_nEnemy001Frame = N_INIT_NUMBER; //フレームを初期化
		MotionCountEnemy001++;            //モーションのカウントを増加

	    //現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountEnemy001 == MotionSetEnemy001[m_MotionStateEnemy001].NumKey)
		{
			MotionCountEnemy001 = N_INIT_NUMBER; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountEnemy001 + NEXT_MOTION_COUNT == MotionSetEnemy001[m_MotionStateEnemy001].NumKey && MotionSetEnemy001[m_MotionStateEnemy001].Loop == N_INIT_NUMBER)
		{
			//特殊な行動の終わり
			m_bMotionEnemyType = false; //モーションの判定をoffにする
			//MotionCountEnemy001=1;
			//SetMotionBoss(NEUTRAL);   //モーションの情報の切り替え
		}
	}
}

//===============================
//敵002のモーションを行う
//===============================
void CEnemyCharacter::MotionInfoEnemy002()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = N_INIT_NUMBER; nModelCount < m_nEnemy002Parts; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy002[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(F_INIT_NUMBER, F_INIT_NUMBER, F_INIT_NUMBER); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCountEnemy002 != MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT)
			{
				//現在のモーションの次のモーションから現在のモーションの位置を引く
				Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002 + NEXT_MOTION_COUNT].aKey[nModelCount].pos - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].pos;

				//現在のモーションの次のモーションから現在のモーションの向きを引く
				Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002 + NEXT_MOTION_COUNT].aKey[nModelCount].rot - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].aKey[nModelCount].rot;
			}
			else
			{
				//最初のモーションのキーから現在のモーションの総数ー１を引く
				Movepos = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].pos;

				//最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetEnemy002[m_MotionStateEnemy002].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot - MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionSetEnemy002[m_MotionStateEnemy002].NumKey - BEFORE_MOTION_COUNT].aKey[nModelCount].rot;
			}


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame; //現在の位置を計算でだした位置と加算させる
			rot = Moverot / (float)MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame; //向きの位置を計算でだした向きと加算させる


			//差分の分だけ加算
			m_pModelPrtsEnemy002[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrtsEnemy002[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}

	m_nEnemy002Frame++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (m_nEnemy002Frame == MotionSetEnemy002[m_MotionStateEnemy002].KeySet[MotionCountEnemy002].Frame)
	{
		m_nEnemy002Frame = N_INIT_NUMBER;  //フレームを初期化
		MotionCountEnemy002++;             //モーションのカウントを増加

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountEnemy002 == MotionSetEnemy002[m_MotionStateEnemy002].NumKey)
		{
			MotionCountEnemy002 = N_INIT_NUMBER; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountEnemy002 + NEXT_MOTION_COUNT == MotionSetEnemy002[m_MotionStateEnemy002].NumKey && MotionSetEnemy002[m_MotionStateEnemy002].Loop == N_INIT_NUMBER)
		{
			//特殊な行動の終わり
			m_bMotionEnemyType = false; //モーションの判定をoffにする
		}
	}
}

//==============================
//モーションの設定
//==============================
void CEnemyCharacter::SetMotionEnemy001(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy001 != motiontype && m_bMotionEnemyType == false) //現在のモーションと違ったら
	{
		m_MotionStateEnemy001 = motiontype;     //モーションを設定
		MotionCountEnemy001 = N_INIT_NUMBER;    //モーションのカウントを初期化
		m_nEnemy001Frame = N_INIT_NUMBER;       //フレームのカウントの初期化

		//モデルのパーツ分繰り返す
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//パーツの情報がある時
			if (m_pModelPrtsEnemy001[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy001[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                                //現在の位置を読み取った値にする
				m_pModelPrtsEnemy001[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						        //現在の向きを読み取った値にする
				m_pModelPrtsEnemy001[nModelCount]->GetPos() += MotionSetEnemy001[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos; //現在の位置を設定したモーションの位置と加算
				m_pModelPrtsEnemy001[nModelCount]->GetRot() += MotionSetEnemy001[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot; //現在の向きを設定したモーションの向きと加算
			}
		}
	}
}


//==============================
//モーションの設定
//==============================
void CEnemyCharacter::SetMotionEnemy002(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy002 != motiontype && m_bMotionEnemyType == false) //現在のモーションと違ったら
	{
		m_MotionStateEnemy002 = motiontype;   //モーションを設定
		MotionCountEnemy002 = N_INIT_NUMBER;  //モーションのカウントを初期化
		m_nEnemy002Frame = N_INIT_NUMBER;     //フレームのカウントの初期化

		//モデルのパーツ分繰り返す
		for (int nModelCount = N_INIT_NUMBER; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//パーツの情報がある時
			if (m_pModelPrtsEnemy002[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy002[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                                //現在の位置を読み取った値にする
				m_pModelPrtsEnemy002[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						        //現在の向きを読み取った値にする
				m_pModelPrtsEnemy002[nModelCount]->GetPos() += MotionSetEnemy002[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].pos; //現在の位置を設定したモーションの位置と加算
				m_pModelPrtsEnemy002[nModelCount]->GetRot() += MotionSetEnemy002[motiontype].KeySet[N_INIT_NUMBER].aKey[nModelCount].rot; //現在の向きを設定したモーションの向きと加算
			}
		}
	}
}
