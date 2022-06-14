#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct ListOFUsers {
	char name[32];
	int winningNums[7];
	int userTicket[7];
	int matchingNumbers;
};

ListOFUsers listofusers[100];

string p1 = "NISTA - 0$\n";
string p2 = "MALO VISE OD NISTA, ALI I DALJE NISTA - 0$\n";
string p3 = "NESTO - 10$\n";
string p4 = "U REDU - 300$\n";
string p5 = "NIJE LOSE - 500$\n";
string p6 = "SRETNICE - 5,000$\n";
string p7 = "IZVRSNO - 100,000$\n";
string p8 = "JACKPOT - 1,000,000$\n";

void LoadingScore(int &NumberOfUsers);
void SavingScore(string name, int winningNums[], int userTicket[], int &matchingNumbers, int NumberOfUsers);
void getuserTicket(int userTicket[], int);
void getwinningNumbers(int winningNums[], int);
void results(string name, int userTicket[], int winningNums[], int size, int &matchingNumbers);
void playerMenu();
int checkMatches(int userTicket[], int winningNums[], int size);
bool checkDuplicates(int userticket[], int size, int i);
void playing(string name1, int userTicket[], int num, int winningNums[], int matchingNumbers, int NumberOfUsers);


int main()
{
	srand((unsigned int)time(NULL));

	const int num = 7;
	int userTicket[num]; // array holds user picked numbers
	int winningNums[num]; // array holds random winning numbers
	int matchingNumbers = 0;
	int NumberOfUsers = 0;
	string name1;
	playing(name1, userTicket, num, winningNums, matchingNumbers, NumberOfUsers);
}

void playerMenu()
{
	cout << "\nLOTO 7:" << endl
		<< "---------------------------" << endl
		<< "1) Igraj Lotto" << endl
		<< "q) Izlaz iz programa" << endl
		<< "s) Spremite trenutni rezultat" << endl
		<< "l) Prikazi povijest igre" << endl
		<< "Molim odaberite jednu od navedenih opcija." << endl;
}

void getuserTicket(int userTicket[], int size)
{
	// Get user lotto numbers
	cout << "Unesite 7 brojeva izmedu 1-40: " << endl;

	//Loop to store 7 lotto numbers in array 
	for (int i = 0; i < size; i++)
	{
		cout << "odabir # " << i + 1 << ": ";
		cin >> userTicket[i];

		//Loop if user enters invalid numbers
		while (checkDuplicates(userTicket, userTicket[i], i) || userTicket[i] < 1 || userTicket[i] > 40)
		{
			if (userTicket[i] < 1 || userTicket[i] > 40)
			{
				cout << "Pogresan unos!" << endl;
				cout << "Unesi broj izmedu 1 i 40: ";
				cin >> userTicket[i];
			}
			if (checkDuplicates(userTicket, userTicket[i], i))
			{
				cout << "Vec ste unijeli taj broj, molim unesite drugi : " << endl;
				cin >> userTicket[i];
				cout << endl;
			}
		}
	}
}

void getwinningNumbers(int winningNums[], int size)

{
	srand(time(0));

	for (int i = 0; i < size; i++)
	{
		winningNums[i] = 1 + (rand() % 40);

		while (checkDuplicates(winningNums, winningNums[i], i))
		{
			winningNums[i] = 1 + (rand() % 40);
		}
	}
}

void results(string name, int userTicket[], int winningNums[], int size, int &matchingNumbers)
{
	int count = checkMatches(userTicket, winningNums, size);
	cout << "" << name << " LOTTO REZULTATI:" << endl;
	cout << "---------------------------" << endl;

	cout << "DOBITNI BROJEVI: ";
	for (int i = 0; i < size; i++)
	{
		cout << " " << winningNums[i];
	}
	cout << endl;
	cout << "" << name << "'s TICKET: ";
	for (int i = 0; i < size; i++)
	{
		cout << " " << userTicket[i];
	
	}
	cout << endl << endl;
	cout << "REZULTATI:" << endl;
	cout << "--------" << endl;
	cout << "Broj pogodaka: " << count << endl;
	cout << endl;
	switch (count)
	{
		case 0:
			cout << p1;
			matchingNumbers = 0;
			break;
		case 1:
			cout << p2;
			matchingNumbers = 1;
			break;
		case 2:
			cout << p3;
			matchingNumbers = 2;
			break;
		case 3:
			cout << p4;
			matchingNumbers = 3;
			break;
		case 4:
			cout << p5;
			matchingNumbers = 4;
			break;
		case 5:
			cout << p6;
			matchingNumbers = 5;
			break;
		case 6:
			cout << p7;
			matchingNumbers = 6;
			break;
		case 7:
			cout << p8;
			matchingNumbers = 7;
			break;
	}
}

