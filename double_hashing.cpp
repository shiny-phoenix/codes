#include <bits/stdc++.h>
using namespace std;

struct Rec
{
        int prn;
        int marks;
        int link;
};

int main()
{
        int size = 23;
        int roll;
        int mrk;
        int insert_count = 0;
        int search_count = 0;
        Rec arr[size];
        for (int i = 0; i <size; i++)
        {
                arr[i].prn = -1;
                arr[i].marks = -1;
                arr[i].link = -1;
        }
        int choice;
        
        do
        {
               cout<<"enter your choice : "<<endl;
               cout<<"1. insert "<<endl;
               cout<<"2. delete "<<endl;
               cout<<"3. search "<<endl; 
               cout<<"4. display "<<endl;
               cout<<"5.quit   " <<endl;
               cin>>choice;     
               
               switch(choice)
               {
                        case 1 :
                                 //insert();
                                 insert_count = 0;
                                  cout<<"enter prn and marks : ";
                                  cin>>roll>>mrk;
                                  int x;
                                  x =(roll%size); 
                                  while(1)
                                  {
                                        if(arr[x%size].prn == -1)
                                        {
                                                insert_count ++;
                                                arr[x%size].prn = roll;
                                                arr[x%size].marks = mrk;
                                                break;
                                        }
                                        else                                    x = 11 - (roll%11);                                         
                                  }            
                                  cout<<"no of comparisons required for insertion: "<<insert_count<<endl;

                                 break;
                        case 2 :
                                 //delete();
                                 
                                 cout<<"enter prn to be deleted ";
                                 cin>>roll;
                                 
                                 
                                 if (arr[roll%size].prn == roll)
                                 {
                                        arr[roll%size].prn = -1;
                                        arr[roll%size].marks  = -1;
                                 } 
                                 else
                                 {
                                        int y = roll%size;
                                        y++;
                                        while(y%size!= roll%size)
                                        {
                                                if (arr[y%size].prn == roll)
                                                  {
                                                        arr[y%size].prn = -1;
                                                        arr[y%size].marks = -1;
                                                  }
                                                  else          y++;
                                        }  
                                 }
                                 break;

                        case 3 :
                                //search();
                                search_count = 0;
                                cout<<"enter prn to search "<<endl;
                                cin>>roll;
                                
                                if (arr[roll%size].prn == roll)
                                 {
                                        cout<<"prn found at index "<<roll%size<<" with no of comparisons : 1"<<endl;
                                        
                                 } 
                                 else
                                 {
                                        int y = roll%size;
                                        int z = y;
                                        y++;
                                        bool flag = 0;
                                        int i = 2;
                                        while(y%size!= z)
                                        {
                                                if (arr[y].prn == roll)
                                                  {
                                                        search_count++;
                                                        cout<<"prn found at index :"<<y%size<<endl;
                                                        cout<<"no of comparisons for searching : "<<search_count<<endl;
                                                        flag = 1;
                                                        break;
                                                  }
                                                  else     
                                                  {
                                                        y+= (2*i) - 1;
                                                        search_count++;
                                                  }
                                        }
                                        if (flag == 0)                   cout<<"prn not found"<<endl;                                        
                                 }
                                break;
                        case 4 :
                                //display();
                                
                                cout<<"prn"<<"\t"<<"marks"<<"\t"<<"link"<<endl;
                                for (int i = 0; i <size; i++)
                                {
                                        cout<<arr[i].prn<<"\t"<<arr[i].marks<<"\t"<<arr[i].link<<endl;
                                }
                                
                                break;
                        default :
                                exit(0);                          
               }             
        }    while (0<choice<4);
               
        return 0;
}