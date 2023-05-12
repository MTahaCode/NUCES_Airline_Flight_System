/*i221547 M Taha Makhdoom*/
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

//pointer declaration 
class City;
City* Cities;

//this is the flight class
class Flight
{
private:
	bool isLocal;
	int HrsOfFlight;
	int DepartureTime;
	int ArrivalTime;
	string DepartureAirport;
	string ArrivalAirport;
	bool* EconomyOccupied;//this and below consist of condititons for occupation and restriction of the clases
	bool* BuisnessOccupied;
	bool* EconomyRestricted;
	bool* BuisnessRestricted;
public:
	Flight(string arr="", string dep="", bool local = 0, int hrs = 0, int depTime = 0, int arrTime = 0)
		: isLocal(local), HrsOfFlight(hrs), DepartureTime(depTime), ArrivalTime(arrTime), DepartureAirport(dep), ArrivalAirport(arr) 
	{
		EconomyOccupied = new bool[50];
		BuisnessOccupied = new bool[10];

		EconomyRestricted = new bool[50];
		BuisnessRestricted = new bool[10];

		for (int i = 0; i < 10; i++)
		{
			BuisnessOccupied[i] = 0;
			BuisnessRestricted[i] = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			EconomyOccupied[i] = 0;
			EconomyRestricted[i] = 0;
		}
	}

	//this caused error so it was removed
	/*~Flight()
	{
		delete[] EconomyOccupied;
		delete[] BuisnessOccupied;
		delete[] EconomyRestricted;
		delete[] BuisnessRestricted;
	}*/

	// Getters
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
	string getDepAirport() const
	{
		return DepartureAirport;
	}
	string getArrAirport() const
	{
		return ArrivalAirport;
	}
	bool getOccupiedEconomyAtIndex(int index) const 
	{
		return EconomyOccupied[index];
	}
	bool getOccupiedBuisnessAtIndex(int index) const 
	{
		return EconomyOccupied[index];
	}
	bool getRestrictedBuisnessAtIndex(int index) const
	{
		return BuisnessRestricted[index];
	}
	bool getRestrictedEconomyAtIndex(int index)
	{
		return EconomyRestricted[index];
	}

	// Setters
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
	void setDepAirport(string dep)
	{
		DepartureAirport = dep;
	}
	void setArrAirport(string arr)
	{
		ArrivalAirport = arr;
	}
	void setOccupiedEconomyAtIndex(int index, bool condition)
	{
		EconomyOccupied[index] = condition;
	}
	void setOccupiedBuisnessAtIndex(int index, bool condition)
	{
		EconomyOccupied[index] = condition;
	}
	
	void RestrictAllSeats()
	{
		for (int i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
			{
				BuisnessRestricted[i] = 1;
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (i % 2 == 0)
			{
				EconomyRestricted[i] = 1;
			}
		}
	}
	void UnRestrictSeats()
	{
		for (int i = 0; i < 10; i++)
		{
			BuisnessRestricted[i] = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			EconomyRestricted[i] = 0;
		}
	}

	friend ostream& operator<<(ostream& op, const Flight& flight);

	bool operator==(const Flight& flight)
	{
		if (this->ArrivalAirport == flight.ArrivalAirport && this->DepartureAirport == flight.DepartureAirport &&
			this->ArrivalTime == flight.ArrivalTime && this->DepartureTime == flight.DepartureTime)
		{
			return 1;
		}
		return 0;
	}
	//takes a plane aggregation
	//manages a departure time and arrival time for the plane
	//aggregation of a departure airport/country and arrival airport/country
};
ostream& operator<<(ostream& op, const Flight& flight)
{
	op << "Is Local: " << flight.isLocal;
	op << " Flight Hours: " << flight.HrsOfFlight;
	op << " Departure Time: " << flight.DepartureTime;
	op << " Arrival Time: " << flight.ArrivalTime;
	op << " Arrival Airport: " << flight.ArrivalAirport;
	op << " Departure Airport: " << flight.DepartureAirport;
	op << endl;
	return op;
}

//this is Admin Class
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

//this is passenger class inheriting from Admin
class Passenger : public Admin
{
private:
	bool isVisa;
	bool isPassportValid;
public:
	Passenger(bool visa = 0, bool pass = 0, string cnic = "", string name = "", string password = "")
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

//this is the seat class
class Seat 
{
protected:
	Passenger& passenger;//aggregation
	const string Name;
public:
	Seat(Passenger& pass, string name = "", bool occupied = 0, bool restrict = 0)
		:Name(name), passenger(pass) {}

	// getters
	string getName() const
	{
		return Name;
	}
	Passenger getPassenger() const
	{
		return passenger;
	}

	//setters
	void setPassenger(Passenger& p)
	{
		passenger = p;
	}

