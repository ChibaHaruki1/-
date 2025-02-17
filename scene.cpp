//====================================
//
//画面遷移処理[scene.cpp]
//Auther:Haruki Chiba
//
//====================================


//====================================
//インクルード
#include "scene.h"
#include "manager.h"
#include "rendererh.h"
#include "bullet.h"
#include "enemy.h"
#include "efect.h"
#include "collision.h"
#include "score.h"
#include "objectX.h"
#include "stage_obj.h"
#include "block.h"
#include "gage.h"
#include "enemyinmotion.h"
#include "bg.h"


//================================
//グローバル変数
CManagerBg* g_pBG; //背景のBGのグローバル変数(すでにbg.hにscene.hをインクルードしている為メンバー変数に持てない　前方宣言なら持てる？)


//=======================
//コンストラクタ
//=======================
CScene::CScene()
{
	m_pCamera = nullptr;               //カメラポインターの初期化
	m_pLight = nullptr;                //光源ポインターの初期化
	m_pPlayerX = nullptr;              //プレイヤーポインターの初期化
	m_bOneSound = false;               //１度だけ音源を流すフラグの初期化
	m_bOneScene = false;               //１度だけそのシーンの処理を通すフラグの初期化
	m_bPlay = false;                   //遊べる状態になっているかどうかのフラグの初期化
	m_Mode = MODE::MODE_RESULT;        //モードの設定
	m_nFrame = CObject::N_INIT_NUMBER; //フレームの初期化
}


//=======================
//デストラクタ
//=======================
CScene::~CScene()
{

}


//=======================
//初期化処理
//=======================
HRESULT CScene::Init()
{
	m_pCamera = new CCamera(); //カメラの動的確保
	m_pLight = new CLight();   //光源の動的確保
	m_pCamera->Init();         //カメラの初期化
	m_pLight->Init();          //光源の初期化

	CManager::GetRenderer()->GetDrawShader() = false; //シェーダーをしない

	return S_OK;               //成功を返す
}


//=======================
//終了処理
//=======================
void CScene::Uninit()
{
	CObject::ReleaseAll();         //全てのUninit()を呼び、deleteする
	CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする

	m_pPlayerX = nullptr;          //情報を無くす

	//カメラの情報がある時
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit(); //カメラの終了処理
		delete m_pCamera;    //メモリの解放
		m_pCamera = nullptr; //情報を無くす
	}

	//光源の情報がある時
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit(); //光源の終了処理
		delete m_pLight;    //メモリの解放
		m_pLight = nullptr; //情報を無くす
	}
}


//=======================
//更新処理
//=======================
void CScene::Update()
{
	m_pCamera->Update(); //カメラの更新処理
	m_pLight->Update();  //光源の更新処理
}

//=======================
//他の物のUpdateを呼ぶ
//=======================
void CScene::AnyUpdate()
{
	//ステージ２にの時
	if (m_Mode == MODE::MODE_GAME02)
	{
		CManager::GetEvent()->Update(); //イベントの更新処理を呼ぶ
	}
}


//=======================
//生成
//=======================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr; //基底クラスの動的確保

	//ゲームモードが１の時
	if (mode == MODE::MODE_GAME01)
	{
		pScene = new CGame01();               //動的確保
		pScene->m_Mode = mode;                //現在のモードを引数と同期させる
											  
		//初期化に成功した時				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //情報を返す
		}									  
	}										  
											  
	//ゲームモードが２の時				   	  
	else if (mode == MODE::MODE_GAME02)		  
	{										  
		pScene = new CGame02();               //動的確保
		pScene->m_Mode = mode;                //現在のモードを引数と同期させる
											  
		//初期化に成功した時				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //情報を返す
		}									  
	}	

	////裏ステージの時
	//else if (mode == MODE::MODE_HIDEGAME)
	//{
	//	pScene = new CHideGame();             //的確保
	//	pScene->m_Mode = mode;                //現在のモードを引数と同期させる

	//	//初期化に成功した時				     
	//	if (SUCCEEDED(pScene->Init()))
	//	{
	//		return pScene;                    //情報を返す
	//	}
	//}
											  
	//タイトルの時						   	  
	else if (mode == MODE::MODE_TITLE)		  
	{										  
		pScene = new CTitle();                //動的確保
		pScene->m_Mode = mode;                //現在のモードを引数と同期させる
											  
		//初期化に成功した時				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //情報を返す
		}									  
	}										  
											  
	//リザルトの時						   	  
	else if (mode == MODE::MODE_RESULT)		  
	{										  
		pScene = new CResult();               //動的確保
		pScene->m_Mode = mode;                //現在のモードを引数と同期させる
											  
		//初期化に成功した時				     
		if (SUCCEEDED(pScene->Init()))		  
		{									  
			return pScene;                    //情報を返す
		}
	}

	//ゲームモードの時
	else if (mode == MODE::MODE_GAMEOVER)
	{
		pScene = new CGameOver();             //動的確保
		pScene->m_Mode = mode;                //現在のモードを引数と同期させる

		//初期化に成功した時
		if (SUCCEEDED(pScene->Init()))
		{
			return pScene;                    //情報を返す
		}
	}

	return nullptr;                           //無を返す
}


