//==================================================
//
//�L�����N�^�[�̊e�p�[�c�̏���[enemycharacter.cpp]
//Auther: Haruki Chiba
//
//==================================================


//=============================
//�C���N���[�h
#include "enemycharacter.h"
#include "rendererh.h"
#include "manager.h"


//======================
//�R���X�g���N�^
//======================
CEnemyCharacter::CEnemyCharacter(int nPriority) : CObjectX(nPriority)
{
	//�G�̃p�[�c������
	for (int nCount = 0; nCount < MAX_ENEMYPARTS; nCount++)
	{
		m_pModelPrtsEnemy[nCount] = nullptr;                   //�G�̃p�[�c�̏�����
		m_pSaveModelPrtInfo[nCount] = {};					   //���f���p�[�c�̕ۊǏ��̏�����
		m_pSaveModelPrtUpdateInfo001[nCount] = {};				   //�X�V�p���f���p�[�c�̕ۊǏ��̏�����
		m_pSaveModelPrtUpdateInfo002[nCount] = {};				   //�X�V�p���f���p�[�c�̕ۊǏ��̏�����
	}

	MotionCountEnemy = 0;                                      //���[�V�������̃J�E���g��������
	m_nNumParts = 0;                                           //�p�[�c���̏�����
	m_nEnemy001Parts = 0;                                      //�G001�p�[�c���̏�����
	m_nEnemy002Parts = 0;                                      //�G002�p�[�c���̏�����
	m_bMotionEnemyType = false;                                //���[�V�����^�C�v�̏�����
	m_MotionStateEnemy = ENEMYWALK;                            //���[�V������Ԃ̏�����
}


//======================
//�f�X�g���N�^
//======================
CEnemyCharacter::~CEnemyCharacter()
{

}


//=======================
//����������
//=======================
HRESULT CEnemyCharacter::Init()
{
	//�����������s������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//========================
//�j������
//========================
void CEnemyCharacter::Uninit()
{
	CObjectX::Uninit(); //�j���������Ă�
	
	//�ő�p�[�c������
	for (int nCount1 = 0; nCount1 < MAX_ENEMYPARTS; nCount1++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy[nCount1] != nullptr)
		{
			m_pModelPrtsEnemy[nCount1]->Uninit(); //�j������
			delete m_pModelPrtsEnemy[nCount1];    //��������
			m_pModelPrtsEnemy[nCount1] = nullptr; //���𖳂���
		}
	}
}

//========================
//�G001�̍X�V����
//========================
void CEnemyCharacter::UpdateEnemy001()
{
	MotionInfoEnemy001(); //���[�V�������s���������Ă�

	//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
	for (int nCount = 0; nCount < m_nEnemy001Parts; nCount++)
	{
		//�p�[�c�̈ʒu�̍X�V
		GetPosPartsEnemy(nCount) = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount].pos.x + GetPos().x,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.y + GetPos().y,
			m_pSaveModelPrtUpdateInfo001[nCount].pos.z + GetPos().z); //�e�p�[�c��ۊǒl�{���݂̈ʒu�ŏC��
	}
}

//========================
//�G002�̍X�V����
//========================
void CEnemyCharacter::UpdateEnemy002()
{
	MotionInfoEnemy002(); //���[�V�������s���������Ă�

	for (int nCount = 0; nCount < m_nEnemy002Parts; nCount++)
	{
		//�p�[�c���Ƃ̈ʒu����ɍX�V�����Ƃ��Ƃ̃p�[�c��pos�𑫂����킹����
		for (int nCount = 0; nCount < m_nEnemy001Parts; nCount++)
		{
			//�p�[�c�̈ʒu�̍X�V
			GetPosPartsEnemy(nCount) = D3DXVECTOR3(m_pSaveModelPrtUpdateInfo002[nCount].pos.x + GetPos().x,
				m_pSaveModelPrtUpdateInfo002[nCount].pos.y + GetPos().y,
				m_pSaveModelPrtUpdateInfo002[nCount].pos.z + GetPos().z); //�e�p�[�c��ۊǒl�{���݂̈ʒu�ŏC��
		}
	}
}

