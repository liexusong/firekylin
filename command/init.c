/*
 *    command/init.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/unistd.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	while (1) {
		if (!fork()) {
			open("/dev/tty1", O_RDWR, 0);
			execve("/bin/sh", NULL, NULL);
			_exit(0);
		}
		waitpid(0, NULL, 0);
	}
}
