#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

void writeNormalFile(char *name, int n);
void writeExtFile(char *name, int n);

int main() {
  writeNormalFile("file1.txt", 1);
  writeExtFile("sample_ext_file.txt", 80);
  exit();
}

void writeNormalFile(char *fileName, int n) {
  int fd = open(fileName, O_CREATE|O_RDWR);
  
  if (fd <= 0) {
    printf(1, "File open failed\n");
    return;
  }

  char x[1024];
  int i;
  for (i = 0; i < 1024; i++) {
    x[i] = 'n';
  }
  
  for (i = 0; i < n; i++) {
    int rc;
    if ((rc = write(fd, x, 1024)) != 1024){
      printf(2, "Normal File, Write failed. Return code %d\n", rc);
      return;
    }
  }
  close(fd);
}

void writeExtFile(char *fileName, int n) {
  int fd = open(fileName, O_CREATE|O_EXTENT|O_RDWR);
  
  if (fd <= 0) {
    printf(1, " Ext File open failed\n");
    return;
  }

  char x[1024];
  int i;
  for (i = 0; i < 1024; i++) {
    x[i] = 'e';
  }
  
  for (i = 0; i < n; i++) {
    int rc;
    if ((rc = write(fd, x, 1024)) != 1024) {
      printf(2, "Extent File, Write failed. Return code %d\n", rc);
      return;
    }
    if (i == 10) {
      writeNormalFile("file2.txt", 5);
    }
    if (i == 50) {
      writeNormalFile("file3.txt", 10);
    }
  }

  struct stat extFileInfo;
  int rc = fstat(fd, &extFileInfo);
  if (rc != 0) {
    printf(2,"fstat error, retruned %d",rc);
    return;
  }

  i = 0;
  while (extFileInfo.extents[i].length) {
    printf(1,"Extent start block:%d, Extent Len:%d\n", extFileInfo.extents[i].start_block_address, extFileInfo.extents[i].length);
    i++;
    if (i >= 12) {
      break;
    }
  }
  close(fd);
}