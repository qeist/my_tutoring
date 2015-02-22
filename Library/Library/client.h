#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ����ü ����� ���ÿ� typedef�� �����ϰ� �ֽ��ϴ�.
// �׷��� 12�� 13��° �ٿ����� �׵� ����ü�� �ѹ��� typedef �ϰ��ֽ��ϴ�. (�ߺ��Դϴ�.)
// ����ü ���� typedef�� ���� 2���� typedef���� ����ü ����� �Ʒ������� ������,
// 2���� typedef���� �����Ͻʽÿ�.

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
 ������ �����̸� return 100;
 �Ϲ� �����̸� return 1;
 �α��� ���д� return 0;
*/
int client_login(ClientList *list);
int clientList_editMyInfo(ClientList *List);
int clientList_leave(ClientList *List);

int clientList_search(ClientList *List, int type);

#endif