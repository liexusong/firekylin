/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd1,fd2,size;
	char buf[1024];

	if(argc<3){
		printf("%s\n","usage:cp src dst");
		_exit(0);
	}

	fd1=open(argv[1],O_READ,0);
	if(fd1<0){
		printf("file open error:%s", argv[1]);
		_exit(0);
	}

	fd2=open(argv[2],O_WRITE,0);
	if(fd2<0){
		printf("file open error:%s", argv[2]);
		_exit(0);
	}

	while((size=read(fd1,buf,1024))){
		write(fd2,buf,size);
	}
}
