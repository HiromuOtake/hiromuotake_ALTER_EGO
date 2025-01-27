//==============================================
//
// ALTER_EGO[title.cpp]
// Author: hiromu otake
//
//==============================================

#include "title.h"
#include "bg.h"
#include "block.h"
#include <sstream>
#include <fstream>

//�ÓI�����o������
CPlayer* CTitle::m_pPlayer = nullptr;
CCamera* CTitle::m_pCamera = nullptr;

//======================================================
// �R���X�g���N�^
//======================================================
CTitle::CTitle() : m_pBg(nullptr), m_nType{}
{
	for (int nCntBeside = 0; nCntBeside < m_BLOCK_BESIDE; nCntBeside++)
	{
		for (int nCntVertical = 0; nCntVertical < m_BLOCK_VERTICAL; nCntVertical++)
		{
			m_nType[nCntBeside][nCntVertical] = {};
		}
	}
}

//======================================================
// �f�X�g���N�^
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CTitle::Init()
{
	CScene::Init();

	// �w�i���쐬
	m_pBg = CBg::Create(CScene::MODE::MODE_TITLE);	
	assert(m_pBg && "�w�i�̍쐬�Ɏ��s���܂����I");

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	m_pCamera = CCamera::Create();

	std::string filename;

	filename = "data\\Stage\\SetStageTitle.txt";

	std::ifstream ifs(filename);
	if (!ifs)
	{
		assert(false && "�X�e�[�W�t�@�C�����J���܂���ł����I");
		return E_FAIL;
	}
	int x = 0, y = 0;	// ���A�c

	// �� 1 �s�ǂݎ�� (���s�R�[�h�܂œǂݍ���)
	std::string n;
	while (std::getline(ifs, n, '\n'))
	{
		std::stringstream ss_n(n);
		std::string t;

		while (std::getline(ss_n, t, '\t'))
		{
			std::stringstream ss_t(t);
			std::vector<std::string> v;
			std::string pair;

			// �u_�v ��؂�œǂݍ���
			while (std::getline(ss_t, pair, '_'))
			{
				v.push_back(pair);
			}

			int type = std::stoi(v[0]);

			if (type == 100)
			{
				m_pPlayer = CPlayer::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f));
			}
			else if (type == 1)
			{
				CBlock::Create(D3DXVECTOR3(x * BLOCK_WIDTH, -y * BLOCK_HEIGHT, 0.0f), CBlock::BLOCK::BLOCK_NORMAL);
			}
			else
			{

			}
			x++;
		}
		x = 0;
		y++;
	}
	return S_OK;

}

//======================================================
// �I������
//======================================================
void CTitle::Uninit()
{
	m_pCamera->Uninit();
	delete m_pCamera;
	m_pCamera = nullptr;

	m_pPlayer->SetUseDeath(true);
	m_pPlayer->SetDeath();
	m_pPlayer = nullptr;

	// �w�i�̉��
	if (m_pBg)
	{
		m_pBg->SetDeath();
		m_pBg = nullptr;
	}

	CScene::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CTitle::Update()
{
	m_pCamera->Update();

	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CTitle::Draw()
{
	//LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//CRenderer* pRenderer = CManager::GetRenderere();

	////�f�o�C�X�̎擾
	//pDevice = pRenderer->GetDevice();

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexture);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// �J�����擾
//======================================================
CCamera* CTitle::GetCamera()
{
	return m_pCamera;
}