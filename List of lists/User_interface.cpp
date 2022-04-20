#include "user_interface.h"


int getValue(int condition, const char* string)
{
	while (true)													// цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		int a;
		std::cin >> a;

		if (std::cin.fail())										// если предыдущее извлечение оказалось неудачным,
		{
			std::cout << "Ошибка! Пожалуйста, повторите ввод! \n";
			std::cin.clear();										// то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n');							// и удаляем значения предыдущего ввода из входного буфера
			std::cout << string;
		}
		else // если всё хорошо и выполнятся условия, то возвращаем a
		{
			switch (condition)
			{
			case Natural_number:
				if (a > 0) { return a; }

				std::cout << "Вы должны ввести натуральное число\n";
				std::cin.ignore(32767, '\n');						// и удаляем значения предыдущего ввода из входного буфера
				continue;

			case O_Or_1:												// На будущее

				if ((a == 0) || (a == 1)) { return a; }

				std::cout << "Вы должны ввести либо 0, либо 1\n";
				std::cin.ignore(32767, '\n');						// и удаляем значения предыдущего ввода из входного буфера
				continue;

			case Main_menu_Commands:

				if (((int)a > 0) && ((int)a < 9)) { return a; }

				std::cout << "У меню всего 7 функций! Повторите ввод: ";
				std::cin.ignore(32767, '\n');						// и удаляем значения предыдущего ввода из входного буфера
				continue;

			default:
				return a;
			}

		}

	}
}



void show_menu()
{
	std::cout << "\n  Функционал подпрограммы:\n"
		<< "\t1. Добавление нового элемента\n"
		<< "\t2. Удаление элемента\n"
		<< "\t3. Показать содержимое списка\n"
		<< "\t4. Показать меню\n"
		<< "\t5. Уйти в основное меню\n";

}

void write_author()
{
	std::cout << "Работу выполнил Калеев Д.А., группа 4211\n";
}

int aboutDirection()
{
	std::cout << "Вы хотите искать данные в прямом или обратном направлении? 0 - в прямом, 1 - в обратном направлении\nВведите: ";
	int left = getValue(O_Or_1, "Вы хотите искать данные в прямом или обратном направлении? 0 - в прямом, 1 - в обратном направлении\n Введите: ");

	return left;
}

My_List::Node* my_search(My_List::Node* list, int& find_data, int& left)
{
	My_List::Node* current;

	left = aboutDirection();

	if (left)
	{
		current = My_List::find(list, find_data, [](My_List::Node* current)
			{
				return current->pPrevious;
			}
		);
	}
	else
	{
		current = My_List::find(list, find_data, [](My_List::Node* current)
			{
				return current->pNext;
			}
		);
	}
	
	return current;
}

void add_element(My_List::Node* list, My_List::Node* current, int& temp_data, int& left)
{
	std::cout << "Введите элемент, от которого мы будем отталкиваться: ";
	int find_data = getValue(Natural_number, "Введите элемент, от которого мы будем отталкиваться: ");
	current = my_search(list, find_data, left);

	if (current)
	{
		std::cout << "Вы хотите вставить данные до заданного элемента или после? 0 - до, 1 - после\nВведите: ";
		int before = getValue(O_Or_1, "Вы хотите вставить данные до заданного элемента или после? 0 - до, 1 - после\nВведите: ");

		My_List::add(current, temp_data, before);
	}
	else
	{
		std::cout << "Добавление невозможно, т.к элемент с такими данными не найден\n";
	}


}

void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left)
{
	std::cout << "Введите данные, которые хотели бы удалить: ";
	find_data = getValue(1, "Введите данные: ");

	current = my_search(list, find_data, left);

	if (current)
	{
		My_List::remove(current);
	}
	else
	{
		std::cout << "Удаление невозможно, т.к элемент с такими данными не найден\n";
	}

}

