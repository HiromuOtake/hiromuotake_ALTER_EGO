//======================================================
//
// ALTER_EGO [manager.cpp]
// Auther : ��|�
//
//======================================================

#include "manager.h"
#include "item.h"
#include "player.h"
#include "particlemanager.h"

// �ÓI�����o������
CRenderer* CManager::m_pRnderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CInputJoyPad* CManager::m_pJoyPad = nullptr;
CLight* CManager::m_pLight = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CModel* CManager::m_pModel = nullptr;
CScene* CManager::m_pScene = nullptr;
CSound* CManager::m_pSound = nullptr;
CParticleManager* CManager::m_pParticleManager = nullptr;
int CManager::m_nMode = 0;
std::string CManager::m_nextStageFile = "";
CScene::MODE CManager::m_nextSceneMode = CScene::MODE_TITLE;
bool CManager::m_bPaused = false;
//CFade* CManager::m_pFade = nullptr;

//======================================================
// �R���X�g���N�^
//======================================================
CManager::CManager()
{
	
}

//======================================================
// �f�X�g���N�^
//======================================================
CManager::~CManager()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	m_pRnderer = new CRenderer();
	m_pRnderer->Init(hWnd, bWindow);

	// �L�[�{�[�h�̐���
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	// �Q�[���p�b�h�̐���
	m_pJoyPad = new CInputJoyPad();
	m_pJoyPad->Init(hInstance, hWnd);

	// ���C�g����
	m_pLight = new CLight();
	m_pLight->Init();

	// �e�N�X�`������
	m_pTexture = new CTexture();

	// ���f������
	m_pModel = new CModel();

	// �T�E���h����
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	// �p�[�e�B�N���}�l�[�W���[����
	m_pParticleManager = new CParticleManager();
	m_pParticleManager->Init();

	// ����
	m_pScene = CScene::Create(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CManager::Uninit ()
{
	CObject::ReleaseAll();	// �S�I�u�W�F�N�g�̉��

	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Uninit();
		delete m_pRnderer;
		m_pRnderer = nullptr;
	}
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Uninit();
		delete m_pParticleManager;
		m_pParticleManager = nullptr;
	}

	CObject::DeleateProcess();

	//if (m_pFade != nullptr)
	//{
	//	m_pFade->Uninit();
	//	delete m_pFade;
	//	m_pFade = nullptr;
	//}
}

//======================================================
// �X�V����
//======================================================
void CManager::Update()
{
	m_nMode = (int)m_pScene->GetMode();

	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Update();
	}
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Update();
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Update();
	}

	bool& pPlayer = CPlayer::GetGoal();

	if (m_nMode == (int)CScene::MODE::MODE_GAME)
	{
		if (m_pKeyboard->GetTrigger(DIK_K) || m_pJoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
		{
			CManager::SetPaused(true); // �|�[�Y��L����
		}

		return;
	}
	else
	{
		if (m_pKeyboard->GetTrigger(DIK_RETURN) == true || pPlayer == false || (m_pJoyPad->GetJoyPadTrigger(CInput::JOYKEY_START) == true ))
		{
			m_nMode++;

			if (m_nMode >= (int)CScene::MODE::MODE_MAX)
			{
				m_nMode = 1;
			}
			SetMode(static_cast<CScene::MODE>(m_nMode));
		}
	}
}

//======================================================
// �`�揈��
//======================================================
void CManager::Draw()
{
	if (m_pRnderer != nullptr)
	{
		m_pRnderer->Draw();
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->Draw();
	}
}

////======================================================
//// �V�[���擾
////======================================================
//CFade* CManager::GetFade()
//{
//	return /*m_pFade*/nullptr;
//}

//======================================================
// ���[�h�ݒ�
//======================================================
void CManager::SetMode(CScene::MODE mode)
{
	//if (m_pFade == nullptr)
	//{
	//	// ����
	//	//m_pFade = CFade::Create(mode);
	//}

	CObject::ReleaseAll();

	//�I������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	
	//m_pFade->SetFade(CFade::FADE::FADE_IN, mode);

	// ����
	m_pScene = CScene::Create(mode);

	// ����
	//CFade::Create(mode)->SetFade(CFade::FADE::FADE_IN, mode);
}