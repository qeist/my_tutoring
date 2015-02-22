#include "book.h"


// 내가 구현한 함수들이더라도 리턴값은 void 를 지양합시다.
// 성공시 0, 실패시 1 리턴
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
	
	// 링크드 리스트 뒤쪽에 연결
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
<관리자 메뉴 함수>
1. 도서 등록 - bookList_add()
2. 도서 삭제 - bookList_delete()
3. 도서 대여 - bookList_borrow()
4. 도서 반납 - bookList_return()
5. 도서 검색 - bookList_search()
+
<사용자 메뉴 함수>
2. 내 대여 목록
*/

/*
함수호출 성공시 0 리턴
함수호출 실패시 1 리턴
*/
int bookList_add(BookList *list)
{
	char buf[128] = {0,};
	int len = 0;
	BookNode *newNode = (BookNode*)malloc(sizeof(newNode));

	newNode->book_id = list->tail->prev->book_id + 1;
	
	printf("   도 서 명  : ");
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

	printf("   출 판 사  : ");
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

	printf("   저 자 명  : ");
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

	printf("   소 장 처  : ");
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

	printf("대여가능 여부 : ");
	fgets(buf, 128, stdin);
	len = strlen(buf);
	// 일부러 개행문자 삽입했는데 이렇게 하는게 맞는건지 궁금합니다.
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
- 삭제에 성공하면 0 리턴
- 삭제에 실패하면 1 리턴
*/
int bookList_delete(BookList *list)
{	
	char buf[64] = { 0, };
	int len = 0;
	int book_id = 0;
	BookNode *bNode = list->head->next;
	
	printf("삭제 할 도서명 혹은 ISBN : ");;
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (bNode->next != NULL)
	{
		if (strcmp(bNode->book_name, buf) == 0 ||
			strcmp(bNode->book_ISBN, buf) == 0)
		{
			book_print_info(bNode);
			printf("도서번호를 입력하면 삭제됩니다 : ");
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
 <도서 대여>
 도서대여 성공시 0 리턴
 도서대여 실패시 1 리턴
*/
int bookList_borrow(BookList *list)
{
	BookNode *bNode = list->head->next;
	
	char buf[64] = {0,};
	int len = 0;

	printf("도서명 또는 ISBN : ");
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (bNode->next != NULL)
	{
		if (strcmp(bNode->book_name, buf) == 0 ||
			strcmp(bNode->book_ISBN, buf) == 0)
		{
			book_print_info(bNode);
			printf("학번 : ");
			printf("도서번호 : ");
		}
	}
	
	

	return 0;
}
int bookList_return(BookList *list)
{
	return 0;
}

/*
- 검색에 성공하면 0 리턴
- 검색에 실패하면 1 리턴
*/
int bookList_search(BookList *list, int type)
{
	char keyword[64] = {0,};
	int len = 0;
	BookNode *curNode = list->head->next;

	printf("검색어를 입력하세요 : ");
	fgets(keyword, 64, stdin);
	len = strlen(keyword);
	keyword[len - 1] = '\0';

	if (type == 1)		// 도서명 검색
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
	else if (type == 2) // 출판사 검색
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
	else if (type == 3) // ISBN 검색
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
	else if (type == 4) // 저자명 검색
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
	else if (type == 5) // 전체 검색
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

	puts("해당 도서가 없습니다.");
	return 1;
}

int bookList_myBorrowList(BookList *list)
{

	return 0;
}

int book_print_info(BookNode *bNode)
{
	printf("  도서 번호  : %07d\n", bNode->book_id);
	printf("   도 서 명  : %s\n", bNode->book_name);
	printf("   출 판 사  : %s\n", bNode->book_publisher);
	printf("   저 자 명  : %s\n", bNode->book_author);
	printf("     ISBN    : %s\n", bNode->book_ISBN);
	printf("   소 장 처  : %s\n", bNode->book_whereis);
	printf("대여가능 여부 : %s\n", bNode->book_isBorrow);
	return 0;
}