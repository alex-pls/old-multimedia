











int DoDialog(HWND hwndParent, int DialogID, DLGPROC fnDialog, long lParam);


int FAR PASCAL MainProc(HWND hDlg, UINT Message, UINT wParam, LONG lParam);


BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



// Dialogs
#define IDD_ABOUTDIALOG 101








