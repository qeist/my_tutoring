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

			if (result == 100)		// 관리자 로그인 성공
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

							if (menu == 1)			// 도서명 검색
								bookList_search(&bList, 1);
							else if (menu == 2)		// 출판사 검색
								bookList_search(&bList, 2);
							else if (menu == 3)		// ISBN 검색
								bookList_search(&bList, 3);
							else if (menu == 4)		// 저자명 검색
								bookList_search(&bList, 4);
							else if (menu == 5)		// 전체 검색
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
							if (menu == 1)			// 이름 검색
								clientList_search(&cList, 1);
							else if (menu == 2)		// 학번 검색
								clientList_search(&cList, 2);
							else if (menu == 3)		// 전체 검색
								clientList_search(&cList, 3);
							else if (menu == 4)		// 전체 리스트
								clientList_search(&cList, 4);
							else if (menu == 5)		// 이전 메뉴
								break;

							menu = 0;
						}
					}
					else if (menu == ADMIN_LOGOUT)
						break;
					else if (menu == ADMIN_QUIT)
					{
						// 루프 두개를 한번에 어떻게 빠져나오지..
						puts("프로그램을 종료합니다.");
						break;
					}
				}
				
			}
			else if (result == 1)	// 일반 로그인 성공
			{
				while (1)
				{
					print_user_menu();
					scanf("%d", &menu);
					getchar();
					
					if (menu == 1)		// 도서 검색
					{
						while (1)
						{
							print_user_submenu();
							scanf("%d", &menu);
							getchar();
							
							if (menu == 1)			// 도서명 검색
								bookList_search(&bList, 1);
							else if (menu == 2)		// 출판사 검색
								bookList_search(&bList, 2);
							else if (menu == 3)		// ISBN 검색
								bookList_search(&bList, 3);
							else if (menu == 4)		// 저자명 검색
								bookList_search(&bList, 4);
							else if (menu == 5)		// 전체 검색
								bookList_search(&bList, 5);
							else if (menu == 6)
								break;
						}
					}
					else if (menu == 2) // 내 내여 목록
						bookList_myBorrowList(&bList);
					else if (menu == 3) // 개인정보 수정
						clientList_editMyInfo(&cList);
					else if (menu == 4) // 회원탈퇴
						clientList_leave(&cList);
					else if (menu == 5) // 로그아웃
						break;
					else if (menu == 6) // 프로그램 종료
					{
						// 루프 두개를 한번에 어떻게 빠져나오지..
						puts("프로그램을 종료합니다.");
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
			// 수정되거나 변경이 있는 data는 전부 메모리에 올려뒀다가
			// 프로그램이 종료될 때, 기존 파일은 지우고 한꺼번에
			// 새로 저장합니다.
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