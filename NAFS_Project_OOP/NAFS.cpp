#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

class Airport;

class Admin
{
protected:
	string CNIC;
	string Name;
	string Password;
public:
	Admin(string cnic = "", string name = "", string password = "")
		:CNIC(cnic), Name(name), Password(password) {}
	
	// Setters
	void setCNIC(string cnic) 
	{ 
		CNIC = cnic; 
	}
	void setName(string name) 
	{ 
		Name = name; 
	}
	void setPassword(string password) 
	{ 
		Password = password; 
	}

	// Getters
	string getCNIC() const 
	{
		return CNIC; 
	}
	string getName() const 
	{ 
		return Name; 
	}
	string getPassword() const 
	{ 
		return Password; 
	}
};

class Passenger : public Admin
{
private:
	bool isVisa;
	bool isPassportValid;
public:
	Passenger(bool visa = 0, bool pass = 0,string cnic = "", string name = "", string password = "")
		: isVisa(visa), isPassportValid(pass), Admin(cnic, name, password) {}
	// getters
	bool getIsVisa() const 
	{
		return isVisa;
	}
	bool getIsPassportValid() const 
	{
		return isPassportValid;
	}
	// setters
	void setIsVisa(bool visa) 
	{
		isVisa = visa;
	}
	void setIsPassportValid(bool pass) 
	{
		isPassportValid = pass;
	}
};

class Seat
{
	//should be abstract
	//takes a passenger details as aggregation
	//must also have a covid thing
protected:
	Passenger& passenger;
	string Name;
	bool isOccupied;
public:
	Seat(Passenger& pass, string name = "", bool occupied = 0)
		:Name(name), isOccupied(occupied), passenger(pass) {}

	// getters
	string getName() const 
	{
		return Name;
	}
	bool getOccupiedStatus() const 
	{
		return isOccupied;
	}
	Passenger getPassenger() const
	{
		return passenger;
	}
	//setters
	void setName(string name)
	{
		Name = name;
	}
	void setOccupied(bool status) 
	{
		isOccupied = status;
	}
	void setPassenger(Passenger& p) 
	{
		passenger = p;
	}
};

//class Buisness : public Seat
//{
//
//};
//
//class Economy : public Seat
//{
//
//};

class Plane
{
	//takes the seats economy and buisness as composition
protected:
	Seat** BuisnessClass;
	Seat** EconomyClass;
public:
	Plane()
	{
		BuisnessClass = new Seat*[10];
		EconomyClass = new Seat*[50];
		for (int i = 0; i < 10; i++)
		{
			Passenger empty;
			BuisnessClass[i] = new Seat(empty);
		}
		for (int i = 0; i < 50; i++)
		{
			Passenger empty;
			EconomyClass[i] = new Seat(empty);
		}
	}

	void ShowAvaliableSeats();
	//keeps check of which are filled and which are not
};

class Flight
{
private:
	Plane& plane;
	bool isLocal;
	int HrsOfFlight;
	int DepartureTime;
	int ArrivalTime;
public:
	Flight(Plane& p, bool local=0, int hrs=0, int depTime=0, int arrTime=0)
		: plane(p), isLocal(local), HrsOfFlight(hrs), DepartureTime(depTime), ArrivalTime(arrTime) {}

	// Getters
	Plane& getPlane() const 
	{
		return plane;
	}
	bool getIsLocal() const 
	{
		return isLocal;
	}
	int getHrsOfFlight() const 
	{
		return HrsOfFlight;
	}
	int getDepartureTime() const 
	{
		return DepartureTime;
	}
	int getArrivalTime() const 
	{
		return ArrivalTime;
	}

	// Setters
	void setPlane(Plane& p) 
	{
		plane = p;
	}
	void setIsLocal(bool local) 
	{
		isLocal = local;
	}
	void setHrsOfFlight(int hrs) 
	{
		HrsOfFlight = hrs;
	}
	void setDepartureTime(int depTime) 
	{
		DepartureTime = depTime;
	}
	void setArrivalTime(int arrTime) 
	{
		ArrivalTime = arrTime;
	}
	//takes a plane aggregation
	//manages a departure time and arrival time for the plane
	//aggregation of a departure airport/country and arrival airport/country
};

class FlightSchedule
{
private:
	Plane plane;
	Flight** Flights;
	int NoOfFlights;
public:
	FlightSchedule(Plane p, int numflights=1): plane(p)
	{
		NoOfFlights = numflights;
		Flights = new Flight * [NoOfFlights];
		for (int i = 0; i < NoOfFlights; i++)
		{
			Flights[i] = new Flight(plane);
		}
	}
	//takes a plane compostion
	//array of flights and puts the plane inside them composition
};

