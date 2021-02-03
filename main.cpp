#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <limits>
#include <cstdlib>
using namespace std;
//GLOBAL VARIABLES
int systemBudget = 0 ;
int selectedCarIndex ;
int continuewithForget = 0 ;
void login();
void loginAdmin();
void registration();
void forget();
void viewallusers();
void carData();
void motorcycleData();
int main();
void adminchoice();
//THIS FUNCTION RETURNING NEW BUDGET FOR EVERY PAYMENT
float updateSystemBudget(float price){
	systemBudget=systemBudget+price;
	return systemBudget;
}
struct car{
    char car_id[10];
    char car_mark[50];
    char car_model[20];
    char car_colour[20];
    int car_year;
    float car_speed;
    float car_price;
};
struct motorcycle{
    char motorcycle_id[10];
    char motorcycle_mark[50];
    float engine_capacity;
    float engine_power;
    float motorcycle_speed;
    float motorcycle_weight;
    float motorcycle_fuel_capacity;
    float motorcycle_price;
};
/////////////////////////////////////////////
car car[1000];
motorcycle mc[1000];
//ACCESSING CARS.TXT FOR READING INFOS
void cars(){
    ifstream ifs;
    ifs.open("cars.txt");
    int carNum = 0;

    while(!ifs.eof()){
        ifs.getline(car[carNum].car_id,10,' ');
        ifs.getline(car[carNum].car_mark,20,' ');
        ifs.getline(car[carNum].car_model,20,' ');
        ifs.getline(car[carNum].car_colour,20,' ');
        ifs >> car[carNum].car_year;
        ifs.ignore();
        ifs >> car[carNum].car_speed;
        ifs.ignore();
        ifs >> car[carNum].car_price;
        ifs.ignore();
        carNum++;
        ifs>>ws;
    }
    ifs.close();
}
//ACCESSING MOTORCYCLES.TXT FOR READING INFOS
void motorcycles(){
    ifstream ifs;
    ifs.open("motorcycles.txt");
    int mcNum = 0;
    while(!ifs.eof()){
        ifs.getline(mc[mcNum].motorcycle_id,10,' ');
        ifs.getline(mc[mcNum].motorcycle_mark,20,' ');
        ifs >> mc[mcNum].engine_capacity;
        ifs.ignore();
        ifs >> mc[mcNum].engine_power;
        ifs.ignore();
        ifs >> mc[mcNum].motorcycle_speed;
        ifs.ignore();
        ifs >> mc[mcNum].motorcycle_weight;
        ifs.ignore();
        ifs >> mc[mcNum].motorcycle_fuel_capacity;
        ifs.ignore();
        ifs >> mc[mcNum].motorcycle_price;
        ifs.ignore();
        mcNum++;
        ifs>>ws;
    }
    ifs.close();
}
//THIS FUNCTION RETURNING NUMBER OF CAR FROM THE CAR.TXT
int carCount(){ 
    int numOfCar = 0;
    ifstream ifs("cars.txt");

    string word;
    while (getline(ifs, word)){
        if (!word.empty())
            numOfCar++;
    }
    ifs.close();
    return numOfCar;
}
//RETURNING AVALIBLE MOTORCYCLE NUMBER
int motorcycleCount(){
    int numOfMotorcycles = 0;
    ifstream ifs("motorcycles.txt");
    string word;
    while (getline(ifs, word)){
        if (!word.empty())
            numOfMotorcycles++;
    }
    ifs.close();
    return numOfMotorcycles;
}
//THIS FUNCTION CHECKING DISCOUNT FOR EVERY ITEM 
float checkDiscount(float pricea){
	int discount = rand() % 10;  
	int randomNumber = rand()%200;
	int lastPrice;

	if(randomNumber>= 100){
		cout<<"\n\t\t\t\t\t\tDISCOUNT APPLIED!"<<endl;
		lastPrice = pricea - (pricea * float(float(discount)/100));
		//cout<<lastPrice<<endl;
		return lastPrice;
	}else{
		cout<<"\n\t\t\t\t\t\tDISCOUND DIDNT FOUND!"<<endl;
		return pricea;
	}
}
//THIS FUNCTION WRITED FOR MAKING DIRECT PAYMENT
void directPay(string customerName,float carPrice, float bgt2){
	int index = 0;
	int okey;
	float newBalance;
    carPrice = checkDiscount(carPrice);
    cout<<"\n\t\t\t\t\t\tNew price :"<<carPrice<<endl;
    cout<<"\n\t\t\t\t\t\t------------------------------"<<endl;
	cout<< "\n\t\t\t\t\t\t1.Complete the payment"<<endl;
    cout<< "\n\t\t\t\t\t\t2.Return selection"<<endl;
    cout<< "\n\t\t\t\t\t\tEnter Choice:";	
    cin >> okey;
    system("cls");
    if(okey == 1){
        newBalance = bgt2 - carPrice;
        if(newBalance >= 0){
        	cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
        	cout<<"\n\t\t\t\t\t\t=> System Balance  : "<<updateSystemBudget(carPrice)<<"$"<<endl;
			cout<<"\n\t\t\t\t\t\t=> Current Balance  : "<<newBalance<<"$"<<endl;
            cout<<"\n\t\t\t\t\t\t=> Thank you."<<endl;
        	cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
        	int returnlog;
            cout<< "\n\t\t\t\t\t\tPRESS 1 FOR RETURN LOGIN = ";	
    		cin >> returnlog;
            if(returnlog == 1){
            	main();
			}else{
				cout<<"PLEASE ENTER THE VALID KEY"<<endl;
				system("pause");
				main();
			}
        	
        }else{
        	cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
            cout<<"\n\t\t\t\t\t\t=> Process not completed."<<endl;
            cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
            int returnlog;
            cout<< "\n\t\t\t\t\t\tPRESS 1 FOR RETURN LOGIN = ";	
    		cin >> returnlog;
            if(returnlog == 1){
            	main();
			}else{
				cout<<"PLEASE ENTER THE VALID KEY"<<endl;
				system("pause");
				main();
			}
        }
    }else if(okey == 2){
    	main();
    	return;
    }	
}
//THIS FUNCTION FOR TAKING PAYMENT MONTH BY MONTH , AND EVERY MONTH I ADDED SOME TAX 2$
void montlyPay(float price, float bgt2){
    int monthNum ;
    int okey;
    cout<<"\t\tPlease enter the appropriate month number (Montly price will be calculate):";
    cin>>monthNum;
    
    float montlyPay = (float(price)/float(monthNum))+2;
    float total = (float(montlyPay)*float(monthNum));
   
    for(int i = 0;i<monthNum;i++){
        cout<<"\t\t\t\t\t\t"<< i+1<<". Month = "<< montlyPay<<" $"<<endl;
    }
    cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
    cout<<"\n\t\t\t\t\t\tMontly Total = "<< total<<"$"<<endl;
    total = checkDiscount(total);
    cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
    cout<< "\n\t\t\t\t\t\t1.Complete the payment"<<endl;
    cout<< "\n\t\t\t\t\t\t2.Return selection"<<endl;
    cout<< "\n\t\t\t\t\t\tEnter Choice:";
    cin >> okey;
    system("cls");
    
    if(okey == 1){
         cout<<"\n\t\t\t\t\t\t----------------------------------"<<endl;
        if(bgt2>= total){
            bgt2 = bgt2-float(total);
            cout<<"\n\t\t\t\t\t\t=> YOUR CURRENTLY BALANCE = "<<bgt2<<"$"<<endl;
            cout<<"\n\t\t\t\t\t\t=> PROCESS COMPLETED THANK YOU <="<<endl;
            int returnlog;
            cout<< "\n\t\t\t\t\t\tPRESS 1 FOR RETURN LOGIN = ";	
    		cin >> returnlog;
            if(returnlog == 1){
            	main();
			}else{
				cout<<"\n\t\t\t\t\t\tPLEASE ENTER THE VALID KEY"<<endl;
				system("pause");
				main();
			}
        }else{
            cout<<"\n\t\t\t\t\t\t=> PROCESS NOT COMPLETED (NOT ENOUGH MONEY) THANK YOU <="<<endl;
            int returnlog;
            cout<< "\n\t\t\t\t\t\tPRESS 1 FOR RETURN LOGIN = ";	
    		cin >> returnlog;
            if(returnlog == 1){
            	main();
			}else{
				cout<<"\n\t\t\t\t\t\tPLEASE ENTER THE VALID KEY"<<endl;
				system("pause");
				main();
			}
        }
    }else if(okey == 2){
    	main();
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DISPLAY CAR FOR PRINTING CARS FROM THE LIST 
void displayCar(){
    cars();
    for (int i = 0; i < carCount(); i++){
        cout<<endl;
        cout<<"\t\t\t\t\t\tCar ID : " << car[i].car_id << endl;
        cout<<"\t\t\t\t\t\tCar Mark : " << car[i].car_mark << endl;
        cout<<"\t\t\t\t\t\tCar Model : " << car[i].car_model << endl;
        cout<<"\t\t\t\t\t\tCar Colour : " << car[i].car_colour << endl;
        cout<<"\t\t\t\t\t\tYear : " << car[i].car_year << endl;
        cout<<"\t\t\t\t\t\tCar Speed : " << car[i].car_speed << endl;
        cout<<"\t\t\t\t\t\tYear : " << car[i].car_year << endl;
        cout<<"\t\t\t\t\t\tPrice : " << car[i].car_price << endl;
    }
}
//SHOWING AVALIABLE MOTORCYCLES FROM THE TXT
void displayMotorcycle(){
    motorcycles();
    for (int i = 0; i < motorcycleCount(); i++){
    	cout<<endl;
        cout<<"\t\t\t\t\t\tMotorcycle ID : " << mc[i].motorcycle_id << endl;
        cout<<"\t\t\t\t\t\tMotorcycle Mark : " << mc[i].motorcycle_mark << endl;
        cout<<"\t\t\t\t\t\tEngine Capacity : " << mc[i].engine_capacity << endl;
        cout<<"\t\t\t\t\t\tEngine Power : " << mc[i].engine_power<< endl;
        cout<<"\t\t\t\t\t\tMotorcycle Speed :  " << mc[i].motorcycle_speed << endl;
        cout<<"\t\t\t\t\t\tMotorcycle Weight :  " << mc[i].motorcycle_weight << endl;
        cout<<"\t\t\t\t\t\tFuel Capacity :  " << mc[i].motorcycle_fuel_capacity << endl;
        cout<<"\t\t\t\t\t\tPrice :  " << mc[i].motorcycle_price << endl;
    }
}
//THIS IS FOR ADDING CAR TO TXT WITH ADMIN PANEL
void addCar(){
    ofstream ofs;
    ofs.open("cars.txt" , fstream::app);
    ofs<<endl;

    int newCar = carCount() + 1;
    cout << "\n\n";
    cout << "Please enter the new car information : " << endl;

    cout << "Car ID : "<<endl;
    cin >> ws;
    cin.getline(car[newCar].car_id,10);
    ofs << car[newCar].car_id;
    ofs << " ";

    cout << "Mark : "<<endl;
    cin.getline(car[newCar].car_mark,20);
    ofs << car[newCar].car_mark;
    ofs << " ";

    cout << "Model : "<<endl;
    cin.getline(car[newCar].car_model,20);
    ofs << car[newCar].car_model;
    ofs << " ";

    cout << "Colour : "<<endl;
    cin.getline(car[newCar].car_colour,20);
    ofs << car[newCar].car_colour;
    ofs << " ";

    cout << "Year : "<<endl;
    cin >> car[newCar].car_year;
    ofs << car[newCar].car_year;
    ofs << " ";

    cout << "Speed : "<< endl;
    cin >> car[newCar].car_speed;
    ofs << car[newCar].car_speed;
    ofs << " ";

    cout << "Price : "<<endl;
    cin >> car[newCar].car_price;
    ofs << car[newCar].car_price;
    ofs << " ";

    ofs.close();
    system("cls");
    carData();
    adminchoice();    
}
//THIS IS DELETECAR FUNCTION DELETING CAR FROM THE CARS.TXT
void deleteCar(){
    char id[10];

    ofstream ofs;
    ofs.open("temp.txt");

    displayCar();

    cout << " " <<endl ;
    cout << "Enter the car id number : "<<endl;
    cout<< " ";
    cin >> ws;
    cin.getline(id,10);
    int x=carCount();
    for(int i = 0; i < carCount(); i++){
        if (strcmp(id,car[i].car_id) != 0){
            ofs << car[i].car_id;
            ofs << " ";
            ofs << car[i].car_mark;
            ofs << " ";
            ofs << car[i].car_model;
            ofs << " ";
            ofs << car[i].car_colour;
            ofs << " ";
            ofs << car[i].car_year;
            ofs << " ";
            ofs << car[i].car_speed;
            ofs << " ";
            ofs << car[i].car_price;
            ofs << " ";
            if(i != carCount()){
                ofs<<endl;
            }
        }
    }

    ofs.close();

    remove("cars.txt");
    rename("temp.txt","cars.txt");
    system("cls");
    carData();
    adminchoice();
}
//ADDING MOTORCYCLES
void addMotorcycle(){
    ofstream ofs;
    ofs.open("motorcycles.txt" , fstream::app);
    ofs<<endl;

    int newMotorcycle = motorcycleCount() + 1;
    cout << "\n\n";
    cout << "Please enter the new motorcycle information : " << endl;

    cout << "Motorcycle ID : " << endl;
    cin >> ws;
    cin.getline(mc[newMotorcycle].motorcycle_id,10);
    ofs << mc[newMotorcycle].motorcycle_id;
    ofs << " ";

    cout << "Mark : " << endl;
    cin.getline(mc[newMotorcycle].motorcycle_mark,20);
    ofs << mc[newMotorcycle].motorcycle_mark;
    ofs << " ";

    cout << "Engine Capacity : " << endl;
    cin >> mc[newMotorcycle].engine_capacity;
    ofs << mc[newMotorcycle].engine_capacity;
    ofs << " ";

    cout << "Engine Power : " << endl;
    cin >> mc[newMotorcycle].engine_power;
    ofs << mc[newMotorcycle].engine_power;
    ofs << " ";

    cout << "Speed : " <<endl;
    cin >> mc[newMotorcycle].motorcycle_speed;
    ofs << mc[newMotorcycle].motorcycle_speed;
    ofs << " ";

    cout << "Weight : " <<endl;
    cin >> mc[newMotorcycle].motorcycle_weight;
    ofs << mc[newMotorcycle].motorcycle_weight;
    ofs << " ";

    cout << "Fuel Capacity : " <<endl;
    cin >> mc[newMotorcycle].motorcycle_fuel_capacity;
    ofs << mc[newMotorcycle].motorcycle_fuel_capacity;
    ofs << " ";

    cout << "Price : " <<endl;
    cin >> mc[newMotorcycle].motorcycle_price;
    ofs << mc[newMotorcycle].motorcycle_price;
    ofs << " ";

    ofs.close();
    system("cls");
    motorcycleData();
    adminchoice();    
}
//DELETING MOTORCYCLES FROM TXT
void deleteMotorcycle(){
    char id[10];

    ofstream ofs;
    ofs.open("temp.txt");

    displayMotorcycle();

    cout << " " <<endl ;
    cout << "Enter the motorcycle id number : "<<endl;
    cout<< " ";
    cin >> ws;
    cin.getline(id,10);
    int x=motorcycleCount();
    for(int i = 0; i < motorcycleCount(); i++){
        if (strcmp(id,mc[i].motorcycle_id) != 0){
            ofs << mc[i].motorcycle_id;
            ofs << " ";
            ofs << mc[i].motorcycle_mark;
            ofs << " ";
            ofs << mc[i].engine_capacity;
            ofs << " ";
            ofs << mc[i].engine_power;
            ofs << " ";
            ofs << mc[i].motorcycle_speed;
            ofs << " ";
            ofs << mc[i].motorcycle_weight;
            ofs << " ";
            ofs << mc[i].motorcycle_fuel_capacity;
            ofs << " ";
            ofs << mc[i].motorcycle_price;
            ofs << " ";
            if(i != carCount()){
                ofs<<endl;
            }
        }
    }
    ofs.close();
    remove("motorcycles.txt");
    rename("temp.txt","motorcycles.txt");
    system("cls");
    motorcycleData();
    adminchoice();    
}
//READING CAR INFOS
void carData (){
    ifstream ifs;
    ifs.open("cars.txt");
    int carNum = 0;

    while(!ifs.eof()){
        ifs.getline(car[carNum].car_id,10,' ');
        ifs.getline(car[carNum].car_mark,20,' ');
        ifs.getline(car[carNum].car_model,20,' ');
        ifs.getline(car[carNum].car_colour,20,' ');
        ifs >> car[carNum].car_year;
        ifs.ignore();
        ifs >> car[carNum].car_speed;
        ifs.ignore();
        ifs >> car[carNum].car_price;
        ifs.ignore();
        carNum++;
        ifs>>ws;
    }
    ifs.close();
}
//READING MOTORCYCLES INFOS
void motorcycleData (){
    ifstream ifs;
    ifs.open("motorcycles.txt");
    int motorcycleNum = 0;

    while(!ifs.eof()){
        ifs.getline(mc[motorcycleNum].motorcycle_id,10,' ');
        ifs.getline(mc[motorcycleNum].motorcycle_mark,20,' ');
        ifs >> mc[motorcycleNum].engine_capacity;
        ifs.ignore();
        ifs >> mc[motorcycleNum].engine_power;
        ifs.ignore();
        ifs >> mc[motorcycleNum].motorcycle_speed;
        ifs.ignore();
        ifs >> mc[motorcycleNum].motorcycle_weight;
        ifs.ignore();
        ifs >> mc[motorcycleNum].motorcycle_fuel_capacity;
        ifs.ignore();
        ifs >> mc[motorcycleNum].motorcycle_price;
        ifs.ignore();
        motorcycleNum++;
        ifs>>ws;
    }
    ifs.close();
}

int main() {
	
    int choice;
    system("CLS");
	cout <<"\n\n\n\t\t\t\t\t\tWelcome to Vehicle Rental System";
    cout <<"\n\n\n\t\t\t\t\t\t!! ALL PRICES FOR ONLY 1 WEEK !!";
    cout << "\n\n\n\t\t\t\t\t\t1.Admin Login";
    cout << "\n\t\t\t\t\t\t2.Customer Login";
    cout << "\n\t\t\t\t\t\t3.Register";
    cout << "\n\t\t\t\t\t\t4.Forgot Password ?";
    cout << "\n\t\t\t\t\t\t5.Exit";
    cout << "\n\n\t\t\t\t\t\tEnter Your Choice:";
    cin>>choice;
    switch(choice){
        case 1:
            loginAdmin();
            break;
        case 2:
            login();
            break;
        case 3:
        	system("cls");
            registration();
            break;
        case 4:
        	system("cls");
            forget();
            break;
        case 5:{
        	system("CLS");
            string decide;
            cout<<"\n\t\t\t\t\tDo you want to really exit?(yes/no):";
            cin>>decide;
            if(decide=="yes"){
            cout<<"\n\t\t\t\t\t     We will miss you,goodbye!"<<endl;
                break;
                }
            else {
            	system("CLS");
                main();
            }
                }
        default:
            cout<<"\n\n\t\t\t\t\t    Wrong Choice Try Again please!"<<endl;
            main();
    }
}
//FOR ADMIN PANNEL SHOWING ALL AVALIABLE USERS 
void viewallusers(){
  ifstream vausers("database.txt");
  string line ="";
  int i=1;

  if ( vausers.is_open() ){

        cout<<"ID" " ""Name " "Surname " "Age " "National ID " "Budget " "Username" " " "" "Password"<<endl;


    while ( getline(vausers,line) ){


        cout<<(i++)<<"."<<line<< endl;
    }

    vausers.close();
  }

}
//THIS IS FOR ADMIN PANNEL FOR ADDIN / REMOVING / SHOWING METHODS 
void adminchoice(){
	system("CLS");
     int choice;
    cout<<"\n\n\t\t\t\t\t\t-------- Admin Panel --------" << endl;
    cout<<"\n\n\t\t\t\t\t\tTOTAL SYSTEM BALANCE = "<<systemBudget<<" $"<< endl;
	cout<<"\n\n\t\t\t\t\t\t1.Add/Remove Vehicle" << endl;
    cout<<"\t\t\t\t\t\t2.View all vehicles" << endl;
    cout<<"\t\t\t\t\t\t3.View all user" << endl;
    cout<<"\t\t\t\t\t\t4.Log off "<<endl;
    cout<<"\t\t\t\t\t\tEnter choice :";
    cin>>choice;
    switch(choice){
        case 1:{
			char c;
			system("CLS");
			cout<<"\n\n\t\t\t\t\t\tAdmin Panel" << endl;
            cout<<"\n\n\t\t\t\t\t\t1.Add Car"<<endl;
            cout<<"\t\t\t\t\t\t2.Add Motorcycle"<<endl;
            cout<<"\t\t\t\t\t\t3.Remove Car"<<endl;
            cout<<"\t\t\t\t\t\t4.Remove Motorcycle"<<endl;
            cout<<"\t\t\t\t\t\t5.Go Back"<<endl;
            cout<<"\n\n\t\t\t\t\t\tEnter Your Choice:";
            cin>>c;
            if(c=='1'){
            	system("CLS");
                    addCar();
            }
            else if(c=='2'){
            	system("CLS");
            		addMotorcycle();
            }
            else if(c=='3'){
            	system("CLS");
            		deleteCar();
            }
            else if(c=='4'){
            	system("CLS");
            		deleteMotorcycle();
            }
            else if(c=='5'){
            		adminchoice();
            }
            else{
            	cout<<"\n\t\t\t\t\t\tWrong Choice...Try Again!";
            	
            	adminchoice();
            }
           break;
            }
        case 2:{
		system("CLS");
            cout<<"\n\n\t\t\t\t\t\t---ALL CARS---" << endl;
			displayCar();
			cout<<"\n\n\t\t\t\t\t\t---ALL MOTORCYCLES---" << endl;
            displayMotorcycle(); 
        string decissionadmn;
        cout<<"\n\n\t\t\t\t\tDo you want to continue?(yes/no): ";
        cin>>decissionadmn;
        if(decissionadmn=="yes"){
                adminchoice();
            }
            else{
                main();
				}
        break;
		}
        case 3:
            {
            system("CLS");
            cout<<"\n\n\t\t\t\t\t\t---All Users---" << endl;
            cout<< endl;
            viewallusers();
           	
            string decissionadmn;
            cout<<"\n\n\t\t\t\t\tDo you want to continue?(yes/no): ";
            cin>>decissionadmn;
            if(decissionadmn=="yes"){
                adminchoice();
            }
            else{
                main();
            }
            }

        	break;
        case 4:
        	cout<<"\n\n\t\t\t\t\t\t\tExiting..."<<endl;
        	system("CLS");
        	main();
        	
        
        
        default:
            cout<<"\n\n\t\t\t\t\t    Wrong Choice Try Again please!"<<endl;
            adminchoice();
    }
    }
//LOGIN MAIN METHODS
void loginAdmin(){
	system("CLS");
	int counterr=0;
    string adminusername="admin";
    string adminpassword="admin";
    string cadminusername,cadminpassword;
    cout <<"\n\n\n\t\t\t\t\t\tWelcome Admin Panel";
    cout<<"\n\n\n\n\t\t\t\t\t\tUsername:";
    cin>>cadminusername;
    cout<<"\n\t\t\t\t\t\tPassword:";
      char ch;
    ch=_getch();
    while(ch != 13){
      cadminpassword.push_back(ch);
      cout << '*';
      ch = _getch();
   }if(cadminusername==adminusername&&cadminpassword==adminpassword){

        counterr=1;
        }
        if(counterr==1){
            adminchoice();
			}
    else{
        cout<<"\n\n\t\t\t\tWrong password or username! Try Again please!"<<endl;
        system("pause");
        loginAdmin();
    }
}
// Login Section FOR NORMAL USERS
void login(){
	
    int counter;
    string  username,checkusername,checkpassword;
    string password="";
    string name,surname,age,nid;
    float bgt;
    float bgt2;
    system("CLS");
    cout <<"\n\n\n\t\t\t\t\t!! ALL PRICES FOR 1 WEEK !!";
	cout <<"\n\n\n\t\t\t\t\t     Welcome to Vehicle Rental System";
    cout<<"\n\n\n\n\t\t\t\t\t\tUsername:";
    cin>>username;
    cout<<"\n\t\t\t\t\t\tPassword:";
      char ch;
    ch=_getch();
    while(ch != 13){
      password.push_back(ch);
      cout << '*';
      ch = _getch();
   }
    ifstream input("database.txt");
    while(input>>name>>surname>>age>>nid>>bgt>>checkusername>>checkpassword){
        if(checkusername==username&&checkpassword==password){
            counter=1;
            bgt2=bgt;
            system("CLS");
        }
    }
    input.close();
    if(counter==1){
	    int  choice;
	    char carSelect[10];
	    char motorcycleSelect[10];
	    ofstream log;
	    log.open("selection_log.txt", fstream::app);
	    ofstream ofs;
	    ofs.open("temp.txt");
	    cout<<"\n\n";
	    cout<< endl;
		string customerName;
	    char c;
	    	cout<<"\t\t\t\t\t\tWelcome,"<<username<<endl;
			cout<<"\n\t\t\t\t\t  Cars or motorcycle?(1 or 2) : ";
	            cin>>choice;

            if(choice == 1){
            	float carPrice;
            	system("cls");
                cout << "\n\t\t\t\t\t\t----------- Cars ----------- " << endl;
                displayCar();
                cout<< "";
                cout<<"\n\t\t\t\t\t\tPlease select car";
                cout<<"\n\t\t\t\t\t\tEnter car ID : ";
                cin >> ws;
                cin.getline(carSelect,10);
                int x = carCount();
                for(int i = 0; i < carCount(); i++){
                    if (strcmp(carSelect,car[i].car_id) != 0){
                        ofs << car[i].car_id;
                        ofs << " ";
                        ofs << car[i].car_mark;
                        ofs << " ";
                        ofs << car[i].car_model;
                        ofs << " ";
                        ofs << car[i].car_colour;
                        ofs << " ";
                        ofs << car[i].car_year;
                        ofs << " ";
                        ofs << car[i].car_speed;
                        ofs << " ";
                        ofs << car[i].car_price;
                        ofs << " ";
                        if(i != carCount()){
                            ofs<<endl;
                        }
                    }
                }
                ofs.close();
                remove("available.txt");
                rename("temp.txt","available.txt");
                for(int i = 0; i < carCount(); i++){
                    if (strcmp(carSelect,car[i].car_id) == 0){
                        log<<"\nCar : "<<car[i].car_id;
                        log<<"\nMark : "<<car[i].car_mark;
                        log<<"\nModel : "<<car[i].car_model;
                        log<<"\nPrice: "<<car[i].car_price;
                        carPrice = car[i].car_price;
                    }
                }
                log.close();
                system("cls");
                cout << endl;
                int paymentSelection;
                cout<< "\t\t\t\t\t\tPress 1 for Direct pay"<<endl;
                cout<< "\t\t\t\t\t\tPress 2 for Monthly pay"<<endl;
                cout<< "\t\t\t\t\t\tEnter your choice:";
                cin>> paymentSelection;
                cout << endl;
                system("cls");
				if(paymentSelection == 1){
                	directPay(customerName,carPrice,bgt2);
				}else if(paymentSelection == 2){
					montlyPay(carPrice,bgt2);
				}
                cout<<endl;
            }
            else{
            	float motorPrice;
                cout << "\n\t\t\t\t\t\t----------- Motorcycles ----------- " << endl;
                displayMotorcycle();
                cout<< " ";
                cout<<"\n\t\t\t\t\t\tPlease select motorcycle";
                cout<<"\n\t\t\t\t\t\tEnter motorcycle ID : ";
                cin >> ws;
                cin.getline(motorcycleSelect,10);
                int x = motorcycleCount();
                for(int i = 0; i < motorcycleCount(); i++){
                    if (strcmp(motorcycleSelect,mc[i].motorcycle_id) != 0){
                        ofs << mc[i].motorcycle_id;
                        ofs << " ";
                        ofs << mc[i].motorcycle_mark;
                        ofs << " ";
                        ofs << mc[i].engine_capacity;
                        ofs << " ";
                        ofs << mc[i].engine_power;
                        ofs << " ";
                        ofs << mc[i].motorcycle_speed;
                        ofs << " ";
                        ofs << mc[i].motorcycle_weight;
                        ofs << " ";
                        ofs << mc[i].motorcycle_fuel_capacity;
                        ofs << " ";
                        ofs << mc[i].motorcycle_price;
                        ofs << " ";
                        if(i != motorcycleCount()){
                            ofs<<endl;
                        }
                    }
                }
                remove("available2.txt");
                rename("temp2.txt","available2.txt");
                for(int i = 0; i < motorcycleCount(); i++){
                    if (strcmp(motorcycleSelect,mc[i].motorcycle_id) == 0){
                        log<<"\nMotorcycle : "<<mc[i].motorcycle_id;
                        log<<"\nMark : "<<mc[i].motorcycle_mark;
                        log<<"\nPrice: "<<mc[i].motorcycle_price;
                        motorPrice = mc[i].motorcycle_price;
                    }
                }
                log.close();
                system("cls");
                cout<<endl;
                int paymentSelection;
                cout<< "\t\t\t\t\t\tPress 1 for Direct pay"<<endl;
                cout<< "\t\t\t\t\t\tPress 2 for Monthly pay"<<endl;
                cout<< "\t\t\t\t\t\tEnter your choice:";
                cin>> paymentSelection;
                cout << endl;
                system("cls");
				if(paymentSelection == 1){
                	directPay(customerName,motorPrice,bgt2);
				}else if(paymentSelection == 2){
					montlyPay(motorPrice,bgt2);
				}
                cout<<endl;
    }
}
    else{
    	continuewithForget=continuewithForget+1;
        string decide;
        if(continuewithForget !=3){
	        cout<<"\n\t\t\t\tPlease check your username or password and try again"<<endl;
	        cout<<"\n\t\t\t\tDo you want to try again?(yes/no):";
	        cin>>decide;
	        if(decide=="yes"){
	        login();
	        }
	        else{
	            main();
	        }
		}else{
			forget();
		}
        
    }
}
//Adding User to data.txt
void registration(){
    string name,surname;
    int age;
    string id;
    float budget;
    cout <<"\n\n\n\t\t\t\t\tWelcome to Vehicle Rental System";
    cout<<"\n\n\n\t\t\t\t\tEnter your name:";
    cin>>name;
    cout<<"\n\t\t\t\t\tEnter your surname:";
    cin>>surname;
    cout<<"\n\t\t\t\t\tEnter your age:";
    cin>>age;
    cout<<"\n\t\t\t\t\tEnter your National ID:";
    cin>>id;
    cout<<"\n\t\t\t\t\tEnter your Budget:";
    cin>>budget;
    string regusername,regpassword;
    cout<<"\n\t\t\t\t\tEnter new username:";
    cin>>regusername;
    ifstream check("data.txt");
    string tempusername,tempHold;
    while(check>>tempusername&&check>>tempHold){
        if(tempusername==regusername){
            cout<<"\n\n\t\t\t\t\t Username already exist";
            check.seekg(0,ios::beg);
            cout<<"\n\t\t\t\t\tEnter new username:";
            cin>>regusername;
        }
    }
    cout<<"\n\t\t\t\t\tEnter new Password:";
    cin>>regpassword;
    ofstream reg("data.txt",ios::app);
    reg<<regusername<<" "<<regpassword<<" "<<id<<endl;
    ofstream regg("database.txt",ios::app);
    regg<<name<<" "<<surname<<" "<<age<<" "<<id<<" "<<budget<<" "<<regusername<<" "<<regpassword<<endl;

    cout<<"\n\t\t\t\t\tRegistration completed succesfully!";
    string decide;
    cout<<"\n\n\t\t\t\t\tDo you want to Login?(yes/no):";
    cin>>decide;
    if(decide=="yes"){
        login();
    }
    else{
        main();
    }
}
//Forget Password
void forget(){
    int counter_forget=0;
    string uname,id,searchuser,searchpass,searchid;
    system("CLS");
    cout <<"\n\n\n\t\t\t\t\tWelcome to Vehicle Rental System ";
    cout <<"\n\n\n\t\t\t\t\t\tPASSWORD REMINDER ";
    cout<<"\n\n\n\n\t\t\t\t\tPlease Enter your username:";
    cin>>uname;
    cout<<"\n\t\t\t\t\tPlease Enter your National ID:";
    cin>>id;
    ifstream searchusername("data.txt");
    while(searchusername>>searchuser>>searchpass>>searchid){
        if(searchid==id&&searchuser==uname){
            counter_forget=1;
        }
    }
    searchusername.close();
    if(counter_forget==1){
        cout<<"\n\t\t\t\t\tYour password is "<<searchpass;
        cin.get();
        int choice ;
		cout<<"\n\n\t\t\t\t\tPress any key for menu ...";
    	cin>>choice;
    	if(choice == 1 ){
    		main();
		}else{
		 	main();	
		}
    }
    else{
        cout<<"\n\t\t\t\t\tWrong Username,Please try again!"<<endl;
        cin.get();
        system("pause");
        system("CLS");
        forget();
    }
}


