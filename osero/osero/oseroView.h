
// oseroView.h : CoseroView クラスのインターフェイス
//

#pragma once

#include <vector>
#include <unordered_map>

using ll = long long;
using namespace std;

const int ValuePlace[MASU_NUM * MASU_NUM] = {
	150, -10, 10,  5,  5, 10, -10, 150,
	-10,-200,  2,  1,  1,  2,-200, -10,
	 10,   2,  0,  1,  1,  0,   2,  10,
	  5,   1,  1,  0,  0,  1,   1,   5,
	  5,   1,  1,  0,  0,  1,   1,   5,
	 10,   2,  0,  1,  1,  0,   2,  10,
	-10,-200,  2,  1,  1,  2,-200, -10,
	150, -10, 10,  5,  5, 10, -10, 150
};

class CoseroView : public CView
{
protected: // シリアル化からのみ作成します。

	ll Black_Board;								//オセロ板(黒)
	ll White_Board;								//オセロ板(白)
	int m_PutNumber;                          //手数
	int m_SearchLv;                           //探索レベル
	BOOL m_FlagForWhite;                      //手番を表すフラグ
	BOOL m_FlagForPlayer;                     //プレイヤーの手番かどうかを表すフラグ
	BOOL m_FlagInGame;                        //ゲーム中かどうかを表すフラグ
	BOOL m_Flag_AI_White;					  //AIが白でゲーム開始したかを表す
	int m_Picture = 1;						//対戦キャラを選択する
	vector<ll> m_VoidTable;					//空所表
	unordered_map<ll, tuple<int, int, BOOL>> m_HashTable;	//ハッシュテーブル

	enum Character_Pictures {
		Face_Normal = 0,
		Face_Thinking
	};
	enum Comment_Pictures {
		C_null = -1,
		C_hello,
		C_start,
		C_put,
		C_think,
		C_lose,
		C_win,
		C_draw,
		C_no_put
	};
	enum Heart_Pictures {
		P_null = 0,
		P_heart
	};

	void InitBoard();                       //オセロ板を初期化する
	void DrawBoard(CDC* pDC);               //オセロ板を描画する
	ll   CanDropDown(ll mov);				//石が置けるか調べる
	void DropDownStone(ll mov, ll rev);		//石を置く
	void Ando(ll mov, ll rev);				//1手前にもどる
	int CountStone(int stone);              //石の数を数える
	void ComputerAI(void);                  //コンピュータの手番処理
	ll Nega_Max(int lv, BOOL Put, int alpha, int beta);//最善手を探索する
	ll Fastest_First(BOOL Flag, int lv, BOOL Put, int alpha, int beta);//速さ優先探索
	int ValueBoard(void);                   //盤面を評価する
	int ValueBoardPlace(void);              //石の並びを評価する
	int ValueBoardDropDownNum(void);        //着手可能場所の数を評価する
	int ValueBoardNumber(void);             //石の数を評価する
	int ValueBoardFixedStone(void);         //確定石の数を評価する
	void ShowPicture1(Character_Pictures i);//画像を表示する
	void ShowPicture2(Comment_Pictures i);	//画像を表示する
	void ShowPicture3(Heart_Pictures i);				//画像を表示する

	void End(void);                         //ゲーム終了の処理

	CoseroView();
	DECLARE_DYNCREATE(CoseroView)

// 属性
public:
	CoseroDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CoseroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStartBlack();
	afx_msg void OnStartWhite();
	afx_msg void OnGameend();
	afx_msg void OnGirl();
	afx_msg void OnBanana();
};

#ifndef _DEBUG  // oseroView.cpp のデバッグ バージョン
inline CoseroDoc* CoseroView::GetDocument() const
   { return reinterpret_cast<CoseroDoc*>(m_pDocument); }
#endif