int checkMatches(int userTicket[], int winningNums[], int size)
{
	int count = 0;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (userTicket[i] == winningNums[j])
			{
				count++;
				break;
			}
		}
	}
	return count;
}

bool checkDuplicates(int userticket[], int ticket, int i)
{
	bool duplicate = false;

	for (int j = 0; j < i; j++)
	{
		if (userticket[j] == ticket)
		{
			duplicate = true;
		}
	}
	return duplicate;
}

void SavingScore(string name, int winningNums[], int userTicket[], int &matchingNumbers, int NumberOfUsers) {
	name.resize(32);
	fstream save("save.bin", ios::binary | ios::out);
	save.write((char*)&NumberOfUsers, sizeof(NumberOfUsers));
	for(int i = 0; i <= NumberOfUsers - 2; i++) {
		save.write((char*)listofusers[i].name, 32);
		save.write((char*)listofusers[i].winningNums, 28);
		save.write((char*)listofusers[i].userTicket, 28);
		save.write((char*)&listofusers[i].matchingNumbers, 4);
	}
	name.resize(32);
	save.write((char*)&name[0], 32);
	save.write((char*)winningNums, 28);
	save.write((char*)userTicket, 28);
	save.write((char*)&matchingNumbers, 4);
}

void LoadingScore(int &NumberOfUsers) {
	fstream save("save.bin", ios::binary | ios::in);
	if(save.fail()) {
		cout << "Greska pri otvaranju save.bin. Provjerie jeste li kreirali datoteku i je li ona pravilno napisana!\n";
    }
	save.read((char*)&NumberOfUsers, sizeof(NumberOfUsers));
	for(int i = 0; i <= NumberOfUsers - 1; i++) {
		save.read((char*)listofusers[i].name, 32);
		save.read((char*)listofusers[i].winningNums, 28);
		save.read((char*)listofusers[i].userTicket, 28);
		save.read((char*)&listofusers[i].matchingNumbers, 4);
	}

}

void playing(string name1, int userTicket[], int num, int winningNums[], int matchingNumbers, int NumberOfUsers) {
	while(true) {	
		char choice;
		playerMenu();
		cin >> choice;
		cout << endl;
		if (choice == '1')
		{
			cout << "Molim unesite Vase ime i prezime: ";
			cin >> name1;
			getline(cin, name1);
			cout << endl;

			getuserTicket(userTicket, num);
			getwinningNumbers(winningNums, num);
			cout << endl;
			results(name1, userTicket, winningNums, num, matchingNumbers);

		}
		else if (choice == 'q' || choice == 'Q')
		{
			cout << "Izabrali ste izaci iz programa." << endl;
		}
		else if (toupper(choice) == 'S')
		{
			cout << "Izabrali ste spremit rezultat." << endl;
			SavingScore(name1, winningNums, userTicket, matchingNumbers, NumberOfUsers + 1);
			cout << "Rezultat spremljen!" << endl;
		}
		else if (toupper(choice) == 'L')
		{
			cout << "Izabrali ste ucitat rezultat." << endl;
			LoadingScore(NumberOfUsers);
			for(int i = 0; i <= NumberOfUsers - 1; i++) {
				cout << listofusers[i].name << "\t";
				for(int j = 0; j < 7; j++) {
					cout << listofusers[i].winningNums[j] << " ";
				}
				cout << "\t";
				for(int j = 0; j < 7; j++) {
					cout << listofusers[i].userTicket[j] << " ";
				}
				cout << "\t";
				cout << listofusers[i].matchingNumbers << " ";
			cout << endl;
			}
		}
		else if (choice != '1' || choice != 'q' || choice != 'Q' || toupper(choice) == 'S' || toupper(choice) == 'L')
		{
			cout << "Pogresan unos." << endl;
			exit(EXIT_FAILURE);
		}
	}
}