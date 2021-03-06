/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if(argc!=4){
		printf("Usage:mount special target type");
		_exit(0);
	}
	if(mount(argv[1],argv[2],argv[3],0)<0){
		printf("%d:%s",errno,strerror(errno));
	}
	return 0;
}
