//=================================
//
//入力処理[input.cpp]
//Author:chiba haruki
//
//=================================


//=================================
//インクルード
#include "input.h"
#include "objectX.h"
#include <vector>


//============================================基底クラスInputの処理============================================

//======================
//コンストラクタ
//======================
CInput::CInput()
{
	m_Input = nullptr;  //入力処理の情報の初期化
	m_Device = nullptr; //デバイスの初期化
}

//======================
//デストラクタ
//======================
CInput::~CInput()
{

}


//=============================
//初期化処理
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//情報がない時
	if (m_Input == nullptr)
	{
		//DirectInputオブジェクトの生成に失敗
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return E_FAIL; //失敗を返す
		}
	}

	return S_OK;           //成功を返す
}


//======================
//終了処理
//======================
void CInput::Uninit()
{
	//デバイスの情報がある時
	if (m_Device != nullptr)
	{
		m_Device->Unacquire(); //モードの取り消し
		m_Device->Release();   //情報を消す
		m_Device = nullptr;    //情報を無くす
	}

	//入力情報がある時
	if (m_Input != nullptr)
	{
		m_Input->Release();    //情報を消す
		m_Input = nullptr;     //情報を無くす
	}
}


//======================
//更新処理
//======================
void CInput::Update()
{

}


//============================================キーボードの処理============================================

//======================
//コンストラクタ
//======================
CInputKeyBoard::CInputKeyBoard()
{
	//std::vector<int>nMAX_KEY;
	//nMAX_KEY.resize(MAX_KEY);

	////キーの最大数分回す
	//for(int& nKey : nMAX_KEY)
	//{
	//	m_aKeyState[nKey] = {};
	//	m_aKeyStateTrigger[nKey] = {};

	//	if (nKey >= MAX_KEY)
	//	{
	//		continue;
	//	}
	//}

	//キーの最大数分回す
	for (int nKey = CObjectX::N_INIT_NUMBER; nKey < MAX_KEY; nKey++)
	{
		m_aKeyState[nKey] = {};        //プレス情報の初期化
		m_aKeyStateTrigger[nKey] = {}; //トリガー情報の初期化
	}
}

//======================
//デストラクタ
//======================
CInputKeyBoard::~CInputKeyBoard()
{

}

//===========================
//キーボードの初期化処理
//===========================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//初期化に失敗した時
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL; //失敗を返す
	}

	//入力デバイス（キーボード）の生成に失敗した時
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &GetDevice(), NULL)))
	{
		return E_FAIL; //失敗を返す
	}

	//データフォーマットを設定に失敗した時
	if (FAILED(GetDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //失敗を返す
	}

	//協調モードを設定に失敗した時
	if (FAILED(GetDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //失敗を返す
	}

	//キーボードへのアクセス権を獲得
	GetDevice()->Acquire();

	return S_OK; //成功を返す
}

//========================
//キーボードの終了処理
//========================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit(); //終了処理を呼ぶ
}


//==========================
//キーボードの更新処理
//==========================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY]; //キーボードの入力情報
	
	//入力デバイスからデータを取得に成功した時
	if (SUCCEEDED(GetDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[CObjectX::N_INIT_NUMBER])))
	{
		//キーの最大数分回す
		for (int nCntKey = CObjectX::N_INIT_NUMBER; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存	
			m_aKeyState[nCntKey] = aKeyState[nCntKey];                                                      //キーボードのプレス情報を保存	
		}
	}
	else
	{
		GetDevice()->Acquire(); //キーボードへのアクセス権を獲得
	}
}


//============================================ジョイパットの処理============================================


//================================
//コンストラクタ
// //================================
CInputJoyPad::CInputJoyPad()
{

}


//================================
//デストラクタ
//================================
CInputJoyPad::~CInputJoyPad()
{

}


//==========================================
//ジョイパッドの初期化処理
//==========================================
HRESULT CInputJoyPad::Init(void)
{
	//メモリのクリア
	memset(&m_JyoPad.joykeyState, CObjectX::N_INIT_NUMBER, sizeof(XINPUT_STATE));
	memset(&m_JyoPad.joykeyStateTrigger, CObjectX::N_INIT_NUMBER, sizeof(XINPUT_STATE));

	//XInputのステート設定(有効にする)
	XInputEnable(true);

	return S_OK; //成功を返す
}

//==========================================
//ジョイパッドの終了処理
//==========================================
void CInputJoyPad::Uninit(void)
{
	//XInputのステートを設定
	XInputEnable(false);
}


//==========================================
//ジョイパッドの更新処理
//==========================================
void CInputJoyPad::Update(void)
{
	XINPUT_STATE joykeystate; //ジョイパッドの入力情報

	//ジョイパッドの情報を取得
	if (XInputGetState(CObjectX::N_INIT_NUMBER, &joykeystate) == ERROR_SUCCESS)
	{
		m_JyoPad.Button = m_JyoPad.joykeyState.Gamepad.wButtons;                              //ボタンの情報を設定
		m_JyoPad.joykeyStateTrigger.Gamepad.wButtons = m_JyoPad.Button & ~m_JyoPad.OldButton; //トリガーの情報を設定
		m_JyoPad.OldButton = m_JyoPad.joykeyState.Gamepad.wButtons;                           //古いボタンの情報を設定

		m_JyoPad.joykeyState = joykeystate;                                                   //ジョイパッドのプレス情報を保存
	}
}
