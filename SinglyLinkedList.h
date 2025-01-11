#pragma once
#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

struct SinglyNode
{
	int data;
	SinglyNode* next;
};

struct SinglyList {
	SinglyNode* head;
	SinglyNode* tail;

	void initSinglyList() { 
		head = tail = NULL;
	}

	SinglyNode* createNodeSingly(int value) { 
		SinglyNode* p = new SinglyNode;
		p->next = NULL;
		p->data = value;
		return p;
	}

	int getValue(int index) { 
		SinglyNode* p = head;
		int i = 0;
		while (p != NULL && i < index) { 
			p = p->next;
			i++;
		}
		if (p != NULL)
			return p->data;
		return -1;
	}

	int getSize() {
		SinglyNode* p = head;
		int i = 0;
		while (p != NULL) {
			p = p->next;
			i++;
		}
		return i;
	}

	void add(int value) {
		SinglyNode* p = createNodeSingly(value);
		if (head == NULL)
			head = tail = p;
		else {
			tail->next = p;
			tail = p;
		}
	}

	void print() {
		SinglyNode* p = head;
		while (p != NULL) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	void insert(int value, int index) {
		SinglyNode* p = createNodeSingly(value);
		if (index == 0)
		{
			p->next = head;
			head = p;
		}
		else {
			SinglyNode* q = head;
			int i = 0;

			while (q != NULL && i < index - 1) {
				q = q->next;
				i++;
			}

			if (q != NULL)
			{
				p->next = q->next;
				q->next = p;
				if (q == tail) {
					tail = p;
				}
			}
		}
	}

	void removeAt(int index) { //xóa node ở vị trí index
		if (head != NULL)
		{
			SinglyNode* p = head;
			SinglyNode* q = NULL;
			int i = 0;
			while (p != NULL && i < index)
			{
				q = p;
				p = p->next;
				i++;
			}
			if (p != NULL)
			{
				if (q == NULL)
				{
					head = p->next;
					delete(p);
				}
				else
				{
					q->next = p->next;
					delete(p);
					if (q->next == NULL)
					{
						tail = q;
					}
				}
			}
		}
	}

	void clear() {
		while (head != NULL) {
			SinglyNode* p = head;
			head = p->next;
			p->next = NULL;
			delete(p);
		}
	}


	void removeAll(int value) {
		if (head != NULL)
		{
			SinglyNode* p = head;
			SinglyNode* q = NULL;
			while (p != NULL)
			{
				if (p->data == value)
				{
					if (q == NULL)
					{
						head = p->next;
						delete(p);
						p = head;
					}
					else
					{
						q->next = p->next;
						delete(p);
						p = q->next;
					}
				}
				else
				{
					q = p;
					p = p->next;
				}
			}
		}
	}
};