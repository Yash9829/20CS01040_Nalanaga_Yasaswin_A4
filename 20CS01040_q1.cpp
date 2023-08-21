#include<bits/stdc++.h>
#include<sstream>
using namespace std;
string removeSpaces(string str) {

    string temp = "";
    for(int i = 0; i < str.size(); i++) {

        if(str[i] != ' '){

            temp += str[i];

        }
    }
    return temp;
}
void processInput(string str, vector<string> &temp) {

    cout << str << endl;
    string k = removeSpaces(str);
    string token;
    istringstream iss(str);
    int count = 0;
    while(getline(iss, token, '|')) {

        if(count == 0) {

            string t = "";
            t = t + token[0];
            temp.push_back(t);

            // token[3] to token.size()

            t = "";
            for(int i = 3; i < token.size(); i++) {

                t += token[i];

            }

            temp.push_back(t);

        } else {

            temp.push_back(token);

        }

        count++;

    }
}
int main() {

    cout << "Note 1: Non terminals are from A to Z only, remaining all considered as terminals\n";
    cout << "Note 2: The terminals of the grammar should be single characters, else I can't distinguish between different terminals come together\n";
    cout << "Enter the no.of lines in the grammar\n";
    int n;
    cin >> n;
    int count = 0;
    // unordered_map<char, int> translator;

    vector<vector<string>> grammar;
    cout << "enter a non cyclic, no epsilon production grammar\n";
    for(int i = 0; i < n; i++) {
        
        string str;
        fflush(stdin);
        getline(cin, str);

        vector<string> temp;
        processInput(str, temp);

        grammar.push_back(temp);

    }


}