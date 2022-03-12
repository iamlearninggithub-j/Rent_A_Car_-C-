#pragma once
#include<iostream>
#include "Entities.h"
#include "FileHelper.h"
using namespace std;

int car_count = 3;
int id = 3;

Car** cars = new Car * [car_count] {
	new Car{ 1,new char[] {"Bentley Continental"},false,350,Date{0,0,0},Date{0,0,0} },
		new Car{ 2,new char[] {"Mercedes 63 AMG"},true,280,Date{0,0,0},Date{0,0,0} },
		new Car{ 3,new char[] {"Rolls Royce Ghost"},false,550,Date{0,0,0},Date{0,0,0} },
};

int user_count = 1;
User** users = new User * [1]{
		new User{2,new char[] {"Rafiq Rafiqli"},new char[] {"Mercedes 63 AMG"},__DATE__}
};


Car** LoadData() {
	Car** car_s = nullptr;
	if (isExist("cars.bin")) {
		car_s = ReadFromFile();
	}
	else {
		WriteCarsToFile(cars, 3);
		car_s = ReadFromFile();
	}
	return car_s;
}

User** LoadUsers() {
	User** user_s = nullptr;
	if (isExist("users.bin")) {
		user_s = ReadUsersFromFile();
	}
	else {
		WriteUsersToFile(users, 1);
		user_s = ReadUsersFromFile();
	}
	return user_s;
}

bool isAdmin(const char* username, const char* pass) {
	if (strcmp(username, "admin") == 0) {

		if (strcmp(pass, "admin") == 0) {
			return true;
		}
		else {
			system("cls");
			cout << "\n Password is incorrect!" << endl;
			Sleep(3000);
			return false;
		}
	}
	else {
		system("cls");
		cout << "\n Username is incorrect!" << endl;
		Sleep(3000);
		return false;
	}
}


void ShowCar(const Car* car) {
	cout << "\n =========CAR INFO==========" << endl;
	cout << "  ID : " << car->id << endl;
	cout << "  MODEL : " << car->model << endl;
	cout << "  Rented : ";
	if (car->isFull) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	cout << "  Price per day : " << car->pricePerDay << "$ " << endl;
	cout << "  Date start : " << car->start.day << "/" << car->start.month << "/" << car->start.year << endl;
	cout << "  Date end : " << car->end.day << "/" << car->end.month << "/" << car->end.year << endl;
}

void ShowAllCars(Car** cars, int count) {
	system("cls");
	for (size_t i = 0; i < count; i++)
	{
		ShowCar(cars[i]);
	}
}

void ShowUser(const User* user) {
	cout << "\n RENT INFO : " << user->fullname << "  " << user->car_id << "  " << user->car_model << "  " << user->takeCarDate << endl;
}

void ShowAllUsers(User** users, int count) {
	for (size_t i = 0; i < count; i++)
	{
		ShowUser(users[i]);
	}
	cout << endl;
	system("pause");
}

Car* getCarById(Car** cars, const int& count, const int& id) {
	for (size_t i = 0; i < count; i++)
	{
		if (cars[i]->id == id) {
			return cars[i];
		}
	}
	return  nullptr;
}
User* getUserByFullname(User** users, const int& count, const char* fullname) {
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(users[i]->fullname, fullname) == 0) {
			return users[i];
		}
	}
	return  nullptr;
}


User** AddUser(User** users, int& count, User* newuser) {
	auto newusers = new User * [count + 1]{};
	for (size_t i = 0; i < count; i++)
	{
		newusers[i] = users[i];
	}
	newusers[count] = newuser;

	users = newusers;
	newusers = nullptr;
	count++;
	return users;
}

// Tasks

//Rent Car proyektine
//
//add car funksiyasi yazmaq
//
//isFull field problem hell elemek
//
//remove Car ozelliyi

int GetLatestCarID()
{
	cars = ReadFromFile(); // to get car count
	return cars[car_count - 1]->id;
}

Car* GetNewCar()
{
	system("cls");
	cout << "\n ========== ADDING NEW CAR ========== " << endl;
	
	int i = GetLatestCarID();
	int id_of_car = i + 1;
	id++;

	cin.ignore();
	cin.clear();

	char* model = new char[100] {}; 
	cout << "\n Enter model of the car : ";
	cin.getline(model, 100);

	bool isFull = false;

	double price = 0;
	cout << " Enter price of the car : ";
	cin >> price;

	cout << "\n Enter start date" << endl;
	int start_day = 0;
	cout << " Day : ";
	cin >> start_day;

	int start_month = 0;
	cout << " Month : ";
	cin >> start_month;

	int start_year = 0;
	cout << " Year : ";
	cin >> start_year;

	cout << "\n Enter end date" << endl;
	int end_day = 0;
	cout << " Day : ";
	cin >> end_day;

	int end_month = 0;
	cout << " Month : ";
	cin >> end_month;

	int end_year = 0;
	cout << " Year : ";
	cin >> end_year;

	Car* new_car = new Car{ id_of_car, model, isFull, price, start_day, start_month, start_year, end_day, end_month, end_year };
	return new_car;
}

void AddCar()
{
	Car* new_car = GetNewCar();
	Car** new_cars = new Car * [car_count + 1]{};
	for (int x = 0; x < car_count; x++)
	{
		new_cars[x] = cars[x];
	}
	new_cars[car_count] = new_car;
	cars = new_cars;
	new_cars = nullptr;
	car_count++;
	global_car_count++;
}

int GetIndexOfCarByID(int id)
{
	cars = ReadFromFile(); // to get car count
	for (int x = 0; x < car_count; x++)
	{
		if (cars[x]->id == id)
		{
			return x;
		}
	}
	return -1;
}


void RemoveCarbByID(int id)
{
	cars = ReadFromFile(); // to get car count
	int index = GetIndexOfCarByID(id);
	if (index != -1)
	{
		Car** new_cars = new Car * [car_count - 1]{};
		for (int x = 0; x < index; x++)
		{
			new_cars[x] = cars[x];
		}
		for (int y = index + 1; y < car_count; y++)
		{
			new_cars[y - 1] = cars[y];
		}
		cars = new_cars;
		new_cars = nullptr;
		car_count--;
		global_car_count--;
		WriteCarsToFile(cars, car_count);
		cars = ReadFromFile();
		cout << "\n Car was successfully deleted!" << endl;
		Sleep(3000);
	}
	else
	{
		cout << "\n There is not a car with this ID." << endl;
		Sleep(3000);
	}
}