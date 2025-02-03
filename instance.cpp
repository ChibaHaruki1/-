//=============================================
//
//インスタンスを管理する処理[instance.cpp]
//Auther;HARUKI CHIBA
//
//=============================================


//=============================================
//インクルード
#include "instance.h"


//=======================
//コンストラクタ
//=======================
CInstance::CInstance()
{
	//オブジェクトの最大数分回す
	for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;         //地面用ブロックのポインターの初期化
		m_pGoUpBlock[nCount] = nullptr;          //上がるためのブロックのポインターの初期化
		m_pRoadBlock[nCount] = nullptr;          //道用ブロックのポインターの初期化
		m_pWallRoadBlock[nCount] = nullptr;      //壁兼道用ブロックのポインターの初期化
		m_pWallRoadBlock001[nCount] = nullptr;   //壁兼道用ブロック001のポインターの初期化
		m_pSmallBlock[nCount] = nullptr;         //小さいブロックのポインターの初期化
		m_pSmallBlock001[nCount] = nullptr;      //小さいブロック001のポインターの初期化
		m_pUpWallBlock[nCount] = nullptr;        //上壁のポインターの初期化
		m_pDebrisX[nCount] = nullptr;            //破片ポインターの初期化
		m_pPraticles001[nCount] = nullptr;       //パーティクル001のポインターの初期化
	}

	//ステージオブジェクトの最大数分回す
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;            //電柱のポインターの初期化
		m_pSurveillanceCameraUp[nCount1] = nullptr;    //監視カメラの上の部分のポインターの初期化
		m_pSurveillanceCameraDown[nCount1] = nullptr;  //監視カメラの下の部分のポインターの初期化
		m_pLaser[nCount1] = nullptr;                   //レーザーのポインターの初期化
	}

	//がれきの最大数分回す
	for (int nCount2 = N_INIT_NUMBER; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;  //木の板群のポインターの初期化
	}

	//敵の最大数分回す
	for (int nCount3 = N_INIT_NUMBER; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;     //敵001のポインターの初期化
		m_pEnemy002[nCount3] = nullptr;     //敵001のポインターの初期化
	}

	//壊れた家分回す
	for (int nCount4 = N_INIT_NUMBER; nCount4 < MAX_BREAKHOUSE; nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;   //壊れた家のポインターの初期化
	}

	//モーション付きの敵の分回す
	for (int nCount5 = N_INIT_NUMBER; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr; //モーション付きの敵のポインターの初期化
		m_pEnemyInMotion001[nCount5] = nullptr; //モーション付きの敵001のポインターの初期化
		m_pEnemyInMotion002[nCount5] = nullptr; //モーション付きの敵002のポインターの初期化
	}

	//スペースシップの数分回す
	for (int nShip = N_INIT_NUMBER; nShip < MAX_SHIP; nShip++)
	{
		m_pSpeceBattleShip000[nShip] = nullptr; //次のステージへ行くオブジェクトの初期化
	}

	//2Dのインスタンスの初期化
	m_pShopScreen = nullptr;    //ショップ時の背景のポインターの初期化
	m_pPlayerHPGage = nullptr;  //プレイヤーのHPゲージのポインターの初期化
	m_pBossHPGage = nullptr;    //ボスのHPゲージのポインターの初期化
	m_pGameScore = nullptr;     //スコアのポインターの初期化

	//３Dの初期化
	m_pFuelGage = nullptr;
	m_pShop = nullptr;               //店の初期化
	m_pEffect = nullptr;             //プレイヤーの弾につくエフェクトの初期化
	m_pExplosion = nullptr;          //爆発エフェクトの初期化
	m_pExplosion001 = nullptr;       //爆発エフェクト001の初期化
	m_pThander = nullptr;            //雷エフェクトの初期化
	m_pFire = nullptr;               //炎エフェクトのポインターの初期化
	m_pImpact = nullptr;             //衝撃波のポインターの初期化
	m_pDebris = nullptr;             //破片のポインターの初期化
	m_pPillarOfFire = nullptr;       //柱状の炎のポインターの初期化
	m_pSepecialAttack = nullptr;     //必殺技のポインターの初期化
	m_pBossSpecialAttack = nullptr;  //ボスの必殺技のポインターの初期化
	m_pEnemy000 = nullptr;           //敵のポインターの初期化
	m_pBoss = nullptr;               //ボスのポインターの初期化

	//Xオブジェクトの初期化
	m_pFinalBlosk = nullptr;         //最終ステージの地面ブロックのポインターの初期化
	m_pFinalCeiling = nullptr;       //最終ステージの天井ブロックのポインターの初期化

	//作られた数の初期化（作る前にインクリメントするためー１で初期化）
	m_nNumFiledBlock = N_INIT_CREATE_NUMBER;           //地面用ブロックの数を初期化
	m_nNumGoUpBlock = N_INIT_CREATE_NUMBER;            //上がる用ブロックの数を初期化
	m_nRoadBlock = N_INIT_CREATE_NUMBER;               //道用ブロックの数を初期化
	m_nWallRoadBlock = N_INIT_CREATE_NUMBER;           //壁兼道用ブロックの数を初期化
	m_nWallRoadBlock001 = N_INIT_CREATE_NUMBER;        //壁兼道用ブロック001の数を初期化
	m_nSmallBlock = N_INIT_CREATE_NUMBER;              //小さいブロックの数を初期化
	m_nSmallBlock001 = N_INIT_CREATE_NUMBER;           //小さいブロック001の数を初期化
	m_nUpWallBlock = N_INIT_CREATE_NUMBER;             //上壁用ブロックの数を初期化
	m_nEnemy001 = N_INIT_CREATE_NUMBER;                //敵001の数を初期化
	m_nEnemy002 = N_INIT_CREATE_NUMBER;                //敵002の数を初期化
	m_nEnemyInMotion = N_INIT_CREATE_NUMBER;           //モーション付きの敵の数を初期化
	m_nEnemyInMotion001 = N_INIT_CREATE_NUMBER;        //モーション付きの敵001の数を初期化
	m_nEnemyInMotion002 = N_INIT_CREATE_NUMBER;        //モーション付きの敵002の数を初期化
	m_nWoodenBoard = N_INIT_CREATE_NUMBER;             //木の板群の数を初期化
	m_nBreakHouse = N_INIT_CREATE_NUMBER;              //壊れた家の数を初期化
	m_nShip = N_INIT_CREATE_NUMBER;                    //スペースシップの数を初期化
	m_nLaser = N_INIT_CREATE_NUMBER;                   //レーザーの数を初期化
}


