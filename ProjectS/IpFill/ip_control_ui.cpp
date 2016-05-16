#include "ip_control_ui.h"

IpControlUI::IpControlUI()
{
  vector<LPCTSTR> edit_str = {
    _T("ip_edit_0"),
    _T("ip_edit_1"),
    _T("ip_edit_2"),
    _T("ip_edit_3") 
  };
  for (auto str : edit_str) {
    edit_str_.push_back(str);
  }
}

IpControlUI::~IpControlUI()
{
}

LPVOID IpControlUI::GetInterface(LPCTSTR pstrName)
{
  if (_tcscmp(pstrName, _T("IpControlUI")) == 0)
    return static_cast<IpControlUI*>(this);

  return CHorizontalLayoutUI::GetInterface(pstrName);
}

void IpControlUI::Init()
{
  for (auto str : edit_str_) {
    edit_vector_.push_back(static_cast<PDUI_EDIT>(FindSubControl(str)));
  }

  __super::Init();
}

CDuiString IpControlUI::GetText() const
{
  CDuiString ret = _T("");
  for (auto ip_emle_edit : edit_vector_) {
    ret += ip_emle_edit->GetText();
    ret += _T(".");
  }

  ret = ret.Mid(0, ret.GetLength() - 1);

  return ret;
}

void IpControlUI::SetText(LPCTSTR pstrText)
{
  CDuiString ip_str = pstrText;
  int begin = 0, end = 0;
  for (auto ip_emle_edit : edit_vector_) {
    end = ip_str.Find(_T("."), begin);
    ip_emle_edit->SetText(ip_str.Mid(begin, end - begin));
    begin = end + 1;
  }
}

BOOL IpControlUI::IsReasonable()
{
  for (auto iter : edit_vector_)
    if (iter->GetText() == _T(""))
      return FALSE;

  return TRUE;
}
