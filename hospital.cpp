#include<iostream>
using namespace std;
//-Global_Variables-
//maximum no of spec
const int Max_Spec=20;
//max no of patients in spec
const int Max_queue=5;
//-arrays to save and control data-
//names in each spec and it's order
string names[Max_Spec][Max_queue];
//status in each spec and it's order
int status[Max_Spec][Max_queue]; //0=regular , 1=urgent
//Number of patients in each spec
int queue_length[Max_Spec];
int menu()
{
    short choice=-1;
    while(choice==-1)
    {
        cout << "\nEnter your choice:\n";
		cout << "1) Add new patient\n";
		cout << "2) Print all patients\n";
		cout << "3) Get next patient\n";
		cout << "4) Exit\n";
        cin>>choice;
        if(choice>4||choice<1)
        {
            puts("enter right NO");
            choice=-1;
        }
    }
    return choice;
}
void print_patient(int spec,string name_p[],int stat_p[])
{
    int len=queue_length[spec];
    if(len==0)
        return;
    cout<<"there are "<<len<<" patients in spec "<<spec<<" and are:\n";
    for(int i=0;i<len;i++)
    {
        cout<<name_p[i]<<' ';
        if(stat_p[i]==0)
            puts("regular");
        else
            puts("urgent");
    }
}
void print_patients()
{
    puts("*_______________________*");
    for(int spec=0;spec<Max_Spec;spec++)
        print_patient(spec,names[spec],status[spec]);
}
//used to shift patients right to add urgent patients first
void Right_Shift(int spec, string names_sp[], int status_sp[])
{
    int len=queue_length[spec];
    for(int i=len-1;i>=0;i--)
    {
        names_sp[i+1] = names_sp[i];
		status_sp[i+1] = status_sp[i];
    }
	queue_length[spec]++;
}
//used to add New patients
bool add_patient()
{
    puts("Enter patients Name,Spec,Status");
    //patient charactastics
    int spec;
    int stats;//0=regular , 1=urgent
    string name;
    cin>>name>>spec>>stats;
    int len=queue_length[spec];
    if(queue_length[spec]>=5)
    {
        puts("Sorry No Room Avaliable");
        return false;
    }
    if(stats==0)//REGULAR ADD
    {
        names[spec][len]=name;
        status[spec][len]=stats;
        queue_length[spec]+=1;
    }
    else//URGENT
    {        
        Right_Shift(spec, names[spec], status[spec]);
        names[spec][0]=name;
        status[spec][0]=stats;
    }
    return true;
}
void left_shift(int spec, string names_sp[], int status_sp[])
{
    int len=queue_length[spec];
    for(int i=1;i<=len;i++)
    {
        names_sp[i-1] = names_sp[i];
		status_sp[i-1] = status_sp[i];
    }
	queue_length[spec]--;
}
void next_patient()
{
    puts("which spec\n");
    int spec,len;
    cin>>spec;
    len=queue_length[spec];
    if(len==0)
    {
        puts("No Patients have a rest");
        return;
    }
    cout<<names[spec][0]<<' ';
    if(status[spec][0]==0)
        puts("regular");
    else
        puts("urgent");
        left_shift(spec,names[spec],status[spec]);
}

void hospital_system()
{
    while(true)
    {
    short choice=menu();
    if(choice==1)
        add_patient();
    else if(choice==2)
        print_patients();
    else if(choice==3)
        next_patient();
    else
        break;
    }
}
int main()
{
    hospital_system();
}