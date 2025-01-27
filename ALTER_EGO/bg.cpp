//==============================================
//
// ALTER_EGO[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "bg.h"
#include "texture.h"

//======================================================
// �R���X�g���N�^
//======================================================
CBg::CBg(int nPriority) : CObject2D(nPriority), m_pVtxBuff(nullptr), m_pTexture(nullptr), m_nTexIdx(0), m_texScrollSpeed01(0.0f), m_texScrollSpeed02(SCREEN_WIDTH)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CBg::~CBg()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CBg::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VTX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �T�C�Y���X�N���[���S�̂ɐݒ�
	CObject2D::SetWidthHeight((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	// �e�N�X�`���̏����ݒ�
	CObject2D::SetTexture(1.0f);
	// �����ɔz�u
	CObject2D::SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CBg::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject2D::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CBg::Update()
{
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// �w�i1�����Ɉړ�
		m_texScrollSpeed01 -= 2.0f;
		if (m_texScrollSpeed01 <= -SCREEN_WIDTH) // �w�i1����ʊO�ɏo���烊�Z�b�g
		{
			m_texScrollSpeed01 = SCREEN_WIDTH;
		}

		// �w�i2�����Ɉړ�
		m_texScrollSpeed02 -= 1.0f;
		if (m_texScrollSpeed02 <= -SCREEN_WIDTH) // �w�i2����ʊO�ɏo���烊�Z�b�g
		{
			m_texScrollSpeed02 = SCREEN_WIDTH;
		}

		// �w�i1�Ɣw�i2�̈ʒu��ݒ�
		SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + m_texScrollSpeed01, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	CObject2D::Update();
}

//======================================================
// �`�揈��
//======================================================
void CBg::Draw()
{
	CObject2D::Draw();
}

void CBg::DrawTexture(int textureID, D3DXVECTOR2 position, D3DXVECTOR2 scale, float alpha)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();
	if (!pDevice) return;

	// �e�N�X�`���̃A�h���X���擾
	LPDIRECT3DTEXTURE9 pTexture = CManager::GetTexture()->GetAddress(textureID);
	if (!pTexture) return;

	// �e�N�X�`���̕��ƍ������擾
	D3DSURFACE_DESC desc;
	if (FAILED(pTexture->GetLevelDesc(0, &desc))) return;
	float texWidth = static_cast<float>(desc.Width);
	float texHeight = static_cast<float>(desc.Height);

	// ���_�f�[�^�̐ݒ�
	VTX_2D vertices[4];
	float width = texWidth * scale.x;
	float height = texHeight * scale.y;

	vertices[0] = { { position.x, position.y, 0.0f }, 1.0f, 0.0f, 0.0f, alpha };
	vertices[1] = { { position.x + width, position.y, 0.0f }, 1.0f, 1.0f, 0.0f, alpha };
	vertices[2] = { { position.x, position.y + height, 0.0f }, 1.0f, 0.0f, 1.0f, alpha };
	vertices[3] = { { position.x + width, position.y + height, 0.0f }, 1.0f, 1.0f, 1.0f, alpha };

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pDevice->CreateVertexBuffer(sizeof(vertices), 0, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pVtxBuff, NULL);
	void* pVertices;
	pVtxBuff->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	pVtxBuff->Unlock();

	// ���e�s��ݒ�
	D3DXMATRIX matOrtho;
	D3DXMatrixOrthoLH(&matOrtho, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);

	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	pDevice->SetTransform(D3DTS_VIEW, &matView);

	// �`��ݒ�
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VTX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetTexture(0, pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �`���̐ݒ蕜��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pVtxBuff->Release(); // ���_�o�b�t�@�����
}

//=====================================================
// �w�i�̐���
//=====================================================
CBg* CBg::Create(CScene::MODE mode)
{
	CBg* pBg = new CBg;
	
	int nId = 0;

	if (pBg != nullptr)
	{
		switch (mode)
		{
		case CScene::MODE::MODE_TITLE:
			nId = CManager::GetTexture()->Regist("data\\Texture\\titlelogo.png");
			break;

		case CScene::MODE::MODE_STAGESELECT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\selectstageBG.png");
			break;

		case CScene::MODE::MODE_TUTORIAL1:
			nId = CManager::GetTexture()->Regist("data\\Texture\\tutorial01.png");
			break;

		case CScene::MODE::MODE_TUTORIAL2:
			nId = CManager::GetTexture()->Regist("data\\Texture\\tutorial02.png");
			break;

		case CScene::MODE::MODE_GAME:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game001.png");
			break;

		case CScene::MODE::MODE_RESULT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\result.png");
			break;

		default:
			break;
		}

		if (nId == -1)
		{
			OutputDebugStringA("�e�N�X�`���̃��[�h�Ɏ��s���܂����B\n");
			delete pBg;
			return nullptr;
		}
		else
		{
			char debugMessage[256];
			sprintf(debugMessage, "�e�N�X�`�����[�h����: ID = %d\n", nId);
			OutputDebugStringA(debugMessage);
		}

		pBg->SetType(TYPE_BG);
		pBg->BindTexture(CManager::GetTexture()->GetAddress(nId));
		pBg->Init();
		pBg->SetUseDeath(true);
	}
	return  pBg;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBg::SetDeath()
{
	CObject::SetDeath();
}