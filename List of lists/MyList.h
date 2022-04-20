#pragma once
#include <iostream>
#include <functional>



namespace My_List
{
	struct Node
	{
		int data = 0;
		Node* pNext = this;
		Node* pPrevious = this;
	};

	struct MyList
	{
		MyList* pNext;
		Node* data;
	};


	MyList* createList();


	void addList(MyList* current);

	void removeList(MyList* current);

	void show_all_lists(MyList* head, const std::function<Node* (Node*)>& fcn);

	void clean_memory(MyList* head);


	/// <summary>
	/// ������� �������� ������ ������
	/// </summary>
	/// <returns>���������� ������������ ������� ������ ������</returns>
	Node* create();

	/// <summary>
	/// �������� ����������� ������� ������
	/// </summary>
	/// <param name="head">�������� ��������� �� ������������ �������</param>
	/// <returns>���������� ������ ��� ���� � ����������� �� ����������</returns>
	bool empty(Node* head);

	/// <summary>
	/// ����� ������ �� ����� ����������� ������
	/// </summary>
	/// <param name="pHead">�������� ��������� �� ������</param>
	/// <param name="message">�������� ���������</param>
	/// <param name="fcn">�������� ������-�������, ���������� �� ������ ������ (������/��������)</param>
	void show(Node* pHead, std::string message, const std::function<Node* (Node*)>& fcn);

	/// <summary>
	/// ����� ������
	/// </summary>
	/// <param name="pHead">�������� ��������� �� ������</param>
	/// <param name="find_data">������� ������</param>
	/// <param name="fcn">�������� ������-�������, ���������� �� ������ ������ (������/��������)</param>
	/// <returns>���������� ��������� �� ������� ������, � ������� �������� ������� ������</returns>
	Node* find(Node* pHead, int find_data, const std::function<Node* (Node*)>& fcn);

	/// <summary>
	/// ����� ���������� ������ ��������
	/// </summary>
	/// <param name="current">�������� ��������� �� ������� ������ ��/����� �������� ����� �������� ������</param>
	/// <param name="data">����������� ������</param>
	/// <param name="before">�������� �� ������� ��/�����</param>
	void add(Node* current, int data, bool before);

	/// <summary>
	/// ������� ���������� ������� ������
	/// </summary>
	/// <param name="current">���������� ������� ������</param>
	void remove(Node* current);

	/// <summary>
	/// ������� ������, ��� ����������
	/// </summary>
	/// <param name="list">��������� �� ��� ������</param>
	void clean_memory_nodes(Node* list);
}