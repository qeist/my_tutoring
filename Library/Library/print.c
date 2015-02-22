#include "print.h"


void print_init_menu(void)
{
	puts(">> 도서관 서비스 <<");
	puts("1. 회원가입    2. 로그인    3. 프로그램 종료");
}

void print_user_menu(void)
{
	puts(">> 회원메뉴 <<");
	puts("1. 도서 검색         2. 내 대여 목록");
	puts("3. 개인정보 수정     4. 회원 탈퇴");
	puts("5. 로그아웃          6. 프로그램 종료");
	puts("");
}

void print_admin_menu(void)
{
	puts(">> 관리자 메뉴 <<");
	puts("1. 도서 등록         2. 도서 삭제");
	puts("3. 도서 대여         4. 도서 반납");
	puts("5. 도서 검색         6. 회원 목록");
	puts("7. 로그아웃          8. 프로그램 종료");
	puts("");
}

void print_login_error(void)
{
	puts("회원 정보를 다시 확인하세요.");
}

void print_menu_error(void)
{
	puts("잘못된 메뉴 선택입니다.");
}

void print_quit(void)
{
	puts("프로그램이 종료됩니다.");
}

void print_user_submenu(void)
{
	puts(">> 도서 검색 <<");
	puts("1. 도서명 검색         2. 출판사 검색");
	puts("3. ISBN 검색           4. 저자명 검색");
	puts("5. 전체 검색           6. 이전 메뉴");
	puts("");
}

void print_admin_submenu(void)
{
	puts(">> 회원 목록 <<");
	puts("1. 이름 검색         2. 학번 검색");
	puts("3. 전체 검색           4. 전체 보기");
	puts("5. 이전 메뉴");
	puts("");
}