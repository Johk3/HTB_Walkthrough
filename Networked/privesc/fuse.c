#define FUSE_USE_VERSION 28



#include <errno.h>

#include <fuse.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>



static FILE	*logFile;



static char	*fileNameNormal="/file";

static char	*fileNameCharDev="/chardev";

static char	*fileNameNormalSubFile="/dir/file";



static char	*realFileName="./RealFile";

static int	realFileHandle=-1;



static int io_getattr(const char *path, struct stat *stbuf) {

  fprintf(logFile, "io_getattr(path=\"%s\", stbuf=0x%p)\n",

      path, stbuf);

  fflush(logFile);



  int res=-ENOENT;

  memset(stbuf, 0, sizeof(struct stat));

  if(strcmp(path, "/") == 0) {

    stbuf->st_mode=S_IFDIR|0755;

    stbuf->st_nlink=2;

    res=0;

  } else if(strcmp(path, fileNameCharDev)==0) {

//    stbuf->st_dev=makedev(5, 2);

    stbuf->st_mode=S_IFCHR|0777;

    stbuf->st_rdev=makedev(5, 2);

    stbuf->st_nlink=1; // Number of hard links

    stbuf->st_size=100;

    res=0;

  } else if(strcmp(path, "/dir")==0) {

    stbuf->st_mode=S_IFDIR|S_ISGID|0777;

    stbuf->st_nlink=1; // Number of hard links

    stbuf->st_size=1<<12;

    res=0;

  } else if((!strcmp(path, fileNameNormal))||(!strcmp(path, fileNameNormalSubFile))) {

    stbuf->st_mode=S_ISUID|S_IFREG|0777;

    stbuf->st_size=100;



    if(realFileName) {

      if(fstat(realFileHandle, stbuf)) {

        fprintf(logFile, "Stat of %s failed, error %d (%s)\n",

            realFileName, errno, strerror(errno));

      } else {

// Just change uid/suid, which is far more interesting during testing

        stbuf->st_mode|=S_ISUID;

        stbuf->st_uid=0;

        stbuf->st_gid=0;

      }

    } else {

      stbuf->st_mode=S_ISUID|S_IFREG|0777;

      stbuf->st_size=100;

    }

    stbuf->st_nlink=1; // Number of hard links

    res=0;

  }



  return(res);

}





static int io_readlink(const char *path, char *buffer, size_t length) {

  fprintf(logFile, "io_readlink(path=\"%s\", buffer=0x%p, length=0x%lx)\n",

      path, buffer, (long)length);

  fflush(logFile);

  return(-1);

}





static int io_unlink(const char *path) {

  fprintf(logFile, "io_unlink(path=\"%s\")\n", path);

  fflush(logFile);

  return(0);

}





static int io_rename(const char *oldPath, const char *newPath) {

  fprintf(logFile, "io_rename(oldPath=\"%s\", newPath=\"%s\")\n",

      oldPath, newPath);

  fflush(logFile);

  return(0);

}





static int io_chmod(const char *path, mode_t mode) {

  fprintf(logFile, "io_chmod(path=\"%s\", mode=0x%x)\n", path, mode);

  fflush(logFile);

  return(0);

}





static int io_chown(const char *path, uid_t uid, gid_t gid) {

  fprintf(logFile, "io_chown(path=\"%s\", uid=%d, gid=%d)\n", path, uid, gid);

  fflush(logFile);

  return(0);

}





/** Open a file. This function checks access permissions and may

 *  associate a file info structure for future access.

 *  @returns 0 when open OK

 */

static int io_open(const char *path, struct fuse_file_info *fi) {

  fprintf(logFile, "io_open(path=\"%s\", fi=0x%p)\n", path, fi);

  fflush(logFile);



  return(0);

}





