#include <bits/stdc++.h>
#define col 5
#define _s 30
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utils.h"
using namespace std;

int init[20],fin[20],a=0,b=0;
string init_dfa[_s],fin_dfa[_s];
int _a = 0, _b = 0;


//put initial value (-1)  in the table (null)
void reset(int nfa_table[][col]){
    for(int i=0;i<500;i++){
        for(int j=0;j<col;j++){
            nfa_table[i][j]=-1;
        }
    }
}



void nfa_initial_final(){
    cout<<"initial states: ";
    for(int i=0;i<a;i++)
        cout<<init[i]<<" ";
        cout<<endl;

        cout<<"final states: ";
    for(int i=0;i<b;i++)
        cout<<fin[i]<<" ";
        cout<<endl;
}


void dfa_initial_final(){
    cout<<"initial states: ";
    for(int i=0;i<_a;i++)
        cout<<init_dfa[i]<<" ";
        cout<<endl;
        cout<<"final states: ";
    for(int i=0;i<_b;i++)
        cout<<fin_dfa[i]<<" ";
        cout<<endl<<endl;
    for(int i=0;i<60;i++)
            cout<<"-";
    cout<<endl<<endl;
}

void minimize_final_state(int x){
    for(int i=x; i<b-1; i++)
        fin[i] = fin[i+1];
        b= b-1;
}

int regexToNfa(string s,int nfa_table[][col]){
    int l = s.length(); //string s is the result generated from postfix
    int states = 1;
    int m,n,j,counter;
    for(int i=0;i<l;i++){
        char x = s[i];

            if(x== 'x'){ nfa_table[states][0] = states;     // add 1 in the row 1 and column 0
                        init[a] = states;                   // init = 1
                         a= a+1;                            // a stores initial state, a = 1
                            states = states+1;              // states = 2
                      nfa_table[states-1][1] = states;      // add 2 in the row 1 and column 1 (number of states)
                        fin[b] = states;                    // fin = 2
                        b= b+1;                             // b stores the final state
                      nfa_table[states][0] = states;        // add 2 in the row 2 and column
                            states = states+1;              // states = 3
            }
            else if (x=='y'){ nfa_table[states][0] = states;    // add 3 in the row 3 and column 0
                        init[a] = states;
                         a = a+1;
                            states = states + 1;
                      nfa_table[states-1][2] = states;
                          fin[b] = states;
                          b = b+1;
                      nfa_table[states][0] = states;
                            states =states+1;
            }
            else if(x=='.'){ m = fin[b-2];
                      n = init[a-1];
                      nfa_table[m][3]=n;
                      minimize_final_state(b-2);     //reduces final state
                      a = a-1;                       //reduces initial states
            }
            else if(x== '|'){ for(j=a-1,counter=0;counter<2;counter++){
                        m = init[j-counter];
                        nfa_table[states][3+counter]=m;
                      }
                      a=a-2;
                      init[a]=states;
                      a = a+1;
                      nfa_table[states][0] = states;
                      states =states+1;
                      for(j=b-1,counter=0;counter<2;counter++){
                        m = fin[j-counter];
                        nfa_table[m][3]=states;
                      }
                      b=b-2;
                      fin[b]=states;
                      b=b+1;
                      nfa_table[states][0] = states;
                      states= states+1;
            }
            else if(x== '*'){ m = init[a-1];
                      nfa_table[states][3] = m;
                      nfa_table[states][0] = states;
                      init[a-1] = states;

                      states = states+1;
                      n = fin[b-1];
                      nfa_table[n][3]=m;
                      nfa_table[n][4]=states;
                      nfa_table[states-1][4]=states;
                      fin[b-1]=states;
                      nfa_table[states][0]=states;
                      states =states+1;

        }
    }
  return states;
}

void print_nfa_table(int nfa_table[][col],int states){
    cout<<endl;
    cout<<"nfa transition table:"<<endl<<endl;
    cout<<setw(10)<<"States"<<setw(10)<<"x"<<setw(10)<<"y"<<setw(10)<<"e"<<setw(10)<<"e"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    for(int i=1;i<states;i++){
        for(int j=0;j<col;j++){
            if(nfa_table[i][j]==-1)
                cout<<setw(10)<<"_";
            else
                cout<<setw(10)<<nfa_table[i][j];
        }
        cout<<endl;
    }

    cout<<endl;
    cout<<endl;
    nfa_initial_final();
}



