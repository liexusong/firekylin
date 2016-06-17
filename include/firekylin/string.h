/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _STRING_H
#define _STRING_H

static inline void memcpy(void *dst, void*src, int size)
{
	__asm__("rep movsb":: "D"(dst),"S"(src),"c"(size));
}

static inline void memset(void *s, int c, int size)
{
	__asm__("rep stosb" ::"D"(s),"a"(c),"c"(size));
}

static inline int strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1==*s2){
		s1++;
		s2++;
	}

	return (int)(*s1-*s2);
}

static inline int strncmp(char *s1, char *s2, size_t n)
{
	while (n--) {
		if (*s1 && (*s1 == *s2)) {
			s1++;
			s2++;
		} else {
			return (*s1 - *s2);
		}
	}
	return 0;
}

static inline char * strncpy(char *dst, char *src, size_t n)
{
	char *t = dst;
	while (n-- && (*t++ = *src++))
		;
	return dst;
}

#endif
