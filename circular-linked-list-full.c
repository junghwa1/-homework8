/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {			//Node
	int key;					//key값
	struct Node* llink;			//left link
	struct Node* rlink;			//right link
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);			//리스트 생성
int freeList(listNode* h);				//리스트에 할당된 메모리 해제
int insertLast(listNode* h, int key);	//리스트의 마지막에 노드 삽입
int deleteLast(listNode* h);			//리스트의 마지막 노드 삭제
int insertFirst(listNode* h, int key);	//리스트의 처음에 노드 삽입
int deleteFirst(listNode* h);			//리스트의 첫번째 노드 삭제
int invertList(listNode* h);			//리스트의 링크를 역순으로 재배치

int insertNode(listNode* h, int key);	//입력받은 key값보다 크거나 같은 노드앞에 새로운 노드 삽입
int deleteNode(listNode* h, int key);	//입력받은 key을 가진 노드 삭제

void printList(listNode* h);			//리스트 정보 출력

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;		//head노드 생성
	printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");		//메뉴 출력
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);			//메뉴 선택

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);		//리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode);		//리스트 정보 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	//입력받은 key값보다 크거나 같은 노드앞에 새로운 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	//입력받은 key을 가진 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	//리스트의 마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	//리스트의 처음에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//리스트의 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);		//리스트의 링크를 역순으로 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode);			//리스트에 할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//메뉴 이외의 다른 값 입력 시 에러문구 출력
			break;
		}

	}while(command != 'q' && command != 'Q');		//q나 Q를 입력받으면 반복문 종료

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; 				//head노드의 rlink은 head노드를 가리킴
	(*h)->llink = *h;				//head노드의 rlink은 head노드를 가리킴
	(*h)->key = -9999;				//head노드의 key값을 -9999로 초기화
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)				//head노드의 rlink가 head노드를 가리킨다면
	{
		free(h);					//메모리 해제
		return 1;					//함수 종료
	}

	listNode* p = h->rlink;			//p에 head노드의 다음 노드를 저장

	listNode* prev = NULL;			//prev는 메모리 해제할 노드를 가리킴
	while(p != NULL && p != h) {	//p가 NULL이 아니고 head노드가 아니라면 반복
		prev = p;					//prev에 p 저장
		p = p->rlink;				//p는 p가 가리키던 다음 노드가 됨
		free(prev);					//prev에 할당된 메모리 해제
	}
	free(h);			//head노드에 할당된 메모리 해제
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//head노드가 NULL아라면
		printf("Nothing to print....\n");	//에러문구 출력
		return;			//함수 종료
	}

	p = h->rlink;		//p는 head노드의 다음 노드

	while(p != NULL && p != h) {				//p가 NULL이 아니고 head노드가 아니라면 반복
		printf("[ [%d]=%d ] ", i, p->key);		//리스트의 인덱스와 key값 출력
		p = p->rlink;							//p에 다음 노드를 저장
		i++;
	}
	printf("  items = %d\n", i);				//리스트의 원소의 개수


	/* print addresses */
	printf("\n---checking addresses of links\n");				//head 노드의 rlink와 llink가 가리키는 노드의 주소 출력
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {				//각 노드의 rlink와 llink가 가리키는 노드의 주소 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;		//head노드가 NULL이라면 함수 종료

	listNode* node = (listNode*)malloc(sizeof(listNode));	//동적 메모리 할당
	node->key = key;		//입력받은 key값 저장
	node->rlink = NULL;		//생성된 노드가 가리키는 노드는 아직 없음
	node->llink = NULL;		//생성된 노드가 가리키는 노드는 아직 없음

	if (h->rlink == h) /* 첫 노드로 삽입 */	//head노드 밖에 없는 경우
	{
		h->rlink = node;		//head노드의 rlink는 생성된 노드를 가리킴
		h->llink = node;		//head노드의 llink는 생성된 노드를 가리킴
		node->rlink = h;		//생성된 노드의 rlink는 head노드를 가리킴
		node->llink = h;		//생성된 노드의 llink는 head노드를 가리킴
	} else {
		h->llink->rlink = node;	//head노드의 이전 노드의 rlink가 생성된 노드를 가리킴
		node->llink = h->llink;	//생선된 노드의 llink는 head노드의 llink가 가리키는 노드를 가리킴
		h->llink = node;		//head노드의 llink는 생성된 노드를 가리킴
		node->rlink = h;		//생성된 노드의 rlink는 head노드를 가리킴
	}

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)			//첫번째 노드가 없거나 리스트가 생성이 안되어 있을때
	{
		printf("nothing to delete.\n");		//에러문구 출력
		return 1;	//함수 종료
	}

	listNode* nodetoremove = h->llink;		//head노드 이전의 노드는 nodetoremove(마지막 노드)

	/* link 정리 */
	nodetoremove->llink->rlink = h;			//nodetoremove노드의 이전노드의 rlink는 head노드를 가리킴
	h->llink = nodetoremove->llink;			//head노드의 llink는 nodetoremove노드의 이전노드를 가리킴

	free(nodetoremove);			//마지막 노드에 할당된 메모리 해제

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//삽입할 노드 동적 메모리 할당
	node->key = key;		//삽입할 노드의 key값은 입력받은 key값을 가짐
	node->rlink = NULL;		//생성된 노드가 가리키는 노드는 아직 없음
	node->llink = NULL;		//생성된 노드가 가리키는 노드는 아직 없음


	node->rlink = h->rlink;		//생선된 노드의 rlink는 기존의 첫번째 노드를 가리킴
	h->rlink->llink = node;		//기존의 첫번째 노드의 llink는 생성된 노드를 가리킴
	node->llink = h;			//생성된 노드의 llink는 head노드를 가리킴
	h->rlink = node;			//head노드의 rlink는 생성된 노드를 가리킴


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)			//첫번째 노드가 없거나 리스트가 생성이 안되어 있을때
	{
		printf("nothing to delete.\n");		//에러문구 출력
		return 0;		//함수 종료
	}

	listNode* nodetoremove = h->rlink;		//head노드 다음의 노드는 nodetoremove(첫번째 노드)

	/* link 정리 */
	nodetoremove->rlink->llink = h;			//nodetoremove노드의 다음노드의 llink는 head노드를 가리킴
	h->rlink = nodetoremove->rlink;			//head노드의 rlink는 nodetoremove노드의 다음노드를 가리킴

	free(nodetoremove);						//첫번째 노드에 할당된 메모리 해제

	return 1;

}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {			//첫번째 노드가 없거나 리스트가 생성이 안되어 있을때
		printf("nothing to invert...\n");		//에러문구 출력
		return 0;		//함수 종료
	}
	listNode *n = h->rlink;			//n은 첫번째 노드
	listNode *trail = h;			
	listNode *middle = h;

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){		//n이 NULL이 아니고 n이 head노드가 아니면 반복
		trail = middle;			//trail은 middle이 됨
		middle = n;				//middel은 n이 됨
		n = n->rlink;			//n은 n의 다음 노드가 됨
		middle->rlink = trail;	//middle의 다음노드는 trail이 됨
		middle->llink = n;		//middle의 이전노드는 n이 됨
	}

	h->rlink = middle;			//첫번째 노드는 반복문이 종료 후의 middle(마지막 노드)이 됨

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;	//리스트가 생성되지 않았다면 함수 종료

	listNode* node = (listNode*)malloc(sizeof(listNode));	//삽입할 노드 동적 메모리 할당
	node->key = key;		//삽입할 노드의 key값은 입력받은 key값을 가짐
	node->llink = node->rlink = NULL;		//생성된 노드가 가리키는 노드는 아직 없음

	if (h->rlink == h)			//첫번쨰 노드가 없으면
	{
		insertFirst(h, key);	//리스트의 처음에 노드 삽입
		return 1;	//함수 종료
	}

	listNode* n = h->rlink;		//n은 첫번째 노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {		//n이 NULL이 아니고 n이 head노드가 아니면 반복
		if(n->key >= key) {				//n의 key값이 입력한 key값보다 크거나 같을 때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {			//n이 첫번째 노드이면
				insertFirst(h, key);	//리스트의 처음에 노드 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;		//삽입할 노드의 rlink는 n을 가리킴
				node->llink = n->llink;	//삽입할 노드의 llink는 n의 이전 노드를 가리킴
				n->llink->rlink = node;	//n의 이전노드의 rlink는 삽입할 노드를 가리킴
				n->llink = node;		//n의 llink는 삽입할 노드를 가리킴
			}
			return 0;		//함수 종료
		}

		n = n->rlink;		//n은 n의 다음노드가 됨
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);		//리스트의 마지막에 노드 삽입
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)			//첫번째 노드가 없거나 리스트가 생성이 안되어 있을때
	{
		printf("nothing to delete.\n");		//에러문구 출력
		return 0;		//함수 종료
	}

	listNode* n = h->rlink;			//n은 첫번째 노드

	while(n != NULL && n != h) {		//n이 NULL이 아니고 head노드가 아닐때 반복
		if(n->key == key) {				//입력받은 key값과 n의 key값이 같다면
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);			//첫번째 노드에 할당된 메모리 해제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);			//마지막 노드에 할당된 메모리 해제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;		//n의 이전노드의 rlink는 n의 다음노드를 가리킴
				n->rlink->llink = n->llink;		//n의 다음노드의 llink는 n의 이전노드를 가리킴
				free(n);			//n에 할당된 메모리 해제
			}
			return 0;		//함수 종료
		}

		n = n->rlink;		//n은 n의 다음노드가 됨
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);		//에러문구 출력
	return 0;
}