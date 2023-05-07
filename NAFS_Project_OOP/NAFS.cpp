#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

class Flight
{
private:
	bool isLocal;
	int HrsOfFlight;
	int DepartureTime;
	int ArrivalTime;
	string DepartureAirport;
	string ArrivalAirport;
public:
	Flight(string arr="", string dep="", bool local = 0, int hrs = 0, int depTime = 0, int arrTime = 0)
		: isLocal(local), HrsOfFlight(hrs), DepartureTime(depTime), ArrivalTime(arrTime), DepartureAirport(dep), ArrivalAirport(arr) {}

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
	op << "Flight Hours: " << flight.HrsOfFlight;
	op << "Departure Time: " << flight.DepartureTime;
	op << "Arrival Time: " << flight.ArrivalTime;
	op << "Arrival Airport: " << flight.ArrivalAirport;
	op << "Departure Airport: " << flight.DepartureAirport;
	op << endl;
	return op;
}

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

class Seat
{
	//takes a passenger details as aggregation
	//must also have a covid thing
protected:
	Passenger& passenger;
	string Name;
	bool isOccupied;
	bool Restrict;
public:
	Seat(Passenger& pass, string name = "", bool occupied = 0, bool restrict = 0)
		:Name(name), isOccupied(occupied), passenger(pass), Restrict(restrict){}

	// getters
	bool getRestrict() const
	{
		return Restrict;
	}
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
	void setRestrict(bool res)
	{
		Restrict = res;
	}
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

	friend ostream& operator<<(ostream& op, const Seat& seat);
};
ostream& operator<<(ostream& op, const Seat& seat)
{
	op << "Name: " << seat.Name;
	op << "IsOccupied: " << seat.isOccupied;
	op << "Restrict: " << seat.Restrict;
	op << endl;
	return op;
}

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
	string Name;
	Seat** BuisnessClass;
	Seat** EconomyClass;
	static int NoOfPlanes;
	int arraysize;
	int NoOfFlights;
	Flight* Schedule;
	bool isPresent(const Flight& flight)
	{
		//checks if the product is present
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
		Name = "Plane" + to_string(NoOfPlanes);
	}
	string getPlaneName()
	{
		return Name;
	}
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
	void RestrictSeats()
	{
		for (int i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
			{
				BuisnessClass[i]->setRestrict(1);
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (i % 2 == 0)
			{
				EconomyClass[i]->setRestrict(1);
			}
		}
	}
	void UnRestrictSeats()
	{
		for (int i = 0; i < 10; i++)
		{
			BuisnessClass[i]->setRestrict(0);
		}
		for (int i = 0; i < 50; i++)
		{
			EconomyClass[i]->setRestrict(0);
		}
	}
	void ShowSeats()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "Buisness Class:\n";
			cout << *BuisnessClass[i];
		}
		for (int i = 0; i < 50; i++)
		{
			cout << "Buisness Class:\n";
			cout << *EconomyClass[i];
		}
	}

	friend ostream& operator<<(ostream& op, const Plane& plane);
	friend void InitializaingDummySchedules();
	//void ShowAvaliableSeats();
	//keeps check of which are filled and which are not
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

