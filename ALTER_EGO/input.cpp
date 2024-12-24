//==============================================
//
// ALTER_EGO[input.cpp]
// Author: hiromu otake
//
//==============================================

#include "input.h"

// �ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
// �R���X�g���N�^
//============================
CInput::CInput() : m_pDevice(nullptr)
{

}

//============================
// �f�X�g���N�^
//============================
CInput::~CInput()
{

}

//============================
// ����������
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================
// �I������
//============================
void CInput::Uninit()
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();      //�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//============================
// �X�V����
//============================
void CInput::Update()
{

}

//============================
// �L�[�{�[�h�̃R���X�g���N�^
//============================
CInputKeyboard::CInputKeyboard() : m_aKeyStateTrigger(), m_aKetStatePress()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		m_aKeyStateTrigger[i] = NULL;
		m_aKetStatePress[i] = NULL;
	}
}

//============================
// �L�[�{�[�h�̃f�X�g���N�^
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
// �L�[�{�[�h�̏���������
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
// �L�[�{�[�h�̏I������
//============================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//============================
// �L�[�{�[�h�̍X�V����
//============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];     //�L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
		{
			m_aKeyStateTrigger[nCnt] = (m_aKetStatePress[nCnt] ^ aKeyState[nCnt]) & aKeyState[nCnt];
			m_aKetStatePress[nCnt] = aKeyState[nCnt];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=================================
// �L�[�{�[�h�̃v���X�����擾
//=================================
bool CInputKeyboard::GetPress(int nKey)
{
	return((m_aKetStatePress[nKey] & 0x80) != 0) ? true : false;
	return(m_aKetStatePress[nKey] & 0x80) != 0;
}

//=================================
// �L�[�{�[�h�̃g���K�[�����擾
//=================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//============================
// �L�[�{�[�h�̃R���X�g���N�^
//============================
CInputJoyPad::CInputJoyPad() : m_aJoyPadStatePress(), m_aJoyPadStateTrigger()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		m_aJoyPadStatePress[i] = NULL;
		m_aJoyPadStateTrigger[i] = NULL;
	}
}

//============================
// �L�[�{�[�h�̃f�X�g���N�^
//============================
CInputJoyPad::~CInputJoyPad()
{

}

//============================
// �L�[�{�[�h�̏���������
//============================
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//============================
// �L�[�{�[�h�̏I������
//============================
void CInputJoyPad::Uninit()
{
	CInput::Uninit();
}

//=============================================
// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
//=============================================
WORD CInputJoyPad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

void CInputJoyPad::UpdateStick(XINPUT_STATE GamePadState)
{
	//�L�[�{�[�h�̏�Ԃ��擾
	if (XInputGetState(0, &GamePadState) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			float fX, fY; //�X�e�B�b�N��X���AY��

			switch (nCntStick)
			{
			case STICKTYPE_LEFT:
				fX = GamePadState.Gamepad.sThumbLX;
				fY = GamePadState.Gamepad.sThumbLY;
				break;
			case STICKTYPE_RIGHT:
				fX = GamePadState.Gamepad.sThumbRX;
				fY = GamePadState.Gamepad.sThumbRY;
				break;
			}

			//�p�x���擾
			m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

			//�X�e�B�b�N�̓|������擾
			m_stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				m_stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			m_stick.afTplDiameter[nCntStick] /= 32768.0f; //�|���Ă����Ԃ̏����l

			//�������̓t���O��������
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				m_bAngle[nCntStick][nCntAngle] = false;
			}

			if (m_stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
				if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}

				//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}
			}

			//�p�x�ɉ��������͏���
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//�X�e�B�b�N�̃g���K�[����ۑ�
				m_stick.abAngleTrigger[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

				//�X�e�B�b�N�̃����[�X����ۑ�
				m_stick.abAngleRelease[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & ~m_bAngle[nCntStick][nCntAngle];

				//���݂̎��Ԃ��擾
				m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
				{
					//�Ō�ɐ^��Ԃ������Ԃ�ۑ�
					m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];

					//�X�e�B�b�N�̃��s�[�g����ۑ�
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//�X�e�B�b�N�̃��s�[�g����ۑ�
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//�X�e�B�b�N�̃v���X����ۑ�
				m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//=================================
//�W���C�p�b�h�̍X�V����
//=================================
void CInputJoyPad::Update()
{
	XINPUT_STATE joykeyState;     //�W���C�p�b�h�̓��͏��

	    //�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
		{
			UpdateStick(joykeyState);
			WORD Button = joykeyState.Gamepad.wButtons;
			WORD OldButton = m_joykeyState;
			m_joyKeyStateTrigger = Button & ~OldButton;    // �g���K�[����
			m_ajoyKeyStateRelease = ~Button & OldButton;    // �����[�X����
			joykeyState.Gamepad.wButtons |= GetJoypadStick(joykeyState.Gamepad.sThumbLX, joykeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

			// ���݂̎��Ԃ��擾����
			m_aJoypadCurrentTime = (WORD)timeGetTime();

			if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime - m_aJoypadExecLastTime) > JOYPAD_SPEED))
			{
				// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aJoypadExecLastTime = m_aJoypadCurrentTime;

				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_joyKeyStateRepeat = joykeyState.Gamepad.wButtons;
			}
			else
			{
				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_joyKeyStateRepeat = 0;
			}
			m_joykeyState = joykeyState.Gamepad.wButtons;                // �v���X����
		}
}

//2�_�̊p�x�����߂�
float CInputJoyPad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //�p�x

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

//=====================================
// �R���g���[���[�̓��͏��̎擾
//=====================================
XINPUT_STATE* CInputJoyPad::GetXInputState(void)
{
	return &m_XInput;
}

//=====================================
// �X�e�B�b�N�̓��͏����擾
//=====================================
CInputJoyPad::STICKINPUT CInputJoyPad::GetStick(void)
{
	return m_stick;
}

//=====================================
//�W���C�p�b�h�̃v���X�����擾
//=====================================
bool CInputJoyPad::GetJoyPadPress(JOYKEY key)
{
	return (m_joykeyState & (0x01 << key)) ? true : false;
}

//=====================================
//�W���C�p�b�h�̃g���K�[�����擾
//=====================================
bool CInputJoyPad::GetJoyPadTrigger(JOYKEY key)
{
	return (m_joyKeyStateTrigger & (0x01 << key)) ? true : false;
}
