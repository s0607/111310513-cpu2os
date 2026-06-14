#include <stdio.h>
#include <pthread.h>

#define TIMES 100000

int balance = 0;
pthread_mutex_t mutex;

void* deposit(void* arg) {
    for (int i = 0; i < TIMES; i++) {
        pthread_mutex_lock(&mutex);
        balance++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (int i = 0; i < TIMES; i++) {
        pthread_mutex_lock(&mutex);
        balance--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("最後帳戶餘額：%d\n", balance);

    if (balance == 0) {
        printf("結果正確，沒有發生資料錯誤。\n");
    } else {
        printf("結果錯誤，發生 race condition。\n");
    }

    return 0;
}
