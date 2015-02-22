#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "fileLoad.h"

enum menu_init {REGISTER = 1, LOGIN, QUIT};
enum admin_menu {BOOK_ADD = 1, BOOK_DELETE, BOOK_BORROW, 
				BOOK_RETURN, BOOK_SEARCH, MEMBER_DISPLAY, 
				ADMIN_LOGOUT, ADMIN_QUIT};


char *path_client = "client.txt";
char *path_book = "book.txt";
char *path_borrow = "borrow.txt";

int main(void)
{
	int menu = 0;
	int result = 0;
	ClientList cList;
	BookList bList;

	fileLoad_book(path_book, &bList);
	fileLoad_client(path_client, &cList);
	//fileLoad_borrow(path_borrow);
	
	while (1)
	{
		print_init_menu();
		scanf("%d", &menu);
		getchar();

		if (menu == REGISTER)
		{
			client_register(&cList);
			menu = 0;
		}
		else if (menu == LOGIN)
		{
			result = client_login(&cList);

			if (result == 100)		// ������ �α��� ����
			{
				while (1)
				{
					print_admin_menu();
					scanf("%d", &menu);
					getchar();

					if (menu == BOOK_ADD)
						bookList_add(&bList);
					else if (menu == BOOK_DELETE)
						bookList_delete(&bList);
					else if (menu == BOOK_BORROW)
						bookList_borrow(&bList);
					else if (menu == BOOK_RETURN)
						bookList_return(&bList);
					else if (menu == BOOK_SEARCH)
					{
						while (1)
						{
							print_user_submenu();
							scanf("%d", &menu);
							getchar();

							if (menu == 1)			// ������ �˻�
								bookList_search(&bList, 1);
							else if (menu == 2)		// ���ǻ� �˻�
								bookList_search(&bList, 2);
							else if (menu == 3)		// ISBN �˻�
								bookList_search(&bList, 3);
							else if (menu == 4)		// ���ڸ� �˻�
								bookList_search(&bList, 4);
							else if (menu == 5)		// ��ü �˻�
								bookList_search(&bList, 5);
							else if (menu == 6)
								break;
						}
						menu = 0;
					}
					else if (menu == MEMBER_DISPLAY)
					{
						print_admin_submenu();

						while (1)
						{
							if (menu == 1)			// �̸� �˻�
								clientList_search(&cList, 1);
							else if (menu == 2)		// �й� �˻�
								clientList_search(&cList, 2);
							else if (menu == 3)		// ��ü �˻�
								clientList_search(&cList, 3);
							else if (menu == 4)		// ��ü ����Ʈ
								clientList_search(&cList, 4);
							else if (menu == 5)		// ���� �޴�
								break;

							menu = 0;
						}
					}
					else if (menu == ADMIN_LOGOUT)
						break;
					else if (menu == ADMIN_QUIT)
					{
						// ���� �ΰ��� �ѹ��� ��� ����������..
						puts("���α׷��� �����մϴ�.");
						break;
					}
				}
				
			}
			else if (result == 1)	// �Ϲ� �α��� ����
			{
				while (1)
				{
					print_user_menu();
					scanf("%d", &menu);
					getchar();
					
					if (menu == 1)		// ���� �˻�
					{
						while (1)
						{
							print_user_submenu();
							scanf("%d", &menu);
							getchar();
							
							if (menu == 1)			// ������ �˻�
								bookList_search(&bList, 1);
							else if (menu == 2)		// ���ǻ� �˻�
								bookList_search(&bList, 2);
							else if (menu == 3)		// ISBN �˻�
								bookList_search(&bList, 3);
							else if (menu == 4)		// ���ڸ� �˻�
								bookList_search(&bList, 4);
							else if (menu == 5)		// ��ü �˻�
								bookList_search(&bList, 5);
							else if (menu == 6)
								break;
						}
					}
					else if (menu == 2) // �� ���� ���
						bookList_myBorrowList(&bList);
					else if (menu == 3) // �������� ����
						clientList_editMyInfo(&cList);
					else if (menu == 4) // ȸ��Ż��
						clientList_leave(&cList);
					else if (menu == 5) // �α׾ƿ�
						break;
					else if (menu == 6) // ���α׷� ����
					{
						// ���� �ΰ��� �ѹ��� ��� ����������..
						puts("���α׷��� �����մϴ�.");
						break;
					}
					menu = 0;
				}
			}
			else
				print_login_error();
		}
		else if (menu == QUIT)
		{
			// �����ǰų� ������ �ִ� data�� ���� �޸𸮿� �÷��״ٰ�
			// ���α׷��� ����� ��, ���� ������ ����� �Ѳ�����
			// ���� �����մϴ�.
			fileSave_book(path_book, &bList);
			//fileSave_borrow(path_borrow);
			fileSave_client(path_client, &cList);
			print_quit();

			getchar();
			break;
		}
		else
			print_menu_error();
	}

	return 0;
}