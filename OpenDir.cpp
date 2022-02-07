#include "stdafx.h"
#include "shlobj.h" 

#define SIZEOF_ARRAY(ar)  (sizeof(ar)/sizeof((ar)[0]))

// - - - - - - - - - - - - - - - - - - - -

int CALLBACK SHBrowseForFolder_callback(HWND hwnd, UINT uMsg,
                                        LPARAM lParam, LPARAM lpData)  // in Help: BrowseCallbackProc
{
    TCHAR  tszStat[MAX_PATH];

    switch (uMsg)
    {
    case BFFM_INITIALIZED:
        ::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
        break;

    case BFFM_SELCHANGED:
        if (! SHGetPathFromIDList((LPITEMIDLIST) lParam, tszStat))
            tszStat[0] = 0;
        ::SendMessage(hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM) tszStat);
        break;

    }
    return 0;
}

// - - - - - - - - - - - - - - - - - - - -

BOOL SelDirDial(HWND pParentWnd, CString& cs,char *ttt)

// ��� � ���� �y���� �p��p����. �� ����� �������� � ���� ����� ��� ���������
// � �p���� ��������.
// 1-� ��p��. - ����, ����p�� ������ ���� p����������� ��� �������.
// 2-� ��p��. - �� ����� �������� �������, �� ������ ���p�����.
// �p� �����-���� ������� �������� ��� ���������.

{
    LPMALLOC     pMalloc;
    BROWSEINFO   bi;
    TCHAR        tszGettingName[MAX_PATH];
    LPITEMIDLIST pBrItemList;
    LPITEMIDLIST pMyCompItemList;
    TCHAR        tszOldPath[MAX_PATH];

    if (SHGetMalloc(&pMalloc) != NOERROR)
        return false;

    if (SHGetSpecialFolderLocation(pParentWnd, CSIDL_DRIVES,
        &pMyCompItemList) != NOERROR)
    {
        pMalloc->Release();
        return false;
    }

    bi.hwndOwner      = pParentWnd;
    // ����� �p���� ���� �p��p����, ����p�� ������ ���� p�����������
    // ��� ���� �������
    bi.pidlRoot       = pMyCompItemList;
    bi.pszDisplayName = NULL;
    bi.lpszTitle      = NULL;
    bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    bi.lpfn           = SHBrowseForFolder_callback;
    bi.lParam         = (LPARAM) tszOldPath;
    bi.lpszTitle	   = ttt;
    _tcsncpy_s(tszOldPath, (LPCTSTR) cs, SIZEOF_ARRAY(tszOldPath));
    tszOldPath[SIZEOF_ARRAY(tszOldPath)-1] = 0;

    pBrItemList = SHBrowseForFolder(&bi);
    if (pBrItemList != NULL)
    {
        if (SHGetPathFromIDList(pBrItemList, tszGettingName))
            cs = tszGettingName;
        pMalloc->Free(pBrItemList);
    }

    pMalloc->Free(pMyCompItemList);
    pMalloc->Release();
    return pBrItemList != NULL;
}
