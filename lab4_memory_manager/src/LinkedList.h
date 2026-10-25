#pragma once

template<typename T>
class DLinkedList
{
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
	};
	Node* head;

public:
	DLinkedList();

	void insert(Node* prevNode, Node* newNode);
	void remove(Node* removeNode);
};

template<typename T>
DLinkedList<T>::DLinkedList()
{
}

template<typename T>
void DLinkedList<T>::insert(Node* prevNode, Node* newNode)
{
	if (!prevNode)
	{
		if (head)
		{
			newNode->next = head;
			newNode->next->prev = newNode;
		}
		else
		{
			newNode->next = nullptr;
		}
		head = newNode;
		head->prev = nullptr;
	}
	else 
	{
		// last node
		if (!prevNode->next)
		{
			prevNode->next = newNode;
			newNode->next = nullptr;
		}
		else
		{
			newNode->next = prevNode->next;
			newNode->next->prev = newNode;
			prevNode->next = newNode;
			newNode->prev = prevNode;
		}
	}
}

template<typename T>
void DLinkedList<T>::remove(Node* removeNode)
{
	if (!removeNode->prev)
	{
		if (!removeNode->next)
		{
			head = nullptr;
		}
		else
		{
			head = removeNode->next;
			head->prev = nullptr;
		}
	}
	else
	{
		// last node
		if (!removeNode->next)
		{
			removeNode->prev->next = nullptr;
		}
		else
		{
			removeNode->prev->next = removeNode->next;
			removeNode->next->prev = removeNode->prev;
		}
	}
}

template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next;
	};
	Node* head;

public:
	LinkedList();

	void insert(Node* prevNode, Node* newNode);
	void remove(Node* prevNode, Node* removeNode);
};

template<typename T>
LinkedList<T>::LinkedList() {}

template<typename T>
void LinkedList<T>::insert(Node* prevNode, Node* newNode)
{
	if (!prevNode) {
		if (!head) {
			newNode->next = head;
		}
		else {
			newNode->next = nullptr;
		}
		head = newNode;
	}
	else {
		if (!prevNode->next) {
			prevNode->next = newNode;
			newNode->next = nullptr;
		}
		else {
			prevNode->next = newNode->next;
			prevNode->next = newNode;
		}
	}
}

template<typename T>
void LinkedList<T>::remove(Node* prevNode, Node* removeNode)
{
	if (!prevNode)
	{
		if (!removeNode->next)
		{
			head = nullptr;
		}
		else
		{
			head = removeNode->next;
		}
	}
	else
	{
		prevNode->next = removeNode->next;
	}
}