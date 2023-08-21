#include<bits/stdc++.h>
#include<sstream>
using namespace std;

void S(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar);
void A(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar);
void B(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar);

void A(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar){

    if(flag == 1)
    return ;

    int old_input_ind = input_ind;
    int old_sent_ind = sent_ind;

    string rem_input = "";
    for(int i = input_ind; i < input.size(); i++){

        rem_input += input[i];

    }
    //grammar[1] is for B
    for(int i = 1; i < grammar[2].size(); i++){

        if(flag == 1)
        return ;

        int break_flag = 0;

        input_ind = old_input_ind;
        sent_ind = old_sent_ind;


        string new_sentential_form = "";
        for(int j = 0; j < sent_ind; j++){

            new_sentential_form += sentential_form[j];

        }

        if(grammar[2][i] != "epsilon"){

            for(int j = 0; j < grammar[2][i].size(); j++){

                new_sentential_form += grammar[2][i][j];

            }
        }

        // now append it the remaining string
        for(int j = sent_ind + 1; j < sentential_form.size(); j++){

            new_sentential_form += sentential_form[j];

        }

        //now checking the terminals matching, if they don't then return, if they will then increment ptrs
        all_steps.push_back({new_sentential_form, "A -> " + grammar[2][i], rem_input});
        int count = all_steps.size();
        string back = "Backtracked, Back to line : ";
        back += to_string(count - 1);

        while(sent_ind < new_sentential_form.size() && input_ind < input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            if(new_sentential_form[sent_ind] != input[input_ind]){

                break;

            } else {

                sent_ind++;
                input_ind++;

            }
        }


        //if both input and sentential form strings are exhausted then make the flag = true and mark the steps for answer
        if(sent_ind == new_sentential_form.size() && input_ind == input.size()){

            flag = 1;
            steps.push_back({new_sentential_form, "A -> " + grammar[2][i], ""});
            // all_steps.push_back({new_sentential_form, "A -> " + grammar[2][i], ""});
            return ;

        }

        //if input string is exhausted and sentential form isn't and we have a terminal at sentential
        if(sent_ind != new_sentential_form.size() && input_ind == input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input is not exhausted and the sentential form is exhausted then just continue with the other productions
        if(sent_ind == new_sentential_form.size() && input_ind != input.size()){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input string is not exhausted and the sentential is also not and obviously we stop at a non terminal
        //at sentential form then just normally call that non terminal function

       if(new_sentential_form[sent_ind] == 'S'){

            steps.push_back({new_sentential_form, "A -> " + grammar[2][i], rem_input});
            // all_steps.push_back({new_sentential_form, "A -> " + grammar[0][i], rem_input});
            int count = all_steps.size();

            S(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();
            
        }else
        if(new_sentential_form[sent_ind] == 'A'){

            steps.push_back({new_sentential_form, "A -> " + grammar[2][i], rem_input});
            // all_steps.push_back({new_sentential_form, "A -> " + grammar[2][i], rem_input});
            int count = all_steps.size();

            A(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }else
        if(new_sentential_form[sent_ind] == 'B'){

            steps.push_back({new_sentential_form, "A -> " + grammar[2][i], rem_input});
            int count = all_steps.size();

            B(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }

        all_steps.push_back({back});

        

    }


}

void B(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar){

    if(flag == 1)
    return ;

    int old_input_ind = input_ind;
    int old_sent_ind = sent_ind;

    string rem_input = "";
    for(int i = input_ind; i < input.size(); i++){

        rem_input += input[i];

    }

    //grammar[1] is for B
    for(int i = 1; i < grammar[1].size(); i++){

        if(flag == 1)
        return ;

        int break_flag = 0;

        input_ind = old_input_ind;
        sent_ind = old_sent_ind;


        string new_sentential_form = "";
        for(int j = 0; j < sent_ind; j++){

            new_sentential_form += sentential_form[j];

        }

        if(grammar[1][i] != "epsilon"){

            for(int j = 0; j < grammar[1][i].size(); j++){

                new_sentential_form += grammar[1][i][j];

            }
        }

        // now append it the remaining string
        for(int j = sent_ind + 1; j < sentential_form.size(); j++){

            new_sentential_form += sentential_form[j];

        }

        all_steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
        int count = all_steps.size();
        string back = "Backtracked, Back to line : ";
        back += to_string(count - 1);
        //now checking the terminals matching, if they don't then return, if they will then increment ptrs
        while(sent_ind < new_sentential_form.size() && input_ind < input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            if(new_sentential_form[sent_ind] != input[input_ind]){

                break;

            } else {

                sent_ind++;
                input_ind++;

            }
        }


        //if both input and sentential form strings are exhausted then make the flag = true and mark the steps for answer
        if(sent_ind == new_sentential_form.size() && input_ind == input.size()){

            flag = 1;
            steps.push_back({new_sentential_form, "B -> " + grammar[1][i], ""});
            // all_steps.push_back({new_sentential_form, "B -> " + grammar[1][i], ""});
            return ;

        }

        //if input string is exhausted and sentential form isn't and we have a terminal at sentential
        if(sent_ind != new_sentential_form.size() && input_ind == input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input is not exhausted and the sentential form is exhausted then just continue with the other productions
        if(sent_ind == new_sentential_form.size() && input_ind != input.size()){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input string is not exhausted and the sentential is also not and obviously we stop at a non terminal
        //at sentential form then just normally call that non terminal function

        if(new_sentential_form[sent_ind] == 'S'){

            steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
            // all_steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
            // int count = all_steps.size();

            S(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();
            
        }else
        if(new_sentential_form[sent_ind] == 'A'){

            steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
            // all_steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
            // int count = all_steps.size();

            A(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }else
        if(new_sentential_form[sent_ind] == 'B'){

            steps.push_back({new_sentential_form, "B -> " +grammar[1][i], rem_input});
            // all_steps.push_back({new_sentential_form, "B -> " + grammar[1][i], rem_input});
            // int count = all_steps.size();

            B(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }

        all_steps.push_back({back});

        

    }

 
}

void S(int &flag, string input, int input_ind, vector<vector<string>> &steps, vector<vector<string>> &all_steps, string sentential_form, int sent_ind, unordered_map<char, int> is_non_terminal, vector<vector<string>> grammar){

    if(flag == 1)
    return ;

    int old_input_ind = input_ind;
    int old_sent_ind = sent_ind;
    string rem_input = "";

    for(int i = input_ind; i < input.size(); i++){

        rem_input += input[i];

    }

    //grammar[1] is for B
    for(int i = 1; i < grammar[0].size(); i++){

        if(flag == 1)
        return ;

        int break_flag = 0;

        input_ind = old_input_ind;
        sent_ind = old_sent_ind;


        string new_sentential_form = "";
        for(int j = 0; j < sent_ind; j++){

            new_sentential_form += sentential_form[j];

        }

        if(grammar[0][i] != "epsilon"){

            for(int j = 0; j < grammar[0][i].size(); j++){

                new_sentential_form += grammar[0][i][j];

            }
        }

        // now append it the remaining string
        for(int j = sent_ind + 1; j < sentential_form.size(); j++){

            new_sentential_form += sentential_form[j];

        }

        all_steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
        int count = all_steps.size();
        string back = "Backtracked, Back to line : ";
        back += to_string(count - 1);
        //now checking the terminals matching, if they don't then return, if they will then increment ptrs
        while(sent_ind < new_sentential_form.size() && input_ind < input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            if(new_sentential_form[sent_ind] != input[input_ind]){

                break;

            } else {

                sent_ind++;
                input_ind++;

            }
        }


        //if both input and sentential form strings are exhausted then make the flag = true and mark the steps for answer
        if(sent_ind == new_sentential_form.size() && input_ind == input.size()){

            flag = 1;
            steps.push_back({new_sentential_form, "S -> " + grammar[0][i], ""});
            // all_steps.push_back({new_sentential_form, "S -> " + grammar[0][i], ""});
            return ;

        }

        //if input string is exhausted and sentential form isn't and we have a terminal at sentential
        if(sent_ind != new_sentential_form.size() && input_ind == input.size() && is_non_terminal[new_sentential_form[sent_ind]] == 0){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input is not exhausted and the sentential form is exhausted then just continue with the other productions
        if(sent_ind == new_sentential_form.size() && input_ind != input.size()){

            all_steps.push_back({back});
            continue ;

        }

        
        //if input string is not exhausted and the sentential is also not and obviously we stop at a non terminal
        //at sentential form then just normally call that non terminal function

        if(new_sentential_form[sent_ind] == 'S'){

            steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // all_steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // int count = all_steps.size();
            S(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();
            
        }else
        if(new_sentential_form[sent_ind] == 'A'){

            steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // all_steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // int count = all_steps.size();
            A(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);

            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }else
        if(new_sentential_form[sent_ind] == 'B'){

            steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // all_steps.push_back({new_sentential_form, "S -> " + grammar[0][i], rem_input});
            // int count = all_steps.size();
            B(flag, input, input_ind, steps, all_steps, new_sentential_form, sent_ind, is_non_terminal, grammar);


            if(flag == 1)
            return ;

            // string back = "Backtracked, Back to line : ";
            // back += char('0' + count);
            // all_steps.push_back({back});

            steps.pop_back();

        }

        all_steps.push_back({back});

    }

}


int main() {

    cout << "NOTE: Here epsilon is marked as &\n";
    cout << "Enter the string\n";
    string input;
    cin >> input;

    string sentential_form = "S";
    unordered_map<char, int> is_non_terminal;

    is_non_terminal['S']++;
    is_non_terminal['B']++;
    is_non_terminal['A']++;

    vector<vector<string>> grammar = {{"S", "nB"}, {"B", "nBAB", "epsilon"}, {"A", "+", "x"}};
    vector<vector<string>> steps, all_steps; //current sentential form, step, remaining input
    int input_ind = 0;
    int sent_ind = 0;
    int flag = 0;
    steps.push_back({sentential_form, "no production", input});
    all_steps.push_back({sentential_form, "no production", input});
    S(flag, input, input_ind, steps, all_steps, sentential_form, sent_ind, is_non_terminal, grammar);

    if(flag != 1){

        all_steps.push_back({"Backtracked, Back to line : 1"});

    }

    cout << "**********The output is****************\n";
    if(flag == 1){

        cout << "\nThe string is accepted\n";
        cout << "\nSTEPS OF ACCEPTANCE ARE:\n";
        cout << "sentential form - Production Applied - Remaining Input\n";
        for(int i = 0; i < steps.size(); i++) {

            for(int j = 0; j < steps[i].size(); j++){

                if(j == 0)
                cout << steps[i][j] << "$" << "\t-----------\t";
                else
                if(j == 1)
                cout << steps[i][j] << "\t-----------\t";
                else
                cout << steps[i][j] << "$";

            }

            cout << endl;

        }

    }else{

        cout << "\nThe string is rejected\n";

    }

    cout << "\nOVERALL STEPS ARE AS FOLLOWS : \n";
    cout << "ind - sentential form - Production Applied - Remaining Input\n";
    for(int i = 0; i < all_steps.size(); i++){

        cout << i + 1 << " : ";
        for(int j = 0; j < all_steps[i].size(); j++){

            if(j == 0 && all_steps[i].size() == 1)
            {
                cout << all_steps[i][j];
                continue ;

            }

            if(j == 0)
            cout << all_steps[i][j] << "$" << "\t-----------\t";
            else
            if(j == 1)
            cout << all_steps[i][j] << "\t-----------\t";
            else
            cout << all_steps[i][j] << "$";

        }

        cout << endl;

    }

    return 0;

}

