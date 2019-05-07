#include "string.h"

void itoa(int n, char str[])
{
	int neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	int i = 0;
	while (n > 0)
	{
		str[i++] = '0' + n % 10;
		n = n / 10;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
}

void htoa(int n, char str[])
{
    int neg = 0;
    if (n < 0)
    {
        neg = 1;
        n = -n;
    }
    int i = 0;
    while (n > 0)
    {
        int digit =n % 16;
        if (digit >= 10)
            str[i++] = 'A' + digit - 10;
        else
            str[i++] = '0' + digit;
        n = n / 16;
    }
    if (neg)
        str[i++] = '-';
    str[i] = '\0';
    reverse(str);
}

void reverse(char s[])
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

void append(char str[], char a)
{
     int len = strlen(str);
     str[len] = a;
     str[len + 1] = '\0';
}

int backspace(char str[])
{
    int len = strlen(str);
    if (len != 0)
    {
        str[len - 1] = '\0';
        return 0;
    }
    else
        return 1;
}

int strcmp(char a[], char b[])
{
    int i;
    for (i = 0; a[i] == b[i]; i++)
        if (a[i] == '\0')
            return 0;
    return a[i] - b[i];
}