//========================
//�G�̕`�揈��
//========================
void CEnemyCharacter::DrawEnemy(int NumPrts, int nNumber)
{
	CRenderer* pRenderer = CManager::GetRenderer();     //�����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice(); //�f�o�C�X�̃|�C���^	

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;      //�v�Z�p�}�g���b�N�X
	D3DXMATRIX pMtx = CObjectX::GetmtxWorld();  //�}�g���b�N�X���擾����
	D3DXVECTOR3 pos, rot;                       //�ʒu�ƌ������擾����ׂ̕ϐ�

	pos = GetPos(); //�ʒu���擾����
	rot = GetRot(); //�������擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pMtx);

	//-----�����𔽉f-----
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxRot);

	//-----�ʒu�𔽉f-----
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//�}�g���b�N�X�ɑ��
	D3DXMatrixMultiply(&pMtx, &pMtx, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &pMtx);

	//�p�[�c������
	for (int nCount = 0; nCount < NumPrts; nCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy[nCount] != nullptr)
		{
			m_pModelPrtsEnemy[nCount]->Draw(pMtx); //�e�p�[�c�̕`�揈��
		}
	}
}

//======================
//�{�X�̃��[�h����
//======================
void CEnemyCharacter::LoodEnemy(const char* aSelect)
{
	int nCount = 0;                      //�ŏ��̃p�[�c�����J�E���g���邽�߂̕ϐ�
	int nKeyCount = 0;                   //���[�V�����̃L�[���J�E���g���邽�߂̕ϐ�
	int nModelPrtsCount = 0;             //��������p�[�c���̃J�E���g���邽�߂̕ϐ�
	char aPrtsPass[MAX_PARTS_SEARCH];    //�e�p�[�c��ǂݎ��ۂ̃p�X��ǂݍ��ނ��߂̕ϐ�
	char m_aDataSearch[MAX_DATA_SEARCH]; //�K�v�ȏ���ǂݎ��ۂ̕������ǂ݂ނ��߂̕ϐ�
								       
	int nMotionCount = 0;                //���[�V�����̐����J�E���g���邽�߂̕ϐ�
	int nKeySetCount = 0;                //���[�V�����̃L�[�Z�b�g�̐����J�E���g���邽�߂̕ϐ�
								         
	FILE* m_pFile = nullptr;             //�t�@�C���|�C���^�[

	//�G�O�Ԗڂ�I��
	if (aSelect == "Enemy000")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy000.txt", "r"); //�t�@�C�����J��
	}

	//�G�P�Ԗڂ�I��
	else if (aSelect == "Enemy001")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy001.txt", "r"); //�t�@�C�����J��
	}

	else if (aSelect == "Enemy002")
	{
		m_pFile = fopen("data\\motion\\normal_motion\\Enemy002.txt", "r"); //�t�@�C�����J��
	}

	//�J���Ȃ�������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//���[�v
	while (1)
	{
		(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

		//���̕�����ǂݎ������
		if (!strcmp(m_aDataSearch, "SCRIPT"))
		{
			//���[�v
			while (1)
			{
				(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

				//���t�@�C���ǂݍ���
				if (!strcmp(m_aDataSearch, "MODEL_FILENAME"))
				{
					(void)fscanf(m_pFile, "%s %s", &m_aDataSearch, &aPrtsPass[nModelPrtsCount]); //�p�[�c���擾

					//���f���p�[�c�J�E���g���ő吔��菬������
					if (nModelPrtsCount < MAX_ENEMYPARTS)
					{
						m_pModelPrtsEnemy[nModelPrtsCount] = CModelPrts::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &aPrtsPass[nModelPrtsCount], GetMesh(), GetBuffMat(), GetdwNumMat(), GetMat());  //�p�[�c�̐���
						m_pModelPrtsEnemy[nModelPrtsCount]->BindSize(GetMaxParts(nModelPrtsCount), GetMinParts(nModelPrtsCount), GetModelSizePartsEnemy(nModelPrtsCount));														   //���𓯊�������
						nModelPrtsCount++; //�z���i�߂�
					}
				}

				//�I������
				if (!strcmp(m_aDataSearch, "END_SCRIPT"))
				{
					break; //�����𔲂���
				}

				//�L�����N�^�p�[�c�̏���ǂݎ��
				if (!strcmp(m_aDataSearch, "CHARACTERSET"))
				{
					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

						//�I������
						if (!strcmp(m_aDataSearch, "END_CHARACTERSET"))
						{
							break; //�����𔲂���
						}

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[0] == '#')
						{
							continue; //���s
						}

						if (!strcmp(m_aDataSearch, "NUM_PARTS"))
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch); //����
							(void)fscanf(m_pFile,"%d",&m_nNumParts);     //�p�[�c���̏�����
						}

						//�p�[�c�̏��̓ǂݍ���
						if (!strcmp(m_aDataSearch, "PARTSSET"))
						{
							//���[�v
							while (1)
							{
								(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

								//�I������
								if (!strcmp(m_aDataSearch, "END_PARTSSET"))
								{
									break; //�����𔲂���
								}

								//�C���f�b�N�X��ǂݎ�����
								if (!strcmp(m_aDataSearch, "INDEX"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetIndexPrts()); //�p�[�c�̃C���f�b�N�X��ǂݎ��
								}

								//�e�p�[�c���ǂ�����ǂݎ�����
								else if (!strcmp(m_aDataSearch, "PARENT"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetIndexModelPrts()); //�e�p�[�c����ǂݎ��

									//�ǂݍ��񂾒l���[�P�̎�
									if (m_pModelPrtsEnemy[nCount]->GetIndexModelPrts() == -1)
									{
										m_pModelPrtsEnemy[nCount]->SetParent(nullptr); //���Ȃ�
									}

									//���̑�
									else
									{
										m_pModelPrtsEnemy[nCount]->SetParent(m_pModelPrtsEnemy[m_pModelPrtsEnemy[nCount]->GetIndexModelPrts()]); //�e�ł����������
									}
								}

								//�ʒu��ǂݎ�����
								else if (!strcmp(m_aDataSearch, "POS"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetPos().x, &m_pModelPrtsEnemy[nCount]->GetPos().y, &m_pModelPrtsEnemy[nCount]->GetPos().z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].pos = m_pModelPrtsEnemy[nCount]->GetPos();                //�ʒu��ۊǂ���
									//m_pSaveModelPrtInfo[nCount].pos += MotionSetEnemy[0].KeySet[0].aKey[nCount].pos;
								}

								else if (!strcmp(m_aDataSearch, "ROT"))
								{
									(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &m_pModelPrtsEnemy[nCount]->GetRot().x, &m_pModelPrtsEnemy[nCount]->GetRot().y, &m_pModelPrtsEnemy[nCount]->GetRot().z); //�ʒu�̓���
									m_pSaveModelPrtInfo[nCount].rot = m_pModelPrtsEnemy[nCount]->GetRot();                //������ۊǂ���
									//m_pSaveModelPrtInfo[nCount].rot += MotionSetEnemy[0].KeySet[0].aKey[nCount].rot;
								}
							}
							nCount++; //�ǂݎ��p�[�c�̔ԍ��𑝂₷
						}
					}
				}

				//���[�V�����̏���ǂݍ��ޏ���
				if (!strcmp(m_aDataSearch, "MOTIONSET"))
				{
					int LoopType = 0; //���[�v���邩�ǂ����̔���p�ϐ�

					//���[�v
					while (1)
					{
						(void)fscanf(m_pFile, "%s", m_aDataSearch); // ����

						//�R�����g��ǂݍ��񂾎�
						if (m_aDataSearch[0] == '#')
						{
							continue;                          //���s
							fgets(m_aDataSearch, 40, m_pFile); //�t�@�C�����當�����ǂݍ���
						}

						//�I������
						if (!strcmp(m_aDataSearch, "END_MOTIONSET"))
						{
							break; //�����𔲂���
						}

						//���[�v���ǂ������肷�����
						else if (!strcmp(m_aDataSearch, "LOOP"))
						{
							(void)fscanf(m_pFile, "%s", m_aDataSearch); //����
							(void)fscanf(m_pFile, "%d", &LoopType);     //���[�v���邩�ǂ�������

							//�ǂݍ��񂾒l���O�̎�
							if (LoopType == 0)
							{
								MotionSetEnemy[nMotionCount].Loop = false; //���[�v���Ȃ�
							}

							//���̑�
							else
							{
								MotionSetEnemy[nMotionCount].Loop = true;  //���[�v����
							}
						}

						//�L�[�̓ǂݍ��ݏ���
						else if (!strcmp(m_aDataSearch, "NUM_KEY")) 
						{
							(void)fscanf(m_pFile, "%s", &m_aDataSearch);                        //����
							(void)fscanf(m_pFile, "%d", &MotionSetEnemy[nMotionCount].NumKey);	//�L�[�̐�������
						}

						//�p�[�c���Ƃ̈ʒu�֌W��ǂݎ��
						if (!strcmp(m_aDataSearch, "KEYSET"))
						{

							//���[�v����
							while (1)
							{
								(void)fscanf(m_pFile, "%s", &m_aDataSearch); //����

								//�R�����g��ǂݍ��񂾎�
								if (m_aDataSearch[0] == '#')
								{
									fgets(m_aDataSearch, 20, m_pFile); //�t�@�C�����當����ǂݎ��
									continue;                          //�����𑱂���
								}

								//���[�V�����̓ǂݍ��ݏI��
								if (!strcmp(m_aDataSearch, "END_KEYSET"))
								{
									break; //�����𔲂���
								}

								//�t���[����ǂݎ�����
								if (!strcmp(m_aDataSearch, "FRAME"))
								{
									(void)fscanf(m_pFile, "%s %d", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].Frame); //�t���[����������
								}

								//�L�[�̒��g�̏���ǂݎ�����
								if (!strcmp(m_aDataSearch, "KEY"))
								{
									//���[�v
									while (1)
									{
										(void)fscanf(m_pFile, "%s", &m_aDataSearch); //������ǂݎ��

										//�R�����g��ǂݍ��񂾎�
										if (m_aDataSearch[0] == '#')
										{
											continue;                           //�����𑱂���
											fgets(m_aDataSearch, 40, m_pFile);  //�t�@�C�����當����ǂݎ��
										}

										//�ʒu��ǂݎ�����
										if (!strcmp(m_aDataSearch, "POS"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z); //�ʒu�̓���
										}

										//������ǂݎ�����
										else if (!strcmp(m_aDataSearch, "ROT"))
										{
											(void)fscanf(m_pFile, "%s %f %f %f", &m_aDataSearch, &MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y,
												&MotionSetEnemy[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z); //�����̓���
										}

										//�I������
										if (!strcmp(m_aDataSearch, "END_KEY"))
										{
											break; //�����𔲂���
										}
									}
									nKeyCount++; //�L�[�J�E���g�̉��Z
								}
							}
							nKeyCount = 0;  //�L�[�J�E���g�̏�����
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++; //�f�[�^�̉��Z
				}
			}
			fclose(m_pFile); //�t�@�C�������
			break;           //�����𔲂���
		}
	}

	//�G1�Ԗڂ�I�����Ă��鎞
	if (aSelect == "Enemy001")
	{
		int RightnCount = 0; //for���p�̕ϐ�
		int LeftnCount = 0;  //for���p�̕ϐ�

		m_nEnemy001Parts = m_nNumParts; //�p�[�c���̎擾

		//�ő�p�[�c������
		for (int nCount = 0; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo001[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����
		}

		//�E���̈ʒu��̂̈ʒu�����Z����
		m_pSaveModelPrtUpdateInfo001[PARTS_RIGHT_SHOLDER_NUMBER].pos += m_pModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//�����̈ʒu��̂̈ʒu�����Z����
		m_pSaveModelPrtUpdateInfo001[PARTS_LEFT_SHOLDER_NUMBER].pos += m_pModelPrtsEnemy[PARTS_BODY_NUMBER]->GetPos();

		//�E������E���̕���܂�
		for (RightnCount = PARTS_RIGHT_SHOLDER_NUMBER; RightnCount <= PARTS_RIGHT_SHOLDER_WEAPON_NUMBER; RightnCount++)
		{
			//�����l�͌��݂̉E�p�[�c�[�P
			for (int nCount1 = RightnCount-1; nCount1 < RightnCount; nCount1++)
			{
				//�ʒu�����Z����,
				m_pSaveModelPrtUpdateInfo001[RightnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount1].pos.x, m_pSaveModelPrtUpdateInfo001[nCount1].pos.y, m_pSaveModelPrtUpdateInfo001[nCount1].pos.z);
			}
		}

		//�������玟�̃p�[�c�i�T�̎����U�j����I���܂Łi�I���͕���܂Łi�V�ԁj�j
		for (LeftnCount = PARTS_LEFT_SHOLDER_NUMBER; LeftnCount <= PARTS_LEFT_SHOLDER_WEAPON_NUMBER; LeftnCount++)
		{
			//�����l�͌��݂̍��p�[�c�[�P
			for (int nCount2 = LeftnCount; nCount2 < LeftnCount; nCount2++)
			{
				m_pSaveModelPrtUpdateInfo001[LeftnCount].pos += D3DXVECTOR3(m_pSaveModelPrtUpdateInfo001[nCount2].pos.x, m_pSaveModelPrtUpdateInfo001[nCount2].pos.y, m_pSaveModelPrtUpdateInfo001[nCount2].pos.z);  //�ʒu�����Z����
			}
		}

		//�����g���񂷁i�����牺�Ȃ̂ō��̔ԍ��{�P�j
		for (int nLowBody = PARTS_LEFT_WAIST_NUMBER + 1; nLowBody <= PARTS_LEFT_WAIST_NUMBER + PARTS_LOWER_BODY_COUNT; nLowBody++)
		{
			//m_pSaveModelPrtUpdateInfo[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����

			//������e�p�[�c����
			for (int nWaist = PARTS_LEFT_WAIST_NUMBER; nWaist < nLowBody; nWaist++)
			{
				m_pSaveModelPrtUpdateInfo001[nLowBody].pos.y += m_pSaveModelPrtInfo[nWaist].pos.y; ////���̕�����(���̈ʒu�[�e�p�[�c)
			}
		}
	}

	//�G002���I�����ꂽ��
	else if (aSelect == "Enemy002")
	{
		m_nEnemy002Parts = m_nNumParts; //�p�[�c���̎擾

		//�ő�p�[�c������
		for (int nCount = 0; nCount < m_nNumParts; nCount++)
		{
			m_pSaveModelPrtUpdateInfo002[nCount].pos = m_pSaveModelPrtInfo[nCount].pos; //�l�𕡐�����
		}

	}
}

