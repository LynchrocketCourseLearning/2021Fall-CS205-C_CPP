//matrix.c
#include "matrix.h"

clock_t start, end;

//在结束时删除矩阵
void mat_del(matp mat) {
    if (mat == NULL) {
        fprintf(stderr, "Error: No such matrix to be deleted.\n");
        exit(EXIT_FAILURE);
    } else if (mat->val != NULL) {
        free(mat->val);
    }
}

//二维数组矩阵删除
void mat_del_2(matp_2 mat) {
    if (mat == NULL) {
        fprintf(stderr, "Error: No such matrix to be deleted.\n");
        exit(EXIT_FAILURE);
    } else if (mat->val != NULL) {
        for (int i = 0; i < mat->row; ++i) {
            free(mat->val[i]);
        }
        free(mat->val);
    }
}

//用于矩阵拷贝
void mat_copy(matp des, const matp src) {
    START;
    des->row = src->row;
    des->col = src->col;
    des->val = (float *) malloc(src->row * src->col * sizeof(float));
    size_t i, j;
    for (i = 0; i < des->row; ++i) {
        for (j = 0; j < des->col; ++j) {
            *(des->val + i * des->row + j) = *(src->val + i * src->row + j);
        }
    }
    END("mat_copy");
}

//用于将一维矩阵拷贝至二维矩阵
void mat_copy_to2(matp_2 des, const matp src) {
    START;
    des->row = src->row;
    des->col = src->col;
    des->val = (float **) malloc(src->row * sizeof(float *));
    size_t k;
    for (k = 0; k < src->row; ++k) {
        *(des->val + k) = malloc(src->col * sizeof(float));
    }
    size_t i, j;
    for (i = 0; i < src->row; ++i) {
        for (j = 0; j < src->col; ++j) {
            des->val[i][j] = *(src->val + i * src->row + j);
        }
    }
    END("mat_copy_to2");
}

//检测矩阵行列是否对应
void mat_match_check(matp des, const matp l_mat, const matp r_mat) {
    if (l_mat->row != r_mat->col) {
        fprintf(stderr, "Error: Not matched source matrices.\n");
        exit(EXIT_FAILURE);
    }
    if (l_mat->row != des->row || r_mat->col != des->col) {
        des->row = l_mat->row;
        des->col = r_mat->col;
        des->val = (float *) malloc(des->row * des->col * sizeof(float));
    }
}

//检测二维数组矩阵
void mat_match_check_2(matp_2 des, const matp_2 l_mat, const matp_2 r_mat) {
    if (l_mat->row != r_mat->col) {
        fprintf(stderr, "Error: Not matched source matrices.\n");
        exit(EXIT_FAILURE);
    }
    if (l_mat->row != des->row || r_mat->col != des->col) {
        des->row = l_mat->row;
        des->col = r_mat->col;
        des->val = (float **) malloc(des->row * des->col * sizeof(float *));
        for (int i = 0; i < des->row; ++i) {
            *(des->val + i) = (float *) malloc(des->row * des->col * sizeof(float));
        }
    }
}

//比较确认一维转二维成功
void mat_compare(const matp m1, const matp_2 m2) {
    size_t i, j;
    for (i = 0; i < m1->row; ++i) {
        for (j = 0; j < m1->col; ++j) {
            if ((*(m1->val + i * m1->row + j) - m2->val[i][j]) > 0.00001) {
                fprintf(stderr, "Error: matrix to 2-dimention wrong.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
