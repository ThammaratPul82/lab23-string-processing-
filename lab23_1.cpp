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

void importDataFromFile(string filename,vector<string> &names,vector<int> &score,vector<char> &grade){
    ifstream fin(filename);
    char format[]="%[^:]: %d %d %d";
    string s;
    while(getline(fin,s)){
        char name[100];
        int a,b,c;
        sscanf(s.c_str(),format,name,&a,&b,&c);
        names.push_back(name);
        int sum=a+b+c;
        score.push_back(sum);
        grade.push_back(score2grade(sum));
    }
}

void getCommand(string &command,string &key){
    string txt;
    cout<<"Please input your command:\n";
    getline(cin,txt);
    int posSpace=txt.find_first_of(' ');
    if(posSpace==-1){
        command=txt;
        key="";
    }else{
        command=txt.substr(0,posSpace);
        key=txt.substr(posSpace+1);
    }
}

void searchName(vector<string>names,vector<int>scores,vector<char>grades,string key){
    bool isfound=false;
    for(unsigned i=0;i<names.size();i++){

        if(toUpperStr(names[i])==toUpperStr(key)){
            isfound=true;
            cout<<"---------------------------------\n";
            cout<<names[i]<<"'s score = "<<scores[i]<<"\n";
            cout<<names[i]<<"'s grade = "<<grades[i]<<"\n";
            cout<<"---------------------------------\n";
        }
    }
    if(!isfound){
        cout<<"---------------------------------\n";
        cout<<"Cannot found.\n";
        cout<<"---------------------------------\n";
    }
}

void searchGrade(vector<string>names,vector<int>scores,vector<char>grades,string key){
    cout<<"---------------------------------\n";
    bool found=false;
    for(unsigned i=0;i<grades.size();i++){
        if(grades[i]==key[0]){
            found=true;
            cout<<names[i]<<" ("<<scores[i]<<")\n";
        }
    }
    if(!found){
        cout<<"Cannot found.\n";
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