//===============================
//�G001�̃��[�V�������s��
//===============================
void CEnemyCharacter::MotionInfoEnemy001()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < m_nEnemy001Parts; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountEnemy != MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
			}
			else
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].pos; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].rot; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������

			//���[�V��������ԂŃ��[�v���I�t�̎�
			if (MotionSetEnemy[ENEMYJUMP].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy == ENEMYJUMP && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey-1)
				{
					MotionSetEnemy[ENEMYJUMP].KeySet[MotionCountEnemy].Frame = 0; //���[�V�����t���[��������������
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                          //�ʒu������������
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                          //����������������
				}
			}

			//���[�V�������U���Ń��[�v���I�t�̎�
			if (MotionSetEnemy[ENEMYATTACK].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy == ENEMYATTACK && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey-1)
				{
					MotionSetEnemy[ENEMYATTACK].KeySet[MotionCountEnemy].Frame = 0; //���[�V�����t���[��������������
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                            //�ʒu��������
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                            //������������
				}
			}

			//���[�V���������S�Ń��[�v���I�t�̎�
			if (MotionSetEnemy[ENEMYDIE].Loop == false)
			{
				//���[�V�����̏�Ԃ������Őݒ肳��Ă��鎞�ƃL�[�Z�b�g���Ō�̎�
				if (m_MotionStateEnemy == ENEMYDIE && MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
				{
					MotionSetEnemy[ENEMYDIE].KeySet[MotionCountEnemy].Frame = 0; //���[�V�����t���[����������
					pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                         //�ʒu��������
					rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                         //������������
				}
			}

			//�����̕��������Z
			m_pModelPrtsEnemy[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsEnemy[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}
	
	GetFrame()++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (GetFrame() == MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame)
	{
		SetFrame(0);        //�t���[����������
		MotionCountEnemy++; //���[�V�����̃J�E���g�𑝉�

	    //���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey)
		{
			MotionCountEnemy = 0; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountEnemy + 1 == MotionSetEnemy[m_MotionStateEnemy].NumKey && MotionSetEnemy[m_MotionStateEnemy].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionEnemyType = false; //���[�V�����̔����off�ɂ���
			//MotionCountEnemy=1;
			//SetMotionBoss(NEUTRAL);   //���[�V�����̏��̐؂�ւ�
		}
	}
}

//===============================
//�G001�̃��[�V�������s��
//===============================
void CEnemyCharacter::MotionInfoEnemy002()
{
	//���f���̃p�[�c���J��Ԃ�
	for (int nModelCount = 0; nModelCount < m_nEnemy002Parts; nModelCount++)
	{
		//�p�[�c�̏�񂪂��鎞
		if (m_pModelPrtsEnemy[nModelCount] != nullptr)
		{
			//�ړ��ʂ̏�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu�̏�����
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̏�����

			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //�ʒu�����݂̃��[�V�����̈ʒu�Ɠ���
			D3DXVECTOR3 Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //���������݂̃��[�V�����̌����Ɠ���

			//�ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
			if (MotionCountEnemy != MotionSetEnemy[m_MotionStateEnemy].NumKey - 1)
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].pos; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̈ʒu������
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy + 1].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].aKey[nModelCount].rot; //���݂̃��[�V�����̎��̃��[�V�������猻�݂̃��[�V�����̌���������
			}
			else
			{
				Movepos = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].pos - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].pos; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
				Moverot = MotionSetEnemy[m_MotionStateEnemy].KeySet[0].aKey[nModelCount].rot - MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionSetEnemy[m_MotionStateEnemy].NumKey - 1].aKey[nModelCount].rot; //�ŏ��̃��[�V�����̃L�[���猻�݂̃��[�V�����̑����[�P������
			}


			//�����̕����t���[���Ŋ������l�ŉ��Z
			pos = Movepos / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			rot = Moverot / (float)MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame; //�����̈ʒu���v�Z�ł����������Ɖ��Z������


			//�����̕��������Z
			m_pModelPrtsEnemy[nModelCount]->GetPos() += pos; //���݂̈ʒu���v�Z�ł������ʒu�Ɖ��Z������
			m_pModelPrtsEnemy[nModelCount]->GetRot() += rot; //�����̈ʒu���v�Z�ł����������Ɖ��Z������
		}
	}

	GetFrame()++; //�t���[���̉��Z

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (GetFrame() == MotionSetEnemy[m_MotionStateEnemy].KeySet[MotionCountEnemy].Frame)
	{
		SetFrame(0);        //�t���[����������
		MotionCountEnemy++; //���[�V�����̃J�E���g�𑝉�

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (MotionCountEnemy == MotionSetEnemy[m_MotionStateEnemy].NumKey)
		{
			MotionCountEnemy = 0; //�J�E���g��0�ɂ���
		}

		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (MotionCountEnemy + 1 == MotionSetEnemy[m_MotionStateEnemy].NumKey && MotionSetEnemy[m_MotionStateEnemy].Loop == 0)
		{
			//����ȍs���̏I���
			m_bMotionEnemyType = false; //���[�V�����̔����off�ɂ���
		}
	}
}

