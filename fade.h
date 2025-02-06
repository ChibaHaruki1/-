//======================================
//
//フェードのクラス管理[fade.h]
//Auther:Chiba Haruki
//
//======================================


#pragma once


//======================================
//インクルード
#include "object2D.h"


class CFade : public CObject2D
{
public:

	//フェードの種類
	enum class FADE
	{
		FADE_NONE = 0,  //何もなし
		FADE_IN,        //フェードイン
		FADE_OUT,       //フェードアウト
		FADE_MAX        //最大数
	};

	CFade(int nPriority = DEFAULT_PRIORITY);  //コンストラクタ
	~CFade()override;						  //デストラクタ
	HRESULT Init()override;					  //初期化処理
	void Uninit()override;					  //破棄処理
	void  Update()override;					  //更新処理
	void Draw()override;					  //描画処理

	static CFade* Create();                   //生成処理


	//============================================
	//情報の設定
	void SetFade(FADE fade) { m_Fade = fade; } //フェードの設定


	//マクロ定義 （constexprでコンパイル時に初期化）
	 static constexpr  int FINISH_FADE_OUT = 255; //フェードアウトの終了する値

private:
	//マクロ定義 （constexprでコンパイル時に初期化）
	 static constexpr  int MAX_FADE_SPEED = 3;    //フェードの処理の色の変化する速度調整

	 static constexpr  int RED = 0;          //赤色
	 static constexpr  int GREEN = 0;        //緑色
	 static constexpr  int BLUE = 0;         //青色

	FADE m_Fade;     //FADEの情報を格納する変数
};
