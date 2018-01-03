
// osero.h : osero アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"       // メイン シンボル

#define TITLE_NAME  L"オンナノコトオセロ"
#define MASU_SIZE   50                       //マス目（石）のサイズ
#define MASU_NUM    8                        //マス目の数（１方向に対する）
#define BOARD_SIZE  MASU_SIZE * MASU_NUM     //オセロ板のサイズ
#define SYSTEM_SIZE 100                      //制御部分のサイズ
#define WINDOW_W    BOARD_SIZE + SYSTEM_SIZE //ウィンドウの横幅
#define WINDOW_H    BOARD_SIZE               //ウィンドウの縦幅
#define BLACK_STONE   1                      //黒石
#define WHITE_STONE  -1                      //白石
#define BLANK         0                      //石なし
#define END_NUMBER   60						 //オセロ終了の手数
#define SEARCH_LV     7                      //探索する手数
#define MIDDLE_NUM    8                      //中盤の始まる手数
#define FINISH_NUM   46                      //終盤の始まる手数

// CoseroApp:
// このクラスの実装については、osero.cpp を参照してください。
//

class CoseroApp : public CWinAppEx
{
public:
	CoseroApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CoseroApp theApp;
