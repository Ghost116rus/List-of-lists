// List of lists.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MyList.h"
#include "User_interface.h"

int main()
{
    setlocale(LC_ALL, "RU");

    My_List::MyList* list_of_lists = nullptr;
    main_menu(list_of_lists);

}