void menu(My_List::Node* list)
{
	int user_choice = 0;


	show_menu();

	while (user_choice != To_main_menu)
	{
		int temp_data = -1;
		int left = -1;
		My_List::Node* current = nullptr;

		switch (user_choice)
		{
		case Add_new_element:

			std::cout << "Введите, данные которые хотите добавить: ";
			temp_data = getValue(1, "Введите данные: ");

			if (My_List::empty(list))
			{
				My_List::add(list, temp_data, 0);
			}
			else
			{
				add_element(list, current, temp_data, left);
			}
			break;

		case Delete_element:

			if (My_List::empty(list))
			{
				std::cout << "Список пустой!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Show_list:


			if (My_List::empty(list))
			{
				std::cout << "Список пустой!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "Проход списка в обратном направлении", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "Проход списка в прямом направлении", [](My_List::Node* current)
					{
						return current->pNext;
					}
				);
			}
			break;

		case Show_menu:

			std::cout << "\n\n";
			show_menu();
			break;

		default:
			break;
		}
		std::cout << "\nВыберите команду: ";
		user_choice = getValue(Menu_Commands, "Выберите команду: ");
	}
}






void show_main_menu()
{
	std::cout << "  Функционал программы:\n"
		<< "1. Инициализация списка списков\n"
		<< "2. Добавление нового списка\n"
		<< "3. Удаление списка\n"
		<< "4. Выбрать список для работы\n"
		<< "5. Показать содержимое всех списков\n"
		<< "6. Показать главное меню\n"
		<< "7. Вывести автора программы\n"
		<< "\n8. Завершение работы\n\n";
}

void show_number_of_lists(My_List::MyList* list_of_lists)
{
	My_List::MyList* current = list_of_lists->pNext;
	int number = 1;

	if (!current)
	{
		std::cout << "Список списков пуст\n";
	}

	while (current)
	{
		std::cout << "Список №" << number++ << "\t";

		if (My_List::empty(current->data))
		{
			std::cout << "Список пуст!\n";
		}
		else
		{
			std::cout << "Первые данные: " << current->data->pNext->data << "\n";
		}
		current = current->pNext;
	}
}

void init(My_List::MyList* list_of_lists, int& user_choice, bool& complete_init)
{
	while ((!complete_init) && (user_choice != Exit))
	{
		std::cout << "Выберите команду: ";
		user_choice = getValue(Menu_Commands, "Выберите команду: ");

		if (user_choice == Init)
		{
			list_of_lists = My_List::createList(); std::cout << "Cписок инициализирован.\n";
			complete_init = true;
		}

		else if (user_choice != Exit)
		{
			std::cout << "Невозможно выполнить операцию, т.к список не инициализирован\n";
		}
	}
}


void main_menu(My_List::MyList* list_of_lists)
{
	int user_choice = 0;
	bool complete_init = false;
	int count = 0;

	show_main_menu();

	init(list_of_lists, user_choice, complete_init);

	while (user_choice != Exit)
	{
		int temp_data = -1;
		int left = -1;
		My_List::MyList* current = nullptr;

		switch (user_choice)
		{
		case Add_new_list:

			current = list_of_lists;

			if (count)
			{
				show_number_of_lists(list_of_lists);
				std::cout << "На какую позицию нужно поставить список: (если будет введено число, превышающее количество списоков, новый список будет добавлен в конец\n";
				temp_data = getValue(1, "Введите данные: ");

				current = list_of_lists;

				for (size_t i = 0; i < count; i++)
				{
					if (i == temp_data - 1)
					{
						break;
					}
					current = current->pNext;
				}
			}

			My_List::addList(current); count++;
			break;

		case Delete_list:

			if (My_List::empty(list))
			{
				std::cout << "Список пустой!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Choise_list:

			if (My_List::empty(list))
			{
				std::cout << "Список пустой!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;


		case Show_all_lists:


			if (My_List::empty(list))
			{
				std::cout << "Список пустой!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "Проход списка в обратном направлении", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "Проход списка в прямом направлении", [](My_List::Node* current)
					{
						return current->pNext;
					}
				);
			}
			break;
			
		case Show_number_of_lists:

			show_number_of_lists(list_of_lists);
			break;

		case Show_main_menu:

			std::cout << "\n\n";
			show_main_menu();
			break;

		case Write_author:

			write_author();
			break;

		default:
			break;
		}
		std::cout << "\nВыберите команду: ";
		user_choice = getValue(Menu_Commands, "Выберите команду: ");
	}
	if (complete_init)
	{
		My_List::clean_memory(list_of_lists);
	}

	std::cout << "Завершение работы\n";
}