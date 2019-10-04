#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
char * def_ftype(struct stat * sb) {
  char * f = NULL;
  switch (sb->st_mode & S_IFMT) {
    case S_IFBLK:
      f = "block special file";
      break;
    case S_IFCHR:
      f = "character special file";
      break;
    case S_IFDIR:
      f = "directory";
      break;
    case S_IFIFO:
      f = "fifo";
      break;
    case S_IFLNK:
      f = "symbolic link";
      break;
    case S_IFREG:
      f = "regular file";
      break;
    case S_IFSOCK:
      f = "socket";
      break;
  }
  return f;
}

void def_pmssn(struct stat * s, char * p) {
  //figure out permission[0]
  switch (s->st_mode & S_IFMT) {
    case S_IFBLK:
      p[0] = 'b';
      break;
    case S_IFCHR:
      p[0] = 'c';
      break;
    case S_IFDIR:
      p[0] = 'd';
      break;
    case S_IFIFO:
      p[0] = 'p';
      break;
    case S_IFLNK:
      p[0] = 'l';
      break;
    case S_IFREG:
      p[0] = '-';
      break;
    case S_IFSOCK:
      p[0] = 's';
      break;
  }
  //figure out permissions[1]
  if (s->st_mode & S_IRUSR) {
    p[1] = 'r';
  }
  else {
    p[1] = '-';
  }
  //figure out permission[2]
  if (s->st_mode & S_IWUSR) {
    p[2] = 'w';
  }
  else {
    p[2] = '-';
  }
  //figure out permission[3]
  if (s->st_mode & S_IXUSR) {
    p[3] = 'x';
  }
  else {
    p[3] = '-';
  }
  //figure out permission[4]
  if (s->st_mode & S_IRGRP) {
    p[4] = 'r';
  }
  else {
    p[4] = '-';
  }
  //figure out permission[5]
  if (s->st_mode & S_IWGRP) {
    p[5] = 'w';
  }
  else {
    p[5] = '-';
  }
  //figure out permission[6]
  if (s->st_mode & S_IXGRP) {
    p[6] = 'x';
  }
  else {
    p[6] = '-';
  }
  //figure out permission[7]
  if (s->st_mode & S_IROTH) {
    p[7] = 'r';
  }
  else {
    p[7] = '-';
  }
  //figure out permission[8]
  if (s->st_mode & S_IWOTH) {
    p[8] = 'w';
  }
  else {
    p[8] = '-';
  }
  //figure out permission[9]
  if (s->st_mode & S_IXOTH) {
    p[9] = 'x';
  }
  else {
    p[9] = '-';
  }
  p[10] = '\0';
}
int main(int argc, char * argv[]) {
  struct stat sb;
  char h_pmsn[11] = {0};
  char * filetype = NULL;
  if (argc < 2) {
    fprintf(stderr, "Wrong argument number!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {  //step5
    if (lstat(argv[i], &sb) == -1) {
      fprintf(stderr, "Wrong lstat\n");
      exit(EXIT_FAILURE);
    }
    //step1
    if (S_ISLNK(sb.st_mode)) {  //step7
      char lnktrgt[256];
      ssize_t len = readlink(argv[i], lnktrgt, 256);
      lnktrgt[len] = '\0';
      printf("  File: %s -> %s\n", argv[i], lnktrgt);
    }
    else {
      printf("  File: %s\n", argv[i]);
    }
    filetype = def_ftype(&sb);  //define filetype
    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
           (unsigned long)sb.st_size,
           (unsigned long)sb.st_blocks,
           (unsigned long)sb.st_blksize,
           filetype);
    if ((S_ISCHR(sb.st_mode)) || S_ISBLK(sb.st_mode)) {  //step6
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
             (unsigned long)sb.st_dev,
             (unsigned long)sb.st_dev,
             (unsigned long)sb.st_ino,
             (unsigned long)sb.st_nlink,
             major(sb.st_rdev),
             minor(sb.st_rdev));
    }
    else {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
             (unsigned long)sb.st_dev,
             (unsigned long)sb.st_dev,
             (unsigned long)sb.st_ino,
             (unsigned long)sb.st_nlink);
    }
    //step2+3

    def_pmssn(&sb, h_pmsn);
    printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           sb.st_mode & ~S_IFMT,
           h_pmsn,
           sb.st_uid,
           getpwuid(sb.st_uid)->pw_name,
           sb.st_gid,
           getgrgid(sb.st_gid)->gr_name);
    //step4
    char * atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
    char * mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
    char * ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
    printf("Access: %s\n", atimestr);
    printf("Modify: %s\n", mtimestr);
    printf("Change: %s\n", ctimestr);
    printf(" Birth: -\n");
    free(atimestr);
    free(mtimestr);
    free(ctimestr);
  }
  //step5

  return EXIT_SUCCESS;
}
