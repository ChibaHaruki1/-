//======================================================================
//
//オブジェクトの情報をTextファイルから読み取る処理
//Auther:Haruki Chiba[object_set.cpp]
//
//======================================================================


//============================
//インクルード
#include "object_set.h"
#include "manager.h"
#include "score.h"


//============================
//static変数の初期化
int CObjectSet::m_nClearScore = 0;


//=========================
//コンストラクタ
//=========================
CObjectSet::CObjectSet()
{
	//読み込むパスの名前を設定
	m_aFieldBlockStratName = "FIELDBLOCKSET";               //地面用ブロックの名前を設定
	m_aGoUpBlockStratName = "GOUPBLOCKSET";                 //上がる用ブロックの名前を設定
	m_aRoadBlockStratName = "ROADBLOCKSET";                 //道用ブロックの名前を設定
	m_aWallRoadBlockStratName = "WALLROADBLOCKSET";         //壁兼道用ブロックの名前を設定
	m_aWallRoadBlock001StratName = "WALLROADBLOCK001SET";   //壁兼道用ブロック001の名前を設定
	m_aSmallBlockStratName = "SMALLBLOCKSET";               //小さいブロックの名前を設定
	m_aSmallBlock001StratName = "SMALLBLOCK001SET";         //小さいブロック001の名前を設定
	m_aUpWallBlockStratName = "UPWALLBLOCKSET";             //上壁の名前を設定

	//終了するパスの名前を設定
	m_aFieldBlockEndName = "END_FIELDBLOCKSET";             //地面用ブロックの名前を設定
	m_aGoUpBlockEndName = "END_GOUPBLOCKSET";				//上がる用ブロックの名前を設定
	m_aRoadBlockEndName = "END_ROADBLOCKSET";				//道用ブロックの名前を設定
	m_aWallRoadBlockEndName = "END_WALLROADBLOCKSET";		//壁兼道用ブロックの名前を設定
	m_aWallRoadBlock001EndName = "END_WALLROADBLOCK001SET";	//壁兼道用ブロック001の名前を設定
	m_aSmallBlockEndName = "END_SMALLBLOCKSET";				//小さいブロックの名前を設定
	m_aSmallBlock001EndName = "END_SMALLBLOCK001SET";		//小さいブロック001の名前を設定
	m_aUpWallBlockEndName = "END_UPWALLBLOCKSET";			//上壁の名前を設定

	//読み取れる最大数分回す
	for (int nCount = 0; nCount < MAX_DATAMOJI; nCount++)
	{
		m_aData[nCount] = {}; //文字の読み取り配列の初期化
	}

	m_nFieldBlockCount = 0;
	m_nGoUpBlock = 0;
	m_nRoadBlock = 0;
}


//=========================
//デストラクタ
//=========================
CObjectSet::~CObjectSet()
{
	m_nClearScore = 0; //スコアの初期化
}


//=========================
//初期化処理
//=========================
HRESULT CObjectSet::Init()
{
	//現在のモードを読み取る
	switch (CManager::GetScene()->GetMode())
	{
		//ステージ１の時
	case CScene::MODE::MODE_GAME01:
		StageOneInformation("data\\TEXT\\OBJECT\\TelephonPole.txt"); //電柱の読み込み
		StageOneInformation("data\\TEXT\\OBJECT\\Block.txt");        //ブロックの読み込み
		StageOneInformation("data\\TEXT\\OBJECT\\BreakHouse.txt");   //壊れた家の読み込み
		StageOneInformation("data\\TEXT\\OBJECT\\Enemy.txt");        //敵の読み込み
		StageOneInformation("data\\TEXT\\OBJECT\\MotionEnemy.txt");  //モーション付きの敵の読み込み

		SetCreateCountInPlayer();                                    //生成数をプレイヤーに渡す処理関数を呼ぶ

		return S_OK;  //処理を抜ける

		//ステージ２の時
	case CScene::MODE::MODE_GAME02:
		StageOneInformation("data\\TEXT\\OBJECT\\Block1.txt");       //ブロック1の読み込み
		StageOneInformation("data\\TEXT\\OBJECT\\Ceiling.txt");      //天井の読み込み

		return S_OK; //処理を抜ける

		//リザルト時の時
	case CScene::MODE::MODE_RESULT:
		ResultScoreWrite("data\\TEXT\\ResultScore.txt");        //リザルトスコアの書き込み
		ResultScoreInformation("data\\TEXT\\ResultScore.txt");  //リザルトスコアの読み込み

		return S_OK;
	}
	return E_FAIL;
}


