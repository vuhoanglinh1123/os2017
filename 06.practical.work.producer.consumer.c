//Vu Hoang Linh
//BI6-086

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

typedef struct {
	char type; 
	int amount;
	char unit; 
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = (item *)malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void log_val() {
	printf("First = %d  Last = %d\n",first,last);
}

int main() {
	item item_1;
	item item_2;

	item_1.type = '1';
	item_1.amount = 0;
	item_1.unit = '1';

	item_2.type = '0';
	item_2.amount = 1;
	item_2.unit = '0';

	printf("\nProducing item no.1: type=%c amount=%d unit=%c\n",
	item_1.type, item_1.amount, item_1.unit);
	produce(&item_1);
	log_val();

	printf("\nProducing item no.2: type=%c amount=%d unit=%c\n",
	item_2.type, item_2.amount, item_2.unit);
	produce(&item_2);
	log_val();

	printf("\nAfter consumed once:\n");
	consume();
	log_val();
}
