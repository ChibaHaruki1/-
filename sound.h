//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
// aaadvf
//
//=============================================================================

//=============================================================================
//
//class化に変更
//Auther:Haruki Chiba
//
//=============================================================================


#ifndef _SOUND_H_
#define _SOUND_H_


//=============================================================================
//インクルード
#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************

//サウンドクラス
class CSound
{
public:

	//音源の情報を収納
	typedef struct
	{
		const char* pFilename;	// ファイル名
		float Volume;           //音量調整
		int nCntLoop;		    // ループカウント
	} SOUNDINFO;

	enum class SOUND_LABEL
	{
		SOUND_LABEL_ITEM_GET = 0,  //アイテムを獲得
		SOUND_LABEL_BOSSBGM,	   //ボス戦用BGM
		SOUND_LABEL_NORMALBGM,	   //通常BGM
		SOUND_LABEL_SE_JUMP,	   // ジャンプ音
		SOUND_LABEL_SE_SHOT,       //撃つときの音
		SOUND_LABEL_SE_CHARGE,     //チャージ完了時の音（プレイヤーの必殺技）
		SOUND_LABEL_SE_WING,       //風の音
		SOUND_LABEL_MAX,           //音源の最大数
	};

	CSound();  //コンストラクタ
	~CSound(); //デストラクタ

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition); //チャンクのチェック関数
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset); //チャンクデータの読み込み関数

	HRESULT InitSound(HWND hWnd);           //初期化処理
	void UninitSound();                     //終了処理
	HRESULT PlaySound(SOUND_LABEL label);   //音源の再生処理
	void StopSound(SOUND_LABEL label);      //指定した音源の停止処理
	void StopSound();                       //音源の停止

private:
	IXAudio2* g_pXAudio2 = nullptr;								                    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* g_pMasteringVoice = nullptr;			                // マスターボイス
	IXAudio2SourceVoice* g_apSourceVoice[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* g_apDataAudio[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD g_aSizeAudio[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};					    // オーディオデータサイズ
};

#endif
