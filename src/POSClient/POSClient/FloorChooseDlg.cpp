// FloorChooseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "FloorChooseDlg.h"
#include "FloorDlg.h"
#include "TableButton.h"

#define ITEM_COLUMNSIZE 7
#define ITEM_LINESIZE	4
// CFloorChooseDlg 对话框

IMPLEMENT_DYNAMIC(CFloorChooseDlg, CDialog)

CFloorChooseDlg::CFloorChooseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFloorChooseDlg::IDD, pParent)
{
	m_nPageSize=ITEM_LINESIZE*ITEM_COLUMNSIZE-2;//每页的大小，需扣除翻页按钮
	m_nFilterId=-1;
	m_nNoUsedTable=0;
	m_bMultiSelect=FALSE;
}

CFloorChooseDlg::~CFloorChooseDlg()
{
	for (std::vector<CButton*>::iterator iter = m_itemButtons.begin(); iter!= m_itemButtons.end();iter++)
	{
		CButton *b = (*iter);
		b->DestroyWindow();
		delete b;
	}
	m_itemButtons.clear();
	for (int i=0;i<6;i++)
	{
		delete m_bpTableStatus[i];
	}
	
}

void CFloorChooseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDOK, m_btOK);
}


BEGIN_MESSAGE_MAP(CFloorChooseDlg, CDialog)
	ON_COMMAND_RANGE(IDC_CLASS_BUTTON,IDC_CLASS_BUTTON+99, &CFloorChooseDlg::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CFloorChooseDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CFloorChooseDlg::OnBnClickedButtonRight)
	ON_COMMAND_RANGE(IDC_TABLE0,IDC_TABLE0+999,&CFloorChooseDlg::OnTableClicked)
	ON_BN_CLICKED(IDOK, &CFloorChooseDlg::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFloorChooseDlg 消息处理程序
BOOL CFloorChooseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!m_strTitle.IsEmpty())
	{
		SetWindowText(m_strTitle);
	}
	else
	{
		theLang.LoadString(m_strTitle,IDS_CHOOSETABLE);
		SetWindowText(m_strTitle);
	}
	CString str2;
	m_btOK.SetImage(_T("Picture\\bt_ok.png"));
	m_btCancel.SetImage(_T("Picture\\bt_cancel.png"));
	m_btCancel.SetTextColor(DEFALUT_TXT_COLOR);
	m_btOK.SetTextColor(DEFALUT_TXT_COLOR);
	theLang.LoadString(str2,IDS_CANCEL);
	m_btCancel.SetWindowText(str2);
	theLang.LoadString(str2,IDS_OK);
	m_btOK.SetWindowText(str2);
	if (!m_bMultiSelect)
	{
		m_btCancel.MoveWindow(ScaleX(250),ScaleY(450),ScaleX(130),ScaleY(60));
		m_btOK.ShowWindow(SW_HIDE);
	}
	SIZE buttonSize;
	CString path;
	for(int i=0;i<6;i++)
	{
		path.Format(_T("Picture\\table%d.png"),i+1);
		m_bpTableStatus[i]=Gdiplus::Image::FromFile(path);
		if(i==0)
		{
			buttonSize.cx=ScaleX(m_bpTableStatus[i]->GetWidth());
			buttonSize.cy=ScaleY(m_bpTableStatus[i]->GetHeight());
		}
	}

	LOGFONT m_tLogFont;
	memset(&m_tLogFont,0,sizeof(LOGFONT));
	m_tLogFont.lfHeight	=ScaleX(20);
	wcscpy_s(m_tLogFont.lfFaceName, _T("Microsoft YaHei"));
	mTableFont.CreateFontIndirect(&m_tLogFont);
	for(int i=0;i<ITEM_LINESIZE;i++)
	{
		POINT topleft;
		topleft.y=15+i*(buttonSize.cy+8);
		CString str2;
		for(int j=0;j<ITEM_COLUMNSIZE;j++)
		{
			int count=i*ITEM_COLUMNSIZE+j;
			topleft.x=30+j*(buttonSize.cx+5);
			//最后2个按钮为翻页按钮
			if (count==m_nPageSize)
			{//前一页
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_LEFT);
				pBtn->SetImage(_T("Picture\\bt_up.png"));
				m_itemButtons.push_back(pBtn);
			}
			else if (count==m_nPageSize+1)
			{//后一页
				CRoundButton2* pBtn=new CRoundButton2;
				pBtn->Create(_T(""),WS_CHILD ,CRect(topleft,buttonSize),this,IDC_BUTTON_RIGHT);
				pBtn->SetImage(_T("Picture\\bt_down.png"));
				m_itemButtons.push_back(pBtn);
			}
			else
			{
				CTableButton* pBtn=new CTableButton;
				pBtn->SetFont(&mTableFont);
				pBtn->Create(_T(""),WS_CHILD,CRect(topleft,buttonSize),this,IDC_TABLE0+count);
				pBtn->SetImages(m_bpTableStatus[0],m_bpTableStatus[0],false);
				m_itemButtons.push_back(pBtn);
			}
		}
	}

	try{
		//读取营业地点
		CRecordset rs( &theDB);
		CString strSQL;
		strSQL.Format(_T("SELECT * FROM rvc_center ORDER BY rvc_center_id"));
		if(rs.Open(CRecordset::forwardOnly,strSQL))
		{
			CDBVariant variant;
			CString strName;
			CRect _rect=CRect(ScaleX(10),ScaleY(400),ScaleX(110),ScaleY(420));
			CButton* pBtn=new CButton;
			theLang.LoadString(strName,IDS_ALL);
			pBtn->Create(strName, WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON| WS_GROUP, _rect,this,IDC_CLASS_BUTTON);
			pBtn->SetCheck(TRUE);
			pBtn->SetFont(GetFont());
			int count=0;
			while(!rs.IsEOF())
			{
				count++;
				_rect.left+=ScaleX(100);
				_rect.right+=ScaleX(100);
				if(count==6)
				{
					_rect.top+=ScaleY(22);
					_rect.bottom+=ScaleY(22);
					_rect.left=ScaleX(10);
					_rect.right=ScaleX(110);
				}
				rs.GetFieldValue(_T("rvc_center_id"),variant);
				rs.GetFieldValue(_T("rvc_center_name"),strName);
				CButton* pBtn=new CButton;
				pBtn->Create(strName, WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, _rect,this, IDC_CLASS_BUTTON+variant.m_iVal);
				pBtn->SetFont(GetFont()); //设置为父窗口的字体
				rs.MoveNext();
			}
		}
		rs.Close();
	}catch(...)
	{
	}
	UpdateRvc(0,TRUE);
	return TRUE; 
}

