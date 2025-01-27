//==============================================
//
//ALTER_EGO[character.cpp]
//Author: hiromu otake
//
//==============================================

#include "character.h"
#include "model.h"
#include "manager.h"

//==============================================
// �R���X�g���N�^
//==============================================
CCharacter::CCharacter(int nPriorit) : m_nLife(0), m_aFilename(), m_pModelParts(), m_pMotion(MOTION_NONE)
, m_pos{ 0.0f,0.0f,0.0f }, m_posold{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f }, m_nFlameCnt(0), m_nKeyCount(0)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CCharacter::~CCharacter()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CCharacter::Init()
{
	m_pMotion = MOTION_NONE;

	FILE* pFile = fopen("data\\Motion\\motion.txt", "r");

	int nCnt = 0;

	if (pFile == NULL)
	{
		return S_FALSE;
	}

	char aStr[m_MAX_LETTER];	// ��������i�[

	// �X�N���v�g���J�n����܂œǂݐi�߂�
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);
		if (strcmp(&aStr[0], "SCRIPT") == 0)
		{
			break;
		}
	}

	// ���C�����[�v
	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_SCRIPT") == 0)
		{ // �X�N���v�g�I��
			fclose(pFile);
			break;
		}
		else if (strcmp(&aStr[0], "MODEL_FILENAME") == 0)
		{ // ���f���t�@�C����ǂݍ���
			//char aFilename[m_MAX_LETTER][m_NUM_MODEL_PARTS];
			char aFilename[m_NUM_MODEL_PARTS][m_MAX_LETTER];
			fscanf(pFile, "%s %s", &aStr[0], &aFilename[nCnt][0]);

			OutputDebugStringA(aFilename[nCnt]);

			m_pModelParts[nCnt] = CModelParts::Create(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f), &aFilename[nCnt][0]);

			nCnt++;
		}
		else if (strcmp(&aStr[0], "CHARACTERSET") == 0)
		{ // �L�����N�^�[�̐ݒ�
			LoadCharacterSet(pFile);
		}
	}

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CCharacter::Uninit()
{

}

//==============================================
// �X�V����
//==============================================
void CCharacter::Update()
{

}

//==============================================
// �`�揈��
//==============================================
void CCharacter::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		m_pModelParts[nCnt]->Draw();
	}
}

//=====================================
// �L�����N�^�[����ǂݍ���
//=====================================
void CCharacter::LoadCharacterSet(FILE* pFile)
{
	char aStr[m_MAX_LETTER];	// ��������i�[
	int nCntModel = 0;		// ���f���̐����J�E���g

	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_CHARACTERSET") == 0)
		{ // �L�����N�^�[�ݒ肪�I���
			break;
		}
		else if (strcmp(&aStr[0], "PARTSSET") == 0)
		{ // �p�[�c�̐ݒ�
			LoadPartsSet(pFile, &nCntModel);
		}
	}
}

//=====================================
// �p�[�c�̐ݒ����ǂݍ���
//=====================================
void CCharacter::LoadPartsSet(FILE* pFile, int* nCntModel)
{
	char aStr[m_MAX_LETTER];	// ��������i�[

	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_PARTSSET") == 0)
		{ // �p�[�c�̐ݒ�I��
			(*nCntModel)++;
			break;
		}
		else if (strcmp(&aStr[0], "INDEX") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_nIdx);				// �C���f�b�N�X
		}
		else if (strcmp(&aStr[0], "PARENT") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_nIdxParents);	// �e���f���̃C���f�b�N�X

			if (m_pModelParts[(*nCntModel)]->m_nIdxParents == -1)
			{
				m_pModelParts[(*nCntModel)]->SetParent(nullptr);
			}
			else
			{
				m_pModelParts[(*nCntModel)]->SetParent(m_pModelParts[m_pModelParts[(*nCntModel)]->m_nIdxParents]);
			}
		}
		else if (strcmp(&aStr[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_pos.x,			// x���W��ǂݍ���
				&m_pModelParts[(*nCntModel)]->m_pos.y,			// y���W��ǂݍ���
				&m_pModelParts[(*nCntModel)]->m_pos.z);			// z���W��ǂݍ���
		}
		else if (strcmp(&aStr[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],										// =
				&m_pModelParts[(*nCntModel)]->m_rot.x,			// x��������ǂݍ���
				&m_pModelParts[(*nCntModel)]->m_rot.y,			// y��������ǂݍ���
				&m_pModelParts[(*nCntModel)]->m_rot.z);			// z��������ǂݍ���
		}
	}
}

//=====================================
// �t�@�C���l�[���̎擾
//=====================================
char* CCharacter::GetFileName()
{
	return m_aFilename[0][0];
}

//=====================================
//���[�V�����t�@�C���̓ǂݍ���
//=====================================
void CCharacter::LoadMotion(int* nCntMotion)
{
	FILE* pFile = fopen("data\\Motion\\motion.txt", "r");

	if (pFile == NULL)
	{
		return;
	}

	char aStr[m_MAX_LETTER];	// ��������i�[

	// �X�N���v�g���J�n����܂œǂݐi�߂�
	while (1)
	{
		fscanf(pFile, "%s", &aStr[0]);
		if (strcmp(&aStr[0], "SCRIPT") == 0)
		{
			break;
		}
	}

	// ���C�����[�v
	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_SCRIPT") == 0)
		{ // �X�N���v�g�I��
			fclose(pFile);
			break;
		}
		else if (strcmp(&aStr[0], "MOTIONSET") == 0)
		{ // ���[�V�����̐ݒ�
			LoadMotionSet(pFile, (*nCntMotion));
			(*nCntMotion)++;
		}
	}
}

