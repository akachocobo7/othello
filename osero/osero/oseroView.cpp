
// oseroView.cpp : CoseroView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "osero.h"
#endif

#include "oseroDoc.h"
#include "oseroView.h"
#include <tuple>
#include <algorithm>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CoseroView

IMPLEMENT_DYNCREATE(CoseroView, CView)

BEGIN_MESSAGE_MAP(CoseroView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_START_BLACK, &CoseroView::OnStartBlack)
	ON_COMMAND(ID_START_WHITE, &CoseroView::OnStartWhite)
	ON_COMMAND(ID_GameEnd, &CoseroView::OnGameend)
	ON_COMMAND(ID_Girl, &CoseroView::OnGirl)
	ON_COMMAND(ID_Banana, &CoseroView::OnBanana)
END_MESSAGE_MAP()

// CoseroView �R���X�g���N�V����/�f�X�g���N�V����

/*========================================================================
�@�\  �R���X�g���N�^
========================================================================*/
CoseroView::CoseroView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

	m_FlagInGame = FALSE;
	InitBoard();
}

CoseroView::~CoseroView()
{
}

BOOL CoseroView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CoseroView �`��

/*========================================================================
�@�\  �`�惁�b�Z�[�W���󂯎�������̕`�揈��
����  pDC : �E�B���h�E�ւ̃f�o�C�X�R���e�L�X�g
========================================================================*/
void CoseroView::OnDraw(CDC* pDC)
{
	CoseroDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B

	DrawBoard(pDC);
}

void CoseroView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CoseroView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CoseroView �f�f

#ifdef _DEBUG
void CoseroView::AssertValid() const
{
	CView::AssertValid();
}

void CoseroView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CoseroDoc* CoseroView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CoseroDoc)));
	return (CoseroDoc*)m_pDocument;
}
#endif //_DEBUG


// CoseroView ���b�Z�[�W �n���h���[

/*========================================================================
�@�\  �I�Z��������������
========================================================================*/
void CoseroView::InitBoard()
{
	Black_Board = 0x0000000810000000;
	White_Board = 0x0000001008000000;

	m_FlagForWhite = FALSE;
	m_PutNumber = 0;
}

/*========================================================================
�@�\  �I�Z����`�悷��
����  pDC : �E�B���h�E�ւ̃f�o�C�X�R���e�L�X�g
========================================================================*/
void CoseroView::DrawBoard(CDC* pDC)
{
	int i;
	ll b = Black_Board, w = White_Board;
	CBrush gray_brush, black_brush, white_brush, green_brush;

	white_brush.CreateStockObject(WHITE_BRUSH);
	gray_brush.CreateSolidBrush(RGB(200, 200, 200));
	green_brush.CreateSolidBrush(RGB(34, 139, 34));
	black_brush.CreateSolidBrush(RGB(0, 0, 0));
	pDC->SelectObject(&green_brush);


	/* �I�Z���̎l�p��`�悷�� */
	pDC->Rectangle((MASU_NUM - 1) * MASU_SIZE, (MASU_NUM - 1) * MASU_SIZE,
				   MASU_NUM * MASU_SIZE - 1, MASU_NUM * MASU_SIZE - 1);

	/* �I�Z���̏�ɂ���΂�`�悷�� */
	if (b & 0x1) {
		pDC->SelectObject(&black_brush);
		pDC->Ellipse((MASU_NUM - 1) * MASU_SIZE + 3, (MASU_NUM - 1) * MASU_SIZE + 3,
					 MASU_NUM * MASU_SIZE - 4, MASU_NUM * MASU_SIZE - 4);
	}
	else if (w & 0x1) {
		pDC->SelectObject(&white_brush);
		pDC->Ellipse((MASU_NUM - 1) * MASU_SIZE + 3, (MASU_NUM - 1) * MASU_SIZE + 3,
					 MASU_NUM * MASU_SIZE - 4, MASU_NUM * MASU_SIZE - 4);
	}
	pDC->SelectObject(&green_brush);
	for (i = MASU_NUM * MASU_NUM - 2; i >= 0; i--) {
		b >>= 1;
		w >>= 1;

		/* �I�Z���̎l�p��`�悷�� */
		pDC->Rectangle(i % MASU_NUM * MASU_SIZE, i / MASU_NUM * MASU_SIZE,
					  (i % MASU_NUM + 1) * MASU_SIZE - 1, (i / MASU_NUM + 1) * MASU_SIZE - 1);

		/* �I�Z���̏�ɂ���΂�`�悷�� */
		if (!((b & 0x1) | (w & 0x1)))continue;
		else if(b & 0x1)pDC->SelectObject(&black_brush);
		else if(w & 0x1)pDC->SelectObject(&white_brush);

		pDC->Ellipse(i % MASU_NUM * MASU_SIZE + 3, i / MASU_NUM * MASU_SIZE + 3,
			(i % MASU_NUM + 1) * MASU_SIZE - 4, (i / MASU_NUM + 1) * MASU_SIZE - 4);

		pDC->SelectObject(&green_brush);
	}

	ShowPicture1(Face_Normal);
	ShowPicture3(P_null);
	if (m_FlagInGame == FALSE) {
		ShowPicture2(C_hello);
	}
	else if (m_PutNumber <= 0) {
		ShowPicture2(C_start);
	}
	else {
		ShowPicture2(C_put);
	}

	pDC->SelectObject(&white_brush);       //�f�t�H���g�̃u���V�ɖ߂�
}

/*========================================================================
�@�\  �}�E�X�̍��{�^���������ꂽ�Ƃ��̏���
����  point : ���{�^���������ꂽ�Ƃ��̃E�B���h�E��̈ʒu
========================================================================*/
void CoseroView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	if (!m_FlagInGame)return;

	int x, y;
	ll mov, rev;

	x = point.x / MASU_SIZE;
	y = point.y / MASU_SIZE;

	mov = pow(2, (MASU_NUM - 1 - x) + (MASU_NUM - 1 - y) * MASU_NUM);

	if (rev = CanDropDown(mov)) {
		DropDownStone(mov, rev);
		m_PutNumber++;

		CDC* pDC = GetDC();                //��ʂ��ĕ`��
		DrawBoard(pDC);
		ReleaseDC(pDC);

		End();
		if (m_FlagInGame)ComputerAI();
	}

	if (m_FlagInGame)End();

	CView::OnLButtonDown(nFlags, point);
}

