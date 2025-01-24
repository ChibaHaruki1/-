//==========================================
//
//ボス用エフェクトの処理[bossefect.cpp]
//Auther:Chiba Haruki
//
//==========================================


//==========================================
//インクルード
#include "main.h"
#include "rendererh.h"
#include "bosseffect.h"
#include "manager.h"


//==================================================================================
//演出用エフェクトのストラテジークラス基底処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CBossEffectDirection::CBossEffectDirection()
{
	m_aEffectFileName = nullptr; //ファイルパスの初期化
	m_nLife = 0;                 //ライフの初期化
	m_pVtxBuffMine = nullptr;    //バッファの初期化
}

//==========================================
//デストラクタ
//==========================================
CBossEffectDirection::~CBossEffectDirection()
{

}

//==================================================================================
//テクスチャの設定処理
//==================================================================================
void CBossEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	VERTEX_3D* pVtx; //バーテクスのポインター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexSize, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================================================================================
//テクスチャの更新処理
//==================================================================================
void CBossEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount ,float fMaxTex)
{
	m_nLife++;  //カウントする

	//ライフが既定の数値以上になった時
	if (m_nLife >= CManagerBossEffect::MAX_BOSSANIMATION_LIFE * dLifeCount)
	{
		VERTEX_3D* pVtx; //バーテクスのポインター

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0U, 0U, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex.x = pVtx[0].tex.x + fMaxTex;
		pVtx[1].tex.x = pVtx[1].tex.x + fMaxTex;
		pVtx[2].tex.x = pVtx[2].tex.x + fMaxTex;
		pVtx[3].tex.x = pVtx[3].tex.x + fMaxTex;

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();

		m_nLife = 0; //ライフを初期化する
	}
}


//==================================================================================
//演出用エフェクトのストラテジークラスの継承処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CAttackEffect::CAttackEffect()
{
	SetFileNamePass("data\\TEXTURE\\UI\\Impact.png"); //ファイルパスを設定
}

//==========================================
//デストラクタ
//==========================================
CAttackEffect::~CAttackEffect()
{

}


//==================================================================================
//必殺技のストラテジークラスの継承処理
//==================================================================================

//==========================================
//コンストラクタ
//==========================================
CSourceSpecialAttackBoss::CSourceSpecialAttackBoss()
{
	SetFileNamePass("data\\TEXTURE\\UI\\SpecialGage\\BossSpecialAllGage002.png"); //ファイルパスを設定
}

//==========================================
//デストラクタ
//==========================================
CSourceSpecialAttackBoss::~CSourceSpecialAttackBoss()
{

}


//=======================================================================================================================================================================
//エフェクトの管理者処理
//=======================================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CManagerBossEffect::CManagerBossEffect(int nPriority) : CObject3D(nPriority)
{               
	m_pEffectDirection000 = nullptr;  //ストラテジー基底クラスのポインターの初期化
	m_nBossRotNumber = 0;             //向きで大きさを判定する変数の初期化(必殺技)
	m_nHitNumber = -1;                //当たった方向を番号で判定する変数の初期化(衝撃波)
	m_dLifeCount = 0.0;               //アニメーションの速度の初期化
}


//===========================
//デストラクタ
//===========================
CManagerBossEffect::~CManagerBossEffect()
{
	//基底クラスのポインターの情報がある時
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;     //情報を消す
		m_pEffectDirection000 = nullptr;  //情報を無くす
	}
}


//============================
//初期化処理
//============================
HRESULT CManagerBossEffect::Init()
{
	//初期化が失敗した時
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //失敗を返す
	}

	SetSizeX(MAX_SIZEX);                         //ｘ軸の大きさの設定
	SetSizeY(MAX_SIZEY);                         //ｙ軸の大きさの設定
	SetSize(GetSizeX(), GetSizeY(), MAX_SIZEZ);  //大きさの設定
	return S_OK;                                 //成功を返す
}


//============================
//初期化処理
//============================
void CManagerBossEffect::Uninit()
{
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}


//============================
//初期化処理
//============================
void CManagerBossEffect::Update()
{
	//m_pEffectDirection000->Effect(m_pTexture, m_pVtxBuff, m_dLifeCount, fMaxTex);
	//m_nLife--;                           //ライフを減らす

	//SetCol(255, 255, 255, m_nAlpha);     //色の設定

	////ライフが尽きた時
	//if (m_nLife <= 0)
	//{
	//	CManager::GetInstance()->DesignationUninit3D(IMPACT);
	//	CObject3D::Release();
	//	return;
	//}

	//CObject3D::Update();
}

//============================
//初期化処理
//============================
void CManagerBossEffect::Draw()
{
	CObject3D::DrawEffect(); //描画処理を呼ぶ
}


//============================
//エフェクトの設定
//============================
void CManagerBossEffect::SetEffect(D3DXVECTOR3 pos)
{
	SetPos(pos); //位置を引数と同期
}


