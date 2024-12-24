//==============================================
//
// ALTER_EGO[model.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "model.h"

//==============================================
// �R���X�g���N�^
//==============================================
CModel::CModel() : m_nNumAll(0), m_pModelList{}, m_pModelName{}
{
	for (int nCnt = 0; nCnt < m_MAXMODEL; nCnt++)
	{
		m_pModelList[nCnt].m_pMesh = nullptr;
		m_pModelList[nCnt].m_pBuffMat = nullptr;
		m_pModelList[nCnt].m_dwNumMat = 0;
		//m_pModelList[nCnt] = {};
		for (int nCntTex = 0; nCntTex < m_MAXSENTENCE; nCntTex++)
		{
			m_pModelName[nCnt][nCntTex] = {};
		}
		memset(m_pModelName[nCnt], 0, sizeof(m_pModelName[nCnt]));
	}
}

//==============================================
// �f�X�g���N�^
//==============================================
CModel::~CModel()
{

}

//==============================================
// ���f���j��
//==============================================
void CModel::Unload()
{
	for (int nCnt = 0; nCnt < m_MAXSENTENCE; nCnt++)
	{
		//���f���j��
		if (m_pModelList[nCnt].m_pMesh != NULL)
		{
			m_pModelList[nCnt].m_pMesh->Release();
			m_pModelList[nCnt].m_pMesh = NULL;
		}
		//���f���j��
		if (m_pModelList[nCnt].m_pBuffMat != NULL)
		{
			m_pModelList[nCnt].m_pBuffMat->Release();
			m_pModelList[nCnt].m_pBuffMat = NULL;
		}
	}
}

//==============================================
// ���f���o�^
//==============================================
int CModel::Regist(const char* pModelName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	for (int nCnt = 0; nCnt < m_MAXMODEL; nCnt++)
	{
		if (m_pModelList[nCnt].m_pMesh == nullptr)
		{// �o�^����Ă��Ȃ�����

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(pModelName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_pModelList[nCnt].m_pBuffMat,
				NULL,
				&m_pModelList[nCnt].m_dwNumMat,
				&m_pModelList[nCnt].m_pMesh);

			strcpy(&m_pModelName[nCnt][0], pModelName);

			nIdx = nCnt;	// ID�ݒ�
			break;
		}
		else if (strcmp(&m_pModelName[nCnt][0], pModelName) == 0)
		{// ���ɐ�������Ă��郂�f���ƈ�v����
			nIdx = nCnt;	// ID�ݒ�
			break;
		}
	}
	return nIdx;	// ID��Ԃ�
}

LPD3DXBUFFER CModel::GetBuffMat(int nIdx)
{
	if (m_pModelList[nIdx].m_pBuffMat != nullptr)
	{
		return m_pModelList[nIdx].m_pBuffMat;
	}
	return nullptr;
}

DWORD CModel::GetNumMat(int nIdx)
{
	if (m_pModelList[nIdx].m_dwNumMat != NULL)
	{
		return m_pModelList[nIdx].m_dwNumMat;
	}
	return NULL;
}

LPD3DXMESH CModel::GetMesh(int nIdx)
{
	if (m_pModelList[nIdx].m_pMesh != nullptr)
	{
		return m_pModelList[nIdx].m_pMesh;
	}
	return nullptr;
}