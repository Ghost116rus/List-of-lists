#include "user_interface.h"

int getValue(int condition, const char* string, int k)
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
			case Variable_options:
				if ((a > 0) && (a < k)) {	return a;	}
				std::cout << "Вы должны ввести натуральное число меньше " << k << std::endl;
				std::cin.ignore(32767, '\n');						// и удаляем значения предыдущего ввода из входного буфера
				continue;

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

			case Menu_Commands:

				if (((int)a > 0) && ((int)a < k)) { return a; }

				std::cout << "У меню всего " << k-1 <<" функций!Повторите ввод : ";
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
	std::cout << "\tВы хотите искать данные в прямом или обратном направлении? 0 - в прямом, 1 - в обратном направлении\n\t Введите: ";
	int left = getValue(O_Or_1, "\tВы хотите искать данные в прямом или обратном направлении? 0 - в прямом, 1 - в обратном направлении\n \tВведите: ", 0);

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
	std::cout << "\tВведите элемент, от которого мы будем отталкиваться: ";
	int find_data = getValue(Natural_number, "\tВведите элемент, от которого мы будем отталкиваться: ", 0);
	current = my_search(list, find_data, left);

	if (current)
	{
		std::cout << "\tВы хотите вставить данные до заданного элемента или после? 0 - до, 1 - после\n\tВведите: ";
		int before = getValue(O_Or_1, "\tВы хотите вставить данные до заданного элемента или после? 0 - до, 1 - после\n\tВведите: ", 0);

		My_List::add(current, temp_data, before);
	}
	else
	{
		std::cout << "\tДобавление невозможно, т.к элемент с такими данными не найден\n";
	}


}

void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left)
{
	std::cout << "\tВведите данные, которые хотели бы удалить: ";
	find_data = getValue(1, "\tВведите данные: ", 0);

	current = my_search(list, find_data, left);

	if (current)
	{
		My_List::remove(current);
	}
	else
	{
		std::cout << "\tУдаление невозможно, т.к элемент с такими данными не найден\n";
	}

}

void menu(My_List::Node* list)
{
	int user_choice = 0;

	show_menu();

	while (user_choice != To_main_menu)
	{
		std::cout << "\n\tВыберите команду: ";
		user_choice = getValue(Menu_Commands, "\tВыберите команду: ", Menu_Commands);

		int temp_data = -1;
		int left = -1;
		My_List::Node* current = nullptr;

		switch (user_choice)
		{
		case Add_new_element:

			std::cout << "\tВведите, данные которые хотите добавить: ";
			temp_data = getValue(1, "\tВведите данные: ", 0);

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
				std::cout << "\tСписок пустой!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Show_list:


			if (My_List::empty(list))
			{
				std::cout << "\tСписок пустой!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "\tПроход списка в обратном направлении", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "\tПроход списка в прямом направлении", [](My_List::Node* current)
					{
						return current->pNext;
					}
				);
			}
			break;

		case Show_menu:
			show_menu();
			std::cout << "\n\n";
			break;

		default:
			break;
		}
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
		<< "6. Показать содержимое списка списков с первыми их данными\n"
		<< "7. Показать главное меню\n"
		<< "8. Вывести автора программы\n"
		<< "\n9. Завершение работы\n\n";
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
		std::cout << "Cписок: " << current->name << "\t";

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

void init(My_List::MyList*& list_of_lists, int& user_choice, bool& complete_init)
{
	while ((!complete_init) && (user_choice != Exit))
	{
		std::cout << "Выберите команду: ";
		user_choice = getValue(Menu_Commands, "Выберите команду: ", Main_menu_Commands);

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


My_List::MyList* find(My_List::MyList* list_of_lists)
{
	show_number_of_lists(list_of_lists);
	std::cout << "Введите имя списка, который нужно найти: ";
	std::string name; std::cin >> name;

	My_List::MyList* previous = list_of_lists;

	while (previous)
	{
		if (previous->pNext)
		{
			if (previous->pNext->name == name)
			{
				return previous;
			}
		}
		previous = previous->pNext;
	}

	return nullptr;
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
		My_List::MyList* current = list_of_lists;

		std::cout << "\nВыберите команду: ";
		user_choice = getValue(Menu_Commands, "Выберите команду: ", Main_menu_Commands);

		switch (user_choice)
		{
		case Add_new_list:

			if (count)
			{
				current = find(list_of_lists);

				if (current)
				{
					std::cout << "До или после заданного элемента? Введите: "; user_choice = getValue(O_Or_1, "", Main_menu_Commands);
					if (user_choice) { current = current->pNext; }
				}
				else
				{
					std::cout << "Заданный элемент не найден!\n"; break;
				}
			}
			My_List::addList(current); count++;
			std::cout << "Добавление выполнено успешно!\n";

			break;

		case Delete_list:

			if (count)
			{
				current = find(list_of_lists);
				My_List::removeList(current); count--;
			}
			else
			{
				std::cout << "Список пустой!\n";
			}

			break;

		case Choise_list:

			if (count)
			{
				current = find(list_of_lists);

				if (current)
				{
					current = current->pNext;
					menu(current->data);
					std::cout << "Чтобы вывести меню, введите 7\n";
				}
				else { std::cout << "Заданный список не найден!\n"; }

			}
			else
			{
				std::cout << "Список пустой!\n";
			}



			break;


		case Show_all_lists:

			left = aboutDirection();

			if (left)
			{
				My_List::show_all_lists(list_of_lists, [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show_all_lists(list_of_lists, [](My_List::Node* current)
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
	}
	if (complete_init)
	{
		My_List::clean_memory(list_of_lists);
	}

	std::cout << "Завершение работы\n";
}