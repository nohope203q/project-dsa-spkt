#include <iostream>
#include "mylib.h"
#include "stack.h"
#include <conio.h> 
#include <string>
#include <algorithm>
#include <windows.h> 
#include <cstdlib>
#include <fstream> 
#include <time.h>   
#include <sstream>
#include <chrono>
#include "PLayer.h"
#include <random>
#include "Disk.h"

#define HEIGHT 29
#define WIDTH 119

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15
using namespace std;

int current_page = 0;
int items_per_page = 18;
int row = 1;
void tuChoiMagnetic(MyWindows console);
void findNickname(string tenFile);
void printHome();
void choiceBXH(MyWindows console);
void printScoreBoard(string tenFile);
void printPlayGame();
void playerMove(MyWindows console, Stack* stack);
void towerOfHanoi(MyWindows console, Stack* stack, int n, int source, int target, int temp);
void draw(MyWindows console, Stack* stack);
void tuChoi(MyWindows console);
void mayChoi(MyWindows console);
void randomDisks(Stack stacks[], int n);
void XaoTron(MyWindows console);
void showHuongDan(MyWindows console);
void draw(MyWindows console, Stack* stack) // vẽ tháp hà nội
{
	
	int left = 5;
	int w = (WIDTH - 4 * left) / 3;
	int x[3];
	x[0] = left + w / 2;
	x[1] = x[0] + w + left;
	x[2] = x[1] + w + left;
	int lastRow = HEIGHT - 4;

	for (int i = 0; i < w; i++)
	{
		console.Write(L"─", x[0] - (w / 2) + i, lastRow, BLUE, BROWN);
		console.Write(L"─", x[1] - (w / 2) + i, lastRow, BLUE, BROWN);
		console.Write(L"─", x[2] - (w / 2) + i, lastRow, BLUE, BROWN);
	}
	for (int i = 0; i < 3; i++)
	{
		MyWindows win(x[i] - w / 2, 2, w, HEIGHT - 6, BLUE, BLUE);
		win.clearConsole();
		win.drawFrame();
		for (int j = 1; j < 15; j++)
		{
			console.Write(L"│", x[i], lastRow - j, BLUE, BROWN);
		}

		Stack temp;
		Disk disk;
		int stackLength = stack[i].getLength();
		while (stack[i].pop(&disk)) { 
			int diskWidth = (disk.size * 4) + 1;
			MyWindows win(x[i] - diskWidth / 2, lastRow - stackLength * 2, diskWidth, 2, disk.size + 3, WHITE);
			win.clearConsole();
			win.drawFrame();
			stackLength--;
			temp.push(disk);
		}
		while (temp.pop(&disk)) {
			stack[i].push(disk);
		}
	}
	Sleep(300);
}
void towerOfHanoi(MyWindows console, Stack* stack, int n, int source, int target, int temp)  // giải thuật tháp hà nội
{
	
	if (n == 1)
	{
		Disk disk;
		if (stack[source - 1].pop(&disk))
		{
			if (stack[target - 1].push(disk))
			{
				draw(console, stack);
			}
			else
			{
				console.Write("Push Error", 2, row++, RED, WHITE);
				return;
			}
		}
		else {
			console.Write("Pop Error", 2, row++, RED, WHITE);
			return;
		}
		return;
	}
	towerOfHanoi(console, stack, n - 1, source, temp, target);
	Disk disk;
	if (stack[source - 1].pop(&disk))
	{
		if (stack[target - 1].push(disk))
		{
			draw(console, stack);
		}
		else
		{
			console.Write("Push Error", 2, row++, RED, WHITE);
			return;
		}
	}
	else
	{
		console.Write("Pop Error", 2, row++, RED, WHITE);
		return;
	}
	towerOfHanoi(console, stack, n - 1, temp, target, source);
}
void playerMove(MyWindows console, Stack* stack) {
	
	console.drawFrame();
	int source, target;
	console.Write(L"Chọn cột nguồn (1-3): ", 2, 27, BLUE, WHITE);
	
	console.gotoXY(36, 27);
	cin >> source;
	console.Write("			", 36, 27, BLUE, WHITE);
	console.gotoXY(36, 26);

	console.Write(L"Chọn cột đích (1-3): ", 2, 27, BLUE, WHITE);

	console.gotoXY(36, 27);
	cin >> target;
	console.Write("			", 36, 27, BLUE, WHITE);
	console.gotoXY(36, 26);
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		console.Write(L"Cột không hợp lệ, vui lòng chọn lại!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                                       ", 36, 2, BLUE, WHITE);
		return;
	}

	if (source < 1 || source > 3 || target < 1 || target > 3 || source==target) {
		console.Write(L"Cột không hợp lệ, vui lòng chọn lại!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                                        ", 36, 2, BLUE, WHITE);
		return;
	}
	Disk disk;
	if (stack[source - 1].pop(&disk)) {
		Disk targetDisk;
		if (stack[target - 1].pop(&targetDisk)) {
			if (targetDisk.size < disk.size) {
				console.Write(L"Không thể đặt đĩa lớn lên đĩa nhỏ hơn!", 36, 2, RED, WHITE);
				Sleep(2000);
				console.Write("                                           ", 36, 2, BLUE, WHITE);
				stack[source - 1].push(disk); 
				stack[target - 1].push(targetDisk); 
				return;
			}
			else {
				stack[target - 1].push(targetDisk);
			}
		}
		stack[target - 1].push(disk);
		draw(console, stack);
	}
	else {
		console.Write(L"Pop Error: Cột nguồn rỗng!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                             ", 36, 2, BLUE, WHITE);
	}
	
}
void tuChoi(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);
	string name;
	DoubleListPlayer listPlayer;
	listPlayer.loadPlayer("rankPlayer.txt");
	console.Write(L"Nhập tên của bạn: ", 5, 10, BLUE, WHITE);
	console.gotoXY(30, 10); 
	getline(cin, name);
	
	if (listPlayer.linearSearch(name, console)) {
		console.Write(L"Tên đã tồn tại! vui lòng nhập tên khác!", 2, row+1, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}

	if (name == "" || name == " ") {
		console.Write(L"Tên không hợp lệ! vui lòng nhập lại!", 2, row+1, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}

	if (name.length() > 15) {
		console.Write(L"Tên quá dài! vui lòng nhập tên dưới 15 kí tự", 2, row+1, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}

	Sleep(500);
	console.Write(L"Nhập số đĩa: ", 5, 12, BLUE, WHITE);
	console.gotoXY(30, 12);
	int n; cin >> n;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		console.Write(L"Số đĩa không hợp lệ! Vui lòng nhập lại!", 5, row++, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}
	console.Write(L"																", 30, 10, BLUE, WHITE);
	console.Write(L"Số bước tối thiểu: " + to_wstring(int(pow(2, n) - 1)), 57, 27, BLUE, WHITE);
	Stack stack[3];
	for (int i = n; i >= 1; i--)
	{
		Disk disk;
		disk.size = i;
		disk.isRedTop = true;
		stack[0].push(disk);
	}
	draw(console, stack);
	bool isWin = false;
	auto start = chrono::steady_clock::now();
	int count = 0;
	console.Write(L"Số bước đi: " + to_wstring(count), 86, 27, BLUE, WHITE);
	while (!isWin) {
		count++;
		playerMove(console, stack);
		if (stack[2].getLength() == n) {
			isWin = true;
		}
		console.Write(L"Số bước đi: " + to_wstring(count), 86, 27, BLUE, WHITE);
	}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	int score = 100;
	int optimalMoves = pow(2, n) - 1;
	int optimalTime = pow(2, n)-1;
	int moves = count;

	double time = chrono::duration <double, milli>(diff).count() / 1000;
	int moveDiff = moves - optimalMoves;
	int timeDiff = time - optimalTime;

	if (moveDiff > 0)
		score -= moveDiff * 5;

	if (timeDiff > 0) 
		score -= (timeDiff / 10) * 2; 

	listPlayer.addPlayer(Player{ name, n, count, time, score });
	listPlayer.sortPlayer();
	listPlayer.savePlayer("rankPlayer.txt");
	console.Write(L"Chúc mừng bạn đã chiến thắng!", 2, 2, BLUE, WHITE);
	console.Write(L"Tên của bạn: " + wstring(name.begin(), name.end()), 2, 3, BLUE, WHITE);
	console.Write(L"Số đĩa: " + to_wstring(n), 2, 4, BLUE, WHITE);
	console.Write(L"Thời gian: " + to_wstring(chrono::duration <double, milli>(diff).count() / 1000) + L"s", 2, 5, BLUE, WHITE);
	console.Write(L"Số bước đi: " + to_wstring(count), 2, 6, BLUE, WHITE);
	console.Write(L"Điểm của bạn: " + to_wstring(score), 2, 7, BLUE, WHITE);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 2, BLUE, WHITE);
	_getch();
	printHome();
}
void mayChoi(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);
	console.Write(L"Chọn số đĩa: ", 5, 10, BLUE, WHITE);
	console.gotoXY(30, 10);
	int n;
	cin >> n;
	Stack stack[3];
	for (int i = n; i >= 1; i--)
	{
		Disk disk;
		disk.size = i;
		disk.isRedTop = true;
		stack[0].push(disk);
	}
	draw(console, stack);
	towerOfHanoi(console, stack, n, 1, 3, 2);
	console.Write(L"ĐÃ HOÀN THÀNH", 53, row++, BLUE, YELLOW);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 2, BLUE, WHITE);
	_getch();
	printHome();
}
void printPlayGame() {
	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);
	console.Write(L"		1. Tháp Hà Nội từ tính", 2, 10, BLUE, WHITE);
	console.Write(L"		2. Tháp Hà Nội không từ tính", 2, 12, BLUE, WHITE);
	console.Write(L"		3. Luyện tập tháp Hà Nội không từ tính", 2, 14, BLUE, WHITE);
	console.Write(L"		4. Máy giải tháp Hà Nội không từ tính", 2, 16, BLUE, WHITE);
	console.Write(L"		5. Trở về menu", 2, 18, BLUE, WHITE);
	console.Write(L"		Nhấn phím số để chọn chức năng: ", 2, 20, BLUE, WHITE);
	console.gotoXY(36, 6);
	char ch = _getch();
	
	switch (ch)
	{
	case '1':
		tuChoiMagnetic(console);
		break;
	case '2':
		tuChoi(console);
		break;
	case '3':
		XaoTron(console);
		break;
	case '4':
		mayChoi(console);
		break;
	case '5':
		printHome();
		break;
		//neu nguoi dung nhap sai, quay lai menu
	default:
		printPlayGame();
		break;
	}
	}
