
#include "editor.h"
#include "gesture.fdh"

#define GRECT_SIZE		32

Gesture::Gesture()
{
	fString = NULL;
	fOpen = false;
}

Gesture::~Gesture()
{
	delete fString;
	fString = NULL;
}

/*
void c------------------------------() {}
*/

void Gesture::Open(int x, int y)
{
	if (fString)
		fString->SetTo("");
	else
		fString = new BString;
	
	UpdateRect(x, y);
	fOpen = true;
}

void Gesture::Drag(int x, int y)
{
char nextchar;

	if (!fOpen)
		return;
	
	if (x <= fRect.left)
	{
		nextchar = 'L';
	}
	else if (x >= fRect.right)
	{
		nextchar = 'R';
	}
	else if (y <= fRect.top)
	{
		nextchar = 'U';
	}
	else if (y >= fRect.bottom)
	{
		nextchar = 'D';
	}
	else
	{
		return;
	}
	
	UpdateRect(x, y);
	if (fString->LastChar() != nextchar)
	{
		fString->Append(nextchar);
		MainWindow->main.editarea->cmd_preview->SetText(*fString);
	}
}

void Gesture::Close(void)
{
	if (fOpen && fString->Length() > 0)
	{
		MainWindow->main.editarea->cmd_preview->SetText("");
		ProcessString(fString->String());
		
		delete fString;
		fString = NULL;
	}
	
	fOpen = false;
}

void Gesture::ProcessString(const char *str)
{
	stat("Processing gesture: '%s'", str);
	
	if (!strcmp(str, "RL"))			// new tab
	{
		TabBar->SetActiveTab(CreateEditView(NULL));
	}
	else if (!strcmp(str, "LR"))	// close tab
	{
		editor.curev->UserClose();
	}
	else if (!strcmp(str, "L"))		// prev tab
	{
		TabBar->SwitchToPrevTab();
	}
	else if (!strcmp(str, "R"))		// next tab
	{
		TabBar->SwitchToNextTab();
	}
	else if (!strcmp(str, "U"))		// Open
	{
		MainWindow->PostMessage(M_FILE_OPEN);
	}
	else if (!strcmp(str, "UD"))	// Open Project
	{
		MainWindow->PostMessage(M_PROJECT_OPEN);
	}
	else if (!strcmp(str, "DU"))	// Save All
	{
		MainWindow->PostMessage(M_FILE_SAVE_ALL);
	}
	else if (!strcmp(str, "DR"))	// Find
	{
		MainWindow->PostMessage(M_SEARCH_FIND);
	}
	else if (!strcmp(str, "DL"))	// Replace
	{
		MainWindow->PostMessage(M_SEARCH_REPLACE);
	}
	else if (!strcmp(str, "D"))		// Find in Files
	{
		MainWindow->PostMessage(M_SEARCH_FIND_FILES);
	}
	else
	{
		stat("unknown gesture '%s'", str);
	}
}

/*
void c------------------------------() {}
*/

void Gesture::UpdateRect(int x, int y)
{
	fRect.left = x - (GRECT_SIZE / 2);
	fRect.top = y - (GRECT_SIZE / 2);
	fRect.right = x + (GRECT_SIZE / 2);
	fRect.bottom = y + (GRECT_SIZE / 2);
}



