#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

typedef struct contacts
{
	string firstName;
	string lastName;
	string phoneNumber;
	string address;
	struct contacts *next;
	struct contacts *prev;
}contacs;

bool checkIfNumberCanBeConverted(string number);
short fromStringToInt(string number);
contacts* createNewContact();
void addContact(contacts *&head);
void goBack(contacts *&head);
void listContacts(contacts *&head);
void mainMenu(contacts *&head);
void modifyContact(contacts *&head);
void modifyContactField(contacts *&head, contacts *iterator);
void readContactsFromFile(contacts *&head);
void searchContact(contacts *&head);
void searchContactBy(contacts *&head, char option);
void selectContactToDelete(contacts *&head);
void writeContactsInFile(contacts *&head);

/*
Function used to check if a string can be converted to a number
*/

bool checkIfNumberCanBeConverted(string number)
{
	//A number can't start with 0
	if ((number.length() > 1) && (number[0] == '0'))
	{
		return false;
	}

	short iterator = 0;

	while (iterator < number.length())
	{
		if ((number[iterator] < '0') || (number[iterator] > '9'))
		{
			return false;
		}
		iterator++;
	}

	return true;
}

/*
Creating a new contact
*/

contacts* createNewContact()
{
	contacts *newContact = new contacts;

	cout << "\n\tIntroduce the last name: ";
	getline(cin, newContact->lastName);
	cout << "\n\tIntroduce the first name: ";
	getline(cin, newContact->firstName);
	cout << "\n\tIntroduce the number: ";
	getline(cin, newContact->phoneNumber);
	cout << "\n\tIntroduce the address: ";
	getline(cin, newContact->address);

	return newContact;
}

/*
Function used to transform a string number into a int
*/

short fromStringToInt(string number)
{
	short iterator = 0;
	short numberInt = 0;

	while (iterator < number.length())
	{
		numberInt = numberInt * 10 + (number[iterator] - '0');
		iterator++;
	}

	return numberInt;
}


/*
Adding a new contact in a sorted list by parsing the list element by element
and compare the new contact with the contacts from the list first by lastName
than if we have multiple contacts with the same lastName by firstName

After this we check on which possition the new contact needs to be added 
first position/ last position/ position iterator
*/

void addContact(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tAdd a new contact\n";

	contacts *iterator = head;
	contacts *newContact = createNewContact();
	//I will use this var to know if I compare the 2 contacts by lastName or firstName
	//before adding it to the list to know on which position the new contact needs to be added
	int compareTwoContactsBy = 2;

	//Compare by last name
	while (((iterator != NULL) && (iterator->next != NULL)) &&
		(iterator->lastName.compare(newContact->lastName) < 0))
	{
		iterator = iterator->next;
	}

	if (iterator != NULL)
	{
		compareTwoContactsBy = iterator->lastName.compare(newContact->lastName);
	}

	//If they have the same last name we start compare by first name
	if ((iterator != NULL) && (iterator->lastName.compare(newContact->lastName) == 0))
	{
		while (((iterator != NULL) && (iterator->next != NULL)) &&
			(iterator->firstName.compare(newContact->firstName) < 0))
		{
			iterator = iterator->next;
		}
		compareTwoContactsBy = iterator->firstName.compare(newContact->firstName);
	}

	//if the list is empty or the new contact is < than the first contact from the phone book
	if ((iterator == NULL) || ((iterator == head) &&
		(compareTwoContactsBy > 0)))
	{
		//Adding the new contact on first position of the list
		newContact->next = head;
		newContact->prev = NULL;
		if (head != NULL)
		{
			head->prev = newContact;
		}
		head = newContact;
	}
	else
	{
		//If we are at the last contact and the new contact is > than the last contact from the phone book
		if ((iterator->next == NULL) &&
			(compareTwoContactsBy < 0))
		{
			//Adding the new contact on the last position of the list
			newContact->next = NULL;
			newContact->prev = iterator;
			iterator->next = newContact;
		}
		else
		{
			//Checking if the lastName and firstName are not the same with the new contact
			if (compareTwoContactsBy != 0)
			{
				//Adding at the position iterator is at
				newContact->next = iterator;
				newContact->prev = iterator->prev;
				iterator->prev->next = newContact;
				iterator->prev = newContact;
			}
		}
	}
}

/*
Function used after an operation is done (adding a new contact, modifying a contact,
deleting a contact,searching for a contact) to go back to the main menu or to exit the phone book
*/

void goBack(contacts *&head)
{
	cout << "\n\n\t1.Go back to main menu.";
	cout << "\n\t2.Exit the phone book.";
	cout << "\n\tIntroduce the number of the option you want : ";
	char number = _getch();

	switch (number)
	{
	case '1':
		mainMenu(head);
		break;
	case '2':
		return;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		goBack(head);
		break;
	}
}

/*
Listing all the contacts alphabetical that are in the phone book
by parsing the list and writing the info about every contact
*/

