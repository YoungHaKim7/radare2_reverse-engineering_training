#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT, 0664);
    size_t size = 1024;
    ftruncate(fd, size); // 파일 크기 설정 [1]

    // 1. mmap으로 파일 매핑
    char *map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
        return -1;

    // 2. 포인터로 파일에 쓰기
    sprintf(map, "Hello, mmap!");

    // 3. 매핑 해제 및 파일 닫기
    munmap(map, size);
    close(fd);
    return 0;
}
