//================================
//
//カメラ処理[camera.cpp]
//Auther:Haruki Chiba
//
//================================


//================================
//インクルード
#include "camera.h"
#include "object.h"
#include "rendererh.h"
#include "manager.h"
#include "player.x.h"


//========================
//コンストラクタ
//========================
CCamera::CCamera()
{
	m_fAdjustmentPosY = INIT_POS_Y; //カメラの高さを調整
	m_fAdjustmentPosZ = INIT_POS_Z; //カメラを手前に引くよう調整
}


//========================
//デストラクタ
//========================
CCamera::~CCamera()
{

}


//========================
//初期化処理
//========================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(F_INIT_NUNBER, F_INIT_NUNBER, F_INIT_NUNBER);      //視点を調整
	m_posR = D3DXVECTOR3(F_INIT_NUNBER, F_INIT_NUNBER, F_INIT_NUNBER);      //注視点を調整
	m_vecU = D3DXVECTOR3(F_INIT_NUNBER, F_INIT_NUNBER_VECU_Y, F_INIT_NUNBER);      //上方向の調整
	m_rot = D3DXVECTOR3(F_INIT_NUNBER, F_INIT_NUNBER, F_INIT_NUNBER);       //向きの調整
	m_fSavePosV = m_posV;                        //視点と同期させる

	return S_OK; //成功を返す
}


//========================
//終了処理
//========================
void CCamera::Uninit()
{

}


//========================
//更新処理
//========================
void CCamera::Update()
{
	//Yキーが押された時
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Y) == true)
	{//視点が下（小さく）になる
		m_posV.y += MAX_CAMERASPEED;           //注視点のY軸を増加させる
		m_fAdjustmentPosY += MAX_CAMERASPEED;  //Y軸の調整分の値を増やす（高くなる）
	}

	//Nキーが押された時
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_N) == true)
	{//視点が上（大きく）なる
		m_posV.y -= MAX_CAMERASPEED;           //注視点のY軸を減少させる
		m_fAdjustmentPosY -= MAX_CAMERASPEED;  //Y軸の調整分の値を減少（低くなる）
	}

	//Zキーが押された
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Z) == true)
	{//視点が左に動く
		m_rot.y += MAX_ROTSPEED;
		m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y); //視点を注視点と向きと同期させる
		m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y); //視点を注視点と向きと同期させる
	}

	////Cキーが押された時
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_C) == true)
	//{//視点が右に動く
	//	rot.y -= MAX_ROTSPEED;
	//	m_posV.x = m_posR.x + sinf(D3DX_PI + rot.y) ;
	//	m_posV.z = m_posR.z + cosf(D3DX_PI + rot.y) ;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_T) == true)
	//{//注視点が下（小さく）になる
	//	m_posR.y += MAX_CAMERASPEED;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_B) == true)
	//{//注視点が上（大きく）なる
	//	m_posR.y -= MAX_CAMERASPEED;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_Q) == true)
	//{//注視点が左に向く
	//	rot.y -= MAX_ROTSPEED;
	//	m_posR.x = m_posV.x + sinf(rot.y) ;
	//	m_posR.z = m_posV.z + cosf(rot.y) ;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_E) == true)
	//{//注視点が右に向く
	//	rot.y += MAX_ROTSPEED;
	//	m_posR.x = m_posV.x + sinf(rot.y) ;
	//	m_posR.z = m_posV.z + cosf(rot.y) ;
	//}

	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_V) == true)
	//{
	//	rot = D3DXVECTOR3(F_INIT_NUNBER, F_INIT_NUNBER, F_INIT_NUNBER);
	//}


	//カメラがプレイヤーにつく処理
	m_posR.x = CManager::GetScene()->GetPlayerX()->GetPos().x;                     //注視点のＸ軸をプレイヤーのＸ軸と同期させる
	m_posR.y = CManager::GetScene()->GetPlayerX()->GetPos().y;                     //注視点のＹ軸をプレイヤーのＹ軸と同期させる
	m_posR.z = CManager::GetScene()->GetPlayerX()->GetPos().z;                     //注視点のＺ軸をプレイヤーのＺ軸と同期させる

	//カメラ自体もプレイヤーに合わせて動く(直接モデルの値を代入するとカメラ回転時強制的に正面に戻されるため）
	m_posV.x = m_posR.x + sinf(D3DX_PI + m_rot.y) * m_fAdjustmentPosZ;             //視点のＸ軸を注視点のＸ軸と向きとそれをかけた調整用の値と同期させる
	m_posV.y = CManager::GetScene()->GetPlayerX()->GetPos().y + m_fAdjustmentPosY; //視点のＹ軸をプレイヤーのＹ軸と調整用の値と同期させる
	m_posV.z = m_posR.z + cosf(D3DX_PI + m_rot.y) * m_fAdjustmentPosZ;             //視点のＺ軸を注視点のＺ軸と向きとそれをかけた調整用の値と同期させる
}


//========================
//カメラの設定（描画）
//========================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = CManager::GetRenderer();     //共通したメモリを持つインスタンスを獲得

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//通常描画処理
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(RADIAN), (float)CMain::SCREEN_WIDTH / (float)CMain::SCREEN_HEIGHT, DRAW_MIN, DRAW_MAX);

	//平行投影
	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)CMain::SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 10.0f, 2000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}