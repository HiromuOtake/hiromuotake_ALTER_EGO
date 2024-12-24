//======================================================
//
// ALTER_EGO [main.h]
// Auther : ��|�
//
//======================================================

#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION  (0x0800)     //�r���h���̌x���Ώ��p�}�N��

#include <Windows.h>
#include <string>
#include "d3dx9.h"
#include "dinput.h"						//���͏����ɕK�v
#include"xaudio2.h"                       //�T�E���h�����ɕK�v
#include "Xinput.h"						//�W���C�p�b�h�����ɕK�v
#include <time.h>
#include <DirectXMath.h>

//���C�u�����̃����N 
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[ d3d9.;ib ]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")         //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")		//�W���C�p�b�h�̏����ɕK�v
#pragma comment(lib,"winmm.lib")		//�����_���ɕK�v

//�}�N����`
#define SCREEN_WIDTH        (1280)       //�E�B���h�E�̕�
#define SCREEN_HEIGHT       (720)        //�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g�̒�`
#define CLASS_NAME          "WindowClass"          //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME         "ALTER EGO"              //�E�B���h�E�̖��O(�L���v�V�����ɕ\��)

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#if 0
#define FIND_MEM_LEAKS
#endif
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define new new (_NORMAL_BLOCK , __FILE__, __LINE__)
#else
#define new new
#endif // FIND_MEM_LEAKS

// stl
#include <unordered_map>
#include <vector>
#include <string>

//==============================================
// 3D�|���S���\����
//==============================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//==============================================
// 2D�|���S���\����
//==============================================
typedef struct
{
	D3DXVECTOR3 pos;     //���_���W
	float rhw;           //���W�ϊ��p�W��(1.0�ŌŒ�)
	D3DCOLOR col;        //���_�J���[
	D3DXVECTOR2 tex;     //�e�N�X�`�����W
}VERTEX_2D;

// ���_�t�H�[�}�b�g���`���邽�߂̍\����
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;  // ���_�̈ʒu
	D3DXVECTOR2 texCoord;  // �e�N�X�`�����W
};

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ToggleFullscreen(HWND hWnd);	// �E�B���h�E���t���X�N���[���ɂ���

#endif // !_MAIN_H_
#pragma once