/************************************************************************
* 函数介绍：显示当前页的桌子
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CFloorChooseDlg::ShowCurrentPage()
{
	try{
		unsigned int index;
		for(int i=0;i<m_nPageSize;i++)
		{
			index=i+m_nCurrentPage*m_nPageSize;
			CTableButton* pButton2=(CTableButton*)GetDlgItem(IDC_TABLE0+i);
			if(index<m_RVCTables.size())
			{
				TableItem table=m_RVCTables[index];
				pButton2->SetWindowText(m_strPrefix+table.name);
				pButton2->SetImages(m_bpTableStatus[table.status],m_bpTableStatus[table.status],false);
				pButton2->Invalidate();
				if(m_bMultiSelect)
				{
					
					if (find(m_tableList.begin(),m_tableList.end(),table.id)!=m_tableList.end())
						pButton2->SetCheck(TRUE);
					else
						pButton2->SetCheck(FALSE);
				}
				pButton2->ShowWindow(SW_SHOW);
			}
			else
			{
				pButton2->ShowWindow(SW_HIDE);
			}
		}
		CWnd* pButton2=GetDlgItem(IDC_BUTTON_LEFT);
		if (m_nCurrentPage>0)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);

		pButton2=GetDlgItem(IDC_BUTTON_RIGHT);
		if (m_nCurrentPage<m_nPageCount-1)
			pButton2->ShowWindow(SW_SHOW);
		else
			pButton2->ShowWindow(SW_HIDE);
	}
	catch(...)
	{
		LOG4CPLUS_ERROR(log_pos,"Catch Exception GetLastError="<<GetLastError());
	}
}

void CFloorChooseDlg::OnBnClickedRadio(UINT uID)
{
	int rvc_id=uID-IDC_CLASS_BUTTON;
	UpdateRvc(rvc_id,TRUE);
}
void CFloorChooseDlg::UpdateRvc(int rvc_id,BOOL reset)
{
	m_RVCTables.clear();
	vector<TableItem>::iterator iter;
	if(rvc_id==0)
	{
		for (iter=FloorDlg::m_Tables.begin();iter!=FloorDlg::m_Tables.end();iter++)
		{
			if (iter->id!=m_nFilterId)
			{
				if (m_nNoUsedTable==1&&iter->status>1)
					continue;
				m_RVCTables.push_back(*iter);
			}
		}
	}
	else
	{
		for (iter=FloorDlg::m_Tables.begin();iter!=FloorDlg::m_Tables.end();iter++)
		{
			if (rvc_id==iter->rvc&&iter->id!=m_nFilterId)
			{
				if (m_nNoUsedTable==1&&iter->status>1)
					continue;
				m_RVCTables.push_back(*iter);
			}
		}
	}
	//m_nCurrentRvc=rvc_id;
	if(reset)
		m_nCurrentPage=0;
	m_nPageCount=(int)ceil((float)m_RVCTables.size()/m_nPageSize);
	ShowCurrentPage();
}
/************************************************************************
* 函数介绍： 桌台显示翻页
* 输入参数：
* 输出参数：
* 返回值  ：
************************************************************************/
void CFloorChooseDlg::OnBnClickedButtonLeft()
{
	if(m_nCurrentPage>0)
		m_nCurrentPage--;
	else
		return;
	ShowCurrentPage();
}

