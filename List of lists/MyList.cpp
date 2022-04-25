#include "MyList.h"

using namespace My_List;




MyList* My_List::createList()
{
	MyList* temp = new MyList;
	temp->pNext = nullptr;
	temp->data = nullptr;


	return temp;
}

void My_List::addList(MyList* current)
{
	MyList* list = new MyList();
	list->pNext = current->pNext;
	list->data = create();
	
	std::cout << "Введите имя нового списка: "; std::cin >> list->name;

	current->pNext = list;
}

void My_List::removeList(MyList* previous)
{
	MyList* list = previous->pNext;
	previous->pNext = previous->pNext->pNext;
	clean_memory_nodes(list->data);
	delete list;

	std::cout << "Удаление списка выполнено успешно\n";
}

void My_List::show_all_lists(MyList* head, const std::function<Node* (Node*)>& fcn)
{
	head = head->pNext;
	while (head)
	{
		std::cout << std::endl;
		std::cout <<"Cписок: " <<  head->name  << "\n";
		show(head->data, "", fcn);
		head = head->pNext;
	}

}

void My_List::clean_memory(MyList* head)
{
	MyList* current;

	while (head->pNext)
	{
		current = head->pNext->pNext;
		clean_memory_nodes(head->pNext->data);
		delete head->pNext;

		head->pNext = current;
	}
	delete head;
}


Node* My_List::create()
{
	Node* Temp = new Node();
	Temp->pNext = Temp;
	Temp->pPrevious = Temp;

	return Temp;	
}

bool My_List::empty(Node* head)
{
	return (head->pNext == head);
}

void My_List::show(Node* pHead, std::string message, const std::function<Node* (Node*)>& fcn)
{
	Node* start = fcn(pHead);
	int number = 1;

	if (start == pHead)
	{
		std::cout << "\tСписок пустой!\n";
	}

	while (start != pHead)
	{
		std::cout << "\t" << number++ << "-ый элемент " << message + " " << start->data << std::endl;
		start = fcn(start);
	} 
}

Node* My_List::find(Node* pHead, int find_data, const std::function<Node* (Node*)>& fcn)
{
	Node* current = fcn(pHead);
	int number = 0;
	while (current != pHead)
	{
		if (current->data == find_data)
		{
			std::cout << "\t Найден за " << number << " итераций\n";
			return current;
		}
		current = fcn(current);
		number++;
	} 

	std::cout << "\t Не удалось найти элемент с заданными данными\n";
	return nullptr;
}

void My_List::add(Node* current, int data, bool before)
{
	if (!(before))
	{
		current = current->pPrevious;
	}

	Node* temp = new Node();
	temp->data = data;

	temp->pNext = current->pNext;
	temp->pPrevious = current;
	current->pNext->pPrevious = temp;
	current->pNext = temp;

	std::cout << "\tДобавление выполено успешно\n";
}

void My_List::remove(Node* current)
{
	if (empty(current)) { return; }

	current->pNext->pPrevious = current->pPrevious;
	current->pPrevious->pNext = current->pNext;

	delete current;

	std::cout << "\tУдаление произошло успешно\n";
}

void My_List::clean_memory_nodes(Node* list)
{
	Node* current = list->pNext;

	while (current != current->pNext)
	{
		list = current->pNext;
		remove(current);
		current = list;
	}
	delete list;
}
