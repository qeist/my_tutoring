#ifndef __BORROW_H__
#define __BORROW_H__

typedef struct _borrowNode BorrowNode;
typedef struct _borrowList BorrowList;
typedef struct _borrowNode
{
	BorrowNode *prev;
	BorrowNode *next;
	int   book_id;
	char *book_name;
	time_t borrow_date;
	time_t return_date;
	
}BorrowNode;

typedef struct _borrowList
{
	BorrowNode *head;
	BorrowNode *tail;
	int len;
}BorrowList;

int bookList_create(BookList *list);
BookNode* bookList_append(BookList *list, BookNode *newBookNode);
int bookList_displayAll(BookList *list);



#endif