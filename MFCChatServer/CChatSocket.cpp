#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	TRACE("##Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szReceiveBuf[MAX_SERVER_BUF] = { 0 };
	Receive(szReceiveBuf, MAX_SERVER_BUF, 0);
	TRACE("##Server szReceiveBuf=%s", szReceiveBuf);
	USES_CONVERSION;
	CString strRecvMsg = A2W(szReceiveBuf);
	/*CString strTime;
	CString strShow = _T("¿Í»§¶Ë:");
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");
	strShow = strTime + strShow;
	strShow += strRecvMsg;*/
	CString strShow;
	CString strInfo = _T("");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);

}
