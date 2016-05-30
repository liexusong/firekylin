/*
 *    include/firekylin/fs.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _FS_H
#define _FS_H

#include <sys/types.h>
#include <firekylin/lock.h>

#define BUF_SIZE	1024
struct buffer {
	dev_t 		b_dev;
	unsigned int    b_block;
	unsigned short  b_flag;
	unsigned short  b_count;
	sleeplock_t	b_lock;
	char            b_data[BUF_SIZE];
	struct buffer * b_hash_prev;
	struct buffer * b_hash_next;
	struct buffer * b_free_prev;
	struct buffer * b_free_next;
};

/* Bits of buffer->b_flag */
#define B_BUSY		0x0001
#define B_VALID 	0x0002
#define B_DIRTY 	0x0004

#define lock_buffer(buf)	require_lock(&((buf)->b_lock))
#define unlock_buffer(buf)	release_lock(&((buf)->b_lock))

struct pipe_inode_ext{
	unsigned long buf;
	unsigned int  head;
	unsigned int  tail;
	unsigned int  size;
	struct task  *wait;
};

#include <firekylin/minixfs_ext.h>

struct inode {
	dev_t 		     i_dev;
	ino_t 		     i_ino;
	mode_t 		     i_mode;
	nlink_t 	     i_nlink;
	uid_t 		     i_uid;
	gid_t 		     i_gid;
	dev_t		     i_rdev;
	off_t 		     i_size;
	time_t 		     i_atime;
	time_t 		     i_mtime;
	time_t 		     i_ctime;
	unsigned short 	     i_flag;
	unsigned short 	     i_count;
	sleeplock_t	     i_lock;
	struct fs_operation *i_op;
	union{
		struct minix_inode_ext	i_minix_ext;
		struct pipe_inode_ext   i_pipe_ext;
	};
};

/* Bits of inode->i_flag */
#define I_BUSY		0x0001
#define I_VALID		0x0002
#define I_DIRTY		0x0004
#define I_MOUNT		0x0008

struct super {
	dev_t                s_dev;
	unsigned short       s_flag;
	unsigned short       s_count;
	sleeplock_t	     s_lock;
	struct fs_operation *s_op;
	struct inode        *s_imount;
	union{
		struct minix_super_ext	s_minix_ext;
	};
};

/* Bits of super->s_flag */
#define S_BUSY		0x0001
#define S_VALID		0x0002
#define S_DIRTY		0x0004
#define S_WRITEABLE	0x0008

#define lock_super(super)	require_lock(&((super)->s_lock))
#define unlock_super(super)	release_lock(&((super)->s_lock))

struct fs_operation{
	int (*super_read)(struct super *super);
	int (*super_write)(struct super *super);
	int (*inode_read)(struct inode *inode);
	int (*inode_write)(struct inode *inode);
	int (*look_up)(struct inode *inode, char *filename, struct inode **res);
	int (*file_read)(struct inode *inode, char *buf, size_t size,
			off_t offset, int rw_flag);
	int (*file_write)(struct inode *inode, char *buf, size_t size,
			off_t offset, int rw_flag);
	int (*mknod)(struct inode *inode, char *name,mode_t mode,dev_t dev);
	int (*mkdir)(struct inode *dir_inode,char *basename,mode_t mode);
	int (*link)(struct inode *dir_inode,char *name,struct inode *inode);
	int (*unlink)(struct inode *dir_inode,char *basename);
	int (*rmdir)(struct inode *dir_inode,char *basename);
	int (*rename)(struct inode *inode,char *old,char *new);
};

struct file {
	unsigned long  f_mode;
	unsigned long  f_count;
	unsigned long  f_pos;
	struct inode * f_inode;
};

#define NAME_LEN	30
struct dir_entry {
	unsigned short ino;
	char name[NAME_LEN];
};

static inline struct inode * ilock(struct inode *inode)
{
	require_lock(&inode->i_lock);
	return inode;
}

static inline struct inode * iunlock(struct inode *inode)
{
	release_lock(&inode->i_lock);
	return inode;
}

static inline struct inode * idup(struct inode *inode)
{
	require_lock(&inode->i_lock);
	inode->i_count++;
	return inode;
}

extern struct fs_operation minix_fs_operation;

extern struct buffer * bread(dev_t dev, long block);
extern void            brelse(struct buffer * buf);
extern struct super  * get_super(dev_t dev);
extern void            put_super(struct super *super);
extern struct inode  * iget(dev_t dev, ino_t ino);
extern void            iput(struct inode *inode);
extern struct inode  * namei(char *path, char **basename);

#define NR_FILE 	64
extern struct file file_table[NR_FILE];
extern sleeplock_t file_table_lock;

#endif
