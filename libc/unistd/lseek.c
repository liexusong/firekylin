/*
 *	libc/unistd/lseek.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <errno.h>

__syscall3(int, lseek, int, fd, long, off, int, where);