void printHome() {
	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);
	console.Write(L"		1. Bắt đầu chơi", 2, 10, BLUE, WHITE);
	console.Write(L"		2. Bảng xếp hạng", 2, 12, BLUE, WHITE);
	console.Write(L"		3. Hướng dẫn chơi", 2, 14, BLUE, WHITE);
	console.Write(L"		4. Thoát", 2, 16, BLUE, WHITE);
	console.Write(L"		Nhấn phím số để chọn chức năng: ", 2, 18, BLUE, WHITE);
	console.gotoXY(36, 10);
	char ch = _getch();
	switch (ch)
	{
	case '1':
		printPlayGame();
		break;
	case '2':
		choiceBXH(console);
		break;
	case '3':
		showHuongDan(console);
		break;
	case '4':
		exit(0);
		break;
	}
}
void choiceBXH(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	console.Write(L"Chọn file bạn muốn xem bảng xếp hạng: ", 2, 10, BLUE, WHITE);
	console.Write(L"1. Bảng xếp hạng người chơi thường", 2, 12, BLUE, WHITE);
	console.Write(L"2. Bảng xếp hạng người chơi từ tính", 2, 14, BLUE, WHITE);
	console.Write(L"3. Trở về trang chủ", 2, 16, BLUE, WHITE);
	console.Write(L"Nhập lựa chọn của bạn: ", 2, 18, BLUE, WHITE);
	console.gotoXY(30, 18);
	char ch = _getch();
	if (ch == '1') {
		printScoreBoard("rankPlayer.txt");
	}
	else if (ch == '2') {
		printScoreBoard("rankPlayerMagnetic.txt");
	}
	else if (ch == '3') {
		printHome();
	}
	else {
		console.Write(L"Lựa chọn không hợp lệ! Vui lòng chọn lại!", 2, 10, RED, WHITE);
		Sleep(1500);
		choiceBXH(console);
	}
}
void printScoreBoard(string tenFile) {
	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);

	// Display the headers
	console.Write(L"Hạng", 5, 2, BLUE, YELLOW);
	console.Write(L"Tên", 18, 2, BLUE, YELLOW);
	console.Write(L"Số đĩa", 45, 2, BLUE, YELLOW);
	console.Write(L"Số bước", 60, 2, BLUE, YELLOW);
	console.Write(L"Thời gian", 75, 2, BLUE, YELLOW);
	console.Write(L"Điểm", 100, 2, BLUE, YELLOW);

	DoubleListPlayer listPlayer;
	listPlayer.loadPlayer(tenFile);

	int i = 0;
	int j = 0;
	Node* p = listPlayer.head;

	while (i < items_per_page * current_page && p != NULL) {
		p = p->next;
		i++;
	}
	while (p != NULL && i < items_per_page*(current_page+1)) {
		console.Write(to_wstring(i + 1), 5, 4 + j, BLUE, WHITE);
		console.Write(wstring(p->data.name.begin(), p->data.name.end()), 18, 4 + j, BLUE, WHITE);
		console.Write(to_wstring(p->data.disks), 45, 4 + j, BLUE, WHITE);
		console.Write(to_wstring(p->data.moves), 60, 4 + j, BLUE, WHITE);
		console.Write(to_wstring(p->data.time), 75, 4 + j, BLUE, WHITE);
		console.Write(to_wstring(p->data.score), 100, 4 + j, BLUE, WHITE);
		p = p->next;
		i++;
		j++;
	}

	console.Write(L"	Nhấn 'n' để xem trang tiếp theo...", 2, 5 + items_per_page, BLUE, WHITE);
	console.Write(L"	Nhấn phím 'p' để quay lại trang trước...", 2, 6 + items_per_page, BLUE, WHITE);
	console.Write(L"	Nhấn phím 'f' để tìm kiếm người chơi theo tên...", 2, 7 + items_per_page, BLUE, WHITE);
	console.Write(L"	Bấm phím bất kì để quay về trang chủ...", 2, 8 + items_per_page, BLUE, WHITE);
	char ch = _getch();

	if (ch == 'n') {
		if (current_page * items_per_page< listPlayer.size()) {
			current_page++;
		}
		printScoreBoard(tenFile);
	}
	else if (ch == 'p' ) {
		if (current_page > 0)
			current_page--;
		printScoreBoard(tenFile);
	}
	else if (ch == 'f') {
		findNickname(tenFile);
	}
	else {
		printHome(); 
	}
}
void randomDisks(Stack stacks[], int n) {
	srand(time(0));
	int remainingDisks = n;
	int disksPerColumn[3] = { 0, 0, 0 };

	for (int i = 0; i < 2; i++) {
		disksPerColumn[i] = rand() % (remainingDisks + 1);
		remainingDisks -= disksPerColumn[i];
	}

	disksPerColumn[2] = remainingDisks;

	if (disksPerColumn[0] == 0 && disksPerColumn[1] == 0) {
		disksPerColumn[0] = rand() % (n + 1);  
		disksPerColumn[1] = n - disksPerColumn[0];  
		disksPerColumn[2] = 0;  
	}

	Disk disks[100];
	for (int i = 0; i < n; i++) {
		disks[i].size = i + 1;  
	}

	int diskIndex = 0;
	for (int i = 0; i < 3; i++) {
		if (disksPerColumn[i] > 0) {
			for (int j = disksPerColumn[i] - 1; j >= 0; j--) {
				stacks[i].push(disks[diskIndex + j]); 
			}
			diskIndex += disksPerColumn[i];  
		}
	}
}
void findNickname(string tenFile) {
	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	console.clearConsole();
	console.drawFrame();
	console.Write(L"Nhập tên người chơi bạn muốn tìm: ", 2, 10, BLUE, WHITE);
	string nickname;
	console.gotoXY(50, 10);
	getline(cin, nickname);
	DoubleListPlayer listPlayer;
	listPlayer.loadPlayer(tenFile);
	listPlayer.linearSearch(nickname, console);
	if (!listPlayer.linearSearch(nickname, console)) {
		console.Write(L"Không tìm thấy người chơi!", 2, 5, RED, WHITE);
	}
	console.Write(L"Nhấn phím 'f' để tiếp tục tìm kiếm...", 2, HEIGHT-8, BLUE, WHITE);
	console.Write(L"Nhấn phím 'b' để quay lại bảng xếp hạng...", 2, HEIGHT - 6, BLUE, WHITE);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 4, BLUE, WHITE);
	char ch = _getch();
	if (ch == 'f') {
		findNickname(tenFile);
	}
	else if (ch == 'b') {
		printScoreBoard(tenFile);
	}
	else {
		printHome();
	}

}
void XaoTron(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	console.Write(L"Nhập số đĩa: ", 5, 10, BLUE, WHITE);
	console.gotoXY(30, 10);
	int n;
	cin >> n;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		console.Write(L"Số đĩa không hợp lệ! Vui lòng nhập lại!", 5, row++, RED, WHITE);
		Sleep(1500);
		XaoTron(console);
	}
	console.Write("                                                  ", 5, row, BLUE, WHITE);
	Stack stack[3];
	randomDisks(stack, n);
	draw(console, stack);
	bool isWin = false;
	auto start = chrono::steady_clock::now();
	int count = 0;
	while (!isWin) {
		count++;
		playerMove(console, stack);
		if (stack[2].getLength() == n) {
			isWin = true;
		}
		
	}
	console.Write(L"Chúc mừng bạn đã chiến thắng!", 47, row++, BLUE, WHITE);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 2, BLUE, WHITE);
	_getch();
	printHome();

}
void drawMagnetic(MyWindows console, Stack* stack)
{
	int left = 5;
	int w = (WIDTH - 4 * left) / 3;
	int x[3];
	x[0] = left + w / 2;
	x[1] = x[0] + w + left;
	x[2] = x[1] + w + left;
	int lastRow = HEIGHT - 4;

	for (int i = 0; i < w; i++) {
		console.Write(L"─", x[0] - (w / 2) + i, lastRow, BLUE, WHITE);
		console.Write(L"─", x[1] - (w / 2) + i, lastRow, BLUE, WHITE);
		console.Write(L"─", x[2] - (w / 2) + i, lastRow, BLUE, WHITE);
	}

	for (int i = 0; i < 3; i++) {
		MyWindows win(x[i] - w / 2, 2, w, HEIGHT - 6, BLUE, BLUE);
		win.clearConsole();
		win.drawFrame();

		// Draw vertical rod line
		for (int j = 1; j < 15; j++) {
			console.Write(L"│", x[i], lastRow - j, BLUE, WHITE);
		}

		Stack temp;
		Disk disk;
		int stackLength = stack[i].getLength();

		while (stack[i].pop(&disk)) {
			int diskWidth = (disk.size * 4) + 1; 
			MyWindows win(x[i] - diskWidth / 2, lastRow - stackLength * 2, diskWidth, 2,
				disk.isRedTop ? RED : GREEN, WHITE); 
			win.clearConsole();
			win.drawFrame();
			stackLength--;
			temp.push(disk); 
		}

		while (temp.pop(&disk)) {
			stack[i].push(disk);
		}
	}

	Sleep(300); 
}
void flipDisk(int rodIndex, Stack* rods) {
	Disk& disk = rods[rodIndex].a[rods[rodIndex].top];
	disk.isRedTop = !disk.isRedTop; 
}
void playerMoveMagnetic(MyWindows console, Stack* stack) {

	console.drawFrame();
	int source, target;
	console.Write(L"Chọn cột nguồn (1-3): ", 2, 27, BLUE, WHITE);

	console.gotoXY(36, 27);
	cin >> source;
	console.Write("			", 36, 27, BLUE, WHITE);
	console.gotoXY(36, 26);

	console.Write(L"Chọn cột đích (1-3): ", 2, 27, BLUE, WHITE);

	console.gotoXY(36, 27);
	cin >> target;
	console.Write("			", 36, 27, BLUE, WHITE);
	console.gotoXY(36, 26);

	if (cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		console.Write(L"Cột không hợp lệ, vui lòng chọn lại!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                                    ", 36, 2, BLUE, WHITE);
		return;
	}

	if (source < 1 || source > 3 || target < 1 || target > 3||source==target) {
		console.Write(L"Cột không hợp lệ, vui lòng chọn lại!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                                           ", 36, 2, BLUE, WHITE);
		return;
	}


	Disk disk;
	if (stack[source - 1].pop(&disk)) {
		Disk targetDisk;
		if (stack[target - 1].pop(&targetDisk)) {
			if (targetDisk.isRedTop == disk.isRedTop) {
				console.Write(L"Không thể đặt đĩa cùng màu lên nhau!", 36, 2, RED, WHITE);
				Sleep(2000);
				console.Write("                                                      ", 36, 2, BLUE, WHITE);

				stack[source - 1].push(disk);
				stack[target - 1].push(targetDisk);
				return;
			}
			if (targetDisk.size < disk.size) {
				console.Write(L"Không thể dặt đĩa lớn lên đĩa nhỏ hơn!", 36, 2, RED, WHITE);
				Sleep(2000);
				console.Write("                                           ", 36, 2, BLUE, WHITE);

				stack[source - 1].push(disk);
				stack[target - 1].push(targetDisk);
				return;
			}
			else {

				stack[target - 1].push(targetDisk);
			}
		}

		stack[target - 1].push(disk);
		flipDisk(target - 1, stack);
		drawMagnetic(console, stack);
	}
	else {
		console.Write(L"Pop Error: Cột nguồn rỗng!", 36, 2, RED, WHITE);
		Sleep(2000);
		console.Write("                          ", 36, 2, BLUE, WHITE);
	}

}
void tuChoiMagnetic(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	string name;
	DoubleListPlayer listPlayer;
	listPlayer.loadPlayer("rankPlayerMagnetic.txt");
	console.Write(L"Nhập tên của bạn: ", 5, 10, BLUE, WHITE);
	console.gotoXY(30, 10);
	getline(cin, name);

	if (name == "" || name == " ") {
		console.Write(L"Tên không hợp lệ! vui lòng nhập lại!", 2, row, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}

	if (name.length() > 15) {
		console.Write(L"Tên quá dài! vui lòng nhập tên dưới 15 kí tự", 2, row, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}

	if (listPlayer.linearSearch(name, console)) {
		//nhap lai
		console.Write(L"Tên đã tồn tại vui lòng nhập tên khác!", 2, row, RED, WHITE);
		Sleep(1500);
		tuChoi(console);
	}
	Sleep(500);
	console.Write("                                                               ", 0, row++, BLUE, WHITE);
	console.Write(L"Nhập số đĩa: ", 5, 12, BLUE, WHITE);
	console.gotoXY(30, 12);
	int n;
	cin >> n;
	console.Write("                                                                         ", 2, 10, BLUE, WHITE);
	console.Write("                                                               ", 18, 12, BLUE, WHITE);
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(32767, '\n');
		console.Write(L"Số đĩa không hợp lệ! Vui lòng nhập lại!", 5, row++, RED, WHITE);
		Sleep(1500);
		tuChoiMagnetic(console);
	}
	Stack stack[3];
	for (int i = n; i >= 1; i--)
	{
		Disk disk;
		disk.size = i;
		disk.isRedTop = true;
		stack[0].push(disk);
	}
	drawMagnetic(console, stack);
	bool isWin = false;
	auto start = chrono::steady_clock::now();
	int count = 0;
	console.Write(L"Số bước đi: " + to_wstring(count), 86, 27, BLACK, WHITE);
	while (!isWin) {
		count++;
		playerMoveMagnetic(console, stack);
		if (stack[2].getLength() == n) {
			isWin = true;
		}
		console.Write(L"Số bước đi: " + to_wstring(count), 86, 27, BLACK, WHITE);
	}
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	int score = 100;
	int optimalTime = pow(2, n) - 1;
	int moves = count;

	double time = chrono::duration <double, milli>(diff).count() / 1000;
	int timeDiff = time - optimalTime;

	if (timeDiff > 0)
		score -= (timeDiff / 10) * 2;

	listPlayer.addPlayer(Player{ name, n, count, time, score });
	listPlayer.sortPlayer();
	listPlayer.savePlayer("rankPlayerMagnetic.txt");
	row--;
	console.Write(L"Chúc mừng bạn đã chiến thắng!", 2, 2, BLUE, WHITE);
	console.Write(L"Tên của bạn: " + wstring(name.begin(), name.end()), 2, 3, BLUE, WHITE);
	console.Write(L"Số đĩa: " + to_wstring(n), 2, 4, BLUE, WHITE);
	console.Write(L"Thời gian: " + to_wstring(chrono::duration <double, milli>(diff).count() / 1000) + L"s", 2, 5, BLUE, WHITE);
	console.Write(L"Số bước đi: " + to_wstring(count), 2, 6, BLUE, WHITE);
	console.Write(L"Điểm của bạn: " + to_wstring(score), 2, 7, BLUE, WHITE);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 2, BLUE, WHITE);
	_getch();
	printHome();
}
void showHuongDan(MyWindows console) {
	console.clearConsole();
	console.drawFrame();
	console.Write(L"GAME THÁP HÀ NỘI BY NHÓM 15", 2, 0, BLUE, WHITE);
	console.Write(L"Cách chơi THÁP HÀ NỘI (không từ tính): ", 2, 2, BLUE, WHITE);
	console.Write(L"1. Mỗi cột đều chứa một số đĩa, đĩa lớn hơn nằm dưới đĩa nhỏ hơn", 2, 4, BLUE, WHITE);
	console.Write(L"2. Mục tiêu của trò chơi là chuyển tất cả các đĩa từ cột nguồn sang cột đích", 2, 6, BLUE, WHITE);
	console.Write(L"3. Mỗi lần chuyển, chỉ được chuyển một đĩa và không được đặt đĩa lớn lên đĩa nhỏ", 2, 8, BLUE, WHITE);
	console.Write(L"4. Bạn có thể chọn chơi thủ công hoặc máy giải tháp Hà Nội", 2, 10, BLUE, WHITE);
	console.Write(L"Cách chơi THÁP HÀ NỘI (có từ tính): ", 2, 14, BLUE, WHITE);
	console.Write(L"1. Mỗi cột đều chứa một số đĩa, đĩa lớn hơn nằm dưới đĩa nhỏ hơn", 2, 16, BLUE, WHITE);
	console.Write(L"2. Mỗi đĩa có mặt dưới màu Xanh và mặt trên màu Đỏ ", 2, 18, BLUE, WHITE);
	console.Write(L"3. Mặt Đỏ của tất cả các đĩa đều hướng lên.", 2, 20, BLUE, WHITE);
	console.Write(L"4. Quy tắc di chuyển: Lật ngược đĩa và đặt nó lên một cọc khác.", 2, 22, BLUE, WHITE);
	console.Write(L"5. Cấm hai mặt đồng màu tiếp xúc nhau", 2, 24, BLUE, WHITE);
	console.Write(L"6. Mục tiêu là di chuyển tất cả các đĩa từ cột 1-> 3 mà không phá vỡ quy tắc", 2, 26, BLUE, WHITE);
	console.Write(L"Nhấn phím bất kì để quay lại trang chủ...", 2, HEIGHT - 2, BLUE, WHITE);
	_getch();
	printHome();

}
int main() {
	srand(time(NULL));
	ShowCur(false);
	MyWindows console(0, 0, WIDTH, HEIGHT, BLUE, WHITE);
	printHome();
	char ch = _getch();
}