//===========================
//エフェクトの生成
//===========================
CManagerBossEffect* CManagerBossEffect::Create(D3DXVECTOR3 pos, CObject3D::TYPE type)
{
	CManagerBossEffect* pEffect = nullptr; //基底クラスのポインター


	//タイプが衝撃波の時
	if (type == CObject3D::TYPE::IMPACT)
	{
		pEffect = new CImpact(); //動的確保

		//初期化に成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CAttackEffect();                                   //ストラテジー継承クラスの動的確保
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), MAX_IMPACT_TEXTURESIZE);  //テクスチャの設定
			pEffect->SetLife(CImpact::MAX_IMPACT_LIFE);                                             //ライフの設定
		}
	}

	//タイプが必殺技の時
	else if (type == CObject3D::TYPE::BOSSSPECIALATTACK)
	{
		pEffect = new CBossSpecialAttack(); //動的確保

		//初期化に成功したとき
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttackBoss();                                                   //ストラテジー継承クラスの動的確保
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), MAX_BOSSANIMETION_TEX);                              //テクスチャの設定
			pEffect->SetSize(CBossSpecialAttack::MAX_SPECIALATTACK_SIZEX, CBossSpecialAttack::MAX_SPECIALATTACK_SIZEX, 0.0f);  //大きさの設定
			pEffect->SetLife(CBossSpecialAttack::MAX_BOSSSPZECIALATTACK_LIFE);                                                 //ライフの設定
		}
	}
	
	//情報がある時
	if (pEffect != nullptr)
	{
		pEffect->SetFileNamePass(pEffect->m_pEffectDirection000->GetFileNamePass()); //ファイルパスを設定
		pEffect->SetPos(pos);                                                        //位置を引数と同期
		pEffect->Lood();                                                             //テクスチャの読み込み
		return pEffect;                                                              //情報を返す
	}

	return nullptr;                                                                  //無を返す
}


//=======================================================================================================================================================
//衝撃波のエフェクトの処理
//=======================================================================================================================================================

//============================
//コンストラクタ
//============================
CImpact::CImpact()
{
	
}

//============================
//デストラクタ
//============================
CImpact::~CImpact()
{

}

//============================
//更新処理
//============================
void CImpact::Update()
{
	SetAddjustLife()--;                                 //ライフを減らす
	SetAddjustSizeX() += PLUS_SIZEX;                    //ｘ軸のサイズを大きくする
	SetAddjustSizeY() += PLUS_SIZEY;                    //ｙ軸のサイズを大きくする

	SetCol(RED, GREEN, BLUE, GetAlpha());               //色の設定
	SetSize(GetSizeX(), GetSizeY(), MAX_SIZEZ);         //大きさの更新

	//右側に当たった時
	if (CObject3D::CollisionPrts1Right(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		SetHitNumber(0); //当たった方向の番号を設定
	}

	//左側に当たった時
	else if (CObject3D::CollisionPrts1Left(GetSizeX() * 1.5f, GetSizeY() * 1.1f, 40.0f) == true)
	{
		SetHitNumber(1); //当たった方向の番号を設定
	}

	//ライフが尽きた時
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->DesignationUninit3D(TYPE::IMPACT); //インスタンスのポインターの情報を無くす
		CObject3D::Release();                                       //自身を破棄する
		return;                                                     //処理を抜ける
	}

	CObject3D::Update();                                            //更新処理を呼ぶ
}


//=======================================================================================================================================================
//必殺技のエフェクトの処理
//=======================================================================================================================================================

//============================
//コンストラクタ
//============================
CBossSpecialAttack::CBossSpecialAttack()
{
	
}

//============================
//デストラクタ
//============================
CBossSpecialAttack::~CBossSpecialAttack()
{

}

//============================
//更新処理
//============================
void CBossSpecialAttack::Update()
{
	this->GetBossEffectDirection()->Effect(GetTexture(), GetBuffer(), ANIMETION_DLLIFE, MAX_BOSSANIMETION_TEX); //テクスチャのサイズの更新

	SetCol(RED, GREEN, BLUE, GetAlpha());          //色の設定

	//サイズが規定値より小さい時
	if (GetSizeX() <= MAXIMUM_SIZEX)
	{
		SetAddjustSizeX() += PLUS_SIZEX;           //サイズを大きくする
	}

	float fPosY = GetPos().y - CManager::GetInstance()->GetBoss()->GetPosPrtsBoss(17).y * ADJUST_PLAYER_POSY; //プレイヤーのpos.yを計算+調整=当たり判定の一番下を設定

	//向き番号が１の時
	if (GetRotNumber() == 1)
	{
		SetEffectSize(GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);    //サイズの設定

		//点BXがプレイヤーより大きい判定にしたいからサイズの更新処理を入れる
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), GetPos().x, GetPos().y + PLUS_POS_Y,
			GetSizeX()*ADJUST_SIZE_X + GetPos().x, fPosY) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE; //プレイヤーのHPゲージを減らす
		}
	}

	//向き番号が２の時
	else if (GetRotNumber() == 2)
	{
		SetEffectSize(-GetSizeX(), MAX_BOSSSPECIALATTACK_Y, 0.0f);   //サイズの設定

		//点SXがプレイヤーより小さい判定にしたいからサイズの更新処理を入れる
		if (CManager::GetScene()->GetPlayerX()->GetCollision()->TenCricale(CManager::GetScene()->GetPlayerX()->GetPos(), -GetSizeX()* ADJUST_SIZE_X + GetPos().x, GetPos().y + PLUS_POS_Y,
			GetPos().x, fPosY) == true)
		{
			CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * MAX_DAMAGE; //プレイヤーのHPゲージを減らす
		}
	}

	//ライフが０以下の時
	if (GetLife() <= 0)
	{
		SetAddjustAlpha() -= MINUS_ALPHA;          //alpha値を減らす
		//アルファ値が０以下の時
		if (GetAlpha() <= 0)
		{
			CObject::Release();                    //自身を削除
			return;                                //処理を抜ける
		}					                       
	}						                       
	else					                       
	{						                       
		SetAddjustLife()--;                        //ライフを減らす
	}
}