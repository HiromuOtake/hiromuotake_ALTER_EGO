//==============================================
//
// ALTER_EGO[input.h]
// Author: hiromu otake
//
//==============================================

#ifndef   _INPUT_H_
#define   _INPUT_H_

#include "main.h"

//�}�N����`
#define JOYPAD_ZONE     (1)
#define JOYPAD_SPEED    (15)
#define MAX_KEY         (256)

class CInput
{
public:
    //�L�[�̎��
    typedef enum
    {
        JOYKEY_UP = 0,
        JOYKEY_DOWN,
        JOYKEY_LEFT,
        JOYKEY_RIGHT,
        JOYKEY_START,
        JOYKEY_BACK,
        JOYKEY_L3,
        JOYKEY_R3,
        JOYKEY_LB,
        JOYKEY_RB,
        JOYKEY_LT,
        JOYKEY_RT,
        JOYKEY_A,
        JOYKEY_B,
        JOYKEY_X,
        JOYKEY_Y,
        JOYKEY_MAX
    }JOYKEY;

    //�X�e�B�b�N�̔ԍ�
    typedef enum
    {
        STICKTYPE_LEFT = 0, // ���X�e�B�b�N
        STICKTYPE_RIGHT, // �E�X�e�B�b�N
        STICKTYPE_MAX
    }STICKTYPE;

    //�X�e�B�b�N�̕���
    typedef enum
    {
        STICKANGLE_UP = 0, // ��
        STICKANGLE_DOWN,   // ��
        STICKANGLE_LEFT,   // ��
        STICKANGLE_RIGHT,  // �E
        STICKANGLE_MAX,
    }STICKANGLE;

    //�X�e�B�b�N�̓��͏��
    typedef struct
    {
        float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
        float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
        bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
        bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
        bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
        bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
    }STICKINPUT;

    CInput();
    ~CInput();
    virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    virtual void Uninit();
    virtual void Update() = 0;
protected:
    static LPDIRECTINPUT8 m_pInput;
    LPDIRECTINPUTDEVICE8 m_pDevice;
};

class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit();
    void Update();
    bool GetPress(int nKey);    // �v���X��Ԏ擾
    bool GetTrigger(int nKey);   // �g���K�[��Ԏ擾
private:
    BYTE m_aKetStatePress[MAX_KEY];
    BYTE m_aKeyStateTrigger[MAX_KEY];
};

class CInputJoyPad : public CInput
{
public:
    CInputJoyPad();
    ~CInputJoyPad();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd);
    void Uninit();
    void Update();
    void UpdateStick(XINPUT_STATE GamePadState);
    bool GetJoyPadPress(JOYKEY nKey);    // �v���X��Ԏ擾
    bool GetJoyPadTrigger(JOYKEY nKey);   // �g���K�[��Ԏ擾
    float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
    WORD GetJoypadStick(SHORT sThumbx, SHORT sThumby, SHORT sDeaZone);
    STICKINPUT GetStick();
    XINPUT_STATE* GetXInputState();
private:
    BYTE m_aJoyPadStatePress[MAX_KEY];
    BYTE m_aJoyPadStateTrigger[MAX_KEY];
    WORD m_joykeyState;                                         //�W���C�p�b�h�̃v���X���
    WORD m_joyKeyStateTrigger; //�W���C�p�b�h�̃g���K�[���
    WORD m_joyKeyStateRepeat; //�W���C�p�b�h�̃��s�[�g���
    WORD m_ajoyKeyStateRelease; //�R���g���[���[�̃����[�X���
    WORD m_aJoypadCurrentTime; //�R���g���[���[�̌��݂̎���
    WORD m_aJoypadExecLastTime; //�R���g���[���[�̍Ō�ɐ^��Ԃ�������
    WORD m_JoypadInput; //�R���g���[���[�̓��͏��
    D3DXVECTOR3 m_joyStickPos; //�X�e�B�b�N�̌X��
    bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̓��͏��
    DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
    DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
    STICKINPUT m_stick; //�X�e�B�b�N�̓��͏��
    XINPUT_STATE m_XInput; //���͏��
    XINPUT_VIBRATION m_JoypadMotor;
    int m_nCntkey;
};



#endif