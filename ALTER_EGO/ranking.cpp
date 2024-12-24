////==============================================
////
////ALTER_EGO[ranking.cpp]
////Author: hiromu otake
////
////==============================================
//
//#include "main.h"
//#include "ranking.h"
//#include "input.h"
//#include "fade.h"
//#include "result.h"
//#include "score.h"
//#include "sound.h"
//#include "bg.h"
//#include <stdio.h>
//#include <string.h>
//
////=====================================================
//// �R���X�g���N�^
////======================================================
//CRanking::CRanking() : m_pTexture(nullptr), m_pVtxBuff(nullptr)
//{
//
//}
//
////======================================================
//// �f�X�g���N�^
////======================================================
//CRanking::~CRanking()
//{
//
//}
//
////==========================================
////�����L���O�̏���������
////==========================================
//
//HRESULT CRanking::Init()
//{
//	CScene::Init();
//
//	CBg::Create(CScene::MODE::MODE_TITLE, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
//
//	CSound* pSound = CManager::GetSound();
//
//	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM001);
//
//	return S_OK;
//}
//
////==========================================
////�����L���O�̏I������
////==========================================
//
//void UninitRanking(void)
//{
//	UninitRankingBG();
//	UninitRankingA();
//	UninitRankingRank();
//
//	//�e�N�X�`����j��
//	if (g_TextureRank != NULL)
//	{
//		g_TextureRank->Release();
//		g_TextureRank = NULL;
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffRank != NULL)
//	{
//		g_pVtxBuffRank->Release();
//		g_pVtxBuffRank = NULL;
//	}
//
//	StopSound();
//}
//
////==========================================
////�����L���O�̍X�V����
////==========================================
//
//void UpdateRanking(void)
//{
//	g_nTimerRanking++;	//�����L���O��_�������鎞�Ԃ̍X�V
//
//	//���_���̃|�C���^
//	VERTEX_2D* pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	int nCntRank = 0;
//	int nCntNumber = 0;
//
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{//ENTER�L�[�������ꂽ
//		//���[�h�ݒ�(�Q�[����ʂɈڍs)
//		SetFade(MODE_TITLE);
//	}
//
//	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
//	{
//		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
//		{
//			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x - RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y - RANK_HEIGHT, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x + RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y - RANK_HEIGHT, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x - RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y + RANK_HEIGHT, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntNumber].pos.x + RANK_WIDTH, g_aRankScore[nCntRank][nCntNumber].pos.y + RANK_HEIGHT, 0.0f);
//
//
//			if (g_aRankScore[nCntRank][nCntNumber].bRight == true)
//			{
//				if (g_nTimerRanking % 1 == 0)
//				{//�Ԃ�����
//					//���_�J���[�̐ݒ�
//					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
//					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
//					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
//					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.6f, 1.0f);
//				}
//				else
//				{//���ɖ߂�
//					//���_�J���[�̐ݒ�
//					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//				}
//			}
//			pVtx += 4;
//		}
//	}
//	//���_�o�b�t�@�̃A�����b�N
//	g_pVtxBuffRank->Unlock();
//}
//
////=======================================================================
////�����L���O�̕`�揈��
////=======================================================================
//
//void DrawRanking(void)
//{
//	DrawRankingBG();
//	DrawRankingA();
//	DrawRankingRank();
//
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntRank = 0;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
//
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_NUMBER; nCntRank++)
//	{
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, g_TextureRank);
//
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);
//
//	}
//}
//
////==========================================
////�����L���O�̃��Z�b�g
////==========================================
//
//void ResetRanking(void)
//{
//	int nCntRank; //�����J�E���g����(����)
//	int nCntNumber;	//�����J�E���g����(����)
//
//	//�����L���O�̏��̏�����
//	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
//	{
//		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
//		{
//			g_aRankScore[nCntRank][nCntNumber].nScore = 0;                       //�g�p���Ă��Ȃ����
//		}
//	}
//}
//
////==========================================
////�����L���O�̐ݒ�
////==========================================
//
//void SetRanking(int nScore)
//{
//	//���_���̃|�C���^
//	VERTEX_2D* pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
//
//	FILE* pFile;
//
//	int nCnt = 0;
//	int nCntRank = 0;
//	int nCntNumber = 0;	//����
//
//	int nCntData = 0;	//�v�f1�̏��
//	int nAddRank = 0;	//����̃X�R�A
//	int nCopyData = 0;	//�f�[�^�̎󂯎M
//	int nData[MAX_RANK];	//���łɃ����N�C�����Ă�X�R�A	
//	int nDataRank[MAX_RANK];	//�f�[�^��ۑ�����p
//	int nDataSave[MAX_RANK];	//�����N�C�������X�R�A�̕ۑ�(���בւ�����)
//
//	pFile = fopen("data\\Ranking.txt", "r");
//
//	if (pFile != NULL)
//	{
//		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
//		{
//			fscanf(pFile, "%d", &nData[nCntRank]);	//�X�R�A���t�@�C������ǂݍ���
//
//			nDataRank[nCntRank] = nData[nCntRank];	//�ۑ�����
//
//			nDataSave[nCntRank] = 0;	//������
//		}
//
//		nAddRank = nScore;	//����̃X�R�A��������
//	}
//	fclose(pFile);
//
//	if (nAddRank >= nData[MAX_RANK - 1])
//	{//����5�ʂ�茻�݂̃X�R�A������������
//		nData[MAX_RANK - 1] = nAddRank;//5�ʂɌ��݂̃X�R�A����
//	}
//
//	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//�v�f1�Ɨv�f2���r����
//	{
//		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
//		{
//			if (nData[nCntData] < nData[nCntRank])
//			{
//				nCopyData = nData[nCntData];	//�󂯎M�ɗv�f1����
//				nData[nCntData] = nData[nCntRank];	//�v�f1�ɗv�f2����
//				nData[nCntRank] = nCopyData;		//���l�����ւ���
//			}
//		}
//	}
//
//	pFile = fopen("data\\Ranking.txt", "w");
//	if (pFile != NULL)
//	{
//		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
//		{
//			fprintf(pFile, "%d\n", nData[nCnt]);	//���בւ������̂����߂ĕۑ�����
//		}
//	}
//
//	fclose(pFile);
//
//	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
//	{
//		nDataSave[nCnt] = nData[nCnt];	//�X�R�A�̑��
//	}
//
//	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
//	{
//		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
//		{
//			g_aRankScore[nCnt][nCntNumber].nScorePos = nData[nCnt] % 10;
//			nData[nCnt] = nData[nCnt] / 10;
//		}
//	}
//
//
//	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
//	{
//		for (nCntNumber = 0; nCntNumber < MAX_NUMBER; nCntNumber++)
//		{
//			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntNumber].nScorePos), 1.0f);
//
//			if (nDataSave[nCntRank] == nScore)
//			{
//				g_aRankScore[nCntRank][nCntNumber].bRight = true;
//			}
//
//			pVtx += 4;
//		}
//
//	}
//
//	//���_�o�b�t�@�̃A�����b�N
//	g_pVtxBuffRank->Unlock();
//}