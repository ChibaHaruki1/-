//============================================
//
//character�N���X�Ǘ�[character.h]
//Ajther: Chiba haruki
//
//============================================

#pragma once

//============================================
//�C���N���[�h
#include "objectX.h"
#include "model_prts.h"


//======================================================
//�L�����N�^�[�̊e�p�[�c�N���X
class CCharacter : public CObjectX
{
public://�O������̃A�N�Z�X�\
	////���ʉ��ł���������
	//typedef enum
	//{
	//	NEUTRAL = 0, //�ҋ@
	//	WALK,        //����
	//	ACTION,      //
	//	JUMP,
	//}COMMON;

	//typedef enum
	//{
	//	BOSSJUMP1=4,
	//}BOSSMOTIONSTATE;

	//typedef enum
	//{
	//	BLOWAWAY=4,
	//}MOTIONSTATE;

	//�{�X�̃��[�V�����̎��
	typedef enum
	{
		BOSSNEUTRAL = 0, //�ҋ@
		BOSSWALK,        //����
		BOSSACTION,      //����
		BOSSJUMP,        //���
		BOSSIMPACT,      //���001
		BOSSATTACK,      //�U��
		BOSSDIE,         //���S
	}BOSSMOTIONSTATE;

	//�v���C���[�̃��[�V�����̎��
	typedef enum
	{
		NEUTRAL = 0, //�ҋ@
		WALK,        //����
		ACTION,      //����
		JUMP,        //���
		BLOWAWAY,    //�������
		DIE,         //���S
		SLOWSHOT,    //������茂��
		TITLE_JUMP,  //�^�C�g�����̔��
		LANDING,     //���n
		LOKING ,     //�T��(�^�C�g����)
	}MOTIONSTATE;

	CCharacter(int nPriority = DEFAULT_PRIORITY1);         //�R���X�g���N�^
	~CCharacter();                                         //�f�X�g���N�^
	HRESULT Init();                                        //����������
	void Uninit();                                         //�j������

	//�v���C���[
    void Lood();
	void UpdatePlayer();                                   //�v���C���[�̍X�V����
	void DrawPlayer(int NumPrts);                          //�v���C���[�̕`�揈��
	void MotionInfo();                                     //���[�V�����̏�����������
	void SetMotion(MOTIONSTATE motiontype);                //���[�V�������Ƃ̏���
	
	//�{�X
	void LoodBoss();
	void UpdateBoss();                                     //�{�X�̍X�V����
	void DrawBoss(int NumPrts);                            //�`�揈��
	void MotionInfoBoss();                                 //�{�X���[�V�����̏�����������
	void SetMotionBoss(BOSSMOTIONSTATE motiontype);        //�{�X���[�V�������Ƃ̏���

	MOTIONSTATE m_MotionState;                   //�v���C���[�̃��[�V�����̎�ނ̏�������
	BOSSMOTIONSTATE m_MotionStateBoss;           //�{�X�̃��[�V�����̎�ނ̏�������
	CModelPrts* m_pModelPrts[MAX_PRTS];          //���f���p�[�c�̏��̃|�C���^�[
	CModelPrts* m_pModelPrtsBoss[MAX_BOSSPARTS]; //���f���p�[�c�̏��̃|�C���^�[


	//=====================================
	//���̎擾
	CModelPrts* GetModelPrtasBoss(int nNumber) { return m_pModelPrtsBoss[nNumber]; } //�{�X�̃p�[�c�̏��̎擾
	//bool& GetMotionType() { return m_bMotionType; }                                  //�v���C���[�̃��[�V�����^�C�v�̎擾


	//=====================================
	//���̐ݒ�
	void SetMotionType(bool bMotionType) { m_bMotionType = bMotionType; }            //�v���C���[�̃��[�V�����^�C�v�̐ݒ�


	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_KEYSET = 8;        //���[�V�����Ɏg���L�[�̐�
	constexpr static int NUM_MOTION = 11;       //�v���C���[���[�V�����̑���
	constexpr static int NUM_RIGHTLEFTPRTS = 4; //�v���C���[�̑��̃p�[�c��
	constexpr static int NUM_MOTIONBOSS = 10;   //�{�X�̃��[�V�����̑���
	constexpr static int NUM_RIGHTPRTSBOSS = 8; //�{�X�̑��̃p�[�c��

private://�O������̃A�N�Z�X�s�\
	//�}�N����`
	static constexpr int MAX_PARTS_SEARCH = 100;                     //�p�[�c�̎擾���̔z��̍ő吔
	static constexpr int MAX_DATA_SEARCH = 512;                      //�e�L�X�g�t�@�C���̓ǂݍ��ݎ��̔z��̍ő吔
															         
