#include <windows.h>
//#include <winuser.h>
HHOOK g_hKeyboard=NULL;
#pragma data_seg("MySec")
HWND g_hWnd=NULL;
#pragma data_seg()

#pragma comment(linker,"/section:MySec,RWS")

//weishenme
/*
#define WH_KEYBOARD_LL 13

typedef struct tagKBDLLHOOKSTRUCT {

DWORD vkCode;

DWORD scanCode;

DWORD flags;

DWORD time;

DWORD dwExtraInfo;

} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;
*/
//weishenme

LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam){
	if(nCode<0||nCode==HC_NOREMOVE)
    {
        return CallNextHookEx(g_hKeyboard,nCode,wParam,lParam);
    }
	if(lParam&0x40000000)//只对WM_DOWN进行响应。
      {
       PostMessage(g_hWnd,WM_KEYDOWN,wParam,lParam);
	//	PostMessage(g_hWnd,WM_CLOSE,0,0);
		//MessageBox(g_hWnd, "hao",   "111",   IDOK); 
		//::SendMessage(g_hWnd,WM_KEYDOWN,wParam,lParam);
      }

		//UnhookWindowsHookEx(g_hKeyboard);
		return CallNextHookEx(g_hKeyboard,nCode,wParam,lParam);
}
void SetHook(HWND hwnd){
	g_hWnd=hwnd;
	//g_hKeyboard=SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,GetModuleHandle("Hook"),0);
	g_hKeyboard=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,GetModuleHandle("Hook"),0);
}