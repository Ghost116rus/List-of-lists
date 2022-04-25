#include "user_interface.h"

int getValue(int condition, const char* string, int k)
{
	while (true)													// ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
	{
		int a;
		std::cin >> a;

		if (std::cin.fail())										// ���� ���������� ���������� ��������� ���������,
		{
			std::cout << "������! ����������, ��������� ����! \n";
			std::cin.clear();										// �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n');							// � ������� �������� ����������� ����� �� �������� ������
			std::cout << string;
		}
		else // ���� �� ������ � ���������� �������, �� ���������� a
		{
			switch (condition)
			{
			case Variable_options:
				if ((a > 0) && (a < k)) {	return a;	}
				std::cout << "�� ������ ������ ����������� ����� ������ " << k << std::endl;
				std::cin.ignore(32767, '\n');						// � ������� �������� ����������� ����� �� �������� ������
				continue;

			case Natural_number:
				if (a > 0) { return a; }

				std::cout << "�� ������ ������ ����������� �����\n";
				std::cin.ignore(32767, '\n');						// � ������� �������� ����������� ����� �� �������� ������
				continue;

			case O_Or_1:												// �� �������

				if ((a == 0) || (a == 1)) { return a; }

				std::cout << "�� ������ ������ ���� 0, ���� 1\n";
				std::cin.ignore(32767, '\n');						// � ������� �������� ����������� ����� �� �������� ������
				continue;

			case Menu_Commands:

				if (((int)a > 0) && ((int)a < k)) { return a; }

				std::cout << "� ���� ����� " << k-1 <<" �������!��������� ���� : ";
				std::cin.ignore(32767, '\n');						// � ������� �������� ����������� ����� �� �������� ������
				continue;

			default:
				return a;
			}

		}

	}
}

void show_menu()
{
	std::cout << "\n  ���������� ������������:\n"
		<< "\t1. ���������� ������ ��������\n"
		<< "\t2. �������� ��������\n"
		<< "\t3. �������� ���������� ������\n"
		<< "\t4. �������� ����\n"
		<< "\t5. ���� � �������� ����\n";

}

void write_author()
{
	std::cout << "������ �������� ������ �.�., ������ 4211\n";
}

int aboutDirection()
{
	std::cout << "\t�� ������ ������ ������ � ������ ��� �������� �����������? 0 - � ������, 1 - � �������� �����������\n\t �������: ";
	int left = getValue(O_Or_1, "\t�� ������ ������ ������ � ������ ��� �������� �����������? 0 - � ������, 1 - � �������� �����������\n \t�������: ", 0);

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
	std::cout << "\t������� �������, �� �������� �� ����� �������������: ";
	int find_data = getValue(Natural_number, "\t������� �������, �� �������� �� ����� �������������: ", 0);
	current = my_search(list, find_data, left);

	if (current)
	{
		std::cout << "\t�� ������ �������� ������ �� ��������� �������� ��� �����? 0 - ��, 1 - �����\n\t�������: ";
		int before = getValue(O_Or_1, "\t�� ������ �������� ������ �� ��������� �������� ��� �����? 0 - ��, 1 - �����\n\t�������: ", 0);

		My_List::add(current, temp_data, before);
	}
	else
	{
		std::cout << "\t���������� ����������, �.� ������� � ������ ������� �� ������\n";
	}


}

void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left)
{
	std::cout << "\t������� ������, ������� ������ �� �������: ";
	find_data = getValue(1, "\t������� ������: ", 0);

	current = my_search(list, find_data, left);

	if (current)
	{
		My_List::remove(current);
	}
	else
	{
		std::cout << "\t�������� ����������, �.� ������� � ������ ������� �� ������\n";
	}

}

void menu(My_List::Node* list)
{
	int user_choice = 0;

	show_menu();

	while (user_choice != To_main_menu)
	{
		std::cout << "\n\t�������� �������: ";
		user_choice = getValue(Menu_Commands, "\t�������� �������: ", Menu_Commands);

		int temp_data = -1;
		int left = -1;
		My_List::Node* current = nullptr;

		switch (user_choice)
		{
		case Add_new_element:

			std::cout << "\t�������, ������ ������� ������ ��������: ";
			temp_data = getValue(1, "\t������� ������: ", 0);

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
				std::cout << "\t������ ������!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Show_list:


			if (My_List::empty(list))
			{
				std::cout << "\t������ ������!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "\t������ ������ � �������� �����������", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "\t������ ������ � ������ �����������", [](My_List::Node* current)
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
	std::cout << "  ���������� ���������:\n"
		<< "1. ������������� ������ �������\n"
		<< "2. ���������� ������ ������\n"
		<< "3. �������� ������\n"
		<< "4. ������� ������ ��� ������\n"
		<< "5. �������� ���������� ���� �������\n"
		<< "6. �������� ���������� ������ ������� � ������� �� �������\n"
		<< "7. �������� ������� ����\n"
		<< "8. ������� ������ ���������\n"
		<< "\n9. ���������� ������\n\n";
}

void show_number_of_lists(My_List::MyList* list_of_lists)
{
	My_List::MyList* current = list_of_lists->pNext;
	int number = 1;

	if (!current)
	{
		std::cout << "������ ������� ����\n";
	}

	while (current)
	{
		std::cout << "C�����: " << current->name << "\t";

		if (My_List::empty(current->data))
		{
			std::cout << "������ ����!\n";
		}
		else
		{
			std::cout << "������ ������: " << current->data->pNext->data << "\n";
		}
		current = current->pNext;
	}
}

void init(My_List::MyList*& list_of_lists, int& user_choice, bool& complete_init)
{
	while ((!complete_init) && (user_choice != Exit))
	{
		std::cout << "�������� �������: ";
		user_choice = getValue(Menu_Commands, "�������� �������: ", Main_menu_Commands);

		if (user_choice == Init)
		{
			list_of_lists = My_List::createList(); std::cout << "C����� ���������������.\n";
			complete_init = true;
		}

		else if (user_choice != Exit)
		{
			std::cout << "���������� ��������� ��������, �.� ������ �� ���������������\n";
		}
	}
}


My_List::MyList* find(My_List::MyList* list_of_lists)
{
	show_number_of_lists(list_of_lists);
	std::cout << "������� ��� ������, ������� ����� �����: ";
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

		std::cout << "\n�������� �������: ";
		user_choice = getValue(Menu_Commands, "�������� �������: ", Main_menu_Commands);

		switch (user_choice)
		{
		case Add_new_list:

			if (count)
			{
				current = find(list_of_lists);

				if (current)
				{
					std::cout << "�� ��� ����� ��������� ��������? �������: "; user_choice = getValue(O_Or_1, "", Main_menu_Commands);
					if (user_choice) { current = current->pNext; }
				}
				else
				{
					std::cout << "�������� ������� �� ������!\n"; break;
				}
			}
			My_List::addList(current); count++;
			std::cout << "���������� ��������� �������!\n";

			break;

		case Delete_list:

			if (count)
			{
				current = find(list_of_lists);
				My_List::removeList(current); count--;
			}
			else
			{
				std::cout << "������ ������!\n";
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
					std::cout << "����� ������� ����, ������� 7\n";
				}
				else { std::cout << "�������� ������ �� ������!\n"; }

			}
			else
			{
				std::cout << "������ ������!\n";
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

	std::cout << "���������� ������\n";
}