//================================================================================================================================
//                                                    ゲームモードの処理
//================================================================================================================================


//================================================================================================================================
//                                                    ステージ１
//================================================================================================================================


//=======================
//コンストラクタ
//=======================
CGame01::CGame01()
{
	m_pFade = nullptr; //フェードポインターの初期化
}


//=======================
//デストラクタ
//=======================
CGame01::~CGame01()
{

}


//=======================
//初期化処理
//=======================
HRESULT CGame01::Init()
{
	float fInitNumber = CObject::F_INIT_NUMBER; //初期値

	//初期化に失敗した時
	if (FAILED(CScene::Init()))
	{
		return E_FAIL;                                           //失敗を返す
	}														    
															    
	g_pBG = CManagerBg::Create(MODE::MODE_TITLE);                //背景のUI生成
	m_pFade = CFade::Create();                                   //フェードの生成

	GetCamera()->GetAdjustmentPosZ() = INIT_CAMERA_ADJUST_POS_Z; //カメラのZ軸の調整

	//カメラの向きの設定
	GetCamera()->SetRot(D3DXVECTOR3(fInitNumber, CObjectX::D3DX_PI_ORI + MINUS_ROT, fInitNumber));

	InitCreate();                                                //タイトルに必要な生成
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING);    //プレイヤーのモーションを探すに設定

	//プレイヤーの向きを設定
	GetPlayerX()->SetRot(D3DXVECTOR3(fInitNumber, CObjectX::D3DX_PI_ORI + MINUS_ROT, fInitNumber));

	//プレイヤーのY軸の位置を設定
	GetPlayerX()->SetPos(D3DXVECTOR3(fInitNumber, INIT_PLAYER_POS_Y, fInitNumber));
															    
	return S_OK;                                                 //成功を返す
}


//=======================
//終了処理
//=======================
void CGame01::Uninit()
{
	CScene::Uninit(); //破棄処理
}


//=======================
//更新処理
//=======================
void CGame01::Update()
{
	//シーンの処理が通った時
	if (GetOneScene() == true)
	{
		//フェードの情報がある時
		if (m_pFade != nullptr)
		{
			m_pFade->CFade::SetFade(CFade::FADE::FADE_OUT); //フェードアウトに設定

			//フェードの処理が終わったら（完全に暗くなったら）
			if (m_pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
			{
				float fInitNumber = CObject::F_INIT_NUMBER; //初期値

				m_pFade->Release();                                                                  //情報を消す
				g_pBG->Release();                                                                    //情報を消す
				m_pFade = nullptr;                                                                   //情報を無くす
				g_pBG = nullptr;                                                                     //情報を無くす
				GetPlayerX()->SetGravityFlag(true);                                                  //重力ON
				GetCamera()->GetAdjustmentPosZ() = UPDATE_CAMERA_ADJUST_POS_Z;                       //カメラのZ軸の調整
				GetCamera()->SetRot(D3DXVECTOR3(fInitNumber, fInitNumber, fInitNumber));             //カメラの向きの初期化
				GetPlayerX()->SetRot(D3DXVECTOR3(fInitNumber, -CObjectX::D3DX_PI_ORI, fInitNumber)); //カメラの向きの初期化
				GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);                        //プレイヤーのモーションを設定
				CompileCreate();                                                                     //createしたいものを関数化して呼ぶ
				return;                                                                              //処理を抜ける
			}
		}

		//スペースシップ０番目の情報がある時
		if (CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER) != nullptr)
		{
			SetAdjustFrame()++; //フレームを増やす

			//フレームが規定値より高い時
			if (GetFrame() >= MAX_FRAME)
			{
				//スペースシップを消す
				CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->Release();	        

				//スペースシップのポインターの初期化
				CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SPECEBATTLESHIP000, BATTLESHIP_NUMBER); 
			}
		}
	}

	//シーンの処理が通っていない時
	else if (GetOneScene() == false)
	{
		GetPlayerX()->SetGravityFlag(false); //プレイヤーの重力Off

		//Enterキーが押された時かAキーを押された時
		if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
		{
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING);    //指定の音源を止める
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_NORMALBGM);  //BDMを流す
			SetOneScene(true);                                                            //シーンの処理が通ったに設定
		}
	}

	//音源が流れていない時
	if (GetOneSound() == false)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDMを流す
		SetOneSound(true);                                                         //一度だけ流す
	}

	CScene::Update(); //更新処理
}


