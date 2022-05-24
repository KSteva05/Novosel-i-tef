#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

void getuserTicket(int userTicket[], int);
void getwinningNumbers(int winningNums[], int);
void results(string name, int userTicket[], int winningNums[], int size);
void playerMenu();
int checkMatches(int userTicket[], int winningNums[], int size);
bool checkDuplicates(int userticket[], int size, int i);


int main()
{
	srand((unsigned int)time(NULL));

	const int num = 7;
	int userTicket[num]; // array holds user picked numbers
	int winningNums[num]; // array holds random winning numbers
	int matchingNumbers = 0;
	string name1;
	char choice;

	playerMenu();
	cin >> choice;
	cout << endl;
	if(choice == '1')
	{
		cout << "Unesite svoje ime: "; 
		cin >> name1;
		cout << endl;

		getuserTicket(userTicket, num);
		getwinningNumbers(winningNums, num);
		cout << endl;
		results(name1, userTicket, winningNums, num);

	}
	else if(choice == 'q' || choice == 'Q')
	{
		cout << "Izabrali ste izaci iz programa." << endl;
	}
	else if(choice != '1' || choice != 'q' || choice != 'Q')
	{
		cout << "Pogresan unos." << endl;
	}

	return 0;
}

void playerMenu()
{
	cout << "\nLITTLETON CITY LOTTO MODEL:" << endl
		<< "---------------------------" << endl
		<< "1) Igraj Lotto" << endl
		<< "q) Izadi iz programa" << endl
		<< "Molim odaberite jednu od navedenih opcija." << endl;
}

bool playAgain()
{
	char choice;
	cout << " " << endl;
	cout << "Ako zelite igrati ponovno pritisnite Y/y\n"
		<< "ako ne, pritisnite bilo koju drugu tipku da bi izasli iz programa." << endl;
	cin >> choice;
	if(choice == 'y' || choice == 'Y')
	{
		choice = true;
	}
	else
		choice = false;

	return choice;
}

void getuserTicket(int userTicket[], int size)
{
	// Get user lotto numbers
	cout << setw(55) << "Unesite sedam brojeva izmedu 1-40: " << endl;

	//Loop to store 7 lotto numbers in array 
	for(int i = 0; i < size; i++)
	{
		cout << "odabir # " << i + 1 << ": ";
		cin >> userTicket[i];

		//Loop if user enters invalid numbers
		while(checkDuplicates(userTicket, userTicket[i], i) || userTicket[i] < 1 || userTicket[i] > 40)
		{
			if(userTicket[i] < 1 || userTicket[i] > 40)
			{
				cout << "Pogresan unos.\n" << endl;
				cout << "Unesite broj izmedu 1 i 40: ";
				cin >> userTicket[i];
				//checks for duplicate numbers in array
			}
			if(checkDuplicates(userTicket, userTicket[i], i))
			{
				cout << "Vec ste unijeli taj broj, molim unesite drugi: " << endl;
				cin >> userTicket[i];
				cout << endl;
			}
		}
	}
}

void getwinningNumbers(int winningNums[], int size)
{
	srand(time(0));

	for(int i = 0; i < size; i++)
	{
		winningNums[i] = 1 + (rand() % 40);

		while(checkDuplicates(winningNums, winningNums[i], i))
		{
			winningNums[i] = 1 + (rand() % 40);
		}
	}
}

void results(string name, int userTicket[], int winningNums[], int size)
{
	int count = checkMatches(userTicket, winningNums, size);
	cout << "" << name << " LOTTO REZULTATI:" << endl;
	cout << "---------------------------" << endl;

	cout << "DOBITNI BROJEVI: ";
	for(int i = 0; i < size; i++)
	{
		cout << " " << winningNums[i];
	}
	cout << endl;
	cout << "" << name << "'s TICKET: ";
	for(int i = 0; i < size; i++)
	{
		cout << " " << userTicket[i];
	}
	cout << endl << endl;
	cout << "REZULTATI:" << endl;
	cout << "--------" << endl;
	cout << "Broj pogodaka: " << count << endl;
	cout << endl;
	cout << "Nagrada : ";
	switch(count)
	{
		case 1: 
		case 2:
			cout << "NISTA\n\n";
			break;
		case 3:
			cout << "BESPLATNI LISTIC\n\n";
			break;
		case 4:
			cout << "NIJE LOSE - $100\n\n";
			break;
		case 5:
			cout << "VRLO DOBRO - $5,000\n\n";
			break;
		case 6:
			cout << "SUPER! - $100,000\n\n";
			break;
		case 7:
			cout << "JACKPOT - $1,000,000 \n\n";
			break;
	}
	cout << endl;
}

int checkMatches(int userTicket[], int winningNums[], int size)
{
	int count = 0;

	for(int i = 0; i < size; i++)
	{
		int temp = userTicket[i];

		if(temp == winningNums[i])
		{
			count++;
		}
	}
	return count;
}

bool checkDuplicates(int userticket[], int ticket, int i)
{
	bool duplicate = false;

	for(int j = 0; j < i; j++)
	{
		if(userticket[j] == ticket)
		{
			duplicate = true;
		}
	}
	return duplicate;
}