#include<conio.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<time.h>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#include"payment.h"
#include<stdio.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include<list>

using namespace std;


//Airplane Parking

#define MAXN 100

bool board[MAXN][MAXN];
int n;

bool isSafe(int row, int col) {
    // Check if the row is safe
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueens(int col, int num_planes) {
    // Base case: all planes have been parked
    if (num_planes == 0) {
        return true;
    }

    // Check if we can place the plane in each row of the current column
    for (int i = 0; i < n; i++) {
        if (isSafe(i, col)) {
            board[i][col] = true;

            // Recur to park the remaining planes
            if (solveNQueens(col + 1, num_planes - 1)) {
                return true;
            }

            // Backtrack if the above recursive call didn't return true
            board[i][col] = false;
        }
    }

    // If no plane can be parked in this column, return false
    return false;
}
//Avoid Bad Weather
// Define the size of the maze
const int ROWS = 5;
const int COLS = 5;
// Define the maze with 0's and 1's
// 0 represents a clear path, 1 represents bad weather
int maze[ROWS][COLS] = {
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 1},
    {0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0},
    {1, 0, 0, 0, 0}
};
// Define a vector to keep track of the solution path
vector<pair<int, int>> path;

// Define a function to check if a given cell is a valid move
bool isValidMove(int row, int col) {
    // Check if the move is within the bounds of the maze and the cell is clear
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS && maze[row][col] == 0);
}

// Define a function to solve the maze using backtracking
bool solveMaze(int row, int col) {
    // Check if we have reached the end of the maze
    if (row == ROWS - 1 && col == COLS - 1) {
        // Add the final cell to the solution path
        path.push_back({row, col});
        return true;
    }
    // Check if the current cell is a valid move
    if (isValidMove(row, col)) {
        // Add the current cell to the solution path
        path.push_back({row, col});
        // Move to the next cell
        if (solveMaze(row + 1, col) || solveMaze(row, col + 1)) {
            return true;
        }
        // Remove the current cell from the solution path
        path.pop_back();
    }
    return false;
}
// Shortest Path
// Define the graph as an adjacency list
unordered_map<string, unordered_map<string, int>> graph1 = {
    {"DELHI", {{"CHENNAI", 2200}, {"MUMBAI", 1400}, {"KOLKATA", 1300}, {"AMRITSAR", 450}}},
    {"CHENNAI", {{"DELHI", 2200}, {"MUMBAI", 1200}, {"KOLKATA", 1650}, {"AMRITSAR", 3100}}},
    {"MUMBAI", {{"DELHI", 1400}, {"CHENNAI", 1200}, {"KOLKATA", 2000}, {"AMRITSAR", 1750}}},
    {"KOLKATA", {{"DELHI", 1300}, {"CHENNAI", 1650}, {"MUMBAI", 2000}, {"AMRITSAR", 1700}}},
    {"AMRITSAR", {{"DELHI", 450}, {"CHENNAI", 3100}, {"MUMBAI", 1750}, {"KOLKATA", 1700}}}
};

// Function to find the shortest path using Dijkstra's Algorithm
int dijkstra(string src, string dst) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    unordered_map<string, int> dist;
    for (auto& it : graph1) {
        dist[it.first] = numeric_limits<int>::max();
    }
    dist[src] = 0;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();
        for (auto& it : graph1[u]) {
            string v = it.first;
            int w = it.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist[dst];
}


//Date Check
bool datecheck(int, int, int, int);
const char l_destination[5][20]={"DELHI","CHENNAI","MUMBAI","KOLKATA","AMRITSAR"};	//local Destination
const char i_destination[11][20]={"LONDON","BERLIN","DUBAI","RIYADH","BEIJING","PARIS","CANBERRA","TOKYO","WASHINGTON","AMSTERDAM","CHENNAI" }; //International Destination

class passenger{
	private:
		const int bseats;
		const int eseats;
	protected:
		string firstname,lastname, phone, mealtype, passport, Address;
		int bus, eco, datedep, payment;
		char origin[30];
		char destination[30];
	public:
		passenger(string f_name, string l_name, string phone_no, string add="N/A", string pass_no="N/A", int dd=000000): bseats(50), eseats(250)
		{
			datedep=dd;
			firstname=f_name;
			lastname=l_name;
			Address=add;
			phone=phone_no;
			passport=pass_no;
			bus = bseats;
			eco = eseats;
		}

