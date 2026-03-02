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

void importDataFromFile(string file, vector<string> &name, vector<int> &score, vector<char> &grade){
    ifstream fin(file);
    string s;
    while(getline(fin, s)){
        int idx = s.find_first_of(':');
        string lineName = s.substr(0,idx);
        name.push_back(lineName);

        string lineScore = s.substr(idx+2);
        int score1, score2, score3;
        int idx2 = lineScore.find_first_of(' ');
        score1 = stoi(lineScore.substr(0,idx2));
        int idx3 = lineScore.find_first_of(' ',idx2+1);
        score2 = stoi(lineScore.substr(idx2+1,idx3));
        score3 = stoi(lineScore.substr(idx3+1));

        int totalScore = score1 + score2 + score3;
        score.push_back(totalScore);
        grade.push_back(score2grade(totalScore));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin,line);
    int idx = line.find_first_of(' ');
    command = line.substr(0,idx);
    key = line.substr(idx+1);
}

void searchName(vector<string> &name, vector<int> &score, vector<char> &grade, string key){
    cout << "---------------------------------\n";
    string keyUpper = toUpperStr(key);
    for(unsigned int i = 0; i < name.size(); i++){
        string nameUpper = toUpperStr(name[i]);
        if(keyUpper == nameUpper){
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            break;
        }else if(i == name.size()-1){
            cout << "Cannot found.\n";
            break;
        }
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i = 0; i < names.size(); i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(found == false) cout << "Cannot found.\n";
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