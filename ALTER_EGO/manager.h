//======================================================
//
// ALTER_EGO [manager.h]
// Auther : ��|�
//
//======================================================

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "light.h"
#include "object3D.h"
#include "texture.h"
#include "scene.h"
#include "fade.h"
#include "model.h"
#include "sound.h"

// �O���錾
class CParticleManager;

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenderere() { return m_pRnderer; }								// �����_���[�̎擾
	static CInputKeyboard* GetKeyboard() { return m_pKeyboard; }						// �L�[�{�[�h�̎擾
	static CInputJoyPad* GetJoyPad() { return m_pJoyPad; }								// �Q�[���p�b�h�̎擾
	static CLight* GetLight() { return m_pLight; }										// ���C�g�̎擾
	static CTexture* GetTexture() { return m_pTexture; }								// �e�N�X�`���̎擾
	static CModel* GetModel() { return m_pModel; }										// ���f���̎擾
	static CScene* GetScene() { return m_pScene; }										// �V�[���̎擾
	static CSound* GetSound() { return m_pSound; }										// �T�E���h�̎擾
	static CParticleManager* GetParticleManager() { return m_pParticleManager; }		// �p�[�e�B�N���}�l�[�W���[�̎擾
	static int& GetMode() { return m_nMode; }											// ���[�h�̎擾
	//static CFade* GetFade();
	static void SetMode(CScene::MODE mode);
	static void SetPaused(bool paused) { m_bPaused = paused; }
	static bool IsPaused() { return m_bPaused; }
	float GetDeltaTime() const { return m_deltaTime; }
private:
	static CRenderer* m_pRnderer;					// �����_���[���
	static CInputKeyboard* m_pKeyboard;				// �L�[�{�[�h���
	static CInputJoyPad* m_pJoyPad;					// �Q�[���p�b�h���
	static CLight* m_pLight;						// ���C�g���
	static CTexture* m_pTexture;					// �e�N�X�`�����
	static CModel* m_pModel;						// ���f�����
	static CScene* m_pScene;						// �V�[�����
	static CSound* m_pSound;						// �T�E���h���
	static CParticleManager* m_pParticleManager;	// �p�[�e�B�N���}�l�[�W���[���
	static int m_nMode;								// ��ʑJ�ڂ��Ǘ�����ÓI�����o
	LARGE_INTEGER m_frequency;						// �p�t�H�[�}���X���g��
	LARGE_INTEGER m_prevTime;						// �O��̃t���[������
	float m_deltaTime;								// �t���[���Ԃ̌o�ߎ���
	static bool m_bPaused;							// �|�[�Y��Ԃ��Ǘ�����ÓI�����o
	//static CFade* m_pFade;
};
#pragma once
