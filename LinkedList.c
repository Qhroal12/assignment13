#define _CRT_SECURE_NO_WARNINGS
#include "LinkedList.h"

LinkedList* createLinkedList() {
	struct linkedList* r;
	r = (struct linkedList*)malloc(sizeof(struct linkedList));

	r->head = (struct pointType*)NULL;
	r->size = 0;

	return r;
}

int destroyLinkedList(LinkedList* li) {
	struct pointType* nptr, * mptr;
	for (nptr = li->head; nptr != NULL; nptr = mptr) {
		mptr = nptr->next;
		free(nptr);
	}

	free(li);

	return 1;
}

int isEmptyLinkedList(LinkedList* li) {
	return (li->size == 0);
}

int sizeLinkedList(LinkedList* li) {
	return li->size;
}

LinkedList* insertFirstLinkedList(LinkedList* li, PointType item) {
	PointType* ptr = (PointType*)malloc(sizeof(PointType));
	*ptr = item;

	ptr->next = li->head;
	li->head = ptr;
	li->size++;

	return li;
}

int printLinkedList(LinkedList* li) {
	PointType* current = li->head;
	printf("LinkedList:\n");

	for (int i = 0; i < li->size; i++) {
		printf("[%d] x:%d, y:%d, next:%x\n",
			i, current->x, current->y, current->next);

		current = current->next;
	}
	printf("\n");
}

LinkedList* insertLastLinkedList(LinkedList* li, PointType item) {
	PointType* ptr = li->head;

	while (ptr->next != NULL) {
		ptr = ptr->next;
	}

	PointType* nPtr = (PointType*)malloc(sizeof(PointType));
	*nPtr = item;
	nPtr->next = NULL;

	ptr->next = nPtr;

	li->size++;

	return li;
}

LinkedList* insertAtLinkedList(LinkedList* li, int at, int x, int y) {
	if (at >= 0 && at < li->size) {

		PointType* item = (PointType*)malloc(sizeof(PointType));
		item->x = x;
		item->y = y;

		PointType* nPtr = li->head;

		for (int i = 0; i < at - 1; i++) {
			nPtr = nPtr->next;
		}

		if (at == 0) {
			li->head = item;
		}
		else {
			item->next = nPtr->next;
			nPtr->next = item;
		}

		li->size++;
	}
}

PointType deleteAtLinkedList(LinkedList* li, int at) {
	if (at >= 0 && at < li->size) {
		PointType* nPtr = li->head;
		PointType* fPtr = (PointType*)NULL;

		for (int i = 0; i < at - 1; i++) {
			nPtr = nPtr->next;
		}

		if (at == 0) {
			fPtr = li->head;
			li->head = fPtr->next;
			printf("삭제된 노드 = x: %d, y: %d, next:%x\n", fPtr->x, fPtr->y, fPtr->next);
		}
		else {
			fPtr = nPtr->next;
			nPtr->next = fPtr->next;
			printf("삭제된 노드 = x: %d, y: %d, next:%x\n", fPtr->x, fPtr->y, fPtr->next);
		}

		PointType delete = *fPtr;

		free(fPtr);
		li->size--;
		
		return delete;
	}
}

LinkedList* insertItemLinkedList(LinkedList* li, PointType* pre,
	PointType item) {

	PointType* nPtr = (PointType*)malloc(sizeof(PointType));
	*nPtr = item;

	if (pre != NULL) {
		nPtr->next = pre->next;
		pre->next = nPtr;
	}
	else {
		nPtr->next = li->head;
		li->head = nPtr;
	}

	li->size++;
}

PointType deleteFirstLinkedList(LinkedList* li) {
	if (li->size != 0) {
		PointType* tPtr = li->head;
		li->head = tPtr->next;

		PointType temp = *tPtr;
		free(tPtr);

		li->size--;
		return temp;
	}
	else {
		return (PointType) { 0, 0, 0 };
	}
}

PointType deleteLastLinkedList(LinkedList* li) {
	PointType* pre;
	PointType* iPtr;

	pre = li->head;

	if (pre == NULL) {
		return (PointType) { 0, 0, 0 };
	}

	iPtr = pre->next;

	if (iPtr == NULL) {
		li->head = NULL;

		PointType temp;
		temp = *pre;

		free(pre);
		li->size--;

		return temp;
	}
	else {
		while (iPtr->next != NULL) {
			pre = iPtr;
			iPtr = iPtr->next;
		}

		PointType temp;
		temp = *iPtr;

		pre->next = NULL;
		free(iPtr);
		li->size--;

		return temp;
	}
}

LinkedList* InsertFirstLinkedList(LinkedList* li, int x, int y) {
	PointType* ptr = (PointType*)malloc(sizeof(PointType));
	ptr->x = x;
	ptr->y = y;

	ptr->next = li->head;
	li->head = ptr;
	li->size++;

	return li;
}

LinkedList* InsertLastLinkedList(LinkedList* li, int x, int y) {

	PointType* ptr = li->head;

	if (li->size == 0) {
		InsertFirstLinkedList(li, x, y);
		return li;
	}

	while (ptr->next != NULL) {
		ptr = ptr->next;
	}

	PointType* nPtr = (PointType*)malloc(sizeof(PointType));
	nPtr->x = x;
	nPtr->y = y;

	nPtr->next = NULL;
	ptr->next = nPtr;

	li->size++;

	return li;
}

void StartLinkedList() {

	struct LinkedList* List = createLinkedList();
	int finish = -1;
	int menu;

	while (finish != 0) {

		int index, x, y = 0;

		printf("\n");
		printf("1. 맨 앞에 추가: 정수를 입력받아 리스트의 가장 앞에 삽입\n");
		printf("2. 맨 뒤에 추가: 정수를 입력받아 리스트의 가장 뒤에 삽입\n");
		printf("3. 특정 위치에 추가: 위치(index)와 정수를 입력받아 해당 위치에 삽입\n");
		printf("4. 특정 위치 삭제: 위치(index)를 입력받아 해당 노드를 삭제하고 값 출력\n");
		printf("5. 전체 목록 출력: 현재 리스트에 저장된 모든 정수를 순서대로 출력\n");
		printf("6. 리스트 크기 확인: 현재 저장된 노드의 총 개수를 출력\n");
		printf("0. 종료: 모든 메모리를 해제(destroy)하고 프로그램을 종료\n\n");

		printf("메뉴를 선택하세요 : ");

		scanf("%d",&menu);

		switch (menu) {

		case 1:
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			InsertFirstLinkedList(List, x, y);
			break;
		case 2:
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			InsertLastLinkedList(List, x, y);
			break;
		case 3:
			printf("추가할 위치(index)를 입력하세요 : ");
			scanf("%d", &index);
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			insertAtLinkedList(List, index, x, y);
			break;
		case 4:
			printf("삭제할 위치(index)를 입력하세요 : ");
			scanf("%d", &index);
			deleteAtLinkedList(List, index);
			break;
		case 5:
			printLinkedList(List);
			break;
		case 6:
			printf("현재 저장된 노드의 수 : %d", sizeLinkedList(List));
			break;
		case 0:
			printf("프로그램을 종료합니다.");
			destroyLinkedList(List);
			finish = 0;
			break;
		}
	}
}