////==============================================
////
//// ALTER_EGO[fade.h]
//// Author: hiromu otake
////
////==============================================
//
//#include "object2D.h"
//#include "scene.h"
//
//#ifndef _FADE_H_
//#define _FADE_H_
//
//class CFade : public CObject2D
//{
//public:
//	typedef enum
//	{
//		FADE_NONE = 0,     //�������Ă��Ȃ����
//		FADE_IN,           //�t�F�[�h�C�����
//		FADE_OUT,          //�t�F�[�h�A�E�g���
//		FADE_MAX
//	}FADE;
//	CFade(int nPriority = 5);
//	~CFade() override;
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	void SetFade(FADE fade, CScene::MODE modeNext);
//	static CFade* Create(CScene::MODE mode);
//	FADE GetFade(void);
//	float FadeColor(void);
//private:
//	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
//	FADE m_Fade;
//	CScene::MODE m_fademode;
//	float m_colorFade;
//};
//
//#endif // !_FADE_H_