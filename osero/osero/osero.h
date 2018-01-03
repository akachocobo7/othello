
// osero.h : osero �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��

#define TITLE_NAME  L"�I���i�m�R�g�I�Z��"
#define MASU_SIZE   50                       //�}�X�ځi�΁j�̃T�C�Y
#define MASU_NUM    8                        //�}�X�ڂ̐��i�P�����ɑ΂���j
#define BOARD_SIZE  MASU_SIZE * MASU_NUM     //�I�Z���̃T�C�Y
#define SYSTEM_SIZE 100                      //���䕔���̃T�C�Y
#define WINDOW_W    BOARD_SIZE + SYSTEM_SIZE //�E�B���h�E�̉���
#define WINDOW_H    BOARD_SIZE               //�E�B���h�E�̏c��
#define BLACK_STONE   1                      //����
#define WHITE_STONE  -1                      //����
#define BLANK         0                      //�΂Ȃ�
#define END_NUMBER   60						 //�I�Z���I���̎萔
#define SEARCH_LV     7                      //�T������萔
#define MIDDLE_NUM    8                      //���Ղ̎n�܂�萔
#define FINISH_NUM   46                      //�I�Ղ̎n�܂�萔

// CoseroApp:
// ���̃N���X�̎����ɂ��ẮAosero.cpp ���Q�Ƃ��Ă��������B
//

class CoseroApp : public CWinAppEx
{
public:
	CoseroApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CoseroApp theApp;
