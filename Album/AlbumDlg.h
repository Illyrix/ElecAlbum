
// AlbumDlg.h: 头文件
//

#pragma once

#include "FadeIn.h"

// CAlbumDlg 对话框
class CAlbumDlg : public CDialog
{
// 构造
public:
	CAlbumDlg(CWnd* pParent = nullptr);	// 标准构造函数
    FadeIn* mFadeIn;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALBUM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
