/** @file    vipPlugIn_.cpp
 *
 *  @brief   Defines the entry point for the DLL application.
 *
 *
 *  @see     %CLASSNAME%
 *
 *  @version 1.0.
 *  @date    28/10/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.0.2
 *  Copyright (C) Alessandro Polo 2006
 *  http://www.ewgate.net/viplib
 *
 ****************************************************************************/

#include <windows.h>

#include "WS_DLL_13_GUI.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////// SETUP MODULE HERE
//////////////////////////////////////////////////////////////////////////////

// Display a dialog box
//
int DoDialog(HWND hwndParent, int DialogID, DLGPROC fnDialog, long lParam)
{
    DLGPROC fn;
    int result;

    fn = (DLGPROC)MakeProcInstance(fnDialog, ghInstApp);
    result = (int) DialogBoxParam(ghInstApp,
                                  MAKEINTRESOURCE(DialogID),
                                  hwndParent,
                                  fn,
                                  lParam);
    FreeProcInstance(fn);

    return result;
}



/* AboutDlgProc()
 *
 * Dialog Procedure for the "about" dialog box.
 *
 */

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            EndDialog(hwnd, TRUE);
            return TRUE;

        case WM_INITDIALOG:
            return TRUE;
    }
    return FALSE;
}


int FAR PASCAL MainProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam)
 {


    switch(Message)
    {
        case WM_INITDIALOG:
        {
            DWORDLONG        dwlFileSize = 0;
            long             lFreeSpaceInKB;


            SetDlgItemInt(hDlg, IDD_SetCapFileSize, gcap.wCapFileSize, TRUE) ;
            return TRUE ;
        }

        case WM_COMMAND :
            switch(GET_WM_COMMAND_ID(wParam, lParam))
            {
                case IDOK :
                {
                    int iCapFileSize ;

                    iCapFileSize = (int) GetDlgItemInt(hDlg, IDD_SetCapFileSize, NULL, TRUE) ;
                    if(iCapFileSize <= 0 || iCapFileSize > nFreeMBs)
                    {
                        // You are asking for more than we have !! Sorry, ...
                        SetDlgItemInt(hDlg, IDD_SetCapFileSize, iCapFileSize, TRUE) ;
                        SetFocus(GetDlgItem(hDlg, IDD_SetCapFileSize)) ;
                        MessageBeep(MB_ICONEXCLAMATION) ;
                        return FALSE ;
                    }
                    gcap.wCapFileSize = (WORD)iCapFileSize ;

                    EndDialog(hDlg, TRUE) ;
                    return TRUE ;
                }

                case IDCANCEL :
                    EndDialog(hDlg, FALSE) ;
                    return TRUE ;

                case IDD_SetCapFileSize:
                {

                }
            }
            break;
    }

    return FALSE ;
}