static int io_read(const char *path, char *buffer, size_t length,

    off_t offset, struct fuse_file_info *fi) {

  fprintf(logFile, "io_read(path=\"%s\", buffer=0x%p, length=0x%lx, offset=0x%lx, fi=0x%p)\n",

      path, buffer, (long)length, (long)offset, fi);

  fflush(logFile);



  if(length<0) return(-1);

  if((!strcmp(path, fileNameNormal))||(!strcmp(path, fileNameNormalSubFile))) {

    if(!realFileName) {

      if((offset<0)||(offset>4)) return(-1);

      if(offset+length>4) length=4-offset;

      if(length>0) memcpy(buffer, "xxxx", length);

      return(length);

    }

    if(lseek(realFileHandle, offset, SEEK_SET)==(off_t)-1) {

      fprintf(stderr, "read: seek on %s failed\n", path);

      return(-1);

    }

    return(read(realFileHandle, buffer, length));

  }

  return(-1);

}





static int io_readdir(const char *path, void *buf, fuse_fill_dir_t filler,

    off_t offset, struct fuse_file_info *fi) {

  fprintf(logFile, "io_readdir(path=\"%s\", buf=0x%p, filler=0x%p, offset=0x%lx, fi=0x%p)\n",

      path, buf, filler, ((long)offset), fi);

  fflush(logFile);



  (void) offset;

  (void) fi;

  if(!strcmp(path, "/")) {

    filler(buf, ".", NULL, 0);

    filler(buf, "..", NULL, 0);

    filler(buf, fileNameCharDev+1, NULL, 0);

    filler(buf, "dir", NULL, 0);

    filler(buf, fileNameNormal+1, NULL, 0);

    return(0);

  } else if(!strcmp(path, "/dir")) {

    filler(buf, ".", NULL, 0);

    filler(buf, "..", NULL, 0);

    filler(buf, "file", NULL, 0);

    return(0);

  }

  return -ENOENT;

}





static int io_access(const char *path, int mode) {

  fprintf(logFile, "io_access(path=\"%s\", mode=0x%x)\n",

      path, mode);

  fflush(logFile);

  return(0);

}





static int io_ioctl(const char *path, int cmd, void *arg,

    struct fuse_file_info *fi, unsigned int flags, void *data) {

  fprintf(logFile, "io_ioctl(path=\"%s\", cmd=0x%x, arg=0x%p, fi=0x%p, flags=0x%x, data=0x%p)\n",

      path, cmd, arg, fi, flags, data);

  fflush(logFile);

  return(0);

}





static struct fuse_operations hello_oper = {

  .getattr	= io_getattr,

  .readlink	= io_readlink,

// .getdir =  deprecated

// .mknod

// .mkdir

  .unlink	= io_unlink,

// .rmdir

// .symlink

  .rename	= io_rename,

// .link

  .chmod	= io_chmod,

  .chown	= io_chown,

// .truncate

// .utime

  .open = io_open,

  .read = io_read,

// .write

// .statfs

// .flush

// .release

// .fsync

// .setxattr

// .getxattr

// .listxattr

// .removexattr

// .opendir

  .readdir	= io_readdir,

// .releasedir

// .fsyncdir

// .init

// .destroy

  .access	= io_access,

// .create

// .ftruncate

// .fgetattr

// .lock

// .utimens

// .bmap

 .ioctl = io_ioctl,

// .poll

};



int main(int argc, char *argv[]) {

  char	buffer[128];



  realFileHandle=open(realFileName, O_RDWR);

  if(realFileHandle<0) {

    fprintf(stderr, "Failed to open %s\n", realFileName);

    exit(1);

  }



  snprintf(buffer, sizeof(buffer), "FuseMinimal-%d.log", getpid());

  logFile=fopen(buffer, "a");

  if(!logFile) {

    fprintf(stderr, "Failed to open log: %s\n", (char*)strerror(errno));

    return(1);

  }

  fprintf(logFile, "Starting fuse init\n");

  fflush(logFile);



  return fuse_main(argc, argv, &hello_oper, NULL);

}
