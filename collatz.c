#include <stdio.h>

typedef struct {
    int n;
    int steps;
} result_t;

void main(void) {
    result_t result = {0,0};
    int n, steps, max_steps = 0;
    
    printf("�R���b�c�̖����v�Z���܂��B�i2�`100000�j\r\n");

    for(n = 2; n <= 100000; n++){
        steps = collutz(n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }    

    printf("���ʁF�X�e�b�v���������Ȃ鏉���l��\"%d\"��%d�X�e�b�v������܂��B\r\n", result.n, result.steps);
}

int collutz(int n){
    int steps;
    for(steps = 0; n != 1; steps++){
        n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    }
    return steps;
}
