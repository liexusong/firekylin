/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <stdarg.h>

static void itos(char **buf, unsigned int num, int base)
{
	char str[] = "0123456789ABCDEF";
	char tmp[20];
	int i = 0;
	if (base == 16) {
		**buf = '0';
		(*buf)++;
		**buf = 'x';
		(*buf)++;
	}
	do {
		tmp[i] = str[num % base];
		i++;
		num = num / base;
	} while (num);
	for (i--; i >= 0; i--) {
		**buf = tmp[i];
		(*buf)++;
	}
}

int vsprintf(char* buf, char* fmt, va_list ap)
{
	char *str = buf;
	char *s;

	while (*fmt) {
		if (*fmt != '%') {
			*str++ = *fmt++;
			continue;
		}
		fmt++;
		switch (*fmt++) {
		case '%':
			*str++ = '%';
			break;
		case 'c':
			*str++ = va_arg(ap, char);
			break;
		case 's':
			s = va_arg(ap, char*);
			while (*s) {
				*str++ = *s++;
			}
			break;
		case 'd':
			itos(&str, va_arg(ap, unsigned int), 10);
			break;
		case 'x':
			itos(&str, va_arg(ap, unsigned int), 16);
			break;
		default:
			break;
		}
	}
	return (int) (str - buf);
}
