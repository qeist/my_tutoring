#include "client.h"

// ���� ������ �Լ����̴��� ���ϰ��� void �� �����սô�.
// ������ 0, ���н� 1 ����
int clientList_create(ClientList *list)
{
	//ClientNode hClientNode, tClientNode;

	// malloc() �Լ��� ���� ���̺귯�� �Լ��� ����� ������ �ݵ�� �Լ� ������ �˾ƺ��� ����սô�. (soen.kr �Ǵ� �������� man page ����)
	// ���̺귯�� �Լ��ε� ��������, ��� ������ ������ ������ �մϴ�.
	// ���̺귯�� �Լ������� ���� ��� ������ �߻��� �� �𸣴� ���Դϴ�.
	// �ڵ����� ���� �߿��� �͵��߿� �ϳ��� "����ó��" �Դϴ�.
	// ���̺귯�� �Լ��� ����� ������ �ݵ�� ���ϰ��� üũ�ϴ� ������ �鿩�� �մϴ�.
	// malloc() �Լ� ȣ��� �޸� ������ ������ ���� �޸� �Ҵ翡 �����ϸ� NULL ���� �����մϴ�.
	// ���� �Ʒ��� �����Ҵ��� �̻������� �ϱ� ���ؼ���,

	// Client *hClientNode = (ClientNode*)malloc(sizeof(ClientNode));
	// ȣ�� ���Ŀ� hClientNode ���� NULL ������ üũ�� ���ƾ� �մϴ�.
	ClientNode *hClientNode = (ClientNode*)malloc(sizeof(ClientNode));
	ClientNode *tClientNode = (ClientNode*)malloc(sizeof(ClientNode));

	if (hClientNode == NULL)
	{
		printf("malloc() ERROR = ClientList_create()\n");
		return 1;
	}

	if (tClientNode == NULL)
	{
		printf("malloc() ERROR = ClientList_create()\n");
		return 1;
	}

	list->head = hClientNode;
	list->tail = tClientNode;

	hClientNode->prev = NULL;
	hClientNode->next = tClientNode;
	tClientNode->prev = hClientNode;
	tClientNode->next = NULL;

	list->len = 0;

	return 0;
}

ClientNode* clientList_append(ClientList *list, ClientNode *newClientNode)
{
	ClientNode *newNode = newClientNode;

	if (newNode == NULL)
		printf("malloc() ERROR = clientList_append()\n");

	// ��ũ�� ����Ʈ ���ʿ� ����
	list->tail->prev->next = newNode;
	newNode->prev = list->tail->prev;
	newNode->next = list->tail;
	list->tail->prev = newNode;

	return newNode;
}

int isMallocError(ClientNode *cNode)
{
	if (cNode == NULL)
	{
		printf("malloc() error.\n");
		return 1;
	}

	return 0;
}

// �й� �ߺ� �˻� �Լ�
// �й��� �ߺ��̸� 1, �ߺ� �ƴϸ� 0 �� ����
int clientList_isUnique(ClientList * list, char* client_id)
{
	ClientNode *curNode = list->head->next;

	while (curNode->next != NULL)
	{ 
		if (atoi(curNode->client_id) == client_id)
		{
			printf("�ߺ��� �й��Դϴ�.\n");
			return 1;
		}
		
		curNode = curNode->next;
	}
	
	return 0;
}


int clientList_displayAll(ClientList *list)
{
	ClientNode *curNode = list->head->next;

	puts("?");
	while (curNode->next != NULL)
	{
		printf("%s \n", curNode->client_name);
		curNode = curNode->next;
	}

	return 0;
}