class Airport
{
private:
	Plane* AllPlanes;
	int NoOfPlanes = 0;
	FlightSchedule** ScheduleForPlanes;
	//takes flights as aggregation
public:
	Airport(int noofplanes=1)
	{
		AllPlanes = new Plane[NoOfPlanes];
		ScheduleForPlanes = new FlightSchedule*[NoOfPlanes];
		for (int i = 0; i < NoOfPlanes; i++)
		{
			ScheduleForPlanes[i] = new FlightSchedule(AllPlanes[i]);
		}
	}
};

class City
{
private:
	Airport* North;
	Airport* South;
public:
	City()
	{
		North = new Airport(5);
		South = new Airport(5);
	}
	//composition of two airports namely north and south
};

class Booking
{
private:
	Passenger* RegisteredPassenger;
	City* DepartureCity;
	City* ArrivalCity;
	Seat* seatsSelected;
	bool isFlightDone;
	int TicketPrice;

public:
	Booking(Passenger& p, City& dep, City& arr, bool done = 0, int price = 0) : isFlightDone(done), TicketPrice(price)
	{
		RegisteredPassenger = &p;
		DepartureCity = &dep;
		ArrivalCity = &arr;
		seatsSelected = new Seat(p);
	}

	// getters
	Passenger* getPassenger() const
	{
		return RegisteredPassenger;
	}
	City* getDepartureCity() const
	{
		return DepartureCity;
	}
	City* getArrivalCity() const
	{
		return ArrivalCity;
	}
	Seat* getSeats() const
	{
		return seatsSelected;
	}
	bool getFlightDone() const
	{
		return isFlightDone;
	}
	int getTicketPrice() const
	{
		return TicketPrice;
	}

	// setters
	void setPassenger(Passenger* passenger)
	{
		RegisteredPassenger = passenger;
	}
	void setDepartureCity(City* city)
	{
		DepartureCity = city;
	}
	void setArrivalCity(City* city)
	{
		ArrivalCity = city;
	}
	void setSeats(Seat* seats)
	{
		seatsSelected = seats;
	}
	void setFlightDone(bool done)
	{
		isFlightDone = done;
	}
	void setTicketPrice(int price)
	{
		TicketPrice = price;
	}

	//ask for which city inital
	//which city going to 
	//which airport in the other ciry
	//show flight schedule of the city
	//ask which time 
	//when selected show seats and ask for seats
	//show cost


	//for country have a string array in global of all countries
	//ask if they want to go to another country or another city
	//check for which country later

	//aggregation of country and airport
	//composition of passenger
	//takes a flight from a list of flights for the day
	//takes seats as well
};

/*string CNIC;
	string Name;
	string Password;*/

int NoOfAdmin = 3;
Admin* AllAdmin = new Admin[NoOfAdmin];

int NoOfPassengers = 1;
Passenger* AllPassengers = new Passenger[NoOfPassengers];

Booking* AllBookings;

void GetAdminInfo()
{
	ifstream GetAdmins("Admin.txt");
	string OneAdmin;
	int AdminFlag = 0;
	while (getline(GetAdmins, OneAdmin))
	{
		string SeperateBySpace;
		int AttributeFlag = 0;
		for (int i = 0; i < OneAdmin.length(); i++)
		{
			if (OneAdmin[i] == ' ')
			{
				if (AttributeFlag == 0)
				{
					AttributeFlag++;
					AllAdmin[AdminFlag].setCNIC(SeperateBySpace);
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 1)
				{
					AttributeFlag++;
					AllAdmin[AdminFlag].setName(SeperateBySpace);
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 2)
				{
					AttributeFlag++;
					AllAdmin[AdminFlag].setPassword(SeperateBySpace);
					SeperateBySpace = "";
				}
			}
			SeperateBySpace += OneAdmin[i];
		}
		AdminFlag++;
	}
	GetAdmins.close();
}

void PrintAdmin()
{
	for (int i = 0; i < 3; i++)
	{
		cout << "CNIC: " << AllAdmin[i].getCNIC();
		cout << " Name: " << AllAdmin[i].getName();
		cout << " Password: " << AllAdmin[i].getPassword()<<endl;
	}
}

void PrintPassengers()
{
	for (int i = 0; i < NoOfPassengers; i++)
	{
		cout << "CNIC: " << AllPassengers[i].getCNIC();
		cout << " Name: " << AllPassengers[i].getName();
		cout << " Password: " << AllPassengers[i].getPassword();
		cout << " Is Passport Valid: " << AllPassengers[i].getIsPassportValid();
		cout << " Is there VISA: " << AllPassengers[i].getIsVisa() << endl;
	}
}

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

