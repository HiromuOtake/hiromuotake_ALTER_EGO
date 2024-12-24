//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,			// BGM0
		SOUND_LABEL_BGM001,				// BGM1
		SOUND_LABEL_SE_JUMP,			// �W�����v��
		SOUND_LABEL_SE_COIN,			// �R�C����
		SOUND_LABEL_SE_DEATH,			// ���S��
		SOUND_LABEL_SE_GOAL,			// �S�[����
		SOUND_LABEL_SE_SHOT,			// �e���ˉ�
		SOUND_LABEL_SE_BUTON,			// �{�^����
		SOUND_LABEL_SE_DELETECIRCLE,	// �T�[�N��������
		SOUND_LABEL_SE_SPAWNSIRCLE,		// �T�[�N�����ŉ�
		SOUND_LABEL_SE_CHOOSECLONE,		// �N���[���I����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;		    // ���[�v�J�E���g
		float Volume;           //����
	} SOUNDINFO;

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopAllSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[CSound::SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[CSound::SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[CSound::SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
	CSound::SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX] =
	{
		{"data/BGM/�l�I��.wav", -1,1.5f} ,			// BGM1
		{"data/BGM/Vivid_Spooky.wav", -1,0.5f},		// BGM0
		{"data/SE/jump.wav", 0,1.0f},				// �W�����v��
		{"data/SE/get000.wav", 0,0.9f},				// �R�C����
		{"data/SE/death.wav", 0,1.0f},				// ���S��
		{"data/SE/goal.wav", 0,2.0f},				// �S�[����
		{"data/SE/shot.wav", 0,1.0f},				// �e���ˉ�
		{"data/SE/get001.wav", 0,2.0f},				// �{�^����
		{"data/SE/spawnsircle.wav", 0,2.0f},		// �T�[�N��������
		{"data/SE/deletesircle.wav", 0,2.0f},		// �T�[�N�����ŉ�
		{"data/SE/chooseclone.wav", 0,2.0f},		// �N���[���I����
	};
};

#endif
