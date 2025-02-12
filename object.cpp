//=========================================
//
//全オブジェクトの処理[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//インクルード
#include "main.h"
#include "object.h"
#include "object3D.h"
#include "manager.h"


//静的メンバーの初期化
CObject* CObject::m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT] = {}; //全オブジェクトの初期化


//==========================
//引数付きコンストラクタ
//==========================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority; //プライオリティを引数と同期する
	m_type = TYPE::NONE;     //タイプを初期化する
	m_nID = N_INIT_NUMBER;   //自身のIDを初期化する

	//オブジェクト分回す
	for (int nCnt = N_INIT_NUMBER; nCnt < MAX_OBJECT; nCnt++)
	{
		//情報がない場合
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{//空いている場所に自身を追加

			m_apObject[m_nPriority][nCnt] = this; //自分自身を代入
			m_nID = nCnt;                         //自分自身のIDを代入
			break;                                //抜ける
		}
	}
}


//====================
//デストラクタ
//====================
CObject::~CObject()
{

}


//====================
//初期化処理
//====================
HRESULT CObject::Init()
{
	return S_OK; //成功
}


//====================
//終了処理
//====================
void CObject::Uninit()
{

}


//====================
//更新処理
//====================
void CObject::Update()
{

}


//====================
//描画処理
//====================
void CObject::Draw()
{

}


//====================
//全オブジェクトの解放
//====================
void CObject::ReleaseAll()
{
	//puriority分回す
	for (int nCountPri = N_INIT_NUMBER; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Release(); //削除処理を呼ぶ
			}
		}
	}
}


//====================
//全オブジェクトの更新
//====================
void CObject::UpdateAll()
{
	//puriority分回す
	for (int nCountPri = N_INIT_NUMBER; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Update(); //更新処理を呼ぶ
			}
		}
	}

}


//====================
//全オブジェクトの描画
//====================
void CObject::DrawAll()
{
	//puriority分回す
	for (int nCountPri = N_INIT_NUMBER; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECT; nCount++)
		{
			//情報がある場合
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Draw(); //描画処理を呼ぶ
			}
		}
	}
}


//=====================
//自分自身の解放
//=====================
void CObject::Release()
{
	int nID = m_nID;             //自身のIDを代入
	int nPriority = m_nPriority; //自身のpriorityを代入

	//情報がある場合
	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit(); //終了処理（破棄）を呼ぶ
		delete m_apObject[nPriority][nID];    //削除する
		m_apObject[nPriority][nID] = nullptr; //情報を無くす
	}
}