		virtual bool ldest()=0;
		virtual bool idest(string pass)=0;
		virtual void seats()=0;
		virtual void Meals()=0;
		virtual void Registration()=0;
		virtual bool display()=0;
		virtual void drive()=0;

};

class booking:public passenger
{
	protected:
		int i,j,n,m,k,NoOfSeats,choice;
	public:

		booking(string f,string l,string num,string add,string pass,int dd):passenger(f,l,add,num,pass,dd)
		{
			n=0;
			m=0;
		}

	bool ldest()
	{

		cout<<endl<<"These are the local destinations where we are flying: \n";
		for(i=0;i<5;i++)
		{
			for(j=0;j<20;j++)
			{
				cout<<l_destination[i][j];
			}
			cout<<"\n";
		}

		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;
		cout<<endl<<"Enter your destination(using BLOCK letters): ";
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(i=0;i<5;i++)
			{
				if(strcmp(l_destination[i],origin)==0)
					n++;
			}
			for(j=0;j<5;j++)
			{
				if(strcmp(l_destination[j],destination)==0)
					m++;
			}
			if(m==1&&n==1)
			{
				payment = lpayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Rs/seat"<<endl;
				return true;
			}
			else
				return false;

		}
	}

		bool idest(string pass)
	{
		passport = pass;
		cout<<endl<<"These are the international destinations where we are flying: \n";
		for(i=0;i<11;i++)
		{
			for(j=0;j<20;j++)
			{
				cout<<i_destination[i][j];
			}
			cout<<"\n";
		}
		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;
		cout<<endl<<"Enter your destination(using BLOCK letters): ";
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(i=0;i<11;i++)
			{
				if(strcmp(i_destination[i],origin)==0)
					n++;
			}
			for(j=0;j<11;j++)
			{
				if(strcmp(i_destination[j],destination)==0)
					m++;
			}
			if(m==1&&n==1)
			{
				payment = ipayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Rs/seat"<<endl;
				return true;
			}
			else
				return false;
		}
	}


		void seats()
		{
			bus_eco:
				if(bus>0&&eco>0)
				{
					cout<<endl<<"1.Business Class\n2.Economy Class\n";
					k = getch();
					switch(k)
					{
						case 49:
						{
							cout<<endl<<"Business Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>NoOfSeats;
							payment=(payment*NoOfSeats)+5000;
							if(NoOfSeats<=bus)
							{
								cout<<endl<<"Seats are available.\n\n";
								bus=bus-NoOfSeats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<bus<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									NoOfSeats = bus;
									payment=(payment*NoOfSeats)+5000;
								 	cout<<"Seats are booked\n\n";
								 	bus=0;
								}
								else
								{
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}

					case 50:
						{
							cout<<endl<<"Economy Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>NoOfSeats;
							payment=(payment*NoOfSeats);
							if(NoOfSeats<=eco)
							{
								cout<<endl<<"Seats are available.\n\n";
								eco=eco-NoOfSeats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<eco<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									NoOfSeats = eco;
									payment=(payment*NoOfSeats);
									cout<<endl<<"Seats are booked\n\n";
									eco=0;
								}
								else
								{
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}

					default:
						{
							cout<<"Error!\n";
							goto bus_eco;
						}
				}
			}
			else
			{
				cout<<endl<<"Sorry no seats available\nHave a nice day!";
				exit(0);
			}
		}


		void Meals()
		{
			meal:
			int n;
			cout<<endl<<"Available meal types:\n1.Vegetarian\n2.Non-Vegetarian\n";
			n = getch();
			if(n==49)
				mealtype="Vegetarian";
			else if(n==50)
				mealtype="Non Vegetarian";
			else
			{
				cout<<"ERROR!!!"<<endl;
				goto meal;
			}
		}

		void Registration()
		{
			int tkt;
			srand (time(NULL));
			tkt = rand()%1000;
			if(k==49)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstname<<" "<<lastname<<endl
				<<"Phone: "<<Address<<endl
				<<"Address: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Food: "<<mealtype
				<<endl<<"Number of Seats: "<<NoOfSeats
				<<endl<<"Class: Business"
				<<endl<<"Date of departure: "<<datedep
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<tkt
				<<endl<<"Bill(in Rupees): "<<payment<<"/-"<<endl;
				outfile.close();
			}
			else if(k==50)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstname<<" "<<lastname<<endl
				<<"Phone: "<<Address<<endl
				<<"Address: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Food: "<<mealtype
				<<endl<<"Number of Seats: "<<NoOfSeats
				<<endl<<"Class: Economy"
				<<endl<<"Date of departure: "<<datedep
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<tkt
				<<endl<<"Bill(in Rupees): "<<payment<<"/-"<<endl;
				outfile.close();
			}
		}

		bool display()
		{
			bool ans;
			system("cls");
			string temp;
			ifstream infile;
			infile.open("flight.txt");
			while(!infile.eof())
			{
				getline(infile,temp);
				cout<<temp<<endl;
			}
			ans = confirm();
			return ans;
		}

		bool confirm()
		{
			char ch;
			confirm:
			cout<<endl<<endl<<"Do you wish to confirm your ticket?(y/n): ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl<<"|STATUS CONFIRMED";
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|STATUS CONFIRMED";
				outfile.close();
				return true;
			}
			else if(ch=='N'||ch=='n')
			{
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|BOOKING CANCELLED";
				cout<<endl<<endl<<"|BOOKING CANCELLED"
				<<endl<<"Going back to main page";

				outfile.close();
				return false;
			}
			else
			{
				cout<<endl<<"ERROR!!!";
				goto confirm;
			}
		}

		inline void drive()
		{
			string pick;
			cout<<endl<<"Please enter your pickup point: ";
			cin.ignore();
			getline(cin,pick);
			cout<<endl<<endl<<"Pickup Location: "<<pick;
			cout<<endl<<"Drop Off: "<<origin<<" Airport"
			<<endl<<"Fare: 300/-";
			cout<<endl<<endl<<"You will be contacted by our driver shortly\nHave a nice day!";
			fstream ofile;
			ofile.open("flight.txt",ios::app);
			ofile<<endl<<endl<<"Pick'n Drop: YES"<<endl<<endl
			<<"Pickup Location: "<<pick
			<<endl<<"Drop Off: "<<origin<<" Airport"
			<<endl<<"Fare: 300/-";
			ofile.close();
		}
};

