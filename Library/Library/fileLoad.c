#include "fileLoad.h"
#include "client.h"
#include "book.h"
#include "borrow.h"

/*
*  - client.txt ������ �ε��ϴ� �Լ�
*  - ������ 0 ���н� 1 ����
*/
int fileLoad_client(const char *path, ClientList *cList) //�� �Լ����� path�� ���� ������ Ȯ���� ���ٸ�, const Ű���带 ����սô�.
{
	
	//������ ������ �ʿ��� ������ �ݵ�� �ʱ�ȭ�� �������Խô�.
	char buf[256] = {0,};
	char *token = NULL;
	FILE *fp = fopen(path, "r");
	ClientNode *tmpNode  = NULL;

	//���� ����� ���̺귯�� ���� �Լ��� ����� ������ �ݵ�� ���ϰ��� Ȯ���ϴ� ������ ���Խô�.
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR - fileLoad_client()\n");
		return 1;
	}


	// client DBLinkedlist ����
	if (clientList_create(cList))
	{
		printf("client DBLinkedlist create error.\n");
		return 1;
	}

	while (1)
	{
		// �й� | ��й�ȣ | �̸� | �ּ� | ��ȭ��ȣ
		if (fgets(buf, 256, fp) == NULL) break;
        
        tmpNode = (ClientNode*)malloc(sizeof(ClientNode));

		if (tmpNode == NULL)
		{
			printf("malloc() ERROR = fileLoad_client()\n");
			return 1;
		}

		// �й�
		token = strtok(buf, "|");

		tmpNode->client_id = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_id, token);
		// ��й�ȣ
		token = strtok(NULL, "|");
		
		tmpNode->client_password = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_password, token);
		// �̸�
		token = strtok(NULL, "|");
		
		tmpNode->client_name = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_name, token);
		// �ּ�
		token = strtok(NULL, "|");
		
		tmpNode->client_address = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_address, token);
		// ��ȭ��ȣ
		token = strtok(NULL, "|");
		
		tmpNode->client_phone = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->client_phone, token);
		
		clientList_append(cList, tmpNode);
	}

	fclose(fp);
	return 0;
}

/*
*  - book.txt ������ �ε��ϴ� �Լ�
*  - ������ 0 ���н� 1 ����
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
		// ������ȣ | ������ | ���ǻ� | ���ڸ� | ISBN | ����ó | �뿩���ɿ���
		if (fgets(buf, 256, fp) == NULL) break;

		tmpNode = (BookNode*)malloc(sizeof(BookNode));
		

		if (tmpNode == NULL)
		{
			printf("malloc() ERROR = fileLoad_book()\n");
			return 1;
		}

		// ������ȣ
		token = strtok(buf, "|");
		tmpNode->book_id = atoi(token);
		
		// ������
		token = strtok(NULL, "|");
		tmpNode->book_name = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_name, token);
		
		// ���ǻ�
		token = strtok(NULL, "|");
		tmpNode->book_publisher = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_publisher, token);

		// ���ڸ�
		token = strtok(NULL, "|");
		tmpNode->book_author = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_author, token);

		// ISBN
		token = strtok(NULL, "|");
		tmpNode->book_ISBN = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_ISBN, token);

		// ����ó
		token = strtok(NULL, "|");
		tmpNode->book_whereis = (char*)malloc(strlen(token) + 1);
		strcpy(tmpNode->book_whereis, token);
		
		// �뿩���� ����
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