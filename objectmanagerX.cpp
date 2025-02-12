//=========================================
//
//全Xオブジェクトの処理[objectmanagerX.cpp] 
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//インクルード
#include "main.h"
#include "manager.h"
#include "objectmanagerX.h"
#include <ppl.h>
//#include "StepTimer.h"
#include <time.h>


//=========================================
//静的メンバーの初期化
CObjectManagerX* CObjectManagerX::m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX] = {}; //全Xオブジェクトの初期化

//using namespace cv;


//==========================
//引数付きコンストラクタ
//==========================
CObjectManagerX::CObjectManagerX(int nPriority)
{
	m_nPriority = nPriority; //プライオリティを引数と同期する
	m_type = TYPE::NONE;     //タイプ初期化する
	m_nID = N_INIT_NUMBER;   //自身のIDを初期化する

	//オブジェクト分回す
	for (int nCnt = N_INIT_NUMBER; nCnt < MAX_OBJECTMANAGERX; nCnt++)
	{
		//情報がない場合
		if (m_apObjectManagerX[m_nPriority][nCnt] == nullptr)
		{//空いている場所に自身を追加

			m_apObjectManagerX[m_nPriority][nCnt] = this; //自分自身を代入
			m_nID = nCnt;                                 //自分自身のIDを代入
			break;                                        //抜ける
		}
	}
}


//====================
//デストラクタ
//====================
CObjectManagerX::~CObjectManagerX()
{

}


//====================
//初期化処理
//====================
HRESULT CObjectManagerX::Init()
{
	return S_OK; //成功
}


//====================
//終了処理
//====================
void CObjectManagerX::Uninit()
{
	//m_nID = 0;
}


//====================
//更新処理
//====================
void CObjectManagerX::Update()
{

}


//====================
//描画処理
//====================
void CObjectManagerX::Draw()
{

}


//====================
//全オブジェクトの解放
//====================
void CObjectManagerX::ReleaseAll()
{
	//puriority分回す(平行処理)
	Concurrency::parallel_for(N_INIT_NUMBER, CObject::MAX_PRIORITY_OBJ, [&](int nCountPri)
		{
			//オブジェクト分回す
			for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECTMANAGERX; nCount++)
			{
				//情報がある場合
				if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
				{
					m_apObjectManagerX[nCountPri][nCount]->Release(); //削除処理を呼ぶ
				}
			}
		});
}


//====================
//全オブジェクトの更新
//====================
void CObjectManagerX::UpdateAll()
{
	////puriority分回す(PPLfor文) 注意点：skydoom.cppのプレイヤーと位置の同期時、平行処理にするから空がかくかくした挙動になる
	//Concurrency::parallel_for(0, CObject::MAX_PRIORITY_OBJ, [&](int nCountPri)
	//	{
	//		//オブジェクト分回す
	//		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
	//		{
	//			//情報がある場合
	//			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
	//			{
	//				m_apObjectManagerX[nCountPri][nCount]->Update(); //更新処理を呼ぶ
	//			}
	//		}
	//	});
	
	//puriority分回す
	for (int nCountPri = N_INIT_NUMBER; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//情報がある場合
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Update(); //更新処理を呼ぶ
			}
		}
	};
	 
	time_t endTime = time(NULL); //終了
}


//====================
//全オブジェクトの描画
//====================
void CObjectManagerX::DrawAll()
{
	//puriority分回す
	for (int nCountPri = N_INIT_NUMBER; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//オブジェクト分回す
		for (int nCount = N_INIT_NUMBER; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//情報がある場合
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Draw(); //描画処理を呼ぶ
			}
		}
	}
}


//=====================
//自分自身の解放
//=====================
void CObjectManagerX::Release()
{
	int nID = m_nID;             //自身のIDを代入
	int nPriority = m_nPriority; //自身のpriorityを代入

	//情報がある場合
	if (m_apObjectManagerX[nPriority][nID] != nullptr)
	{
		m_apObjectManagerX[nPriority][nID]->Uninit(); //終了処理（破棄）を呼ぶ
		delete m_apObjectManagerX[nPriority][nID];    //削除する
		m_apObjectManagerX[nPriority][nID] = nullptr; //情報を無くす
	}
}