#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct {
	char type; 
	int amount;
	char unit; 
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t s;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	sem_wait(&s);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	sem_post(&s);
}

item *consume() {
	item *i = (item *)malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
	sem_wait(&s);
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	sem_post(&s);
	return i;
}

void log_val() {
	printf("First = %d  Last = %d\n",first,last);
}

void *produce_thread(void *param){
	item item_1;
	item item_2;
	item item_3;

	item_1.type = '1';
	item_1.amount = 0;
	item_1.unit = '1';

	item_2.type = '0';
	item_2.amount = 1;
	item_2.unit = '0';

	item_3.type = '1';
	item_3.amount = 1;
	item_3.unit = '0';

	printf("\nProducing item no.1: type=%c amount=%d unit=%c\n",
	item_1.type, item_1.amount, item_1.unit);
	produce(&item_1);
	log_val();

	printf("\nProducing item no.2: type=%c amount=%d unit=%c\n",
	item_2.type, item_2.amount, item_2.unit);
	produce(&item_2);
	log_val();

	printf("\nProducing item no.3: type=%c amount=%d unit=%c\n",
	item_3.type, item_3.amount, item_3.unit);
	produce(&item_3);
	log_val();
}

void *consume_thread(void *param) {
	printf("\nAfter consumed once:\n");
	consume();
	log_val();

	printf("\nAfter consumed twice:\n");
	consume();
	log_val();
}

int sem_init(sem_t *sem, int pshared, unsigned int value);

int sem_wait(sem_t *sem);

int sem_post(sem_t *sem);

int sem_destroy(sem_t *sem);


int main() {
	sem_init(&s, 0, 8);

	pthread_t tid_1, tid_2;
	pthread_create(
		&tid_1,
		NULL,
		produce_thread,
		NULL);

	pthread_join(tid_1, NULL);

	pthread_create(
		&tid_2,
		NULL,
		consume_thread,
		NULL);

	pthread_join(tid_2, NULL);

	sem_destroy(&s);
}
