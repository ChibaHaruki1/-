//===========================================
//
//全体を管理する処理[manager.cpp]
//Auther:Chiba Haruki
//
//===========================================


//===========================================
//インクルード
#include "manager.h"
#include "rendererh.h"


//===========================================
//static変数の初期化
CRenderer* CManager::m_pRenderer = nullptr;       //レンダラーの初期化
CInputKeyBoard* CManager::m_pKeyBoard = nullptr;  //キーボードの初期化
CInputJoyPad* CManager::m_pJyoPad = nullptr;      //JOYPADの初期化
CSound* CManager::m_pSound = nullptr;             //音源の初期化
CScene* CManager::m_pScene = nullptr;             //シーンの初期化
CInstance* CManager::m_pInstance = nullptr;       //インスタンスの初期化
CObjectSet* CManager::m_pObjectSet = nullptr;     //オブジェクト配置の初期化
CEvent* CManager::m_pEvent = nullptr;             //イベントの初期化
CMain* CManager::m_pMain = nullptr;               //メインの初期化


//===================
//コンストラクタ
//===================
CManager::CManager()
{

}

//===================
//デストラクタ
//===================
CManager::~CManager()
{

}

//==================
//初期化処理
//==================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pSound = new CSound();                     //動的確保
	m_pSound->InitSound(hWnd);                   //音源の初期化
							                     
	m_pMain = new CMain();                       //動的確保
								                 
	m_pRenderer = new CRenderer();               //動的確保をする
										         
	m_pKeyBoard = new CInputKeyBoard();          //キーボードの動的確保
										         
	m_pJyoPad = new CInputJoyPad();              //ジョイパットの動的確保

	m_pRenderer->Init(hInstance, hWnd, bWindow); //レンダラーのWindowの処理を呼び出す

	//キーボードの初期化処理に失敗した時
	if (FAILED(m_pKeyBoard->Init(hInstance, hWnd)))
	{
		return E_FAIL; //失敗を返す
	}

	//ジョイパットの初期化処理に失敗した時
	if (FAILED(m_pJyoPad->Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//==================
//終了処理
//==================
void CManager::Uninit()
{
	//レンダラーの情報がある時
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit(); //破棄処理を呼ぶ
		delete m_pRenderer;    //情報を消す
		m_pRenderer = nullptr; //情報を無くす
	}

	//キーボードの情報がある時
	if (m_pKeyBoard != nullptr)
	{
		m_pKeyBoard->Uninit(); //破棄処理を呼ぶ
		delete m_pKeyBoard;    //情報を消す
		m_pKeyBoard = nullptr; //情報を無くす
	}


	//ジョイパットの情報がある時
	if (m_pJyoPad != nullptr)
	{
		m_pJyoPad->Uninit(); //破棄処理を呼ぶ
		delete m_pJyoPad;    //情報を消す
		m_pJyoPad = nullptr; //情報を無くす
	}

	//音源の情報がある時
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound(); //破棄処理を呼ぶ
		delete m_pSound;         //情報を消す
		m_pSound = nullptr;      //情報を無くす
	}

	//画面遷移の情報があるとき
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit(); //破棄処理を呼ぶ
		delete m_pScene;    //情報を消す
		m_pScene = nullptr; //情報を無くす
	}

	//インスタンス情報があるとき
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit(); //破棄処理を呼ぶ
		delete m_pInstance;    //情報を消す
		m_pInstance = nullptr; //情報を無くす
	}

	//textファイルの情報がある時
	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;    //情報を消す
		m_pObjectSet = nullptr; //情報を無くす
	}

	//イベントの情報がある時
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;        //情報を消す
		m_pEvent = nullptr;     //情報を無くす
	}

	//メインの情報がある時
	if (m_pMain != nullptr)
	{
		delete m_pMain;         //情報を消す
		m_pMain = nullptr;      //情報を無くす
	}
}

//==================
//更新処理
//==================
void CManager::Update()
{
	m_pKeyBoard->Update(); //キーボードの更新処理
	m_pJyoPad->Update();   //ジョイパットの更新処理
	m_pRenderer->Update(); //レンダラーの更新処理
	m_pScene->Update();    //更新処理を呼ぶ
	m_pScene->AnyUpdate(); //その他更新処理を呼ぶ(基底クラスから継承していないクラスの処理)
}


//==================
//描画処理
//==================
void CManager::Draw()
{
	m_pRenderer->Draw();   //レンダラーの描画処理
}


//===============================
//画面遷移のモードの変更
//===============================
void CManager::SetMode(CScene::MODE mode)
{
	//sceneの情報がある時
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();  //破棄処理を呼ぶ
		delete m_pScene;     //情報を消す
		m_pScene = nullptr;  //情報を無くす
	}

	//インスタンス情報があるとき
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();  //破棄処理を呼ぶ
		delete m_pInstance;     //情報を消す
		m_pInstance = nullptr;  //情報を無くす
	}

	//eventの情報がある時
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;     //情報を消す
		m_pEvent = nullptr;  //情報を無くす
	}

	m_pSound->StopSound();           //音源を止める
	m_pInstance = new CInstance();   //インスタンスの生成
	m_pScene = CScene::Create(mode); //シーンの生成

	//タイトルとリザルト時以外の時textファイルの情報を読み込む
	if (mode != CScene::MODE::MODE_TITLE)
	{
		m_pObjectSet = CObjectSet::Create(); //textから読み取ったオブジェクトを配置する
		m_pEvent = new CEvent();             //動的確保する
	}

	//シーンがリザルトの時
	if (mode == CScene::MODE::MODE_RESULT)
	{
		//情報がある時
		if (m_pObjectSet != nullptr)
		{
			delete m_pObjectSet;     //情報を消す
			m_pObjectSet = nullptr;  //情報を無くす
		}
	}
}