//=====================================
// �L�����N�^�[����ǂݍ���
//=====================================
void CCharacter::LoadMotionSet(FILE* pFile, int nCntMotion)
{
	char aStr[m_MAX_LETTER];	// ��������i�[
	int nCntKeySet = 0;

	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
		{ // �L�����N�^�[�ݒ肪�I���
			break;
		}
		else if (strcmp(&aStr[0], "LOOP") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],							// =
				&m_pMotionSet[nCntMotion].nLoop);	// ���[�v
		}
		else if (strcmp(&aStr[0], "NUM_KEY") == 0)
		{
			fscanf(pFile, "%s %d",
				&aStr[0],							// =
				&m_pMotionSet[nCntMotion].NumKey);	// ���Ԗڂ̃L�[
		}
		else if (strcmp(&aStr[0], "KEYSET") == 0)
		{ // �p�[�c�̐ݒ�
			LoadKeySet(pFile, nCntMotion, nCntKeySet);
			nCntKeySet++;
		}
	}
}

//=====================================
// ���f���̃L�[��ǂݍ���
//=====================================
void CCharacter::LoadKeySet(FILE* pFile, int nCntMotion, int nCntKeySet)
{
	char aStr[m_MAX_LETTER];	// ��������i�[
	int nCntKey = 0;

	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "#") == 0)
		{
			//fgets(aStr, 20, pFile);
			LoadSkip(pFile);
			continue;
		}

		if (strcmp(&aStr[0], "END_KEYSET") == 0)
		{ // �p�[�c�̐ݒ�I��

			break;
		}
		else if (strcmp(&aStr[0], "KEY") == 0)
		{ // �p�[�c�̐ݒ�
			LoadKey(pFile, nCntMotion, nCntKeySet, nCntKey);
			nCntKey++;
		}
		else if (strcmp(&aStr[0], "FRAME") == 0)
		{
			fscanf(pFile, "%s %f",
				&aStr[0],												// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].nFlame);	// �t���[���ǂݍ���
		}
	}
}

//=====================================
// ���f���̃L�[�̐ݒ����ǂݍ���
//=====================================
void CCharacter::LoadKey(FILE* pFile, int nCntMotion, int nCntKeySet, int nCntKey)
{
	char aStr[m_MAX_LETTER];	// ��������i�[

	while (1)
	{
		// �������ǂݍ���
		fscanf(pFile, "%s", &aStr[0]);

		if (strcmp(&aStr[0], "END_KEY") == 0)
		{ // �p�[�c�̐ݒ�I��
			break;
		}
		else if (strcmp(&aStr[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],															// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x,	// x���W��ǂݍ���
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x,	// y���W��ǂݍ���
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].pos.x);	// z���W��ǂݍ���
		}
		else if (strcmp(&aStr[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f",
				&aStr[0],															// =
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.x,	// x��������ǂݍ���
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.y,	// y��������ǂݍ���
				&m_pMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.z);	// z��������ǂݍ���
		}
	}
	return;
}

void CCharacter::LoadSkip(FILE* pFile)
{
	int nSkip;

	while (1)
	{
		nSkip = fgetc(pFile);

		if (nSkip == '\n' || nSkip == EOF)
		{
			break;
		}
	}
}

void CCharacter::SetMotion(MOTION motion)
{
	if (m_pMotion != motion)
	{
		m_pMotion = motion;

		m_nFlameCnt = 0;

		m_nKeyCount = 0;

		for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
		{
			//g_Player.aModel[nCnt].pos = g_aMotionSet[motion].aKeySet[0].aKey[nCnt].pos;
			m_pModelParts[nCnt]->m_rot = m_pMotionSet[motion].aKeySet[0].aKey[nCnt].rot;
		}
	}
}

void CCharacter::PlayerMotion(void)
{
	D3DXVECTOR3 posMotion[m_NUM_MODEL_PARTS];
	D3DXVECTOR3 rotMotion[m_NUM_MODEL_PARTS];

	//���̃L�[
	int nNextKey = (m_nKeyCount + 1) % m_pMotionSet[m_pMotion].NumKey;

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		//���݂̃L�[����ߋ��̃L�[�������Ă���t���[���Ŋ���
		rotMotion[nCnt] = ((m_pMotionSet[m_pMotion].aKeySet[nNextKey].aKey[nCnt].rot) - (m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].aKey[nCnt].rot)) / (float)m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].nFlame;
		m_pModelParts[nCnt]->m_rot += rotMotion[nCnt];
	}

	m_nFlameCnt++;

	//
	if (m_nFlameCnt >= m_pMotionSet[m_pMotion].aKeySet[m_nKeyCount].nFlame)
	{
		m_nFlameCnt = 0;
		m_nKeyCount = (m_nKeyCount + 1) % m_pMotionSet[m_pMotion].NumKey;
	}
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3& CCharacter::GetPos()
{
	return m_pos;
}

//======================================================
// �ߋ��̈ʒu�̎擾
//======================================================
D3DXVECTOR3& CCharacter::GetPosOld()
{
	return m_posold;
}

D3DXVECTOR3& CCharacter::GetRot()
{
	return m_rot;
}

CModelParts* CCharacter::GetModelParts(int idx)
{
	return m_pModelParts[idx];
}