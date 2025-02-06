//=======================================
//
//スコアのクラス管理[score.h]
//Author:chiba haruki
//
//=======================================

#pragma once

//=======================================
//インクルード
#include "object2D.h"
#include "scene.h"


//============================================================
//スコアの管理クラス
class CManagerScore : public CObject2D
{
public://外部からのアクセス可能

	//弾構造体の定義
	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		bool bUse;       //使用しているかどうか
	}Score;

	CManagerScore(int nPriority = DEFAULT_PRIORITY);               //コンストラクタ
	~CManagerScore()override;                                      //デストラクタ
	 HRESULT Init()override;                                       //初期化
	 void Uninit()override;                                        //終了処理
	 void Update() override;                                       //更新処理
	 void Draw()override;                                          //描画処理
	 void SetScorepos(D3DXVECTOR3 pos);                            //スコアの位置設定処理
	 void SetScore(int nScore);                                    //スコアの設定処理
	 void AddScore(int nValue);                                    //スコアのカウント増減処理
	 void InitAddScore(int nValue);                                //スコアのカウント増減処理
	 void PosScore(void);                                          //スコアの設定処理
	 static  CManagerScore* Create(CScene::MODE mode, int Number); //スコアの生成処理

	 //マクロ定義 （constexprでコンパイル時に初期化）
	  static constexpr  int MAX_SCORE = 10;             //スコアの最大数
	  static constexpr  float DIVISION_SCORE = 0.1f;    //スコアの最大数
	  static constexpr  int DIGIT = 10;                 //桁管理用
	  static constexpr  int MAX_SIZE_X = 20;            //スコアのX軸の大きさ
	  static constexpr  int MAX_SIZE_Y = 40;            //スコアのY軸の大きさ
	  static constexpr  int MAX_TEXTURE_SIZEX = 10;     //スコアのX軸の大きさ
	  static constexpr  float FMAX_SCORE = 10.0f;       //スコアの最大数(float型)
	  static constexpr  float PLUSSCORE_POSX = 40.0f;   //スコアのX軸の増加させる値
	  static constexpr  float CORE_POSX = 900.0f;       //スコアのX軸の位置
	  static constexpr  float CORE_POS1X = 40.0f;       //スコアのX軸の位置
	  static constexpr  float SCORE_POSY = 40.0f;       //スコアのY軸の位置

private:
	//マクロ定義
	static constexpr int MOVE_PVTX = 4;             //バーテクスの移動値
	static constexpr int INIT_DIGIT = 1;            //桁管理用の初期値
	static constexpr int BEFORE_DIGIT = 1;          //前の桁

	static constexpr float ADJUST_TEX_POS_X = 1.0f; //テクスチャのX軸の位置の調整値
	static constexpr float ADJUST_TEX_POS_Y = 1.0f; //テクスチャのY軸の位置の調整値

	Score m_aScore[MAX_SCORE];                      //スコアの情報
	int m_nSocre;                                   //スコアの値を保管する用
	float m_fPosX;                                  //スコアの初期化位置(x)の更新
	float m_fPosY;                                  //スコアの初期化位置(x)の更新
};


//============================================================
//ゲームスコア
class CGameScore : public CManagerScore
{
public:
	CGameScore(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CGameScore()override;                         //デストラクタ
};


//============================================================
//リザルトスコアクラス
class CResultScore : public CManagerScore
{
public:
	CResultScore(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CResultScore()override;                         //デストラクタ
};
