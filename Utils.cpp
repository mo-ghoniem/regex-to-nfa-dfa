#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include "utils.h"

using namespace std;


/*
 useDotForConcatenation function simplifies the expression, as we have no symbol for concatenation
 operation, so useDotForConcatenation function provide one.
*/

string Utils::useDotForConcatenation(string regex)
{
    vector<char>v;
    for(int i = 0; i < regex.size() - 1; i++)
    {
        char cur = regex[i];
        if(cur != '|' && cur != '(')   // Don't add '.' after '|' and '('
        {
            char next = regex[i + 1];
            if(next != '|' && next != '*' && next != ')')   // Don't add '.' if '|', '*', ')' are the next characters
            {
                regex = regex.insert(i + 1, ".");
                i++;
            }
        }
    }
    v.push_back('(');
    for(int i =0; i<regex.size(); i++)
    {
        v.push_back(regex[i]);
    }
    v.push_back(')');
    string regex2 = "";
    stringstream ss;

    for(int i =0; i<v.size(); i++)
    {
        ss << regex2 << v[i];
    }
    ss>>regex2;
    return regex2;
}



/*
    converts given regular expression into it's corresponding
    postfix notation
*/
string Utils::postfix(string s)
{
    char a[200]; //store the new expression after postfix
    stack <char> ch;
    int j=0; //legnth of a
    for(int i=0; i<s.length(); i++)
    {
        char x = s[i];
        if(x=='x')
        {

            a[j]='x';
            j =j+1;
        }
        else if(x== 'y')
        {

            a[j]='y';
            j=j+1;
        }
        else if (x== '(')
        {
            ch.push('(');
        }
        else if(x== ')')
        {
            while(!ch.empty())
            {
                if(ch.top()=='(')
                {
                    ch.pop();
                    break;
                }
                else
                {
                    a[j]=ch.top();
                    ch.pop();
                    j=j+1;
                }
            }
        }
        else if(x== '.')
        {
            if(ch.empty())
            {
                ch.push('.');
            }
            else
            {
                char temp = ch.top();
                if(temp=='(')
                    ch.push('.');
                else if(temp=='*')
                {
                    a[j]=ch.top();
                    ch.pop();
                    j = j+1;
                    if(ch.top()== '.')
                    {
                        a[j] = '.';
                        j = j+1;
                    }
                    else
                    {
                        ch.push('.');
                    }
                }
                else if(temp=='.')
                {
                    a[j]=ch.top();
                    ch.pop();
                    j = j+1;
                    ch.push('.');
                }
                else if(temp == '|')
                {
                    ch.push('.');
                }
            }
        }
        else if (x=='|')
        {
            if(ch.empty())
            {
                ch.push('|');
            }
            else
            {
                char temp = ch.top();
                if(temp == '(')
                    ch.push('|');
                else if(temp == '*')
                {
                    a[j] = ch.top();
                    ch.pop();
                    j = j+1;
                    ch.push('|');
                }
                else if(temp == '.')
                {
                    a[j] = ch.top();
                    j = j+1;
                    ch.pop();
                    ch.push('|');
                }
            }
        }
        else if(x== '*')
        {
            if(ch.empty())
            {
                ch.push('*');
            }
            else
            {
                char temp = ch.top();
                if(temp == '(' || temp == '.' || temp == '|' )
                    ch.push('*');
                else
                {
                    a[j] = ch.top();
                    ch.pop();
                    j = j+1;
                    ch.push('*');
                }
            }
        }
    }

    return a;
}
