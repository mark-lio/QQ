
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatServerDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCChatServerDlg::OnBnClickedStopBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BTN, &CMFCChatServerDlg::OnBnClickedCalBtn)
	ON_BN_CLICKED(IDC_EMAIL_BTN, &CMFCChatServerDlg::OnBnClickedEmailBtn)
	ON_BN_CLICKED(IDC_QQ_BTN, &CMFCChatServerDlg::OnBnClickedQqBtn)
	ON_BN_CLICKED(IDC_BAIDU_BTN, &CMFCChatServerDlg::OnBnClickedBaiduBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("4399"));

	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));
	m_WordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatServerDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP_light);
		BITMAP bmp;
		bmpBackground.GetBitmap(&bmp);
		CBitmap* pBmp = dcBmp.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
			0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg) {
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	TRACE("##OnBnClickedStartBtn");
	CString strPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("port=%s", szPort);
	int iPort = _ttoi(strPort);
	m_server = new CServerSocket;
	if (!m_server->Create(iPort)) {
		TRACE("m_server->Create(iPort) fail ,errorCode=%d",GetLastError());
		return;
	}
	else {
		TRACE("m_server->Create(iPort) success");
	}
	if (!m_server->Listen()) {
		TRACE("m_server->Listen() error,errorCode=%d", GetLastError());
		return;
	}
	/*CString str;
	m_tm = CTime::GetCurrentTime();
	str=m_tm.Format("%X");
	str += _T("建立服务");*/
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("建立服务");
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowText(strTmpMsg);
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);
	m_chat->Send(szSendBuf, MAX_SERVER_BUF, 0);
	/*CString strShow = _T("服务端:");
	CString strTime;
	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X");
	strShow = strTime + strShow;
	strShow += strTmpMsg;*/
	CString strShow;
	CString strInfo = _T("服务端:");
	strShow = CatShowString(strInfo, strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	m_server->Close();
	if (m_server) {
		delete m_server;
		m_server = NULL;
	}
	if (m_chat) {
		delete m_chat;
		m_chat = NULL;
	}
	CString strShow;
	strShow = CatShowString(_T(""), _T("服务器停止"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);
	if (IDC_MSG_LIST== pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == L"黑色") {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色") {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"绿色") {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (strColor == L"蓝色") {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}
	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedEmailBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedQqBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"F:\\TIM\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);

}


void CMFCChatServerDlg::OnBnClickedBaiduBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"https://www.baidu.com", NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN) {
		if (GetKeyState(VK_CONTROL) < 0) {
			if (pMsg->wParam == 'X') {
				CDialogEx::OnOK();
			}
		}

	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
