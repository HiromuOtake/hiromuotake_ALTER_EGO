////==============================================
////
//// ALTER_EGO[fade.cpp]
//// Author: hiromu otake
////
////==============================================
//
//#include "manager.h"
//#include "fade.h"
//#include <cassert>
//
//// �ÓI�����o������
//LPDIRECT3DTEXTURE9 CFade::m_pTextureTemp = nullptr;
//
////======================================================
//// �R���X�g���N�^
////======================================================
//CFade::CFade(int nPriority) : CObject2D(nPriority)
//{
//	m_Fade = FADE_NONE;
//	m_colorFade = 0.0f;
//}
//
////======================================================
//// �f�X�g���N�^
////======================================================
//CFade::~CFade()
//{
//
//}
//
////======================================================
//// �����ݒ�
////======================================================
//HRESULT CFade::Init()
//{
//	CObject2D::SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
//
//	CObject2D::Init();
//
//	m_Fade = FADE_NONE;
//
//	return S_OK;
//}
//
////======================================================
//// �I������
////======================================================
//void CFade::Uninit()
//{
//
//}
//
////======================================================
//// �X�V����
////======================================================
//void CFade::Update()
//{
//	if (m_Fade != FADE_NONE)
//	{
//		if (m_Fade == FADE_IN)
//		{//�t�F�[�h�C�����
//			m_colorFade -= 0.03f;          //�|���S���𓧖��ɂ��Ă���
//			CObject2D::SetColor(m_colorFade);
//
//			if (m_colorFade <= 0.0f)
//			{
//				m_colorFade = 0.0f;
//				CObject2D::SetColor(m_colorFade);
//				m_Fade = FADE_NONE;     //�������Ă��Ȃ���Ԃ�
//				SetDeath();
//				SetUseDeath(false);
//			}
//		}
//
//		else if (m_Fade == FADE_OUT)
//		{//�t�F�[�h�A�E�g���
//			m_colorFade += 0.03f;          //�|���S����s�����ɂ��Ă���
//			CObject2D::SetColor(m_colorFade);
//
//			if (m_colorFade >= 1.0f)
//			{
//				m_colorFade = 1.0f;
//				CObject2D::SetColor(m_colorFade);
//				m_Fade = FADE_IN;      //�t�F�[�h�C����Ԃ�
//
//				//���[�h�ݒ�(���̉�ʂɈڍs)
//				CManager::SetMode(m_fademode);
//				return;
//			}
//		}
//	}
//
//	//CObject2D::Update();
//}
//
////======================================================
//// �`�揈��
////======================================================
//void CFade::Draw()
//{
//	CObject2D::Draw();
//}
//
////=====================================================
//// �t�F�[�h�̐���
////=====================================================
//CFade* CFade::Create(CScene::MODE mode)
//{
//	CFade* pFade = new CFade;
//
//	if (pFade != nullptr)
//	{
//		pFade->SetType(TYPE_FIELD);
//		pFade->Init();
//	}
//	return  pFade;
//}
//
////==============================================
////�t�F�[�h��ʂ̐ݒ菈��
////==============================================
//void CFade::SetFade(FADE fade, CScene::MODE modeNext)
//{
//	m_fademode = modeNext;
//	m_Fade = fade;
//
//	if (fade == FADE::FADE_IN)
//	{
//		m_colorFade = 1.0f;
//	}
//	else if(fade == FADE::FADE_OUT)
//	{
//		m_colorFade = 0.0f;
//	}
//	else
//	{
//		assert(false && "�C�����A�E�g�Őݒ肵�Ă�������");
//	}
//	SetColor(m_colorFade);
//}
//
////==============================================
////�t�F�[�h��ʂ̎擾
////==============================================
//CFade::FADE CFade::GetFade(void)
//{
//	return m_Fade;
//}
//
////==============================================
////�t�F�[�h��ʂ̐F�̎擾
////==============================================
//float CFade::FadeColor(void)
//{
//	return m_colorFade;
//}
