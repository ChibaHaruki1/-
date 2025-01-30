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
	for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
	{
		m_pModelPrtsEnemy[nCount] = nullptr;                   //敵のパーツの初期化
		m_pSaveModelPrtInfo[nCount] = {};					   //モデルパーツの保管情報の初期化
		m_pSaveModelPrtUpdateInfo001[nCount] = {};				   //更新用モデルパーツの保管情報の初期化
		m_pSaveModelPrtUpdateInfo002[nCount] = {};				   //更新用モデルパーツの保管情報の初期化
	}

	MotionCountEnemy = 0;                                      //モーション時のカウントを初期化
	m_nNumParts = 0;                                           //パーツ数の初期化
	m_nEnemy001Parts = 0;                                      //敵001パーツ数の初期化
	m_nEnemy002Parts = 0;                                      //敵002パーツ数の初期化
	m_bMotionEnemyType = false;                                //モーションタイプの初期化
	m_MotionStateEnemy = ENEMYWALK;                            //モーション状態の初期化
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
	for (int nCount1 = 0; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy[nCount1] != nullptr)
		{
			m_pModelPrtsEnemy[nCount1]->Uninit(); //破棄処理
			delete m_pModelPrtsEnemy[nCount1];    //情報を消す
			m_pModelPrtsEnemy[nCount1] = nullptr; //情報を無くす
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
	for (int nCount = 0; nCount < m_nEnemy001Parts; nCount++)
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

	for (int nCount = 0; nCount < m_nEnemy002Parts; nCount++)
	{
		//パーツごとの位置を常に更新＝もともとのパーツのposを足し合わせた物
		for (int nCount = 0; nCount < m_nEnemy001Parts; nCount++)
		{
			//パーツの位置の更新
			GetPosPartsEnemy(nCount) = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo002[nCount].pos.x + GetPos().x,
				m_pSaveModelPrtUpdateInfo002[nCount].pos.y + GetPos().y,
				m_pSaveModelPrtUpdateInfo002[nCount].pos.z + GetPos().z); //各パーツを保管値＋現在の位置で修正
		}
	}
}

//========================
//敵の描画処理
//========================
void CEnemyCharacter::DrawEnemy(int NumPrts, int nNumber)
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
		if (m_pModelPrtsEnemy[nCount] != nullptr)
		{
			m_pModelPrtsEnemy[nCount]->Draw(pMtx); //各パーツの描画処理
		}
	}
}

