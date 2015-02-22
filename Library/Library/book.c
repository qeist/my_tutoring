#include "book.h"


// ���� ������ �Լ����̴��� ���ϰ��� void �� �����սô�.
// ������ 0, ���н� 1 ����
int bookList_create(BookList *list)
{
	BookNode *hBookNode = (BookNode*)malloc(sizeof(BookNode));
	BookNode *tBookNode = (BookNode*)malloc(sizeof(BookNode));

	if (hBookNode == NULL)
	{
		printf("malloc() ERROR = BookList_create()\n");
		return 1;
	}

	if (tBookNode == NULL)
	{
		printf("malloc() ERROR = BookList_create()\n");
		return 1;
	}

	list->head = hBookNode;
	list->tail = tBookNode;

	hBookNode->next = tBookNode;
	tBookNode->prev = hBookNode;
	hBookNode->prev = NULL;
	tBookNode->next = NULL;

	list->len = 0;
	
	return 0;
}

BookNode* bookList_append(BookList *list, BookNode *newBookNode)
{
	BookNode *newNode = newBookNode;
	
	// ��ũ�� ����Ʈ ���ʿ� ����
	list->tail->prev->next = newNode;
	newNode->prev = list->tail->prev;
	newNode->next = list->tail;
	list->tail->prev = newNode;

	return newNode;
}

int bookList_displayAll(BookList *list)
{
	BookNode *curNode = list->head->next;

	while (curNode->next != NULL)
	{
		printf("%s \n", curNode->book_name);
		curNode = curNode->next;
	}

	return 0;
}

/*
<������ �޴� �Լ�>
1. ���� ��� - bookList_add()
2. ���� ���� - bookList_delete()
3. ���� �뿩 - bookList_borrow()
4. ���� �ݳ� - bookList_return()
5. ���� �˻� - bookList_search()
+
<����� �޴� �Լ�>
2. �� �뿩 ���
*/

/*
�Լ�ȣ�� ������ 0 ����
�Լ�ȣ�� ���н� 1 ����
*/
int bookList_add(BookList *list)
{
	char buf[128] = {0,};
	int len = 0;
	BookNode *newNode = (BookNode*)malloc(sizeof(newNode));

	newNode->book_id = list->tail->prev->book_id + 1;
	
	printf("   �� �� ��  : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';
	newNode->book_name = (char*)malloc(len);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()\n");
		return 1;
	}
	strcpy(newNode->book_name, buf);

	printf("   �� �� ��  : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';
	newNode->book_publisher = (char*)malloc(len);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()");
		return 1;
	}
	strcpy(newNode->book_publisher, buf);

	printf("   �� �� ��  : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';
	newNode->book_author = (char*)malloc(len);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()");
		return 1;
	}
	strcpy(newNode->book_author, buf);

	printf("     ISBN    : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';
	newNode->book_ISBN = (char*)malloc(len);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()");
		return 1;
	}
	strcpy(newNode->book_ISBN, buf);

	printf("   �� �� ó  : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';
	newNode->book_whereis = (char*)malloc(len);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()");
		return 1;
	}
	strcpy(newNode->book_whereis, buf);

	printf("�뿩���� ���� : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	// �Ϻη� ���๮�� �����ߴµ� �̷��� �ϴ°� �´°��� �ñ��մϴ�.
	buf[len - 1] = '\n';
	buf[len] = '\0';
	newNode->book_isBorrow = (char*)malloc(len+1);
	if (newNode->book_name == NULL)
	{
		printf("malloc() ERROR = bookList_add()");
		return 1;
	}
	strcpy(newNode->book_isBorrow, buf);

	bookList_append(list, newNode);
	return 0;
}

/*
- ������ �����ϸ� 0 ����
- ������ �����ϸ� 1 ����
*/
int bookList_delete(BookList *list)
{	
	char buf[64] = { 0, };
	int len = 0;
	int book_id = 0;
	BookNode *bNode = list->head->next;
	
	printf("���� �� ������ Ȥ�� ISBN : ");;
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (bNode->next != NULL)
	{
		if (strcmp(bNode->book_name, buf) == 0 ||
			strcmp(bNode->book_ISBN, buf) == 0)
		{
			book_print_info(bNode);
			printf("������ȣ�� �Է��ϸ� �����˴ϴ� : ");
			scanf("%d", &book_id);
			if (bNode->book_id == book_id)
			{
				bNode->prev->next = bNode->next;
				bNode->next->prev = bNode->prev;
				free(bNode);
				return 0;
			}
		}

		bNode = bNode->next;
	}

	return 1;
}

/*
 <���� �뿩>
 �����뿩 ������ 0 ����
 �����뿩 ���н� 1 ����
*/
int bookList_borrow(BookList *list)
{
	BookNode *bNode = list->head->next;
	
	char buf[64] = {0,};
	int len = 0;

	printf("������ �Ǵ� ISBN : ");
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (bNode->next != NULL)
	{
		if (strcmp(bNode->book_name, buf) == 0 ||
			strcmp(bNode->book_ISBN, buf) == 0)
		{
			book_print_info(bNode);
			printf("�й� : ");
			printf("������ȣ : ");
		}
	}
	
	

	return 0;
}
int bookList_return(BookList *list)
{
	return 0;
}

/*
- �˻��� �����ϸ� 0 ����
- �˻��� �����ϸ� 1 ����
*/
int bookList_search(BookList *list, int type)
{
	char keyword[64] = {0,};
	int len = 0;
	BookNode *curNode = list->head->next;

	printf("�˻�� �Է��ϼ��� : ");
	fgets(keyword, 64, stdin);
	len = strlen(keyword);
	keyword[len - 1] = '\0';

	if (type == 1)		// ������ �˻�
	{
		while (curNode->next != NULL)
		{
			if (strcmp(keyword, curNode->book_name) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			curNode = curNode->next;
		}
	}
	else if (type == 2) // ���ǻ� �˻�
	{
		while (curNode->next != NULL)
		{
			if (strcmp(keyword, curNode->book_publisher) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			curNode = curNode->next;
		}
	}
	else if (type == 3) // ISBN �˻�
	{
		while (curNode->next != NULL)
		{
			if (strcmp(keyword, curNode->book_ISBN) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			curNode = curNode->next;
		}
	}
	else if (type == 4) // ���ڸ� �˻�
	{
		while (curNode->next != NULL)
		{
			if (strcmp(keyword, curNode->book_author) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			curNode = curNode->next;
		}
	}
	else if (type == 5) // ��ü �˻�
	{
		while (curNode->next != NULL)
		{
			if (strcmp(keyword, curNode->book_name) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			if (strcmp(keyword, curNode->book_publisher) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			if (strcmp(keyword, curNode->book_ISBN) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			if (strcmp(keyword, curNode->book_author) == 0)
			{
				book_print_info(curNode);
				return 0;
			}

			curNode = curNode->next;
		}
	}

	puts("�ش� ������ �����ϴ�.");
	return 1;
}

int bookList_myBorrowList(BookList *list)
{

	return 0;
}

int book_print_info(BookNode *bNode)
{
	printf("  ���� ��ȣ  : %07d\n", bNode->book_id);
	printf("   �� �� ��  : %s\n", bNode->book_name);
	printf("   �� �� ��  : %s\n", bNode->book_publisher);
	printf("   �� �� ��  : %s\n", bNode->book_author);
	printf("     ISBN    : %s\n", bNode->book_ISBN);
	printf("   �� �� ó  : %s\n", bNode->book_whereis);
	printf("�뿩���� ���� : %s\n", bNode->book_isBorrow);
	return 0;
}