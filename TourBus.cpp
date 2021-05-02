#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
using namespace std;

class TourBus
{
private:
    int busId;
    char destination[50];
    char time[20];
    int fair;
    int maxSeats;
public:
    int booked;
    void book()
    {
        booked++;
    }
    int getId()
    {
        return busId;
    }
    char* getDest()
    {
        return destination;
    }
    char* getTime()
    {
        return time;
    }
    int getFair()
    {
        return fair;
    }
    void input();
    void display();
    void show();
};
class Ticket
{
private:
    char name[50];
    int tbid;
    char tdestination[50];
    char ttime[20];
    int tfair;
public:
    void genrate(char cname[],int cbid,char cdestination[],char ctime[],int cfair)
    {
        strcpy(name,cname);
        tbid = cbid;
        strcpy(tdestination,cdestination);
        strcpy(ttime,ctime);
        tfair = cfair;
    }
    void display()
    {
        cout<<name<<"\tBus Id:"<<tbid<<"\t"<<tdestination<<"\t"<<ttime<<"\t"<<tfair<<endl;
    }
};

void TourBus::input()
{
    cout << "Enter bus Id : ";
    cin >> busId;
    cin.get();
    cout << "Enter bus destination : ";
    cin.getline(destination,50);
    cout << "Enter time of bus : ";
    cin.getline(time,20);
    cout << "Enter Fare of the bus : ";
    cin >> fair;
    maxSeats = 50;
    booked = 0;
}
void TourBus::display()
{
    cout<<busId<<"\t"<<destination<<"\t"<<time<<"\t"<<maxSeats<<"\t\t"<<booked<<"\t"<<fair<<endl;
}
void TourBus::show()
{
    cout<<"Bus Id : "<<busId<<endl;
    cout<<"Destination : "<<destination<<endl;
    cout<<"Time : "<<time<<endl;
    cout<<"Fair : Rs."<<fair<<endl;
}

int main()
{
    int ch;
    fstream myFile,myTkt;
    TourBus bus;
    Ticket tkt;
    do
    {
        system("CLS");
        cout<<"================================="<<endl;
        cout<<"Welcome to Tour Bus Ticket System"<<endl;
        cout<<"================================="<<endl;
        cout << "Press 1 - Add a new Tour Bus"<<endl;
        cout << "Press 2 - Display all Tour Bus"<<endl;
        cout << "Press 3 - Book a Ticket"<<endl;
        cout << "Press 4 - Display Booked Ticket"<<endl;
        cout << "Press 5 - Exit"<<endl;
        cout << "Enter Your Choice : ";
        cin >> ch;
        switch(ch)
        {
        case 1:
            myFile.open("tourbus.txt",ios::app | ios::binary);
            bus.input();
            myFile.write((char*)&bus,sizeof(bus));
            myFile.close();
            cout << "Bus added Successfully"<<endl;
            getch();
            break;
        case 2:
            cout<<endl;
            cout<<"BusId"<<"\t"<<"Destination"<<"\t\t"<<"Time"<<"\t\t"<<"MaxSeats"<<"\t"<<"Booked"<<"\t"<<"Fair(Rs.)"<<endl;
            cout<<"=================================================================================="<<endl;
            myFile.open("tourbus.txt",ios::in | ios::binary);
            if(myFile.fail())
                cout << "Can't open file"<<endl;
            else
            {
                while(myFile.read((char*)&bus,sizeof(bus)))
                    bus.display();
            }
            myFile.close();
            cout<<"=================================================================================="<<endl;
            getch();
            break;
        case 3:
            int bid,chk;
            chk=0;
            char name[30];
            cout << "Enter the Bus Id : ";
            cin >> bid;
            cin.get();
            myFile.open("tourbus.txt",ios::in | ios::out |ios::binary);
            if(myFile.fail())
                cout<<"Can't Open File"<<endl;
            else
            {
                while(myFile.read((char*)&bus,sizeof(bus)))
                {

                    if(bus.getId()==bid)
                    {
                        if(bus.booked==50)
                        {
                            cout<<"No Seats Available"<<endl;
                            chk=1;
                            break;
                        }
                        bus.show();
                        chk=1;
                        cout<<"Enter The Customer Name : ";
                        cin.getline(name,30);
                        bus.book();
                        myTkt.open("ticket.txt",ios::app|ios::binary);
                        tkt.genrate(name,bus.getId(),bus.getDest(),bus.getTime(),bus.getFair());
                        myTkt.write((char*)&tkt,sizeof(tkt));
                        myTkt.close();
                        cout<<"Ticket Booked"<<endl;
                        break;
                    }
                }
            }
            if(chk==0)
                    cout<<"No Bus Found"<<endl;
            myFile.close();
            getch();
            break;
        case 4:
            cout<<endl;
            cout<<"-: Booked Tickets :-"<<endl;
            cout<<"================================================================================="<<endl;
            myTkt.open("ticket.txt",ios::in|ios::out|ios::binary);
            if(myTkt.fail())
                cout<<"Can't Open File"<<endl;
            else
            {
                while(myTkt.read((char*)&tkt,sizeof(tkt)))
                    tkt.display();
            }
            myTkt.close();
            cout<<"================================================================================="<<endl;
            getch();
            break;
        default :
            break;
        }
    }while(ch!=5);

    return 0;
}
