#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &score,vector<char> &grades){
ifstream table(filename.c_str());
string textline;
char format[]="%[^:]: %d %d %d";
int j=0;
while(getline(table,textline))
{
    int totalscore[3];
    char nametemp[100];
    sscanf(textline.c_str(),format,nametemp,&totalscore[0],&totalscore[1],&totalscore[2]);
    names.push_back(nametemp);
    for (int i = 1; i < 3; i++)
    {
        totalscore[0]+=totalscore[i];
    }
    score.push_back(totalscore[0]);
    grades.push_back(score2grade(score[j]));
    j++;
}
table.close();
}

void getCommand(string &command,string &keys){
string text;
cout<<"Please input your command: ";
getline(cin,text);
char format[]="%s %[^:]";
char com[100],k[100];
sscanf(text.c_str(),format,com,k);
command=com;
keys=k;
}

void searchName(vector<string> &names,vector<int> &score,vector<char> &grade,string key){
cout<<"---------------------------------\n";
int k=0;
for (unsigned int i = 0; i < names.size(); i++)
{
   
    string temp=toUpperStr(names[i]);
    if(temp==key)
    {
        cout<<names[i]<<"'s score = "<<score[i]<<endl;
        cout<<names[i]<<"'s grade = "<<grade[i]<<endl;
        k++;
    }
}
if(k==0)cout<<"Cannot found.\n";
cout<<"---------------------------------\n";
}

void searchGrade(vector<string> &names,vector<int> &score,vector<char> &grade,string key){

cout<<"---------------------------------\n";
for (unsigned int i = 0; i < names.size(); i++)
{
    char kk=key[0];
    if(grade[i]==kk)
    {
        cout<<names[i]<<" ("<<score[i]<<")"<<endl;
    }
}
cout<<"---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