//==============================
//���[�V�����̐ݒ�
//==============================
void CEnemyCharacter::SetMotionEnemy(ENEMYMOTIONSTATE motiontype)
{
	if (m_MotionStateEnemy != motiontype && m_bMotionEnemyType == false) //���݂̃��[�V�����ƈ������
	{
		m_MotionStateEnemy = motiontype; //���[�V������ݒ�
		MotionCountEnemy = 0;            //���[�V�����̃J�E���g��������
		SetFrame(0);                     //�t���[���̃J�E���g�̏�����

		//���f���̃p�[�c���J��Ԃ�
		for (int nModelCount = 0; nModelCount < MAX_ENEMYPARTS; nModelCount++)
		{
			//�p�[�c�̏�񂪂��鎞
			if (m_pModelPrtsEnemy[nModelCount] != nullptr)
			{
				m_pModelPrtsEnemy[nModelCount]->SetPos(m_pSaveModelPrtInfo[nModelCount].pos);                             //���݂̈ʒu��ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy[nModelCount]->SetRot(m_pSaveModelPrtInfo[nModelCount].rot);						      //���݂̌�����ǂݎ�����l�ɂ���
				m_pModelPrtsEnemy[nModelCount]->GetPos() += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].pos;   //���݂̈ʒu��ݒ肵�����[�V�����̈ʒu�Ɖ��Z
				m_pModelPrtsEnemy[nModelCount]->GetRot() += MotionSetEnemy[motiontype].KeySet[0].aKey[nModelCount].rot;   //���݂̌�����ݒ肵�����[�V�����̌����Ɖ��Z
			}
		}
	}
}
