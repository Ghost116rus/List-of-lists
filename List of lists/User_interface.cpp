#include "user_interface.h"


int getValue(int condition, const char* string)
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

			case Main_menu_Commands:

				if (((int)a > 0) && ((int)a < 9)) { return a; }

				std::cout << "� ���� ����� 7 �������! ��������� ����: ";
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
	std::cout << "�� ������ ������ ������ � ������ ��� �������� �����������? 0 - � ������, 1 - � �������� �����������\n�������: ";
	int left = getValue(O_Or_1, "�� ������ ������ ������ � ������ ��� �������� �����������? 0 - � ������, 1 - � �������� �����������\n �������: ");

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
	std::cout << "������� �������, �� �������� �� ����� �������������: ";
	int find_data = getValue(Natural_number, "������� �������, �� �������� �� ����� �������������: ");
	current = my_search(list, find_data, left);

	if (current)
	{
		std::cout << "�� ������ �������� ������ �� ��������� �������� ��� �����? 0 - ��, 1 - �����\n�������: ";
		int before = getValue(O_Or_1, "�� ������ �������� ������ �� ��������� �������� ��� �����? 0 - ��, 1 - �����\n�������: ");

		My_List::add(current, temp_data, before);
	}
	else
	{
		std::cout << "���������� ����������, �.� ������� � ������ ������� �� ������\n";
	}


}

void delete_element(My_List::Node* list, My_List::Node* current, int& find_data, int& left)
{
	std::cout << "������� ������, ������� ������ �� �������: ";
	find_data = getValue(1, "������� ������: ");

	current = my_search(list, find_data, left);

	if (current)
	{
		My_List::remove(current);
	}
	else
	{
		std::cout << "�������� ����������, �.� ������� � ������ ������� �� ������\n";
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

			std::cout << "�������, ������ ������� ������ ��������: ";
			temp_data = getValue(1, "������� ������: ");

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
				std::cout << "������ ������!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Show_list:


			if (My_List::empty(list))
			{
				std::cout << "������ ������!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "������ ������ � �������� �����������", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "������ ������ � ������ �����������", [](My_List::Node* current)
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
		std::cout << "\n�������� �������: ";
		user_choice = getValue(Menu_Commands, "�������� �������: ");
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
		<< "6. �������� ������� ����\n"
		<< "7. ������� ������ ���������\n"
		<< "\n8. ���������� ������\n\n";
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
		std::cout << "������ �" << number++ << "\t";

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

void init(My_List::MyList* list_of_lists, int& user_choice, bool& complete_init)
{
	while ((!complete_init) && (user_choice != Exit))
	{
		std::cout << "�������� �������: ";
		user_choice = getValue(Menu_Commands, "�������� �������: ");

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
				std::cout << "�� ����� ������� ����� ��������� ������: (���� ����� ������� �����, ����������� ���������� ��������, ����� ������ ����� �������� � �����\n";
				temp_data = getValue(1, "������� ������: ");

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
				std::cout << "������ ������!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;

		case Choise_list:

			if (My_List::empty(list))
			{
				std::cout << "������ ������!\n";
			}
			else
			{
				delete_element(list, current, temp_data, left);
			}
			break;


		case Show_all_lists:


			if (My_List::empty(list))
			{
				std::cout << "������ ������!\n"; break;
			}

			left = aboutDirection();

			if (left)
			{
				My_List::show(list, "������ ������ � �������� �����������", [](My_List::Node* current)
					{
						return current->pPrevious;
					}
				);
			}
			else
			{
				My_List::show(list, "������ ������ � ������ �����������", [](My_List::Node* current)
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
		std::cout << "\n�������� �������: ";
		user_choice = getValue(Menu_Commands, "�������� �������: ");
	}
	if (complete_init)
	{
		My_List::clean_memory(list_of_lists);
	}

	std::cout << "���������� ������\n";
}