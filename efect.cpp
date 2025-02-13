//===================================
//
//エフェクトの処理[efect.cpp]
//Auther:Chiba Haruki
//
//===================================


//===================================
//インクルード
#include "main.h"
#include "rendererh.h"
#include "efect.h"
#include "manager.h"


//==================================================================================
//演出用エフェクトのストラテジークラス基底処理
//==================================================================================

//========================
//コンストラクタ
//========================
CEffectDirection::CEffectDirection()
{
	m_aEffectFileName = nullptr;  //ファイルパスの初期化
	m_nLife = INIT_LIFE;          //ライフの初期化
	m_pVtxBuffMine = nullptr;     //バッファの初期化
}

//========================
//デストラクタ
//========================
CEffectDirection::~CEffectDirection()
{

}

//==================================================================================
//テクスチャの設定処理
//==================================================================================
void CEffectDirection::SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize)
{
	CMain::VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(BUFFNUMBE, BUFFNUMBE, (void**)&pVtx, CObject3D::N_INIT_NUMBER);

	//テクスチャ座標の設定
	pVtx[TexNumber_0].tex = D3DXVECTOR2(CObject3D::F_INIT_NUMBER, CObject3D::F_INIT_NUMBER); //UV座標に注意（上限１．０ｆ）
	pVtx[TexNumber_1].tex = D3DXVECTOR2(fTexSize, CObject3D::F_INIT_NUMBER);
	pVtx[TexNumber_2].tex = D3DXVECTOR2(CObject3D::F_INIT_NUMBER, TEXTURE_SIZE);
	pVtx[TexNumber_3].tex = D3DXVECTOR2(fTexSize, TEXTURE_SIZE);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==================================================================================
//テクスチャの更新処理
//==================================================================================
void CEffectDirection::Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex)
{
	m_nLife++;  //カウントする

	//ライフが既定の数値になった時
	if (m_nLife >=MAX_EXPLOSION_LIFE * dLifeCount)
	{
		CMain::VERTEX_3D* pVtx; //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(BUFFNUMBE, BUFFNUMBE, (void**)&pVtx, CObject3D::N_INIT_NUMBER);

		//テクスチャ座標の設定
		pVtx[TexNumber_0].tex.x = pVtx[TexNumber_0].tex.x + fMaxTex;
		pVtx[TexNumber_1].tex.x = pVtx[TexNumber_1].tex.x + fMaxTex;
		pVtx[TexNumber_2].tex.x = pVtx[TexNumber_2].tex.x + fMaxTex;
		pVtx[TexNumber_3].tex.x = pVtx[TexNumber_3].tex.x + fMaxTex;

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();

		m_nLife = CObject3D::N_INIT_NUMBER; //ライフを初期化する
	}
}


//==================================================================================
//雷のエフェクト
//==================================================================================

//========================
//コンストラクタ
//========================
CThunder::CThunder()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Effect\\thunder.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CThunder::~CThunder()
{

}


//==================================================================================
//爆発エフェクト
//==================================================================================

//========================
//コンストラクタ
//========================
CExplotion::CExplotion()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\explosion001.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CExplotion::~CExplotion()
{

}


//==================================================================================
//炎の爆発エフェクト
//==================================================================================

//========================
//コンストラクタ
//========================
CExplotionPillar::CExplotionPillar()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\Fire000.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CExplotionPillar::~CExplotionPillar()
{

}


//==================================================================================
//柱状の炎エフェクト
//==================================================================================

//========================
//コンストラクタ
//========================
CExplotionPillar001::CExplotionPillar001()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\PillarOfFireAll.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CExplotionPillar001::~CExplotionPillar001()
{

}


//==================================================================================
//破片エフェクトのストラテジークラスの継承処理
//==================================================================================

//========================
//コンストラクタ
//========================
CFormerDebris::CFormerDebris()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\Effect\\Debris.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CFormerDebris::~CFormerDebris()
{

}


