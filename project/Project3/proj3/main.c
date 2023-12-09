//main.c
#include "IO.h"
#include "matrix.h"
#include "mul.h"

clock_t start, end;

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Error: The number of arguments is unexpected.\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp_mat1 = fopen(*(argv + 1), "r");
    valid_file(fp_mat1, *(argv + 1));
    FILE *fp_mat2 = fopen(*(argv + 2), "r");
    valid_file(fp_mat2, *(argv + 2));

    size_t mat1_row = get_rows(fp_mat1), mat1_col = get_cols(fp_mat1);
    size_t mat2_row = get_rows(fp_mat2), mat2_col = get_cols(fp_mat2);

    mat mat1, mat2, mat_out;
    mat_init(fp_mat1, mat1_row, mat1_col, &mat1);
    mat_init(fp_mat2, mat2_row, mat2_col, &mat2);
    mat_match_check(&mat_out, &mat1, &mat2);

    mat_2 mat1_2, mat2_2, mat_out_2;
    mat_copy_to2(&mat_out_2, &mat_out);
    mat_copy_to2(&mat1_2, &mat1);
    mat_copy_to2(&mat2_2, &mat2);
    mat_match_check_2(&mat_out_2, &mat1_2, &mat2_2);

//    //测试拷贝一维数组和二维数组的区别
//    mat test1;
//    mat_2 test2;
//    mat_copy(&test1, &mat1);
//    mat_copy_to2(&test2, &mat1);
//    mat_del(&test1);
//    mat_del_2(&test2);

    //比较拷贝是否成功
    mat_compare(&mat1, &mat1_2);
    mat_compare(&mat2, &mat2_2);

   //ijk
   mat_mul_simple(&mat_out, &mat1, &mat2);
   mat_mul_simple_2(&mat_out_2, &mat1_2, &mat2_2);
   mat_compare(&mat_out, &mat_out_2);

   //ikj
   mat_mul_divide(&mat_out, &mat1, &mat2);
   mat_mul_divide_2(&mat_out_2, &mat1_2, &mat2_2);
   mat_compare(&mat_out, &mat_out_2);

    //Strasen
   START;
   strassen(mat_out_2.row, mat1_2.val, mat2_2.val, mat_out_2.val);
   END("strassen");

    //SIMD
    // mat_dot(&mat_out_2, &mat1_2, &mat2_2);

    //OpenBLAS
    blas(&mat_out, &mat1, &mat2);

   FILE *fp_mat_out = fopen(*(argv + 3), "r");

   if (fp_mat_out == NULL) {
       fp_mat_out = fopen(*(argv + 3), "w+");
       mat_out_file(fp_mat_out, &mat_out);
   } else {
       fprintf(stderr, "Error: The file has existed. Please try again after checked.\n");
       exit(EXIT_FAILURE);
   }


    mat_del(&mat1);
    mat_del(&mat2);
    mat_del(&mat_out);
    mat_del_2(&mat1_2);
    mat_del_2(&mat2_2);
    mat_del_2(&mat_out_2);

    close_file(fp_mat1);
    close_file(fp_mat2);
   close_file(fp_mat_out);
    return 0;
}