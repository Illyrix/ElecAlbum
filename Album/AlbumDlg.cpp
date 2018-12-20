
// AlbumDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Album.h"
#include "AlbumDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct FadeInWorkThreadParam {
    CWnd* pCwnd;
    FadeIn* fi;
} THREAD_SWAP;


// CAlbumDlg 对话框

const int SWITCH_IMAGE_EVID = 1;

CAlbumDlg::CAlbumDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ALBUM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlbumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlbumDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CAlbumDlg 消息处理程序

BOOL CAlbumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    const LPCTSTR pImgs[] = {
        _T("../pics/1.jpg"),
        _T("../pics/2.jpg"),
        _T("../pics/3.jpg"),
        _T("../pics/4.jpg"),
        _T("../pics/5.jpg"),
        _T("../pics/6.jpg"),
        _T("../pics/7.jpg"),
        _T("../pics/8.jpg"),
        _T("../pics/9.jpg")
    };
    mFadeIn = new FadeIn(pImgs, 9, _T("../pics/0.jpg"));
    SetTimer(SWITCH_IMAGE_EVID, 4000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAlbumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        mFadeIn->OnPaint(GetDlgItem(IDC_STATIC));
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAlbumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAlbumDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == SWITCH_IMAGE_EVID) {
        // mFadeIn->StartFade(GetDlgItem(IDC_STATIC));
        THREAD_SWAP.fi = mFadeIn;
        THREAD_SWAP.pCwnd = this;
        AfxBeginThread(FadeInWorkThread, NULL);
    }
    else {
        CDialog::OnTimer(nIDEvent);
    }
}

UINT FadeInWorkThread(LPVOID) {
    THREAD_SWAP.fi->StartFade(THREAD_SWAP.pCwnd);
    return 0;
}