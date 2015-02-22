#ifndef __BOOK_H__
#define __BOOK_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _bookNode BookNode;
typedef struct _bookList BookList;
typedef struct _bookNode
{
	BookNode *prev;
	BookNode *next;
	int   book_id;
	char *book_name;
	char *book_publisher;
	char *book_author;
	char *book_ISBN;
	char *book_whereis;
	char *book_isBorrow;
}BookNode;

typedef struct _bookList
{
	BookNode *head;
	BookNode *tail;
	int len;
}BookList;

int bookList_create(BookList *list);
BookNode* bookList_append(BookList *list, BookNode *newBookNode);
int bookList_displayAll(BookList *list);


int bookList_add(BookList *list);
int bookList_delete(BookList *list);
int bookList_borrow(BookList *list);
int bookList_return(BookList *list);
int bookList_search(BookList *list, int type);

int bookList_myBorrowList(BookList *list);

int book_print_info(BookNode *bNode);
#endif