#include <stdio.h>
#include <time.h>

typedef struct {
    int n;
    int steps;
} result_t;

result_t collutz_roop(int first_n, int last_n){
    int n, steps;
    result_t result = {0, 0};
    
    for(n = first_n; n <= last_n; n++){
        steps = collutz((unsigned long)n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }
    
    return result;
}

int collutz(unsigned long n){
    int steps;
    for(steps = 0; n != 1; steps++){
        n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    }
    return steps;
}

void main(void) {
    result_t result;
    const int first_n = 2, last_n = 1000000;
    clock_t start_time, end_time;
    
    printf("�R���b�c�̖����v�Z���܂��B�i%d�`%d�j\r\n", first_n, last_n);
    start_time = clock();
    result = collutz_roop(first_n, last_n);
    end_time = clock();
    printf("���ʁF�X�e�b�v���������Ȃ鏉���l��\"%d\"��%d�X�e�b�v������܂��B\r\n", result.n, result.steps);
    printf("%d[ms]�ł����B\r\n", end_time - start_time);
}
