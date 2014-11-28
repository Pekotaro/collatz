#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MEMO_LENGTH (memo_size / 2)
#define MAX_MEMO_INDEX (MEMO_LENGTH - 1)

typedef struct {
    int n;
    unsigned short steps;
} result_t;

//��������B�������ߖ�̂��߁Auchar�Q��(2�o�C�g)�ŕ\������B
typedef struct {
    unsigned char high, low;
} memo_t;

//�����̈�̑傫�� 2�`1000,000�̎��͂��ꂭ�炢�ɂ��Ă����̂��ł������Ȃ�B�Ȃ����͂킩��Ȃ��B
unsigned long memo_size = 2 * 1024 * 1024;

static memo_t* glob_memo; //�����̈�̃|�C���^

/*****************************************************
 * �����̈���m�ۂ���B
 *****************************************************/
memo_t* allocMemo(){
    long size;
    memo_t* ptr_memo = NULL;
    
    //�����̈�m��
    while(1){
        ptr_memo = (memo_t*)calloc(memo_size / sizeof(memo_t), sizeof(memo_t));
        if(ptr_memo != NULL || memo_size < 0) break;
        memo_size = memo_size - (256 * 1024);
    }
    if(ptr_memo == NULL){
            printf("�������擾���s");
            exit(1);
    }
    return ptr_memo;
}

/*****************************************************
 * ��������l���擾����B
 *****************************************************/
unsigned short getMemo(const unsigned int n){
    if(n > MAX_MEMO_INDEX) return 0;
    return (int)((int)(glob_memo[n].high << 8) + (int)glob_memo[n].low);
}

/*****************************************************
 * �����ɒl��o�^����B
 *****************************************************/
void registerMemo(const unsigned int n, const unsigned short steps){
    if(n > MAX_MEMO_INDEX) return;
    glob_memo[n].high = (unsigned char)(steps >> 8);
    glob_memo[n].low = (unsigned char)(steps &  0xFF);
}


/*****************************************************
 * �R���b�c�̌v�Z���s���ċA�֐�
 *****************************************************/
int collatz(const unsigned long long n){
    unsigned long long next_n;
    unsigned short memo, steps_to_1;
    
    if(n == 1) return 0;
    
    memo = getMemo(n);
    if(memo > 0) return memo;
    
    next_n = (n % 2 == 0) ? n / 2 : (n * 3) + 1;
    
    steps_to_1 = collatz(next_n) + 1;
    registerMemo(n, steps_to_1);
    
    return steps_to_1;
}

/******************************************************
 * ���C���E���[�v
 ******************************************************/
result_t collatz_roop(int first_n, int last_n){
    int n;
    unsigned short steps;
    result_t result = {0, 0};
    
    glob_memo = allocMemo();
    
    //�v�Z���[�v
    for(n = first_n; n <= last_n; n++){
        steps = collatz((unsigned long long)n);
        if(steps > result.steps){
            result.n = n;
            result.steps = steps;
        }
    }
    free(glob_memo);
    return result;
}

/*****************************************************
 * ���s�J�n�A�I�������B
 *****************************************************/
void main(void) {
    result_t result;
    const int first_n = 2, last_n = 1000000;
    clock_t start_time, end_time;
    
    start_time = clock();
    printf("�R���b�c�̖����v�Z���܂��B�i%d�`%d�j\r\n", first_n, last_n);
    
    //���s
    result = collatz_roop(first_n, last_n);
    
    end_time = clock();
    printf("���ʁF�X�e�b�v���������Ȃ鏉���l��\"%d\"��%d�X�e�b�v������܂��B\r\n", result.n, result.steps);
    printf("time=%.3f[s]   memo size=%lu[byte]\r\n", (double)(end_time - start_time) / CLOCKS_PER_SEC, memo_size);
    
    return;
}
