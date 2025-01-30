//===========================================
//
//当たり判定処理[collision.cpp]
//Auther:Haruki Chiba
//
//===========================================


//===========================================
//インクルード
#include "collision.h"
#include "manager.h"
#include "player.x.h"


//============================
//コンストラクタ
//============================
CCollision::CCollision()
{

}


//===========================
//デストラクタ
//===========================
CCollision::~CCollision()
{

}


//======================
//各方向の判定
//======================
bool CCollision::ColiisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//右の当たり判定
	if (pos.x - (Size.x *ADJUST_HALF) >= pos1.x + (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		move.x = move.x + CPlayerX::MAX_MOVESPEED; //右側に押す
		return true; //当たっている判定を返す
	}

	//左の当たり判定
	else if (pos.x + (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x + (Size.x *ADJUST_HALF) <= pos1.x - (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		move.x = move.x - CPlayerX::MAX_MOVESPEED; //左側に押す
		return true; //当たっている判定を返す
	}

	//手前からの判定
	else  if (pos.x + (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF <= pos1.z - (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z)
	{
		move.z = move.z - CPlayerX::MAX_MOVESPEED; //手前に押す
		return true; //当たっている判定を返す
	}

	//後ろからの判定
	else  if (pos.x + (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z
		&& pos.z - Size.z *ADJUST_HALF >= pos1.z + (Size1.z *ADJUST_HALF))
	{
		move.z = move.z + CPlayerX::MAX_MOVESPEED; //奥に押す
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//==============================
//左右のみの判定(押し出し無し)
//==============================
bool CCollision::ColiisionBox1(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//右の当たり判定
	if (pos.x - (Size.x *ADJUST_HALF) >= pos1.x + (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		return true; //当たっている判定を返す
	}

	//左の当たり判定
	else if (pos.x + (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x + (Size.x *ADJUST_HALF) <= pos1.x - (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//==============================
//左右のみの判定(押し出し有り)
//==============================
bool CCollision::ColiisionBoxRoadBlock001(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{

	//右の当たり判定
	if (pos.x - (Size.x *ADJUST_HALF) >= pos1.x + (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		move.x = move.x + CPlayerX::MAX_MOVESPEED; //右側に押す
		return true; //当たっている判定を返す
	}

	//左の当たり判定
	else if (pos.x + (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x + (Size.x *ADJUST_HALF) <= pos1.x - (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + Size.z *ADJUST_HALF >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - Size.z *ADJUST_HALF <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		move.x = move.x - CPlayerX::MAX_MOVESPEED; //左側に押す
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//======================
//全方位の判定
//======================
bool CCollision::AnyColiisionBoxAll(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	if (pos.x + (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.y + (Size.y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Size.y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Y
		&& pos.z + (Size.z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Z
		&& pos.z - (Size.z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z)
	{
		return true; //当たっている判定を返す
	}

	return false; //当たっていない判定を返す
}

//==========================================================================================================
//真ん中から右側の判定
//==========================================================================================================
bool CCollision::ColiisionBoxRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//真ん中から右半分の当たり判定（高さ無し）
	if (pos.x <=pos1.x + (Size1.x *ADJUST_HALF) 
		&& pos.x + (Size.x *ADJUST_HALF)>=pos1.x + (Size1.x *ADJUST_HALF))
		
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}

//==========================================================================================================
//真ん中から左方向の判定
//==========================================================================================================
bool CCollision::ColiisionBoxLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1)
{
	//真ん中から左半分の当たり判定（高さ無し）
	if (pos.x >= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.x - (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF))

	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//==================
//上側の判定
//==================
bool CCollision::ColiisionBoxInside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//上側の判定
	if (pos.x + (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.y >= pos1.y
		&& pos.y <= pos1.y + (Size1.y)
		&& pos.z + (Size.z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z
		&& pos.z - (Size.z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Z)
	{
		return true;  //当たっている判定を返す
	}
	return false;     //当たっていない判定を返す
}


//==================
//下側の判定
//==================
bool CCollision::ColiisionBoxOutside(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1, D3DXVECTOR3& move) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//下側の判定
	if (pos.x + (Size.x *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.x - (Size.x *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.y <= pos1.y
		&& pos.y >= pos1.y - (Size1.y* ADJUST_HALF)
		&& pos.z + (Size.z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z
		&& pos.z - (Size.z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Z)
	{
		move.y -= CPlayerX::MAX_MOVESPEED * 2.0f; //下側に戻す
		return true; //当たっている判定を返す
	}
	return false;    //当たっていない判定を返す
}


//====================
//円の当たり判定
//====================
bool CCollision::CircleCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, D3DXVECTOR3 Size, D3DXVECTOR3 Size1) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSum = (Size.x * ADJUST_SEMICIRCLE + Size.y * ADJUST_SEMICIRCLE + Size.z * ADJUST_SEMICIRCLE)* ADJUST_SEMICIRCLE;      //１つ目の半径
	float radiuSum1 = (Size1.x * ADJUST_SEMICIRCLE + Size1.y * ADJUST_SEMICIRCLE + Size1.z * ADJUST_SEMICIRCLE)* ADJUST_SEMICIRCLE;  //２つ目の半径

	//距離が対象の半径より小さい（触れている）時
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//==============================================================================================================================
//３ｄポリゴンとモデルの判定
//==============================================================================================================================

//======================
//全方向の判定
//======================
bool CCollision::ColiisionBox3D(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	if (pos.x - (X *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.x + (X *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.y + (Y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Y
		&& pos.z + (Z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Z
		&& pos.z - (Z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_Z)
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//======================
//右方向の判定
//======================
bool CCollision::ColiisionBox3DRight(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	//右側の当たり判定を増やす
	if (pos.x + (X *ADJUST_HALF) >= pos1.x - (Size1.x *ADJUST_HALF)
		&& pos.x + (X *ADJUST_HALF) <= pos1.x - (Size1.x *ADJUST_HALF) + ADJUST_DIFFERENCE_POS_X
		&& pos.y + (Y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + (Z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF) 
		&& pos.z - (Z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっている判定を返す
}


//======================
//左方向の判定
//======================
bool CCollision::ColiisionBox3DLeft(D3DXVECTOR3 pos, D3DXVECTOR3 pos1, float X, float Y, float Z, D3DXVECTOR3 Size1)
{
	//右側の当たり判定を増やす
	if (pos.x - (X *ADJUST_HALF) >= pos1.x + (Size1.x *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_X
		&& pos.x - (X *ADJUST_HALF) <= pos1.x + (Size1.x *ADJUST_HALF)
		&& pos.y + (Y *ADJUST_HALF) >= pos1.y - (Size1.y *ADJUST_HALF) - ADJUST_DIFFERENCE_POS_Y
		&& pos.y - (Y *ADJUST_HALF) <= pos1.y + (Size1.y *ADJUST_HALF)
		&& pos.z + (Z *ADJUST_HALF) >= pos1.z - (Size1.z *ADJUST_HALF)
		&& pos.z - (Z *ADJUST_HALF) <= pos1.z + (Size1.z *ADJUST_HALF))
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//=========================
//ボスの円の当たり判定
//=========================
bool CCollision::Coliision3DcircleBoss(D3DXVECTOR3 pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX, int nNumber) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z + CManager::GetInstance()->GetBoss()->GetModelPrtasBoss(nNumber)->GetPos().z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSum = (X * ADJUST_SEMICIRCLE + m_fSizeX + Y * ADJUST_SEMICIRCLE + Z * ADJUST_SEMICIRCLE) * ADJUST_SEMICIRCLE;          //１つ目の半径
	float radiuSum1 = (Size1.x * ADJUST_SEMICIRCLE + Size1.y * ADJUST_SEMICIRCLE + Size1.z * ADJUST_SEMICIRCLE) * ADJUST_SEMICIRCLE;  //２つ目の半径

	//距離が対象の半径より小さい（触れている）時
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//====================
//円の当たり判定
//====================
bool CCollision::Coliision3Dcircle(D3DXVECTOR3& pos, D3DXVECTOR3& pos1, float X, float Y, float Z, D3DXVECTOR3 Size1, float m_fSizeX) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	float lengthX = pos.x - pos1.x; //posとpos1のｘの距離を常に比較
	float lengthY = pos.y - pos1.y; //posとpos1のｙの距離を常に比較
	float lengthZ = pos.z - pos1.z; //posとpos1のｚの距離を常に比較

	float CenterDistance = sqrtf(lengthX * lengthX + lengthY * lengthY + lengthZ * lengthZ);//posとpos1の距離を計算

	float radiuSum = (X * ADJUST_SEMICIRCLE + m_fSizeX + Y * ADJUST_SEMICIRCLE + Z * ADJUST_SEMICIRCLE) * ADJUST_SEMICIRCLE;          //１つ目の半径
	float radiuSum1 = (Size1.x * ADJUST_SEMICIRCLE + Size1.y * ADJUST_SEMICIRCLE + Size1.z * ADJUST_SEMICIRCLE) * ADJUST_SEMICIRCLE;  //２つ目の半径

	//距離が対象の半径より小さい（触れている）時
	if (CenterDistance <= radiuSum + radiuSum1)
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}


//=========================
//円の当たり判定(自作)
//=========================
bool CCollision::TenCricale(D3DXVECTOR3& pos1, float SX, float BY, float BX, float SY) //参照渡しだが変える値のみ参照しないとstaicと同じになる
{
	//ひし形（◇）状の当たり判定の条件式
	if (SX <= pos1.x && BY >= pos1.y && BX >= pos1.x && SY <= pos1.y)
	{
		return true; //当たっている判定を返す
	}

	return false;    //当たっていない判定を返す
}
