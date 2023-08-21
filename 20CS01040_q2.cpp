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

string findSamePrefix(vector<string> temp) {

    // find the prefix that occurs atleast twice in the given rule
    int max_length = 0;
    int first = -1;
    for(int i = 1; i < temp.size(); i++) {

        for(int k = i + 1; k < temp.size(); k++) {

            // cout << temp[k] << endl;
            int count = 0;
            for(int l = 0; l < min(temp[k].size(), temp[i].size()); l++) {

                if(temp[i][l] != temp[k][l]) {

                    break;

                }

                count++;

            }

            max_length = max(max_length, count);

            if(max_length != 0){

                first = i;
                break;
            }
        }

        if(max_length != 0){

            break;
        }

        
    }

    string prefix = "";
    if (first == -1) {

        // cout << "Hi I am prefix returned at findPrefix: " << prefix << endl;
        return prefix;

    } else {

        for(int i = 0; i < max_length; i++) {

            prefix += temp[first][i];

        }

        // cout << "Hi I am prefix returned at findPrefix: " << prefix << endl;
        return prefix;

    }

}

vector<string> eliminateSamePrefix(string prefix,vector<string> &temp, int &next_char) {

    int flag = 0, first = 0;
    vector<string> new_productions;
    char c = (char)('A' + next_char);
    string C = "";
    C += c;
    // cout <<"***********" << C << " " << c <<" "<< next_char <<"**************\n";
    // cout << "Temp prefix and c is: " << prefix << "\n";
    for(int i = 1; i < temp.size(); i++){

        // cout << "###" << temp[i] << "\n";
        flag = 0;
        if(prefix.size() > temp[i].size()){

            continue ;

        }

        for(int j = 0; j < prefix.size(); j++) {

            // cout << i << ":" << temp[i] << endl;
            if(temp[i][j] != prefix[j]) //mismatch
            {
                // cout << i << ":" << temp[i][0] <<"&"<<prefix[j]<< endl;
                flag = 1;
                break;
            }

        }

        if(flag == 1)
        continue ;

        //take the remaining string and form a new production rules
        // char c = (char)('A' + next_char);
        // string C = "" + c;
        int n = temp[i].size();
        if(first == 0)
        new_productions.push_back(C);

        string t = "";
        // cout << "***********" << prefix.size() << "************\n";
        for(int k = prefix.size(); k < temp[i].size(); k++) {

            // cout << "###" << temp[i][k - 1] <<"###"<< endl;
            t += temp[i][k];
            // cout << t << endl;
        }

        if(first == 0){

            temp[i] = prefix;
            temp[i] += c;
            first++;
            next_char++;

        } else {

            temp[i] = "";
            // cout << temp[i] <<"$$$$$$$\n";

        }

        if(prefix.size() < n){

            new_productions.push_back(t);
        }
        else {

            if(prefix.size() == n){

                new_productions.push_back("ϵ");

            }
        }

    }

    // cout << "The temp value is\n";
    // for(int i = 0; i < temp.size(); i++) {

    //     cout << temp[i] << " ";

    // }
    // cout << "\n";

    return new_productions;
}

