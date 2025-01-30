//==============================================
//
//�G��character�N���X�Ǘ�[enemycharacter.h]
//Ajther: Chiba haruki
//
//==============================================

#pragma once

//==============================================
//�C���N���[�h
#include "objectX.h"
#include "model_prts.h"

class CEnemyCharacter : public CObjectX
{
public:

	//�G�̃��[�V�����̎��
	typedef enum
	{
		ENEMYWALK = 0,  //����
		ENEMYJUMP,      //���
		ENEMYATTACK,    //�U��
		ENEMYDIE,       //���S

	}ENEMYMOTIONSTATE;

	CEnemyCharacter(int nPriority = DEFAULT_PRIORITY1);        //�R���X�g���N�^
	~CEnemyCharacter();                                        //�f�X�g���N�^
	HRESULT Init();                                            //����������
	void Uninit();                                             //�j������
	void UpdateEnemy001();                                     //�G001�̍X�V����
	void UpdateEnemy002();                                     //�G002�̍X�V����
	void DrawEnemy(int NumPrts, int nNumber);                  //�`�揈��
	void LoodEnemy(const char* aSelect);                       //���f����ǂݍ��ޏ����{�����擾���鏈��
	void MotionInfoEnemy001();                                 //�G001�̃��[�V�����̏�����������
	void MotionInfoEnemy002();                                 //�G002�̃��[�V�����̏�����������


	//===========================
	//���̎擾
	int& GetEnemy001PartsNumber() { return m_nEnemy001Parts; } //�G001�̃p�[�c���̎擾


	//===========================
	//���̐ݒ�
	void SetMotionEnemy(ENEMYMOTIONSTATE motiontype);                          //�{�X���[�V�������Ƃ̏���
	void SetMotionType(bool bMotionType) { m_bMotionEnemyType = bMotionType; } //���[�V�����^�C�v�̐ݒ�


	ENEMYMOTIONSTATE m_MotionStateEnemy;                      //�{�X�̃��[�V�����̎�ނ̏�������
	CModelPrts* m_pModelPrtsEnemy[MAX_ENEMYPARTS];            //���f���p�[�c�̏��̃|�C���^�[

private:
	//�}�N����`
	constexpr static int MAX_ENEMYKEYSET = 5;                 //���[�V�����Ɏg���L�[�̐�
	constexpr static int NUM_ENEMYMOTION = 10;                //���[�V�����̐�
	constexpr static int HALF = 2;                            //int�^�̎��̔���


	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct
	{
		int Frame;                 //�t���[����
		Key aKey[MAX_ENEMYPARTS];  //�L�[��(�p�[�c���m��)
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;                        //���[�V���������[�v���邩�ǂ�������p
		int NumKey;						  //�L�[�̑���
		KeySet KeySet[MAX_ENEMYKEYSET];	  //���[�V�����̃L�[�Z�b�g�i���[�V�������̃L�[�Z�b�g�̐��j
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}SAVEMODELINFO;

	//�L�����N�^�[�̏���ۊǂ���ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_ENEMYPARTS], m_pSaveModelPrtUpdateInfo[MAX_ENEMYPARTS]; //���f���p�[�c�̏��̃|�C���^�[
	D3DXVECTOR3 SaveMotionPos[MAX_ENEMYPARTS];                 //�e�p�[�c�̈ʒu�����m�ۂ���ϐ�
	D3DXVECTOR3 SaveMotionRot[MAX_ENEMYPARTS];                 //�e�p�[�c�̌��������l������ϐ�
	MotionSet MotionSetEnemy[NUM_ENEMYMOTION];                 //�e���[�V�����̎�ނ��i�[����ϐ�

	int MotionCountEnemy;    //���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)
	int m_nNumParts;         //�p�[�c��
	int m_nEnemy001Parts;    //�G001�̃p�[�c��
	int m_nEnemy002Parts;    //�G002�̃p�[�c��
	bool m_bMotionEnemyType; //����ȃ��[�V�������ǂ���
};