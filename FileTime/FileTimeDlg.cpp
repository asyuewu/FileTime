
// FileTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileTime.h"
#include "FileTimeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 对话框数据
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileTimeDlg 对话框



CFileTimeDlg::CFileTimeDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CFileTimeDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTimeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, m_button_browse);
    DDX_Control(pDX, IDC_BUTTON2, m_button_ok);
    DDX_Control(pDX, IDC_BUTTON3, m_button_language);
    DDX_Control(pDX, IDC_BUTTON4, m_button_message);
    DDX_Control(pDX, IDC_BUTTON5, m_button_creation);
    DDX_Control(pDX, IDC_BUTTON6, m_button_modify);
    DDX_Control(pDX, IDC_BUTTON7, m_button_lastAccess);
    DDX_Control(pDX, IDC_DATETIMEPICKER1, m_creationTime);
    DDX_Control(pDX, IDC_DATETIMEPICKER2, m_modifyTime);
    DDX_Control(pDX, IDC_DATETIMEPICKER3, m_lastAccessTime);
    DDX_Control(pDX, IDC_EDIT1, m_edit_filter);
    DDX_Control(pDX, IDC_STATIC1, m_static_path);
    DDX_Control(pDX, IDC_STATIC2, m_static_filter);
    DDX_Control(pDX, IDC_STATIC3, m_static_apply);
    DDX_Control(pDX, IDC_STATIC4, m_static_setting);
    DDX_Control(pDX, IDC_STATIC5, m_static_sync);
    DDX_Control(pDX, IDC_STATIC6, m_static_time);
    DDX_Control(pDX, IDC_CHECK1, m_check_folders);
    DDX_Control(pDX, IDC_CHECK2, m_check_subfolders);
    DDX_Control(pDX, IDC_CHECK3, m_check_creation);
    DDX_Control(pDX, IDC_CHECK4, m_check_modify);
    DDX_Control(pDX, IDC_CHECK5, m_check_lastAccess);
}

