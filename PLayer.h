#pragma once
#include <iostream>
#include "mylib.h"
#include "stack.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Disk.h"

using namespace std;

struct Player {
	string name;
	int disks;
	int moves;
	double time;	
	int score;

	/*Player(const string& n, int d, int m, double t, int s) : name(n), disks(d), moves(m), time(t), score(s) {}*/
};

struct Node {
	Player data;
	Node* prev;
	Node* next;
};

struct DoubleListPlayer {
	Node* head = NULL;
	Node* tail = NULL;
	int count=0;

	Node* createNodeDoubly(Player player) {
		Node* p = new Node;
		p->next = p->prev = NULL;
		p->data = player;
		return p;
	}

	void addPlayer(Player player) {
		Node* p = createNodeDoubly(player);
		if (head == NULL) {
			head = tail = p;
		}
		else {
			tail->next = p;
			p->prev = tail;
			tail = p;
		}
		count++;
	}

	void loadPlayer(string tenFile) {
		ifstream file(tenFile);
		if (!file.is_open()) {
			return;
		}
		string line;
		int rank = 1;
		while (getline(file, line)) { 
			stringstream ss(line);
			string name;
			double time;
			int moves, score;
			int disks;

			getline(ss, name, ',');
			ss >> disks; ss.ignore(); 
			ss >> moves; ss.ignore(); 
			ss >> time; ss.ignore(); 
			ss >> score;

			Player player;
			player.name = name;
			player.disks = disks;
			player.moves = moves;
			player.time = time;
			player.score = score;

			addPlayer(player);

		}
		file.close();
	}

	void savePlayer(string tenFile) { //ghi de len file
		ofstream file(tenFile);
		if (file.is_open()) {
			Node* p = head;
			while (p != NULL) {
				file << p->data.name << "," << p->data.disks << "," << p->data.moves << "," << p->data.time << "," << p->data.score << endl;
				p = p->next;
			}
			file.close();
		}
	}

	//sap xep theo thu tu giam dan, UU TIEN SO DIA, NEU SO DIA BANG NHAU THI UU TIEN SO DIEM
	void sortPlayer() {
		Node* p = head;
		while (p->next != NULL) {
			Node* q = p->next;
			while (q != NULL) {
				if (p->data.disks < q->data.disks) {
					Player temp = p->data;
					p->data = q->data;
					q->data = temp;
				}
				else if (p->data.disks == q->data.disks) {
					if (p->data.score < q->data.score) {
						Player temp = p->data;
						p->data = q->data;
						q->data = temp;
					}
				}
				q = q->next;
			}
			p = p->next;
		}
	}

	
	bool linearSearch(string name, MyWindows console) {
		Node* p = head;
		bool check = false;
		while (p != NULL) {
			if (p->data.name == name) {
				check = true;
				console.Write("Nguoi choi: " + p->data.name + " - " + to_string(p->data.disks) + " dia - " + to_string(p->data.moves) 
					+ " buoc di chuyen - " + to_string(p->data.time) + " giay - " + to_string(p->data.score) + " diem", 2, 5, 1, 15);
			}
			p = p->next;
		}
		if (check == false) {

			return false;
		}
		else {
			return true;
		}
	}

	int size() {
		return count;
	}

	
};


