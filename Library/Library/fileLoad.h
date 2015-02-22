#ifndef __FILELOAD_H__
#define __FILELOAD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "book.h"

#include <direct.h>

//extern ClientList cList;


int fileLoad_client(const char *path, ClientList *cList);
int fileLoad_book(const char *path, BookList *bList);
int fileLoad_borrow(const char *path);

int fileSave_client(const char *path, ClientList *cList);
int fileSave_book(const char *path, BookList *bList);
int fileSave_borrow(const char *path);
#endif