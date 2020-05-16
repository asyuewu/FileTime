
// FileTimeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CFileTimeDlg �Ի���
class CFileTimeDlg : public CDialogEx
{
// ����
public:
    CFileTimeDlg(CWnd* pParent = NULL);    // ��׼���캯��

// �Ի�������
    enum { IDD = IDD_FILETIME_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


// ʵ��
protected:
    HICON m_hIcon;

    // ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL modifyFileTime(const CString pathName, const SYSTEMTIME *lpsctime, const SYSTEMTIME *lpsatime, const SYSTEMTIME *lpswtime);
    afx_msg void modifyDirectoryTime(const CString directoryPath, const CString fileFilter);
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton6();
    afx_msg void OnBnClickedButton7();
    CButton m_button_browse;
    CButton m_button_ok;
    CButton m_button_language;
    CButton m_button_message;
    CButton m_button_creation;
    CButton m_button_modify;
    CButton m_button_lastAccess;
    CDateTimeCtrl m_creationTime;
    CDateTimeCtrl m_modifyTime;
    CDateTimeCtrl m_lastAccessTime;
    CEdit m_edit_filter;
    CStatic m_static_path;
    CStatic m_static_filter;
    CStatic m_static_apply;
    CStatic m_static_setting;
    CStatic m_static_sync;
    CStatic m_static_time;
    CButton m_check_folders;
    CButton m_check_subfolders;
    CButton m_check_creation;
    CButton m_check_modify;
    CButton m_check_lastAccess;
};
