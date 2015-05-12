#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

#include "err_util.h"

unsigned char *buf = NULL;
int buf_size = 0;
int buf_capacity = 0;

BOOL append_buf()
{
	unsigned char *tmp_buf;
	int next_size;
	int unit = 1024;

	if (buf == NULL) {
		next_size = unit;
		buf = (unsigned char*)malloc(unit);
		if (buf == NULL) {
			fprintf(stderr, "error : malloc() size=%d\n", unit);
			return FALSE;
		}
		buf_capacity = next_size;
		memset(buf, 0, buf_capacity);
	}
	else {
		next_size = buf_capacity * unit;
		tmp_buf = (unsigned char*)realloc(buf, next_size);
		if (tmp_buf == NULL) {
			fprintf(stderr, "error : realloc() size=%d\n", next_size);
			free(buf);
			buf = NULL;
			return FALSE;
		}
		buf = tmp_buf;
		buf_capacity = next_size;

		memset((buf + buf_capacity - unit), 0, unit);
	}

	return TRUE;
}

BOOL check_buf_size()
{
	if (buf_size >= buf_capacity - 1) {
		if (append_buf() == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

void free_buf()
{
	if (buf != NULL) {
		free(buf);
		buf = NULL;
	}
}

BOOL copy_text_to_clipboard(char *buf, int buf_size)
{
	BOOL rv;
	HGLOBAL h;
	void *g_mem;

	// allocate memory for clipboard
	h = GlobalAlloc(GHND | GMEM_SHARE, buf_size + 1);
	if (h == NULL) {
		print_get_lasterror_string("GlobalAlloc()");
		free_buf();
		return FALSE;
	}
	g_mem = GlobalLock(h);
	memset(g_mem, 0, buf_size + 1);
	memcpy(g_mem, buf, buf_size);
	GlobalUnlock(h);

	// clipboard operation
	rv = OpenClipboard(NULL);
	if (rv == FALSE) {
		print_get_lasterror_string("OpenClipboard()");
		free_buf();
		return FALSE;
	}

	EmptyClipboard();
	SetClipboardData(CF_TEXT, h);
	CloseClipboard();

	return TRUE;
}

int main(int argc, char *argv[])
{
	int c;

	_setmode(_fileno(stdin), _O_BINARY);

	while(TRUE) {
		if (check_buf_size() == FALSE) {
			return -1;
		}

		c = fgetc(stdin);
		if (c < 0) {
			break;
		}

		buf[buf_size] = (unsigned char)c;
		buf[buf_size + 1] = 0;
		buf_size += 1;
	}

	copy_text_to_clipboard(buf, buf_size);

	free_buf();

	return 0;
}