//==================================================================================
//必殺技
//==================================================================================

//========================
//コンストラクタ
//========================
CSourceSpecialAttack::CSourceSpecialAttack()
{
	SetEffectFileNamePass("data\\TEXTURE\\UI\\SpecialGage\\SpecialGageRE.png"); //ファイルパスを設定
}

//========================
//デストラクタ
//========================
CSourceSpecialAttack::~CSourceSpecialAttack()
{

}


//=======================================================================================================================================================================
//エフェクトの管理者処理
//=======================================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CManagerEffect::CManagerEffect(int nPriority) : CObject3D(nPriority)
{
	SetLife(SET_BULLET_LIFE);                  //ライフの設定
	m_pEffectDirection000 = nullptr;           //ストラテジー基底クラスのポインターの初期化
	m_nEffectNumber = EXCLUSION_EFFECT_NUMBER; //エフェクトナンバーの初期化
	m_dLifeCount = CObject3D::F_INIT_NUMBER;              //アニメーションの速度の初期化
	m_fMaxTex = CObject3D::F_INIT_NUMBER;                 //テクスチャの大きさの初期化
}

//===========================
//デストラクタ
//===========================
CManagerEffect::~CManagerEffect()
{
	//ストラテジー基底クラスのポインターの情報がある時
	if (m_pEffectDirection000 != nullptr)
	{
		delete m_pEffectDirection000;    //情報を消す
		m_pEffectDirection000 = nullptr; //情報を無くす
	}
}

//============================
//初期化処理
//============================
HRESULT CManagerEffect::Init()
{
	//初期化に失敗した時
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;            //失敗を返す
	}

	return S_OK;                  //成功を返す
}

//============================
//破棄処理
//============================
void CManagerEffect::Uninit()
{
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}

//============================
//更新処理
//============================
void CManagerEffect::Update()
{
	//アニメーションの速度が０以外の時
	if (m_dLifeCount != MIN_DLIFECOUNT)
	{
		m_pEffectDirection000->Effect(GetTexture(), GetBuffer(), m_dLifeCount, m_fMaxTex); //ストラテジーの基底クラスの処理を呼ぶ
	}

	SetAdjustLife()--;                       //ライフを減らす

	//エフェクトナンバーがIF_EFFECTNUMBER以外の時
	if (m_nEffectNumber != IF_EFFECTNUMBER)
	{
		//アルファ値が０以下の時
		if (GetAlpha() > CObject3D::N_INIT_NUMBER)
		{
			SetAdjustAlpha() -= MINUS_ALPHA; //アルファ値を減らす
		}
	}

	SetCol(CObject3D::RED, CObject3D::GREEN, CObject3D::BLUE, GetAlpha());    //色の設定

	//ライフが尽きた時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		//炎エフェクト時
		if (m_nEffectNumber == IF_EFFECTNUMBER)
		{
			this->SetEffect(GetPos());                 //自身のエフェクトを呼ぶ
			SetAlpha(FIRE_ALPHA);                      //アルファ値の設定
			SetLife(FIRE_LIFE);                        //ライフの設定
			m_nEffectNumber = EXCLUSION_EFFECT_NUMBER; //エフェクトナンバーの初期化（その後消すため）
		}

		//その他の時
		else
		{
			CObject3D::Release(); //自身を消す
			return;               //処理を抜ける
		}
	}

	CObject3D::Update();          //更新処理を呼ぶ
}

//============================
//描画処理
//============================
void CManagerEffect::Draw()
{
	CObject3D::DrawEffect(); //描画処理を呼ぶ
}


//============================
//エフェクトの設定
//============================
void CManagerEffect::SetEffect(D3DXVECTOR3 pos)
{
	SetPos(pos); //位置を引数と同期させる
}


