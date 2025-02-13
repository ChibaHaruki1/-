
//=============================================
//
//入力のクラス管理[input.h]
//Author:chiba haruki
//
//=============================================


#pragma once


//=============================================
//インクルード
#include "main.h"


//=============================================
//キーボードの大まかな処理クラス
class CInput
{
public:
	CInput();                                                    //コンストラクタ
	virtual ~CInput();                                           //デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);        //初期化処理
	virtual void Uninit();                                       //破棄処理
	virtual void Update();                                       //更新処理

	LPDIRECTINPUT8& GetInput() { return m_Input; }               //入力情報を取得
	LPDIRECTINPUTDEVICE8& GetDevice() { return m_Device; }       //デバイス情報を取得

private:
	//全入力処理で共有
	LPDIRECTINPUT8 m_Input;         //入力情報を保管する用の変数
	LPDIRECTINPUTDEVICE8 m_Device;  //デバイス情報を保管する用の変数
};


//=============================================
//キーボードのクラス
class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();                                       //コンストラクタ
	~CInputKeyBoard()override;                              //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;   //初期化処理
	void Uninit()override;                                  //破棄処理
	void Update()override;                                  //更新処理


	//==================================
	//情報の取得
	inline bool  GetKeyboardPress(int nKey) { return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false; }        //プレスの情報を取得
	inline bool GetKeyboardTrigger(int nKey) { return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false; } //トリガーの情報を取得

private:
	//マクロ定義
	 static constexpr int MAX_KEY = 256;                   //キーの最大数

	BYTE m_aKeyState[MAX_KEY];                             //キーボードの情報を格納
	BYTE m_aKeyStateTrigger[MAX_KEY];                      //キーボードトリガーの情報を格納
};


//=============================================
//ジョイパットのクラス
class CInputJoyPad
{
public:

	//キーの種類
	enum class JOYKEY
	{
		JOYKEY_UP = 0, //上キー
		JOYKEY_DOWN,   //下キー
		JOYKEY_LEFT,   //左キー
		JOYKEY_RIGHT,  //右キー
		JOYKEY_START,  //startキー
		JOYKEY_BACK,   //backキー
		JOYKEY_L3,     //L3キー
		JOYKEY_R3,     //R3キー
		JOYKEY_LB,     //LBキー
		JOYKEY_RB,     //RBキー
		JOYKEY_LT,     //LTキー
		JOYKEY_RT,     //RTキー
		JOYKEY_A,      //Aキー
		JOYKEY_B,      //Bキー
		JOYKEY_X,      //Xキー
		JOYKEY_Y,      //Yキー
		JOYKEY_MAX     //最大数
	};

	CInputJoyPad();      //コンストラクタ
	~CInputJoyPad();     //デストラクタ
	HRESULT Init(void);  //初期化処理
	void Uninit(void);   //破棄処理
	void Update(void);   //更新処理


	//==================================
	//情報の取得
	inline bool GetJoypadPress(JOYKEY key) { return (m_JyoPad.joykeyState.Gamepad.wButtons & (0x01 << (int)key)); }           //JyoPadのプレス情報を設定
	inline bool GetJoypadTrigger(JOYKEY key) { return (m_JyoPad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << (int)key)); }  //JyoPadのトリガー情報を設定

private:
	//コントローラーの構造体
	typedef struct {
		int KeyPressCount;					//キーを押してる時間のカウント
		int JoyKeyPressCount;				//キーを押してる時間のカウント
		XINPUT_STATE joykeyState;			//ジョイパッドのプレス情報
		XINPUT_STATE joykeyStateTrigger;	//ジョイパッドのトリガー情報
		int Time;							//時間を計る
		D3DXVECTOR3 joykeyStickPos;			// スティックの傾き
		XINPUT_STATE XInput;				// 入力情報
		XINPUT_STATE joykeyStateRelease;	// コントローラーのリリース情報
		XINPUT_STATE joykeyCurrentTime;		// コントローラーの現在の時間
		XINPUT_STATE joykeyExecLastTime;	// コントローラーの最後に真を返した時間
		XINPUT_STATE joykeyInput;			// コントローラーの入力情報
		XINPUT_VIBRATION joykeyMoter;		// コントローラーのモーター
		WORD Button;						//ボタンの判定
		WORD OldButton;						//古いボタンの判定

	}Joypad;

	Joypad m_JyoPad; //JoyPadの構造体の情報を格納する為の変数
};