void CFloorChooseDlg::OnBnClickedButtonRight()
{
	if(m_nCurrentPage<m_nPageCount-1)
		m_nCurrentPage++;
	else
		return;
	ShowCurrentPage();
}
void CFloorChooseDlg::OnTableClicked(UINT uID)
{
	UINT index=m_nCurrentPage*m_nPageSize+(uID-IDC_TABLE0);
	if (index>=m_RVCTables.size())
	{//越界
		LOG4CPLUS_ERROR(log_pos,"index=["<<index<<"] out of range. m_RVCTables.size()="<<m_RVCTables.size());
		return;
	}
	if (m_bMultiSelect)
	{//加入列表
		CTableButton* pButton2=(CTableButton*)GetDlgItem(uID);
		//先修改状态
		BOOL bCheck=pButton2->GetCheck();
		bCheck=!bCheck;
		pButton2->SetCheck(bCheck);
		if (bCheck==TRUE)
		{
			m_tableList.push_back(m_RVCTables[index].id);
		}
		else
		{
			std::vector<int>::iterator iter=find(m_tableList.begin(),m_tableList.end(),m_RVCTables[index].id);
			if(iter!=m_tableList.end())
			{
				m_tableList.erase(iter);
			}
		}
		return;
	}
	m_nTableId=m_RVCTables[index].id;
	CDialog::OnOK();

}
void CFloorChooseDlg::OnBnClickedOk()
{
	OnOK();
}

void CFloorChooseDlg::OnPaint()
{
	if(!IsIconic())
	{
		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect,DEFALUT_BACKGROUND_COLOR);
 		CDialog::OnPaint();
	}
}
