#pragma once
#include <iostream>
#include <string>
#include "mylib.h"
#include "Player.h"
#include "Disk.h"
using namespace std;

struct Stack {
	const int MAX = 100;
	Disk* a;
	int count;
	int top = -1;

	Stack() {
		a = new Disk[MAX];

		count = 0;
	}

	~Stack() {
		delete[] a;
	}

	bool isEmpty() {
		return top == -1;
	}

	bool isFull() {
		return top == MAX - 1;
	}

	int push(Disk value) {
		if (isFull()) {
			return false;
		}
		a[++top] = value;
		count++;
		return true;
	}

	int pop(Disk* value) {
		if (isEmpty()) {
			return false;
		}
		*value = a[top--];
		count--;
		return true;
	}

	int peek() {
		if (isEmpty())
			return 0;
		return a[top].size;
	}

	int getLength() {
		return count;
	}



};






