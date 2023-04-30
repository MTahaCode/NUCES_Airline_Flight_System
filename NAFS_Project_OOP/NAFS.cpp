#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

class Airport;

class User
{
	
};

class Admin : public User
{

};

class Passenger : public User
{

};

class Seat
{
	//should be abstract
	//takes a passenger details as aggregation
	//must also have a covid thing
};

class Buisness : public Seat
{

};

class Economy : public Seat
{

};

class Plane
{
	//takes the seats economy and buisness as composition
	//keeps check of which are filled and which are not
};

class Flight
{
	//takes a plane aggregation
	//manages a departure time and arrival time for the plane
	//aggregation of a departure airport/country and arrival airport/country
};

class FlightSchedule
{
	//takes a plane compostion
	//array of flights and puts the plane inside them composition
};

class Airport
{
	//takes flights as aggregation
};

class City
{
	//composition of two airports namely north and south
};

class Booking
{
	//aggregation of country and airport
	//composition of passenger
	//takes a flight from a list of flights for the day
	//takes seats as well
};

int NoOfAdmin = 3;
int NoOfPassengers = 5;
Admin* AllAdmin = new Admin[NoOfAdmin];
Passenger* AllPassengers = new Passenger[NoOfPassengers];
Booking* AllBookings = new Booking[5];
//should have a outside function to change their size
//should also allow to save in file

void VerifyFinancialDetail()
{

}

bool AdminExists(string login)
{
	//check through the admins
	return 0;
}

bool PassengerExists(string login)
{
	//check through the passengers cnic
	return 0;
}

bool UserExists(string login)
{
	if (AdminExists(login) == 1 || PassengerExists(login) == 1)
	{
		return 1;
	}
	return 0;
}

bool isValidPassword(string password)
{
	//check for special
	string specialChars = "!@#$%^&*()_+-={}[]|\\:;\"'<>,.?/~`";
	bool specialExists = 0;
	bool upperExists = 0;
	bool lowerExists = 0;
	bool numbersExist = 0;
	for (int i = 0; i < specialChars.length(); i++)
	{
		for (int j = 0; j < password.length(); j++)
		{
			if (specialChars[i] == password[j])
			{
				specialExists = 1;
			}
		}
	}
	//check for upper, lower, numbers
	for (int i = 0; i < password.length(); i++)
	{
		if (upperExists==0 && password[i] >= 'A' && password[i] <= 'Z')
		{
			upperExists = 1;
		}
		if (lowerExists == 0 && password[i] >= 'a' && password[i] <= 'z')
		{
			lowerExists = 1;
		}
		if (numbersExist == 0 && password[i] >= '0' && password[i] <= '9')
		{
			numbersExist = 1;
		}
	}
	if (specialExists == 0)
	{
		cout << "\nShould have special Characters\n";
	}
	if (upperExists == 0)
	{
		cout << "\nShould have uppercase Characters\n";
	}
	if (lowerExists == 0)
	{
		cout << "\nShould have lowercase Characters\n";
	}
	if (numbersExist == 0)
	{
		cout << "\nShould have numbers\n";
	}
	if (specialExists == 1 && upperExists == 1 && lowerExists == 1 && numbersExist == 1)
	{
		return 1;
	}
	return 0;
}

void Register()
{
	//ask for cnic
	// check if this cnic doesnt already exist as a registered one
	// 
	//ask for password
	//ask to renter password
	//if both dont match say the passwords dont match please reenter passwords
	//after correct password check 
	
	string LoginCNIC;
	do
	{
		cout << "Enter CNIC: ";
		cin.ignore();
		getline(cin, LoginCNIC);
		if (UserExists(LoginCNIC) == 1)
		{
			cout << "\nThe CNIC Already exists please enter a new one\n";
		}
	} while (UserExists(LoginCNIC) == 1);

	string PasswordOriginal;
	string PasswordAgain;
	bool same;
	do
	{
		same = 1;
		cout << "Enter New Password: ";
		getline(cin, PasswordOriginal);
		
		cout << "Enter Password Again:";
		getline(cin, PasswordAgain);
		if (PasswordOriginal != PasswordAgain)
		{
			cout << "\nThe two passwords are not same. Enter Again\n";
			same = 0;
		}
	} while (!isValidPassword(PasswordOriginal) || !same);

	//ask for financial details
	//need to add to the arrays code still left

}

void Login()
{
	string LoginName;
	cout << "Enter your account login name: ";
	cin.ignore();
	getline(cin, LoginName);

	string Password;
	cout << "Enter your account password: ";
	cin.ignore();
	getline(cin, Password);

	//have to login to special thing
	//can make a function that would search for both admins and passengers and allows 0 if not found and 1 if admin and 2 if passenger
	//for the admin same for everyone
	//for the passengers we will make a template and add values there regarding each passenger
}

int main()
{
	bool Exit = 0;
	while (!Exit)
	{
		char MainSelection = 0;
		cout << "Welcome to NUCES Airline Flight System\n";
		cout << "To Login Press 1\n";
		cout << "To Register Press 2\n";
		cout << "For Basic Details Press 3\n";
		cout << "To Exit Press 4\n==>";
		cin >> MainSelection;
		switch (MainSelection)
		{
		case '1':
		{
			Login();
			break;
		}
		case '2':
		{
			Register();
			break;
		}
		case '3':
		{
			cout<<"BasicDetails()";
			break;
		}
		case '4':
		{
			return 0;
			break;
		}
		default:
			cout << "Invalid Selection\n";
			Sleep(1000);
			system("cls");
			break;
		}
	}
	


	return 0;
}