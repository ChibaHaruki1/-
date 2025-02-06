//=====================================================
//
//���[�V�����t���̓G�̃N���X�Ǘ�[enemyinmotion.h]
//Auther;Haruki Chiba
//
//=====================================================


#pragma once


//=====================================================
//�C���N���[�h
#include "enemycharacter.h"


//================================================================================
//���[�V�����G�̃}�l�[�W���[�Ǘ��N���X
class CManagerEnemyInMotion : public CEnemyCharacter
{
public: //�A�N�Z�X�\

	CManagerEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);                     //�R���X�g���N�^
	~CManagerEnemyInMotion()override;                                             //�f�X�g���N�^
	HRESULT Init()override;                                                       //����������
	void Uninit()override;                                                        //�j������
	void Update() override;                                                       //�X�V����
	void Draw()override;                                                          //�`�揈��

	static CManagerEnemyInMotion* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);    //��������

protected:
	int m_nJumpFrame;                            //��Ԃ܂ł̎���
	int JumpNumber;                              //�s��������Ԃ悤�ɔԍ�������ׂ̕ϐ�
	int JumpRecastTime;                          //��Ԉׂ̃��L���X�g�^�C���i�A���ŐG��Ă��锻��ɂȂ�ׂ��̏C���j

	//�}�N����`
	 static constexpr  float MAX_SPEED = 2.0f;     //�ǂ������鑬�x
	 static constexpr  int MAX_BUULET_SPEED = 30;  //�e�̑���

};





//================================================================================
//���[�V�����t���̓G�i����j
class CEnemyInMotion001 : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion001(int nPriority = DEFAULT_PRIORITY1);              //�R���X�g���N�^
	~CEnemyInMotion001()override;                                      //�f�X�g���N�^
	void Update() override;                                            //�X�V����
	void Draw()override;                                               //�`�揈��
	void AdjustmentBulletAndRot();                                     //�v���C���[�ɑ΂���@�̂ƒe�̒�������
	void WhenCollisionBlock();                                         //�n�ʗp�u���b�N�ɐG��Ă��鎞�̏���
	void Correctionrot();                                              //�������C������֐�
	void PlayerBloWwaway();                                            //������΂�����
	void Die();                                                        //���S���̏���

private:
	//�}�N����`
	 static constexpr  int MAX_LIFE = 10;                                //���C�t�̍ő�l
	 static constexpr  int PLUS_SCORE = 2000;                            //�X�R�A�̉��Z�l
	 static constexpr  int MIN_RANDOM1 = 150;                            //����1�̍ŏ��l
	 static constexpr  int MAX_RANDOM1 = MIN_RANDOM1*2;                  //����1�̍ő�l
	 static constexpr  int MIN_RANDOM2 = 50;                             //����2�̍ŏ��l
	 static constexpr  int MAX_RANDOM2 = MIN_RANDOM2*2;                  //����2�̍ő�l
													                   
	 static constexpr  float ADJUST_PRTAS_ROTX = 0.01f;                  //�p�[�c��X���̌����𒲐�����l
	 static constexpr  float ADJUST_BULLET_ROTY = 0.3f;                  //�e��Y���̌����𒲐�����l
	 static constexpr  float MULTIPLICATIOB_ADJUST_BULLET_ROTY = 4.0f;   //�e��Y���̌����𒲐�����|���Z�̒l
	 static constexpr  float IF_ADJUST_BULLET_ROTY = 3.0f;               //�e��Y���̌����𒲐�����������̊|���Z�̒l
	 static constexpr  float MAX_EXPLOSION_SIZE1 = 200.0f;               //�����G�t�F�N�g�̑傫���̒l�P
	 static constexpr  float MAX_EXPLOSION_SIZE2 = 300.0f;               //�����G�t�F�N�g�̑傫���̒l�Q
	 static constexpr  float MAX_DAMAGE = 0.1f;                          //�_���[�W��

	int m_nHitFrame;                                                   //�v���C���[�Ɠ����������̃��L���X�g�^�C��
	bool m_bHit;                                                       //�����������ǂ����̔���p�ϐ�
};


//================================================================================
//���[�V�����t���̓G�i�ʏ�j
class CEnemyInMotion002 : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion002(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CEnemyInMotion002()override;                           //�f�X�g���N�^
	void Update() override;                                 //�X�V����	
	void Draw()override;                                    //�`�揈��
};
