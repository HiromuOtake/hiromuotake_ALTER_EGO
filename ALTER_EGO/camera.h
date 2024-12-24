//==============================================
//
// ALTER_EGO[camera.h]
// Author: hiromu otake
//
//==============================================

#ifndef  _CAMERA_H_
#define  _CAMERA_H_

#include "manager.h"
#include "object.h"

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();									// �J�����̐ݒ�
	void SetShake(int nShakeTime, float fShakePower);	// �h��̐ݒ�
	static D3DXVECTOR3* GetRot();
	static CCamera* Create();
	static constexpr float m_CAMERAPOS_X = 950.0f;
	static constexpr float m_CAMERAPOS_Y = 550.0f;
	static constexpr float m_CAMERAPOS_Z = 100.0f;
	static constexpr float m_CORRECTIOM_WIDTH = 1.564f;
	static constexpr float m_CORRECTIOM_HEIGHT = 1.67f;
	//static constexpr float m_CAMERAPOS_X = 850.0f;
	//static constexpr float m_CAMERAPOS_Y = 450.0f;
	//static constexpr float m_CAMERAPOS_Z = 100.0f;
	//static constexpr float m_CORRECTIOM_WIDTH = 1.405f;
	//static constexpr float m_CORRECTIOM_HEIGHT = 1.39f;
private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	static D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;		// �r���[�s��
	//int m_nShakeTime;
	//float m_fShakePower;
	bool m_bCameraChanger;
	CInputKeyboard* m_Keyboard;
};

#endif
