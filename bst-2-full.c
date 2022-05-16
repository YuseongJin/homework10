/*Binary Search Tree #2*/

#include <stdio.h>//standard input/output library, 표준 입출력 라이브러리
#include <stdlib.h>//c표준 유틸리티 함수들을 모아 놓은 헤더파일

typedef struct node {//구조체 선언
	int key;//int 형 변수 key 멤버 선언
	struct node *left;//자기참조 구조체, left
	struct node *right;//자기참조 구조체, right
} Node;//구조체 별칭

/* for stack */
#define MAX_STACK_SIZE		20
//MAX_STACK_SIZE를 20 으로 정의
Node* stack[MAX_STACK_SIZE];
int top = -1;
//int형 변수 top선언후 -1삽입

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
//MAX_QUEUE_SIZE를 20 으로 정의
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
//int형 변수 front선언후 -1삽입
int rear = -1;
//int형 변수 rear선언후 -1삽입

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();

//함수 원형선언

int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	int key;//int형 변수 선언, 키보드
	Node* head = NULL;//node head의 값을 선언후 NULL로 초기화

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력

	do{//do-while문을 통하여 반복 출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		//메뉴 출력

		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력받기	

		switch(command) {//스위치문
		//소문자와 대문자 모두 입력 받기
		case 'z': case 'Z'://z키를 입력 받았을 때
			initializeBST(&head);//initializeBST함수 실행
			break;//스위치문 끝
		case 'q': case 'Q'://q키를 입력 받았을 때
			freeBST(head);//freeBST함수 실행
			break;//스위치문 끝
		case 'i': case 'I'://i키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			insert(head, key);//insert함수 실행
			break;//스위치문 끝
		case 'd': case 'D'://d키를 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);
			//키 값 입력받기
			deleteNode(head, key);
			//deleteLeafNode함수 실행
			break;//스위치문 끝

		case 'r': case 'R'://r키를 입력 받았을 때
			recursiveInorder(head->left);
			//recursiveInorder함수 실행
			break;//스위치문 끝
		case 't': case 'T'://t키를 입력 받았을 때
			iterativeInorder(head->left);
			//iterativeInorder함수 실행
			break;//스위치문 끝

		case 'l': case 'L'://l키를 입력 받았을 때
			levelOrder(head->left);
			//levelOrder함수 실행
			break;//스위치문 끝

		case 'p': case 'P'://p키를 입력 받았을 때
			printStack();
			//printStack함수 실행
			break;//스위치문 끝

		default://이 외의 입력을 받았을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			//경고문 출력
			break;//스위치문 끝
		}

	}while(command != 'q' && command != 'Q');
	//q키를 사용하기 전까지 계속 반복
	return 1;//종료
}

int initializeBST(Node** h) {//BST초기화함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)//h가 NULL이 아니라면
		freeBST(*h);//freeBST함수 실행

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	//h를 동적 메모리 할당
	(*h)->left = NULL;	/* root */
	//h의 left값을 NULL로 초기화
	(*h)->right = *h;
	//h의 right에 h를 대입
	(*h)->key = -9999;
	//h의 key값을 -9999로 초기화

	top = -1;
	//top에 -1대입

	front = rear = -1;
	//-1을 rear에 삽입후 front에 삽입

	return 1;//종료
}



