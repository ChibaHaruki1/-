//===================================
//
//２ｄのＵＩの処理設定[2d_ui.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//インクルード
#include "2d_ui.h"
#include "rendererh.h"
#include "manager.h"


//=============================================================================================================================
//２DUIのマネージャー管理クラスの処理
//=============================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CManager2DUI::CManager2DUI(int nPriority) : CObject2D(nPriority)
{
	
}

//==========================
//デストラクタ
//==========================
CManager2DUI::~CManager2DUI()
{

}

//======================
//初期化処理
//======================
HRESULT CManager2DUI::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}


//======================
//終了処理
//======================
void CManager2DUI::Uninit()
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}


//=======================
//更新処理
//=======================
void CManager2DUI::Update()
{

}

//=====================
//描画処理
//=====================
void CManager2DUI::Draw()
{
	CObject2D::Draw(); //描画処理を呼ぶ
}

//=====================
//生成処理
//=====================
CManager2DUI* CManager2DUI::Create(TYPE_UI TypeUI)
{
	CManager2DUI* pManager2DUI = nullptr; //基底クラスのポインター

	//タイプが店のメニューの時
	if (TypeUI== TYPE_UI::SHOPMENU)
	{
		pManager2DUI = new CShopMenu(CObject2D::INIT_PRIORITY); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pManager2DUI->Init()))
		{
			pManager2DUI->Lood(); //テクスチャの読み込み
			return pManager2DUI;  //情報を返す
		}
	}

	return nullptr;               //無を返す
}

//==============================================
//現在作られているオブジェクトUIの生成処理
//==============================================
CManager2DUI* CManager2DUI::NowCreate(int nNumber)
{
	CManager2DUI* pManager2DUI = new CNowCreateUI(); //動的確保

	//初期化に成功した時
	if (SUCCEEDED(pManager2DUI->Init()))
	{
		//番号が０番の時
		if (nNumber == CRETAE_NUMBER_0)
		{
			pManager2DUI->SetFileNamePass("data\\TEXTURE\\StageObj\\SHOP.png");    //ファイルパスを設定
		}

		//番号が１番の時
		else if (nNumber == CRETAE_NUMBER_1)
		{
			pManager2DUI->SetFileNamePass("data\\TEXTURE\\StageObj\\images.jpg");  //ファイルパスを設定
		}

		pManager2DUI->Lood(); //テクスチャの読み込み
		return pManager2DUI;  //情報を返す
	}

	return nullptr;           //無を返す
}



//=============================================================================================================================
//今作ろうとしている物のUI表示の処理
//=============================================================================================================================

//==========================
//引数付きコンストラクタ
//==========================
CNowCreateUI::CNowCreateUI(int nPriority) : CManager2DUI(nPriority)
{
	
}


//======================
//コンストラクタ
//======================
CNowCreateUI::~CNowCreateUI()
{

}


//======================
//初期化処理
//======================
HRESULT CNowCreateUI::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject2D::F_INIT_NUMBER, SIZEX, CObject2D::F_INIT_NUMBER, SIZEY); //サイズの設定

	return S_OK; //成功を返す
}


//===========================================================================================================================================================
//メニューUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CShopMenu::CShopMenu(int nPriority) : CManager2DUI(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\Menyu001.png"); //ファイルパスの設定
}


//=======================
//デストラクタ
//=======================
CShopMenu::~CShopMenu()
{

}


//=======================
//初期化処理
//=======================
HRESULT CShopMenu::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject2D::F_INIT_NUMBER, SIZEX, CObject2D::F_INIT_NUMBER, SIZEY); //サイズの取得

	return S_OK; //成功を返す
}


//===========================================================================================================================================================
//メニューUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CBuyText::CBuyText(int nPriority) : CManager2DUI(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\buy001.png"); //ファイルパスを設定
}


//=======================
//デストラクタ
//=======================
CBuyText::~CBuyText()
{

}


