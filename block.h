//======================================
//
//障害物のクラス管理[block.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//インクルード
#include "objectX.h"


//==================================================================
//ストラテジー基底クラス
//==================================================================
class CBlockXStrategy
{
public:
	CBlockXStrategy();          //コンストラクタ
	~CBlockXStrategy();         //デストラクタ

	const char* GetBlockFileNamePass() { return m_aBlockFile; }                               //ファイルパスを取得
	void SetBlockFileNamePass(const char* aBlockFileName) { m_aBlockFile = aBlockFileName; }  //ファイルパスを設定

private:
	const char* m_aBlockFile;  //ファイルパスを保管する用の変数
};


//==================================================================
//ストラテジークラス継承
class CBlock000 : public CBlockXStrategy
{
public:
	CBlock000();   //コンストラクタ
	~CBlock000();  //デストラクタ
};


//==================================================================
//ストラテジークラス継承
class CBlock001 : public CBlockXStrategy
{
public:
	CBlock001();   //コンストラクタ
	~CBlock001();  //デストラクタ
};


//==================================================================
//ストラテジークラス継承
class CBlock002 : public CBlockXStrategy
{
public:
	CBlock002();   //コンストラクタ
	~CBlock002();  //デストラクタ
};


//==================================================================
//ストラテジークラス継承
class CBlock003 : public CBlockXStrategy
{
public:
	CBlock003();   //コンストラクタ
	~CBlock003();  //デストラクタ
};


//==================================================================
//ストラテジークラス継承
class CBlock004 : public CBlockXStrategy
{
public:
	CBlock004();   //コンストラクタ
	~CBlock004();  //デストラクタ
};

//==================================================================

//ストラテジークラス継承
class CBlock005 : public CBlockXStrategy
{
public:
	CBlock005();   //コンストラクタ
	~CBlock005();  //デストラクタ
};


//==================================================================
//ストラテジークラス継承
class CBlock006 : public CBlockXStrategy
{
public:
	CBlock006();   //コンストラクタ
	~CBlock006();  //デストラクタ
};


//==================================================================
//次のステージへ行く用のobj
class CSpaceBattleShip : public CBlockXStrategy
{
public:
	CSpaceBattleShip();   //コンストラクタ
	~CSpaceBattleShip();  //デストラクタ
};


//==================================================================
//ボス専用のブロック（ステージ）
class CFinalBlock : public CBlockXStrategy
{
public:
	CFinalBlock();   //コンストラクタ
	~CFinalBlock();	 //デストラクタ
};


//==================================================================
// ボス専用のブロック（ステージ）
class CFinalBlock1 : public CBlockXStrategy
{
public:
	CFinalBlock1() { SetBlockFileNamePass("data\\XFILE\\BLOCK\\FianlStageCeiling.x"); }  //コンストラクタ
	~CFinalBlock1() {};																	 //デストラクタ
};


//==================================================================
//がれきに関するブロック
class CRubble : public CBlockXStrategy
{
public:
	CRubble() {};  //コンストラクタ
	~CRubble() {}; //デストラクタ
};


//==================================================================
//ブロックの基底クラス
//==================================================================
class CManagerBlock : public  CObjectX
{
public:
	CManagerBlock(int nPriority = DEFAULT_PRIORITY1);  //コンストラクタ
	~CManagerBlock()override;						   //デストラクタ
	HRESULT Init()override;                            //初期化処理  
	void Uninit()override;                             //破棄処理
	void Update() override;                            //更新処理
	void Draw()override;
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type); //テキストファイルに情報を書き込む処理

	static CManagerBlock* Create(D3DXVECTOR3 pos, STRATEGYTYPE type);                    //生成処理

private:
	static int m_nCreateCount;          //作られた数を保管する
	CBlockXStrategy* m_pBlockXStrategy; //ストラテジー基底クラスのポインター
};


//==================================================================
//3D障害物のクラス管理
class CFiledBlock : public  CManagerBlock
{
public:
	CFiledBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CFiledBlock()override;                         //デストラクタ
};


//==================================================================
//上に上がるためのブロック
class CGoUpBlock : public CManagerBlock
{
public:
	CGoUpBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CGoUpBlock()override;                         //デストラクタ
};


//==================================================================
//道用のブロック
class CRoadBlock : public CManagerBlock
{
public:
	CRoadBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CRoadBlock()override;                         //デストラクタ
};


//==================================================================
//壁兼道用ブロック
class CWallRoadBlock : public CManagerBlock
{
public:
	CWallRoadBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CWallRoadBlock()override;                         //デストラクタ
};


//==================================================================
//小さいブロック
class CSmallBlock : public CManagerBlock
{
public:
	CSmallBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CSmallBlock()override;                         //デストラクタ
};


//==================================================================
//上壁のブロック
class CUpWallBlock : public CManagerBlock
{
public:
	CUpWallBlock(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CUpWallBlock()override;                         //デストラクタ
};


//==================================================================
//次のステージへ行く為のシップ
class CSpaceBattleShip000 : public CManagerBlock
{
public:
	CSpaceBattleShip000(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CSpaceBattleShip000()override;                         //デストラクタ

private:
	//マクロ定義
	static constexpr float INIT_ROT_X = -0.3f; //X軸の向きの初期値
	static constexpr float INIT_ROT_Y = 1.0f;  //Y軸の向きの初期値
};


//==================================================================
//足場
class CScaffold : public CManagerBlock
{
public:
	CScaffold(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CScaffold()override;                         //デストラクタ
};


//==================================================================
//天井
class CCeiling : public CManagerBlock
{
public:
	CCeiling(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CCeiling()override;                         //デストラクタ
};


//==================================================================
//木の板群
class CWoodenBorad : public CManagerBlock
{
public:
	CWoodenBorad(int nPriority = DEFAULT_PRIORITY1); //コンストラクタ
	~CWoodenBorad()override;	                     //デストラクタ
	void Update()override;                           //更新処理
};
