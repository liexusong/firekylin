/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H

#define	NR_SIG		32

#define SIGHUP		1
#define SIGINT		2
#define SIGQUIT		3
#define SIGILL		4
#define SIGTRAP		5
#define SIGABRT		6
#define SIGFPU		7
#define SIGKILL		8
#define SIGUSR1		9
#define SIGSEGV		10
#define SIGUSR2		11
#define SIGPIPE		12
#define SIGALARM	13
#define SIGTREM		14
#define SIGCHLD		15
#define SIGTKFLT	16
#define SIGCONT		17
#define SIGSTOP		18
#define SIGTSTP		19
#define SIGTTIN		20
#define	SIGTTOU		21

#define SIGCTL_SETMASK		1
#define SIGCTL_GETMASK		2
#define SIGCTL_SETSUSPEND	3
#define SIGCTL_GETSUSPEND	4
#define SIGCTL_SETHANDLE	5
#define SIGCTL_SEND		6
#define SIGCTL_PAUSE		7

typedef unsigned long 	  sigset_t;
typedef void        	(*sigfunc_t)(int signo, int ret);

#define SIG_ERR		((sigfunc_t)-1)
#define SIG_DFL		((sigfunc_t)0)
#define SIG_IGN		((sigfunc_t)1)

#endif
