//==============================================
//
//ALTER_EGO[modelparts.cpp]
//Author: hiromu otake
//
//==============================================

#include "modelparts.h"
#include "model.h"
#include "manager.h"
#include "objectX.h"

//==============================================
// �R���X�g���N�^
//==============================================
CModelParts::CModelParts() : m_pos{ 0.0f,0.0f,0.0f }, m_rot{ 0.0f,0.0f,0.0f },m_min{ 0.0f,0.0f,0.0f }, m_max{ 0.0f,0.0f,0.0f }, m_size{ 0.0f,0.0f,0.0f }
, m_pParent(nullptr), m_pMesh(nullptr), m_pVtxBuff(nullptr), m_nNumVtx(0), m_sizeFVF(0), m_nIdx(0), m_nIdxParents(0), m_nModelIdx(0), m_nNumAll(0), m_pModelList{}, m_pModelName{}
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CModelParts::~CModelParts()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CModelParts::Init()
{
	return S_OK;
}

//==============================================
// �I������
//==============================================
void CModelParts::Uninit()
{
	delete this;
}

//==============================================
// �X�V����
//==============================================
void CModelParts::Update()
{

}

//==============================================
// �`�揈��
//==============================================
void CModelParts::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							//�f�o�C�X�ւ̃|�C���^
	CRenderer* pRenderer = CManager::GetRenderere();
	pDevice = pRenderer->GetDevice();					//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

	D3DXMATRIX mtxParent;								// �e�̍s����擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		// �e�̃��[���h�ϊ��s����擾
		mtxParent = m_pParent->GetWoarldMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pModelList->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModelList->m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);

		//���f��(�p�[�c)�̕`��
		m_pModelList->m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//======================================================
// �e�N�X�`������
//======================================================
void CModelParts::BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh)
{
	m_pModelList->m_pBuffMat = BuffMat;
	m_pModelList->m_dwNumMat = dwNumMat;
	m_pModelList->m_pMesh = Mesh;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_���̎擾
	m_nNumVtx = Mesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_sizeFVF = D3DXGetFVFVertexSize(Mesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;

		if (vtx.x < m_min.x)
		{
			m_min.x = vtx.x;
		}
		else if (vtx.x > m_max.x)
		{
			m_max.x = vtx.x;
		}

		if (vtx.y < m_min.y)
		{
			m_min.y = vtx.y;
		}
		else if (vtx.y > m_max.y)
		{
			m_max.y = vtx.y;
		}

		if (vtx.z < m_min.z)
		{
			m_min.z = vtx.z;
		}
		else if (vtx.z > m_max.z)
		{
			m_max.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���̃|�C���^��i�߂�
		m_pVtxBuff += m_sizeFVF;
	}

	m_size = m_max - m_min;

	//���_�o�b�t�@�̃A�����b�N
	Mesh->UnlockVertexBuffer();

}

//==============================================
// ���f���o�^
//==============================================
int CModelParts::Regist(const char* pModelName)
{
	int nIdx = 0;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	for (int nCnt = 0; nCnt < m_NUM_MODEL_PARTS; nCnt++)
	{
		if (m_pModelList[nCnt].m_bUse == true)
		{
			continue;
		}

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

			m_pModelList[nCnt].m_bUse = true;
			break;
		}
	}
	return nIdx;	// ID��Ԃ�
}

//=====================================
// ���f���p�[�c�̐���
//=====================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char* aModel)
{
	CModelParts* pModelParts = new CModelParts;

	pModelParts->Init();

	pModelParts->m_pos = pos;
	pModelParts->m_rot = rot;

	CModel* pModel = CManager::GetModel();

	pModelParts->BindModel(pModel->GetBuffMat(pModel->Regist(aModel)),
		pModel->GetNumMat(pModel->Regist(aModel)),
		pModel->GetMesh(pModel->Regist(aModel)));

	return pModelParts;
}

//=====================================
// �e�̐ݒ�
//=====================================
void CModelParts::SetParent(CModelParts* pModelParts)
{
	if (m_pParent == nullptr)
	{
		m_pParent = pModelParts;
	}
}

//=====================================
// �e�̃��[���h�}�g���b�N�X���擾
//=====================================
D3DXMATRIX CModelParts::GetWoarldMatrix()
{
	return m_mtxWorld;
}

//======================================================
// �傫���̎擾
//======================================================
D3DXVECTOR3& CModelParts::GetPos()
{
	return m_pos;
}

//======================================================
// �傫���̎擾
//======================================================
D3DXVECTOR3& CModelParts::GetSize()
{
	return m_size;
}

//======================================================
// �ŏ��̎擾
//======================================================
D3DXVECTOR3& CModelParts::GetMin()
{
	return m_min;
}

//======================================================
// �ő�̎擾
//======================================================
D3DXVECTOR3& CModelParts::GetMax()
{
	return m_max;
}

//======================================================
// �p�[�c��
//======================================================
int& CModelParts::GetIdx()
{
	return m_nIdx;
}