void recursiveInorder(Node* ptr)
//재귀적 중위 순회 함수
{
	if(ptr) {//ptr이라면
		recursiveInorder(ptr->left);
		//recursiveInorder함수 실행, left
		printf(" [%d] ", ptr->key);
		//ptr의 키 값 출력
		recursiveInorder(ptr->right);
		//recursiveInorder함수 실행, right
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
//반복 중위 순회 함수
{
	for(;;)//for 문의 무한루프
	{
		for(; node; node = node->left)
			push(node);
			//push 함수 실행
		node = pop();
		//pop함수 실행후 node에 삽입 

		if(!node) break;//node가 아니라면 중지
		printf(" [%d] ", node->key);
		//node의 key값 출력

		node = node->right;
		//node의 right 값을 node에 삽입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
//노드 레벨 순으로 순회하는 함수
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */
	//ptr이 아니라면 종료

	enQueue(ptr);

	for(;;)//반복문
	{
		ptr = deQueue();//deQueue값 ptr에 대입
		if(ptr) {//ptr 이라면
			printf(" [%d] ", ptr->key);
			//ptr의 key값 출력

			if(ptr->left)
			//ptr의 left값이라면
				enQueue(ptr->left);
				//enqueue함수 실행, left
			if(ptr->right)
			//ptr의 right값이라면
				enQueue(ptr->right);
				//enqueue함수 실행, right
		}
		else//이외
			break;//종료

	}

}


int insert(Node* head, int key)
//삽입 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//node 포인터형 변수 newNode 선언후 동적메모리할당
	newNode->key = key;
	//newnode의 key값을 key값으로 초기화
	newNode->left = NULL;
	//newnode의 left값을 NULL로 초기화
	newNode->right = NULL;
	//newnode의 right값을 NULL로 초기화

	if (head->left == NULL) {
	//head의 left값이 NULL이라면
		head->left = newNode;
		//head의 left값에 newNOde값 대입
		return 1;//종료
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//node 포인터변수 ptr선언 후 head의 left값 대입

	Node* parentNode = NULL;
	//node 포인터변수 parentNode선언 후 NULL로 초기화
	while(ptr != NULL) {
	//ptr이 NULL과 다르다면

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;
		//ptr의 key값이 key값과 같다면 종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;
		//parentNode에 ptr값 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
		//ptr의 key값이 key보다 작다면
			ptr = ptr->right;
			//ptr의 right값을 ptr에 대입
		else//이외
			ptr = ptr->left;
			//ptr의 left값을 ptr에 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
	//parentNode의 key값이 key보다 크다면
		parentNode->left = newNode;
		//parentNode의 left에 newNode 대입
	else//이외
		parentNode->right = newNode;
		//parentNode의 right에 newNode 대입
	return 1;//종료
}


int deleteNode(Node* head, int key)
//노드 삭제 함수
{
	if (head == NULL) {
	//head가 NULL이라면
		printf("\n Nothing to delete!!\n");
		//삭제할 것이 없음을 알림
		return -1;//종료(비정상)
	}

	if (head->left == NULL) {
	//head의 left값이 NULL이라면
		printf("\n Nothing to delete!!\n");
		//삭제할 것이 없음을 알림
		return -1;//종료(비정상)
	}

	/* head->left is the root */
	Node* root = head->left;
	//node포인트변수 root선언 후 head의 left값 대입

	Node* parent = NULL;
	//node포인트변수 parent선언 후 NULL로 초기화
	Node* ptr = root;
	//node포인트변수 ptr선언 후 root값 대입

	while((ptr != NULL)&&(ptr->key != key)) {
	//ptr이 NULL이랑 다르고, ptr의 key값이 key값가 다르다면
		if(ptr->key != key) {
		//ptr의 key값이 key값과 다르다면

			parent = ptr;	/* save the parent */
			//ptr을 parent에 대입

			if(ptr->key > key)
			//ptr의 key값이 key보다 크다면
				ptr = ptr->left;
				//ptr의 left값을 ptr에 대입
			else//이외
				ptr = ptr->right;
				//ptr의 right값을 ptr에 대입
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)//ptr이 NULL이라면
	{
		printf("No node for key [%d]\n ", key);
		//key의 노드가 없음을 출력
		return -1;
		//종료
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)
	//ptr의 left값이 NULL이고, ptr의 right값도 NULL이라면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
		//parent가 NULL이랑 다르다면
			if(parent->left == ptr)
			//parent의 left값이 ptr이랑 같다면
				parent->left = NULL;
				//parent의 left값을 NULL로 초기화

			else//이외
				parent->right = NULL;
				//parent의 right값을 NULL로 초기화
		} else {//이외
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;
			//head의 left값을 NULL로 초기화

		}

		free(ptr);//ptr 할당해제
		return 1;//종료
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))
	//ptr의 left값이 NULL이거나 ptr의 right값이 NULL이라면
	{
		Node* child;
		//node 포인터변수 child 선언
		if (ptr->left != NULL)
		//ptr의 left의 값이 NULL이랑 다르다면
			child = ptr->left;
			//ptr의 left값을 child에 대입
		else //이외
			child = ptr->right;
			//ptr의 right값을 child에 대입

		if(parent != NULL)
		//parent가 NULL이 아니라면
		{
			if(parent->left == ptr)
			//parent의 left값이 ptr이랑 같다면
				parent->left = child;
				//child값을 parent의 left에 대입
			else//이외
				parent->right = child;
				//child값을 parent의 right에 대입
		} else {//이 외
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;//child를 root에 삽입
		}

		free(ptr);//ptr 할당해제
		return 1;//종료
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	//Node 포인트변수 candidate 선언
	parent = ptr;//ptr을 parent에 대입


	candidate = ptr->right;
	//ptr의 right값을 candidate에 대입

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)
	//candidate의 left값이 NULL과 다르다면
	{
		parent = candidate;
		//candidate값을 parent에 대입
		candidate = candidate->left;
		//candidate의 left값을 candidate에 대입
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
	//parent의 right와 candidate와 같다면
		parent->right = candidate->right;
		//candidate의 right값을 parent의 right에 대입
	else//이외
		parent->left = candidate->right;
		//candidate의 right값을 parent의 left에 대입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;//candidate의 key값을 ptr의 key에 대입

	free(candidate);//candidate 할당해제
	return 1;//종료
}


void freeNode(Node* ptr)
//freeNode 함수
{
	if(ptr) {//ptr이라면
		freeNode(ptr->left);
		freeNode(ptr->right);
		//freeNode함수 실행, left, right
		free(ptr);//ptr 할당해제
	}
}

int freeBST(Node* head)//freeBST함수
//BST: 이진 탐색 트리
{

	if(head->left == head)
	//head의 값을 head의 left에 대입
	{
		free(head);//head 할당해제
		return 1;//종료
	}

	Node* p = head->left;
	//포인트 변수 node p선언후 head의 left값 대입

	freeNode(p);//freenode함수 실행

	free(head);//head 할당해제
	return 1;//종료
}



Node* pop()//pop함수
{
	if (top < 0) return NULL;//top이 0보다 작다면 NULL값 반환
	return stack[top--];//stack값 반환
}

void push(Node* aNode)//push함수
{
	stack[++top] = aNode;//anode값을 stack에 삽입
}


void printStack()//스택 출력
{
	int i = 0;//int형 변수 i선언후 0으로 초기화
	printf("--- stack ---\n");
	while(i <= top)//i가 top보다 작거나 같다면
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		//스택 출력
	}
}


Node* deQueue()//dequeue 함수, 큐에서 데이터를 출력하는함수
{
	if (front == rear) {//앞과 뒤가 같다면
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;//NULL값  반환
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	//위치 이동
	return queue[front];//queue값 반환

}

void enQueue(Node* aNode)//enqueue함수, 큐에서 데이터를 입력하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	//위치 이동
	if (front == rear) {//앞과 뒤가 같다면
		// printf("\n....Now Queue is full!!\n");
		return;//종료
	}

	queue[rear] = aNode;//aNode를 queue에 대입, 뒤
}





