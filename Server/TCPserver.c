#include <ansi_c.h>
#include <tcpsupp.h>
#include <cvirte.h>		
#include <userint.h>
#include "TCPserver.h"

static int panelHandle;
static unsigned int serverHandle;   // קליינט כל הנדל מייצג שיחה פעילה
static unsigned int clientHandle;

int ServerFunc(unsigned handle, int xType, int errCode, void *callbackData);
int connectFunc (unsigned handle, int xType, int errCode, void *callbackData);

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "TCPserver.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK exitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}


int ServerFunc (unsigned handle, int xType, int errCode, void *callbackData) // ממשק עם קליינטים
{
	char received_text[200];
	int bytes_received;
	switch(xType)
	{
		case TCP_CONNECT:
			printf("A client just connected\n");
			break;
		case TCP_DISCONNECT:
			printf("A client just disconnected\n");
			break;
		case TCP_DATAREADY:
			bytes_received = ServerTCPRead (handle, received_text, 199, 0);
			received_text[bytes_received]='\0';
			InsertTextBoxLine (panelHandle, PANEL_TEXTBOX, -1, received_text);
			
			clientHandle= handle; // saving the clinet that connected info
			break;
	}
	return 0;
}

int CVICALLBACK openCloseServerFunc (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)	// פונקציית יצירת שרת
{
	switch (event)
	{
		case EVENT_COMMIT:
			 RegisterTCPServer (8889, ServerFunc, 0);    
			break;
	}
	return 0;
}



int CVICALLBACK connectToServer (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)	  // פונקציית חיבור לשרת
{
	switch (event)
	{
		case EVENT_COMMIT:
		ConnectToTCPServer (&serverHandle, 8889, "83.130.152.250", connectFunc, 0, 0);

			break;
	}
	return 0;
}

int connectFunc (unsigned handle, int xType, int errCode, void *callbackData)  // פונקציית ממשק עם שרת
{

	char text[200];
	switch(xType)
	{

		case TCP_DISCONNECT:
			printf("The server disconnected you\n");
			break;
		case TCP_DATAREADY:
			ClientTCPRead (serverHandle,text , 199, 0);
			SetCtrlVal (panelHandle, PANEL_TEXTMSG, text);
			break;
	}

	return 0;
	
}

int CVICALLBACK sendTextToserver (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char send_text[200];
			GetCtrlVal (panelHandle, PANEL_STRING, send_text);
 			ClientTCPWrite (serverHandle, send_text, strlen(send_text)+1, 0); //שולח הודעה לשרת
			break;
	}
	return 0;
}