//=======================
//デストラクタ
//=======================
CInstance::~CInstance()
{

}


//=======================
//初期化処理
//=======================
HRESULT CInstance::Init()
{
	return S_OK;
}


//=======================
//破棄処理
//=======================
void CInstance::Uninit()
{
	//オブジェクトの最大数分回す
	for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECT_DATA; nCount++)
	{
		m_pFieldBlock[nCount] = nullptr;         //地面用ブロックのポインターの初期化
		m_pGoUpBlock[nCount] = nullptr;          //上がるためのブロックのポインターの初期化
		m_pRoadBlock[nCount] = nullptr;          //道用ブロックのポインターの初期化
		m_pWallRoadBlock[nCount] = nullptr;      //壁兼道用ブロックのポインターの初期化
		m_pWallRoadBlock001[nCount] = nullptr;   //壁兼道用ブロック001のポインターの初期化
		m_pSmallBlock[nCount] = nullptr;         //小さいブロックのポインターの初期化
		m_pSmallBlock001[nCount] = nullptr;      //小さいブロック001のポインターの初期化
		m_pUpWallBlock[nCount] = nullptr;        //上壁のポインターの初期化
		m_pDebrisX[nCount] = nullptr;            //破片ポインターの初期化
		m_pPraticles001[nCount] = nullptr;       //パーティクル001のポインターの初期化
	}

	//ステージオブジェクトの最大数分回す
	for (int nCount1 = N_INIT_NUMBER; nCount1 < MAX_STAGEOBJECT; nCount1++)
	{
		m_pTelephonPole[nCount1] = nullptr;            //電柱のポインターの初期化
		m_pSurveillanceCameraUp[nCount1] = nullptr;    //監視カメラの上の部分のポインターの初期化
		m_pSurveillanceCameraDown[nCount1] = nullptr;  //監視カメラの下の部分のポインターの初期化
		m_pLaser[nCount1] = nullptr;                   //レーザーのポインターの初期化
	}

	//がれきの最大数分回す
	for (int nCount2 = N_INIT_NUMBER; nCount2 < MAX_RUBBLE; nCount2++)
	{
		m_pWoodenBoard[nCount2] = nullptr;  //木の板群のポインターの初期化
	}

	//敵の最大数分回す
	for (int nCount3 = N_INIT_NUMBER; nCount3 < MAX_ENEMY; nCount3++)
	{
		m_pEnemy001[nCount3] = nullptr;     //敵001のポインターの初期化
		m_pEnemy002[nCount3] = nullptr;     //敵001のポインターの初期化
	}

	//壊れた家分回す
	for (int nCount4 = N_INIT_NUMBER; nCount4 < MAX_BREAKHOUSE; nCount4++)
	{
		m_pBreakHouse[nCount4] = nullptr;   //壊れた家のポインターの初期化
	}

	//モーション付きの敵の分回す
	for (int nCount5 = N_INIT_NUMBER; nCount5 < MAX_ENEMYINMOTION; nCount5++)
	{
		m_pEnemyInMotion000[nCount5] = nullptr; //モーション付きの敵のポインターの初期化
		m_pEnemyInMotion001[nCount5] = nullptr; //モーション付きの敵001のポインターの初期化
		m_pEnemyInMotion002[nCount5] = nullptr; //モーション付きの敵002のポインターの初期化
	}

	//スペースシップの数分回す
	for (int nShip = N_INIT_NUMBER; nShip < MAX_SHIP; nShip++)
	{
		m_pSpeceBattleShip000[nShip] = nullptr; //次のステージへ行くオブジェクトの初期化
	}

	//2Dのインスタンスの初期化
	m_pShopScreen = nullptr;    //ショップ時の背景のポインターの初期化
	m_pPlayerHPGage = nullptr;  //
	m_pBossHPGage = nullptr;
	m_pGameScore = nullptr;

	//３Dの初期化
	m_pFuelGage = nullptr;
	m_pShop = nullptr;               //店の初期化
	m_pEffect = nullptr;             //プレイヤーの弾につくエフェクトの初期化
	m_pExplosion = nullptr;          //爆発エフェクトの初期化
	m_pExplosion001 = nullptr;       //爆発エフェクト001の初期化
	m_pThander = nullptr;            //雷エフェクトの初期化
	m_pFire = nullptr;               //炎エフェクトのポインターの初期化
	m_pImpact = nullptr;             //衝撃波のポインターの初期化
	m_pDebris = nullptr;             //破片のポインターの初期化
	m_pPillarOfFire = nullptr;       //柱状の炎のポインターの初期化
	m_pSepecialAttack = nullptr;     //必殺技のポインターの初期化
	m_pBossSpecialAttack = nullptr;  //ボスの必殺技のポインターの初期化
	m_pEnemy000 = nullptr;           //敵のポインターの初期化
	m_pBoss = nullptr;               //ボスのポインターの初期化

	//Xオブジェクトの初期化
	m_pFinalBlosk = nullptr;         //最終ステージの地面ブロックのポインターの初期化
	m_pFinalCeiling = nullptr;       //最終ステージの天井ブロックのポインターの初期化
}