class Manage
{
	private:
		string temp,y,c2;
		int option;
	public:
		int change()
		{
			int i=0;

			ifstream file("flight.txt");
			if(file.is_open())
			{
			cout<<endl<<"Enter your Ticket Number or Press 0 to exit\nTicket Number: ";
			cin>>temp;
			if(temp=="0")
				return 1;
			string v("Ticket: "+temp);

			while(!file.eof())
			{
				getline(file,y);
				if(y==v)
				{
					file.seekg(0,ios::beg);
					while(!file.eof())
					{
						getline(file,temp);
						cout<<temp<<endl;
					}
					cout<<endl<<endl<<"1.Change date\n2.Cancel the flight\n3.Go Back\n";
					option = getch();
					switch(option)
					{
						case 49:
						{
							file.seekg(0,ios::beg);
							ofstream ofile("temp.txt");
							cout<<endl<<"Enter the new date of departure(DDMMYYYY): ";
							cin>>c2;
							string c1("Date of departure: "+c2);
							while(!file.eof())
							{
								getline(file,y);
								if(i==11)
								{
									i++;
									ofile<<c1<<endl;
								}
								else
								{
									i++;
									ofile<<y<<endl;
								}
							}
							file.close();
							ofile.close();
							ofstream outfile;
							outfile.open("flight.txt");
							ifstream readfile("temp.txt");
							while(!readfile.eof())
							{
								getline(readfile,y);
								outfile<<y<<endl;
							}
							outfile.close();
							readfile.close();
							remove("temp.txt");
							cout<<endl<<"Date Changed!";
							return 1;
							break;
						}

						case 50:
						{
							file.close();
							ofstream ofli;
							ofli.open("flight.txt",ios::trunc);
							ofli.close();
							remove("flight.txt");
							system("cls");
							cout<<endl<<"Booking cancelled!\n\n";
							return 1;
							break;
						}
						case 51:
							system("cls");
							return 1;
					}
				}
			}
		}
		else if(!file.is_open())
		{
			cout<<endl<<endl<<"unable to find any record"<<endl;
			cout<<endl<<"going back to main page\n\n";
			file.close();
			return 1;
		}
	}
};



class complain
{
	private:
		string f_name, l_name, p_num;
		int choice;
		string sentence;
		string types;
		char ch;
	public:
		complain(string f,string l,string num)
		{
			f_name = f;
			l_name = l;
			p_num = num;
		}

