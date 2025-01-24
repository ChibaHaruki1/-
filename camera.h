//========================================
//
//カメラクラス管理[camera.h]
//Auther:Haruki Chiba
//
//========================================

#ifndef _CAMERA_H_
#define _CAMERA_H_


//========================================
//インクルード
#include "main.h"
#include "input.h"


//==============================================================
//カメラのクラス
class CCamera
{
public:
	CCamera();                                                //コンストラクタ
	~CCamera();                                               //デストラクタ
	HRESULT Init();                                           //初期化処理
	void Uninit();                                            //破棄処理
	void Update();                                            //更新処理
	void SetCamera();                                         //カメラの情報の設定	


	//======================================
	//情報の取得
	D3DXVECTOR3& GetRot() { return m_rot; }                     //向きを取得
	int& GetAdjustmentPosZ() { return m_fAdjustmentPosZ; }    //Z軸の位置を調整値を取得
	float& GetAdjustmentPosY() { return m_fAdjustmentPosY; }  //Y軸の位置を調整値を取得


	//======================================
	//情報の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	//マクロ定義
	static constexpr float MAX_ROTSPEED = 0.01f;   //カメラの回転の速さを調整する
	static constexpr float MAX_CAMERASPEED = 1.0f; //カメラの移動の速さを調整

	D3DXVECTOR3 m_rot;                  //向き
	D3DXVECTOR3 m_fSavePosV;          //Y軸の位置を保管する用の変数
	D3DXVECTOR3 m_posV;               //視点
	D3DXVECTOR3 m_posR;               //注視点
	D3DXVECTOR3 m_vecU;               //上方向
	D3DXMATRIX m_mtxProjection;       //プロジェクション
	D3DXMATRIX m_mtxView;             //ビュー行列
	int m_fAdjustmentPosZ;            //Z軸用の位置を調整する用の変数
	float m_fAdjustmentPosY;          //Y軸用の位置を調整する用の変数
};

#endif // !_CAMERA_H_