void listContacts(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tContacts";

	contacts *iterator = head;
	short index = 0;

	if (iterator == NULL)
	{
		cout << "\n\n\tThe phone book is empty.";
	}
	else
	{
		cout << "\n\n\tThe contacts from the phone book are:";
		while (iterator != NULL)
		{
			cout << "\n\t" << index << ".";
			cout << iterator->lastName << " " << iterator->firstName << " ";
			cout << iterator->phoneNumber << " " << iterator->address;
			iterator = iterator->next;
			index++;
		}
	}
}

/*
Main menu used to navigate and do operations on the phone book
(add a new contact/ modify a contact/ delete a contact/ search for a contact)
*/

void mainMenu(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tPhone Book. Main Menu";
	cout << "\n\n\tChoose an option by inserting the number of the option:\n";
	cout << "\n\t1.List all the contacts";
	cout << "\n\t2.Add a new contact";
	cout << "\n\t3.Modify a contact";
	cout << "\n\t4.Delete a contact";
	cout << "\n\t5.Search for a contact";
	cout << "\n\t6.Exit the phone book";
	cout << "\n\n\tIntroduce the number of the option you want:";
	char option = _getch();

	switch (option)
	{
	case '1':
		listContacts(head);
		break;
	case '2':
		addContact(head);
		break;
	case '3':
		modifyContact(head);
		break;
	case '4':
		selectContactToDelete(head);
		break;
	case '5':
		searchContact(head);
		break;
	case '6':
		return;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
	goBack(head);
}

/*
Modify a specific field of a contact
(last name, first name, phone number, address) 
The user will choose from all the contacts, the contact that he wants to modify
and than select the field he wants to modify
*/

void modifyContact(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tModify a contact from the phone book";
	if (head == NULL)
	{
		cout << "\n\n\tThe phone book is empty.";
		return;
	}

	short iteratorInt = 0;
	short numberInt = 0;
	string number;
	contacts *iterator = head;

	listContacts(head);
	do
	{
		cout << "\n\n\tIntroduce the number of the contact that you want to modify from the phone book: ";
		getline(cin, number);
	} while ((checkIfNumberCanBeConverted(number) == false) || (number.length() >= 5));

	numberInt = fromStringToInt(number);

	while ((iterator != NULL) && (iteratorInt < numberInt))
	{
		iterator = iterator->next;
		iteratorInt++;
	}

	if (iteratorInt == numberInt)
	{
		modifyContactField(head, iterator);
	}
	else
	{
		cout << "\n\tThe contact with the number " << numberInt << " doesn't exist.";
	}
}

/*
Function used to modify a specific field of an contact
*/

void modifyContactField(contacts *&head, contacts *iterator)
{
	cout << "\n\tWhat do you want to modify in this contact?";
	cout << "\n\t1.Modify the last name";
	cout << "\n\t2.Modify the first name";
	cout << "\n\t3.Modify the phone number";
	cout << "\n\t4.Modify the address";
	cout << "\n\n\tIntroduce the number of the option you want:";

	char answer = _getch();
	string newInfo;

	switch (answer)
	{
	case '1':
		cout << "\n\tIntroduce the new last name: ";
		getline(cin, newInfo);
		iterator->lastName = newInfo;
		break;
	case '2':
		cout << "\n\tIntroduce the new first name: ";
		getline(cin, newInfo);
		iterator->firstName = newInfo;
		break;
	case '3':
		cout << "\n\tIntroduce the new phone number: ";
		getline(cin, newInfo);
		iterator->phoneNumber = newInfo;
		break;
	case '4':
		cout << "\n\tIntroduce the new address: ";
		getline(cin, newInfo);
		iterator->address = newInfo;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}

	cout << "\n\n\tDo you want to modify anything else about this contact?";
	cout << "\n\t1.Yes";
	cout << "\n\t2.No";
	cout << "\n\n\tIntroduce the number of the option you want:";
	char option = _getch();

	switch (option)
	{
	case '1':
		modifyContactField(head, iterator);
		break;
	case '2':
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
}

/*
Reading the contacts everytime we start the program from a file
The info about a contact is separated by '|' in the file
Creating a doubly linked list with the contacts from the file
*/

void readContactsFromFile(contacts *&head)
{
	char aux[100];
	contacts *iterator = head;
	ifstream input("contacts.in");

	while (input.getline(aux, 100, '|'))
	{
		contacts *newContact = new contacts;

		newContact->lastName = aux;

		input.getline(aux, 100, '|');
		newContact->firstName = aux;

		input.getline(aux, 100, '|');
		newContact->phoneNumber = aux;

		input.getline(aux, 100);
		newContact->address = aux;

		if (head == NULL)
		{
			head = newContact;
			newContact->prev = NULL;
			newContact->next = NULL;
			iterator = head;
		}
		else 
		{
			iterator->next = newContact;
			newContact->prev = iterator;
			newContact->next = NULL;
			iterator = iterator->next;
		}
	}
	input.close();
}

/*
Function that represents the menu for searching a contact by different criteries
*/

void searchContact(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tSearch for a specific contact\n";
	cout << "\n\t1.Search by last name";
	cout << "\n\t2.Search by first name";
	cout << "\n\t3.Search by phone number";
	cout << "\n\tIntroduce the number of the option you want : ";

	char number = _getch();

	switch (number)
	{
	case '1':
	case '2':
	case '3':
		searchContactBy(head, number);
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
}

/*
Function used to search for a contact(or multiple contacts) by parsing 
the list of contacts using a iterator and checking if the contacts contain 
the name/number the user introduced.
*/

void searchContactBy(contacts *&head, char option)
{
	contacts *iterator = head;
	short index = 0;
	string searchText;

	switch (option)
	{
	case '1':
		// Search contact by last name 
		cout << "\n\tIntroduce the last name or a part of it: ";
		getline(cin, searchText);
		cout << "\n\tThe contacts that you are searching for are:";
		while (iterator != NULL)
		{
			if ((searchText.length() <= head->lastName.length()) &&
				(head->lastName.find(searchText) < head->lastName.length()))
			{
				cout << "\n\t" << index << ".";
				cout << iterator->lastName << " " << iterator->firstName;
				cout << " " << iterator->phoneNumber << " " << iterator->address;
			}
			iterator = iterator->next;
		}
		break;
	case '2':
		// Search contact by first name 
		cout << "\n\tIntroduce the first name or a part of it: ";
		getline(cin, searchText);
		cout << "\n\tThe contacts that you are searching for are:";
		while (iterator != NULL)
		{
			if ((searchText.length() < head->firstName.length()) &&
				(head->firstName.find(searchText) < head->firstName.length()))
			{
				cout << "\n\t" << index << ".";
				cout << iterator->lastName << " " << iterator->firstName;
				cout << " " << iterator->phoneNumber << " " << iterator->address;
			}
			iterator = iterator->next;
		}
		break;
	case '3':
		// Search contact by phone number 
		cout << "\n\tIntroduce the phone number or a part of it: ";
		getline(cin, searchText);
		cout << "\n\tThe contacts that you are searching for are:";
		while (iterator != NULL)
		{
			if ((searchText.length() < head->phoneNumber.length()) &&
				(head->phoneNumber.find(searchText) < head->phoneNumber.length()))
			{
				cout << "\n\t" << index << ".";
				cout << iterator->lastName << " " << iterator->firstName;
				cout << " " << iterator->phoneNumber << " " << iterator->address;
			}
			iterator = iterator->next;
		}
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
}

/*
Function used to delete a contact from the phone book
The user will choose from all the contacts, the contact that he wants to delete
*/

void selectContactToDelete(contacts *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tDelete a contact from the phone book";
	if (head == NULL)
	{
		cout << "\n\n\tThe phone book is empty.";
		return;
	}

	contacts *iterator = head;
	short iteratorInt = 0;
	short numberInt = 0;
	string number;

	listContacts(head);
	do
	{
		cout << "\n\n\tIntroduce the number of the contact that you want to delete from the phone book: ";
		getline(cin, number);
	} while ((checkIfNumberCanBeConverted(number) == false) || (number.length() >= 5));

	numberInt = fromStringToInt(number);

	while ((iterator != NULL) && (iteratorInt < numberInt))
	{
		iterator = iterator->next;
		iteratorInt++;
	}

	//If there are contacts in the phone book
	//If the number he introduced is a correct number
	if (iterator != NULL)
	{
		//Checking if the contact is on the first position
		if (iteratorInt == 0)
		{
			if (iterator->next == NULL)
			{
				//Deleting the first contact and the phone book becomes empty
				head = NULL;
			}
			else 
			{
				//Deleting the first contact
				head = head->next;
				head->prev = NULL;
			}
		}
		else
		{
			//Checking if the contact is on the last position
			if (iterator->next == NULL)
			{
				// Deleting the last contact
				iterator->prev->next = NULL;
			}
			else
			{
				//Deleting a contact that is not first and not last
				iterator->next->prev = iterator->prev;
				iterator->prev->next = iterator->next;
			}
		}
		delete iterator;
		cout << "\n\tThe contact has been deleted.";
	}
	else
	{
		cout << "\n\n\tYou introduced a wrong number.";
	}
}

/*
Apply the modifies made on the phone book so
next time when we start the program the phone book will
be actualized
*/

void writeContactsInFile(contacts *&head)
{
	contacts *iterator = head;
	ofstream output("contacts.in");

	while (iterator != NULL)
	{
		output << iterator->lastName << "|" << iterator->firstName << "|";
		output << iterator->phoneNumber << "|" << iterator->address;
		if (iterator->next != NULL)
		{
			output << "\n";
		}
		iterator = iterator->next;
	}

	output.close();
}

int main()
{
	contacts *head = NULL;

	readContactsFromFile(head);
	mainMenu(head);
	writeContactsInFile(head);

	return 0;
}