	void type()
	{
		back:
		cout<<endl<<endl<<"Enter the type of complain you want to register:\n1.Airport Handling\n2.Baggage Delivery\n3.Booking and ticketing\n4.Other\n";
		choice = getch();
		cin.ignore();
		cout<<"Enter your complain:\n";
		if(choice==49)
		{
			cout<<"Airport Handling: ";
			types = "Aiprort Handling: ";
		}
		else if(choice==50)
		{
			cout<<"Baggage Delivery: ";
			types = "Baggage Delivery: ";
		}
		else if(choice==51)
		{
			cout<<"Booking and Ticketing: ";
			types = "Booking and Ticketing: ";
		}
		else if(choice==52)
		{
			cout<<"Other: ";
			types = "Other: ";
		}
		getline(cin,sentence);
		cout<<endl<<"Do you want to edit your complain(y/n): ";
		ch=getch();
		if(ch=='Y'||ch=='y')
			goto back;
		else
		{
			cout<<endl<<"Complain noted!\n";
			ofstream outfile;
			outfile.open("complain.txt");
			outfile<<"Name: "<<f_name<<" "<<l_name<<endl
			<<"Phone: "<<p_num<<endl
			<<"Complain:\n"<<types<<sentence;
			outfile.close();

		}
	}
};



class routes{
	public:
		bool print()
		{
			int i,j;
			char ch;
			cout<<"\n\n\n\n\tFollowing are the international flights available"<<endl;
			for(i=0;i<11;i++)
			{
				cout<<endl;
				for(j=0;j<11;j++)
				{
					if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<i_destination[i]<<" to "<<i_destination[j]<<endl;
					}

				}
			}
			cout<<"\n\n\n\n\tFollowing are the local flights available"<<endl;
			for(i=0;i<5;i++)
			{
				cout<<endl;
				for(j=0;j<5;j++)
				{
						if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<l_destination[j]<<endl;
					}
				}
			}
			cout<<endl<<"Do you want to book a flight(y/n) ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl;
				return true;
			}
			else
				return false;
		}

};