	static constexpr int PLAYER_PARTS_BODY_NUMBER = 0;               //�v���C���[�̑̂̔ԍ�
	static constexpr int PLAYER_PARTS_RIGHTHAND_NUMBER = 5;          //�v���C���[�̉E��̔ԍ�
	static constexpr int PLAYER_PARTS_LEFTHAND_NUMBER = 9;           //�v���C���[�̍���̔ԍ�
	static constexpr int PLAYER_PARTS_WAIST_NUMBER = 10;             //�v���C���[�̍��̔ԍ�
	static constexpr int PLAYER_PARTS_GUN_NUMBER = 17;               //�v���C���[�̏e�̔ԍ�
	static constexpr int PLAYER_PARTS_SHOULDER_FROM_HAND = 4;        //�v���C���[�̌�������For�����񂷍�0,1,2,3�̏��i���A��r�A���r�A��j�ŉ񂷗p
	static constexpr int PLAYER_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;  //�v���C���[�̉E������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A�E������͂Q�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int PLAYER_PARTS_LEFT_SHOULDER_FROM_HAND = 6;   //�v���C���[�̍�������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A��������͂U�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int PLAYER_PARTS_LOWER_BODY_COUNT = 6;          //�v���C���[�̉����g�̃p�[�c��
	static constexpr int PLAYER_PARTS_HEAD_AND_BODY_COUNT = 2;       //�v���C���[�̓��Ƒ̂̐�
	static constexpr int PLAYER_NEXT_MOTION_COUNT = 1;               //�v���C���[�̃��[�V�������̍��������߂鎞�̎��̃��[�V�����J�E���g
	static constexpr int PLAYER_BEFORE_MOTION_COUNT = 1;             //�v���C���[�̃��[�V�������̍������������̑O�̃��[�V�����J�E���g


	static constexpr int BOSS_PARTS_BODY_NUMBER = 0;                 //�{�X�̑̂̔ԍ�
	static constexpr int BOSS_PARTS_RIGHTHAND_NUMBER = 5;            //�{�X�̉E��̔ԍ�
	static constexpr int BOSS_PARTS_LEFTHAND_NUMBER = 9;             //�{�X�̍���̔ԍ�
	static constexpr int BOSS_PARTS_WAIST_NUMBER = 10;               //�{�X�̍��̔ԍ�
	static constexpr int BOSS_PARTS_GUN_NUMBER = 17;                 //�{�X�̏e�̔ԍ�
	static constexpr int BOSS_PARTS_SHOULDER_FROM_HAND = 4;          //�{�X�̌�������For�����񂷍�0,1,2,3�̏��i���A��r�A���r�A��j�ŉ񂷗p
	static constexpr int BOSS_PARTS_RIGHT_SHOULDER_FROM_HAND = 2;    //�{�X�̉E������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A�E������͂Q�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int BOSS_PARTS_LEFT_SHOULDER_FROM_HAND = 6;     //�{�X�̍�������E���For�����񂵂������̒l�i�O�`�R�̏ꍇ�A��������͂U�Ԉȏ�Ȃ̂łǂꂭ�炢����Ă��邩����ɑ��������ׁj
	static constexpr int BOSS_PARTS_LOWER_BODY_COUNT = 6;            //�{�X�̉����g�̃p�[�c��
	static constexpr int BOSS_PARTS_HEAD_AND_BODY_COUNT = 2;         //�{�X�̓��Ƒ̂̐�
	static constexpr int BOSS_NEXT_MOTION_COUNT = 1;                 //�{�X�̃��[�V�������̍��������߂鎞�̎��̃��[�V�����J�E���g
	static constexpr int BOSS_BEFORE_MOTION_COUNT = 1;               //�{�X�̃��[�V�������̍������������̑O�̃��[�V�����J�E���g

	static constexpr float BOSS_PLUS_POS_Y= 200.0f;                  //�{�X�̃p�[�c��Y���̈ʒu����ɏグ��ׂ̒l



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
		Key aKey[MAX_PRTS];        //�L�[��(�p�[�c���m��)
	}KeySet;

	//���[�V�����̍\����
	typedef struct
	{
		bool Loop;                  //���[�V���������[�v���邩�ǂ�������p
		int NumKey;                 //�L�[�̑���
		KeySet KeySet[MAX_KEYSET];  //���[�V�����̃L�[�Z�b�g�i���[�V�������̃L�[�Z�b�g�̐��j
	}MotionSet;

	//���[�V���������m�ۂ���\����
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //����
	}SAVEMODELINFO;

	//�L�����N�^�[�̏���ۊǂ���ϐ�
	SAVEMODELINFO m_pSaveModelPrtInfo[MAX_PRTS], m_pSaveModelPrtInfoBoss[MAX_BOSSPARTS];   //���f���p�[�c�̏��̃|�C���^�[
	D3DXVECTOR3 SaveMotionPos[MAX_PRTS], SaveMotionPosBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̈ʒu�����m�ۂ���ϐ�
	D3DXVECTOR3 SaveMotionRot[MAX_PRTS], SaveMotionRotBoss[MAX_BOSSPARTS];                 //�e�p�[�c�̌��������l������ϐ�
	MotionSet MotionSetPlayer[NUM_MOTION], MotionSetBoss[NUM_MOTIONBOSS];                  //�e���[�V�����̎�ނ��i�[����ϐ�

	int m_nMotionFrameBoss;            //���[�V�������̃t���[�����J�E���g���邽�߂̕ϐ�
	int MotionCount, MotionCountBoss;  //���݂̃��[�V�������J�E���g���邽�߂̕ϐ�(Key�J�E���g)

	bool m_bMotionType, m_bMotionBossType;       //����ȃ��[�V�������ǂ����𔻒肷��ׂ̕ϐ�
};