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
/* �ʿ��� ������� �߰� */

typedef struct Node {			//Node
	int key;					//key��
	struct Node* llink;			//left link
	struct Node* rlink;			//right link
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);			//����Ʈ ����
int freeList(listNode* h);				//����Ʈ�� �Ҵ�� �޸� ����
int insertLast(listNode* h, int key);	//����Ʈ�� �������� ��� ����
int deleteLast(listNode* h);			//����Ʈ�� ������ ��� ����
int insertFirst(listNode* h, int key);	//����Ʈ�� ó���� ��� ����
int deleteFirst(listNode* h);			//����Ʈ�� ù��° ��� ����
int invertList(listNode* h);			//����Ʈ�� ��ũ�� �������� ���ġ

int insertNode(listNode* h, int key);	//�Է¹��� key������ ũ�ų� ���� ���տ� ���ο� ��� ����
int deleteNode(listNode* h, int key);	//�Է¹��� key�� ���� ��� ����

void printList(listNode* h);			//����Ʈ ���� ���

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;		//head��� ����
	printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");		//�޴� ���
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);			//�޴� ����

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);		//����Ʈ ����
			break;
		case 'p': case 'P':
			printList(headnode);		//����Ʈ ���� ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);	//�Է¹��� key������ ũ�ų� ���� ���տ� ���ο� ��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);	//�Է¹��� key�� ���� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);	//����Ʈ�� �������� ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//����Ʈ�� ������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	//����Ʈ�� ó���� ��� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//����Ʈ�� ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode);		//����Ʈ�� ��ũ�� �������� ���ġ
			break;
		case 'q': case 'Q':
			freeList(headnode);			//����Ʈ�� �Ҵ�� �޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//�޴� �̿��� �ٸ� �� �Է� �� �������� ���
			break;
		}

	}while(command != 'q' && command != 'Q');		//q�� Q�� �Է¹����� �ݺ��� ����

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h; 				//head����� rlink�� head��带 ����Ŵ
	(*h)->llink = *h;				//head����� rlink�� head��带 ����Ŵ
	(*h)->key = -9999;				//head����� key���� -9999�� �ʱ�ȭ
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)				//head����� rlink�� head��带 ����Ų�ٸ�
	{
		free(h);					//�޸� ����
		return 1;					//�Լ� ����
	}

	listNode* p = h->rlink;			//p�� head����� ���� ��带 ����

	listNode* prev = NULL;			//prev�� �޸� ������ ��带 ����Ŵ
	while(p != NULL && p != h) {	//p�� NULL�� �ƴϰ� head��尡 �ƴ϶�� �ݺ�
		prev = p;					//prev�� p ����
		p = p->rlink;				//p�� p�� ����Ű�� ���� ��尡 ��
		free(prev);					//prev�� �Ҵ�� �޸� ����
	}
	free(h);			//head��忡 �Ҵ�� �޸� ����
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//head��尡 NULL�ƶ��
		printf("Nothing to print....\n");	//�������� ���
		return;			//�Լ� ����
	}

	p = h->rlink;		//p�� head����� ���� ���

	while(p != NULL && p != h) {				//p�� NULL�� �ƴϰ� head��尡 �ƴ϶�� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);		//����Ʈ�� �ε����� key�� ���
		p = p->rlink;							//p�� ���� ��带 ����
		i++;
	}
	printf("  items = %d\n", i);				//����Ʈ�� ������ ����


	/* print addresses */
	printf("\n---checking addresses of links\n");				//head ����� rlink�� llink�� ����Ű�� ����� �ּ� ���
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {				//�� ����� rlink�� llink�� ����Ű�� ����� �ּ� ���
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;		//head��尡 NULL�̶�� �Լ� ����

	listNode* node = (listNode*)malloc(sizeof(listNode));	//���� �޸� �Ҵ�
	node->key = key;		//�Է¹��� key�� ����
	node->rlink = NULL;		//������ ��尡 ����Ű�� ���� ���� ����
	node->llink = NULL;		//������ ��尡 ����Ű�� ���� ���� ����

	if (h->rlink == h) /* ù ���� ���� */	//head��� �ۿ� ���� ���
	{
		h->rlink = node;		//head����� rlink�� ������ ��带 ����Ŵ
		h->llink = node;		//head����� llink�� ������ ��带 ����Ŵ
		node->rlink = h;		//������ ����� rlink�� head��带 ����Ŵ
		node->llink = h;		//������ ����� llink�� head��带 ����Ŵ
	} else {
		h->llink->rlink = node;	//head����� ���� ����� rlink�� ������ ��带 ����Ŵ
		node->llink = h->llink;	//������ ����� llink�� head����� llink�� ����Ű�� ��带 ����Ŵ
		h->llink = node;		//head����� llink�� ������ ��带 ����Ŵ
		node->rlink = h;		//������ ����� rlink�� head��带 ����Ŵ
	}

	return 1;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)			//ù��° ��尡 ���ų� ����Ʈ�� ������ �ȵǾ� ������
	{
		printf("nothing to delete.\n");		//�������� ���
		return 1;	//�Լ� ����
	}

	listNode* nodetoremove = h->llink;		//head��� ������ ���� nodetoremove(������ ���)

	/* link ���� */
	nodetoremove->llink->rlink = h;			//nodetoremove����� ��������� rlink�� head��带 ����Ŵ
	h->llink = nodetoremove->llink;			//head����� llink�� nodetoremove����� ������带 ����Ŵ

	free(nodetoremove);			//������ ��忡 �Ҵ�� �޸� ����

	return 1;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		//������ ��� ���� �޸� �Ҵ�
	node->key = key;		//������ ����� key���� �Է¹��� key���� ����
	node->rlink = NULL;		//������ ��尡 ����Ű�� ���� ���� ����
	node->llink = NULL;		//������ ��尡 ����Ű�� ���� ���� ����


	node->rlink = h->rlink;		//������ ����� rlink�� ������ ù��° ��带 ����Ŵ
	h->rlink->llink = node;		//������ ù��° ����� llink�� ������ ��带 ����Ŵ
	node->llink = h;			//������ ����� llink�� head��带 ����Ŵ
	h->rlink = node;			//head����� rlink�� ������ ��带 ����Ŵ


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)			//ù��° ��尡 ���ų� ����Ʈ�� ������ �ȵǾ� ������
	{
		printf("nothing to delete.\n");		//�������� ���
		return 0;		//�Լ� ����
	}

	listNode* nodetoremove = h->rlink;		//head��� ������ ���� nodetoremove(ù��° ���)

	/* link ���� */
	nodetoremove->rlink->llink = h;			//nodetoremove����� ��������� llink�� head��带 ����Ŵ
	h->rlink = nodetoremove->rlink;			//head����� rlink�� nodetoremove����� ������带 ����Ŵ

	free(nodetoremove);						//ù��° ��忡 �Ҵ�� �޸� ����

	return 1;

}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {			//ù��° ��尡 ���ų� ����Ʈ�� ������ �ȵǾ� ������
		printf("nothing to invert...\n");		//�������� ���
		return 0;		//�Լ� ����
	}
	listNode *n = h->rlink;			//n�� ù��° ���
	listNode *trail = h;			
	listNode *middle = h;

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;

	while(n != NULL && n != h){		//n�� NULL�� �ƴϰ� n�� head��尡 �ƴϸ� �ݺ�
		trail = middle;			//trail�� middle�� ��
		middle = n;				//middel�� n�� ��
		n = n->rlink;			//n�� n�� ���� ��尡 ��
		middle->rlink = trail;	//middle�� �������� trail�� ��
		middle->llink = n;		//middle�� �������� n�� ��
	}

	h->rlink = middle;			//ù��° ���� �ݺ����� ���� ���� middle(������ ���)�� ��

	return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;	//����Ʈ�� �������� �ʾҴٸ� �Լ� ����

	listNode* node = (listNode*)malloc(sizeof(listNode));	//������ ��� ���� �޸� �Ҵ�
	node->key = key;		//������ ����� key���� �Է¹��� key���� ����
	node->llink = node->rlink = NULL;		//������ ��尡 ����Ű�� ���� ���� ����

	if (h->rlink == h)			//ù���� ��尡 ������
	{
		insertFirst(h, key);	//����Ʈ�� ó���� ��� ����
		return 1;	//�Լ� ����
	}

	listNode* n = h->rlink;		//n�� ù��° ���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {		//n�� NULL�� �ƴϰ� n�� head��尡 �ƴϸ� �ݺ�
		if(n->key >= key) {				//n�� key���� �Է��� key������ ũ�ų� ���� ��
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {			//n�� ù��° ����̸�
				insertFirst(h, key);	//����Ʈ�� ó���� ��� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;		//������ ����� rlink�� n�� ����Ŵ
				node->llink = n->llink;	//������ ����� llink�� n�� ���� ��带 ����Ŵ
				n->llink->rlink = node;	//n�� ��������� rlink�� ������ ��带 ����Ŵ
				n->llink = node;		//n�� llink�� ������ ��带 ����Ŵ
			}
			return 0;		//�Լ� ����
		}

		n = n->rlink;		//n�� n�� ������尡 ��
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);		//����Ʈ�� �������� ��� ����
	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)			//ù��° ��尡 ���ų� ����Ʈ�� ������ �ȵǾ� ������
	{
		printf("nothing to delete.\n");		//�������� ���
		return 0;		//�Լ� ����
	}

	listNode* n = h->rlink;			//n�� ù��° ���

	while(n != NULL && n != h) {		//n�� NULL�� �ƴϰ� head��尡 �ƴҶ� �ݺ�
		if(n->key == key) {				//�Է¹��� key���� n�� key���� ���ٸ�
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);			//ù��° ��忡 �Ҵ�� �޸� ����
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);			//������ ��忡 �Ҵ�� �޸� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;		//n�� ��������� rlink�� n�� ������带 ����Ŵ
				n->rlink->llink = n->llink;		//n�� ��������� llink�� n�� ������带 ����Ŵ
				free(n);			//n�� �Ҵ�� �޸� ����
			}
			return 0;		//�Լ� ����
		}

		n = n->rlink;		//n�� n�� ������尡 ��
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);		//�������� ���
	return 0;
}