int main()
{

	main:
	system("COLOR 9f");
	cout<<"\n\t\t\t\tDATA STRUCTURES AND ALGORITHM MINI PROJECT \n";
	cout<<"\t\t\t\t\tTopic: FLIGHT MANAGEMENT SYSTEM\n";
	cout<<"Team Members:\nEnrollment No.\tName\n21102167\tVarsha Singh\n21102161\tPriyansh Fatwani\n21102163\tYashvardhan Shekhawat\n21102147\tSudhanshu Ranjan\n";
	cout<<"\nPress Enter to continue... ";
	getch();
	system("cls");

	//ASCII art for the title "VERTIGO AIRLINES"
	cout<<"\n\n";
	std::cout << " _   _   _   _   _      _   _   _   _   _   _   _   _  \n";
    std::cout << "| | | | | | | | | |    | | | | | | | | | | | | | | | |\n";
    std::cout << "| H | a | p | p | y |    | A | i | r | l | i | n | e | s |\n";
    std::cout << "|_| |_| |_| |_| |_|    |_| |_| |_| |_| |_| |_| |_| |_|\n";

	cout<<"\n\t\t                            Fly with us around the world!                                 ";
	cout<<"\n";

	cout<<endl<<"\n\n\nWelcome to HAPPY Airlines"<<endl;
	string f_name, l_name, add, pass_no,phone_no;
	int choice,choice2, datedep, date, month, year;
	bool ans;
	char ch;
	time_t t= time(NULL);
	tm* timePtr=localtime(&t);
	date=(timePtr->tm_mday);
	month=(timePtr->tm_mon)+1;
	year=(timePtr->tm_year)+1900;

	//Choice between admin login and user login
	cout<<endl<<"Press 1 for Admin Login"<<endl<<"Press 2 for User Login"<<endl;
	choice = getch();
	system("cls");
	if(choice==49)
	{
		string pass;
		cout<<"Enter Password: ";
		cin>>pass;
		if(pass=="admin")
		{
			cout<<"Access Granted\n";

			system("cls");
			admin:
			cout<<"Welcome to Admin Portal!\n";
			cout<<endl<<"Press 1 to Check Airplane Parking"
			<<endl<<"Press 2 to Check for Bad Weather Conditions"
			<<endl<<"Press 3 to Check for Shortest Path"
			<<endl<<"Press 0 for Exit\n";
			choice2 = getch();
			system("cls");
			switch(choice2)
			{
			case 48:	//choice = 0
			{	//Exit
				cout<<"Thank You for using HAPPY Airlines\n";
				exit(0);
			}

			default:
			{
				cout<<endl<<endl<<"ERROR!!!";
				goto back2;
			}
			case 49:
			{
				cout << "Enter the Number of Happy Airplanes present: ";
				cin >> n;
				// Initialize the board to all false
				memset(board, false, sizeof(board));

				// Solve the airplane parking problem
				if (solveNQueens(0, n)) {
					// Print the solution
					cout<<"Considering the airport as a Matrix with m rows and columns then The Airplanes can be parked as follows:\n\n";
					cout << "Parking configuration:\n";
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							if (board[i][j]) {
								cout << "P ";
							} else {
								cout << ". ";
							}
						}
						cout << endl;
					}
				}
				else{
					cout << "No parking configuration exists at the Moment\n";
				}
				cout<<"\n\nPress Enter to go back to Admin Menu...."<<getch();
				system("cls");
				goto admin;
				break;
			}


			case 50:
			{
				// Solve the maze starting from the top-left corner
				bool success = solveMaze(0, 0);

				cout<<"Considering the path to different airports is displayed through the given Matrix: \n";
				//display the maze
				for(int i=0;i<ROWS;i++)
				{
					cout<<"[ ";
					for(int j=0;j<COLS;j++){
						cout<<maze[i][j]<<" ";
					}
					cout<<"]";
					cout<<endl;
				}
				cout<<"Here 0 represents a clear path, 1 represents bad weather\n\n";


				if (success) {
					// Print the solution path
					cout << "The optimal route with clear weather is:\n";
					cout<<"Source--> ";
					for (auto p : path) {
						cout << "(" << p.first << "," << p.second << ")" << "-->";
					}
					cout<<" Destination\n\n";
				} else {
					cout << "No solution exists.\n";
				}
				cout<<"\n\nPress Enter to go back to Admin Menu...."<<getch();
				system("cls");
				goto admin;
				break;
			}
			case 51:
			{
				string src, dst;
				// Define the graph as an adjacency list
				unordered_map<string, unordered_map<string, int>> graph3 = {
					{"DELHI", {{"CHENNAI", 2200}, {"MUMBAI", 1400}, {"KOLKATA", 1300}, {"AMRITSAR", 450}}},
					{"CHENNAI", {{"DELHI", 2200}, {"MUMBAI", 1200}, {"KOLKATA", 1650}, {"AMRITSAR", 3100}}},
					{"MUMBAI", {{"DELHI", 1400}, {"CHENNAI", 1200}, {"KOLKATA", 2000}, {"AMRITSAR", 1750}}},
					{"KOLKATA", {{"DELHI", 1300}, {"CHENNAI", 1650}, {"MUMBAI", 2000}, {"AMRITSAR", 1700}}},
					{"AMRITSAR", {{"DELHI", 450}, {"CHENNAI", 3100}, {"MUMBAI", 1750}, {"KOLKATA", 1700}}}
				};
				//display the graph
				cout<<"Considering the cities as nodes and the distance between them as the weight of the edge between them, the graph is as follows:\n\n";
				cout<<"\nSource: (Destination, Distance)\n";
				for (auto& source : graph3) {
				cout << source.first << ": ";
				for (auto& dest : source.second) {
					cout << "(" << dest.first << ", " << dest.second << ") ";
				}
				cout << endl;
				}
				cout<<"\n\n";

				// Get the source and destination city from the user
				cout << "Enter source city (DELHI, CHENNAI, MUMBAI, KOLKATA, AMRITSAR): ";
				cin >> src;
				cout << "Enter destination city (DELHI, CHENNAI, MUMBAI, KOLKATA, AMRITSAR): ";
				cin >> dst;
				int dist = dijkstra(src, dst);
				if (dist == numeric_limits<int>::max()) {
					cout << "\n\nNo route found between " << src << " and " << dst << endl;
				} else {
					cout << "\n\nThe Shortest Distance between " << src << " and " << dst << " is " << dist << " km" << endl;
				}
				cout<<"\n\nPress Enter to go back to Admin Menu...."<<getch();
				system("cls");
				goto admin;
				break;
			}

			}

			goto admin;
		}
		else
		{
			cout<<"Access Denied\n";

			system("cls");
			goto main;
		}
	}
	else if(choice==50)
	{
	back2:
	cout<<"Welcome to User Portal!\n";
	cout<<endl<<"Press 1 for Booking"
	<<endl<<"Press 2 for Routes"
	<<endl<<"Press 3 for Complaint"
	<<endl<<"Press 4 for Manage"
	<<endl<<"Press 0 for Exit\n";
	choice = getch();
	system("cls");
	switch(choice)
	{
		case 49:
			{
				my:
				cout<<">>>>>>>>>>BOOKING<<<<<<<<<<<\n";
				passenger *ptr;
				cout<<"Enter Your First Name: ";
				cin>>f_name;
				cin.ignore();
				cout<<"Enter Your Last Name: ";
				getline(cin,l_name);
				cout<<"Enter Your Address(Using Commas only): ";
				getline(cin,add);
				cout<<"Enter Your Phone Num(Without -): ";
				cin>>phone_no;
				date:
				cout<<"Enter date of departure(DDMMYYYY): ";
				cin>>datedep;
				booking obj1(f_name,l_name,phone_no,add,pass_no,datedep);
				ptr = &obj1;
				back:
				cout<<endl<<"1.Local Destination\n2.International Destination\n3.Back\n4.Exit\n";
				choice = getch();

				if(choice==49)
				{

					if(ptr->ldest()==false)
					{
						cout<<endl<<"We do not fly to this place\nPlease Choose again\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						ptr->seats();
						ptr->Meals();
						ptr->Registration();
						system("cls");
						ans = ptr->display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl<<endl
							<<"Would you like to avail our Pick'n Drop facility?(y/n)";
							ch = getch();
							if(ch=='y'||ch=='Y')
								ptr->drive();
							else if(ch=='n' || ch=='N')
							{
								ofstream ofile;
								ofile.open("flight.txt", ios::app);
								ofile<<endl<<endl<<"Pick'n Drop: NO";
								ofile.close();
							}
							getch();
							system("cls");
							goto back2;
						}
					}
				}
				else if(choice==50)
				{
					cout<<endl<<"Enter Your Passport Num(Without \"-\"): ";
					cin>>pass_no;
					ans = ptr->idest(pass_no);
					if(ans==false)
					{
						cout<<endl<<"We do not fly to this place\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						ptr->seats();
						ptr->Meals();
						ptr->Registration();
						system("cls");
						ans = ptr->display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl<<endl
							<<"Would you like to avail our Pick'n Drop facility?(y/n)";
							ch = getch();
							if(ch=='y'||ch=='Y')
								ptr->drive();
							else if(ch=='n' || ch=='N')
							{
								ofstream ofile;
								ofile.open("flight.txt", ios::app);
								ofile<<endl<<endl<<"Pick'n Drop: NO";
								ofile.close();
							}
							getch();
							system("cls");
							goto back2;
						}
					}
				}
				else if(choice==51)
				{
					system("cls");
					goto back2;
				}
				else
					exit(0);
				break;
			}

			case 50:	//choice = 2
				{
					cout<<">>>>>>>>>>ROUTES<<<<<<<<<<<\n";
					routes obj;
					ans = obj.print();
					if(ans==true)
						goto my;
					else if(ans==false)
					{
						cout<<endl;
						system("cls");
						goto back2;
					}
					break;
				}

			case 51:	//choice = 3
				{
					cout<<">>>>>>>>>>COMPLAINT<<<<<<<<<<<\n";
					cout<<"Enter Your First Name: ";
					cin>>f_name;
					cin.ignore();
					cout<<"Enter Your Last Name: ";
					getline(cin,l_name);
					cout<<"Enter Your Phone Num(Without -): ";
					cin>>phone_no;
					complain obj(f_name,l_name,phone_no);
					obj.type();
					system("cls");
					goto back2;
					break;
				}


			case 52:
				{
					cout<<">>>>>>>>>>MANAGE<<<<<<<<<<<\n";
					Manage pass;
					chnge:
					choice= pass.change();
					if (choice==1)
					{

						system("cls");
						goto back2;
					}
					else
					{
						cout<<"No record found\n";
						goto chnge;
					}

					break;
				}

			case 48:	//choice = 0
				{
					//Exit
					cout<<"Thank You for using HAPPY Airlines\n";
					exit(0);
				}

			default:
				cout<<endl<<endl<<"ERROR!!!";
				goto back2;
	}
	}
	else
	{
		cout<<"Invalid Input\n";

		system("cls");
		goto main;
	}
    return 0;
}