//============================================================================================================================
//敵の情報を無くす
//============================================================================================================================
void CInstance::DesignationUninitXEnemy(CObjectX::TYPE type, int nNumber)
{
	//タイプが敵の時
	if (type == CObjectX::TYPE::ENEMY)
	{
		m_pEnemy000 = nullptr;                  //情報を無くす
	}

	//タイプが敵001の時
	else if (type == CObjectX::TYPE::ENEMY001)
	{
		m_pEnemy001[nNumber] = nullptr;         //指定した番号の情報を無くす
	}

	//タイプが敵002の時
	else if (type == CObjectX::TYPE::ENEMY002)
	{
		m_pEnemy002[nNumber] = nullptr;         //指定した番号の情報を無くす
	}

	//タイプがボスの時
	else if (type == CObjectX::TYPE::BOSS)
	{
		m_pBoss = nullptr;                      //情報を無くす
	}

	//タイプがモーション付きの敵の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_pEnemyInMotion000[nNumber] = nullptr; //情報を無くす
	}

	//タイプがモーション付きの敵001の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_pEnemyInMotion001[nNumber] = nullptr; //情報を無くす
	}

	//タイプがモーション付きの敵001の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION002)
	{
		m_pEnemyInMotion002[nNumber] = nullptr; //情報を無くす
	}

}