//===========================
//エフェクトの生成
//===========================
CManagerEffect* CManagerEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CManagerEffect* pEffect = nullptr; //基底クラスのポインター

	//雷
	if (type == CObject3D::TYPE::THENDER)
	{
		pEffect = new CNatureEffect(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_nEffectNumber = CObject3D::N_INIT_NUMBER;                                            //エフェクトナンバーの設定
			pEffect->m_pEffectDirection000 = new CThunder();                                                //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CNatureEffect::MAX_THANDER_TEX);  //一分割
			pEffect->m_fMaxTex = CNatureEffect::MAX_THANDER_TEX;                                            //テクスチャの最大サイズの設定
			pEffect->SetSize(CNatureEffect::THANDER_SIZEX, CNatureEffect::THANDER_SIZEY, CObject3D::F_INIT_NUMBER); //大きさを設定
			pEffect->m_dLifeCount = MIN_DLIFECOUNT;                                                         //アニメーションの速度の設定
			
		}
	}

	//爆発
	else if (type == CObject3D::TYPE::EXPLOSION)
	{
		pEffect = new CExplosion(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                             //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CExplosion::MAX_EXPLOSION_TEX);  //八分割
			pEffect->m_fMaxTex = CExplosion::MAX_EXPLOSION_TEX;                                            //テクスチャの最大サイズの設定
			pEffect->SetSize(CExplosion::EXPLSION_SIZEX, CExplosion::EXPLSION_SIZEY, CObject3D::F_INIT_NUMBER); //大きさを設定
			pEffect->m_dLifeCount = CExplosion::MAX_EXPLOSION_ANIMETION_SPEED;                             //アニメーションの速度の設定
		}
	}

	//爆発００１
	else if (type == CObject3D::TYPE::EXPLOSION001)
	{
		pEffect = new CExplosion001(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotion();                                                        //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetEffectFileNamePass("data\\TEXTURE\\UI\\Explosion\\explosion004.png");  //テクスチャのファイルパスを設定
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CExplosion001::MAX_EXPLOSION001_TEX);       //八分割
			pEffect->m_fMaxTex = CExplosion001::MAX_EXPLOSION001_TEX;                                                 //テクスチャの最大サイズの設定
			pEffect->SetSize(CExplosion001::EXPLSION001_SIZEX, CExplosion001::EXPLSION001_SIZEY, CObject3D::F_INIT_NUMBER); //大きさを設定
			pEffect->m_dLifeCount = CExplosion001::MAX_EXPLOSION001_ANIMETION_SPEED;                                  //アニメーションの進める速さを設定
		}
	}

	//炎
	else if (type == CObject3D::TYPE::FIRE)
	{
		pEffect = new CFire(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar();                            //継承クラス
			pEffect->m_nEffectNumber = IF_EFFECTNUMBER;                                         //エフェクトナンバーの設定
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CFire::MAX_FIRE_TEX); //八分割     
			pEffect->m_fMaxTex = CFire::MAX_FIRE_TEX;                                           //テクスチャの最大サイズの設定
			pEffect->SetSize(CFire::FIRE_SIZEX, CFire::FIRE_SIZEY, CObject3D::F_INIT_NUMBER);   //大きさの設定
			pEffect->m_dLifeCount = CFire::MAX_FIRE_ANIMETION_SPEED;                            //アニメーションの進める速さを設定
		}
	}

	//柱状の炎
	else if (type == CObject3D::TYPE::PILLAROFFIRE)
	{
		pEffect = new CPillarOfFire(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CExplotionPillar001();                                            //ストラテジーの継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CPillarOfFire::MAX_PILLAROFFIRE_TEX);    //八分割
			pEffect->m_fMaxTex = CPillarOfFire::MAX_PILLAROFFIRE_TEX;                                              //テクスチャの最大サイズの設定
			pEffect->SetSize(CPillarOfFire::PILLAROFFIRE_SIZEX, CPillarOfFire::PILLAROFFIRE_SIZEY, CObject3D::F_INIT_NUMBER); //大きさの設定
			pEffect->m_dLifeCount = CPillarOfFire::MAX_PILLAROFFIRE_ANIMETION_SPEED;                               //アニメーションの進める速さを設定
		}
	}

	//破片
	else if (type == CObject3D::TYPE::DEBRIS)
	{
		pEffect = new CDebris(); //継承クラス

		//初期化に成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CFormerDebris();                                   //ストラテジー継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CDebris::MAX_DEBRIS_TEX); //一分割
			pEffect->m_fMaxTex = CDebris::MAX_DEBRIS_TEX;                                           //テクスチャの最大サイズの設定
		}
	}

	//必殺技
	else if (type == CObject3D::TYPE::SPECIALATTACK)
	{
		pEffect = new CSpecialAttack(); //継承クラス

		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->m_pEffectDirection000 = new CSourceSpecialAttack();                                          //ストラテジー継承クラス
			pEffect->m_pEffectDirection000->SetInfo(pEffect->GetBuffer(), CSpecialAttack::MAX_SPECIALATTACK_TEX); //八分割
			pEffect->m_fMaxTex = CSpecialAttack::MAX_SPECIALATTACK_TEX;                                           //テクスチャの最大サイズの設定
			pEffect->SetSize(CSpecialAttack::SPECIALATTACK_SIZEX, CSpecialAttack::SPECIALATTACK_SIZEY, CObject3D::F_INIT_NUMBER);  //大きさの設定
		}
	}

	//テクスチャーや位置の同期
	if (pEffect != nullptr)
	{
		pEffect->SetFileNamePass(pEffect->m_pEffectDirection000->GetEffectFileNamePass());  //テクスチャのファイルパスの同期
		pEffect->SetPos(pos);                                                               //位置の同期
		pEffect->Lood();                                                                    //テクスチャの読み込み関数
		return pEffect;                                                                     //情報を返す
	}

	return nullptr; //無を返す
}


