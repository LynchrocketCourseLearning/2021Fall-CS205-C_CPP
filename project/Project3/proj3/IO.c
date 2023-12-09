//IO.c
#include "IO.h"
#include "matrix.h"

clock_t start, end;

//判断文件指针是否指向成功
void valid_file(FILE *fp, const char *filename) {
    if (fp == NULL) {
        fprintf(stderr, "Error: (%s) No such file.\n", filename);
        exit(EXIT_FAILURE);
    }
}

//关闭文件
void close_file(FILE *fp) {
    if (fp != NULL) {
        free(fp);
    } else {
        fprintf(stderr, "Error: The file pointer has been deleted.\n");
        exit(EXIT_FAILURE);
    }
}

//获取矩阵行数
size_t get_rows(FILE *fp) {
    rewind(fp);
    size_t row_cnt = 0;
    char tmp[1010];
    while (fgets(tmp, 1000, fp)) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            row_cnt++;
        }
    }
    return row_cnt;
}

//获取矩阵列数
size_t get_cols(FILE *fp) {
    rewind(fp);
    size_t col_cnt = 0;
    char tmp;
    while ((tmp = fgetc(fp)) != '\n') {
        if (tmp == ' ') {
            col_cnt++;
        }
    }
    col_cnt++;
    return col_cnt;
}

//用于从文件中读取矩阵数据，初始化矩阵
void mat_init(FILE *fp, size_t row, size_t col, matp mat) {
    rewind(fp);

    START;
    mat->row = row;
    mat->col = col;
    mat->val = (float *) malloc(row * col * sizeof(float));
    size_t i, j;
    float tmp = 0;
    int che = 0;
    int control = 0;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            if ((che = fscanf(fp, "%f", &tmp)) != EOF) {
                if (che != 1) {
                    fprintf(stderr, "Error: For input not float.\n");
                    exit(EXIT_FAILURE);
                }
                *(mat->val + j + i * row) = tmp;
            } else {
                control = 1;
                break;
            }
        }
        if (control == 1) break;
    }
    END("mat_init");
}

//输出矩阵到文件中
void mat_out_file(FILE *fp, matp mat) {
    rewind(fp);

    START;
    size_t i, j;
    float tmp;
    for (i = 0; i < mat->row; ++i) {
        for (j = 0; j < mat->col; ++j) {
            tmp = *(mat->val + j + i * mat->row);
            fprintf(fp, "%.2f ", tmp);
        }
        fprintf(fp, "\n");
    }
    END("mat_out_file");
}

//内存映射，仅限于linux
//读
//void map_read(const char *filename, matp m) {
//    int fd = open(filename, O_RDONLY);
//    size_t len = lseek(fd, 0, SSEK_END);
//    float *buff = (float *) mmap(NULL, len, PORT_READ, MAP_PRIVATE, fd, 0);
//    close(fd);
//
//    memcpy(m->val, buff, len);
//    munmap(buff, len);
//}
//
//写
//void map_write(const char *filename, matp m) {
//    size_t len = m->row * m->col;
//    int fd = open(filename, O_RDWR | O_CREAT, 00777);
//
//    lseek(fd, len - 1, SEEK_END);
//    write(fd, " ", 1);
//    char *buff = (char *) mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    close(fd);
//
//    memcpy(buff, m->val, len);
//    munmap(buff, len);
//}