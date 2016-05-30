/*
 *    fs/minix/super.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

int minix1_read_super(struct super *super)
{
	struct minix1_super *m1_super;
	struct buffer *buf;

	buf = bread(super->s_dev, 1);
	m1_super = (struct minix1_super *) (buf->b_data);
	if (m1_super->s_magic != 0x138f)
		panic("Not availbale minix file system %x", m1_super->s_magic);
	super->s_minix_ext.s_ninodes = m1_super->s_ninodes;
	super->s_minix_ext.s_nzones = m1_super->s_nzones;
	super->s_minix_ext.s_imap_blocks = m1_super->s_imap_blocks;
	super->s_minix_ext.s_zmap_blocks = m1_super->s_zmap_blocks;
	super->s_minix_ext.s_firstdatazone = m1_super->s_firstdatazone;
	super->s_minix_ext.s_log_zone_size = m1_super->s_log_zone_size;
	super->s_minix_ext.s_max_size = m1_super->s_max_size;
	super->s_minix_ext.s_magic = m1_super->s_magic;

	brelse(buf);
	return 0;
}

int minix1_write_super(struct super *super)
{
	return 0;
}
