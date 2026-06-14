#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>
#define BUFFER_SIZE 5 
#define PRODUCE_COUNT 20
int buffer[BUFFER_SIZE]; 
int in = 0; 
int out = 0;
pthread_mutex_t mutex; 
sem_t empty; 
sem_t full;
void* producer(void* arg) {
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i; 
        printf("生產者生產：%d\n", i); 
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(2); }
        return NULL; }
        int main() { 
            pthread_t p, c;
            pthread_mutex_init(&mutex, NULL);
            sem_init(&empty, 0, BUFFER_SIZE); 
            sem_init(&full, 0, 0);
            pthread_create(&p, NULL, producer, NULL); 
            pthread_create(&c, NULL, consumer, NULL);
            pthread_join(p, NULL); 
            pthread_join(c, NULL);
            pthread_mutex_destroy(&mutex); 
            sem_destroy(&empty); 
            sem_destroy(&full);
            return 0; 
        }