//=======================
//初期化時のCretae関数を呼ぶ
//=======================
void CGame01::InitCreate()
{
	float fInitNumber = CObject::F_INIT_NUMBER; //初期値

	//プレイヤーの生成
	GetPlayerX() = CPlayerX::Create();

	//スペースシップ1番目の生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(fInitNumber, BATTLESHIP_0_POS_Y, BATTLESHIP_0_POS_Z));

	//空の生成
	CSkyDoom::Create(D3DXVECTOR3(fInitNumber, fInitNumber, SKY_POS_Z), SKY_CREATE_NUMBER);
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame01::CompileCreate()
{
	int nInitNumber = CObject::N_INIT_NUMBER; //初期値

	//スペースシップ２番目の生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(BATTLESHIP_1_POS_X, BATTLESHIP_1_POS_Y, CObject::F_INIT_NUMBER));

	//スコアの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, nInitNumber);

	//プレイヤーのHPゲージの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, nInitNumber);
}


//================================================================================================================================
//                                                    ステージ2
//================================================================================================================================


//=======================
//コンストラクタ
//=======================
CGame02::CGame02()
{
	SetPlay(false); //遊べるに設定
}


//=======================
//デストラクタ
//=======================
CGame02::~CGame02()
{

}


//=======================
//初期化処理
//=======================
HRESULT CGame02::Init()
{
	float fInitNumber = CObject::F_INIT_NUMBER; //初期値

	//初期化に失敗した時
	if (FAILED(CScene::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CompileCreate();                                                                      //createしたいものを関数化して呼ぶ
	GetPlayerX()->SetPos(D3DXVECTOR3(POS_X, POS_Y, CObject::F_INIT_NUMBER));              //プレイヤーの位置の設定
	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING);                             //プレイヤーのモーションを探すに設定

	 //Y軸の向きを設定
	CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetRot(D3DXVECTOR3(fInitNumber, -CObjectX::D3DX_PI_ORI, fInitNumber));

	return S_OK;       //成功を返す
}


//=======================
//終了処理
//=======================
void CGame02::Uninit()
{
	CScene::Uninit(); //破棄処理
}


//=======================
//更新処理
//=======================
void CGame02::Update()
{
	//シーンの処理が通った時
	if (GetOneScene() == false)
	{
		SetAdjustFrame()++; //フレームを増やす

		//第一行動
		if (GetFrame() <= FRAME_1)
		{
			GetPlayerX()->SetGravityFlag(false);                                                              //プレイヤーの重力Off
			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().x += PLUS_POS_X;   //X軸の位置の増加
			GetPlayerX()->SetAdjustPos().x += PLUS_POS_X;                                                     //X軸の位置の増加
		}

		//第二行動
		else if (GetFrame() <= FRAME_2)
		{
			GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);                                      //プレイヤーのモーションを設定
			GetPlayerX()->SetGravityFlag(true);                                                                //重力ON
		}

		//第三行動
		else if (GetFrame() <= FRAME_3)
		{
			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().x += PLUS_POS_X;    //X軸の位置の増加
			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().y += PLUS_POS_Y;    //Y軸の位置の増加
		}
		else
		{
			SetOneScene(true);                                                                                 //フラグのOff
			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->Release();                         //スペースシップを消す

			//スペースシップのポインターの初期化
			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SPECEBATTLESHIP000, BATTLESHIP_NUMBER); 
			return;
		}
	}

	CScene::Update(); //更新処理
}


