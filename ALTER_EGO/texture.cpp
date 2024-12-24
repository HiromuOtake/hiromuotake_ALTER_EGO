//==============================================
//
// ALTER_EGO[texture.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "texture.h"

// �ÓI�����o������
LPD3DXBUFFER CTexture::m_pBuffMat = nullptr;
DWORD CTexture::m_dwNumMat = 0;

//==============================================
// �R���X�g���N�^
//==============================================
CTexture::CTexture() : m_pTextureList{}, m_pTextureName{}, m_nNumAll(0)
{
	for (int nCntTex = 0; nCntTex < m_MAXSENTENCE; nCntTex++)
	{
		for (int nCnt = 0; nCnt < m_MAXTEXTURE; nCnt++)
		{
			m_pTextureList[nCnt] = {};
			m_pTextureName[nCnt][nCntTex] = {};
			m_nNumAll = 0;
		}
	}
}

//==============================================
// �f�X�g���N�^
//==============================================
CTexture::~CTexture()
{

}

//==============================================
// �e�N�X�`���̔j��
//==============================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < m_MAXSENTENCE; nCnt++)
	{
		//�e�N�X�`����j��
		if (m_pTextureList[nCnt] != NULL)
		{
			m_pTextureList[nCnt]->Release();
			m_pTextureList[nCnt] = NULL;
		}
	}
}

//==============================================
// �e�N�X�`���̓o�^
//==============================================
int CTexture::Regist(const char* pTextureName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	for (int nCnt = 0; nCnt < m_MAXTEXTURE; nCnt++)
	{
		if (m_pTextureList[nCnt] == nullptr)
		{// �o�^����Ă��Ȃ�����

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pTextureName,
				&m_pTextureList[nCnt]);

			strcpy(&m_pTextureName[nCnt][0], pTextureName);

			nIdx = nCnt;	// ID�ݒ�
			m_nNumAll++;	// �e�N�X�`����
			break;
		}
		else if (strcmp(&m_pTextureName[nCnt][0], pTextureName) == 0)
		{// ���ɐ�������Ă���e�N�X�`���ƈ�v����
			nIdx = nCnt;	// ID�ݒ�
			break;
		}
	}
	return nIdx;	// ID��Ԃ�
}

LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx <= -1)
	{
		return nullptr;
	}
	else
	{
		return m_pTextureList[nIdx];
	}
}