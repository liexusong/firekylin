/* This file is part of The Firekylin Operating System.
 *
 * Copyright (c) 2016, Liuxiaofeng
 * All rights reserved.
 *
 * This program is free software; you can distribute it and/or modify
 * it under the terms of The BSD License, see LICENSE.
 */

#include <ctype.h>

#undef iscntrl

int iscntrl(int c)
{
	return (__ctype[(c)+1]&(_C));
}
