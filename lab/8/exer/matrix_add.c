#include <stdio.h>
#include <time.h>
#include <immintrin.h>

typedef struct matrix
{
    size_t row;
    size_t col;
    float* val;
}mat, *matp;

void init_mat(matp m, size_t row, size_t col){
    m->row = row;
    m->col = col;
    m->val = (float*)malloc(row*col*sizeof(float));
}

void create_mat(matp m){
    for (size_t i = 0; i < m->row; i++)
    {
        for (size_t j = 0; j < m->col; j++)
        {
            srand((unsigned)time(NULL));
            *(m->val+i*m->row+j) = (float)rand();
        }
    }
    printf("created!\n");
    printf("%f\n",*(m->val+1+6));
}

void free_mat(matp m){
    free(m->val);
}

void add_mat1(matp A, matp B, matp res){
    for (size_t i = 0; i < A->row; i++)
    {
        for (size_t j = 0; j < A->col; j++)
        {
            *(res->val + i*A->row + j) = *(A->val + i*A->row + j) + *(B->val + i*B->row + j);
        }   
    }
    printf("add_mat1 was used\n");
    printf("%f\n", *(res->val+1+6));
}

void add_mat2(matp A, matp B, matp res){
    for (size_t i = 0; i < A->row; i++)
    {
        for (size_t j = 0; j < A->col; j++)
        {
            *(res->val + i + j*res->col) = *(A->val + i + j*A->col) + *(B->val + i + j*B->col);
        }   
    }
    printf("add_mat2 was used\n");
}

void simd_add(matp A, matp B, matp res){
    size_t len = res->col/4;
    float s[4] = {0};
    for (size_t i=0;i<res->row;i++){
        for(size_t j=0;j<len;j++){
            __m128 m1 = _mm_set_ps(A->val[i*A->row+j*4],A->val[i*A->row+j*4+1],A->val[i*A->row+j*4+2],A->val[i*A->row+j*4+3]);
            __m128 m2 = _mm_set_ps(B->val[i*B->row+j*4],B->val[i*B->row+j*4+1],B->val[i*B->row+j*4+2],B->val[i*B->row+j*4+3]);
            __m128 re = _mm_add_ps(m1,m2);
            _mm_store_ps(s, re);
            res->val[i*res->row+j*4] = s[0] + s[1] + s[2] + s[3];
        }
    }
    printf("simd_add was used\n");
}

int main(){
    mat A;
    mat B;
    mat res;
    init_mat(&A, 4096, 4096);
    init_mat(&B, 4096, 4096);
    init_mat(&res, 4096, 4096);
    create_mat(&A);
    create_mat(&B);

    clock_t time1 = clock();
    // time_t t1 = time(NULL);
    add_mat1(&A, &B, &res);
    clock_t time2 = clock();
    // time_t t2 = time(NULL);
    // double diff = difftime(t2, t1);
    printf("add_mat1 costs %ld (ns)\n", time2-time1);

    // t1 = time(NULL);
    time1 = clock();
    add_mat2(&A, &B, &res);
    time2 = clock();
    // t2 = time(NULL);
    // diff = difftime(t2, t1);
    printf("add_mat2 costs %ld (ns)\n", time2-time1);

    // t1 = time(NULL);
    time1 = clock();
    simd_add(&A, &B, &res);
    time2 = clock();
    // t2 = time(NULL);
    // diff = difftime(t2, t1);
    printf("simd_add costs %ld (ns)\n", time2-time1);

    free_mat(&A);
    free_mat(&B);
    free_mat(&res);
    return 0;
}





