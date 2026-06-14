#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#define N 5 
#define EAT_TIMES 3
pthread_mutex_t chopsticks[N]; 
sem_t room;
void* philosopher(void* arg) { 
    int id = *(int*)arg;
    int left = id; 
    int right = (id + 1) % N;
    for (int i = 0; i < EAT_TIMES; i++) {
        printf("哲學家 %d 正在思考\n", id);
        sleep(1);
        sem_wait(&room);
        pthread_mutex_lock(&chopsticks[left]);
        printf("哲學家 %d 拿起左邊筷子 %d\n", id, left);
        pthread_mutex_lock(&chopsticks[right]);
        printf("哲學家 %d 拿起右邊筷子 %d\n", id, right);
        printf("哲學家 %d 正在吃飯\n", id); 
        sleep(1);
        pthread_mutex_unlock(&chopsticks[right]); 
        pthread_mutex_unlock(&chopsticks[left]);
        printf("哲學家 %d 放下筷子\n", id);
        sem_post(&room); }
        return NULL; }
        int main() { 
            pthread_t philosophers[N]; 
            int ids[N];
            sem_init(&room, 0, N - 1);
            for (int i = 0; i < N; i++) {
                pthread_mutex_init(&chopsticks[i], NULL); 
            }
            for (int i = 0; i < N; i++) {
                ids[i] = i;
                pthread_create(&philosophers[i], NULL, philosopher, &ids[i]); }
                for (int i = 0; i < N; i++) {
                    pthread_join(philosophers[i], NULL); }
                    for (int i = 0; i < N; i++) { 
                        pthread_mutex_destroy(&chopsticks[i]); }
                        sem_destroy(&room); 
                        return 0; }