//============================================================================================================================
//3Dモデルのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninitX(CObjectX::TYPE type, int nNumber)
{
	//タイプが監視カメラの上部分の時
	if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		m_pSurveillanceCameraUp[nNumber] = nullptr;   //指定した番号の情報をなくす
	}

	//タイプが破片の時
	else if (type == CObjectX::TYPE::DEBRIS)
	{
		if (m_pDebrisX[nNumber] != nullptr)
		{
			m_pDebrisX[nNumber] = nullptr;            //指定した番号の情報をなくす
		}
	}

	//タイプがスペースシップの時
	else if (type == CObjectX::TYPE::SPECEBATTLESHIP000)
	{
		if (m_pSpeceBattleShip000[nNumber] != nullptr)
		{
			m_pSpeceBattleShip000[nNumber] = nullptr; //指定した番号の情報を無くす
		}
	}
}


//============================================================================================================================
//２Dのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninit2D(CObject2D::TYPE type)
{
	//タイプが背景の時
	if (type == CObject2D::TYPE::SCREEN)
	{
		m_pShopScreen = nullptr;     //情報を無くす
	}
}


//============================================================================================================================
//３Dのnullptrにしたいものを指定する処理
//============================================================================================================================
void CInstance::DesignationUninit3D(CObject3D::TYPE type, int nNumber)
{
	//タイプが衝撃波の時
	if (type == CObject3D::TYPE::IMPACT)
	{
		m_pImpact = nullptr;         //情報を無くす
	}

	//タイプがレーザーの時
	else if (type == CObject3D::TYPE::LASER)
	{
		m_pLaser[nNumber] = nullptr; //情報を無くす
	}
}


//============================================================================================================================
//2Dのインスタンスを生成する処理
//============================================================================================================================
CObject2D* CInstance::GetCreateObjectInstnace2D(CObject2D::TYPE type, int nNumber)
{
	//タイプが背景の時
	if (type == CObject2D::TYPE::SCREEN)
	{
		return m_pShopScreen = CShopScreen::Create();                                  //背景を生成
	}														                           
															                           
	//タイプがHPの時										                             
	else if (type == CObject2D::TYPE::HP)					                           
	{														                           
		return m_pPlayerHPGage = CManagerGage::Create(type);                           //HPゲージの生成
	}

	//タイプがボスのHPの時
	else if (type == CObject2D::TYPE::BOSSHP)
	{
		return m_pBossHPGage = dynamic_cast<CBossHPGage*>(CManagerGage::Create(type)); //ボスのHPゲージの生成
	}

	//タイプがスコアの時
	else if (type == CObject2D::TYPE::SCORE)
	{
		m_pGameScore = CManagerScore::Create(CScene::MODE::MODE_GAME01, nNumber);      //スコアの生成
	}

	return nullptr; //無を返す
}


//============================================================================================================================
//3Dのインスタンスを生成する処理
//============================================================================================================================
CObject3D* CInstance::GetCreateObjectInstnace(CObject3D::TYPE type, int nNumber, D3DXVECTOR3 pos)
{

	//タイプがパーティクル001の時
	if (type == CObject3D::TYPE::PRTICLES001)
	{
		return m_pPraticles001[nNumber] = CParticles001::Create(pos);   //パーティクル001の生成
	}

	//タイプがエフェクトの時
	else if (type == CObject3D::TYPE::EFFECT)
	{
		return m_pEffect = CEffect::Create(pos);                        //エフェクトの生成
	}

	//タイプが爆発の時
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		return m_pExplosion = CManagerEffect::Create(pos, type);        //爆発のエフェクトの生成
	}

	//タイプが爆発001の時
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		return m_pExplosion001 = CManagerEffect::Create(pos, type);     //爆発エフェクト001の生成
	}

	//タイプが雷の時
	else if (type == CObject3D::TYPE::THENDER)
	{
		return m_pThander = CManagerEffect::Create(pos, type);          //雷エフェクトの生成
	}

	//タイプが炎の時
	else if (type == CObject3D::TYPE::FIRE)
	{
		return m_pFire = CManagerEffect::Create(pos, type);             //炎エフェクトの生成
	}

	//タイプが衝撃波の時
	else if (type == CObject3D::TYPE::IMPACT)
	{
		return m_pImpact = CManagerBossEffect::Create(pos, type);       //衝撃波の生成
	}

	//タイプが破片の時
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		return m_pDebris = CManagerEffect::Create(pos, type);           //破片の生成
	}

	//タイプが柱状の炎の時
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		return m_pPillarOfFire = CManagerEffect::Create(pos, type);     //柱状の炎のエフェクトの生成
	}

	//タイプが必殺技の時
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		return m_pSepecialAttack = dynamic_cast<CSpecialAttack*>(CManagerEffect::Create(pos, type)); //必殺技のエフェクトの生成
	}

	//タイプがボスの必殺技の時
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		return m_pBossSpecialAttack = CManagerBossEffect::Create(pos, type); //ボスの必殺技のエフェクトの生成
	}

	//タイプが燃料ゲージの時
	else if (type == CObject3D::TYPE::FUELGAGE)
	{
		return 	m_pFuelGage = CFuelGage::Create();                            //燃料ゲージの生成
	}

	//タイプがレーザーの時
	else if (type == CObject3D::TYPE::LASER)
	{
		m_nLaser++;
		return m_pLaser[m_nLaser] = CUI::Create(type);                        //レーザーの生成
	}

	return nullptr; //無を返す
}