//================================================================================
//ステージ１番目のオブジェクトの情報を設定
//================================================================================
void CObjectSet::StageOneInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	//外部ファイル読み込み (無限)
	while (1)
	{
		(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

		//コメントを読み込んだ時
		if (m_aData[0] == '#')
		{
			continue; //続行
		}

		//この文字を見つけた時
		if (!strcmp(m_aData, "END_SCRIPT"))
		{
			fclose(pFile);        //ファイルを閉じる
			pFile = nullptr;      //ファイルの情報を無くす
			break;                //処理を抜ける
		}

		LoodTelephonPole(pFile);  //電柱の情報を読み取る
		LoodBlock(pFile);         //ブロックの情報を読み取る
		LoodBreakHouse(pFile);    //壊れた家の情報を読み取る
		LoodEnemy(pFile);         //敵の情報を読み込む
		LoodMotionInEnemy(pFile); //モーション付きの敵の情報を読み込む
		LoodCeiling(pFile);
	}
}

//================================================================================
//リザルトスコアの情報を読み込む
//================================================================================
void CObjectSet::ResultScoreInformation(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "r"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	LoodResultScore(pFile); //リザルトスコアの読み込み処理を呼ぶ

	fclose(pFile);          //ファイルを閉じる
}

//================================================================================
//リザルトスコアの情報を書き込む
//================================================================================
void CObjectSet::ResultScoreWrite(const char* pFileName)
{
	FILE* pFile = fopen(pFileName, "w"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (pFile == nullptr)
	{
		return; //処理を抜ける
	}

	fprintf(pFile, "%d", m_nClearScore); //文字を書き込む

	fclose(pFile);                       //ファイルを閉じる
}


//=================================
//電柱の情報を読み込む処理
//=================================
void CObjectSet::LoodTelephonPole(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	///これが書かれていた時
	if (!strcmp(m_aData, "TELEPHONPOLESET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_TELEPHONPOLESET"))
			{
				CManager::GetScene()->GetPlayerX()->SetLaserCount(CManager::GetInstance()->GetLaserCount());
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount()++;    //電柱の配列を進める
				CManager::GetScene()->GetPlayerX()->GetAllTelephonPoleCount()++; //作られた全体数もカウントするー＞増やす

				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::TELEPHONPOLE, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX, PosY, PosZ));                                    //電柱の生成
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERAUP, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + 20.0f, PosY + 180.0f, PosZ - 50.0f));   //監視カメラの上の部分の生成
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SURVEILLANCECAMERADOWN, CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(), D3DXVECTOR3(PosX + 20.0f, PosY + 170.0f, PosZ - 50.0f)); //監視カメラの下の部分の生成
				CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::LASER, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //レーザーの生成
			}
		}
	}
}

//=================================
//壊れた家の情報を読み込む処理
//=================================
void CObjectSet::LoodBreakHouse(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, "BREAKHOUSESET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_BREAKHOUSESET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::BREAKHOUSE, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //壊れた家の生成
			}
		}
	}
}

//=================================
//天井の情報を読み込む処理
//=================================
void CObjectSet::LoodCeiling(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, "CEILINGSET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_CEILINGSET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALCEILLING, D3DXVECTOR3(PosX, PosY, PosZ)); //ボス戦の足場
			}
		}
	}
}