/*========================================================================
�@�\  ���̈ʒu�ɐ΂��u���邩�ǂ������ׂ�
����  m : �΂�u�����Ƃ���ꏊ
�ߒl  �΂��u����Ȃ� �΂����]����ʒu ���A�u���Ȃ��Ȃ� 0 ��Ԃ�
========================================================================*/
ll CoseroView::CanDropDown(ll mov)
{
	if ((Black_Board | White_Board) & mov)return 0;		//����ӏ����󔒂Ŗ����ꍇ


	ll rev = 0, r, mask;

	if (m_FlagForWhite) {						//�����łꍇ
		r = 0;
		mask = (mov >> 1) & 0x7f7f7f7f7f7f7f7f;	//�E�����֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {	//���΂��A�������
			r |= mask;
			mask = (mask >> 1) & 0x7f7f7f7f7f7f7f7f;
		}
		if (mask & White_Board)rev |= r;				//���΂�����ΕԂ��ʒu���m�肷��

		r = 0;
		mask = (mov >> 8) & 0x00ffffffffffffff;	//�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask >> 8) & 0x00ffffffffffffff;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov << 1) & 0xfefefefefefefefe;	//�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask << 1) & 0xfefefefefefefefe;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov << 8) & 0xffffffffffffff00;	//������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask << 8) & 0xffffffffffffff00;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov >> 9) & 0x007f7f7f7f7f7f7f;	//�E�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask >> 9) & 0x007f7f7f7f7f7f7f;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov >> 7) & 0x00fefefefefefefe;	//���������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask >> 7) & 0x00fefefefefefefe;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov << 9) & 0xfefefefefefefe00;	//��������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask << 9) & 0xfefefefefefefe00;
		}
		if (mask & White_Board)rev |= r;

		r = 0;
		mask = (mov << 7) & 0x7f7f7f7f7f7f7f00;	//�E������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & Black_Board) != 0) {
			r |= mask;
			mask = (mask << 7) & 0x7f7f7f7f7f7f7f00;
		}
		if (mask & White_Board)rev |= r;
	}
	else {										//�����łꍇ
		r = 0;
		mask = (mov >> 1) & 0x7f7f7f7f7f7f7f7f;	//�E�����֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {	//���΂��A�������
			r |= mask;
			mask = (mask >> 1) & 0x7f7f7f7f7f7f7f7f;
		}
		if (mask & Black_Board)rev |= r;				//���΂�����ΕԂ��ʒu���m�肷��

		r = 0;
		mask = (mov >> 8) & 0x00ffffffffffffff;	//�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask >> 8) & 0x00ffffffffffffff;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov << 1) & 0xfefefefefefefefe;	//�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask << 1) & 0xfefefefefefefefe;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov << 8) & 0xffffffffffffff00;	//������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask << 8) & 0xffffffffffffff00;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov >> 9) & 0x007f7f7f7f7f7f7f;	//�E�������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask >> 9) & 0x007f7f7f7f7f7f7f;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov >> 7) & 0x00fefefefefefefe;	//���������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask >> 7) & 0x00fefefefefefefe;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov << 9) & 0xfefefefefefefe00;	//��������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask << 9) & 0xfefefefefefefe00;
		}
		if (mask & Black_Board)rev |= r;

		r = 0;
		mask = (mov << 7) & 0x7f7f7f7f7f7f7f00;	//�E������֕Ԃ��邩�𒲂ׂ�
		while (mask != 0 && (mask & White_Board) != 0) {
			r |= mask;
			mask = (mask << 7) & 0x7f7f7f7f7f7f7f00;
		}
		if (mask & Black_Board)rev |= r;
	}

	return rev;
}