//=======================================================================================================================================================
//自然系のエフェクト処理
//=======================================================================================================================================================
CNatureEffect::CNatureEffect()
{

}
CNatureEffect::~CNatureEffect()
{

}


//==============================================================================================================================================================
//爆発エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CExplosion::CExplosion()
{

}

//===========================
//コンストラクタ
//===========================
CExplosion::~CExplosion()
{

}


//==============================================================================================================================================================
//炎エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
CFire::CFire()
{
	SetLife(FIRELIFE); //ライフの設定
}

//===========================
//コンストラクタ
CFire::~CFire()
{

}

//===========================
//描画処理
//===========================
void CFire::Draw()
{
	CObject3D::DrawEffect1(); //描画処理を呼ぶ
}


//==============================================================================================================================================================
//柱状の炎
//==============================================================================================================================================================

//===========================
//コンストラクタ
CPillarOfFire::CPillarOfFire()
{
	SetLife(PILLARFIRELIFE); //ライフの設定
}

//===========================
//コンストラクタ
CPillarOfFire::~CPillarOfFire()
{

}

//============================
//初期化処理
//============================
HRESULT CPillarOfFire::Init()
{
	//初期化処理が成功した時
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //失敗を返す
	}

	return S_OK;       //成功を返す
}

//============================
//更新処理
//============================
void CPillarOfFire::Update()
{
	this->GetEffectDirection()->Effect(GetTexture(), GetBuffer(), D_LIFECOUNT, MAX_PILLAROFFIRE_TEX); //自身のストラテジー継承クラスの処理を呼ぶ
	SetCol(CObject3D::RED, CObject3D::GREEN, CObject3D::BLUE, GetAlpha());                            //色の設定

	//当たり判定
	if (CObject3D::CollisionPrtsPlayer(PILLAROFFIRE_SIZEX, PILLAROFFIRE_SIZEY, PILLAROFFIRE_SIZEZ) == true)
	{
		//プレイヤーのHPゲージを減らす
		CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() -= CManager::GetInstance()->GetPlayerHPGage()->GetPlayerHPSizeX() * ADJUST_PLAYER_HP_GAGE;
	}

	//ライフが０以下の時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		SetAdjustAlpha() -= MINUS_ALPHA;  //アルファ値を減らす

		//アルファ値が０以下の時
		if (GetAlpha() <= CObject3D::N_INIT_NUMBER)
		{
			CObject::Release(); //自身を削除
			return;             //処理を抜ける
		}
	}
	else
	{
		SetAdjustLife()--;      //ライフを減らす
	}
}


