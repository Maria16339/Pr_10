#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Posada { SLUZHBOVETS };
string posadaStr[] = { "службовець" };
struct Pracivnyk
{
	string prizv;
	unsigned rik_pr;
	Posada posada;
	union
	{

		int oklad;
	};
};
int main();
void Create(Pracivnyk* p, const int N);
void Print(Pracivnyk* p, const int N);
void Sort(Pracivnyk* p, const int N);
double LineSearch(Pracivnyk* p, const int N);
int BinSearch(Pracivnyk* p, const int N, const string prizv, const Posada posada);
int* IndexSort(Pracivnyk* p, const int N);
void PrintIndexSorted(Pracivnyk* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість працівників N: "; cin >> N;

	Pracivnyk* p = new Pracivnyk[N];
	int iposada;
	Posada posada;
	string prizv;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ  робітників" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - бінарний пошук працівника за посадою та прізвищем" << endl;
		cout << " [6] - індексне впорядкування та вивід даних" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;

		case 2:
			Print(p, N);
			break;
		case 3:
			LineSearch(p, N);
			break;
		case 4:
			Sort(p, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " посада (0 - службовець): ";
			cin >> iposada;
			posada = (Posada)iposada;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " Прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, posada)) != -1)
				cout << "Знайдено працівника в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Pracivnyk* p, const int N)
{
	int posada;
	for (int i = 0; i < N; i++)
	{
		cout << "Працівник № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " рік прийому: "; cin >> p[i].rik_pr;
		cout << " посада (0 - службовець): ";
		cin >> posada;
		p[i].posada = (Posada)posada;
		switch (p[i].posada)
		{

		case SLUZHBOVETS:
			cout << "  Оклад: "; cin >> p[i].oklad;
			break;
		}
		cout << endl;
	}
}
void Print(Pracivnyk* p, const int N)
{
	cout << "==============================================="
		<< endl;
	cout << "| № | Прізвище | Рік прийому | Посада | Оклад |"
		<< endl;
	cout << "-----------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].rik_pr << " "
			<< "| " << setw(11) << left << posadaStr[p[i].posada];
		switch (p[i].posada)
		{

		case SLUZHBOVETS:
			cout << "|" << " " << setw(8) << right
				<< p[i].oklad << " |" << endl;
			break;
		}
	}
	cout << "==============================================="
		<< endl;
	cout << endl;
}
double LineSearch(Pracivnyk* p, const int N)
{
	cout << "Прізвища службовців:" << endl;
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].posada == SLUZHBOVETS)

		{

			{
				k++;
				cout << setw(3) << right << k
					<< " " << p[i].prizv << endl;
			}
		}
	}
	return 100.0 * k / n;
}

void Sort(Pracivnyk* p, const int N)
{
	Pracivnyk tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].posada > p[i1 + 1].posada)
				||
				(p[i1].posada == p[i1 + 1].posada &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Pracivnyk* p, const int N, const string prizv, const Posada posada)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].posada == posada)
			return m;
		if ((p[m].posada < posada)
			||
			(p[m].posada == posada &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Pracivnyk* p, const int N)
{

	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].posada > p[value].posada) ||
				(p[I[j]].posada == p[value].posada &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Pracivnyk* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "==============================================="
		<< endl;
	cout << "| № | Прізвище | Рік прийому | Посада | Оклад |"
		<< endl;
	cout << "-----------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].rik_pr << " "
			<< "| " << setw(11) << left << posadaStr[p[I[i]].posada];
		switch (p[I[i]].posada)
		{

		case SLUZHBOVETS:
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right
				<< p[I[i]].oklad << " |"
				<< endl;
			break;
		}
	}
	cout << "==============================================="
		<< endl;
	cout << endl;
}