// ������ 0, ���н� 1 ����
int client_register(ClientList *list)
{
	// �й� | ��й�ȣ | �̸� | �ּ�
	// 1. �й��� ���� �Է¹޾� �ߺ� �˻�.
	// 2. ���� ������ �й��� ������ �����޽����� ����ؾ���.
	// 3. ������ ������ �й������� �����Ͽ� �����ؾ� �Ѵ�.
	// 4. ȸ�������� �Ϸ�Ǹ� �ʱ� �޴��� ���ư��� �Ѵ�.

	ClientNode newNode = {0,};
	char buffer[128] = {0,};
	char *client_id = NULL;
	int len = 0; // ������ �������� '\0'�� �ֱ� ����
	printf("�й��� �Է��ϼ��� : ");
	fgets(buffer, 128, stdin);
	len = strlen(buffer);
	buffer[len - 1] = '\0';

	newNode.client_id = (char*)malloc(len);
	strcpy(newNode.client_id, buffer);

	if (!clientList_isUnique(list, newNode.client_id))
	{
		printf("��й�ȣ�� �Է��ϼ��� : ");
		fgets(buffer, 128, stdin);
		// ��й�ȣ�� 1111 �Է������� length �� 5.
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_password = (char*)malloc(len);
		if (newNode.client_password == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("�̸��� �Է��ϼ��� : ");
		fgets(buffer, 128, stdin);
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_name = (char*)malloc(len);
		if (newNode.client_name == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("�ּҸ� �Է��ϼ��� : ");
		fgets(buffer, 128, stdin);
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_address = (char*)malloc(len);
		if (newNode.client_address == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("��ȭ��ȣ�� �Է��ϼ��� : ");
		fgets(buffer, 128, stdin);
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_phone = (char*)malloc(len);
		if (newNode.client_phone == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}
	}
	
	clientList_append(list, &newNode);

	return 0;
}

int client_login(ClientList *list)
{
	char student_id[128] = {0,};
	char password[128] = {0,};
	int len = 0;
	ClientNode *curNode = list->head->next;

	printf("�й� : ");
	fgets(student_id, 128, stdin);
	len = strlen(student_id);
	student_id[len - 1] = '\0';

	printf("��й�ȣ : ");
	fgets(password, 128, stdin);
	len = strlen(password);
	password[len - 1] = '\0';

	while (curNode->next != NULL)
	{
		// �й� �Է��� ��ġ�ϸ�
		if (strcmp(curNode->client_id, student_id) == 0)
		{
			// ��й�ȣ�� ��ġ�ϴ��� Ȯ��
			if (strcmp(curNode->client_password, password) == 0)
			{
				// ������ �����̸� return 100
				if (strcmp(curNode->client_id, "admin") == 0)
					return 100;

				return 1;
			}
		}

		curNode = curNode->next;
	}

	return 0;
}

/*

3. �������� ���� - clientList_editMyInfo()
4. ȸ�� Ż�� - clientList_leave()

*/


/*
 ȸ������ ���� ������ 0 ����
 ȸ������ ���� ���н� 1 ����
*/
int clientList_editMyInfo(ClientList *list)
{
	ClientNode *cNode = list->head->next;
	char buf[64] = {0,};
	int len = 0;
	
	printf("�й��� �Է��ϼ��� : ");
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (cNode->next != NULL)
	{
		if (strcmp(cNode->client_id, buf) == 0)
		{
			printf("���ο� ��й�ȣ : ");
			fgets(buf, 64, stdin);
			len = strlen(buf);
			buf[len - 1] = '\0';

			free(cNode->client_password);
			cNode->client_password = (char*)malloc(len);
			strcpy(cNode->client_password, buf);

			printf("���ο� �ּ� : ");
			fgets(buf, 64, stdin);
			len = strlen(buf);
			buf[len - 1] = '\0';

			free(cNode->client_address);
			cNode->client_address = (char*)malloc(len);
			strcpy(cNode->client_address, buf);

			printf("���ο� ����ó : ");
			fgets(buf, 64, stdin);
			len = strlen(buf);
			buf[len - 1] = '\n';
			buf[len] = '\0';

			free(cNode->client_phone);
			cNode->client_phone = (char*)malloc(len+1);
			strcpy(cNode->client_phone, buf);

			return 0;
		}

		cNode = cNode->next;
	}
	
	printf("ȸ������ ���� �����߽��ϴ�.\n");
	return 1;
}

/*
 ȸ�� Ż�� �Լ�
 Ż�� ������ 0 ����
 Ż�� ���н� 1 ����
*/
int clientList_leave(ClientList *List)
{
	return 0;
}

int clientList_search(ClientList *List, int type)
{
	return 0;
}