class Airport
{
private:
	Plane* AllPlanes;
	int NoOfPlanes = 0;
	/*FlightSchedule** ScheduleForPlanes;*/
	//takes flights as aggregation
public:
	Airport(int noofplanes=1)
	{
		NoOfPlanes = noofplanes;
		AllPlanes = new Plane[NoOfPlanes];
		/*ScheduleForPlanes = new FlightSchedule*[NoOfPlanes];
		for (int i = 0; i < NoOfPlanes; i++)
		{
			ScheduleForPlanes[i] = new FlightSchedule(AllPlanes[i]);
		}*/
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
};
ostream& operator<<(ostream& op, const Airport& air)
{

	for (int i = 0; i < air.NoOfPlanes; i++)
	{
		op << air.AllPlanes[i];
	}
	return op;
}

class City
{
private:
	string Name;
	Airport* North;
	Airport* South;
public:
	City(string name="")
	{
		Name = name;
		North = new Airport(5);
		South = new Airport(5);
	}
	friend ostream& operator<<(ostream& op, const City& city);
	friend void InitializaingDummySchedules();
	friend void ChangeSchedule();
	friend void RestrictPassengers(bool ToRestrict);
	//composition of two airports namely north and south
};
ostream& operator<<(ostream& op, const City& city)
{
	
	op <<"North:\n" << *city.North;
	op <<"South:\n" << *city.South;
	return op;
}

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

//Plane** Planes = new Plane * [5];

City* Cities = new City[5]{City("Islamabad"), City("Lahore"), City("Quetta"), City("Peshawar"), City("Karachi") };

void GetAdminInfo();
void PrintAdmin();
void PrintPassengers();
void VerifyFinancialDetail();
bool AdminExists(string login);
bool PassengerExists(string login);
bool UserExists(string login);
bool isValidPassword(string password);
void AddToFile(Passenger ToBeRegistered);
void UpdatePassengerArray();
void Register();
int FindInAdmin(string CNIC);
int FindInPassengers(string CNIC);
void Login();
void DisplayPlanesInCity()
{
	for (int i = 0; i < 5; i++)
	{
		cout << Cities[i];
	}
}
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
void ChangeSchedule()
{
	//change schedule to a plane
	//ask for city
	//then ask for airport
	// then ask for plane 
	// then ask what to change 
	// then ask new 
	// then change
	int citySelection = -1;
	int airportSelection = -1;
	int planeSelection = -1;
	bool addOrDelete = 0;

	//asking for city
	char Selection=0;
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
		cout << "Do you want to add or delete a schedule:";
		cout << "1) add\n";
		cout << "2) deleten\n";
		cin >> Selection;
		if (Selection < '1' || Selection > '2')
		{
			cout << "Invalid\n";
		}
		else
		{
			addOrDelete = Selection - '0' -1;
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


	/*while (!Exit)
	{
		
		cout << "To Restrict No Of Passengers in a plane Press 2\n";
		cout << "To Update Airline Inquiry Press 3\n";
		cout << "To go Back Press 4\n";
		char Selection = 0;
		cin >> Selection;
		switch (Selection)
		{
		case '1':
		{
			ChangeSchedule();
			break;
		}
		case '2':
		{
			cout << "RestrictPassengers()";
			break;
		}
		case '3':
		{
			cout << "UpdateAirlineInquiry()";
			break;
		}
		case '4':
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
	}*/
}
void RestrictPassengers(bool ToRestrict)
{
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


	if (ToRestrict == 1)
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
	else if (ToRestrict == 0)
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
	if (airportSelection == 1)
	{
		Cities[citySelection].North->AllPlanes[planeSelection].ShowSeats();
	}
	else if (airportSelection == 2)
	{
		Cities[citySelection].South->AllPlanes[planeSelection].ShowSeats();
	}
}
void AdminFunction()
{
	bool Exit = 0;
	while (!Exit)
	{
		cout << "To Change Schedule Press 1\n";
		cout << "To Restrict No Of Passengers in a plane Press 2\n";
		cout << "To UnRestrict No Of Passengers in a plane Press 3\n";
		cout << "To Update Airline Inquiry Press 4\n";
		cout << "To go Back Press 5\n";
		char Selection = 0;
		cin >> Selection;
		switch (Selection)
		{
		case '1':
		{
			ChangeSchedule();
			break;
		}
		case '2':
		{
			RestrictPassengers(1);
			break;
		}
		case '3':
		{
			RestrictPassengers(0);
			break;
		}
		case '4':
		{
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
//a func to increase the booking pointer


int main()
{
	InitializaingDummySchedules();
	GetAdminInfo();
	UpdatePassengerArray();
	PrintPassengers();
	PrintAdmin();
	AdminFunction();
	/*bool Exit = 0;
	while (!Exit)
	{
		char MainSelection = 0;
		cout << "Welcome to NUCES Airline Flight System\n";
		cout << "To Login Press 1\n";
		cout << "To Register Press 2\n";
		cout << "For Basic Details Press 3\n";
		cout << "To Exit Press 4\n==>";
		cin.get(MainSelection);
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
			cout << "Invalid Selection. Wait a few seconds.\n";
			Sleep(1000);
			system("cls");
			break;
		}
	}*/
	return 0;
}

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

void PrintAdmin()
{
	for (int i = 0; i < 3; i++)
	{
		cout << "CNIC: " << AllAdmin[i].getCNIC();
		cout << " Name: " << AllAdmin[i].getName();
		cout << " Password: " << AllAdmin[i].getPassword() << endl;
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

void VerifyFinancialDetail()
{

}

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
				continue;
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
	cout << "Enter you name(for space use _ only): ";
	string name;
	cin.ignore();
	getline(cin, name);
	ToBeRegistered.setName(name);
	//3434 M_Taha_Makhdoom Po1, 0 0 
	//gets cnic
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

void Login()
{
	int AdminIndex = -1;
	int PassengerIndex = -1;

	string LoginName;
	do
	{
		cout << "Enter CNIC: ";
		cin.ignore();
		getline(cin, LoginName);
		AdminIndex = FindInAdmin(LoginName);
		PassengerIndex = FindInPassengers(LoginName);
		if (AdminIndex == -1 && PassengerIndex == -1)
		{
			cout << "This CNIC is not registered\n";
		}
	} while (AdminIndex == -1 && PassengerIndex == -1);

	string Password;
	do
	{
		cout << "Enter your account password: ";
		//cin.ignore();
		getline(cin, Password);
		if (AdminIndex != -1 && Password != AllAdmin[AdminIndex].getPassword())
		{
			cout << "1Wrong Password\n";
		}
		else if (PassengerIndex != -1 && Password != AllPassengers[PassengerIndex].getPassword())
		{
			cout << AllPassengers[PassengerIndex].getPassword();
			cout << "2Wrong Password\n";
		}
	} while ((AdminIndex != -1 && Password != AllAdmin[AdminIndex].getPassword()) || (PassengerIndex != -1 && Password != AllPassengers[PassengerIndex].getPassword()));


	if (AdminIndex != -1)
	{
		cout << "Admin at index " << AdminIndex;
		AdminFunction();
	}
	else if (PassengerIndex != -1)
	{
		cout << "Passenger at index " << PassengerIndex;
	}

	//have to login to special thing
	//can make a function that would search for both admins and passengers and allows 0 if not found and 1 if admin and 2 if passenger
	//for the admin same for everyone
	//for the passengers we will make a template and add values there regarding each passenger
}