//=======================
//Cretae関数を呼ぶ
//=======================
void CGame02::CompileCreate()
{
	int nInitNumber = CObject::N_INIT_NUMBER;   //初期値
	float fInitNumber = CObject::F_INIT_NUMBER; //初期値

	//Xファイルのcreate
	GetPlayerX() = CPlayerX::Create(); //プレイヤーの生成

	//スペースシップの生成
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(POS_X, POS_Y, BATTLESHOP_POS_Z));    

	//空の生成
	CSkyDoom::Create(D3DXVECTOR3(fInitNumber, fInitNumber, SKY_POS_Z), nInitNumber);                                         

	//店の生成
	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, nInitNumber, D3DXVECTOR3(SHOP_POS_X, fInitNumber, SHOP_POS_Z));

	//ボス戦の足場
	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::FINALBLOCK, D3DXVECTOR3(SCAFFOLD_POS_X, SCAFFOLD_POS_Y, fInitNumber));     

	//スコアの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());  

	//プレイヤーのHPゲージの生成
	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, nInitNumber);                                             
}


////================================================================================================================================
////                                                    裏ステージ
////================================================================================================================================
//
//
////=======================
////コンストラクタ
////=======================
//CHideGame::CHideGame()
//{
//	SetPlay(false); //遊べるに設定
//}
//
//
////=======================
////デストラクタ
////=======================
//CHideGame::~CHideGame()
//{
//
//}
//
//
////=======================
////初期化処理
////=======================
//HRESULT CHideGame::Init()
//{
//	//初期化に失敗した時
//	if (FAILED(CScene::Init()))
//	{
//		return E_FAIL; //失敗を返す
//	}
//
//	CompileCreate();                                                                      //createしたいものを関数化して呼ぶ
//	GetPlayerX()->SetPos(D3DXVECTOR3(-POS_X, 200.0f, 0.0f));                              //プレイヤーの位置の設定
//	GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::LOKING);                             //プレイヤーのモーションを探すに設定
//	CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->GetRot().y = -CObjectX::D3DX_PI_ORI;  //Y軸の向きを設定
//
//	return S_OK;       //成功を返す
//}
//
//
////=======================
////終了処理
////=======================
//void CHideGame::Uninit()
//{
//	CScene::Uninit(); //破棄処理
//}
//
//
////=======================
////更新処理
////=======================
//void CHideGame::Update()
//{
//	//シーンの処理が通った時
//	if (GetOneScene() == false)
//	{
//		SetAdjustFrame()++;
//
//		if (GetFrame() <= 80)
//		{
//			GetPlayerX()->SetGravityFlag(false);                                                //プレイヤーの重力Off
//			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().x += PLUS_POS_X;    //X軸の位置の増加
//			GetPlayerX()->SetAdjustPos().x += PLUS_POS_X;                                      //X軸の位置の増加
//		}
//		else if (GetFrame() <= 81)
//		{
//			GetPlayerX()->SetMotion(CCharacter::MOTIONSTATE::TITLE_JUMP);                       //プレイヤーのモーションを設定
//			GetPlayerX()->SetGravityFlag(true);                                                 //重力ON
//		}
//		else if (GetFrame() <= 300)
//		{
//			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().x += PLUS_POS_X;    //X軸の位置の増加
//			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->SetAdjustPos().y += 3.0f;         //X軸の位置の増加
//		}
//		else
//		{
//			SetOneScene(true);                                                                  //フラグのOff
//			CManager::GetInstance()->GetSpeceBattleShip(BATTLESHIP_NUMBER)->Release();                          //スペースシップを消す
//			CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::SPECEBATTLESHIP000, 0); //スペースシップのポインターの初期化
//			return;
//		}
//	}
//	CScene::Update(); //更新処理
//}
//
//
////=======================
////Cretae関数を呼ぶ
////=======================
//void CHideGame::CompileCreate()
//{
//	//Xファイルのcreate
//	GetPlayerX() = CPlayerX::Create();                                                                                        //プレイヤーの生成
//	CManager::GetInstance()->CreateBlock(CObjectX::STRATEGYTYPE::SPECEBATTLESHIP000, D3DXVECTOR3(-POS_X, 200.0f, 100.0f));    //スペースシップの生成
//	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 0);                                                                     //空の生成
//	CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::SHOP, 0, D3DXVECTOR3(200.0f, 0.0f, 150.0f));            //店の生成
//	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::SCORE, CManager::GetObjectSet()->GetClearScore());    //スコアの生成
//	CManager::GetInstance()->GetCreateObjectInstnace2D(CObject2D::TYPE::HP, 0);                                               //プレイヤーのHPゲージの生成
//}