BEGIN_MESSAGE_MAP(CFileTimeDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON1, &CFileTimeDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CFileTimeDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CFileTimeDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CFileTimeDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CFileTimeDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CFileTimeDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CFileTimeDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CFileTimeDlg 消息处理程序

BOOL CFileTimeDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);            // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    ModifyStyle(0, WS_MINIMIZEBOX);
    GetSystemMenu(FALSE)->InsertMenuW(-1, MF_BYPOSITION, SC_MINIMIZE, _T("最小化"));

    m_creationTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
    m_modifyTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
    m_lastAccessTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

    m_check_folders.SetCheck(TRUE);
    m_check_subfolders.SetCheck(TRUE);
    m_check_creation.SetCheck(TRUE);
    m_check_modify.SetCheck(TRUE);
    m_check_lastAccess.SetCheck(TRUE);

    MoveWindow(CRect(0, 0, 350, 350));

    int windowW, windowH;
    int clientW, clientH;
    int frameW, frameH;
    int buttonW, buttonH;
    int editW, editH;
    int timeW, timeH;
    int checkH;
    int staticH;
    int textH;

    CRect rt;

    GetWindowRect(&rt);
    windowW = rt.Width();
    windowH = rt.Height();

    GetClientRect(&rt);
    clientW = rt.Width();
    clientH = rt.Height();

    frameW = windowW - clientW;
    frameH = windowH - clientH;

    m_button_browse.GetWindowRect(&rt);
    buttonW = rt.Width();
    buttonH = rt.Height();

    m_edit_filter.GetWindowRect(&rt);
    editW = rt.Width();
    editH = rt.Height();

    m_creationTime.GetWindowRect(&rt);
    timeW = rt.Width();
    timeH = rt.Height();

    m_check_creation.GetWindowRect(&rt);
    checkH = rt.Height();

    m_static_filter.GetWindowRect(&rt);
    staticH = rt.Height();

    textH = staticH;

    clientW = 5 + 10 + 10 + buttonW + 10 + 5 + 10 + timeW + 10 + checkH + 10 + 10 + 5;
    clientH = 5 + textH + 5 + buttonH + 5 + staticH + 2 + editH + 10
        + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10 + 10
        + 5 + checkH + 15 + buttonH + 15;

    windowW = clientW + frameW;
    windowH = clientH + frameH;
    MoveWindow(CRect(0, 0, windowW, windowH));

    int x, y, n;
    double t;

    m_static_apply.MoveWindow(CRect(5, 5,
        clientW - 5, 5 + textH + 5 + buttonH + 5 + staticH + 2 + editH + 10));
    n = int((buttonH - textH) / 2.0 + 0.5);
    m_static_path.MoveWindow(CRect(5 + 10 + 2, 5 + textH + 5 + n,
        clientW - 5 - 10 - buttonW - 10, 5 + textH + 5 + n + buttonH));
    m_button_browse.MoveWindow(clientW - 5 - 10 - buttonW, 5 + textH + 5,
        buttonW, buttonH);
    m_static_filter.MoveWindow(5 + 10, 5 + textH + 5 + buttonH + 5,
        clientW - (5 + 10) * 2, staticH);
    m_edit_filter.MoveWindow(5 + 10, 5 + textH + 5 + buttonH + 5 + staticH + 2,
        clientW - (5 + 10) * 2, editH);

    x = 5 + 10 + 10 + buttonW + 10 + 5;
    y = 5 + textH + 5 + buttonH + 5 + staticH + 2 + editH + 10;
    m_static_setting.MoveWindow(CRect(5, y + 5,
        clientW - 5, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10 + 10));
    m_static_sync.MoveWindow(CRect(5 + 10, y + 5 + textH + 5,
        5 + 10 + 10 + buttonW + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10));
    m_button_creation.MoveWindow(5 + 10 + 10, y + 5 + textH + 5 + textH + 5,
        buttonW, buttonH);
    m_button_modify.MoveWindow(5 + 10 + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5,
        buttonW, buttonH);
    m_button_lastAccess.MoveWindow(5 + 10 + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5,
        buttonW, buttonH);
    m_static_time.MoveWindow(CRect(x, y + 5 + textH + 5,
        clientW - 5 - 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10));
    m_creationTime.MoveWindow(x + 10, y + 5 + textH + 5 + textH + 5,
        timeW, buttonH);
    m_modifyTime.MoveWindow(x + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5,
        timeW, buttonH);
    m_lastAccessTime.MoveWindow(x + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5,
        timeW, buttonH);
    n = int((buttonH - checkH) / 2.0 + 0.5);
    m_check_creation.MoveWindow(x + 10 + timeW + 10, y + 5 + textH + 5 + textH + 5 + n,
        checkH, checkH);
    m_check_modify.MoveWindow(x + 10 + timeW + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + n,
        checkH, checkH);
    m_check_lastAccess.MoveWindow(x + 10 + timeW + 10, y + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + n,
        checkH, checkH);

    y = 5 + textH + 5 + buttonH + 5 + staticH + 2 + editH + 10
        + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10 + 10;
    m_check_folders.MoveWindow(CRect(20, y + 5,
        clientW / 2 - 5, y + 5 + checkH));
    m_check_subfolders.MoveWindow(CRect(clientW / 2 + 5, y + 5,
        clientW - 20, y + 5 + checkH));

    y = 5 + textH + 5 + buttonH + 5 + staticH + 2 + editH + 10
        + 5 + textH + 5 + textH + 5 + buttonH + 5 + buttonH + 5 + buttonH + 10 + 10
        + 5 + checkH;
    t = (clientW - 2 - 2 - buttonW * 3) / 4.0;
    m_button_message.MoveWindow(int(2 + t + 0.5), y + 15,
        buttonW, buttonH);
    m_button_ok.MoveWindow(int(2 + t + buttonW + t + 0.5), y + 15,
        buttonW, buttonH);
    m_button_language.MoveWindow(int(2 + t + buttonW + t + buttonW + t + 0.5), y + 15,
        buttonW, buttonH);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileTimeDlg::OnPaint()
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
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileTimeDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



static int gLanguage = 0;
static CString gPath;
static CString gFailedPath = _T("Failed:");
static CString gSucceedPath = _T("Succeed:");
static int gFailedCount = 0, gSucceedCount = 0;


HBRUSH CFileTimeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    return hbr;
}