/*========================================================================
�@�\  �I�Z���̏�ɐ΂�u��
����  mov, rev : �΂�u���ꏊ�A��������Ԃ��ꏊ
========================================================================*/
void CoseroView::DropDownStone(ll mov, ll rev)
{
	if (m_FlagForWhite) {
		White_Board ^= mov | rev;
		Black_Board ^= rev;
	}
	else {
		Black_Board ^= mov | rev;
		White_Board ^= rev;
	}

	m_FlagForWhite = !m_FlagForWhite;
}

/*========================================================================
�@�\  1��O�ɖ߂�
����  mov, rev : �΂�u���ꏊ�A��������Ԃ��ꏊ
========================================================================*/
void CoseroView::Ando(ll mov, ll rev)
{
	m_FlagForWhite = !m_FlagForWhite;

	if (m_FlagForWhite) {
		White_Board ^= mov | rev;
		Black_Board ^= rev;
	}
	else {
		Black_Board ^= mov | rev;
		White_Board ^= rev;
	}
}

/*========================================================================
�@�\  ���i���΁j�ŃQ�[�����J�n���鎞�̏���
========================================================================*/
void CoseroView::OnStartBlack()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	m_FlagInGame = TRUE;
	m_FlagForPlayer = FALSE;
	m_Flag_AI_White = TRUE;
	InitBoard();

	CDC* pDC = GetDC();                //��ʂ��ĕ`��
	DrawBoard(pDC);
	ReleaseDC(pDC);
}

/*========================================================================
�@�\  ���i���΁j�ŃQ�[�����J�n���鎞�̏���
========================================================================*/
void CoseroView::OnStartWhite()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	m_FlagInGame = TRUE;
	m_FlagForPlayer = TRUE;
	m_Flag_AI_White = FALSE;
	InitBoard();

	CDC* pDC = GetDC();                //��ʂ��ĕ`��
	DrawBoard(pDC);
	ReleaseDC(pDC);
	ComputerAI();
}

/*========================================================================
�@�\  �I�Z���ԏ�́i���������́j�΂̐��𐔂���
����  stone : ������΂̐F
�ߒl  �΂̐�
========================================================================*/
int CoseroView::CountStone(int stone)
{
	int count;

	if (stone == 1)count = __popcnt64(Black_Board);	//���΂𐔂���
	else count = __popcnt64(White_Board);			//���΂𐔂���

	return(count);
}

