//========================================
//
//オブジェクトクラス管理[object.h]
//Auther:Chiba Haruki
//
//========================================

#pragma once

//========================================
//インクルード
#include "main.h"


//全てを管理するので仮想関数（純粋仮想関数）
class CObject
{
public:

	//それぞれのタイプ
	enum class TYPE
	{
		NONE = 0,           //無し
		ENEMY,              //敵
		PLAYER,             //プレイヤー
		BULLET,             //通常弾
		SPECIALBULLET,      //必殺弾
		BOSSBULLET,         //ボスの弾
		ENEMYBULLET,        //敵の弾
		BATTLESHIPBULLET,   //敵の弾
		BLOCK,              //ブロック
		ITEM,               //アイテム
		SCORE,              //スコア
		FIELD,              //地面
		PRTICLES,           //パーティクル
		PRTICLES001,        //パーティクル１
		EFFECT,             //エフェクト
		EXPLOSION,          //爆発
		EXPLOSION001,       //爆発１
		THENDER,            //雷
		FIRE,               //炎
		PILLAROFFIRE,       //柱状の炎
		IMPACT,             //衝撃波
		DEBRIS,             //破片
		SPECIALATTACK,      //必殺技
		BOSSSPECIALATTACK,  //ボスの必殺技

		//UI
		SCREEN,         //背景
		BUYSENDTEXT,    //買うテキスト
		HP,             //HPゲージ
		MP,             //MPゲージ
		BOSSHP,         //ボスHPゲージ
		BOSSMP,         //ボスMPゲージ
		FUELGAGE,       //燃料ゲージ
		MAX,            //最大数
	};

	//UIのタイプ
	enum class TYPE_UI
	{
		NONEUI = 0,      //無し
		CLING,           //オブジェクトにつくUI
		TELEPHONPOLEUI,  //電柱のUI
		TELEPHONPOLEUI1, //電柱のUI
		BUYTEXT,         //買うtext
		TALKTEXTR,       //話すtext
		LASER,           //レーザー
		NOWCREATE,       //今作ろうとしているUI
		SHOPMENU,
	};

	CObject(int nPriority= DEFAULT_PRIORITY);                                              //コンストラクタ
	virtual ~CObject();                                                                    //デストラクタ
	virtual HRESULT Init()=0;                                                              //初期化処理
	virtual void Uninit() = 0;                                                             //終了処理
	virtual void Update() = 0;                                                             //更新処理
	virtual void Draw() = 0;                                                               //描画処理
	static void ReleaseAll();                                                              //全オブジェクトの解放
	static void UpdateAll();                                                               //全オブジェクトの更新
	static void DrawAll();                                                                 //全オブジェクトの描画
	static CObject* GetObject1(int nPri, int nIndex) { return m_apObject[nPri][nIndex]; }  //オブジェクト取得
	TYPE GetType() {return m_type;}                                                        //タイプ取得
	void SetType(TYPE type) { m_type = type; }                                             //タイプ設定
	void Release();      
	
	//マクロ定義
	constexpr static int MAX_OBJECT = 200;                    //オブジェクトの最大数
	constexpr static int DEFAULT_PRIORITY = 3;                //描画順の初期値
	constexpr static int MAX_PRIORITY_OBJ = 4;                //描画順の最大数//自分自身の解放

private:

	static CObject* m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT]; //全オブジェクトの管理
	int m_nPriority; //自身のプライオリティ
	int m_nID;       //自分自身のID
	TYPE m_type;     //オブジェクトタイプ

};

