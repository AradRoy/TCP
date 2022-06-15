#include <tcpsupp.h>
#include <cvirte.h>		
#include <userint.h>
#include <ansi_c.h>
#include "Client.h"

static int panelHandle;
unsigned int serverHandle;

int m_x, m_y, l_pressed;
	static pre_x, pre_y;

	//int m_x, m_y, l_pressed;
	static pre_x2, pre_y2;

int connectFunc(unsigned Handle, int xType, int errCode, void *callbackData);

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Client.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	SetCtrlAttribute(panelHandle, PANEL_CANVAS, ATTR_PEN_WIDTH, 3);

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

int CVICALLBACK connectToServer (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ConnectToTCPServer (&serverHandle, 8889, "77.126.96.149", connectFunc, 0, 0);

			//ConnectToTCPServer (&serverHandle, 8889, "192.168.1.102", connectFunc, 0, 0);
			break;
	}
	return 0;
}
int connectFunc(unsigned Handle, int xType, int errCode, void *callbackData)
{
	char text[200];
	switch(xType)
	{
		case TCP_DISCONNECT:
			printf("The server disconnected you\n");
			break;
		case TCP_DATAREADY:
			ClientTCPRead (serverHandle,text , 199, 0);
			sscanf (text, "%d %d", &pre_x2, &pre_y2);
			CanvasDrawPoint (panelHandle, PANEL_CANVAS, MakePoint (pre_x2, pre_y2));
		
			break;
	}

	return 0;
}
int CVICALLBACK sendText (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}


int CVICALLBACK canvasFunc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char sendtext[200];
	switch (event)
	{
		
		case EVENT_LEFT_CLICK:
			
			GetRelativeMouseState (panelHandle, PANEL_CANVAS, &m_x, &m_y, &l_pressed, 0, 0); 
			
			CanvasDrawPoint (panelHandle, PANEL_CANVAS, MakePoint(m_x,m_y));
			
			pre_x=m_x;
			pre_y=m_y;
		
		case EVENT_MOUSE_POINTER_MOVE:
			
			GetRelativeMouseState (panelHandle, PANEL_CANVAS, &m_x, &m_y, &l_pressed, 0, 0); 
			
			if (l_pressed)
			{
				CanvasDrawLine (panelHandle, PANEL_CANVAS, MakePoint(pre_x, pre_y), MakePoint(m_x,m_y));
				pre_x=m_x;
				pre_y=m_y;
				sprintf (sendtext, "%d %d", pre_x,pre_y);
				ClientTCPWrite(serverHandle,sendtext , 199, 0);
			}
			
			break;
		
		
	}
	
	return 0;
}

int CVICALLBACK timerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			break;
	}
	return 0;
}
