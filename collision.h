//===========================================
//
//当たり判定クラス管理[collision.h]
//Auther:Chiba Haruki
//
//===========================================

#ifndef COLLISION_H_
#define COLLISION_H_

//===========================================
//インクルード
#include "main.h"
#include "input.h"


//================================================================
//当たり判定クラス
class CCollision
{
public://外部からのアクセス可能
	CCollision();
	~CCollision();
	bool ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);             //それぞれの当たり判定(プレイヤー用)
	bool ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);            //左右の当たり判定(プレイヤー用)
	bool ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move); //道のブロックの時の当たり判定

	bool AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                          //全方位の当たり判定
	bool ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);       //上の当たり判定
	bool ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move);      //下の当たり判定
	bool ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                           //真ん中から右側の判定
	bool ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                            //真ん中から左の判定

	bool CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1);                        //円の当たり判定

	//3Dポリゴンとモデルの当たり判定
	bool ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1);      //それぞれの当たり判定(プレイヤー用)
	bool ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1); //それぞれの当たり判定(プレイヤー用)
	bool ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1);  //それぞれの当たり判定(プレイヤー用)

	//fSizeXでｘ軸の増量値を渡し半径を増加させる
	bool Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float fSizeX, int nNumber); //ビーム系の当たり判定で使える
	bool Coliision3Dcircle(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float fSizeX);     //ビーム系の当たり判定で使える[
	bool TenCricale(D3DXVECTOR3& pos1, float SX, float BY, float BX, float SY); //ひし形の当たり判定（Ｓ＝small,Ｂ＝bigの略）

private:
	//マクロ定義
	static constexpr float ADJUST_DIFFERENCE_POS_X = 10.0f;  //X軸の当たり判定の大きさの調整時の差の値
	static constexpr float ADJUST_DIFFERENCE_POS_Y = 10.0f;  //Y軸の当たり判定の大きさの調整時の差の値
	static constexpr float ADJUST_DIFFERENCE_POS_Z = 10.0f;  //Z軸の当たり判定の大きさの調整時の差の値
	static constexpr float ADJUST_SEMICIRCLE = 0.5f;         //半径にする為の値
	static constexpr float ADJUST_HALF = 0.5f;               //当たり判定の倍率（半分）
};

#endif // !COLLISION_H_

