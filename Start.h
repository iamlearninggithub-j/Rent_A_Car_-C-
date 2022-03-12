#pragma once
#include<iostream>
#include <Windows.h>
#include "Functions.h"
#include "FileHelper.h"
using namespace std;


void Menu() 
{
	system("cls");
	cout << "\n ======= MAIN MENU ======= " << endl;
	cout << "   ADMIN           1  " << endl;
	cout << "   GUEST           2  " << endl;
	cout << " ========================= " << endl;
}
void Start() {
	Menu();
	cout << "\n Enter your selection : ";
	char select = 0;
	cin >> select;
	if (select == '1') 
	{
		system("cls");
		cin.ignore();
		cin.clear();
		cout << "\n ========= LOG IN =========" << endl;
		char* username = new char[100]{};
		cout << "\n Enter username : ";
		cin.getline(username, 100);
		char* pass = new char[100]{};
		cout << " Enter password : ";
		cin.getline(pass, 100);
		if (isAdmin(username, pass))
		{
			while (true)
			{
				system("cls");
				cout << "\n =======================" << endl;
				cout << "   CARS              1  " << endl;
				cout << "   RENTS             2  " << endl;
				cout << "   ADD CAR           3  " << endl;
				cout << "   DELETE CAR        4  " << endl;
				cout << "   MAIN MENU         5  " << endl;
				cout << " =======================" << endl;
				cout << "\n Enter your selection : ";
				char s = 0;
				cin >> s;
				if (s == '1')
				{
					auto cars = LoadData();
					ShowAllCars(cars, global_car_count);
					cout << endl;
					system("pause");
				}
				else if (s == '2')
				{
					auto users = LoadUsers();
					system("cls");
					ShowAllUsers(users, global_user_count);
				}
				else if (s == '3')
				{
					cars = ReadFromFile();
					car_count = global_car_count;
					AddCar();
					WriteCarsToFile(cars, car_count);
					cars = ReadFromFile();
					cout << "\n Car was successfully added!" << endl;
					Sleep(3000);
				}
				else if (s == '4')
				{
					system("cls");
					cout << "\n ========== DELETING A CAR ========== " << endl;
					auto cars = LoadData();
					ShowAllCars(cars, global_car_count);
					int id = 0;
					cout << "\n Enter ID of the car : ";
					cin >> id;
					RemoveCarbByID(id);
				}
				else if (s == '5')
				{
					break;
				}
				else
				{
					system("cls");
					cout << "\n Incorrect Input! " << endl;
					Sleep(3000);
				}
			}
		}
	}
	else if (select == '2')
	{
		while (true)
		{
			system("cls");
			auto cars = LoadData();
			ShowAllCars(cars, global_car_count);
			cout << "\n  Enter Car ID : ";
			int id = 0;
			cin >> id;
			auto car = getCarById(cars, global_car_count, id);
			if (car == nullptr)
			{
				system("cls");
				cout << "\n There is not a car with this ID." << endl;
				Sleep(3000);
				break;
			}
			else
			{
				system("cls");
				if (car->isFull)
				{
					cout << "\n You cannot select this car." << endl;
					cout << " Car is full." << endl;
					return;
				}
				else
				{
					system("cls");
					ShowCar(car);

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
					cin.ignore();
					cin.clear();

					int total_days = end_day - start_day;
					cout << "\n Total Payments : " << total_days * car->pricePerDay << "$" << endl;

					cout << "\ Enter your own info"  << endl;
					cout << " Enter name and surname : " << endl;
					char* fullname = new char[100]{};
					cin.getline(fullname, 100);
					User* user = new User{ car->id,fullname,car->model,__DATE__ };
					car->isFull = true;
					cout << "\n Your rent process was completed successfully!" << endl;
					WriteCarsToFile(cars, global_car_count);


					auto users = LoadUsers();
					users = AddUser(users, global_user_count, user);
					WriteUsersToFile(users, global_user_count);
				}
			}
		}
	}
	else
	{
		system("cls");
		cout << "\n Incorrect Input! " << endl;
		Sleep(3000);
	}
}