void print_dfa_table(string dfa_tab[][3],int state){
    cout<<endl<<endl;
    cout<<endl<<endl;
    cout<<setw(10)<<"dfa transistion table"<<endl<<endl;
    cout<<setw(10)<<"States"<<setw(10)<<"a"<<setw(10)<<"b"<<endl;
    for(int i=0;i<60;i++)
        cout<<"-";
    cout<<endl;
    for(int i=0;i<state;i++){
        for(int j=0;j<3;j++){
            cout<<setw(10)<<dfa_tab[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    //dfa_initial_final();
}
vector <int> eclosure(int nfa_table[][col], int x){
    stack <int> s;
    map <int, int> m;
    vector <int> v;
    int y;

    s.push(x);
    m[x] = 1;

    while(!s.empty()){
        y = s.top();
            s.pop();
        if(nfa_table[y][3] == -1)
            continue;
        else{
            s.push(nfa_table[y][3]);
            m[nfa_table[y][3]] = 1;

            if(nfa_table[y][4] == -1)
                continue;
            else{
                s.push(nfa_table[y][4]);
                m[nfa_table[y][4]] == -1;
            }
        }
    }

    map <int, int> ::iterator itr;
    itr = m.begin();

    while(itr != m.end()){
        v.push_back(itr->first);
        itr++;
    }
    return v;
}

/*
   state_name() function gives a new name to all new dfa state.
*/
string state_name(int i){
    char s = 'q';
    string p ;
    p =p+s;
    if(i==0){
            p = p+'0';
        return p;
    }
   int a[100];
   int j=0;
    while(i>0){
        int x = i%10;
        a[j]=x;
        j = j+1;
        i = i/10;
    }
    for(int i=j-1;i>=0;i--){
            int x = a[i];
        switch(x){
            case 0: p =p+'0';
                    break;
            case 1: p =p+'1';
                    break;
            case 2: p =p+'2';
                    break;
            case 3: p =p+'3';
                    break;
            case 4: p =p+'4';
                    break;
            case 5: p =p+'5';
                    break;
            case 6: p =p+'6';
                    break;
            case 7: p =p+'7';
                    break;
            case 8: p =p+'8';
                    break;
            case 9: p =p+'9';
                    break;

        }
    }
    return p;
}

//checks if it's initial state
void is_initial(vector <int> v, string s){
    for(int i=0;i<v.size();i++){
        if(v[i] == init[0]){
            init_dfa[_a] = s;
            _a = _a+1;
        }
    }
}

//checks if it's final state
void is_final(vector <int> v, string s){
    for(int i=0;i<v.size();i++){
        if(v[i] == fin[0]){
            fin_dfa[_b] = s;
            _b = _b+1;
        }
    }
}

bool is_valid(string word){
    int len = word.length();
    int i=0;
    for(i=0;i<len;i++){
        if(word[i] == 'x' || word[i] == 'y')
            continue;
        else
            return false;

    }

    if(i==len)
        return true;
}

int convertNfaToDfa(int nfa_table[][col],int states,string dfa_tab[][3]){
    bool flag[states];
    memset(flag,true,sizeof(flag)); //make sure all states E-closure found

    int state = 0,j = 0;
    map <vector<int>,string> map_state;
    vector <int> v,v1,v2,v3,v4;

    v = eclosure(nfa_table,init[0]);
    flag[init[a]] = false;

    map_state[v] = state_name(j++);
    is_initial(v,map_state[v]); //check whether current state is initial state or not
    is_final(v,map_state[v]);

    stack < vector<int> > st;
    st.push(v); //transition of e-closure to over input symbol x
    int counter = 0;
    while(true){

       while(!st.empty()){
        vector <int> v ;
        v  = st.top();
             st.pop();
        counter = counter+1;
        dfa_tab[state][0] = map_state[v];       //find transition of a state over input symbol 'x' and 'y'

        for(int i=0;i<v.size();i++){
            flag[v[i]] = false;
            int temp = nfa_table[v[i]][1];      //over input symbol x
            int temp1 = nfa_table[v[i]][2];     //over input symbol y
            if(temp>=0)
                v1.push_back(temp);
            if(temp1>=0)
                v3.push_back(temp1);
        }

        map <int,int> map_temp,map_temp1;  //remove duplicate state
        map <int,int> ::iterator it;

        for(int i=0;i<v1.size();i++){
            v2 = eclosure(nfa_table,v1[i]);
            for(int j=0;j<v2.size();j++){
                map_temp[v2[j]] = 1;
            }
            v2.clear();
        }

        for(int i=0;i<v3.size();i++){
            v4 = eclosure(nfa_table,v3[i]);
            for(int j=0;j<v4.size();j++){
                map_temp1[v4[j]] = 1;
            }
            v4.clear();
        }


        for(it = map_temp.begin(); it != map_temp.end(); it++){
            v2.push_back(it->first);
            flag[it->first] = false;
        }

        for(it = map_temp1.begin(); it != map_temp1.end(); it++){
            v4.push_back(it->first);
            flag[it->first] = false;
        }

        if(v2.empty()){
            dfa_tab[state][1] = "--";
        } else {
            string t = map_state[v2];
            char flag1 = t[0];
            if( flag1 == 'q'){
                dfa_tab[state][1] = map_state[v2];   //check v2 has already been mapped or not
            } else {
                dfa_tab[state][1] = state_name(j++);
                map_state[v2] = dfa_tab[state][1];
                is_initial(v2,map_state[v2]);
                is_final(v2,map_state[v2]);
                st.push(v2);                        //not mapped state will be pushed into stack
            }
        }

        if(v4.empty()){
            dfa_tab[state][2] = "--";
        } else {
            string t = map_state[v4];
            char flag1 = t[0];
            if( flag1 == 'q'){
                dfa_tab[state][2] = map_state[v4];
            } else {
                dfa_tab[state][2] = state_name(j++);
                map_state[v4] = dfa_tab[state][2];
                is_initial(v4,map_state[v4]);
                is_final(v4,map_state[v4]);
                st.push(v4);
            }
        }
        v1.clear();
        v2.clear();
        v3.clear();
        v4.clear();
       state = state+1;
    }

        int k = 1;
        for(k=1;k<states;k++){
            if(flag[k]){
                v = eclosure(nfa_table,k);
                map_state[v] = state_name(j++);
                is_initial(v,map_state[v]);
                is_final(v,map_state[v]);
                cout<<endl<<map_state[v]<<" represents :- ";
                for(int i=0;i<v.size();i++)
                    cout<<v[i]<<" ";
                cout<<endl;
                st.push(v);
                break;
            }
        }

        if(k == states)
                break;

    }

    print_dfa_table(dfa_tab,state);     //this function print dfa table

    return state;


}

void simulator(string dfa_tab[][3],string word,int state){
    int len = word.length();
    string temp = init_dfa[0];
    bool check = is_valid(word);     //makes sure that word need to be simulated is only consist of 'x' and 'y'

    if(!check){
        temp = "--";
    }

    int i=0;
    for(i=0;i<len;i++){
        if(temp == "--"){
            cout<<endl<<"String rejected"<<endl<<endl;
            break;
        } else {
            int _xtate;
            int j=0;

            for(j=0;j<state;j++){       //find the index over which transition need to be performed.
                if(temp == dfa_tab[j][0])
                    break;
            }

            if(word[i]=='x'){
                temp = dfa_tab[j][1];
            } else if(word[i]=='y'){
                temp = dfa_tab[j][2];
            }
        }
    }

    if(i == len){
            int j=0;
        for(j=0;j<_b;j++){
            if(temp == fin_dfa[j]){
                cout<<endl<<"String accepted"<<endl<<endl;
                break;
            }
        }
        if(j==_b){
            cout<<endl<<"String rejected"<<endl<<endl;
        }
    }

}

int main(){
    int nfa_table[500][col];
    reset(nfa_table);
    int states=0;
    cout<<"Enter a regex:  ";
    string Reg;
    cin>>Reg;

    Utils utils;
    Reg=utils.useDotForConcatenation(Reg);
    Reg=utils.postfix(Reg);


    states = regexToNfa(Reg,nfa_table);
    print_nfa_table(nfa_table,states);

    string dfa_tab[states][3];
    int dfa_state = 0;
    dfa_state = convertNfaToDfa(nfa_table,states,dfa_tab);

    while(true){

        string word;
        cout<<"Enter a string for test: ";
        cin>>word;

        if(word[0] == '1')
            break;

        simulator(dfa_tab,word,dfa_state);
    }


 return 0;
}
