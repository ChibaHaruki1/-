//=========================================
//
//エフェクトのクラス管理[efect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once

//=========================================
//インクルード
#include "object3D.h"
#include<memory>


//========================================================================================================
//ストラテジークラス基底
class CEffectDirection
{
public:
	CEffectDirection();  //コンストラクタ
	~CEffectDirection(); //デストラクタ

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                  //テクスチャ（座標）の情報
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex);  //エフェクトの処理

	const char* GetEffectFileNamePass() { return m_aEffectFileName; }                               //ファイルパスを取得
	void SetEffectFileNamePass(const char* aEffectFieName) { m_aEffectFileName = aEffectFieName; }  //ファイルパスを設定

private:
	//マクロ定義
	constexpr static float MAX_EXPLOSION_LIFE = 8;        //アニメーションの更新する時のライフ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //自身のバッファー
	int m_nLife;                            //テクスチャのライフ（アニメーション用の）
	const char* m_aEffectFileName;          //テクスチャのファイルパス

};


//========================================================================================================
//ストラテジークラス継承　雷
class CThunder : public CEffectDirection
{
public:
	CThunder();   //コンストラクタ
	~CThunder();  //デストラクタ		
};


//========================================================================================================
//ストラテジークラス継承　爆発
class CExplotion : public CEffectDirection
{
public:
	CExplotion();   //コンストラクタ
	~CExplotion();  //デストラクタ						  
};


//========================================================================================================
//炎
class CExplotionPillar : public CEffectDirection
{
public:
	CExplotionPillar();   //コンストラクタ
	~CExplotionPillar();  //デストラクタ
};


//========================================================================================================
//柱状の炎
class CExplotionPillar001 : public CEffectDirection
{
public:
	CExplotionPillar001();   //コンストラクタ
	~CExplotionPillar001();	 //デストラクタ
};


//========================================================================================================
//ストラテジー継承　破片
class CFormerDebris : public CEffectDirection
{
public:
	CFormerDebris();   //コンストラクタ
	~CFormerDebris();  //デストラクタ
};


//========================================================================================================
//ストラテジー継承　必殺技
class CSourceSpecialAttack : public CEffectDirection
{
public:
	CSourceSpecialAttack();   //コンストラクタ
	~CSourceSpecialAttack();  //デストラクタ
};


//========================================================================================================
//エフェクト管理の基底クラス
//========================================================================================================
class CManagerEffect : public CObject3D
{
public:
	CManagerEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerEffect();								   //デストラクタ
	HRESULT Init()override;							   //初期化処理
	void Uninit()override;							   //破棄処理
	void Update()override;							   //更新処理
	void Draw()override;							   //描画処理
	void SetEffect(D3DXVECTOR3 pos);

	static CManagerEffect* Create(D3DXVECTOR3 pos, TYPE type); //生成処理


	//============================
	//情報の取得
	CEffectDirection* GetEffectDirection() { return m_pEffectDirection000; } //ストラテジー基底クラスのポインターを取得


	//============================
	//情報の設定
	void SetMaxTex(float fMaxTex) { m_fMaxTex = fMaxTex; }


protected://継承クラスのみアクセス可能

	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static int SET_BULLET_LIFE = 42;            //ライフの最大数
	constexpr static int MINUS_ALPHA = 5;                 //アルファ値の減算値
	constexpr static float m_fSepecialAttackX = 200.0f;   //必殺技のX軸の大きさ
	constexpr static float m_fSepecialAttackY = 200.0f;   //必殺技のY軸の大きさ

private:
	//マクロ定義
	constexpr static int RED = 255;          //赤色
	constexpr static int GREEN = 255;        //緑色
	constexpr static int BLUE = 255;         //青色
	
	int m_nEffectNumber;                      //最後にエフェクトを呼ぶかどうか
	double m_dLifeCount;                      //アニメーションの速度
	float m_fMaxTex;                          //テクスチャの最大のサイズ
	CEffectDirection* m_pEffectDirection000;  //ストラテジー基底クラスのポインター
};


//========================================================================================================
//自然系のエフェクトクラス
class CNatureEffect : public CManagerEffect
{
public:
	CNatureEffect();            //コンストラクタ
	~CNatureEffect()override;   //デストラクタ


	//=========================
	//マクロ定義
	constexpr static float THANDER_SIZEX = 70.0f;  //雷エフェクトのX軸の大きさ
	constexpr static float THANDER_SIZEY = 70.0f;  //雷エフェクトのY軸の大きさ
	constexpr static float MAX_THANDER_TEX = 1.0f; //アニメーションの分割数
};


//========================================================================================================
//1つ目の爆発エフェクト
class CExplosion : public CManagerEffect
{
public:
	CExplosion();          //コンストラクタ
	~CExplosion()override; //デストラクタ


	//=========================
	//マクロ定義
	constexpr static float EXPLSION_SIZEX = 90.0f;                 //爆発エフェクトのX軸の大きさ
	constexpr static float EXPLSION_SIZEY = 90.0f;                 //爆発エフェクトのY軸の大きさ
	constexpr static float MAX_EXPLOSION_TEX = 0.125f;             //アニメーションの分割数
	constexpr static double MAX_EXPLOSION_ANIMETION_SPEED = 0.6;   //アニメーションの速さ
};


//========================================================================================================
//二つ目の爆発エフェクト
class CExplosion001 : public CManagerEffect
{
public:
	CExplosion001();           //コンストラクタ
	~CExplosion001()override;  //デストラクタ