/*========================================================================
�@�\  �Q�[���I���̏���
========================================================================*/
void CoseroView::End()
{
	if (m_PutNumber == END_NUMBER)    //�Q�[���I���̏���
	{
		int P_num, AI_num;
		if (m_Flag_AI_White) {
			P_num = CountStone(BLACK_STONE);
			AI_num = CountStone(WHITE_STONE);
		}
		else {
			P_num = CountStone(WHITE_STONE);
			AI_num = CountStone(BLACK_STONE);
		}

		if (P_num > AI_num) {
			ShowPicture2(C_lose);
			MessageBox(TEXT("You Win!"));
		}
		else if (P_num < AI_num) {
			ShowPicture2(C_win);
			ShowPicture3(P_heart);
			MessageBox(TEXT("You Lose!"));
		}
		else {
			ShowPicture2(C_draw);
			MessageBox(TEXT("Draw Game!"));
		}

		m_FlagInGame = FALSE;
	}
}

/*========================================================================
�@�\  �őP���T������
	  lv   : ��ǂ݂̎萔
	  Put  : ���̎�Ԃ̑O�ɑ��肪�΂�u�������ǂ���
�ߒl  �]���l
========================================================================*/
ll CoseroView::Nega_Max(int lv, BOOL Put, int alpha, int beta)
{
	int i, temp, size = m_VoidTable.size(), max;
	BOOL FlagForPut = FALSE;
	ll mov, best_mov, rev;

	if (lv == 0)return -ValueBoard();

	max = alpha;

	for (i = 0; i < size; i++) {
		mov = m_VoidTable[i];
		if (rev = CanDropDown(mov)) {
			FlagForPut = TRUE;
			DropDownStone(mov, rev);
			m_VoidTable.erase(m_VoidTable.begin() + i);
			temp = -Nega_Max(lv - 1, TRUE, -beta, -max);
			m_VoidTable.insert(m_VoidTable.begin() + i, mov);
			Ando(mov, rev);

			if (temp >= beta)return(temp);
			if (temp > max) {
				max = temp;
				best_mov = mov;
			}
		}
	}

	if (FlagForPut) {
		if (lv == m_SearchLv)return(best_mov);
		return max;
	}
	else if (!Put)return(-ValueBoard());
	else
	{
		m_FlagForWhite = !m_FlagForWhite;
		temp = -Nega_Max(lv - 1, FALSE, -beta, -max);
		m_FlagForWhite = !m_FlagForWhite;
		return(temp);
	}
}

/*========================================================================
�@�\  �őP���T������
����  Flag : �R���s���[�^�̎�Ԃ̎� TRUE�A�l�̎�Ԃ̎� FALSE
lv		   : ��ǂ݂̎萔
Put		   : ���̎�Ԃ̑O�ɑ��肪�΂�u�������ǂ���
�ߒl  �]���l
========================================================================*/
ll CoseroView::Fastest_First(BOOL Flag, int lv, BOOL Put, int alpha, int beta)
{
	int temp, i, size = m_VoidTable.size(), max;
	ll mov, rev, best_mov;
	BOOL FlagForPut = FALSE;

	if (lv == 0)return -ValueBoard();

	max = alpha;

	if (lv >= 6) {
		int count = 0, CanPut;
		tuple<int, ll, ll, int> p[60];

		for (i = 0; i < size; i++) {
			mov = m_VoidTable[i];
			if (rev = CanDropDown(mov)) {
				DropDownStone(mov, rev);
				CanPut = ValueBoardDropDownNum();
				if (CanPut < 0)CanPut = -CanPut;
				p[count] = make_tuple(CanPut, mov, rev, i);
				Ando(mov, rev);
				count++;
			}
		}

		sort(p, p + count);

		for (i = 0; i < count; i++) {
			FlagForPut = TRUE;
			DropDownStone(get<1>(p[i]), get<2>(p[i]));
			m_VoidTable.erase(m_VoidTable.begin() + get<3>(p[i]));
			temp = -Fastest_First(!Flag, lv - 1, TRUE, -beta, -max);
			m_VoidTable.insert(m_VoidTable.begin() + get<3>(p[i]), get<1>(p[i]));
			Ando(get<1>(p[i]), get<2>(p[i]));

			if (temp >= beta)return(temp);
			if (temp > max) {
				max = temp;
				best_mov = get<1>(p[i]);
			}
		}
	}
	else {
		for (i = 0; i < size; i++) {
			mov = m_VoidTable[i];
			if (rev = CanDropDown(mov)) {
				FlagForPut = TRUE;
				DropDownStone(mov, rev);
				m_VoidTable.erase(m_VoidTable.begin() + i);
				temp = -Fastest_First(!Flag, lv - 1, TRUE, -beta, -max);
				m_VoidTable.insert(m_VoidTable.begin() + i, mov);
				Ando(mov, rev);

				if (temp >= beta)return(temp);
				if (temp > max) {
					max = temp;
					best_mov = mov;
				}
			}
		}
	}

	if (FlagForPut) {
		if (lv == m_SearchLv)return(best_mov);
		return max;
	}
	else if (!Put)return(-ValueBoard());
	else
	{
		m_FlagForWhite = !m_FlagForWhite;
		temp = -Fastest_First(!Flag, lv - 1, FALSE, -beta, -max);
		m_FlagForWhite = !m_FlagForWhite;
		return(temp);
	}
}

