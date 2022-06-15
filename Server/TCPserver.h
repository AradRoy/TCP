/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: exitFunc */
#define  PANEL_TOGGLEBUTTON               2       /* control type: textButton, callback function: openCloseServerFunc */
#define  PANEL_TEXTBOX                    3       /* control type: textBox, callback function: (none) */
#define  PANEL_COMMANDBUTTON              4       /* control type: command, callback function: connectToServer */
#define  PANEL_STRING                     5       /* control type: string, callback function: sendTextToserver */
#define  PANEL_TEXTMSG                    6       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK connectToServer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exitFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK openCloseServerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK sendTextToserver(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
