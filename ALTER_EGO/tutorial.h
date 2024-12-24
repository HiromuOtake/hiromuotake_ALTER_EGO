////==============================================
////
//// ALTER_EGO[tutorial.h]
//// Author: hiromu otake
////
////==============================================
//
//#include "manager.h"
//#include "scene.h"
//#include "player.h"
//#include "camera.h"
//#include "item.h"
//
//class CTutorial : public CScene
//{
//public:
//	// ��ʂ̎��
//	typedef enum
//	{
//		MODE_TITLE = 0,
//		MODE_TUTORIAL,
//		MODE_GAME,
//		MODE_RESULT,
//		MODE_MAX,
//	}MODE;
//	CTutorial();							// �R���X�g���N�^
//	~CTutorial()override;					// �f�X�g���N�^
//	HRESULT Init()override;				// �����ݒ�
//	void Uninit()override;				// �I������
//	void Update()override;				// �X�V����
//	void Draw()override;				// �`�揈��
//	static CPlayer* GetPlayer();
//	static CCamera* GetCamera();
//	static const int m_BLOCK_BESIDE = 30;
//	static const int m_BLOCK_VERTICAL = 15;
//private:
//	static CPlayer* m_pPlayer;
//	static CItem* m_pItem;
//	static CCamera* m_pCamera;
//	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
//};
//
//#pragma once
