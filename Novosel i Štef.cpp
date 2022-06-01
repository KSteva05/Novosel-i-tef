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
		cout << "Molim unesite Vase ime: ";
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

/***************************************
FUNCTION NAME: playerMenu

INPUT:

OUTPUT:

DESCRIPTION:
***************************************/
void playerMenu()
{
	cout << "\nLITTLETON CITY LOTTO MODEL:" << endl
		<< "---------------------------" << endl
		<< "1) Igraj Lotto" << endl
		<< "q) Izlaz iz programa" << endl
		<< "Molim odaberite jednu od navedenih opcija." << endl;
}

/***************************************
FUNCTION NAME: playAgain

INPUT:

OUTPUT:

DESCRIPTION:
***************************************/
bool playAgain()
{
	char choice;
	cout << " " << endl;
	cout << "If you would like to play again press Y/y\n"
		<< "otherwise press any key to exit the game" << endl;
	cin >> choice;
	if(choice == 'y' || choice == 'Y')
	{
		choice = true;
	}
	else
		choice = false;

	return choice;
}

/***************************************
FUNCTION NAME: getuserTicket

INPUT:

OUTPUT:

DESCRIPTION: Get user lotto numbers
	between 1 and 40 with no duplicate
	entries.
***************************************/
void getuserTicket(int userTicket[], int size)
{
	// Get user lotto numbers
	cout << "Unesite 7 brojeva izmedu 1-40: " << endl;

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
				cout << "Pogresan unos!" << endl;
				cout << "Unesi broj izmedu 1 i 40: ";
				cin >> userTicket[i];
				//checks for duplicate numbers in array
			}
			if(checkDuplicates(userTicket, userTicket[i], i))
			{
				cout << "Vec ste unijeli taj broj, molim unesite drugi : " << endl;
				cin >> userTicket[i];
				cout << endl;
			}
		}
	}
}

/***************************************
FUNCTION NAME: getuserTicket

INPUT:

OUTPUT:

DESCRIPTION:
***************************************/
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


/***************************************
FUNCTION NAME: Results

INPUT:

OUTPUT:

DESCRIPTION: displays lotto results
***************************************/
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
	cout << "Dobitak : ";
	switch(count)
	{
		case 1:
		case 2:
			cout << "NISTA\n\n";
			break;
		case 3:
			cout << "BESTPLATNI LISTIC\n\n";
			break;
		case 4:
			cout << "NIJE LOSE - $100\n\n";
			break;
		case 5:
			cout << "SRETNICE! - $5,000\n\n";
			break;
		case 6:
			cout << "SUPER! - $100,000\n\n";
			break;
		case 7:
			cout << "JACKPOT - $1,000,000\n\n";
			break;
	}
	cout << endl;
}

/***************************************
FUNCTION NAME: checkMatches

INPUT:

OUTPUT:

DESCRIPTION: Compares user lotto numbers
	to random generated numbers to see
	how many matches there are.
***************************************/
int checkMatches(int userTicket[], int winningNums[], int size)
{
	int count = 0;

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; i < size; j++)
			if(userTicket[i] == winningNums[j])
		{
			count++;
			break;
		}
	}
	return count;
}

/***************************************
FUNCTION NAME: checkDuplicates

INPUT:

OUTPUT:

DESCRIPTION: checks for duplicate
	numbers.
***************************************/
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