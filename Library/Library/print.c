#include "print.h"


void print_init_menu(void)
{
	puts(">> ������ ���� <<");
	puts("1. ȸ������    2. �α���    3. ���α׷� ����");
}

void print_user_menu(void)
{
	puts(">> ȸ���޴� <<");
	puts("1. ���� �˻�         2. �� �뿩 ���");
	puts("3. �������� ����     4. ȸ�� Ż��");
	puts("5. �α׾ƿ�          6. ���α׷� ����");
	puts("");
}

void print_admin_menu(void)
{
	puts(">> ������ �޴� <<");
	puts("1. ���� ���         2. ���� ����");
	puts("3. ���� �뿩         4. ���� �ݳ�");
	puts("5. ���� �˻�         6. ȸ�� ���");
	puts("7. �α׾ƿ�          8. ���α׷� ����");
	puts("");
}

void print_login_error(void)
{
	puts("ȸ�� ������ �ٽ� Ȯ���ϼ���.");
}

void print_menu_error(void)
{
	puts("�߸��� �޴� �����Դϴ�.");
}

void print_quit(void)
{
	puts("���α׷��� ����˴ϴ�.");
}

void print_user_submenu(void)
{
	puts(">> ���� �˻� <<");
	puts("1. ������ �˻�         2. ���ǻ� �˻�");
	puts("3. ISBN �˻�           4. ���ڸ� �˻�");
	puts("5. ��ü �˻�           6. ���� �޴�");
	puts("");
}

void print_admin_submenu(void)
{
	puts(">> ȸ�� ��� <<");
	puts("1. �̸� �˻�         2. �й� �˻�");
	puts("3. ��ü �˻�           4. ��ü ����");
	puts("5. ���� �޴�");
	puts("");
}