	friend ostream& operator<<(ostream& op, const Seat& seat);
};
ostream& operator<<(ostream& op, const Seat& seat)
{
	op << "Name: " << seat.Name;
	return op;
}

//this is the plane class
class Plane
{
protected:
	string Name;
	Seat** BuisnessClass;//composition
	Seat** EconomyClass;//composition
	static int NoOfPlanes;
	int arraysize;
	int NoOfFlights;
	Flight* Schedule;//composition
	bool isPresent(const Flight& flight)
	{
		//checks if the schedule is present
		for (int i = 0; i < arraysize; i++)
		{
			if (Schedule[i] == flight)
			{
				return 1;
			}
		}
		return 0;
	}
	bool isArrayFilled()
	{
		Flight empty;
		for (int i = 0; i < NoOfFlights; i++)
		{
			if (Schedule[i] == empty)
			{
				return 0;
			}
		}
		return 1;
	}
	void increaseArray()
	{
		Flight* temp = new Flight[arraysize];
		for (int i = 0; i < arraysize; i++)
		{
			temp[i] = Schedule[i];
		}
		delete[] Schedule;
		arraysize++;
		Schedule = new Flight[arraysize];
		for (int i = 0; i < arraysize - 1; i++)
		{
			Schedule[i] = temp[i];
		}
		delete[] temp;
	}
	void FixArray()
	{
		for (int i = 0; i < arraysize; i++)
		{
			if (i + 1 != arraysize && Schedule[i].getArrAirport() == "")
			{
				Flight temp = Schedule[i];
				Schedule[i] = Schedule[i + 1];
				Schedule[i + 1] = temp;
			}
		}
	}
public:
	Plane(int size= 1)
	{
		arraysize = size;
		Schedule = new Flight[arraysize];
		NoOfFlights = 0;
		NoOfPlanes++;
		BuisnessClass = new Seat * [10];
		EconomyClass = new Seat * [50];
		int buisness=0;
		for (int i = 0; i < 10; i++)
		{
			Passenger empty;
			BuisnessClass[i] = new Seat(empty,"A"+to_string(buisness++));
		}
		int economy = 0;
		for (int i = 0; i < 50; i++)
		{
			Passenger empty;
			if (i < 10)
			{
				string str = "B";
				str.append("0");
				str.append(to_string(economy));
				EconomyClass[i] = new Seat(empty, str);
			}
			else
			{
				EconomyClass[i] = new Seat(empty, "B" + to_string(economy));
			}
			economy++;
		}
		Name = "Plane" + to_string(NoOfPlanes);
	}
	string getPlaneName()
	{
		return Name;
	}
	//to add or remove flights
	void AddFlight(const Flight& flight)
    {
		if (isArrayFilled())
		{
			increaseArray();
		}
        if (isPresent(flight))
        {
            cout << "Flight is already present\n";
            return;
        }
		else
		{
			for (int i = 0; i < arraysize; i++)
			{
				Flight empty;
				if (Schedule[i] == empty)
				{
					Schedule[i] = flight;
					break;
				}
			}
			NoOfFlights++;
		}
    }
	void RemoveFlight(const Flight& flight)
	{
		if (!isPresent(flight))
		{
			cout << "The Flight is not present \n";
		}
		for (int i = 0; i < NoOfFlights; i++)
		{
			if (Schedule[i] == flight)
			{
				Flight empty;
				Schedule[i] = empty;
				NoOfFlights--;
				FixArray();
			}
		}
	}
	//to change restriction of seats
	void RestrictSeats()
	{
		for (int j = 0; j < NoOfFlights; j++)
		{
			Schedule[j].RestrictAllSeats();
		}
	}
	void UnRestrictSeats()
	{
		for (int j = 0; j < NoOfFlights; j++)
		{
			Schedule[j].UnRestrictSeats();
		}
	}
	void ShowSeats()
	{
		for (int j = 0; j < NoOfFlights; j++)
		{
			cout << "Buisness Class:\n";
			for (int i = 0; i < 10; i++)
			{
				cout << *BuisnessClass[i];
				cout << " Restricted Status:" << Schedule[j].getRestrictedBuisnessAtIndex(i) << endl;
			}
			cout << "Economy Class:\n";
			for (int i = 0; i < 50; i++)
			{
				cout << *EconomyClass[i];
				cout << " Restricted Status:" << Schedule[j].getRestrictedEconomyAtIndex(i) << endl;
			}
		}
	}
	//for finding the seats
	Seat* FindSeat(string seatName)
	{
		for (int i = 0; i < 10; i++)
		{
			if (BuisnessClass[i]->getName() == seatName)
			{
				return BuisnessClass[i];
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (EconomyClass[i]->getName() == seatName)
			{
				return EconomyClass[i];
			}
		}
		Passenger pass;
		Seat empty(pass);
		return &empty;
	}
	friend ostream& operator<<(ostream& op, const Plane& plane);
	friend void InitializaingDummySchedules();
	Flight& GetScheduleAtIndex(int index)
	{
		return Schedule[index];
	}
	int GetNoOfFlights() const
	{
		return NoOfFlights;
	}

	void ShowAvaliableSeats(int flightIndex)
	{
		cout << "\nBuisness Seats:\n";
		for (int i = 0; i < 10; i++)
		{
			if (!Schedule[flightIndex].getOccupiedBuisnessAtIndex(i) || !Schedule[flightIndex].getRestrictedBuisnessAtIndex(i))
			{
				cout << BuisnessClass[i]->getName()<<" ";
			}
		}

		cout << "\nEconomy Seats:\n";
		for (int i = 0; i < 50; i++)
		{
			if (!Schedule[flightIndex].getOccupiedEconomyAtIndex(i) || !Schedule[flightIndex].getRestrictedBuisnessAtIndex(i))
			{
				cout << EconomyClass[i]->getName() <<" ";
			}
		}
	}
};
ostream& operator<<(ostream& op, const Plane& plane)
{
	op << "Name: " << plane.Name << endl;
	for (int i = 0; i < plane.NoOfFlights; i++)
	{
		op << plane.Schedule[i];
	}
	return op;
}
int Plane::NoOfPlanes = 0;

//this is Airport Class
class Airport
{
protected:
	const string Name;
	Plane* AllPlanes;//composition
	int NoOfPlanes = 0;
public:
	Airport(string name = "", int noofplanes = 1) : Name(name)
	{
		NoOfPlanes = noofplanes;
		AllPlanes = new Plane[NoOfPlanes];
	}
	string getName()
	{
		return Name;
	}
	Airport(const Airport& other)
	{
		NoOfPlanes = other.NoOfPlanes;

		AllPlanes = new Plane[NoOfPlanes];
		for (int i = 0; i < NoOfPlanes; i++)
		{
			AllPlanes[i] = other.AllPlanes[i];
		}

		/*ScheduleForPlanes = new FlightSchedule * [NoOfPlanes];
		for (int i = 0; i < NoOfPlanes; i++)
		{
			ScheduleForPlanes[i] = new FlightSchedule(*other.ScheduleForPlanes[i]);
		}*/
	}
	friend ostream& operator<<(ostream& op, const Airport& air);
	friend void InitializaingDummySchedules();
	friend void ChangeSchedule();
	friend void RestrictPassengers(bool ToRestrict);
	//getters
	Plane& GetPlaneAtIndex(int index)
	{
		return AllPlanes[index];
	}
	int GetNoOfPlanes()
	{
		return NoOfPlanes;
	}
};
ostream& operator<<(ostream& op, const Airport& air)
{

	for (int i = 0; i < air.NoOfPlanes; i++)
	{
		op << air.AllPlanes[i];
	}
	return op;
}

//This is the City Class
class City
{
private:
	const string Name;
	Airport* North;//composition
	Airport* South;//composition
public:
	City(string name="") : Name(name)
	{
		North = new Airport("North", 5);
		South = new Airport("South",5);
	}
	string getName()
	{
		return Name;
	}
	Airport* getNorth()
	{
		return North;
	}
	Airport* getSouth()
	{
		return South;
	}