// abcD|abc
void doLeftFactor(vector<string> curr_rule, vector<vector<string>> &new_grammar, int &next_char) {

    // take the curr rule and left factor it, find the longest common prefix
    // trie is a good idea to implement this but, I will implement without it, deadline is mon and also I got other things to look at
    // vector<vector<string>> temp;
    // temp.push_back(curr_rule);
    new_grammar.push_back(curr_rule);
    bool is_same_prefix = false;
    // unordered_map<int, int> left_factored_productions;
    for(int i = 0; i < new_grammar.size(); i++) {

        // string prefix = findSamePrefix(temp[i]);
        string prefix = findSamePrefix(new_grammar[i]);
        // cout << "the prefix : " << prefix << endl;
        if(prefix.size() == 0){

            // left_factored_productions[i] = 1;
            // cout << "Right here :" <<prefix << "" << " " << new_grammar.size()<<endl;
            is_same_prefix = false;

        } else {

            is_same_prefix = true;

        }

        // cout << "we are at doLeftfactor\n";
        while(is_same_prefix) {

            // temp.push_back(eliminateSamePrefix(prefix, temp[i], next_char));
            // string prefix = findSamePrefix(temp[i]);
            new_grammar.push_back(eliminateSamePrefix(prefix, new_grammar[i], next_char));
            prefix = findSamePrefix(new_grammar[i]);
            // cout << "the prefix : " << prefix << endl;
            // cout << ":The grammar is : \n";
            // for (int p = 0; p < new_grammar[i].size(); p++)
            // cout << new_grammar[i][p] << " ";
            // cout << endl;
            
            // cout << "2nd time\n";
            //  new_grammar.push_back(eliminateSamePrefix(prefix, new_grammar[i], next_char));
            // prefix = findSamePrefix(new_grammar[i]);
            // cout << "the prefix : " << prefix << endl;
            // cout << ":The grammar is : \n";
            // for (int p = 0; p < new_grammar[i].size(); p++)
            // cout << new_grammar[i][p] << " ";
            // cout << endl;

            // cout << "3rd tine prefix is : \n";
            // prefix = findSamePrefix(new_grammar[i]);
            // cout << "the prefix : " << prefix << endl;
            if(prefix.size() == 0){

                // cout << "Hiii\n";
                break;
                is_same_prefix = false;

            } else {

                is_same_prefix = true;

            }

            // break ;

        }

    }
    return ;
}

void processInput(string str, vector<string> &temp, int &next_char) {

    // cout << str << endl;
    string k = removeSpaces(str);
    // cout << k << endl;
    string token;
    istringstream iss(k);
    int count = 0;
    while(getline(iss, token, '|')) {

        // cout << token << endl;
        if(count == 0) {

            string t = "";
            t = t + token[0];
            
            if(token[0] >= 'A' && token[0] <= 'Z')
            next_char = max(next_char, (token[0] - 'A') + 1);

            temp.push_back(t);

            // token[3] to token.size()

            t = "";
            // cout << "Our suspect : "<<token[4] << endl;
            for(int i = 3; i < token.size(); i++) {

                t += token[i];

                if(token[i] >= 'A' && token[i] <= 'Z')
                next_char = max(next_char, (token[i] - 'A') + 1);

            }

            // cout <<"^^^^^^^^^^^^^^^^"<< token << t << endl;
            temp.push_back(t);

        } else {

            for(int i = 0; i < token.size(); i++){

                if(token[i] >= 'A' && token[i] <= 'Z')
                next_char = max(next_char, (token[i] - 'A') + 1);

                // cout <<token[i]<< " " << next_char << " " <<char(next_char + 'A')<< endl;
            } 

            temp.push_back(token);

        }

        count++;

    }
}
int main() {

    cout << "NOTE : General instructions, non terminals are capital letters with single character\nFor the introduction of new non terminals I have taken the maximum non terminal in the input grammar and from there I keep on adding one for a new non terminal\n";
    cout << "\nEnter the no.of lines in the grammar\n";
    int n;
    cin >> n;
    int count = 0;
    // unordered_map<char, int> translator;
    int next_char = INT_MIN;
    vector<vector<string>> grammar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter grammar productions\n";
    // fflush(stdin);
    for(int i = 0; i < n; i++) {
        
        string str;
        // fflush(stdin);
        getline(cin, str);

        vector<string> temp;
        processInput(str, temp, next_char);

        grammar.push_back(temp);

    }

    // cout << "*****************\n";
    // for(int i = 0; i < grammar.size(); i++) {

    //     for(int j = 0; j < grammar[i].size(); j++) {

    //         cout << grammar[i][j] << " ";

    //     }

    //     cout << "\n";
    
    // }
    // cout << "*****************\n";
    vector<vector<string>> new_grammar;
    // int back = 0;
    for(int i = 0; i < grammar.size(); i++) {

        //find longest prefix among all the productions of a non terminal
        doLeftFactor(grammar[i], new_grammar, next_char);

    }

    cout << "\nThe required left factored grammar is : \n";
    for(int i = 0; i < new_grammar.size(); i++) {

        cout << new_grammar[i][0] <<" -> ";
        for(int j = 1; j < new_grammar[i].size(); j++){

            cout << new_grammar[i][j] << " ";

        }
        cout << endl;
    }


}

// Test cases(Gate questions)
// A -> aAB | aBc | aAc

// S -> aSSbS | aSaSb | abb | b

// S->iEtS|iEtSeS|a 
// E->b