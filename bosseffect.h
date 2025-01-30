//=========================================
//
//ボス用エフェクトのクラス管理[bossefect.h]
//Auther:Chiba Haruki
//
//=========================================

#pragma once


//=========================
//インクルード
#include "object3D.h"


//========================================================================================================
//ストラテジークラス基底
class CBossEffectDirection
{
public:
	CBossEffectDirection();   //コンストラクタ
	~CBossEffectDirection();  //デストラクタ

	void SetInfo(LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, float fTexSize);                                                 //テクスチャの設定
	void Effect(LPDIRECT3DTEXTURE9 m_pTexture, LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff, double dLifeCount, float fMaxTex); //テクスチャの更新
	

	//===========================
	//情報の取得
	const char* GetFileNamePass() { return m_aEffectFileName; }                                                       //ファイルパスの取得


	//===========================
	//情報の設定
	void SetFileNamePass(const char* aFilePass) { m_aEffectFileName = aFilePass; }                                    //ファイルパスの設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMine; //自身のバッファ
	int m_nLife;                            //アニメーションのライフ用の変数
	const char* m_aEffectFileName;          //ファイルパス
};


//========================================================================================================
//ストラテジークラス継承　衝撃破
class CAttackEffect : public CBossEffectDirection
{
public:
	CAttackEffect();   //コンストラクタ
	~CAttackEffect();  //デストラクタ
};


//========================================================================================================
//必殺技
class CSourceSpecialAttackBoss : public CBossEffectDirection
{
public:
	CSourceSpecialAttackBoss();   //コンストラクタ
	~CSourceSpecialAttackBoss();  //デストラクタ
};


//========================================================================================================
//ボスエフェクト管理の基底クラス
class CManagerBossEffect : public CObject3D
{
public: //外部からアクセス可能
	CManagerBossEffect(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CManagerBossEffect();								   //デストラクタ
	HRESULT Init()override;								   //初期化処理
	void Uninit()override;								   //破棄処理
	void Update()override;								   //更新処理
	void Draw()override;								   //描画処理
	void SetEffect(D3DXVECTOR3 pos);                       //エフェクトの位置の設定

	static CManagerBossEffect* Create(D3DXVECTOR3 pos, TYPE type);  //生成処理（継承クラスをTYPEで生成する）


	//=================================
	//情報の取得
	CBossEffectDirection* GetBossEffectDirection() { return m_pEffectDirection000; } //ストラテジー基底クラスのポインターを取得
	int& GetRotNumber() { return m_nBossRotNumber; }                                 //左右どちらの向きになっているか数字で判定する情報を取得
	int& GetHitNumber() { return m_nHitNumber; }                                     //衝撃波に当たったかどうか判定用の変数の取得


	//=================================
	//情報の設定
	void SetRotNumber(int nRotNumber) { m_nBossRotNumber = nRotNumber; }             //左右どちらの向きになっているか数字で判定する情報を設定
	void SetHitNumber(int nHitNumber) { m_nHitNumber = nHitNumber; }                 //衝撃波に当たったかどうか判定用の変数の設定


	//マクロ定義 （constexprでコンパイル時に初期化）
	constexpr static float MAX_BOSSANIMETION_TEX = 0.125f;     //アニメーションの分割数
	constexpr static float MAX_IMPACT_TEXTURESIZE = 1.0f;      //衝撃波のテクスチャの大きさ
	constexpr static float MAX_BOSSANIMATION_LIFE = 8;         //アニメーションの更新する時のライフ
	constexpr static float MAX_BOSSSPECIALATTACK_X = 200.0f;   //ボスの必殺技のY軸の大きさ
	constexpr static float MAX_BOSSSPECIALATTACK_Y = 200.0f;   //ボスの必殺技のY軸の大きさ
	constexpr static float PLUS_POS_Y = 100.0f;                //必殺技のY軸の位置を足し合わせる為のマクロ
	constexpr static float MAX_DAMAGE = 0.005f;                //ボスの必殺技のダメージ数
	constexpr static float MAX_SIZEX = 40.0f;                  //ｘ軸の大きさ
	constexpr static float MAX_SIZEY = 40.0f;                  //ｙ軸の大きさ
	constexpr static float MAX_SIZEZ = 40.0f;                  //ｚ軸の大きさ

private://外部からのアクセス不可能

	CBossEffectDirection* m_pEffectDirection000; //ストラテジー基底クラスのポインター

	int m_nBossRotNumber; //向きで大きさを変えるための変数
	int m_nHitNumber;     //当たった方向を番号で保管する用の変数

	double m_dLifeCount;  //アニメーションの速度
};


//========================================================================================================
//衝撃波のエフェクト処理
class CImpact : public CManagerBossEffect
{
public:
	CImpact();              //コンストラクタ
	~CImpact()override;     //デストラクタ
	void Update()override;  //更新処理


	//================================
	//マクロ定義
	constexpr static int MAX_IMPACT_LIFE = 100; //ライフの最大値

private:
	//マクロ定義
	constexpr static int RED = 255;             //赤色
	constexpr static int GREEN = 255;           //緑色
	constexpr static int BLUE = 255;            //青色

	constexpr static float PLUS_SIZEX = 4.0f;   //ｘ軸の大きさを加算する値
	constexpr static float PLUS_SIZEY = 1.0f;   //ｙ軸の大きさを加算する値
};


//========================================================================================================
//必殺技のエフェクト処理
class CBossSpecialAttack : public CManagerBossEffect
{
public:
	CBossSpecialAttack();           //コンストラクタ
	~CBossSpecialAttack()override;  //デストラクタ
	void Update()override;          //更新処理

	//==========================
	//マクロ定義
	constexpr static float MAX_SPECIALATTACK_SIZEX = 200.0f; //ｘ軸の大きさ
	constexpr static float MAX_SPECIALATTACK_SIZEY = 200.0f; //ｙ軸の大きさ
	constexpr static int MAX_BOSSSPZECIALATTACK_LIFE = 120;  //ライフの最大値

private:
	//マクロ定義
	constexpr static int RED = 255;                          //赤色
	constexpr static int GREEN = 255;                        //緑色
	constexpr static int BLUE = 255;                         //青色
	constexpr static int MINUS_ALPHA = 5;                    //アルファ値を減算していく値


	constexpr static float ADJUST_SIZE_X = 0.8f;            //必殺技の当たり判定の乗算調整値
	constexpr static float MAXIMUM_SIZEX = 2000.0f;          //サイズを加算していく時の最大値
	constexpr static float PLUS_SIZEX = 20.0f;               //ｘ軸の大きさを加算する値
	constexpr static float ADJUST_PLAYER_POSY = 1.5f;        //プレイヤーのpos.yの位置の値を調整する値

	constexpr static double ANIMETION_DLLIFE = 0.3;          //アニメーションの速さの調整値
};