/*ll CoseroView::Fastest_First(BOOL Flag, int lv, BOOL Put, int alpha, int beta)
{
	int temp, i, size = m_VoidTable.size(), max;
	ll mov, rev, best_mov;
	BOOL FlagForPut = FALSE;
	tuple<int, int, BOOL> val;

	if (lv == 0)return -ValueBoard();

	auto itr = m_HashTable.find(Black_Board ^ ~White_Board);

	if (itr != m_HashTable.end()) {
		val = itr->second;
		if (m_SearchLv != lv) {
			if (END_NUMBER - lv == get<1>(val) && m_FlagForWhite == get<2>(val)) {
				return get<0>(val);
			}
		}
	}

	max = alpha;

	if (lv >= 6) {
		int count = 0, CanPut;
		tuple<int, ll, ll, int> p[60];

		for (i = 0; i < size; i++) {
			mov = m_VoidTable[i];
			if (rev = CanDropDown(mov)) {
				DropDownStone(mov, rev);
				CanPut = ValueBoardDropDownNum();
				if (CanPut < 0)CanPut = -CanPut;
				p[count] = make_tuple(CanPut, mov, rev, i);
				Ando(mov, rev);
				count++;
			}
		}

		sort(p, p + count);

		for (i = 0; i < count; i++) {
			FlagForPut = TRUE;
			DropDownStone(get<1>(p[i]), get<2>(p[i]));
			m_VoidTable.erase(m_VoidTable.begin() + get<3>(p[i]));
			temp = -Fastest_First(!Flag, lv - 1, TRUE, -beta, -max);
			m_VoidTable.insert(m_VoidTable.begin() + get<3>(p[i]), get<1>(p[i]));
			Ando(get<1>(p[i]), get<2>(p[i]));

			if (temp >= beta) {
				m_HashTable[Black_Board ^ ~White_Board] = make_tuple(temp, END_NUMBER - lv, m_FlagForWhite);
				return temp;
			}
			if (temp > max) {
				max = temp;
				best_mov = get<1>(p[i]);
			}
		}
	}
	else {
		for (i = 0; i < size; i++) {
			mov = m_VoidTable[i];
			if (rev = CanDropDown(mov)) {
				FlagForPut = TRUE;
				DropDownStone(mov, rev);
				m_VoidTable.erase(m_VoidTable.begin() + i);
				temp = -Fastest_First(!Flag, lv - 1, TRUE, -beta, -max);
				m_VoidTable.insert(m_VoidTable.begin() + i, mov);
				Ando(mov, rev);

				if (temp >= beta) {
					m_HashTable[Black_Board ^ ~White_Board] = make_tuple(temp, END_NUMBER - lv, m_FlagForWhite);
					return temp;
				}
				if (temp > max) {
					max = temp;
					best_mov = mov;
				}
			}
		}
	}

	if (FlagForPut) {
		if (lv == m_SearchLv)return(best_mov);

		m_HashTable[Black_Board ^ ~White_Board] = make_tuple(max, END_NUMBER - lv, m_FlagForWhite);
		return max;
	}
	else if (!Put)return(-ValueBoard());
	else
	{
		m_FlagForWhite = !m_FlagForWhite;
		temp = -Fastest_First(!Flag, lv - 1, FALSE, -beta, -max);
		m_FlagForWhite = !m_FlagForWhite;

		m_HashTable[Black_Board ^ ~White_Board] = make_tuple(temp, END_NUMBER - lv, m_FlagForWhite);

		return(temp);
	}
}*/

