
#define INCL_WIN
#define INCL_GPI
#define	INCL_WINWINDOWMGR
#define	INCL_WINMESSAGEMGR
#define ID_WINDOW   256
#define WM_USER_PROC_DLGS (WM_USER + 0)
#define MAXCHALLENGELENGTH	256
#define MAXPASSWORDLENGTH	256
#define MAXRESPONSELENGTH	256
#define MAXSEEDLENGTH		256


#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key.h"
#include "resource.h"

MRESULT EXPENTRY WndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
static void ProcessDialogBoxes(HWND hwnd);
MRESULT EXPENTRY PMKeyDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
void CenterWindow(HWND hwnd);

HAB	hab;

int
main(void)
{
	HMQ  hmq;                             /* Message queue handle         */
	HWND hwndClient = NULLHANDLE;         /* Client area window handle    */
	HWND hwndFrame = NULLHANDLE;          /* Frame window handle          */
	QMSG qmsg;                            /* Message from message queue   */
	ULONG flCreate;                       /* Window creation control flags*/
	char szClientClass[] = "PMKey";

	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);

	if (!WinRegisterClass(hab, szClientClass, (PFNWP)WndProc,
			CS_SIZEREDRAW, 0))
		return 0;

	flCreate = 0;

	if ((hwndFrame = WinCreateStdWindow(HWND_DESKTOP, 0, &flCreate,
			szClientClass, "", 0, (HMODULE)0L, ID_WINDOW, &hwndClient)) == 0L)
		return 0;

	WinSetWindowPos(hwndFrame, HWND_TOP, 0, 0, 0, 0, SWP_SIZE);

	while (WinGetMsg(hab, &qmsg, 0L, 0, 0))
		WinDispatchMsg(hab, &qmsg);
	WinDestroyWindow(hwndFrame);
	WinDestroyMsgQueue(hmq);
	WinTerminate(hab);
	return 0;
}

MRESULT EXPENTRY
WndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			/* Post a user defined message that will execute the dialog boxes*/
			WinPostMsg( hwnd, WM_USER_PROC_DLGS, MPVOID, MPVOID); 
			break;
		}
		case WM_USER_PROC_DLGS:
		{
			ProcessDialogBoxes(hwnd);
			WinPostMsg(hwnd, WM_QUIT, (MPARAM)0, (MPARAM)0);
			break;
		}
	}
	return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

static void ProcessDialogBoxes(HWND hwnd)
{
	WinDlgBox(HWND_DESKTOP, hwnd, PMKeyDlgProc, 0L, ID_PMKEY_DLG, 0);
	return;
}

MRESULT EXPENTRY PMKeyDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
	switch (msg) {
		case WM_INITDLG:
		{
			/* Position the dialog box in the center of the screen */
			CenterWindow(hwnd);
			/* Set the maximum length for the challenge and the password */
			WinSendDlgItemMsg(hwnd, ID_CHALLENGE_EDIT, EM_SETTEXTLIMIT,MPFROMSHORT(MAXCHALLENGELENGTH-1),MPVOID);
			WinSendDlgItemMsg(hwnd, ID_PASSWORD_EDIT, EM_SETTEXTLIMIT,MPFROMSHORT(MAXPASSWORDLENGTH-1),MPVOID);
			WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, ID_CHALLENGE_EDIT));
			return (MRESULT) TRUE;
		}

		case WM_COMMAND:
			switch(SHORT1FROMMP(mp1)) {

				case ID_COMPUTE_BTN:
				{
					static char challenge[MAXCHALLENGELENGTH];
					static char password[MAXPASSWORDLENGTH];
					static char response[MAXRESPONSELENGTH];
					static char seed[MAXSEEDLENGTH];
					int algorithm;
					int keynum;

					WinQueryDlgItemText(hwnd, ID_CHALLENGE_EDIT, 
						MAXCHALLENGELENGTH, challenge);
					WinQueryDlgItemText(hwnd, ID_PASSWORD_EDIT, 
						MAXPASSWORDLENGTH, password);

					if (!KeyParseChallenge(challenge, 
							&algorithm, &keynum, seed))
					{
						WinMessageBox(HWND_DESKTOP, hwnd, 
							"Invalid OTP challenge.", "Error", 
							0, MB_OK | MB_ERROR);
						return (MRESULT) TRUE;
					}

					if (algorithm == -1)
						algorithm = 4;

					if (!KeyGenerateResponse(algorithm, keynum, seed, password,
							response))
					{
						WinMessageBox(HWND_DESKTOP, hwnd, 
							"Key crunch failed.", "Error", 
							0, MB_OK | MB_ERROR);
						return (MRESULT) TRUE;
					}

					WinSetDlgItemText(hwnd, ID_RESPONSE_EDIT, response);

					return (MRESULT) TRUE;
				}

				case ID_EXIT_BTN:
				{
					WinDismissDlg(hwnd, 0);
					return (MRESULT) TRUE;
				}

				default: return WinDefDlgProc(hwnd,msg,mp1,mp2);
			}


		default:
			return WinDefDlgProc(hwnd, msg, mp1, mp2);
		}
}

void CenterWindow(HWND hwnd)
{
	RECTL rclRect1;
	RECTL rclRect2;
	int x,y;

	/* Position the dialog box in the center of the screen */
	WinQueryWindowRect(HWND_DESKTOP, &rclRect1);
	WinQueryWindowRect(hwnd, &rclRect2);
	x = ((rclRect1.xRight - rclRect1.xLeft) - (rclRect2.xRight - rclRect2.xLeft)) / 2;
	y = ((rclRect1.yTop - rclRect1.yBottom) - (rclRect2.yTop - rclRect2.yBottom)) / 2;
	WinSetWindowPos(hwnd, HWND_TOP, x, y, (rclRect2.xRight - rclRect2.xLeft),
	(rclRect2.yTop - rclRect2.yBottom), SWP_SIZE | SWP_MOVE | SWP_SHOW);
	return;
}
