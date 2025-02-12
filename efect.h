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
	static constexpr int TexNumber_0 = 0;                 //テクスチャの番号０番目
	static constexpr int TexNumber_1 = 1;                 //テクスチャの番号１番目
	static constexpr int TexNumber_2 = 2;                 //テクスチャの番号２番目
	static constexpr int TexNumber_3 = 3;                 //テクスチャの番号３番目
	static constexpr UINT BUFFNUMBE = 0U;                 //バッファのロック時の番号

	static constexpr float TEXTURE_SIZE = 1.0f;           //テクスチャの大きさ

	static constexpr int INIT_LIFE = 0;                   //ライフの初期値
	static constexpr int MAX_EXPLOSION_LIFE = 8;          //アニメーションの更新する時のライフ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine;               //自身のバッファー
	int m_nLife;                                          //テクスチャのライフ（アニメーション用の）
	const char* m_aEffectFileName;                        //テクスチャのファイルパス

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


protected://継承クラスのみアクセス可能

	//マクロ定義 （constexprでコンパイル時に初期化）
	static constexpr  int SET_BULLET_LIFE = 42;            //ライフの最大数
	static constexpr  int MINUS_ALPHA = 5;                 //アルファ値の減算値
	static constexpr  float m_fSepecialAttackX = 200.0f;   //必殺技のX軸の大きさ
	static constexpr  float m_fSepecialAttackY = 200.0f;   //必殺技のY軸の大きさ

private:
	//マクロ定義
	static constexpr int EXCLUSION_EFFECT_NUMBER = -1; //エフェクトの番号の判定からの除外値
	static constexpr int IF_EFFECTNUMBER = 1;          //エフェクトナンバーの条件式の値
	static constexpr double MIN_DLIFECOUNT = 0.0;      //アニメーションライフの最小値

	static constexpr int FIRE_ALPHA = 200;             //ファイアーエフェクトのアルファ値
	static constexpr int FIRE_LIFE = 60;               //ファイアーエフェクトのライフ

	int m_nEffectNumber;                               //最後にエフェクトを呼ぶかどうか
	double m_dLifeCount;                               //アニメーションの速度
	float m_fMaxTex;                                   //テクスチャの最大のサイズ
	CEffectDirection* m_pEffectDirection000;           //ストラテジー基底クラスのポインター
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
	static constexpr  float THANDER_SIZEX = 70.0f;  //雷エフェクトのX軸の大きさ
	static constexpr  float THANDER_SIZEY = 70.0f;  //雷エフェクトのY軸の大きさ
	static constexpr  float MAX_THANDER_TEX = 1.0f; //アニメーションの分割数
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
	static constexpr  float EXPLSION_SIZEX = 90.0f;                 //爆発エフェクトのX軸の大きさ
	static constexpr  float EXPLSION_SIZEY = 90.0f;                 //爆発エフェクトのY軸の大きさ
	static constexpr  float MAX_EXPLOSION_TEX = 0.125f;             //アニメーションの分割数
	static constexpr  double MAX_EXPLOSION_ANIMETION_SPEED = 0.6;   //アニメーションの速さ
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
	static constexpr  float EXPLSION001_SIZEX = 90.0f;                 //爆発エフェクトのX軸の大きさ
	static constexpr  float EXPLSION001_SIZEY = 90.0f;                 //爆発エフェクトのY軸の大きさ
	static constexpr  float MAX_EXPLOSION001_TEX = 0.125f;             //アニメーションの分割数
	static constexpr  double MAX_EXPLOSION001_ANIMETION_SPEED = 0.6;   //アニメーションの速さ
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
	static constexpr  float FIRE_SIZEX = 92.0f;                 //炎エフェクトのX軸の大きさ
	static constexpr  float FIRE_SIZEY = 190.0f;                //炎エフェクトのY軸の大きさ
	static constexpr  float MAX_FIRE_TEX = 0.125f;              //アニメーションの分割数
	static constexpr  double MAX_FIRE_ANIMETION_SPEED = 0.5;    //アニメーションの速さ

private:
	//マクロ定義
	static constexpr  int FIRELIFE = 120; //ライフの最大数
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
	static constexpr  float PILLAROFFIRE_SIZEX = 200.0f;                 //柱状の炎エフェクトのX軸の大きさ
	static constexpr  float PILLAROFFIRE_SIZEY = 600.0f;                 //柱状の炎エフェクトのY軸の大きさ
	static constexpr  float PILLAROFFIRE_SIZEZ = 40.0f;                  //柱状の炎エフェクトのZ軸の大きさ
	static constexpr  float MAX_PILLAROFFIRE_TEX = 0.125f;               //アニメーションの分割数
	static constexpr  double MAX_PILLAROFFIRE_ANIMETION_SPEED = 0.5;     //アニメーションの速さ

private:
	//マクロ定義
	static constexpr  int PILLARFIRELIFE = 180;           //ファイアのライフ
	static constexpr  int MINUS_ALPHA = 5;                //アルファ値の減算値

	static constexpr  double  D_LIFECOUNT = 0.5;          //アニメーションライフの調整値

	static constexpr float ADJUST_PLAYER_HP_GAGE = 0.01f; //プレイヤーのHPゲージの減りを調整する値
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
	static constexpr  int SET_EFFECT_LIFE = 30; //ライフの最大数

	static constexpr  float SIZEX = 40.0f;      //X軸の大きさ
	static constexpr  float SIZEY = 40.0f;      //Y軸の大きさ

	static constexpr int CREATE_PRIORITY = 0;   //生成時のプライオリティの番号
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
	static constexpr  float MAX_DEBRIS_TEX = 1.0f; //アニメーションの分割数


private:
	//マクロ定義
	static constexpr  int DEBRISLIFE = 10;         //ライフの最大数

	static constexpr  float SIZEX = 50.0f;         //X軸の大きさ
	static constexpr  float PLUS_SIZEX = 4.0f;     //X軸の大きさを増やす値

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
	static constexpr  int ROT_NUMBER_1 = 1;                 //向き番号１
	static constexpr  int ROT_NUMBER_2 = 2;                 //向き番号２

	static constexpr  float SPECIALATTACK_SIZEX = 200.0f;   //必殺技エフェクトのX軸の大きさ
	static constexpr  float SPECIALATTACK_SIZEY = 200.0f;   //必殺技エフェクトのY軸の大きさ
	static constexpr  float MAX_SPECIALATTACK_TEX = 0.125f; //アニメーションの分割数


private:
	//マクロ定義
	static constexpr  int SPECIALATTACKLIFE = 180;      //ライフの最大数
	static constexpr  int MINUS_ALPHA = 5;              //アルファ値の減算値

	static constexpr double D_LIFECOUNT = 0.3;          //アニメーションライフの調整値

	static constexpr  float MAXIMUM_SIZEX = 2000.0f;    //サイズを加算していく時の最大値
	static constexpr  float MAX_DAMAGE_BOSS = 0.00005f; //サイズを加算していく時の最大値
	static constexpr  float PLUS_SIZEX = 30.0f;         //X軸の大きさを増やす値


	int m_nRotNumber;                                   //向きで大きさを変えるための変数
};
