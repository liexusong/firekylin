/*
 *    fs/minix/super.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

struct fs_operation minix_fs_operation={
	minix1_read_super,
	minix1_write_super,
	minix1_read_inode,
	minix1_write_inode,
	minix1_look_up,
	minix1_file_read,
	minix1_file_readdir,
	minix1_file_write,
	minix1_mknod,
	minix1_mkdir,
	minix1_link,
	minix1_unlink,
	minix1_rmdir,
	minix1_rename
};
