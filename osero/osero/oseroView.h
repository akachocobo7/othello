
// oseroView.h : CoseroView �N���X�̃C���^�[�t�F�C�X
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
protected: // �V���A��������̂ݍ쐬���܂��B

	ll Black_Board;								//�I�Z����(��)
	ll White_Board;								//�I�Z����(��)
	int m_PutNumber;                          //�萔
	int m_SearchLv;                           //�T�����x��
	BOOL m_FlagForWhite;                      //��Ԃ�\���t���O
	BOOL m_FlagForPlayer;                     //�v���C���[�̎�Ԃ��ǂ�����\���t���O
	BOOL m_FlagInGame;                        //�Q�[�������ǂ�����\���t���O
	BOOL m_Flag_AI_White;					  //AI�����ŃQ�[���J�n��������\��
	int m_Picture = 1;						//�ΐ�L������I������
	vector<ll> m_VoidTable;					//�󏊕\
	unordered_map<ll, tuple<int, int, BOOL>> m_HashTable;	//�n�b�V���e�[�u��

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

	void InitBoard();                       //�I�Z��������������
	void DrawBoard(CDC* pDC);               //�I�Z����`�悷��
	ll   CanDropDown(ll mov);				//�΂��u���邩���ׂ�
	void DropDownStone(ll mov, ll rev);		//�΂�u��
	void Ando(ll mov, ll rev);				//1��O�ɂ��ǂ�
	int CountStone(int stone);              //�΂̐��𐔂���
	void ComputerAI(void);                  //�R���s���[�^�̎�ԏ���
	ll Nega_Max(int lv, BOOL Put, int alpha, int beta);//�őP���T������
	ll Fastest_First(BOOL Flag, int lv, BOOL Put, int alpha, int beta);//�����D��T��
	int ValueBoard(void);                   //�Ֆʂ�]������
	int ValueBoardPlace(void);              //�΂̕��т�]������
	int ValueBoardDropDownNum(void);        //����\�ꏊ�̐���]������
	int ValueBoardNumber(void);             //�΂̐���]������
	int ValueBoardFixedStone(void);         //�m��΂̐���]������
	void ShowPicture1(Character_Pictures i);//�摜��\������
	void ShowPicture2(Comment_Pictures i);	//�摜��\������
	void ShowPicture3(Heart_Pictures i);				//�摜��\������

	void End(void);                         //�Q�[���I���̏���

	CoseroView();
	DECLARE_DYNCREATE(CoseroView)

// ����
public:
	CoseroDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����
public:
	virtual ~CoseroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

#ifndef _DEBUG  // oseroView.cpp �̃f�o�b�O �o�[�W����
inline CoseroDoc* CoseroView::GetDocument() const
   { return reinterpret_cast<CoseroDoc*>(m_pDocument); }
#endif