//======================
//ボスのロード処理
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int nCount = 0;                      //最初のパーツ数をカウントするための変数
	int nKeyCount = 0;                   //モーションのキーをカウントするための変数
	int nModelPrtsCount = 0;             //生成するパーツ数のカウントするための変数
	char aPrtsPass[MAX_PARTS_SEARCH];    //各パーツを読み取る際のパスを読み込むための変数
	char m_aDataSearch[MAX_DATA_SEARCH]; //必要な情報を読み取る際の文字列を読みむための変数
								       
	int nMotionCount = 0;                //モーションの数をカウントするための変数
	int nKeySetCount = 0;                //モーションのキーセットの数をカウントするための変数
								         
	FILE* m_pFile = nullptr;             //ファイルポインター

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
					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						m_pModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //パーツの生成
						m_pModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizePartsEnemy(nModelPrtsCount));														   //情報を同期させる
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

						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch); //検索
							(void)fscanf(m_pFile,"%d",&m_nNumParts);     //パーツ数の初期化
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
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetIndexPrts()); //パーツのインデックスを読み取る
								}

								//親パーツかどうかを読み取る条件
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetIndexModelPrts()); //親パーツかを読み取る

									//読み込んだ値がー１の時
									if (m_pModelPrtsEnemy[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrtsEnemy[nCount]->SetParent(nullptr); //情報なし
									}

									//その他
									else
									{
										m_pModelPrtsEnemy[nCount]->SetParent(m_pModelPrtsEnemy[m_pModelPrtsEnemy[nCount]->GetIndexModelPrts()]); //親である情報を入れる
									}
								}

								//位置を読み取る条件
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetPos().x, &m_pModelPrtsEnemy[nCount]->GetPos().y, &m_pModelPrtsEnemy[nCount]->GetPos().z); //位置の同期
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrtsEnemy[nCount]->GetPos();                //位置を保管する
									//m_pSaveModelPrtInfo[nCount].pos += MotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetRot().x, &m_pModelPrtsEnemy[nCount]->GetRot().y, &m_pModelPrtsEnemy[nCount]->GetRot().z); //位置の同期
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrtsEnemy[nCount]->GetRot();                //向きを保管する
									//m_pSaveModelPrtInfo[nCount].rot += MotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
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
							fgets(m_aDataSearch, 40, m_pFile); //ファイルから文字列を読み込む
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
								MotionSetEnemy[nMotionCount].Loop = false; //ループしない
							}

							//その他
							else
							{
								MotionSetEnemy[nMotionCount].Loop = true;  //ループする
							}
						}

						//キーの読み込み条件
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) 
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                        //検索
							(void)fscanf(m_pFile, "%d", &MotionSetEnemy[nMotionCount].NumKey);	//キーの数を検索
						}

						//パーツごとの位置関係を読み取る
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{

							//ループする
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //検索

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

								//フレームを読み取る条件
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].Frame); //フレーム数を検索
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
											fgets(m_aDataSearch, 40, m_pFile);  //ファイルから文字を読み取る
										}

										//位置を読み取る条件
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //位置の同期
										}

										//向きを読み取る条件
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //向きの同期
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
					nMotionCount++; //データの加算
				}
			}
			fclose(m_pFile); //ファイルを閉じる
			break;           //処理を抜ける
		}
	}

	//敵1番目を選択している時
	if (aSelect == "Enemy001")
	{
		int RightnCount = 0; //for分用の変数
		int LeftnCount = 0;  //for分用の変数

		m_nEnemy001Parts = m_nNumParts; //パーツ数の取得

		//最大パーツ数分回す
		for (int nCount = 0; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo001[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //値を複製する
		}

		//右肩の位置を体の位置分加算する
		m_pSaveModelPrtUpdateInfo001[PARTS_RIGHT_SHOLDER_NUMBER].pos += m_pModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//左肩の位置を体の位置分加算する
		m_pSaveModelPrtUpdateInfo001[PARTS_LEFT_SHOLDER_NUMBER].pos += m_pModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//右肩から右肩の武器まで
		for (RightnCount = PARTS_RIGHT_SHOLDER_NUMBER; RightnCount <= PARTS_RIGHT_SHOLDER_WEAPON_NUMBER; RightnCount++)
		{
			//初期値は現在の右パーツー１
			for (int nCount1 = RightnCount-1; nCount1 < RightnCount; nCount1++)
			{
				//位置を加算する,
				m_pSaveModelPrtUpdateInfo001[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount1].pos.x, m_pSaveModelPrtUpdateInfo001[nCount1].pos.y, m_pSaveModelPrtUpdateInfo001[nCount1].pos.z);
			}
		}

		//左肩から次のパーツ（５の次＝６）から終わりまで（終わりは武器まで（７番））
		for (LeftnCount = PARTS_LEFT_SHOLDER_NUMBER; LeftnCount <= PARTS_LEFT_SHOLDER_WEAPON_NUMBER; LeftnCount++)
		{
			//初期値は現在の左パーツー１
			for (int nCount2 = LeftnCount; nCount2 < LeftnCount; nCount2++)
			{
				m_pSaveModelPrtUpdateInfo001[LeftnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount2].pos.x, m_pSaveModelPrtUpdateInfo001[nCount2].pos.y, m_pSaveModelPrtUpdateInfo001[nCount2].pos.z);  //位置を加算する
			}
		}

		//下半身分回す（腰から下なので腰の番号＋１）
		for (int nLowBody = PARTS_LEFT_WAIST_NUMBER + 1; nLowBody <= PARTS_LEFT_WAIST_NUMBER + PARTS_LOWER_BODY_COUNT; nLowBody++)
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
		for (int nCount = 0; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo002[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //値を複製する
		}

	}
}