/*========================================================================
�@�\  AI
========================================================================*/
void CoseroView::ComputerAI()
{
	int i;
	ll mov = 0x8000000000000000, rev;

	for (i = 0; i < MASU_NUM * MASU_NUM; i++){		//�������΂�u���Ȃ��Ȃ�A�p�X
		if (m_PutNumber == 60)break;
		if (CanDropDown(mov))break;
		mov = (mov >> 1) & 0x7fffffffffffffff;
	}
	if (i == MASU_NUM * MASU_NUM) {
		m_FlagForWhite = !m_FlagForWhite;
		ShowPicture2(C_no_put);
		return;
	}

	ShowPicture1(Face_Thinking);
	ShowPicture2(C_think);

	m_VoidTable.clear();
	for (ll s = 0x8000000000000000; s != 0; s = (s >> 1) & 0x7fffffffffffffff) {
		if (!((Black_Board | White_Board) & s)) {
			m_VoidTable.push_back(s);
		}
	}
	if (m_PutNumber >= FINISH_NUM) {
		mov = Fastest_First(TRUE, m_SearchLv = END_NUMBER - m_PutNumber, TRUE, -9999, 9999);	//�I��
	}
	else {
		mov = Nega_Max(m_SearchLv = SEARCH_LV, TRUE, -9999, 9999);  //�őP���T������
	}

	rev = CanDropDown(mov);
	DropDownStone(mov, rev);
	m_PutNumber++;

	//�f�o�b�O�p
	int c = 0;
	ll m;
	for (m = mov; m != 0; m = ((m >> 1) & 0x7fffffffffffffff))c++;
	ATLTRACE("x���W:%d y���W:%d\n", MASU_NUM - (c - 1) % MASU_NUM, MASU_NUM - (c - 1) / MASU_NUM);


	CDC* pDC = GetDC();                //��ʂ��ĕ`��
	DrawBoard(pDC);
	ReleaseDC(pDC);

	mov = 0x8000000000000000;
	for (i = 0; i < MASU_NUM * MASU_NUM; i++){      //���肪�΂�u���Ȃ��Ȃ�A������x
		if (m_PutNumber == 60)break;
		if (CanDropDown(mov))break;
		if (i == MASU_NUM * MASU_NUM - 1)
		{
			m_FlagForWhite = !m_FlagForWhite;
			ComputerAI();
		}
		mov = (mov >> 1) & 0x7fffffffffffffff;
	}
}

/*========================================================================
�@�\  �Ֆʂ�]������i�]���֐��{�́j
�ߒl  �]���l
========================================================================*/
int CoseroView::ValueBoard()
{
	int value = 0;
	int BP = 1, BD = 40, BF = 45;			//�]���l�̏d��

	if (m_PutNumber >= FINISH_NUM) {		//�I��
		value += ValueBoardNumber();
	}
	else {
		value += ValueBoardPlace() * BP;
		value += ValueBoardDropDownNum() * BD;
		value += ValueBoardFixedStone() * BF;
	}

	if (!m_Flag_AI_White)value = -value;		//AI�����Ȃ甽�]

	// ATLTRACE("%d\n", value);		//�f�o�b�O�p

	return value;
}

/*========================================================================
�@�\  �Ֆʂ�΂̂���ꏊ�ŕ]������
�ߒl  �]���l
========================================================================*/
int CoseroView::ValueBoardPlace()
{
	int value = 0, i, c;
	ll b = Black_Board, w = White_Board;

	if (m_Flag_AI_White) {
		if ((__popcnt64(w)) >= 1)c = 0;					//�S�ő΍�
		else if ((__popcnt64(b)) == 0)c = -50000;		//�����S�ł�������]���l�A�b�v
		else c = 50000;
	}
	else {
		if ((__popcnt64(b)) >= 1)c = 0;
		else if ((__popcnt64(w)) == 0)c = 50000;
		else c = -50000;
	}

	for (i = MASU_NUM * MASU_NUM - 1; i >= 0; i--) {
		value += (b & 0x1) * ValuePlace[i];
		value -= (w & 0x1) * ValuePlace[i];

		b >>= 1;
		w >>= 1;
	}

	return(-value - c);
}

