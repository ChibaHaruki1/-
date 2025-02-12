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
		CLING,           //オブジェクトにつくUI
		TELEPHONPOLEUI,  //電柱のUI
		TELEPHONPOLEUI1, //電柱のUI
		SCREEN,         //背景
		BUYSENDTEXT,    //買うテキスト
		HP,             //HPゲージ
		MP,             //MPゲージ
		TALKTEXTR,       //話すtext
		BOSSHP,         //ボスHPゲージ
		BOSSMP,         //ボスMPゲージ
		FUELGAGE,       //燃料ゲージ
		LASER,          //レーザー
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

	CObject(int nPriority = DEFAULT_PRIORITY);                                                    //コンストラクタ
	virtual ~CObject();                                                                           //デストラクタ
	virtual HRESULT Init() = 0;                                                                   //初期化処理
	virtual void Uninit() = 0;                                                                    //終了処理
	virtual void Update() = 0;                                                                    //更新処理
	virtual void Draw() = 0;                                                                      //描画処理
	static void ReleaseAll();                                                                     //全オブジェクトの解放
	static void UpdateAll();                                                                      //全オブジェクトの更新
	static void DrawAll();                                                                        //全オブジェクトの描画
	inline static CObject* GetObject1(int nPri, int nIndex) { return m_apObject[nPri][nIndex]; }  //オブジェクト取得
	inline TYPE GetType() { return m_type; }                                                      //タイプ取得
	inline void SetType(TYPE type) { m_type = type; }                                             //タイプ設定
	void Release();

	//マクロ定義
	static constexpr  int DEFAULT_PRIORITY = 3;               //描画順の初期値
	static constexpr  int MAX_PRIORITY_OBJ = 4;               //描画順の最大数//自分自身の解放

	static constexpr int N_INIT_NUMBER = 0;                   //int型の初期化の値
	static constexpr float F_INIT_NUMBER = 0.0f;              //float型の初期化の値

	static constexpr UINT BUFF_NUMBE = 0U;                    //バッファのロック時の番号
	static constexpr UINT STARTVERTEX = 0U;                   //描画時の初めのバーテクス番号
	static constexpr UINT STREAMNUMBER = 0U;                  //ストリーム設定時の番号
	static constexpr UINT PRIMITIVECOUNT = 2U;                //描画時のPrimitiveCountの設定

	static constexpr int PVTX_NUMBER_0 = 0;                   //頂点情報のpvtxの番目
	static constexpr int PVTX_NUMBER_1 = 1;                   //頂点情報のpvtxの１番目
	static constexpr int PVTX_NUMBER_2 = 2;                   //頂点情報のpvtxの２番目
	static constexpr int PVTX_NUMBER_3 = 3;                   //頂点情報のpvtxの３番目
	static constexpr int PVTX_NUMBER_OF = 4;                  //pvtxの基本数

	static constexpr int INIT_PRIORITY = 0;                   //プライオリティの初期値
	static constexpr int N_INIT_COL_NUMBER = 255;             //色の初期値

	static constexpr int N_INIT_ALPHA_NUMBER = 255;           //アルファ値の初期値
	static constexpr int RED = 255;                           //赤色
	static constexpr int GREEN = 255;                         //緑色
	static constexpr int BLUE = 255;                          //青色

private:
	//マクロ定義
	static constexpr  int MAX_OBJECT = 500;                    //オブジェクトの最大数

	static CObject* m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT]; //全オブジェクトの管理

	int m_nPriority; //自身のプライオリティ
	int m_nID;       //自分自身のID
	TYPE m_type;     //オブジェクトタイプ

};