//============================================================================================================================
//Xオブジェクトのインスタンスを生成する処理
//============================================================================================================================
CObjectX* CInstance::GetCreateObjectInstanceX(CObjectX::TYPE type, int nNumber, D3DXVECTOR3 pos)
{
	//タイプが破片の時
	if (type == CObjectX::TYPE::DEBRIS)
	{
		return m_pDebrisX[nNumber] = CDebrisX::Create(pos);                      //破片の生成
	}																	         
																		         
	//タイプが電柱の時													         
	else if (type == CObjectX::TYPE::TELEPHONPOLE)						         
	{																	         
		return m_pTelephonPole[nNumber] = CStageObj::Create(pos, type);          //電柱の生成
	}

	//タイプが監視カメラの上の部分の時
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		return m_pSurveillanceCameraUp[nNumber] = CStageObj::Create(pos, type);  //監視カメラの上の部分の生成
	}

	//タイプが監視カメラの下の部分の時
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERADOWN)
	{
		return m_pSurveillanceCameraDown[nNumber] = CStageObj::Create(pos, type); //監視カメラの下の部分の生成
	}

	//タイプが壊れた家の時
	else if (type == CObjectX::TYPE::BREAKHOUSE)
	{
		m_nBreakHouse++;                                                           //作られた数を増やす
		return m_pBreakHouse[m_nBreakHouse] = CStageObj::Create(pos, type);        //壊れた家の生成
	}																		       
																			       
	//タイプが店の時														        
	else if (type == CObjectX::TYPE::SHOP)									       
	{																		       
		return m_pShop = CStageObj::Create(pos, type);                             //店の生成
	}																		       
																			       
	//タイプが敵の時														        
	else if (type == CObjectX::TYPE::ENEMY)									       
	{																		       
		return m_pEnemy000 = CManagerEnemy::Create(pos, type);                     //敵の生成
	}																		       
																			       
	//タイプが敵001の時													  	       
	else if (type == CObjectX::TYPE::ENEMY001)								       
	{																		       
		m_nEnemy001++;														       
		return m_pEnemy001[m_nEnemy001] = CManagerEnemy::Create(pos, type);        //敵001の生成
	}																		       
																			       
	//タイプが敵001の時													  	       
	else if (type == CObjectX::TYPE::ENEMY002)								       
	{																		       
		m_nEnemy002++;														       
		return m_pEnemy002[m_nEnemy002] = CManagerEnemy::Create(pos, type);        //敵002の生成
	}

	//タイプがモーション付きの時
	else if (type == CObjectX::TYPE::ENEMYINMOTION)
	{
		m_nEnemyInMotion++;
		return m_pEnemyInMotion000[m_nEnemyInMotion] = CManagerEnemyInMotion::Create(pos, type);     //モーション付きの敵の生成
	}

	//タイプがモーション付きの敵001の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION001)
	{
		m_nEnemyInMotion001++;
		return m_pEnemyInMotion001[m_nEnemyInMotion001] = CManagerEnemyInMotion::Create(pos, type);  //モーション付きの敵001の生成
	}

	//タイプがモーション付きの敵001の時
	else if (type == CObjectX::TYPE::ENEMYINMOTION002)
	{
		m_nEnemyInMotion002++;
		return m_pEnemyInMotion002[m_nEnemyInMotion002] = CManagerEnemyInMotion::Create(pos, type);  //モーション付きの敵001の生成
	}

	//タイプがボスの時
	else if (type == CObjectX::TYPE::BOSS)
	{
		return m_pBoss = CBoss::Create(pos); //ボスの生成
	}

	return nullptr; //無を返す
}


