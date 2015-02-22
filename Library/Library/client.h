#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 구조체 선언과 동시에 typedef를 정의하고 있습니다.
// 그런데 12번 13번째 줄에서는 그들 구조체를 한번더 typedef 하고있습니다. (중복입니다.)
// 구조체 선언에 typedef를 빼고 2줄의 typedef문을 구조체 선언부 아래쪽으로 빼던가,
// 2줄의 typedef문을 제거하십시오.

typedef struct _clientNode ClientNode;
typedef struct _clientList ClientList;
typedef struct _clientNode
{
	ClientNode *prev;
	ClientNode *next;
	char *client_id;
	char *client_password;
	char *client_name;
	char *client_address;
	char *client_phone;
}ClientNode;

typedef struct _clientList
{
	ClientNode *head;
	ClientNode *tail;
	int len;
}ClientList;

int clientList_create(ClientList *list);
ClientNode* clientList_append(ClientList *list, ClientNode *newClientNode);
int clientList_displayAll(ClientList *list);
int clientList_isUnique(ClientList * list, int client_id);

int client_register(ClientList *list);

/*
client_login()
 관리자 계정이면 return 100;
 일반 계정이면 return 1;
 로그인 실패는 return 0;
*/
int client_login(ClientList *list);
int clientList_editMyInfo(ClientList *List);
int clientList_leave(ClientList *List);

int clientList_search(ClientList *List, int type);

#endif