/*========================================================================
�@�\  ����\��̐��ŔՖʂ�]������
�ߒl  �]���l
========================================================================*/
int CoseroView::ValueBoardDropDownNum()
{
	int i, value = 0;
	ll mov = 0x8000000000000000;

	for (i = 0; i < MASU_NUM * MASU_NUM; i++) {
		if (CanDropDown(mov))value += 1;
		mov = (mov >> 1) & 0x7fffffffffffffff;
	}

	if (m_FlagForWhite)return(value);
	else return(-value);
}

/*========================================================================
�@�\  ����Ƃ̐΂̐��̍��ŔՖʂ�]������
========================================================================*/
int CoseroView::ValueBoardNumber()
{
	int value = 0;

	value += __popcnt64(Black_Board);	//���΂𐔂���
	value -= __popcnt64(White_Board);	//���΂𐔂���

	return(-value);
}

/*========================================================================
�@�\  �m��΂̐��ŔՖʂ�]������
�ߒl  �]���l
========================================================================*/
int CoseroView::ValueBoardFixedStone()
{
	ll i;
	int value = 0;

	if ((Black_Board | White_Board) & 0x8000000000000000) {
		if (Black_Board & 0x8000000000000000) {
			i = 0x8000000000000000;
			while (Black_Board & i) {
				value += 1;
				i = (i >> 1) & 0x7fffffffffffffff;
			}
			i = 0x8000000000000000;
			while (Black_Board & i) {
				value += 1;
				i = (i >> 8) & 0x00ffffffffffffff;
			}
		}
		else {
			i = 0x8000000000000000;
			while (White_Board & i) {
				value -= 1;
				i = (i >> 1) & 0x7fffffffffffffff;
			}
			i = 0x8000000000000000;
			while (White_Board & i) {
				value -= 1;
				i = (i >> 8) & 0x00ffffffffffffff;
			}
		}
	}
	if ((Black_Board | White_Board) & 0x0100000000000000) {
		if (Black_Board & 0x0100000000000000) {
			i = 0x0100000000000000;
			while (Black_Board & i) {
				value += 1;
				i = (i << 1) & 0xfffffffffffffffe;
			}
			i = 0x0100000000000000;
			while (Black_Board & i) {
				value += 1;
				i = (i >> 8) & 0x00ffffffffffffff;
			}
		}
		else {
			i = 0x0100000000000000;
			while (White_Board & i) {
				value -= 1;
				i = (i << 1) & 0xfffffffffffffffe;
			}
			i = 0x0100000000000000;
			while (White_Board & i) {
				value -= 1;
				i = (i >> 8) & 0x00ffffffffffffff;
			}
		}
	}
	if ((Black_Board | White_Board) & 0x0000000000000080) {
		if (Black_Board & 0x0000000000000080) {
			i = 0x0000000000000080;
			while (Black_Board & i) {
				value += 1;
				i = (i >> 1) & 0x7fffffffffffffff;
			}
			i = 0x0000000000000080;
			while (Black_Board & i) {
				value += 1;
				i = (i << 8) & 0xffffffffffffff00;
			}
		}
		else {
			i = 0x0000000000000080;
			while (White_Board & i) {
				value -= 1;
				i = (i >> 1) & 0x7fffffffffffffff;
			}
			i = 0x0000000000000080;
			while (White_Board & i) {
				value -= 1;
				i = (i << 8) & 0xffffffffffffff00;
			}
		}
	}
	if ((Black_Board | White_Board) & 0x0000000000000001) {
		if (Black_Board & 0x0000000000000001) {
			i = 0x0000000000000001;
			while (Black_Board & i) {
				value += 1;
				i = (i << 1) & 0xfffffffffffffffe;
			}
			i = 0x0000000000000001;
			while (Black_Board & i) {
				value += 1;
				i = (i << 8) & 0xffffffffffffff00;
			}
		}
		else {
			i = 0x0000000000000001;
			while (White_Board & i) {
				value -= 1;
				i = (i << 1) & 0xfffffffffffffffe;
			}
			i = 0x0000000000000001;
			while (White_Board & i) {
				value -= 1;
				i = (i << 8) & 0xffffffffffffff00;
			}
		}
	}

	return(-value);
}