//============================================================================================================================
//ブロックの生成処理
//============================================================================================================================
CObjectX* CInstance::CreateBlock(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//タイプが地面用ブロックの時
	if (type == CObjectX::STRATEGYTYPE::FIELDBLOCK)
	{
		m_nNumFiledBlock++;                                                                  //作られた数を増やす
		return m_pFieldBlock[m_nNumFiledBlock] = CManagerBlock::Create(pos, type);           //地面用のブロックの生成
	}

	//タイプが上がる用ブロックの時												  	        
	else if (type == CObjectX::STRATEGYTYPE::GOUPBLOCK)
	{
		m_nNumGoUpBlock++;                                                                   //作られた数を増やす
		return m_pGoUpBlock[m_nNumGoUpBlock] = CManagerBlock::Create(pos, type);             //上がるためのブロックの生成
	}

	//タイプが道用ブロックの時													            
	else if (type == CObjectX::STRATEGYTYPE::ROADBLOCK)
	{
		m_nRoadBlock++;                                                                      //作られた数を増やす
		return m_pRoadBlock[m_nRoadBlock] = CManagerBlock::Create(pos, type);                //道用ブロックの生成
	}

	//タイプが壁兼道用ブロックの時													        
	else if (type == CObjectX::STRATEGYTYPE::WALLROADBLOCK)
	{
		m_nWallRoadBlock++;                                                                  //作られた数を増やす
		return m_pWallRoadBlock[m_nWallRoadBlock] = CManagerBlock::Create(pos, type);        //壁兼道用ブロックの生成
	}

	//タイプが壁兼道用ブロック001の時
	else if (type == CObjectX::STRATEGYTYPE::WALLROADBLOCK001)
	{
		m_nWallRoadBlock001++;                                                               //作られた数を増やす
		return m_pWallRoadBlock001[m_nWallRoadBlock001] = CManagerBlock::Create(pos, type);  //壁兼道用ブロック001の生成
	}

	//タイプが小さいブロックの時
	else if (type == CObjectX::STRATEGYTYPE::SMALLBLOCK)
	{
		m_nSmallBlock++;                                                                     //作られた数を増やす
		return m_pSmallBlock[m_nSmallBlock] = CManagerBlock::Create(pos, type);              //小さいブロックの生成
	}

	//タイプが小さいブロック001の時
	else if (type == CObjectX::STRATEGYTYPE::SMALLBLOCK001)
	{
		m_nSmallBlock001++;                                                                  //作られた数を増やす
		return m_pSmallBlock001[m_nSmallBlock001] = CManagerBlock::Create(pos, type);        //小さいブロック001の生成
	}

	//タイプが上壁の時
	else if (type == CObjectX::STRATEGYTYPE::UPWALLBLOCK)
	{
		m_nUpWallBlock++;                                                                    //作られた数を増やす
		return m_pUpWallBlock[m_nUpWallBlock] = CManagerBlock::Create(pos, type);            //上壁の生成
	}

	//タイプがスペースシップの時
	else if (type == CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000)
	{
		m_nShip++;
		return m_pSpeceBattleShip000[m_nShip] = CManagerBlock::Create(pos, type);            //スペースシップの生成
	}

	//タイプが最終ステージの地面の時
	else if (type == CObjectX::STRATEGYTYPE::FINALBLOCK)
	{
		return m_pFinalBlosk = CManagerBlock::Create(pos, type);                              //最終ステージの地面の生成
	}

	//タイプが最終ステージの天井の時
	else if (type == CObjectX::STRATEGYTYPE::FINALCEILLING)
	{
		return m_pFinalCeiling = CManagerBlock::Create(pos, type);                           //最終ステージの天井の生成
	}

	return nullptr; //無を返す
}


//============================================================================================================================
//がれきの生成
//============================================================================================================================
CObjectX* CInstance::CreateRubble(CObjectX::STRATEGYTYPE type, D3DXVECTOR3 pos)
{
	//タイプが木の板群の時
	if (type == CObjectX::STRATEGYTYPE::WODDENBORAD)
	{
		m_nWoodenBoard++;                                                          //作られた数を増やす
		return m_pWoodenBoard[m_nWoodenBoard] = CManagerBlock::Create(pos, type);  //木の板群の生成
	}

	return nullptr; //無を返す
}

