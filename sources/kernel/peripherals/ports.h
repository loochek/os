#ifndef PORTS_H
#define PORTS_H

unsigned char inportb (unsigned short port);
void outportb (unsigned short port, unsigned char data);
unsigned short inportw (unsigned short port);
void outportw (unsigned short port, unsigned short data);

#endif
