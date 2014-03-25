#include "stdint.h"
#include "stdlib.h"
#include "jupiterV1_1.h"

#define MAX_QUEUE_SIZE 30

typedef struct
{
	ALARM_STRUCT data;
	void * next_node;
}NodeStr;

typedef struct
{
	uint8_t queue_size;
	void * front;
	void * rear;
}queueInfo;

void enqueue(ALARM_STRUCT * alarms);
void dequeue(void);
bool queueEmpty(void);
void init_queue(void);
