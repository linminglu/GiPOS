// SortListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "POSClient.h"
#include "SortListCtrl.h"

CSortListCtrl::CSortListCtrl(void)
: m_bAsc(false)
, m_nSortedCol(0)
{
}
CSortListCtrl::~CSortListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
 ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CSortListCtrl::OnLvnColumnclick)
END_MESSAGE_MAP()
int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
 CSortListCtrl* pList = (CSortListCtrl*)lParamSort;
 int nItem1,nItem2;
 LVFINDINFO FindInfo;
 FindInfo.flags = LVFI_PARAM;
 FindInfo.lParam = lParam1;
 nItem1 = pList->FindItem(&FindInfo, -1);
 FindInfo.lParam = lParam2;
 nItem2 = pList->FindItem(&FindInfo, -1);
 if((nItem1 == -1) || (nItem2 == -1))
 {
  return 0;
 }
 CString str1, str2;
 str1 = pList->GetItemText(nItem1, pList->m_nSortedCol);
 str2 = pList->GetItemText(nItem2, pList->m_nSortedCol);
 HDITEM headerItem;
 headerItem.mask = HDI_LPARAM;
 CHeaderCtrl* pHeaderCtrl = pList->GetHeaderCtrl( );
 pHeaderCtrl->GetItem(pList->m_nSortedCol, &headerItem);
 int iCompRes = 0;

 if(str1> str2)
	 iCompRes = 1;
 else if(str1< str2)
	 iCompRes = -1;
 else
	 iCompRes = 0;

 if(pList->m_bAsc)
  return iCompRes;
 else
  return iCompRes * -1;
 return 0;
}
void CSortListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
 LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
 // TODO: 在此添加控件通知处理程序代码
 if(pNMLV->iSubItem == m_nSortedCol)
 {
  m_bAsc = !m_bAsc;
 }
 else
 {
  m_bAsc = TRUE;
  m_nSortedCol = pNMLV->iSubItem;
 }
 //非常重要，不能遗漏
 //********************************************************
//  int num = this->GetItemCount(); 
//     while(num--)
//   this->SetItemData(num, num); 
 //********************************************************
 SortItems(ListCompare, (DWORD)this);
 UpdateData(FALSE);
 *pResult = 0;
}

