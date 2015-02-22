#include "fileLoad.h"
#include "client.h"
#include "book.h"
#include "borrow.h"

/*
*  - client.txt 파일을 로드하는 함수
*  - 성공시 0 실패시 1 리턴
*/
int fileLoad_client(const char *path, ClientList *cList) //이 함수에서 path에 대한 변경이 확실히 없다면, const 키워드를 사용합시다.
{
	
	//변수의 선언이 필요할 때에는 반드시 초기화를 습관들입시다.
	char buf[256] = {0,};
	char *token = NULL;
	FILE *fp = fopen(path, "r");
	ClientNode *tmpNode  = NULL;

	//파일 입출력 라이브러리 관련 함수를 사용할 때에도 반드시 리턴값을 확인하는 습관을 들입시다.
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR - fileLoad_client()\n");
		return 1;
	}


	// client DBLinkedlist 생성
	if (clientList_create(cList))
	{
		printf("client DBLinkedlist create error.\n");
		return 1;
	}

	while (1)
	{
		// 학번 | 비밀번호 | 이름 | 주소 | 전화번호
		if (fgets(buf, 256, fp) == NULL) break;
        
        tmpNode = (ClientNode*)malloc(sizeof(ClientNode));

		if (tmpNode == NULL)
		{
			printf("malloc() ERROR = fileLoad_client()\n");
			return 1;
		}

		// 학번
		token = strtok(buf, "|");

		tmpNode->client_id = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_id, token);
		// 비밀번호
		token = strtok(NULL, "|");
		
		tmpNode->client_password = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_password, token);
		// 이름
		token = strtok(NULL, "|");
		
		tmpNode->client_name = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_name, token);
		// 주소
		token = strtok(NULL, "|");
		
		tmpNode->client_address = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_address, token);
		// 전화번호
		token = strtok(NULL, "|");
		
		tmpNode->client_phone = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_phone, token);
		
		clientList_append(cList, tmpNode);
	}

	fclose(fp);
	return 0;
}

/*
*  - book.txt 파일을 로드하는 함수
*  - 성공시 0 실패시 1 리턴
*/
int fileLoad_book(const char *path, BookList *bList)
{
	char buf[256] = { 0, };
	char *token = NULL;
	FILE *fp = fopen(path, "r");
	BookNode *tmpNode = NULL;
	
	if (fp == NULL)
	{ 
		printf("FILE OPEN ERROR - fileLoad_book()\n");
		return 1;
	}

	if (bookList_create(bList))
	{
		printf("book DBLinkedlist create error.\n");
		return 1;
	}

	while (1)
	{
		// 도서번호 | 도서명 | 출판사 | 저자명 | ISBN | 소장처 | 대여가능여부
		if (fgets(buf, 256, fp) == NULL) break;

		tmpNode = (BookNode*)malloc(sizeof(BookNode));
		

		if (tmpNode == NULL)
		{
			printf("malloc() ERROR = fileLoad_book()\n");
			return 1;
		}

		// 도서번호
		token = strtok(buf, "|");
		tmpNode->book_id = atoi(token);
		
		// 도서명
		token = strtok(NULL, "|");
		tmpNode->book_name = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_name, token);
		
		// 출판사
		token = strtok(NULL, "|");
		tmpNode->book_publisher = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_publisher, token);

		// 저자명
		token = strtok(NULL, "|");
		tmpNode->book_author = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_author, token);

		// ISBN
		token = strtok(NULL, "|");
		tmpNode->book_ISBN = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_ISBN, token);

		// 소장처
		token = strtok(NULL, "|");
		tmpNode->book_whereis = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_whereis, token);
		
		// 대여가능 여부
		token = strtok(NULL, "|");
		tmpNode->book_isBorrow = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_isBorrow, token);
		
		bookList_append(bList, tmpNode);

	}

	fclose(fp);
	return 0;
}

/*
*
*
*
*/
int fileLoad_borrow(const char *path)
{


	return 0;
}


int fileSave_client(const char *path, ClientList *cList)
{
	ClientNode *curNode = cList->head->next;
	FILE *fp = fopen("temp_client.txt", "wt");

	while (curNode->next != NULL)
	{
		fprintf(fp, "%s|%s|%s|%s|%s", curNode->client_id, curNode->client_password
									 , curNode->client_name, curNode->client_address
									 , curNode->client_phone);
		curNode = curNode->next;
	}

	fclose(fp);

	if (remove("client.txt") == -1)
		printf("remove error! : %d\n", errno);
	if (rename("temp_client.txt", path) == -1)
		printf("rename error! : %d\n", errno);

	return 0;
}

int fileSave_book(const char *path, BookList *bList)
{
	BookNode *curNode = bList->head->next;
	FILE *fp = fopen("temp_book.txt", "wt");

	while (curNode->next != NULL)
	{
		fprintf(fp, "%07d|%s|%s|%s|%s|%s|%s", curNode->book_id, curNode->book_name
										, curNode->book_publisher, curNode->book_author
										, curNode->book_ISBN, curNode->book_whereis
										, curNode->book_isBorrow);

		curNode = curNode->next;
	}

	fclose(fp);

	if (remove("book.txt") == -1)
		printf("remove error! : %d\n", errno);
	if (rename("temp_book.txt", path) == -1)
		printf("rename error! : %d\n", errno);

	return 0;
}

int fileSave_borrow(const char *path)
{
	return 0;
}