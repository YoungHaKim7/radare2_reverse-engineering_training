#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source_file> <dest_file>\n", argv[0]);
        exit(1);
    }
    int srcfd, dstfd; // src 파일 서술자, dst 파일 서술자
    void *src, *dst;  // src 메모리 주소, dst 메모리 주소
    size_t copysz;    // 다음 copy할  메모리 내용 size
    struct stat sbuf;
    off_t fsz = 0;  // 다음 읽기, 쓰기를 기록할 위치(offset)
    long page_size; // 시스템의 PAGE SIZE

    if ((srcfd = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "can't open %s for reading \n", argv[1]);
        exit(1);
    }

    if ((dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0) {
        fprintf(stderr, "can't open %s for writing\n", argv[2]);
        exit(1);
    }

    // file 사이즈 얻기 위한 용도
    if (fstat(srcfd, &sbuf) < 0) {
        fprintf(stderr, "fstat error\n");
        exit(1);
    }

    if (ftruncate(dstfd, sbuf.st_size) < 0) {
        fprintf(stderr, "ftruncate error\n");
        exit(1);
    }

    page_size = sysconf(_SC_PAGESIZE);
    printf("page_size : %ld\n", page_size);

    while (fsz < sbuf.st_size) {

        if ((sbuf.st_size - fsz) > page_size)
            copysz = page_size;
        else
            copysz = sbuf.st_size - fsz;

        // src 주소 설정
        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, srcfd, fsz)) ==
            MAP_FAILED) {
            fprintf(stderr, "mmap error for input \n");
            printf("error : %s\n", strerror(errno));
            exit(1);
        }

        // dst 주소 설정 , 여기서 MAP_SHARED를 MAP_RPIVATE로 바꾸면? dst파일에
        // 저장되지 않는다.
        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, dstfd,
                        fsz)) == MAP_FAILED) {
            fprintf(stderr, "mmap error for output\n");
            exit(1);
        }

        // src -> dst로 내용 복사
        memcpy(dst, src, copysz);

        // 메모리 해제
        munmap(src, copysz);
        munmap(dst, copysz);
        // 복사한 내용만큼 다음 메모리 위치를 이동시킬 offset 증가
        fsz += copysz;
    }

    exit(0);
}