void AddToFile(Passenger ToBeRegistered)
{
	ofstream AddARegisteredPassenger("Passengers.txt", ios::app);

	AddARegisteredPassenger << ToBeRegistered.getCNIC() << " ";
	AddARegisteredPassenger << ToBeRegistered.getName() << " ";
	AddARegisteredPassenger << ToBeRegistered.getPassword() << " ";
	AddARegisteredPassenger << ToBeRegistered.getIsPassportValid() << " ";
	AddARegisteredPassenger << ToBeRegistered.getIsVisa() << " " << endl;;
	AddARegisteredPassenger.close();
}

void UpdatePassengerArray()
{
	//first deleting original
	delete[] AllPassengers;
	NoOfPassengers = 0;

	//get no of passengers
	ifstream GetNumPass("Passengers.txt");
	string APassenger;
	while (getline(GetNumPass, APassenger))
	{
		NoOfPassengers++;
		cout << NoOfPassengers;
	}
	GetNumPass.close();

	//making the array
	AllPassengers = new Passenger[NoOfPassengers];

	//getting passengers
	ifstream GetPassengers("Passengers.txt");
	int PassengersFlag = 0;
	while (getline(GetPassengers, APassenger))
	{
		string SeperateBySpace;
		int AttributeFlag = 0;
		for (int i = 0; i < APassenger.length(); i++)
		{
			if (APassenger[i] == ' ')
			{
				if (AttributeFlag == 0)
				{
					AttributeFlag++;
					AllPassengers[PassengersFlag].setCNIC(SeperateBySpace);
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 1)
				{
					AttributeFlag++;
					AllPassengers[PassengersFlag].setName(SeperateBySpace);
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 2)
				{
					AttributeFlag++;
					AllPassengers[PassengersFlag].setPassword(SeperateBySpace);
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 3)
				{
					AttributeFlag++;
					AllPassengers[PassengersFlag].setIsPassportValid(stoi(SeperateBySpace));
					SeperateBySpace = "";
				}
				else if (AttributeFlag == 4)
				{
					AttributeFlag++;
					AllPassengers[PassengersFlag].setIsVisa(stoi(SeperateBySpace));
					SeperateBySpace = "";
				}
			}
			SeperateBySpace += APassenger[i];
		}
		PassengersFlag++;
	}
	GetPassengers.close();
}

void Register()
{
	Passenger ToBeRegistered;

	//get name
	cout << "Enter you name: ";
	string name;
	cin.ignore();
	getline(cin, name);
	ToBeRegistered.setName(name);

	//gets cnic
	string CNIC;
	do
	{
		cout << "Enter CNIC: ";
		cin.ignore();//might cause problem
		getline(cin, CNIC);
		if (UserExists(CNIC) == 1)
		{
			cout << "\nThe CNIC Already exists please enter a new one\n";
		}
	} while (UserExists(CNIC) == 1);
	ToBeRegistered.setCNIC(CNIC);

	//gets password
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
	ToBeRegistered.setPassword(PasswordOriginal);

	//asking for passport
	char haspassport;
	do
	{
		cout << "Do You have passport?\n";
		cout << "Press 1 for yes\n";
		cout << "Press 2 for no\n";
		cin >> haspassport;
		if (haspassport != '1' && haspassport != '2')
		{
			cout << "Invalid input\n";
			continue;
		}
		else if (haspassport == '1')
		{
			ToBeRegistered.setIsPassportValid(1);
		}
		else if (haspassport == '2')
		{
			ToBeRegistered.setIsPassportValid(0);
		}
	} while (haspassport != '1' && haspassport != '2');

	char hasvisa;
	do
	{
		cout << "Do You have visa?\n";
		cout << "Press 1 for yes\n";
		cout << "Press 2 for no\n";
		cin >> hasvisa;
		if (hasvisa != '1' && hasvisa != '2')
		{
			cout << "Invalid input\n";
			continue;
		}
		else if (hasvisa == '1')
		{
			ToBeRegistered.setIsVisa(1);
		}
		else if (hasvisa == '2')
		{
			ToBeRegistered.setIsVisa(0);
		}
	} while (hasvisa != '1' && hasvisa != '2');
	
	AddToFile(ToBeRegistered);
	UpdatePassengerArray();

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
	GetAdminInfo();
	UpdatePassengerArray();
	PrintPassengers();
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