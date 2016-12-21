#ifndef _CrBtnPara_H
#define _CrBtnPara_H
#include <vector>
#include "roundbutton2.h"

typedef std::vector<CRoundButton2*>CPButtonList;
typedef std::vector<CRoundButton2*>::iterator CPbuttonIter;
typedef struct{

	CString name;
	RECT	rect;//按钮的位置
	//CString icon;//按钮图片的参数
	CString picture;//背景图片
	//CString iconPos;//按钮图片位置
	CString font;//字体
	int fontSize;//字体大小
	//COLORREF bkg_color;//背景颜色
	COLORREF txt_color;//字体颜色
	int txt_pos;//文字位置
	int	next_page;//点击该按钮跳转到哪个页面
	int	function;//点击该按钮执行哪个函数


}CR_BTN_PARA;


//#define GLOBAL		_T("GLOBAL")
#define BTN_NUM		_T("btn_num")


#define BTN_NAME	_T("btn_name")
#define BTN_RECT	_T("rect")
#define BTN_BKG_PIC	_T("pic")
#define BTN_ICON	_T("icon")
#define BTN_ICON_POSITION	_T("icon_position")
#define BTN_FONT	_T("font")
#define BTN_FONT_SIZE	_T("font_size")
#define BTN_BKG_COLOR	_T("bkg_color")
#define BTN_TXT_COLOR	_T("txt_color")
#define BTN_NEXT_PAGE	_T("next_page")
#define BTN_FUNCTION	_T("function")


class CreatButton{
public:
	CreatButton();
	static int m_nFullWidth;
	static int m_nFullHeight;
//private:
	BOOL bSetBk;//按钮透明背景只需要设置一次
public:
	int m_nShowStatus;
	CPButtonList m_buttonList;
	CRect GenaratePage2(CString fileName,CDialog* dlg);
	void CreateBtn2(CR_BTN_PARA btnParam,CDialog* dlg);
	void ReleaseBtn();
	void ShowButtons(int nCmdShow);
	void SetBkGnd(CDC* pDC);
};
#endif