//=======================
//初期化処理
//=======================
HRESULT CBuyText::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject2D::F_INIT_NUMBER, SIZEX, CObject2D::F_INIT_NUMBER, CMain::SCREEN_HEIGHT);  //サイズの設定
	SetCol(CObject2D::RED, CObject2D::GREEN, CObject2D::BLUE, ALPHA);                                     //色の設定

	return S_OK; //成功を返す
}

//========================
//生成処理
//========================
CBuyText* CBuyText::Create()
{
	CBuyText* pText = new CBuyText(CObject2D::INIT_PRIORITY); //動的確保

	//情報がある時
	if (pText != nullptr)
	{
		//初期化が成功した時
		if (SUCCEEDED(pText->Init()))
		{
			pText->Lood(); //テクスチャの読み込み
			return pText;  //情報を返す
		}
	}

	return nullptr;        //無を返す
}


//===========================================================================================================================================================
//選択時のUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CSelectGage::CSelectGage(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage.png"); //ファイルパスを設定
	m_fSizeX = CObject2D::F_INIT_NUMBER;                                   //１番目のサイズのX軸の初期化
	m_fSize1X = SIZE1X;                                         //２番目のサイズのX軸の初期化
	m_fSizeY = SIZEY;                                           //１番目のサイズのY軸の初期化
	m_fSize1Y = SIZE1Y;                                         //２番目のサイズのY軸の初期化
}


//=======================
//デストラクタ
//=======================
CSelectGage::~CSelectGage()
{

}


//=======================
//初期化処理
//=======================
HRESULT CSelectGage::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject2D::F_INIT_NUMBER, m_fSizeX, CObject2D::F_INIT_NUMBER,m_fSizeY); //サイズの設定
	SetCol(CObject2D::RED, CObject2D::GREEN, CObject2D::BLUE, ALPHA);                          //色の設定

	return S_OK; //成功を返す
}


//========================
//破棄処理
//========================
void CSelectGage::Uninit()
{
	CObject2D::Uninit(); //破棄処理を呼ぶ
}


//========================
//更新処理
//========================
void CSelectGage::Update()
{
	CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y); //サイズの更新
}

//========================
//描画処理
//========================
void CSelectGage::Draw()
{
	CObject2D::Draw(); //描画処理
}


//========================
//生成処理
//========================
CSelectGage* CSelectGage::Create()
{
	CSelectGage* pSelectGage = new CSelectGage(); //動的確保

	//情報がある時
	if (pSelectGage != nullptr)
	{
		//初期化に成功した時
		if (SUCCEEDED(pSelectGage->Init()))
		{
			pSelectGage->Lood(); //ｘファイルの読み込み
			return pSelectGage;  //情報を返す
		}
	}

	return nullptr;              //無を返す
}


//===========================================================================================================================================================
//選択時のUIの処理
//===========================================================================================================================================================

//=======================
//コンストラク
//=======================
CSelectGage001::CSelectGage001(int nPriority) : CSelectGage(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage001.png"); //ファイルパスを設定

}


//=======================
//デストラクタ
//=======================
CSelectGage001::~CSelectGage001()
{

}


//=======================
//初期化処理
//=======================
HRESULT CSelectGage001::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	CObject2D::SetSIze(CObject2D::F_INIT_NUMBER, GetSizeX(), CObject2D::F_INIT_NUMBER, GetSizeY()); //サイズの設定

	return S_OK; //成功を返す
}

//========================
//更新処理
//========================
void CSelectGage001::Update()
{
	
}

//========================
//生成処理
//========================
CSelectGage001* CSelectGage001::Create()
{
	CSelectGage001* pSelectGage = new CSelectGage001(); //動的確保

    //初期化が成功した時
	if (SUCCEEDED(pSelectGage->Init()))
	{
		pSelectGage->Lood(); //ｘファイルを読み込み
		return pSelectGage;  //情報を返す
	}

	return nullptr;              //無を返す
}