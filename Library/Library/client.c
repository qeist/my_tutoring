#include "client.h"

// 내가 구현한 함수들이더라도 리턴값은 void 를 지양합시다.
// 성공시 0, 실패시 1 리턴
int clientList_create(ClientList *list)
{
	//ClientNode hClientNode, tClientNode;

	// malloc() 함수와 같은 라이브러리 함수를 사용할 때에는 반드시 함수 원형을 알아보고 사용합시다. (soen.kr 또는 리눅스의 man page 참고)
	// 라이브러리 함수인데 괜찮겠지, 라는 안일한 생각은 버려야 합니다.
	// 라이브러리 함수일지라도 언제 어떻게 에러가 발생할 지 모르는 일입니다.
	// 코딩에서 가장 중요한 것들중에 하나는 "예외처리" 입니다.
	// 라이브러리 함수를 사용할 때에는 반드시 리턴값을 체크하는 습관을 들여야 합니다.
	// malloc() 함수 호출시 메모리 공간의 부족에 의해 메모리 할당에 실패하면 NULL 값을 리턴합니다.
	// 따라서 아래의 동적할당을 이상적으로 하기 위해서는,

	// Client *hClientNode = (ClientNode*)malloc(sizeof(ClientNode));
	// 호출 이후에 hClientNode 값이 NULL 인지를 체크해 보아야 합니다.
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

	// 링크드 리스트 뒤쪽에 연결
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

// 학번 중복 검사 함수
// 학번이 중복이면 1, 중복 아니면 0 을 리턴
int clientList_isUnique(ClientList * list, char* client_id)
{
	ClientNode *curNode = list->head->next;

	while (curNode->next != NULL)
	{ 
		if (atoi(curNode->client_id) == client_id)
		{
			printf("중복된 학번입니다.\n");
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

// 성공시 0, 실패시 1 리턴
int client_register(ClientList *list)
{
	// 학번 | 비밀번호 | 이름 | 주소
	// 1. 학번을 먼저 입력받아 중복 검사.
	// 2. 만일 동일한 학번이 있으면 오류메시지를 출력해야함.
	// 3. 문제가 없으면 학번순으로 정렬하여 저장해야 한다.
	// 4. 회원가입이 완료되면 초기 메뉴로 돌아가야 한다.

	ClientNode newNode = {0,};
	char buffer[128] = {0,};
	char *client_id = NULL;
	int len = 0; // 버퍼의 마지막에 '\0'을 넣기 위해
	printf("학번을 입력하세요 : ");
	fgets(buffer, 128, stdin);
	len = strlen(buffer);
	buffer[len - 1] = '\0';

	newNode.client_id = (char*)malloc(len);
	strcpy(newNode.client_id, buffer);

	if (!clientList_isUnique(list, newNode.client_id))
	{
		printf("비밀번호를 입력하세요 : ");
		fgets(buffer, 128, stdin);
		// 비밀번호를 1111 입력했으면 length 는 5.
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_password = (char*)malloc(len);
		if (newNode.client_password == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("이름을 입력하세요 : ");
		fgets(buffer, 128, stdin);
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_name = (char*)malloc(len);
		if (newNode.client_name == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("주소를 입력하세요 : ");
		fgets(buffer, 128, stdin);
		len = strlen(buffer);
		buffer[len - 1] = '\0';
		newNode.client_address = (char*)malloc(len);
		if (newNode.client_address == NULL)
		{
			printf("malloc() ERROR = client_register()\n");
		}

		printf("전화번호를 입력하세요 : ");
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

	printf("학번 : ");
	fgets(student_id, 128, stdin);
	len = strlen(student_id);
	student_id[len - 1] = '\0';

	printf("비밀번호 : ");
	fgets(password, 128, stdin);
	len = strlen(password);
	password[len - 1] = '\0';

	while (curNode->next != NULL)
	{
		// 학번 입력이 일치하면
		if (strcmp(curNode->client_id, student_id) == 0)
		{
			// 비밀번호도 일치하는지 확인
			if (strcmp(curNode->client_password, password) == 0)
			{
				// 관리자 계정이면 return 100
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

3. 개인정보 수정 - clientList_editMyInfo()
4. 회원 탈퇴 - clientList_leave()

*/


/*
 회원정보 수정 성공시 0 리턴
 회원정보 수정 실패시 1 리턴
*/
int clientList_editMyInfo(ClientList *list)
{
	ClientNode *cNode = list->head->next;
	char buf[64] = {0,};
	int len = 0;
	
	printf("학번을 입력하세요 : ");
	fgets(buf, 64, stdin);
	len = strlen(buf);
	buf[len - 1] = '\0';

	while (cNode->next != NULL)
	{
		if (strcmp(cNode->client_id, buf) == 0)
		{
			printf("새로운 비밀번호 : ");
			fgets(buf, 64, stdin);
			len = strlen(buf);
			buf[len - 1] = '\0';

			free(cNode->client_password);
			cNode->client_password = (char*)malloc(len);
			strcpy(cNode->client_password, buf);

			printf("새로운 주소 : ");
			fgets(buf, 64, stdin);
			len = strlen(buf);
			buf[len - 1] = '\0';

			free(cNode->client_address);
			cNode->client_address = (char*)malloc(len);
			strcpy(cNode->client_address, buf);

			printf("새로운 연락처 : ");
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
	
	printf("회원정보 수정 실패했습니다.\n");
	return 1;
}

/*
 회원 탈퇴 함수
 탈퇴 성공시 0 리턴
 탈퇴 실패시 1 리턴
*/
int clientList_leave(ClientList *List)
{
	return 0;
}

int clientList_search(ClientList *List, int type)
{
	return 0;
}