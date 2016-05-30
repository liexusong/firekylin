/*
 *    fs/minix/inode.c
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include "minix_fs.h"

static void m1_read_inode(struct inode *inode, struct minix1_inode *m1)
{
	inode->i_mode = m1->i_mode;
	inode->i_nlink = m1->i_nlinks;
	inode->i_uid = m1->i_uid;
	inode->i_gid = m1->i_gid;
	inode->i_size = m1->i_size;
	inode->i_atime = inode->i_mtime = inode->i_ctime = m1->i_time;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		inode->i_rdev = m1->i_zone[0];
	else {
		inode->i_minix_ext.i_zone[0] = m1->i_zone[0];
		inode->i_minix_ext.i_zone[1] = m1->i_zone[1];
		inode->i_minix_ext.i_zone[2] = m1->i_zone[2];
		inode->i_minix_ext.i_zone[3] = m1->i_zone[3];
		inode->i_minix_ext.i_zone[4] = m1->i_zone[4];
		inode->i_minix_ext.i_zone[5] = m1->i_zone[5];
		inode->i_minix_ext.i_zone[6] = m1->i_zone[6];
		inode->i_minix_ext.i_zone[7] = m1->i_zone[7];
		inode->i_minix_ext.i_zone[8] = m1->i_zone[8];
	}
	inode->i_flag |= I_VALID;
}

static void m1_write_inode(struct inode *inode, struct minix1_inode *m1)
{
	m1->i_mode = inode->i_mode;
	m1->i_uid = inode->i_uid;
	m1->i_gid = inode->i_gid;
	m1->i_nlinks = inode->i_nlink;
	m1->i_size = inode->i_size;
	m1->i_time = inode->i_ctime;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		m1->i_zone[0] = inode->i_rdev;
	else {
		m1->i_zone[0] = inode->i_minix_ext.i_zone[0];
		m1->i_zone[1] = inode->i_minix_ext.i_zone[1];
		m1->i_zone[2] = inode->i_minix_ext.i_zone[2];
		m1->i_zone[3] = inode->i_minix_ext.i_zone[3];
		m1->i_zone[4] = inode->i_minix_ext.i_zone[4];
		m1->i_zone[5] = inode->i_minix_ext.i_zone[5];
		m1->i_zone[6] = inode->i_minix_ext.i_zone[6];
		m1->i_zone[7] = inode->i_minix_ext.i_zone[7];
		m1->i_zone[8] = inode->i_minix_ext.i_zone[8];
	}
	inode->i_flag &= ~I_DIRTY;
}

static int __minix1_rw_inode(struct inode *inode, int rw)
{
	struct super *super;
	struct buffer *buf;
	struct minix1_inode *m1;
	long block;

	super = get_super(inode->i_dev);

	block = 2 + super->s_minix_ext.s_imap_blocks
		  + super->s_minix_ext.s_zmap_blocks
		  + (inode->i_ino - 1) / INODES_PER_BLOCK;
	put_super(super);

	buf = bread(inode->i_dev, block);
	m1 = (struct minix1_inode *) buf->b_data
			+ (inode->i_ino - 1) % INODES_PER_BLOCK;
	if (rw) {
		m1_read_inode(inode, m1);
	} else {
		m1_write_inode(inode, m1);
		buf->b_flag|=B_DIRTY;
	}
	brelse(buf);
	return 0;
}

int minix1_read_inode(struct inode * inode)
{
	return __minix1_rw_inode(inode, 1);
}

int minix1_write_inode(struct inode * inode)
{
	return __minix1_rw_inode(inode, 0);
}

static int __minix1_bmap(struct inode *inode, int block, int create)
{
	struct buffer *buffer;
	int res;

	if (block < 7) {
		if (create && (!inode->i_minix_ext.i_zone[block])) {
			inode->i_minix_ext.i_zone[block] = minix1_alloc_block(inode->i_dev);
			inode->i_ctime = current_time();
			inode->i_flag |= I_DIRTY;
		}
		return inode->i_minix_ext.i_zone[block];
	}

	block -= 7;
	if (block < 512) {
		if (create && !inode->i_minix_ext.i_zone[7]) {
			inode->i_minix_ext.i_zone[7] = minix1_alloc_block(
					inode->i_dev);
			inode->i_ctime = current_time();
			inode->i_flag |= I_DIRTY;
		}
		if (!inode->i_minix_ext.i_zone[7])
			return 0;
		buffer = bread(inode->i_dev, inode->i_minix_ext.i_zone[7]);
		res = *((short*) (buffer->b_data + block * 2));
		if (create && !res) {
			res = minix1_alloc_block(inode->i_dev);
			*((short*) (buffer->b_data + block * 2)) = res;
			buffer->b_flag |= B_DIRTY;
		}
		brelse(buffer);
		return res;
	}
	return 0;
}

int minix1_rbmap(struct inode *inode, int block)
{
	return __minix1_bmap(inode, block, 0);
}

int minix1_wbmap(struct inode *inode, int block)
{
	return __minix1_bmap(inode, block, 1);
}
