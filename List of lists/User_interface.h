#pragma once
#include <iostream>
#include "MyList.h"


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

	Variable_options = 13,
	Natural_number = 14,
	O_Or_1 = 15,
	Menu_Commands = 6,
	Main_menu_Commands = 10
};

///* Функция со мной ещё со 2 - ого семестра, когда об объектной обработки исключений ничего не было известно  */
//int getValue(int condition, const char* string, int k);
//
///*  Вывод главного меню  */
//void show_main_menu();
//
///*  Вывод информации об авторе  */
//void write_author();
//
//int aboutDirection();
//
//void add_element(My_List::Node* list, My_List::Node* current, int& temp_data, int& left);
//
//void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left);
//

/*  основная программная реализация интерфейса  */
void main_menu(My_List::MyList* list_of_lists);