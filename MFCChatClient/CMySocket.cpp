#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"
#include "MFCChatClient.h"
CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("####OnConnect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("与服务器连接成功!");
#endif
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("与服务器连接成功!");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("##Client OnReceive");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szReceiveBuf[MAX_SEND_BUF] = { 0 };
	Receive(szReceiveBuf, MAX_SEND_BUF, 0);
	TRACE("##Server szReceiveBuf=%s", szReceiveBuf);
	USES_CONVERSION;
	CString strRecvMsg = A2W(szReceiveBuf);
	/*CString strTime;
	CString strShow = _T("服务端:");
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");
	strShow = strTime + strShow;
	strShow += strRecvMsg;*/
	CString strShow;
	CString strInfo = _T("服务端:");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		CString strMsg = strName+("[自动回复]") + strAutoSendMsg;
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, MAX_SEND_BUF, 0);
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
