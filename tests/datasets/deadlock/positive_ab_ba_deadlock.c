#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

void *thread1_func(void *arg) {
  // 线程1: 先锁A，再锁B (AB顺序)
  if (pthread_mutex_lock(&lockA) != 0)
    return NULL;
  printf("Thread1: lockA acquired\n");
  sleep(1);

  if (pthread_mutex_lock(&lockB) != 0) {
    pthread_mutex_unlock(&lockA);
    return NULL;
  }
  printf("Thread1: lockB acquired\n");

  pthread_mutex_unlock(&lockB);
  pthread_mutex_unlock(&lockA);
  return NULL;
}

void *thread2_func(void *arg) {
  // 线程2: 先锁B，再锁A (BA顺序) - 与线程1相反，形成死锁
  if (pthread_mutex_lock(&lockB) != 0)
    return NULL;
  printf("Thread2: lockB acquired\n");
  sleep(1);

  if (pthread_mutex_lock(&lockA) != 0) {
    pthread_mutex_unlock(&lockB);
    return NULL;
  }
  printf("Thread2: lockA acquired\n");

  pthread_mutex_unlock(&lockA);
  pthread_mutex_unlock(&lockB);
  return NULL;
}

int main() {
  pthread_t t1, t2;
  if (pthread_create(&t1, NULL, thread1_func, NULL) != 0)
    return 1;
  if (pthread_create(&t2, NULL, thread2_func, NULL) != 0)
    return 1;

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
