#include "terminal_control.h"
#include "game_utils.h"

COORD getCursorPosition()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(stdOut, &consoleInfo);

	return consoleInfo.dwCursorPosition;
}