/*
 *	libc/unistd/fstat.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <errno.h>

__syscall2(int, fstat, int, fd, struct stat*, statbuf);