BOOL CFileTimeDlg::modifyFileTime(const CString pathName, const SYSTEMTIME *lpsctime, const SYSTEMTIME *lpsatime, const SYSTEMTIME *lpswtime)
{
    // TODO: 在此添加控件通知处理程序代码
    HANDLE hFile = CreateFile(pathName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, 
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    if(m_check_creation.GetCheck() == BST_CHECKED)
    {
        FILETIME lfctime, fctime;
        if(!SystemTimeToFileTime(lpsctime, &lfctime))
        {
            CloseHandle(hFile);
            return FALSE;
        }
        LocalFileTimeToFileTime(&lfctime, &fctime);
        if(!SetFileTime(hFile, &fctime, NULL, NULL))
        {
            CloseHandle(hFile);
            return FALSE;
        }
    }
    if(m_check_lastAccess.GetCheck() == BST_CHECKED)
    {
        FILETIME lfatime, fatime;
        if(!SystemTimeToFileTime(lpsatime, &lfatime))
        {
            CloseHandle(hFile);
            return FALSE;
        }
        LocalFileTimeToFileTime(&lfatime, &fatime);
        if(!SetFileTime(hFile, NULL, &fatime, NULL))
        {
            CloseHandle(hFile);
            return FALSE;
        }
    }
    if(m_check_modify.GetCheck() == BST_CHECKED)
    {
        FILETIME lfwtime, fwtime;
        if(!SystemTimeToFileTime(lpswtime, &lfwtime))
        {
            CloseHandle(hFile);
            return FALSE;
        }
        LocalFileTimeToFileTime(&lfwtime, &fwtime);
        if(!SetFileTime(hFile, NULL, NULL, &fwtime))
        {
            CloseHandle(hFile);
            return FALSE;
        }
    }

    CloseHandle(hFile);

    return TRUE;
}


void CFileTimeDlg::modifyDirectoryTime(const CString directoryPath, const CString fileFilter)
{
    CFileFind finder;
    CString endBackSlash = directoryPath.Right(1) == _T("\\") ? _T("") : _T("\\");
    BOOL bWorking = finder.FindFile(directoryPath + endBackSlash + _T("*"));
    while(bWorking)
    {
        bWorking = finder.FindNextFile();
        if(finder.IsDots())
            continue;
        if(finder.IsDirectory())
        {
            if(m_check_folders.GetCheck() == BST_CHECKED)
            {
                SYSTEMTIME sctime, satime, swtime;
                m_creationTime.GetTime(&sctime);
                m_lastAccessTime.GetTime(&satime);
                m_modifyTime.GetTime(&swtime);
                if(modifyFileTime(finder.GetFilePath(), &sctime, &satime, &swtime))
                    gSucceedPath += _T("\r\n") + finder.GetFilePath(), gSucceedCount++;
                else
                    gFailedPath += _T("\r\n") + finder.GetFilePath(), gFailedCount++;
            }
            modifyDirectoryTime(finder.GetFilePath(), fileFilter);
        }
        else
        {
            SYSTEMTIME sctime, satime, swtime;
            m_creationTime.GetTime(&sctime);
            m_lastAccessTime.GetTime(&satime);
            m_modifyTime.GetTime(&swtime);
            if(modifyFileTime(finder.GetFilePath(), &sctime, &satime, &swtime))
                gSucceedPath += _T("\r\n") + finder.GetFilePath(), gSucceedCount++;
            else
                gFailedPath += _T("\r\n") + finder.GetFilePath(), gFailedCount++;
        }
    }
    finder.Close();
}


int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    switch(uMsg)
    {
    case BFFM_INITIALIZED:
        ::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)(LPCTSTR)gPath);
        break;

    case BFFM_SELCHANGED:
        {
            TCHAR buffer[MAX_PATH];
            if(SHGetPathFromIDList((LPCITEMIDLIST)lParam, buffer))
                ::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)buffer);
        }
        break;

    default:
        break;
    }
    return 0;
}


void CFileTimeDlg::OnBnClickedButton1()
{
    // TODO: 在此添加控件通知处理程序代码
    BROWSEINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.hwndOwner = this->m_hWnd;
    bi.lpszTitle = _T("Select a file or folder:");
    bi.ulFlags = BIF_BROWSEINCLUDEFILES;
    bi.lpfn = BrowseCallbackProc;
    LPITEMIDLIST pIDL = SHBrowseForFolder(&bi);
    if(pIDL)
    {
        gFailedPath = _T("Failed:");
        gSucceedPath = _T("Succeed:");
        gFailedCount = gSucceedCount = 0;

        TCHAR buffer[MAX_PATH];
        if(SHGetPathFromIDList(pIDL, buffer))
        {
            PWSTR name;
            SIGDN sigdn;
            memset(&sigdn, 0, sizeof(sigdn));
            if(SHGetNameFromIDList(pIDL, sigdn, &name) == S_OK)
                m_static_path.SetWindowText(name);

            gPath = buffer;

            CFileStatus status;
            if(CFile::GetStatus(gPath, status))
            {
                m_creationTime.SetTime(&status.m_ctime);
                m_modifyTime.SetTime(&status.m_mtime);
                m_lastAccessTime.SetTime(&status.m_atime);
                UpdateData(FALSE);
            }
        }
        IMalloc *malloc = NULL;
        if(SUCCEEDED(SHGetMalloc(&malloc)))
        {
            malloc->Free(pIDL);
            malloc->Release();
        }
    }
}


void CFileTimeDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if(!PathFileExists(gPath))
    {
        MessageBox(_T("File or directory is not valid!"), _T("Message"));
        return;
    }

    gFailedPath = _T("Failed:");
    gSucceedPath = _T("Succeed:");
    gFailedCount = gSucceedCount = 0;

    CString fileFilter;
    m_edit_filter.GetWindowText(fileFilter);

    if(GetFileAttributes(gPath) & FILE_ATTRIBUTE_DIRECTORY)
    {
        if(m_check_folders.GetCheck() == BST_CHECKED)
        {
            SYSTEMTIME sctime, satime, swtime;
            m_creationTime.GetTime(&sctime);
            m_lastAccessTime.GetTime(&satime);
            m_modifyTime.GetTime(&swtime);
            if(modifyFileTime(gPath, &sctime, &satime, &swtime))
                gSucceedPath += _T("\r\n") + gPath, gSucceedCount++;
            else
                gFailedPath += _T("\r\n") + gPath, gFailedCount++;
        }
        if(m_check_subfolders.GetCheck() == BST_CHECKED)
            modifyDirectoryTime(gPath, fileFilter);
    }
    else
    {
        SYSTEMTIME sctime, satime, swtime;
        m_creationTime.GetTime(&sctime);
        m_lastAccessTime.GetTime(&satime);
        m_modifyTime.GetTime(&swtime);
        if(modifyFileTime(gPath, &sctime, &satime, &swtime))
            gSucceedPath += _T("\r\n") + gPath, gSucceedCount++;
        else
            gFailedPath += _T("\r\n") + gPath, gFailedCount++;
    }

    CString message;
    CString count;
    count.Format(_T("%d"), gFailedCount);
    message = _T("Failed: ") + count;
    count.Format(_T("%d"), gSucceedCount);
    message += _T("\r\n\r\nSucceed: ") + count;
    MessageBox(message, _T("Result"));
}


void CFileTimeDlg::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    gLanguage = (gLanguage + 1) % 2;
    if(gLanguage == 0)
    {
        m_button_browse.SetWindowText(_T("Browse"));
        m_button_ok.SetWindowText(_T("OK"));
        m_button_language.SetWindowText(_T("中文"));
        m_button_message.SetWindowText(_T("Message"));
        m_button_creation.SetWindowText(_T("Created"));
        m_button_modify.SetWindowText(_T("Modified"));
        m_button_lastAccess.SetWindowText(_T("Last accessed"));
        m_static_filter.SetWindowText(_T("File filter"));
        m_static_apply.SetWindowText(_T("Apply to"));
        m_static_setting.SetWindowText(_T("Setting"));
        m_static_sync.SetWindowText(_T("Sync"));
        m_static_time.SetWindowText(_T("Time"));
        m_check_folders.SetWindowText(_T("Apply to folders"));
        m_check_subfolders.SetWindowText(_T("Search in subfolders"));
    }
    else
    {
        m_button_browse.SetWindowText(_T("打开"));
        m_button_ok.SetWindowText(_T("确认"));
        m_button_language.SetWindowText(_T("English"));
        m_button_message.SetWindowText(_T("信息"));
        m_button_creation.SetWindowText(_T("创建时间"));
        m_button_modify.SetWindowText(_T("修改时间"));
        m_button_lastAccess.SetWindowText(_T("访问时间"));
        m_static_filter.SetWindowText(_T("关键字"));
        m_static_apply.SetWindowText(_T("应用于"));
        m_static_setting.SetWindowText(_T("设置"));
        m_static_sync.SetWindowText(_T("同步为"));
        m_static_time.SetWindowText(_T("时间"));
        m_check_folders.SetWindowText(_T("修改文件夹时间"));
        m_check_subfolders.SetWindowText(_T("搜索子文件夹"));
    }
}


void CFileTimeDlg::OnBnClickedButton4()
{
    // TODO: 在此添加控件通知处理程序代码
    if(!PathFileExists(gPath))
    {
        MessageBox(_T("File or directory is not valid!"), _T("Message"));
        return;
    }

    CString message = gFailedPath + _T("\r\n\r\n") + gSucceedPath;
    CString count;
    count.Format(_T("%d"), gFailedCount);
    message.Replace(_T("Failed:"), _T("Failed: ") + count);
    count.Format(_T("%d"), gSucceedCount);
    message.Replace(_T("Succeed:"), _T("Succeed: ") + count);
    MessageBox(message, _T("Message"));
}


void CFileTimeDlg::OnBnClickedButton5()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileStatus status;
    CTime ctime;
    m_creationTime.GetTime(ctime);
    m_modifyTime.SetTime(&ctime);
    m_lastAccessTime.SetTime(&ctime);
    UpdateData(FALSE);
}


void CFileTimeDlg::OnBnClickedButton6()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileStatus status;
    CTime ctime;
    m_modifyTime.GetTime(ctime);
    m_creationTime.SetTime(&ctime);
    m_lastAccessTime.SetTime(&ctime);
    UpdateData(FALSE);
}


void CFileTimeDlg::OnBnClickedButton7()
{
    // TODO: 在此添加控件通知处理程序代码
    CFileStatus status;
    CTime ctime;
    m_lastAccessTime.GetTime(ctime);
    m_creationTime.SetTime(&ctime);
    m_modifyTime.SetTime(&ctime);
    UpdateData(FALSE);
}
