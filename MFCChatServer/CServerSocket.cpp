#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("####OnAccept");
	CMFCChatServerDlg* dlg =(CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));
	/*CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str=dlg->m_tm.Format("%X");
	str += _T("客户端连接成功");*/
	CString strShow;
	CString strInfo = _T("客户端连接成功");
	strShow = dlg->CatShowString(strInfo, _T(""));
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);
}
