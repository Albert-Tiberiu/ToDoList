#include <iostream>
#include<fstream>
#include<windows.h>
using namespace std;
int app=1;
void main_menu()
{
    char x;
    system("CLS");
    cout<<"Activities:"<<endl<<endl;
    ifstream f("day.txt");
    if(!(f.get(x)))
        cout<<"There are no tasks!"<<endl;
    else
    {
    cout<<x;
    while(f.get(x))//f.get citeste si spatiile
        cout<<x;
    }
    f.close();
}
void input(char &nr_ordine)
{
    char in[500],x;
    int input;
    cout<<endl<<"To add a task enter 1.";
    cout<<endl<<"To delete one of the tasks enter 2.";
    cout<<endl<<"To delete all the tasks enter 3.";
    cout<<endl<<"To exit the app enter 0."<<endl;
    cin>>input;
    cin.get();
    if(input==1 && nr_ordine!='z')
        {
        ofstream d("day.txt", ios::app);// cu ios::app nu fac overwriting
        cin.get(in,501);
        nr_ordine++;
        d<<nr_ordine<<"."<<in<<endl;
        d.close();
        }
    else if(input==2)
    {
        char ordine,x;
        string line;
        int nr=0,ok=0;
        cout<<endl<<"Type the letter corresponding to the activity you want to delete.";
        cin>>ordine;
        ifstream f("day.txt");
        ofstream e("dap.txt");
        while(getline(f,line)) //f citeste x pana la intalnirea lui endl(\n) rezultand un sir(line)
        {
            if(nr==ordine-'a') ok=1;
            if(ok==1)
            {
                while(f>>x && getline(f,line))
                {
                e<<ordine<<line<<endl;
                ordine++;
                }
            }
            else
            {
                e<<line<<endl;
                nr++;
            }
        }
        f.close();
        e.close();
        remove("day.txt");
        rename("dap.txt","day.txt");
        nr_ordine=ordine-1;
    }
    else if(input==3)
        {
        ofstream d("day.txt");
        d.close();
        nr_ordine='a'-1;
        remove("ordine.txt");
        }
    else app=0;
    if(nr_ordine=='z') cout<<"Too many tasks. Take a break!:)";
}
int main()
{
    char nr_ordine,x;
    ifstream b("ordine.txt");
    if(!(b>>x)) nr_ordine='a'-1;
    else nr_ordine=x;
    b.close();
    while(app)
    {
    main_menu();
    input(nr_ordine);
    ofstream a("ordine.txt");
    a<<nr_ordine;
    a.close();
    }
return 0;
}
