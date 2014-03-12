#include "queue.h"

static NodeStr *queue_front = NULL;
static NodeStr *queue_rear = NULL;
queueInfo QInfo;

void init_queue(void)
{
	QInfo.queue_size = 0;
	QInfo.front = NULL;
	QInfo.rear = NULL;
}

void enqueue(ALARM_STRUCT * alarms)
{
	NodeStr * temp;
    uint8_t size;
    size = sizeof(NodeStr);
	if(QInfo.queue_size > MAX_QUEUE_SIZE)
		return;	
	temp = (NodeStr *)malloc(size);
	if(temp == NULL)
		return;// memory allocate failed
    memset(temp, 0, size);
	QInfo.queue_size++;
    size = sizeof(ALARM_STRUCT);
	memcpy(&temp->data, alarms, size);
	temp->next_node = NULL;
	QInfo.front = queue_front;// update poiter to front queue
	QInfo.rear = queue_rear;
	if((queue_front == NULL) && (queue_rear == NULL))
	{
		queue_front = queue_rear = temp;
		return;
	}
	queue_rear->next_node = temp;
	queue_rear = temp;
}

void dequeue(void)
{
	NodeStr * temp = queue_front;
	if(temp == NULL)
		return;
	if(queue_front == queue_rear)
		queue_front = queue_rear = NULL;
	else
		queue_front = queue_front->next_node;

	QInfo.front = queue_front;
	QInfo.rear = queue_rear;
    QInfo.queue_size--;
	free(temp);
}

bool queueEmpty(void)
{
	NodeStr * temp = queue_front;
	if(temp == NULL)
		return TRUE;
	else
		return FALSE;
}