//=================================
//敵の情報を読み込む処理
//=================================
void CObjectSet::LoodEnemy(FILE* pFile)
{
	int nNumber = 0;               //生成番号
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, "ENEMYSET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_ENEMYSET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);      //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);      //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);      //三番目の値を格納
				(void)fscanf(pFile, "%d", &nNumber);   //生成する敵の週類を番号で取得

				//番号で判定
				switch (nNumber)
				{
				case 0:
					CManagerEnemy::Create(D3DXVECTOR3(PosX, PosY, PosZ), CObjectX::TYPE::ENEMY);                                   //敵の生成
					break; //処理を抜ける

				case 1:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY001, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //敵001の生成
					break; //処理を抜ける

				case 2:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMY002, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //敵002の生成
					break; //処理を抜ける
				}
			}
		}
	}
}

//==============================================
//モーション付きの敵の情報を読み込む処理
//==============================================
void CObjectSet::LoodMotionInEnemy(FILE* pFile)
{
	int nNumber = 0;               //生成番号
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	//これが書かれていた時
	if (!strcmp(m_aData, "MOTIONENEMYSET"))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, "END_MOTIONENEMYSET"))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData);    //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);      //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);      //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);      //三番目の値を格納
				(void)fscanf(pFile, "%d", &nNumber);   //生成する敵の週類を番号で取得

				//番号で判定
				switch (nNumber)
				{
				case 1:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //敵001の生成
					break; //処理を抜ける

				case 2:
					CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION002, 0, D3DXVECTOR3(PosX, PosY, PosZ)); //敵002の生成
					break; //処理を抜ける
				}
			}
		}
	}
}

//========================================
//ブロックの情報を読み込む処理
//========================================
void CObjectSet::LoodBlock(FILE* pFile)
{
	float PosX, PosY, PosZ = 0.0f; //posの位置を保管するための変数

	//地面用ブロックの読み込み
	if (!strcmp(m_aData, m_aFieldBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData);     //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aFieldBlockEndName))
			{
				m_nFieldBlockCount++;               //生成数を増やす
				break;                              //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FIELDBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //地面用ブロックの生成
			}
		}
	}

	//上がる用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aGoUpBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData);     //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aGoUpBlockEndName))
			{
				m_nGoUpBlock++;                     //生成数を増やす
				break;                              //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::GOUPBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //上がる用ブロックの生成
			}
		}
	}

	//道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aRoadBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData);     //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aRoadBlockEndName))
			{
				m_nRoadBlock++;                     //生成数を増やす
				break;                              //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::ROADBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //道用ブロックの生成
			}
		}
	}

	//壁兼道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aWallRoadBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aWallRoadBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //壁兼道用ブロックの生成
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aWallRoadBlock001StratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aWallRoadBlock001EndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::WALLROADBLOCK001, D3DXVECTOR3(PosX, PosY, PosZ)); //壁兼道用ブロック001の生成
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aSmallBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aSmallBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //小さいブロックの生成
			}
		}
	}

	// 道用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aSmallBlock001StratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aSmallBlock001EndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SMALLBLOCK001, D3DXVECTOR3(PosX, PosY, PosZ)); //小さいブロック001の生成
			}
		}
	}
	// 上の壁用ブロックの情報を読み込む
	else if (!strcmp(m_aData, m_aUpWallBlockStratName))
	{
		//ループ(無限月読)
		while (1)
		{
			(void)fscanf(pFile, "%s", m_aData); //文字を読み取る

			//題名がEND_TELEPHONPOLESETだった時
			if (!strcmp(m_aData, m_aUpWallBlockEndName))
			{
				break; //処理を抜ける
			}

			//題名がPOSだった時
			if (!strcmp(m_aData, "POS"))
			{
				(void)fscanf(pFile, "%s", m_aData); //文字を読み取る 個々の場合「＝」を読み取る
				(void)fscanf(pFile, "%f", &PosX);   //一番目の値を格納
				(void)fscanf(pFile, "%f", &PosY);   //二番目の値を格納
				(void)fscanf(pFile, "%f", &PosZ);   //三番目の値を格納

				//生成する
				CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::UPWALLBLOCK, D3DXVECTOR3(PosX, PosY, PosZ)); //上壁のブロックの生成
			}
		}
	}
}


