//===================================
//
//地面の設定をする処理[field.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "main.h"
#include "field.h"
#include "rendererh.h"
#include "manager.h"
#include <iostream>
#include <cstdio>


//===================================
//ネームスペースの宣言
using namespace std; //c++の基礎の省略


//===================================
//文字列の設定
string u8FieldText = u8"地面の情報設定";   //日本語対応


//===================================
//static変数の初期化
int CField::m_nCountField = CObject3D::N_INIT_NUMBER; //作られた地面の初期化


//============================
//コンストラクタ
//============================
CField::CField(int nPriority) : CObject3D(nPriority)
{
	SetSizeX(SIZEX);                             //ｘ軸の大きさを設定
	SetFileNamePass("data\\TEXTURE\\bg101.jpg"); //ファイルパスを設定
}


//============================
//デストラクタ
//============================
CField::~CField()
{

}


//============================
//初期化処理
//============================
HRESULT CField::Init()
{
	//初期化が成功した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//==========================
//終了処理
//==========================
void CField::Uninit()
{
	CObject3D::Uninit(); //破棄処理を呼ぶ
}

//========================
//更新処理
//========================
void CField::Update()
{
	SetSize(GetSizeX(), CObject3D::F_INIT_NUMBER, GetSizeX()); //大きさの設定

	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_1) == true)
	//{
	//	m_fSizeX += 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_2) == true)
	//{
	//	m_fSizeX -= 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_O) == true)
	//{
	//	//TextFileWrite();
	//}
}


//======================================
//テキストファイルに書き込む処理
//======================================
void CField::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ)
{
	FILE* m_pFile;                                       //ファイルポインター
	m_pFile = fopen("data\\TEXT\\ResultScore.txt", "a"); //ファイルを読み込む

	//ファイルの情報が無かった時
	if (m_pFile == nullptr)
	{
		return; //処理を抜ける
	}

	m_nCountField++;                                                    //作られた数を増やす
	fprintf(m_pFile, "%s", "\n\n");                                     //改行
	fprintf(m_pFile, "%s", "#=====================================\n"); //文字を書き込む
	fprintf(m_pFile, "%s", "#");                                        //文字を書き込む
	fprintf(m_pFile, "%d", m_nCountField);                              //数字を書き込む
	fprintf(m_pFile, "%s", u8FieldText.data());                         //文字を書き込む(全角文字)
	fprintf(m_pFile, "%s", "\n");                                       //改行を行う
	fprintf(m_pFile, "%s", "#=====================================\n"); //数字を書き込む
	fprintf(m_pFile, "%s", "FILED\n");                                  //文字を書き込む
	fprintf(m_pFile, "%s", "		POS = ");                           //「POS」の文字を書き込む
	fprintf(m_pFile, "%.1f ", m_fPosX);                                 //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%.1f ", m_fPosY);                                 //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%.1f ", m_fPosZ);                                 //「位置」の文字を書き込む(少数点第１まで)
	fprintf(m_pFile, "%s", "\n");                                       //改行を行う
	fprintf(m_pFile, "%s", "END_FILED\n");                              //文字を書き込む
	fclose(m_pFile);                                                    //ファイルを閉じる
}


//======================
//描画処理
//======================
void CField::Draw()
{
	CObject3D::Draw(); //基底クラスの描画処理を呼ぶ
}


//========================
//床を生成
//========================
CField* CField::Create(D3DXVECTOR3 pos)
{
	CField* pCField = new CField(CREATE_PRIORITY); //動的確保

    //初期化が成功した時
	if (SUCCEEDED(pCField->Init()))
	{
		pCField->SetPos(pos); //位置を引数と同期させる
		pCField->Lood();      //テクスチャの読み込み
		return pCField;       //情報を返す
	}

	return nullptr;               //無を返す
}