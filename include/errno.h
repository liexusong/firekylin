/*
 *    include/errno.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _ERRNO_H
#define _ERRNO_H

#define ERROR		1
#define EPERM		2
#define ENOENT		3
#define EINTR		4
#define EIO		5
#define E2BIG		6
#define EISDIR		7
#define EINVAL		8
#define EACCESS		9
#define EBADF		10
#define ENOTDIR		11
#define ENOMEM		12
#define EAGAIN		13
#define ENOEXEC		14
#define ENODEV		15
#define EMFILE		16
#define EEXIST		17
#define ENOSPACE	18
#define ERSCH		19
#define EBUSY		20
#define ESPIPE		21
#define ENOTBLK		22

extern int errno;

#endif