//================================================================================================================================
//                                                    タイトルモードの処理
//================================================================================================================================

//======================
//コンストラクタ
//======================
CTitle::CTitle()
{
	m_pFade = nullptr;
}


//======================
//デストラクタ
//======================
CTitle::~CTitle()
{

}


//======================
//初期化
//======================
HRESULT CTitle::Init()
{
	//CManagerBg::Create(MODE::MODE_TITLE);
	//////CBgText::Create();
	//pFade = CFade::Create();

	CScene::Init();

	GetCamera()->GetAdjustmentPosZ() = 700;

	return S_OK;
}


//======================
//終了処理
//======================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
	//CObjectManagerX::ReleaseAll(); //全てのunitを呼び、deleteする
}


//=======================
//更新処理
//=======================
void CTitle::Update()
{
	////Enterキーが押されたとき
	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true && pFade->GetAlph() <= 245)
	//{
	//	SetOneScene(true);
	//}

	//else if (GetOneScene() == true)
	//{
	//	pFade->CFade::SetFade(CFade::FADE::FADE_OUT);

	//	//フェードの処理が終わったら（完全に暗くなったら）
	//	if (pFade->GetAlph() >= CFade::FINISH_FADE_OUT)
	//	{
	//		CManager::SetMode(CScene::MODE::MODE_GAME01);
	//		return; //処理を抜ける
	//	}

	//	//CManager::SetMode(CScene::MODE_GAME01);
	//}

	//if (GetOneSound() == false)
	//{
	//	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_WING); //BDMを流す
	//	SetOneSound(true);
	//}

	CScene::Update();
}


//=============================
//タイトルゲーム画面処理
//=============================
void CTitle::Game()
{

}


//================================================================================================================================
//                                                   リザルトモードの処理
//================================================================================================================================


//======================
//コンストラクタ
//======================
CResult::CResult()
{
	
}


//======================
//デストラクタ
//======================
CResult::~CResult()
{

}


//======================
//初期化
//======================
HRESULT CResult::Init()
{
	CManagerBg::Create(MODE::MODE_RESULT); //リザルトBGの生成

	return S_OK;                           //成功を返す
}


//======================
//終了処理
//======================
void CResult::Uninit()
{
	CScene::Uninit(); //破棄処理
}


//=======================
//更新処理
//=======================
void CResult::Update()
{
	//Enterキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true || CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A) == true)
	{
		SetOneScene(true);                            //シーンの処理が通ったに設定
	}

	//シーンの処理が通った時
	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_GAME01); //モードの設定
		return;                                       //処理を抜ける
	}
}


//================================================================================================================================
//                                                   ゲームオーバーモードの処理
//================================================================================================================================


//======================
//コンストラクタ
//======================
CGameOver::CGameOver()
{
	
}


//======================
//デストラクタ
//======================
CGameOver::~CGameOver()
{

}


//======================
//初期化
//======================
HRESULT CGameOver::Init()
{
	CManagerBg::Create(MODE::MODE_GAMEOVER); //ゲームオーバーBGの生成

	return S_OK;                             //成功を返す
}


//======================
//終了処理
//======================
void CGameOver::Uninit()
{
	CScene::Uninit(); //破棄処理
}


//=======================
//更新処理
//=======================
void CGameOver::Update()
{
	//Enterキーが押されたとき
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_RETURN) == true|| CManager::GetJyoPad()->GetJoypadTrigger(CInputJoyPad::JOYKEY::JOYKEY_A)==true)
	{
		SetOneScene(true);                             //シーンの処理が通ったに設定
	}

	//シーンの処理が通った時
	else if (GetOneScene() == true)
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);  //モードの設定
		return;                                        //処理を抜ける
	}
}