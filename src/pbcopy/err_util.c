#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>

#include "err_util.h"

BOOL get_lasterror_string(char *buf, int buf_size)
{
	if (buf == NULL) return FALSE;

	memset(buf, 0, sizeof(char));

	DWORD err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, 0, (void*)buf, buf_size, NULL);

	return TRUE;
}

void _print_get_lasterror_string(char *func_name, char *file_name, int line_num)
{
	char msg[512];
	char err_msg[256];
	get_lasterror_string(err_msg, 256);

	// format message
	_snprintf_s(msg, 512, _TRUNCATE, "error : %s,%s,%d : %s\n", func_name, file_name, line_num, msg);

	// output error message
	fprintf(stderr, msg);
	OutputDebugString(msg);
}
