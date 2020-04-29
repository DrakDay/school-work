#include "q.h"



int main() {
	struct qelement* item1 = NewItem();
	item1->payload = 1;
	struct qelement* item2 = NewItem();
	item2->payload = 2;
	struct qelement* item3 = NewItem();
	item3->payload = 3;
	struct qelement* item4 = NewItem();
	item4->payload = 4;
	struct qelement* item5 = NewItem();
	item5->payload = 5;
	struct qelement* item6 = NewItem();
	item6->payload = 6;

	struct Queue * q1 = (struct Queue*) malloc(sizeof(struct Queue));
	struct Queue * q2 = (struct Queue*) malloc(sizeof(struct Queue));;

	initQueue(q1);
	initQueue(q2);

	addQueue(q1, item1);
	addQueue(q1, item2);
	addQueue(q1, item3);

	addQueue(q2, item4);
	addQueue(q2, item5);
	addQueue(q2, item6);

	struct qelement* q1x = q1->head;
	struct qelement* q2x = q2->head;

	//while (q1x != NULL) {
	//	printf("%d", q1x->payload);
	//	q1x= q1x->prev;
	//}

	while (q1->head != NULL) {
		struct qelement * temp = delQueue(q1);
		printf("%d", temp->payload);
	}

	printf("\n");

	while (q1x != NULL) {
		printf("%d", q1x->payload);
		q1x= q1x->prev;
}
	printf("\n");



	rotQueue(q2);

//	while (q2x != NULL) {
//		printf("%d", q2x->payload);
//		q2x = q2x->prev;
	//}

	while (q2->head != NULL) {
		struct qelement * temp = delQueue(q2);
		printf("%d", temp->payload);
	}

	printf("\n");
	return 1;
}