#include <iostream>
#include <iomanip>
using namespace std;
struct student {
    string name;
    int num;
    float top;
};\
void print(int quantity, student** arr) {
	for (int i = 0; i < quantity; i++) {
		cout << setw(3) << i << setw(5) <<"| " << arr[i]->name << " " << arr[i]->num << " " << arr[i]->top << endl;
	}
	cout << endl;
}
void sort(int quantity,student* arr, student **directory) {
	for (int i = 0; i < quantity; i++) {
		int count = 0;
		for (int j = 0; j < quantity; j++) {
			if (arr[i].num > arr[j].num) 
				count += 1;
		}
		while ( directory[count]->num==arr[i].num) {
			count += 1;
		}
		directory[count ] = &arr[i];
	}
}
int searc(int First, int Last, student** directory, int search) {
	if (Last - First == 1 || Last == First)
		return First;
	int newFirst, newLast;
	int k = First + (Last - First) / 2;
	if (directory[k]->num > search) {
		newFirst = First;
		newLast = k;
	}
	else {
		newFirst = k;
		newLast = Last;
	}
	return searc(newFirst, newLast, directory, search);
}
int main()
{
	system("chcp 1251 > text");
	int quantity,userchoice; cout << "Введите кол-во полей\n";
	cin >> quantity;
	student* arr = new student[quantity];
	for (int i = 0; i < quantity; i++) {
		arr[i].name = char(rand() % 26 + 0x61);
		arr[i].num = rand();
		arr[i].top = float(rand() % 100) + float(rand() % 101) / 100;
	}
	student a; a.num = -1;
	student** directory = new student*[quantity];
	for (int i = 0; i < quantity; i++)
		directory[i] = &a;
	sort(quantity, arr, directory);
	print(quantity, directory);
	int search, lasts;
	cout << "Если поиск по совпадению - 1, если по интервалу -2:\n";
	cin >> userchoice;
	cout << "Введите число: ";
	switch (userchoice) {
	case 1: {
		cin >> search;
		lasts = search; break;
	}
	case 2: {
		cin >> search;
		cout << "Введите число: ";
		cin >> lasts;}
	}
	int s = searc(0, quantity, directory, search);
	if (userchoice == 2) 
		s += 1;

	bool count = 0;
	while (directory[s]->num >= search) {
		if (s == 0) {
			s -= 1;
			break;
		}
		s -= 1;
	}
	s += 1;
	while (directory[s]->num <= lasts) {
		cout << setw(3) << s << setw(5) << "| " <<  directory[s]->name << " " << directory[s]->num << " " << directory[s]->top << endl;
		if (s == quantity-1)
			break;
		s += 1;
		count += 1;
	}
	if (!count)
		cout << "Ничего не найдено";
}