	friend ostream& operator<<(ostream& op, const City& city);
	friend void InitializaingDummySchedules();
	friend void ChangeSchedule();
	friend void RestrictPassengers(bool ToRestrict);
	void ShowScheduleGoingTo(int cityArrSelection, int cityDepSelection)
	{
		//for north one
		cout << "In the North Airport:\n";
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < North->GetPlaneAtIndex(i).GetNoOfFlights(); j++)
			{
				if (North->GetPlaneAtIndex(i).GetScheduleAtIndex(j).getArrAirport() == Cities[cityArrSelection].Name &&
					North->GetPlaneAtIndex(i).GetScheduleAtIndex(j).getDepAirport() == Cities[cityDepSelection].Name)
				{
					cout << North->GetPlaneAtIndex(i).GetScheduleAtIndex(j);
				}
			}
		}

		cout << "In the South Airport:\n";
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < North->GetPlaneAtIndex(i).GetNoOfFlights(); j++)
			{
				if (South->GetPlaneAtIndex(i).GetScheduleAtIndex(j).getArrAirport() == Cities[cityArrSelection].Name &&
					South->GetPlaneAtIndex(i).GetScheduleAtIndex(j).getDepAirport() == Cities[cityDepSelection].Name)
				{
					cout << South->GetPlaneAtIndex(i).GetScheduleAtIndex(j);
				}
			}
		}
	}
};
ostream& operator<<(ostream& op, const City& city)
{
	
	op <<"North:\n" << *city.North;
	op <<"South:\n" << *city.South;
	return op;
}

