#pragma once
#include <iostream>
#include "MyList.h"

void show_main_menu()
{
	std::cout << "  ���������� ���������:\n"
		<< "1. ������������� ������ �������\n"
		<< "2. ���������� ������ ������\n"
		<< "3. �������� ������\n"
		<< "4. �������� ���������� ���������� ������\n"
		<< "5. �������� ���������� ���� �������\n"
		<< "6. �������� ������� ����\n"
		<< "7. ������� ������ ���������\n"
		<< "\n8. ���������� ������\n\n";
}

enum Options
{
	Init = 1,
	Add_new_list = 2,
	Delete_list = 3,
	Choise_list = 4,
	Show_all_lists = 5,
	Show_number_of_lists = 6,
	Show_main_menu = 7,
	Write_author = 8,
	Exit = 9,

	Add_new_element = 1,
	Delete_element = 2,
	Show_list = 3,
	Show_menu = 4,
	To_main_menu = 5,

	Natural_number = 14,
	O_Or_1 = 15,
	Menu_Commands = 16,
	Main_menu_Commands = 17
};

/* ������� �� ���� ��� �� 2 - ��� ��������, ����� �� ��������� ��������� ���������� ������ �� ���� ��������  */
int getValue(int condition, const char* string);

/*  ����� �������� ����  */
void show_main_menu();

/*  ����� ���������� �� ������  */
void write_author();

int aboutDirection();

void add_element(My_List::Node* list, My_List::Node* current, int& temp_data, int& left);

void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left);


/*  �������� ����������� ���������� ����������  */
void main_menu(My_List::MyList* list);