void CoseroView::OnGameend()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	if (m_FlagInGame == TRUE) {
		m_PutNumber = END_NUMBER;
		End();
	}

}

void CoseroView::ShowPicture1(Character_Pictures i) {
	int width, height = 0;
	double size = 1;
	CString filePath;
	CImage* img = new CImage();
	CDC* pDC = GetDC();

	if (m_Picture == 1) {
		switch (i) {
		case Face_Normal:
			filePath = "picture\\2.5.png";
			break;
		case Face_Thinking:
			filePath = "picture\\2.png";
			break;
		default:
			break;
		}
	}
	else if (m_Picture == 2) {
		filePath = "picture\\banana.jpg";
	}

	img->Load(filePath);

	width = img->GetWidth();
	height = img->GetHeight();

	img->Draw(*pDC, MASU_SIZE * MASU_NUM + 5, 270, int(width * size), int(height * size), 0, 0, width, height);
	/* ���S�͉摜��\��������Ƃ��ɉ摜�̃T�C�Y�����߂����
	�E�S�͉摜�̂ǂ��̃s�N�Z������ǂ��̃s�N�Z���܂ł�
	�\�������邩�����߂����								  */
}

void CoseroView::ShowPicture2(Comment_Pictures i) {
	int width, height = 0;
	double size = 1.0;
	CString filePath;
	CImage* img = new CImage();
	CDC* pDC = GetDC();

	std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
	std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
	std::uniform_int_distribution<> rd(0, 2);        // [0, 1] �͈͂̈�l����

	if (m_Picture == 1) {
		switch (i) {
		case C_hello:
			filePath = "picture\\hello.png";
			break;
		case C_start:
			filePath = "picture\\start.png";
			break;
		case C_put:
			if (rd(mt) == 0) {
				filePath = "picture\\put1.png";
			}
			else if (rd(mt) == 1) {
				filePath = "picture\\put2.png";
			}
			else {
				filePath = "picture\\put3.png";
			}
			break;
		case C_think:
			filePath = "picture\\thinking.png";
			break;
		case C_lose:
			filePath = "picture\\lose.png";
			break;
		case C_win:
			filePath = "picture\\win.png";
			break;
		case C_draw:
			filePath = "picture\\draw.png";
			break;
		case C_no_put:
			filePath = "picture\\no_put.png";
			break;
		default:
			filePath = "picture\\null_comment.png";
			break;
		}
	}
	else {
		switch (i) {
		case C_put:
			filePath = "picture\\put_1.jpg";
			break;
		case C_think:
			filePath = "picture\\apple.jpg";
			break;
		default:
			filePath = "picture\\put_0.jpg";
			break;
		}
	}

	img->Load(filePath);

	width = img->GetWidth();
	height = img->GetHeight();

	if (m_Picture == 1) {
		img->Draw(*pDC, MASU_SIZE * MASU_NUM + 30, 187, int(width * size), int(height * size), 0, 0, width, height);
	}
	else {
		img->Draw(*pDC, MASU_SIZE * MASU_NUM + 120, 187, int(width * size), int(height * size), 0, 0, width, height);
	}
}

void CoseroView::ShowPicture3(Heart_Pictures i) {
	int width, height = 0;
	double size = 1.0;
	CString filePath;
	CImage* img = new CImage();
	CDC* pDC = GetDC();

	if (m_Picture == 1) {
		switch (i) {
		case P_null:
			filePath = "picture\\null_heart.png";
			break;
		case P_heart:
			filePath = "picture\\heart2.png";
			break;
		default:
			break;
		}
	}
	else {
		filePath = "picture\\null_heart.png";
	}

	img->Load(filePath);

	width = img->GetWidth();
	height = img->GetHeight();

	img->Draw(*pDC, MASU_SIZE * MASU_NUM + 130, 265, int(width * size), int(height * size), 0, 0, width, height);
}

void CoseroView::OnGirl()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	ShowPicture2(C_null);
	m_Picture = 1;
	ShowPicture3(P_null);
	ShowPicture1(Face_Normal);
	ShowPicture2(C_hello);
}


void CoseroView::OnBanana()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	ShowPicture2(C_null);
	m_Picture = 2;
	ShowPicture3(P_null);
	ShowPicture1(Face_Normal);
	ShowPicture2(C_hello);
}