//===============================
//敵001のモーションを行う
//===============================
void CEnemyCharacter::MotionInfoEnemy001()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < m_nEnemy001Parts; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCountEnemy != MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //現在のモーションの次のモーションから現在のモーションの位置を引く
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //現在のモーションの次のモーションから現在のモーションの向きを引く
			}
			else
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].pos; //最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].rot; //最初のモーションのキーから現在のモーションの総数ー１を引く
			}


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //現在の位置を計算でだした位置と加算させる
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //向きの位置を計算でだした向きと加算させる

			//モーションが飛ぶでループがオフの時
			if (MotionSetEnemy[ENEMYJUMP].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy == ENEMYJUMP && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey-1)
				{
					MotionSetEnemy[ENEMYJUMP].KeySet[MotionCountEnemy].Frame = 0; //モーションフレームを初期化する
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                          //位置を初期化する
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                          //向きを初期化する
				}
			}

			//モーションが攻撃でループがオフの時
			if (MotionSetEnemy[ENEMYATTACK].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy == ENEMYATTACK && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey-1)
				{
					MotionSetEnemy[ENEMYATTACK].KeySet[MotionCountEnemy].Frame = 0; //モーションフレームを初期化する
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                            //位置を初期化
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                            //向きを初期化
				}
			}

			//モーションが死亡でループがオフの時
			if (MotionSetEnemy[ENEMYDIE].Loop == false)
			{
				//モーションの状態が歩きで設定されている時とキーセットが最後の時
				if (m_MotionStateEnemy == ENEMYDIE && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
				{
					MotionSetEnemy[ENEMYDIE].KeySet[MotionCountEnemy].Frame = 0; //モーションフレームを初期化
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                         //位置を初期化
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                         //向きを初期化
				}
			}

			//差分の分だけ加算
			m_pModelPrtsEnemy[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrtsEnemy[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}
	
	GetFrame()++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (GetFrame() == MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame)
	{
		SetFrame(0);        //フレームを初期化
		MotionCountEnemy++; //モーションのカウントを増加

	    //現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey)
		{
			MotionCountEnemy = 0; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountEnemy + 1 == MotionSetEnemy[m_MotionStateEnemy].NumKey && MotionSetEnemy[m_MotionStateEnemy].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionEnemyType = false; //モーションの判定をoffにする
			//MotionCountEnemy=1;
			//SetMotionBoss(NEUTRAL);   //モーションの情報の切り替え
		}
	}
}

//===============================
//敵001のモーションを行う
//===============================
void CEnemyCharacter::MotionInfoEnemy002()
{
	//モデルのパーツ分繰り返す
	for (int nModelCount = 0; nModelCount < m_nEnemy002Parts; nModelCount++)
	{
		//パーツの情報がある時
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//移動量の初期化
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置の初期化
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの初期化

			//移動量の変数
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //位置を現在のモーションの位置と同期
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //向きを現在のモーションの向きと同期

			//最初のキーじゃないなら差分を求める
			if (MotionCountEnemy != MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //現在のモーションの次のモーションから現在のモーションの位置を引く
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //現在のモーションの次のモーションから現在のモーションの向きを引く
			}
			else
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].pos; //最初のモーションのキーから現在のモーションの総数ー１を引く
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].rot; //最初のモーションのキーから現在のモーションの総数ー１を引く
			}


			//差分の分をフレームで割った値で加算
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //現在の位置を計算でだした位置と加算させる
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //向きの位置を計算でだした向きと加算させる


			//差分の分だけ加算
			m_pModelPrtsEnemy[nModelCount]->GetPos() += pos; //現在の位置を計算でだした位置と加算させる
			m_pModelPrtsEnemy[nModelCount]->GetRot() += rot; //向きの位置を計算でだした向きと加算させる
		}
	}

	GetFrame()++; //フレームの加算

	//終わりのフレームになったらカウントを最初からにする
	if (GetFrame() == MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame)
	{
		SetFrame(0);        //フレームを初期化
		MotionCountEnemy++; //モーションのカウントを増加

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey)
		{
			MotionCountEnemy = 0; //カウントを0にする
		}

		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (MotionCountEnemy + 1 == MotionSetEnemy[m_MotionStateEnemy].NumKey && MotionSetEnemy[m_MotionStateEnemy].Loop == 0)
		{
			//特殊な行動の終わり
			m_bMotionEnemyType = false; //モーションの判定をoffにする
		}
	}
}

//==============================
//モーションの設定
//==============================
void CEnemyCharacter::SetMotionEnemy(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy != motiontype && m_bMotionEnemyType == false) //現在のモーションと違ったら
	{
		m_MotionStateEnemy = motiontype; //モーションを設定
		MotionCountEnemy = 0;            //モーションのカウントを初期化
		SetFrame(0);                     //フレームのカウントの初期化

		//モデルのパーツ分繰り返す
		for (int nModelCount = 0; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//パーツの情報がある時
			if (m_pModelPrtsEnemy[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                             //現在の位置を読み取った値にする
				m_pModelPrtsEnemy[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						      //現在の向きを読み取った値にする
				m_pModelPrtsEnemy[nModelCount]->GetPos() += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].pos;   //現在の位置を設定したモーションの位置と加算
				m_pModelPrtsEnemy[nModelCount]->GetRot() += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].rot;   //現在の向きを設定したモーションの向きと加算
			}
		}
	}
}