//================================================
//resultスコアの情報を読み込む
//================================================
void CObjectSet::LoodResultScore(FILE* pFile)
{
	(void)fscanf(pFile, "%d", &m_nClearScore); //一番目の値を格納

	CManagerScore::Create(CScene::MODE::MODE_RESULT, m_nClearScore); //リザルトスコアの生成
}


//==========================================
//ブロックの読み込む名前のパスの取得処理
//==========================================
const char* CObjectSet::GetStratBlockName(CObjectX::TYPE type)
{
	//タイプが地面用ブロックの時
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockStratName;           //名前を返す
	}

	//タイプが上がるようブロックの時
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockStratName;            //名前を返す
	}

	//タイプが道用ブロックの時
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockStratName;            //名前を返す
	}

	//タイプが壁兼道用ブロックの時
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockStratName;        //名前を返す
	}

	//タイプが壁兼道用ブロック001の時
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001StratName;     //名前を返す
	}

	//タイプが小さいブロックの時
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockStratName;           //名前を返す
	}

	//タイプが小さいブロック001の時
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001StratName;        //名前を返す
	}

	//上壁の時
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockStratName;          //名前を返す
	}

	return nullptr; //無を返す
}


//==========================================
//ブロックの終了する名前のパスの取得処理
//==========================================
const char* CObjectSet::GetEndBlockName(CObjectX::TYPE type)
{
	//タイプが地面用ブロックの時
	if (type == CObjectX::TYPE::FIELDBLOCK)
	{
		return m_aFieldBlockEndName;           //名前を返す
	}

	//タイプが上がるようブロックの時
	else if (type == CObjectX::TYPE::GOUPBLOCK)
	{
		return m_aGoUpBlockEndName;            //名前を返す
	}

	//タイプが道用ブロックの時
	else if (type == CObjectX::TYPE::ROADBLOCK)
	{
		return m_aRoadBlockEndName;            //名前を返す
	}

	//タイプが壁兼道用ブロックの時
	else if (type == CObjectX::TYPE::WALLROADBLOCK)
	{
		return m_aWallRoadBlockEndName;        //名前を返す
	}

	//タイプが壁兼道用ブロック001の時
	else if (type == CObjectX::TYPE::WALLROADBLOCK_001)
	{
		return m_aWallRoadBlock001EndName;     //名前を返す
	}

	//タイプが小さいブロックの時
	else if (type == CObjectX::TYPE::SMALLBLOCK)
	{
		return m_aSmallBlockEndName;           //名前を返す
	}

	//タイプが小さいブロック001の時
	else if (type == CObjectX::TYPE::SMALLBLOCK_001)
	{
		return m_aSmallBlock001EndName;        //名前を返す
	}

	//上壁の時
	else if (type == CObjectX::TYPE::UPWALLBLOCK)
	{
		return m_aUpWallBlockEndName;          //名前を返す
	}

	return nullptr; //無を返す
}


//========================================
//生成数をプレイヤーに渡す処理関数
//========================================
void CObjectSet::SetCreateCountInPlayer()
{
	CManager::GetScene()->GetPlayerX()->SetFieldBlockCount(m_nFieldBlockCount); //地面用ブロックの生成数を取得
	CManager::GetScene()->GetPlayerX()->SetGoUpBlockCount(m_nGoUpBlock);        //上がる用ブロックの生成数を取得

}


//========================================
//textファイルの情報を生成
//========================================
CObjectSet* CObjectSet::Create()
{
	CObjectSet* m_pObjectSet = new CObjectSet(); //動的確保

	//初期化に成功
	if (SUCCEEDED(m_pObjectSet->Init()))
	{
		return m_pObjectSet; //情報を返す
	}

	return nullptr; //無を返す
}