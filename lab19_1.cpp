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

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream source;
    source.open(filename.c_str());
    string textline;
    char name[100];
    char format[] = "%[^:]: %d %d %d";
    int a,b,c,sum;
    while(getline(source,textline)){
        const char *cText = textline.c_str();
        sscanf(cText,format,name,&a,&b,&c);
        sum = a+b+c;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
    source.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command: ";
    string textline;
    getline(cin,textline);
    int lo = textline.find_first_of(" ");
    command = textline.substr(0,lo);
    key = textline.substr(lo+1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0;i < names.size();i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0;i < names.size();i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    cout << "---------------------------------\n";
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