	//=========================
	//マクロ定義
	constexpr static float EXPLSION001_SIZEX = 90.0f;                 //爆発エフェクトのX軸の大きさ
	constexpr static float EXPLSION001_SIZEY = 90.0f;                 //爆発エフェクトのY軸の大きさ
	constexpr static float MAX_EXPLOSION001_TEX = 0.125f;             //アニメーションの分割数
	constexpr static double MAX_EXPLOSION001_ANIMETION_SPEED = 0.6;   //アニメーションの速さ
};


//========================================================================================================
//炎エフェクト
class CFire : public CManagerEffect
{
public:
	CFire();              //コンストラクタ
	~CFire()override;	  //デストラクタ
	void Draw()override;  //描画処理


	//=========================
	//マクロ定義
	constexpr static float FIRE_SIZEX = 92.0f;                 //炎エフェクトのX軸の大きさ
	constexpr static float FIRE_SIZEY = 190.0f;                //炎エフェクトのY軸の大きさ
	constexpr static float MAX_FIRE_TEX = 0.125f;              //アニメーションの分割数
	constexpr static double MAX_FIRE_ANIMETION_SPEED = 0.5;    //アニメーションの速さ

private:
	//マクロ定義
	constexpr static int FIRELIFE = 120; //ライフの最大数
};


//========================================================================================================
//柱状の炎
class CPillarOfFire : public CManagerEffect
{
public:
	CPillarOfFire();           //コンストラクタ
	~CPillarOfFire()override;  //デストラクタ
	HRESULT Init()override;    //初期化処理
	void Update()override;     //更新処理


	//=========================
	//マクロ定義
	constexpr static float PILLAROFFIRE_SIZEX = 200.0f;                 //柱状の炎エフェクトのX軸の大きさ
	constexpr static float PILLAROFFIRE_SIZEY = 600.0f;                 //柱状の炎エフェクトのY軸の大きさ
	constexpr static float PILLAROFFIRE_SIZEZ = 40.0f;                  //柱状の炎エフェクトのZ軸の大きさ
	constexpr static float MAX_PILLAROFFIRE_TEX = 0.125f;               //アニメーションの分割数
	constexpr static double MAX_PILLAROFFIRE_ANIMETION_SPEED = 0.5;     //アニメーションの速さ

private:
	//マクロ定義
	constexpr static int PILLARFIRELIFE = 180; //ファイアのライフ

	constexpr static int RED = 255;          //赤色
	constexpr static int GREEN = 255;        //緑色
	constexpr static int BLUE = 255;         //青色
	constexpr static int MINUS_ALPHA = 5;    //アルファ値の減算値
};


//========================================================================================================
//弾の軌道につくエフェクト
class CEffect : public CObject3D
{
public:
	CEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CEffect()override;							//デストラクタ
	HRESULT Init()override;						//初期化処理
	void Uninit()override;						//破棄処理
	void Update()override;						//更新処理
	void Draw()override;						//描画処理
	
	static CEffect* Create(D3DXVECTOR3 pos);    //生成処理

private:
	//マクロ定義
	constexpr static int SET_EFFECT_LIFE = 30; //ライフの最大数

	constexpr static float SIZEX = 40.0f; //X軸の大きさ
	constexpr static float SIZEY = 40.0f; //Y軸の大きさ
};


//========================================================================================================
//破片エフェクトのクラス
class CDebris : public CManagerEffect
{
public:
	CDebris();              //コンストラクタ
	~CDebris()override;     //デストラクタ
	void Update()override;  //更新処理


	//=========================
	//マクロ定義
	constexpr static float MAX_DEBRIS_TEX = 1.0f; //アニメーションの分割数


private:
	//マクロ定義
	constexpr static int DEBRISLIFE = 10;         //ライフの最大数

	constexpr static float SIZEX = 50.0f;         //X軸の大きさ
	constexpr static float PLUS_SIZEX = 4.0f;     //X軸の大きさを増やす値

};


//========================================================================================================
//必殺技のクラス
class CSpecialAttack : public CManagerEffect
{
public:
	CSpecialAttack();                               //コンストラクタ
	~CSpecialAttack()override;                      //デストラクタ
	void Update()override;                          //更新処理
	void HitEnemy();                                //敵との当たり判定処理


	//==========================
	//情報の取得
	int& GetRotNumber() { return m_nRotNumber; }    //現在の向きを番号で取得する


	//=========================
	//マクロ定義
	constexpr static float SPECIALATTACK_SIZEX = 200.0f;   //必殺技エフェクトのX軸の大きさ
	constexpr static float SPECIALATTACK_SIZEY = 200.0f;   //必殺技エフェクトのY軸の大きさ
	constexpr static float MAX_SPECIALATTACK_TEX = 0.125f; //アニメーションの分割数


private:
	//マクロ定義
	constexpr static int SPECIALATTACKLIFE = 180;      //ライフの最大数

	constexpr static int RED = 255;                    //赤色
	constexpr static int GREEN = 255;                  //緑色
	constexpr static int BLUE = 255;                   //青色
	constexpr static int MINUS_ALPHA = 5;              //アルファ値の減算値

	constexpr static float MAXIMUM_SIZEX = 2000.0f;    //サイズを加算していく時の最大値
	constexpr static float MAX_DAMAGE_BOSS = 0.00005f; //サイズを加算していく時の最大値
	constexpr static float PLUS_SIZEX = 30.0f;         //X軸の大きさを増やす値

	int m_nRotNumber;                                  //向きで大きさを変えるための変数
};
