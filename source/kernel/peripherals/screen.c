#include "screen.h"
#include "ports.h"
#include "../stdlib.h"

//privates declaration

#define  VIDEO_ADDRESS 0xb8000
#define  MAX_ROWS  25
#define  MAX_COLS  80
//  Screen  device I/O ports
#define  REG_SCREEN_CTRL 0x3D4
#define  REG_SCREEN_DATA 0x3D5


int get_cursor_offset();
void set_cursor_offset(int offset);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int print_char(char c, int col, int row, char attr);

//public

void print_c(char* message, char attr)
{
	print_at(message, -1, -1, attr);
}

void print(char* message)
{
	print_at(message, -1, -1, WHITE_ON_BLACK);
}

void print_at(char* message, int col, int row, char attr)
{
	int offset;
	if (col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else
	{
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	int i = 0;
	while (message[i] != 0)
	{
		offset = print_char(message[i++], col, row, attr);
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}

void clear_screen()
{
	int screen_size = MAX_COLS * MAX_ROWS;
	unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;

	for (int i = 0; i < screen_size; i++) {
		vidmem[i * 2] = ' ';
		vidmem[i * 2 + 1] = WHITE_ON_BLACK;
	}
	set_cursor_offset(get_offset(0, 0));
}

//private

int print_char(char c, int col, int row, char attr)
{
	unsigned char* vidmem = (unsigned char*)VIDEO_ADDRESS;
	if (!attr) attr = WHITE_ON_BLACK;

	int offset;
	if (col >= 0 && row >= 0) 
		offset = get_offset(col, row);
	else 
		offset = get_cursor_offset();

	if (c == '\n') 
	{
		row = get_offset_row(offset);
		offset = get_offset(0, row + 1);
	}
	else 
	{
		vidmem[offset] = c;
		vidmem[offset + 1] = attr;
		offset += 2;
	}
	if (offset >= MAX_ROWS * MAX_COLS * 2) 
	{
		for (int i = 1; i < MAX_ROWS; i++)
			memcpy(get_offset(0, i) + VIDEO_ADDRESS,
				get_offset(0, i - 1) + VIDEO_ADDRESS,
				MAX_COLS * 2);

		/* Blank last line */
		unsigned char* last_line = get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
		for (int i = 0; i < MAX_COLS * 2; i += 2)
		{
			last_line[i] = 0;
			last_line[i + 1] = attr;
		}
		offset = get_offset(0, 24);
	}
	set_cursor_offset(offset);
	return offset;
}


int get_cursor_offset() 
{
	/* Use the VGA ports to get the current cursor position
	 * 1. Ask for high byte of the cursor offset (data 14)
	 * 2. Ask for low byte (data 15)
	 */
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset)
{
	/* Similar to get_cursor_offset, but instead of reading we write data */
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row)
{
	return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset)
{
	return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset)
{
	return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}