//==============================================================================================================================================================
//弾につくエフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CEffect::CEffect(int nPriority) : CObject3D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Effect\\effect000.png");  //テクスチャのファイルパスを設定
}


//===========================
//デストラクタ
//===========================
CEffect::~CEffect()
{

}


//============================
//初期化処理
//============================
HRESULT CEffect::Init()
{
	//初期化が成功した時
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL;                               //失敗を返す
	}

	SetSize(SIZEX, SIZEY, CObject3D::F_INIT_NUMBER); //大きさの設定
	return S_OK;                                     //成功を返す
}


//============================
//破棄処理
//============================
void CEffect::Uninit()
{
	CObject3D::Uninit(); //基底クラスの破棄処理を呼ぶ
}


//============================
//更新処理
//============================
void CEffect::Update()
{
	SetAdjustLife()--;        //ライフを減らす

	//ライフが０以下の時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CObject3D::Release(); //自身を消す
		return;               //処理を抜ける
	}

	CObject3D::Update();      //更新処理を呼ぶ
}


//============================
//描画処理
//============================
void CEffect::Draw()
{
	CObject3D::DrawEffect(); //描画処理を呼ぶ
}


//===========================
//エフェクトの生成
//===========================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pEffect = new CEffect(CREATE_PRIORITY); //動的確保

	//情報がある時
	if (pEffect != nullptr)
	{
		//初期化が成功した時
		if (SUCCEEDED(pEffect->Init()))
		{
			pEffect->SetPos(pos);      //位置を引数と同期させる
			pEffect->Lood();           //テクスチャの読み込み
			return pEffect;            //情報を返す
		}						       
	}							       
								       
	return nullptr;                    //無を返す
}


//==============================================================================================================================================================
//爆発エフェクト001
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CExplosion001::CExplosion001()
{

}


//===========================
//コンストラクタ
//===========================
CExplosion001::~CExplosion001()
{

}


//==============================================================================================================================================================
//破片エフェクト
//==============================================================================================================================================================

//===========================
//コンストラクタ
//===========================
CDebris::CDebris()
{
	SetLife(DEBRISLIFE); //ライフの設定
	SetSizeX(SIZEX);     //ｘ軸の大きさを設定
}


//===========================
//コンストラクタ
//===========================
CDebris::~CDebris()
{

}

//===========================
//更新処理
//===========================
void CDebris::Update()
{
	SetAdjustLife()--;                                           //ライフを減らす
	SetAddjustSizeX() += PLUS_SIZEX;                             //ｘ軸のサイズを大きくする
	SetSize(GetSizeX(), GetSizeX(), CObject3D::F_INIT_NUMBER);   //サイズの設定

	//ライフが０以下の時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		CObject3D::Release(); //自身を消す
	}
}


//==============================================================================================================================================================
//必殺技
//==============================================================================================================================================================

//===========================
//コンストラクタ
CSpecialAttack::CSpecialAttack()
{
	SetLife(SPECIALATTACKLIFE);               //ライフの設定
	SetSizeX(m_fSepecialAttackX);             //ｘ軸の大きさを設定
	m_nRotNumber = CObject3D::N_INIT_NUMBER;  //向き番号の初期化
}

//===========================
//コンストラクタ
CSpecialAttack::~CSpecialAttack()
{

}

