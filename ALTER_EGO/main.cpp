//======================================================
//
// ALTER_EGO [main.cpp]
// Auther : ��|�
//
//======================================================

#include "main.h"
#include "manager.h"

// �O���[�o���ϐ�
CManager* g_pManager = nullptr;
int g_nCntFPS = 0;
bool g_isFullscreen = false;			// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;

//=================
//���C���֐�
//=================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef FIND_MEM_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),								//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,										//�E�B���h�E�̃X�^�C��
		WindowProc,										//�E�B���h�E�v���V�[�W��
		0,												// 0 �ɂ���(�ʏ�͎g�p���Ȃ�)
		0,												//��Ɠ���
		hInstance,										//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),					//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),						//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),						//�N���C�A���g�̈�̔w�i�F
		NULL,											//���j���[�o�[
		CLASS_NAME,										//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),					//�t�@�C���̃A�C�R��
	};

	HWND hWnd;			//�E�B���h�E�n���h��(���ʎq)
	MSG  msg;			//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,			//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,					//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),		//�E�B���h�E�̕�
		(rect.bottom - rect.top),		//�E�B���h�E�̍���
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��̓E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�쐬�f�[�^

	// ������������
	g_pManager = new CManager();		// �����_���[����
	g_pManager->Init(hInstance, hWnd, TRUE);

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W�փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DorectX�̏���
			//�X�V����
			g_pManager->Update();
			//�`�揈��
			g_pManager->Draw();
		}
	}
	//�I������
	g_pManager->Uninit();
	delete g_pManager;


	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//======================================
//�E�B���h�E�v���V�[�W��
//======================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;   //�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:			//�E�B���h�E�j��
		//WM_OUIT ���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_CLOSE:				//����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j�󂷂�
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;			//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_KEYDOWN:			//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:			//[ESK]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j�󂷂�
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//����̏�����Ԃ�
}

//=========================================
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//=========================================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}