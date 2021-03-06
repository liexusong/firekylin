/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <signal.h>
#include <errno.h>

int sigefillset(sigset_t *set)
{
	*set = ~(sigset_t) 0;
	return 0;
}
