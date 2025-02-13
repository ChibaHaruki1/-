//======================================
//
//主要情報を管理するクラス[manager.h]
//Auther:Chiba Hruki
//
//======================================


#pragma once


//======================================
//インクルード
#include "main.h"
#include "rendererh.h"
#include "input.h"
#include "block.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "instance.h"
#include "scene.h"
#include "object_set.h"
#include "event.h"


class CManager
{
public:
	CManager();                                                  //コンストラクタ
	~CManager();                                                 //デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //初期化処理
	void Uninit();                                               //終了処理
	void Update();                                               //更新処理
	void Draw();                                                 //描画処理


	//==================================
	//情報を取得
	inline static CRenderer* GetRenderer() { return m_pRenderer; }      //レンダラーの情報を取得
	inline static CInputKeyBoard* GetKeyBorad() { return m_pKeyBoard; } //キーボードの情報を取得
	inline static CInputJoyPad* GetJyoPad() { return m_pJyoPad; }       //ジョイパットの情報を取得
	inline static CSound* GetSound() { return m_pSound; }               //音源の情報を取得
	inline static CInstance* GetInstance() { return m_pInstance; }      //インスタンス情報を取得する
	inline static CScene* GetScene() { return m_pScene; }               //シーンの情報を取得
	inline static CObjectSet* GetObjectSet() { return m_pObjectSet; }   //オブジェクト配置の情報を取得
	inline static CEvent* GetEvent() { return m_pEvent; }               //イベントの情報を取得
	inline static CMain* GetMain() { return m_pMain; }                  //メインの情報を取得


   //==================================
   //情報の設定
	static void SetMode(CScene::MODE mode);                      //モードの設定


private:
	static CRenderer* m_pRenderer;                               //レンダラーのポインター
	static CInputKeyBoard* m_pKeyBoard;                          //キーボードのポインター
	static CInputJoyPad* m_pJyoPad;                              //ジョイパットのポインター
	static CSound* m_pSound;                                     //音源のポインター
	static CScene* m_pScene;                                     //現在のシーンのポインター
	static CInstance* m_pInstance;                               //各クラスのポインター
	static CObjectSet* m_pObjectSet;                             //オブジェクト配置のポインター
	static CEvent* m_pEvent;                                     //ステージ毎のイベントポインター
	static CMain* m_pMain;                                       //メインのポインター
};
