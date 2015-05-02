#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iterator>
#include <vector>
#include <utility>
#include <ctime>
#include <fstream>
#include <string>

#define LLI long long int
#define LLU long long unsigned int
#define LI  long int
#define LU  long unsigned
#define MAX(a,b) ((b)^(((a)^(b))&-((a)>(b))))
#define MIN(a,b) ((b)^(((a)^(b))&-((a)<(b))))
#define BUG printf("BUGGEeee");
#define PRINT(n) printf("%d",&n);
#define MOD 1000000007
#define POWER2(v) (v && !(v & (v - 1)))
#define kk argv[1]+argv[2]

using namespace std;


const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

const std::string getDay() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%A", &tstruct);

    return buf;
}

int convert_time(int *hrs,int *min,int *sec,string tim)
{
    int k=0,j=0,prev=0,next=-1;
    char temp[30]="";
    for(int i=0;i<tim.length();i++)
    {
        if(tim[i]==':' && k==0)
        {
            temp[j]='\0';
            *hrs=atoi(temp);
            k=1;
            j=0;
            if(*hrs<=6)
            {
                *hrs+=12;
            }
            //cout<<*hrs;
        }
        else if(tim[i]==':' && k==1)
        {
            temp[j]='\0';
            *min=atoi(temp);
            k=2;
            j=0;
            //cout<<*min;
        }
        else
        {
            temp[j]=tim[i];
            j++;
        }
    }
    temp[j]='\0';
            *sec=atoi(temp);
            //cout<<*sec;

    return ((*hrs)*3600+(*min)*60);
}


//mp is map of <name,index>
//vec contains starting and ending time of every session of every student
//N-> number of students
void dentry(string *mp,vector<pair<string,string> > *vec,string day_name,vector<pair<string,string> > tt,int N)
{
    int i,j,p;
    int time_val[N][tt.size()];
    for(i=0;i<N;i++)
    {
        for(j=0;j<tt.size();j++)
        {
            time_val[i][j]=0;
        }
    }
    int diff1,diff2,diff;
    for(i=0;i<N;i++)
    {
        for(j=0;j<vec[i].size();j++)
        {
            int hrs_s,hrs_e,min_s,min_e,sec_s,sec_e,tot_s,tot_e;
            tot_s=convert_time(&hrs_s,&min_s,&sec_s, vec[i][j].first);
            tot_e=convert_time(&hrs_e,&min_e,&sec_e, vec[i][j].second);
            for(int p=0;p<tt.size();p++)
            {
                int hrs_1,hrs_2,min_1,min_2,sec_1,sec_2,tot_1,tot_2;
                tot_1=convert_time(&hrs_1,&min_1,&sec_1, tt[p].first);
                tot_2=convert_time(&hrs_2,&min_2,&sec_2, tt[p].second);
                if(tot_1<tot_s)
                {
                    diff1=tot_s;
                }
                else
                {
                    diff1=tot_1;
                }
                if(tot_2<tot_e)
                {
                    diff2=tot_2;
                }
                else
                {
                    diff2=tot_e;
                }

                /*if(((diff1==tot_s && diff2==tot_e)|| (diff1==tot_1 && diff2==tot_2)) && ((tot_s>tot_1 && tot_e>tot_2) || (tot_s<tot_1 && tot_e<tot_2)))
                {
                    continue;
                }
                else
                {
                    diff=diff2-diff1;
                    time_val[i][p]+=diff/60;
                }*/

                diff=diff2-diff1;
                if(diff>=0)
                {

                    time_val[i][p]+=diff/60;   	
                }
               

            }
        }
    }

   
    for(i=0;i<N;i++)
    {
    	//cout<<mp[i];
        //cout<<tt.size();
        for(j=0;j<tt.size();j++)
        {
           	//cout<<" "<<time_val[i][j];

            if((time_val[i][j])>=30)
            {
            	//int hrs,min;
            	string start,end,name,date_cur;
            	date_cur=currentDateTime();
            	start=tt[j].first;
            	end=tt[j].second;
            	name=mp[i];
            	cout<<name<<" "<<start<<" "<<end<<" "<<day_name<<" "<<date_cur<<endl;
            }
        }
        //cout<<endl;
    }

}







int main(int argc,char* argv[])
{
    std::string::size_type sz;
    int i,j;
	ifstream ptr("data.txt");
	string line;
    getline(ptr,line);
    int N=atoi(line.c_str());
    string name[N];
    for(i=0;i<N;i++)
    {
        getline(ptr,name[i]);
    }
    vector<pair<string,string> >vec[N];
    for(i=0;i<N;i++)
    {
        getline(ptr,line);
        int K=atoi(line.c_str());
        for(j=0;j<K;j++)
        {
            getline(ptr,line);
            string a,b;
            char temp[20]="";
            int pos=line.find(" ");
            int len=line.length();
            size_t posa=line.copy(temp,pos,0);
            //cout<<posa;
            temp[posa]='\0';
            a=string(temp);
            posa=line.copy(temp,len-pos+1,pos+1);
            temp[posa]='\0';
            b=string(temp);
            pair<string,string> ptemp;
            ptemp.first=a;
            ptemp.second=b;
            vec[i].push_back(ptemp);
            //cout<<a<<" "<<b<<endl;
        }
    }
    //cout<<line;

	string day_name=getDay();
    vector <pair<string,string> > tt(4);
    tt={{"08:30:00","09:25:00"},{"09:25:00","10:20:00"},{"10:30:00","11:25:00"},{"11:25:00","12:20:00"}};
    //cout<<N;
    cout<<day_name;
    dentry(name,vec,day_name,tt,N);
	/*
	string str[2]={"Guri","Aadesh"};
	
	vector <pair<string,string> > vec[2];
	vector <pair<string,string> > vec1(3);
	vec1={{"08:30:20","09:10:00"},{"09:12:20","09:23:21"},{"09:24:00","12:20:00"}};
	vector <pair<string,string> > vec2(3);
	vec2={{"08:30:20","09:10:00"},{"09:12:20","09:23:21"},{"10:20:00","10:20:00"}};
	vec[0]=vec1;
	vec[1]=vec2;
	vector <pair<string,string> > tt(4);
	tt={{"08:30:00","09:25:00"},{"09:25:00","10:20:00"},{"10:30:00","11:25:00"},{"11:25:00","12:20:00"}};*/
	//dentry(str,vec,day_name,tt,2);
	//cout<<hrs<<":"<<min<<":"<<sec;
	return 0;
}


