////==============================================
////
////ALTER_EGO[ranking.h]
////Author: hiromu otake
////
////==============================================
//
//#ifndef  _RANKING_H_
//#define  _RANKING_H_
//
//#include "manager.h"
//#include "scene.h"
//#include "object3D.h"
//
////#define NUM_RANK     (2)
//
//class CRanking : public CScene
//{
//public:
//	typedef struct
//	{
//		D3DXVECTOR3 pos;     //�ʒu
//		int nScore;          //�X�R�A
//		int nScorePos;		//�e�N�X�`���̈ʒu
//		bool bRight;		//�V���������N�C�������ꍇ�_��������
//	}RankScore;
//
//	// ��ʂ̎��
//	typedef enum
//	{
//		MODE_TITLE = 0,
//		MODE_TYUTORIAL,
//		MODE_GAME,
//		MODE_RESULT,
//		MODE_MAX,
//	}MODE;
//	CRanking();							// �R���X�g���N�^
//	~CRanking()override;					// �f�X�g���N�^
//	HRESULT Init()override;				// �����ݒ�
//	void Uninit()override;				// �I������
//	void Update()override;				// �X�V����
//	void Draw()override;				// �`�揈��
//	void ResetRanking();
//	void SetRanking(int nScore);
//	static const int m_RANK = 1;
//	static const int m_NUMBER = 8;
//	static constexpr float m_RANK_WIDTH = 50.0f;
//	static constexpr float m_RANK_HEIGHT = 50.0f;
//private:
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
//	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
//	RankScore m_aRankScore[m_RANK][m_NUMBER];       //�����L���O�X�R�A���
//	int m_nRnkUpdate = -1;                             //�X�V�����NNo
//	int m_nTimerRanking;                               //�����L���O��ʕ\���^�C�}�[
//};
//
//#endif 