//this is the booking class
class Booking
{
private:
	Passenger* RegisteredPassenger;//aggregation
	City* DepartureCity;//aggregation
	City* ArrivalCity;//aggregation
	Airport* DepartureAirport;//aggregation
	Seat* seatsSelected;//aggregation
	Flight* flightSelected;//aggregation
	bool isFlightDone;
	int TicketPrice;

public:
	Booking(Passenger* p, City* dep, City* arr, Airport* depAirport, Seat* seat, Flight* flight, int price = 0) : TicketPrice(price)
	{
		RegisteredPassenger = p;
		DepartureCity = dep;
		ArrivalCity = arr;
		seatsSelected = seat;
		DepartureAirport = depAirport;
		flightSelected = flight;
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

	friend ostream& operator<<(ostream& op, const Booking& booking);
};
ostream& operator<<(ostream& op, const Booking& booking)
{
	op << "Passenger: " << booking.RegisteredPassenger->getName() << endl;
	op << "Departure City: " << booking.DepartureCity->getName() << endl;
	op << "Arrival City: " << booking.ArrivalCity->getName() << endl;
	op << "Departure Airport: " << booking.DepartureAirport->getName() << endl;
	op << "Seats Selected: " << booking.seatsSelected->getName() << endl;
	op << "Is The Flight Done: " << booking.isFlightDone << endl;
	op << "Ticket Price: " << booking.TicketPrice << endl;
	return op;
}
//initialization of Admins
int NoOfAdmin = 3;
Admin* AllAdmin = new Admin[NoOfAdmin];
//Initilization of Passengers
int NoOfPassengers = 1;
Passenger* AllPassengers = new Passenger[NoOfPassengers];
//stores bookings
int TotalBookings = 0;
Booking** AllBookings = NULL;

//initializes all the info
void GetAdminInfo();
void UpdatePassengerArray();
void InitializaingDummySchedules();

//a function that is too complex to implement
void VerifyFinancialDetail();

//basic functions necessary for login
bool AdminExists(string login);
bool PassengerExists(string login);
bool UserExists(string login);
bool isValidPassword(string password);
int FindInAdmin(string CNIC);
int FindInPassengers(string CNIC);
void Login();

//functions for register
void AddToFile(Passenger ToBeRegistered);
void Register();

//Fucnctions for testing and displaying
void DisplayPlanesInCity();
void ShowBookings();
void PrintAdmin();
void PrintPassengers();

//Admin Fuctions
void ChangeSchedule();
void RestrictPassengers(bool ToRestrict);
void AdminFunction();

//passenger functions
void AddBooking(Booking& NewBooking);
void MakeBooking(Passenger& passenger);
void PassengerFunction(Passenger& passenger);

int main()
{
	//initializes
	Cities = new City[5]{ City("Islamabad"), City("Lahore"), City("Quetta"), City("Peshawar"), City("Karachi") };
	InitializaingDummySchedules();
	GetAdminInfo();
	UpdatePassengerArray();
	//print passengers and admins
	cout << "\nList of All the Passengers:\n";
	PrintPassengers();

	cout << "\nList of All the Admins:\n";
	PrintAdmin();
	bool Exit = 0;
	while (!Exit)
	{
		char MainSelection = 0;
		cout << "\nWELCOME TO NUCES AIRLINE FLIGHT SYSTEM\n";
		cout << "To Login Press 1\n";
		cout << "To Register Press 2\n";
		cout << "For Basic Details Press 3\n";
		cout << "To Exit Press 4\n==>";
		cin.get(MainSelection);
		switch (MainSelection)
		{
		case '1':
		{
			//for login
			Login();
			break;
		}
		case '2':
		{
			//for registration
			Register();
			break;
		}
		case '3':
		{
			//basic details
			cout<<"BasicDetails()";
			break;
		}
		case '4':
		{
			return 0;
			break;
		}
		default:
			cout << "Invalid Selection. Wait a few seconds.\n";
			Sleep(1000);
			system("cls");
			break;
		}
	}
	
	//deleting bookings;
	for (int i = 0; i < TotalBookings; i++)
	{
		delete[] AllBookings[i];
	}
	delete[] AllBookings;

	//deleting passengers and admin
	delete[] AllAdmin;
	delete[] AllPassengers;
	
	return 0;
}

//this is function that does everything related to passengers
void PassengerFunction(Passenger& passenger)
{
	bool Exit = 0;
	while (!Exit)
	{
		//asking for functinos and doing the respective thing
		cout << "To make a booking Press 1\n";
		cout << "To Change Passport avaliability Press 2\n";
		cout << "To Change VISA avaliability Press 3\n";
		cout << "To ask for route details Press 4\n";
		cout << "To Update Airline Inquiry Press 5\n";
		cout << "To go Back Press 6\n==>";
		char Selection = 0;
		cin >> Selection;
		switch (Selection)
		{
		case '1':
		{
			//for making booking
			MakeBooking(passenger);
			break;
		}
		case '2':
		{
			//for changing passport status
			char Selection;
			do
			{
				Selection = 0;
				cout << "What is Passport Status:\n";
				cout << "1) Valid\n";
				cout << "2) Not Valid\n";
				cin >> Selection;
				cout << Selection;
				if (Selection < '1' || Selection > '2')
				{
					cout << "Invalid\n";
				}
			} while (Selection < '1' || Selection > '2');
			if (Selection == '1')
			{
				passenger.setIsPassportValid(1);
			}
			else if (Selection == '2')
			{
				passenger.setIsPassportValid(0);
			}
			break;
		}
		case '3':
		{
			//change visa status
			char Selection;
			do
			{
				Selection = 0;
				cout << "What is VISA Status:\n";
				cout << "1) Valid\n";
				cout << "2) Not Valid\n";
				cin >> Selection;
				cout << Selection;
				if (Selection < '1' || Selection > '2')
				{
					cout << "Invalid\n";
				}
			} while (Selection < '1' || Selection > '2');
			if (Selection == '1')
			{
				passenger.setIsVisa(1);
			}
			else if (Selection == '2')
			{
				passenger.setIsVisa(0);
			}
			break;
		}
		case '4':
		{
			//route details
			cout << "Route Details\n";
			break;
		}
		case '5':
		{
			//airline inquiry
			cout << "Updating Airline Inquiry";
			break;
		}
		case '6':
		{
			return;
			break;
		}
		default:
		{
			cout << "Invalid Selection. Wait a few seconds.\n";
			Sleep(1000);
			system("cls");
			break;
		}
		}
	}

	// 
	// 
	// 
	// 
	//change routes for the planes
	// restrict no of passengers in a plane
	//update airline inquiry details
}
//for making bookings
void MakeBooking(Passenger& passenger)
{
	//all the indexes and pointers to various things used ahead
	int cityArrSelection = -1;
	int cityDepSelection = -1;
	int DepTime = -1;
	bool NorthOrSouth = 0;
	Seat* SeatFound = NULL;
	Flight* FlightFound = NULL;
	int FlightIndex = -1;
	int PlaneIndex = 1;
	int Ticket = 0;
	//asking for city initial
	char Selection = 0;
	do
	{
		Selection = 0;
		cout << "Which City are you departing from\n";
		cout << "1) Islamabad\n";
		cout << "2) Lahore\n";
		cout << "3) Quetta\n";
		cout << "4) Peshawar\n";
		cout << "5) Karachi\n";
		cin >> Selection;
		cout << Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			cityDepSelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');

	//asking for city after
	do
	{
		Selection = 0;
		cout << "Which City are you going to:\n";
		cout << "1) Islamabad\n";
		cout << "2) Lahore\n";
		cout << "3) Quetta\n";
		cout << "4) Peshawar\n";
		cout << "5) Karachi\n";
		cin >> Selection;
		cout << Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			cityArrSelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');

	//asking for the airport
	do
	{
		Selection = 0;
		cout << "Which Airport are you at:\n";
		cout << "1) North\n";
		cout << "2) South\n";
		cin >> Selection;
		cout << Selection;
		if (Selection < '1' || Selection > '2')
		{
			cout << "Invalid\n";
		}
		else
		{
			NorthOrSouth = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '2');

	//showing schedule
	cout << "Schedule of the city:\n";
	Cities[cityDepSelection].ShowScheduleGoingTo(cityArrSelection, cityDepSelection);

	//asking for time
	int time = 0;
	do
	{
		Selection = 0;
		cout << "Enter Time According to Schedule: ";
		cin >> time;
		if (time < 0)
		{
			cout << "Invalid\n";
		}
		else
		{
			DepTime = time;
		}
	} while (time < 0);

	//now showing all avaliable seats
	for (int i = 0; i < 5; i++)
	{
		bool Break1 = 0;

		if (!NorthOrSouth)
		{
			for (int j = 0; j < Cities[i].getNorth()->GetNoOfPlanes(); i++)
			{
				bool Break2 = 0;
				cout << "For the North Airport:\n";
				for (int k = 0; k < Cities[i].getNorth()->GetPlaneAtIndex(j).GetNoOfFlights(); k++)
				{
					if (time == Cities[i].getNorth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k).getDepartureTime())
					{
						Cities[i].getNorth()->GetPlaneAtIndex(j).ShowAvaliableSeats(k);
						FlightIndex = k;
						PlaneIndex = j;
						Break2 = 1;
						break;
					}
				}
				if (Break2)
				{
					Break1 = 1;
					break;
				}
			}
		}
		else
		{
			for (int j = 0; j < Cities[i].getSouth()->GetNoOfPlanes(); i++)
			{
				bool Break2 = 0;
				cout << "For the South Airport:\n";
				for (int k = 0; k < Cities[i].getSouth()->GetPlaneAtIndex(j).GetNoOfFlights(); k++)
				{
					if (time == Cities[i].getSouth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k).getDepartureTime())
					{
						Cities[i].getSouth()->GetPlaneAtIndex(j).ShowAvaliableSeats(k);
						FlightIndex = k;
						PlaneIndex = j;
						Break2 = 1;
						break;
					}
				}
				if (Break2)
				{
					Break1 = 1;
					break;
				}
			}
		}
		if (Break1)
		{
			break;
		}
	}

	//running for wrong or occupied seat
	while (1)
	{
		string SeatName;
		cout << "Enter Seat Name: ";
		cin >> SeatName;

		//finding the seat name
		for (int i = 0; i < 5; i++)
		{
			bool Break1 = 0;
			if (!NorthOrSouth)
			{
				for (int j = 0; j < Cities[i].getNorth()->GetNoOfPlanes(); i++)
				{
					bool Break2 = 0;
					cout << "For the North Airport:\n";
					for (int k = 0; k < Cities[i].getNorth()->GetPlaneAtIndex(j).GetNoOfFlights(); k++)
					{
						if (time == Cities[i].getNorth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k).getDepartureTime())
						{
							SeatFound = Cities[i].getNorth()->GetPlaneAtIndex(j).FindSeat(SeatName);
							FlightFound = &Cities[i].getNorth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k);
							Break2 = 1;
							break;
						}
					}
					if (Break2)
					{
						Break1 = 1;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < Cities[i].getSouth()->GetNoOfPlanes(); i++)
				{
					bool Break2 = 0;
					cout << "For the South Airport:\n";
					for (int k = 0; k < Cities[i].getSouth()->GetPlaneAtIndex(j).GetNoOfFlights(); k++)
					{
						if (time == Cities[i].getSouth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k).getDepartureTime())
						{
							SeatFound = Cities[i].getSouth()->GetPlaneAtIndex(j).FindSeat(SeatName);
							FlightFound = &Cities[i].getNorth()->GetPlaneAtIndex(j).GetScheduleAtIndex(k);
							Break2 = 1;
							break;
						}
					}
					if (Break2)
					{
						Break1 = 1;
						break;
					}
				}
			}
			if (Break1)
			{
				break;
			}
		}

		//doing other things
		if (SeatFound->getName() == "")
		{
			cout << "Seat Not Found\n";
			continue;
		}
		if ((SeatFound->getName()[0] == 'A' && FlightFound->getOccupiedBuisnessAtIndex(SeatFound->getName()[1] - '0')))
		{
			cout << SeatFound->getName()[1] - '0';
			cout << "This Seat is Occupied\n";
			continue;
		}
		else if (SeatFound->getName()[0] == 'B' && FlightFound->getOccupiedBuisnessAtIndex((10 * SeatFound->getName()[1] - '0') + (SeatFound->getName()[2] - '0')))
		{
			cout << (10 * (SeatFound->getName()[1] - '0')) + (SeatFound->getName()[2] - '0');
			cout << "This Seat is Occupied\n";
			continue;
		}
		if (SeatFound->getName()[0] == 'A' && FlightFound->getRestrictedBuisnessAtIndex(SeatFound->getName()[1] - '0')
			|| (SeatFound->getName()[0] == 'B' && FlightFound->getRestrictedBuisnessAtIndex((10 * SeatFound->getName()[1] - '0') + (SeatFound->getName()[2] - '0'))))
		{
			cout << "This Seat is Restricted\n";
			continue;
		}

		if (SeatName[0] = 'A')
		{
			FlightFound->setOccupiedBuisnessAtIndex(SeatFound->getName()[1] - '0', 1);
		}
		else
		{
			FlightFound->setOccupiedEconomyAtIndex((10 * SeatFound->getName()[1] - '0') + (SeatFound->getName()[2] - '0'), 1);
		}
		break;
	}
	//checking for passport
	if (!passenger.getIsPassportValid())
	{
		cout << "Your Passport is not Valid\n";
		return;
	}
	//showing cost
	cout << "The cost for this Seat is: ";
	if (FlightFound->getIsLocal())
	{
		Ticket = FlightFound->getHrsOfFlight() * 20000;
		cout << FlightFound->getHrsOfFlight() * 20000;
	}
	else
	{
		Ticket = FlightFound->getHrsOfFlight() * 10000;
		cout << FlightFound->getHrsOfFlight() * 10000;
	}
	//adding booking
	if (!NorthOrSouth)
	{
		Booking* NewBooking = new Booking(&passenger, &Cities[cityArrSelection], &Cities[cityDepSelection], Cities[cityDepSelection].getNorth(), SeatFound, FlightFound, Ticket);
		AddBooking(*NewBooking);
	}
	else
	{
		Booking* NewBooking = new Booking(&passenger, &Cities[cityArrSelection], &Cities[cityDepSelection], Cities[cityDepSelection].getSouth(), SeatFound, FlightFound, Ticket);
		AddBooking(*NewBooking);
	}
}
//adds a booking to the booking array
void AddBooking(Booking& NewBooking)
{
	Booking** temp = new Booking * [TotalBookings];
	for (int i = 0; i < TotalBookings; i++)
	{
		temp[i] = AllBookings[i];
	}
	delete[] AllBookings;
	TotalBookings++;
	AllBookings = new Booking * [TotalBookings];
	for (int i = 0; i < TotalBookings - 1; i++)
	{
		AllBookings[i] = temp[i];
	}
	AllBookings[TotalBookings - 1] = &NewBooking;
	delete[] temp;
}
//does everything related to Admin
void AdminFunction()
{
	bool Exit = 0;
	while (!Exit)
	{
		//asks
		cout << "To Change Schedule Press 1\n";
		cout << "To Restrict No Of Passengers in a plane Press 2\n";
		cout << "To UnRestrict No Of Passengers in a plane Press 3\n";
		cout << "To Update Airline Inquiry Press 4\n";
		cout << "To go Back Press 5\n==>";
		char Selection = 0;
		cin >> Selection;
		switch (Selection)
		{
		case '1':
		{
			//to change schedule
			ChangeSchedule();
			break;
		}
		case '2':
		{
			//to restrict 
			RestrictPassengers(1);
			break;
		}
		case '3':
		{
			//to unrestrict
			RestrictPassengers(0);
			break;
		}
		case '4':
		{
			//to update arilinr inquirey
			cout << "UpdateAirlineInquiry()";
			break;
		}
		case '5':
		{
			return;
			break;
		}
		default:
		{
			cout << "Invalid Selection. Wait a few seconds.\n";
			Sleep(1000);
			system("cls");
			break;
		}
		}
	}

	// 
	// 
	// 
	// 
	//change routes for the planes
	// restrict no of passengers in a plane
	//update airline inquiry details
}
//to restrict or unrestrict seats in a plane for all flights
void RestrictPassengers(bool ToRestrict)
{
	//used ahead
	int citySelection = -1;
	int airportSelection = -1;
	int planeSelection = -1;

	//asking for city
	char Selection = 0;
	do
	{
		Selection = 0;
		cout << "Which City\n";
		cout << "1) Islamabad\n";
		cout << "2) Lahore\n";
		cout << "3) Quetta\n";
		cout << "4) Peshawar\n";
		cout << "5) Karachi\n";
		cin >> Selection;
		cout << Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			citySelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');

	//asking for airport
	do
	{
		Selection = 0;
		cout << "Which Airport:\n";
		cout << "1) North\n";
		cout << "2) South\n";
		cin >> Selection;
		if (Selection < '1' || Selection > '2')
		{
			cout << "Invalid\n";
		}
		else
		{
			airportSelection = Selection - '0';
		}
	} while (Selection < '1' || Selection > '2');

	//asking for plane
	int counter = 0;
	do
	{
		Selection = 0;
		counter = 0;
		cout << "Which Plane:\n";
		for (int i = 0; i < 5; i++)
		{
			if (airportSelection == 1)
			{
				cout << ++counter << ") " << Cities[citySelection].North->AllPlanes[i].getPlaneName() << endl;
			}
			else if (airportSelection == 2)
			{
				cout << ++counter << ") " << Cities[citySelection].South->AllPlanes[i].getPlaneName() << endl;
			}
		}
		cin >> Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			planeSelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');
	//for restriting
	if (ToRestrict)
	{
		if (airportSelection == 1)
		{
			Cities[citySelection].North->AllPlanes[planeSelection].RestrictSeats();
		}
		else if (airportSelection == 2)
		{
			Cities[citySelection].South->AllPlanes[planeSelection].RestrictSeats();
		}
	}
	//for unresticting
	else
	{
		if (airportSelection == 1)
		{
			Cities[citySelection].North->AllPlanes[planeSelection].UnRestrictSeats();
		}
		else if (airportSelection == 2)
		{
			Cities[citySelection].South->AllPlanes[planeSelection].UnRestrictSeats();
		}
	}
	//for showing 
	if (airportSelection == 1)
	{
		Cities[citySelection].North->AllPlanes[planeSelection].ShowSeats();
	}
	else if (airportSelection == 2)
	{
		Cities[citySelection].South->AllPlanes[planeSelection].ShowSeats();
	}
}
//for initializing all the schdules
void InitializaingDummySchedules()
{
	ifstream get;
	string str;
	int FlightFlag = 0;

	//for Islamabad
	{
		get.open("IslamabadSchedule.txt");
		while (getline(get, str))
		{
			string SeperateBySpace;
			int AttributeFlag = 0;
			Flight FromFile;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					if (AttributeFlag == 0)
					{
						AttributeFlag++;
						FromFile.setArrAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 1)
					{
						AttributeFlag++;
						FromFile.setDepAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 2)
					{
						AttributeFlag++;
						FromFile.setIsLocal(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 3)
					{
						AttributeFlag++;
						FromFile.setHrsOfFlight(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 4)
					{
						AttributeFlag++;
						FromFile.setDepartureTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 5)
					{
						AttributeFlag++;
						FromFile.setArrivalTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					continue;
				}
				SeperateBySpace += str[i];
			}
			for (int i = 0; i < 5; i++)
			{
				Cities[0].North->AllPlanes[i].AddFlight(FromFile);
				Cities[0].South->AllPlanes[i].AddFlight(FromFile);
			}
			FlightFlag++;
		}
		get.close();
	}

	//for Lahore
	{
		get.open("LahoreSchedule.txt");
		FlightFlag = 0;
		while (getline(get, str))
		{
			string SeperateBySpace;
			int AttributeFlag = 0;
			Flight FromFile;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					if (AttributeFlag == 0)
					{
						AttributeFlag++;
						FromFile.setArrAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 1)
					{
						AttributeFlag++;
						FromFile.setDepAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 2)
					{
						AttributeFlag++;
						FromFile.setIsLocal(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 3)
					{
						AttributeFlag++;
						FromFile.setHrsOfFlight(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 4)
					{
						AttributeFlag++;
						FromFile.setDepartureTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 5)
					{
						AttributeFlag++;
						FromFile.setArrivalTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					continue;
				}
				SeperateBySpace += str[i];
			}
			for (int i = 0; i < 5; i++)
			{
				Cities[1].North->AllPlanes[i].AddFlight(FromFile);
				Cities[1].South->AllPlanes[i].AddFlight(FromFile);
			}
			FlightFlag++;
		}
		get.close();
	}

	//for Quetta
	{
		get.open("QuettaSchedule.txt");
		FlightFlag = 0;
		while (getline(get, str))
		{
			string SeperateBySpace;
			int AttributeFlag = 0;
			Flight FromFile;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					if (AttributeFlag == 0)
					{
						AttributeFlag++;
						FromFile.setArrAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 1)
					{
						AttributeFlag++;
						FromFile.setDepAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 2)
					{
						AttributeFlag++;
						FromFile.setIsLocal(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 3)
					{
						AttributeFlag++;
						FromFile.setHrsOfFlight(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 4)
					{
						AttributeFlag++;
						FromFile.setDepartureTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 5)
					{
						AttributeFlag++;
						FromFile.setArrivalTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					continue;
				}
				SeperateBySpace += str[i];
			}
			for (int i = 0; i < 5; i++)
			{
				Cities[2].North->AllPlanes[i].AddFlight(FromFile);
				Cities[2].South->AllPlanes[i].AddFlight(FromFile);
			}
			FlightFlag++;
		}
		get.close();
	}

	//for Peshawar
	{
		get.open("PeshawarSchedule.txt");
		FlightFlag = 0;
		while (getline(get, str))
		{
			string SeperateBySpace;
			int AttributeFlag = 0;
			Flight FromFile;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					if (AttributeFlag == 0)
					{
						AttributeFlag++;
						FromFile.setArrAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 1)
					{
						AttributeFlag++;
						FromFile.setDepAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 2)
					{
						AttributeFlag++;
						FromFile.setIsLocal(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 3)
					{
						AttributeFlag++;
						FromFile.setHrsOfFlight(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 4)
					{
						AttributeFlag++;
						FromFile.setDepartureTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 5)
					{
						AttributeFlag++;
						FromFile.setArrivalTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					continue;
				}
				SeperateBySpace += str[i];
			}
			for (int i = 0; i < 5; i++)
			{
				Cities[3].North->AllPlanes[i].AddFlight(FromFile);
				Cities[3].South->AllPlanes[i].AddFlight(FromFile);
			}
			FlightFlag++;
		}
		get.close();
	}

	//for Karachi
	{
		get.open("KarachiSchedule.txt");
		FlightFlag = 0;
		while (getline(get, str))
		{
			string SeperateBySpace;
			int AttributeFlag = 0;
			Flight FromFile;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ' ')
				{
					if (AttributeFlag == 0)
					{
						AttributeFlag++;
						FromFile.setArrAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 1)
					{
						AttributeFlag++;
						FromFile.setDepAirport(SeperateBySpace);
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 2)
					{
						AttributeFlag++;
						FromFile.setIsLocal(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 3)
					{
						AttributeFlag++;
						FromFile.setHrsOfFlight(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 4)
					{
						AttributeFlag++;
						FromFile.setDepartureTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					else if (AttributeFlag == 5)
					{
						AttributeFlag++;
						FromFile.setArrivalTime(stoi(SeperateBySpace));
						SeperateBySpace = "";
					}
					continue;
				}
				SeperateBySpace += str[i];
			}
			for (int i = 0; i < 5; i++)
			{
				Cities[4].North->AllPlanes[i].AddFlight(FromFile);
				Cities[4].South->AllPlanes[i].AddFlight(FromFile);
			}
			FlightFlag++;
		}
		get.close();
	}
}
//for changing schedule 
void ChangeSchedule()
{
	//used ahead
	int citySelection = -1;
	int airportSelection = -1;
	int planeSelection = -1;
	bool addOrDelete = 0;

	//asking for city
	char Selection = 0;
	do
	{
		Selection = 0;
		cout << "Which City\n";
		cout << "1) Islamabad\n";
		cout << "2) Lahore\n";
		cout << "3) Quetta\n";
		cout << "4) Peshawar\n";
		cout << "5) Karachi\n";
		cin >> Selection;
		cout << Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			citySelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');

	//asking for airport
	do
	{
		Selection = 0;
		cout << "Which Airport:\n";
		cout << "1) North\n";
		cout << "2) South\n";
		cin >> Selection;
		if (Selection < '1' || Selection > '2')
		{
			cout << "Invalid\n";
		}
		else
		{
			airportSelection = Selection - '0';
		}
	} while (Selection < '1' || Selection > '2');

	//asking for plane
	int counter = 0;
	do
	{
		Selection = 0;
		counter = 0;
		cout << "Which Plane:\n";
		for (int i = 0; i < 5; i++)
		{
			if (airportSelection == 1)
			{
				cout << ++counter << ") " << Cities[citySelection].North->AllPlanes[i].getPlaneName() << endl;
			}
			else if (airportSelection == 2)
			{
				cout << ++counter << ") " << Cities[citySelection].South->AllPlanes[i].getPlaneName() << endl;
			}
		}
		cin >> Selection;
		if (Selection < '1' || Selection > '5')
		{
			cout << "Invalid\n";
		}
		else
		{
			planeSelection = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '5');

	//asking to add or delete a schedule
	do
	{
		Selection = 0;
		cout << "Do you want to add or delete a schedule:\n";
		cout << "1) add\n";
		cout << "2) delete\n";
		cin >> Selection;
		if (Selection < '1' || Selection > '2')
		{
			cout << "Invalid\n";
		}
		else
		{
			addOrDelete = Selection - '0' - 1;
		}
	} while (Selection < '1' || Selection > '2');

	//for adding
	if (!addOrDelete)
	{
		cout << "Enter the destination: ";
		string destination;
		cin.ignore();
		getline(cin, destination);

		cout << "Enter Departure:";
		string departure;
		getline(cin, departure);

		cout << "Enter Duration of Flight";
		int duration = 0;
		cin >> duration;

		cout << "Enter Departure time (in 2400 hour format)";
		int dep = 0;
		cin >> dep;

		cout << "Enter Arrival time (in 2400 hour format)";
		int arr;
		cin >> arr;

		cout << "For Local Press 1, For International Press 0";
		bool islocal = 0;
		cin >> islocal;
		/*(string arr="", string dep="", bool local = 0, int hrs = 0, int depTime = 0, int arrTime = 0)*/
		Flight New(destination, departure, islocal, duration, dep, arr);
		if (airportSelection == 1)
		{
			Cities[citySelection].North->AllPlanes[planeSelection].AddFlight(New);
			cout << Cities[citySelection].North->AllPlanes[planeSelection];
		}
		else if (airportSelection == 2)
		{
			Cities[citySelection].South->AllPlanes[planeSelection].AddFlight(New);
			cout << Cities[citySelection].South->AllPlanes[planeSelection];
		}
	}
	//for deleting
	else
	{
		cout << "Enter the destination: ";
		string destination;
		cin.ignore();
		getline(cin, destination);

		cout << "Enter Departure:";
		string departure;
		getline(cin, departure);

		cout << "Enter Departure time (in 2400 hour format)";
		int dep = 0;
		cin >> dep;

		cout << "Enter Arrival time (in 2400 hour format)";
		int arr;
		cin >> arr;
		Flight AboutToBeDeleted(destination, departure, 0, 0, dep, arr);

		if (airportSelection == 1)
		{
			Cities[citySelection].North->AllPlanes[planeSelection].RemoveFlight(AboutToBeDeleted);
			cout << Cities[citySelection].North->AllPlanes[planeSelection];
		}
		else if (airportSelection == 2)
		{
			Cities[citySelection].South->AllPlanes[planeSelection].RemoveFlight(AboutToBeDeleted);
			cout << Cities[citySelection].South->AllPlanes[planeSelection];
		}
	}
}
//for showing bookings
void ShowBookings()
{
	for (int i = 0; i < TotalBookings; i++)
	{
		cout << *AllBookings[i];
	}
}
//for displaying the planes
void DisplayPlanesInCity()
{
	for (int i = 0; i < 5; i++)
	{
		cout << Cities[i];
	}
}
//for getting the admins infor frim file
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
				continue;
			}
			SeperateBySpace += OneAdmin[i];
		}
		AdminFlag++;
	}
	GetAdmins.close();
}
//for printing the admins
void PrintAdmin()
{
	for (int i = 0; i < 3; i++)
	{
		cout << "CNIC: " << AllAdmin[i].getCNIC();
		cout << " Name: " << AllAdmin[i].getName();
		cout << " Password: " << AllAdmin[i].getPassword() << endl;
	}
}
//for printing the passengers
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
//for verifying the financial details
void VerifyFinancialDetail()
{

}
//checking for admins
bool AdminExists(string login)
{
	bool AlreadyExists = 0;
	for (int i = 0; i < 3; i++)
	{
		if (login == AllAdmin[i].getCNIC())
		{
			AlreadyExists = 1;
		}
	}
	return AlreadyExists;
}
//checking for passengers
bool PassengerExists(string login)
{
	bool AlreadyExists = 0;
	for (int i = 0; i < NoOfPassengers; i++)
	{
		if (login == AllPassengers[i].getCNIC())
		{
			AlreadyExists = 1;
		}
	}
	return AlreadyExists;
}
//for bothr
bool UserExists(string login)
{
	if (AdminExists(login) == 1 || PassengerExists(login) == 1)
	{
		return 1;
	}
	return 0;
}
//checking the password okay
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
		if (upperExists == 0 && password[i] >= 'A' && password[i] <= 'Z')
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
//adding passenger to file
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
//updating the passengers array after change or after adding
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
				continue;
			}
			SeperateBySpace += APassenger[i];
		}
		PassengersFlag++;
	}
	GetPassengers.close();
}
//for registering
void Register()
{
	Passenger ToBeRegistered;

	cin.ignore();

	//get name
	cout << "Enter you name(for space use _ only): ";
	string name;
	getline(cin, name);
	ToBeRegistered.setName(name);
	//get cnic
	string CNIC;
	do
	{
		cout << "Enter CNIC: ";
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
	//checking for visa
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

	//check if it doesnt already exits
	if (!UserExists(CNIC))
	{
		AddToFile(ToBeRegistered);
		UpdatePassengerArray();
	}
}
//finding the admin
int FindInAdmin(string CNIC)
{
	for (int i = 0; i < 3; i++)
	{
		if (CNIC == AllAdmin[i].getCNIC())
		{
			return i;
		}
	}
	return -1;
}
//finding passengers
int FindInPassengers(string CNIC)
{
	for (int i = 0; i < 3; i++)
	{
		if (CNIC == AllPassengers[i].getCNIC())
		{
			return i;
		}
	}
	return -1;
}
//for login
void Login()
{
	int AdminIndex = -1;
	int PassengerIndex = -1;
	//getting cnic
	cin.ignore();
	string LoginName;
	do
	{
		cout << "Enter CNIC: ";
		getline(cin, LoginName);
		AdminIndex = FindInAdmin(LoginName);
		PassengerIndex = FindInPassengers(LoginName);
		if (AdminIndex == -1 && PassengerIndex == -1)
		{
			cout << "This CNIC is not registered\n";
		}
	} while (AdminIndex == -1 && PassengerIndex == -1);
	//getting password and chekcing
	string Password;
	do
	{
		cout << "Enter your account password: ";
		getline(cin, Password);
		if (AdminIndex != -1 && Password != AllAdmin[AdminIndex].getPassword())
		{
			cout << "Wrong Password\n";
		}
		else if (PassengerIndex != -1 && Password != AllPassengers[PassengerIndex].getPassword())
		{
			cout << AllPassengers[PassengerIndex].getPassword();
			cout << "Wrong Password\n";
		}
	} while ((AdminIndex != -1 && Password != AllAdmin[AdminIndex].getPassword()) || (PassengerIndex != -1 && Password != AllPassengers[PassengerIndex].getPassword()));

	//going to correct one
	if (AdminIndex != -1)
	{
		system("cls");
		cout << "WELCOME TO THE ADMIN FUNCTION, " << AllAdmin[AdminIndex].getName() << endl;
		AdminFunction();
	}
	else if (PassengerIndex != -1)
	{
		system("cls");
		cout << "WELCOME TO THE PASSENGER FUNCTION, " << AllPassengers[PassengerIndex].getName() << endl;
		PassengerFunction(AllPassengers[PassengerIndex]);
	}
}