//============================
//更新処理
//============================
void CSpecialAttack::Update()
{
	this->GetEffectDirection()->Effect(GetTexture(), GetBuffer(), D_LIFECOUNT, MAX_SPECIALATTACK_TEX); //自身のストラテジー継承クラスの処理を呼ぶ

	SetCol(CObject3D::RED, CObject3D::GREEN, CObject3D::BLUE, GetAlpha());          //色の設定

	//ｘ軸の大きさが規定値より小さい時
	if (GetSizeX() <= MAXIMUM_SIZEX)
	{
		SetAddjustSizeX() += PLUS_SIZEX;                                            //サイズを大きくする
	}

	//向き番号が１の時
	if (m_nRotNumber == ROT_NUMBER_1)
	{
		SetEffectSize(GetSizeX(), m_fSepecialAttackY, CObject3D::F_INIT_NUMBER);    //サイズの設定
	}

	//向き番号が２の時
	else if (m_nRotNumber == ROT_NUMBER_2)
	{
		SetEffectSize(-GetSizeX(), m_fSepecialAttackY, CObject3D::F_INIT_NUMBER);   //サイズの設定
	}

	HitEnemy();                                                          //当たり判定処理を呼ぶ

	//ライフが０以下の時
	if (GetLife() <= CObject3D::N_INIT_NUMBER)
	{
		SetAdjustAlpha() -= MINUS_ALPHA;                                 //アルファ値を減らす

		//アルファ値が０以下の時
		if (GetAlpha() <= CObject3D::N_INIT_NUMBER)
		{
			CObject::Release(); //自身を削除
			return;             //処理を抜ける
		}
	}
	else
	{
		SetAdjustLife()--;     //ライフを減らす
	}
}

//============================
//敵との当たり判定処理
//============================
void CSpecialAttack::HitEnemy()
{
	//ボスの情報がある時
	if (CManager::GetInstance()->GetBoss() != nullptr)
	{
		//ボスの最大パーツ数分回す
		for (int nCount2 = CObject3D::N_INIT_NUMBER; nCount2 < CObjectX::MAX_BOSSPARTS; nCount2++)
		{
			//当たり判定
			if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetBoss()->GetPosPartsBoss(nCount2),
				m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
				CManager::GetInstance()->GetBoss()->GetModelSizePartsBoss(nCount2), GetSizeX()))
			{
				//ボスのHPゲージを減らす
				CManager::GetInstance()->GetBossHPGage()->GetBossHPSizeX() -= CMain::SCREEN_WIDTH * MAX_DAMAGE_BOSS; 
			}
		}
	}

	//モーション付きの敵の作られた分回す
	for (int nMotionInEnemy001 = 0; nMotionInEnemy001 < CManager::GetInstance()->GetMotionInEnemy001Count() + 1; nMotionInEnemy001++)
	{
		//情報がある時
		if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001) != nullptr)
		{
			//モーション付きの敵の最大パーツ数分回す
			for (int nCount1 = 0; nCount1 < CObjectX::MAX_ENEMYPARTS; nCount1++)
			{
				//当たり判定
				if (CManager::GetScene()->GetPlayerX()->GetCollision()->Coliision3Dcircle(GetPos(), CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetPosPartsEnemy(nCount1),
					m_fSepecialAttackX, m_fSepecialAttackY, CBullet3D::MAX_BULLET3D_SIZE_Z,
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetModelSizePartsEnemy(nCount1), GetSizeX()))
				{
					CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() = 0; //ライフを消す

					//モーション付きの敵のライフが尽きた時
					if (CManager::GetInstance()->GetEnemyInMotion001(nMotionInEnemy001)->GetLife() <= 0)
					{
						CManager::GetInstance()->DesignationUninitXEnemy(CObjectX::TYPE::ENEMYINMOTION001, nMotionInEnemy001);  //ポインターをnullptrにする
						return;                                                                                                 //処理を抜ける
					}
				}
			}
		}
	}
}