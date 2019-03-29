#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
using namespace std;

static const double pi = 3.14159265358979323846, e=2.71828182845904523536;
static bool degree=true;
static double x=NAN, y=NAN, z=NAN, ans=NAN;

int presedance(char symbol);
string evaluate(string operand1, string oprtr, string operand2);
int factorial(int operand);
int C(int operand1, int operand2);
int P(int operand1, int operand2);
bool isunary(string infix, int index);
bool isnum(char symbol);
bool issym(string tocheck);
bool issym(char tocheck);
void check(string &infix);
double s2d(string str);
int s2i(string str);
string d2s(double d);
void prtstv(vector<string> vec);
vector<string> intovec(string infix);
double solve(vector<string> infixvector);

// trignometric rand deg
int presedance(char symbol){
    switch (symbol)
    {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case 'C':
        case 'P': return 3;
        case '^': return 4;
        case 'L':
        case 'l':
        case 'S':
        case 's':
        case 'D':
        case 'c':
        case 'T':
        case 't':
        case '!': return 5;
        case '(': return 6;
        default: return 0;
    }
}

string evaluate(string operand1, string oprtr, string operand2){
    switch (oprtr[0])
    {
        case '+': return d2s(s2d(operand1)+s2d(operand2));
        case '-': return d2s(s2d(operand1)-s2d(operand2));
        case '*': return d2s(s2d(operand1)*s2d(operand2));
        case '/':
            if(!s2d(operand2)) throw "error deviding by 0";
            return d2s(s2d(operand1)/s2d(operand2));
        case '%': return d2s(s2i(operand1)%s2i(operand2));
        case '^': return d2s(pow(s2d(operand1), s2d(operand2)));
        case 'C': return d2s(C(s2i(operand1), s2i(operand2)));
        case 'P': return d2s(P(s2i(operand1), s2i(operand2)));
        case 'L': return d2s(log(s2d(operand2))/log(s2i(operand1)));
        default:
            break;
    }
    throw "error evaluating "+operand1+oprtr+operand2;
}

int factorial(int number){
    if(!number) return 1;
    if(number<0) throw "trying to calculate factorial of negative number";
    return number*factorial(number-1);
}

int C(int n, int r){
    if(r>n) return 0;
    return P(n,r)/factorial(r);
}

int P(int n, int r){
    if(r>n) return 0;
    return factorial(n)/factorial(n-r);
}

bool isunary(string infix, int index){
    switch(infix[index]){
        case '+':
        case '-': if(!index) return true;
            if(infix[index-1]=='!') return false;
            if(issym(infix[index-1])) return true;
        default: break;
    }
    return false;
}

bool isnum(char symbol){
    if(isdigit(symbol)) return true;
    switch(symbol){
        case 'p':
        case 'e':
        case 'a':
        case 'x':        
        case 'y':
        case 'z':
        case '.': return true;
        default : return false;
    }
}

bool issym(string tocheck){
    if(tocheck.size()!=1) return 0;
    if(issym(tocheck[0])) return 1;
    return 0;
}

bool issym(char tocheck){
    if(presedance(tocheck) || tocheck==')') return true;
    return false;
}

void check(string &infix){
    if(infix.empty()) throw "nothing to solve";
    switch (infix[0])
    {

        case 'q': 
        case 'Q': throw "terminating\n";

        case 'X': if(ans!=ans) throw "nothing in history";
            x=ans;
            throw "variable updated";
        case 'Y': if(ans!=ans) throw "nothing in history";
            y=ans;
            throw "variable updated";
        case 'Z': if(ans!=ans) throw "nothing in history";
            z=ans;
            throw "variable updated";
        case 'A': degree=!degree;
            throw "Angles unit switched";
    
        default:
            break;
    }
    int brackets=0;
    // if(isunary(infix, 0)) infix.insert(infix.begin(), '0');
    for(unsigned i=0; i<infix.length(); i++){
        if(isdigit(infix[i])) continue;
        else switch(infix[i]){
            case 'p':
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    }                    
                infix.replace(i, 1, d2s(pi));
                continue;
            case 'e':
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    } 
                infix.replace(i, 1, d2s(e));
                continue;
            case 'x':
                if(x!=x) throw "Nothing in x";
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    } 
                infix.replace(i, 1, d2s(x));
                continue;
            case 'y':
                if(y!=y) throw "Nothing in y";
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    } 
                infix.replace(i, 1, d2s(y));
                continue;
            case 'z':
                if(z!=z) throw "Nothing in z";
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    } 
                infix.replace(i, 1, d2s(z));
                continue;
            case 'a':
                if(ans!=ans) throw "Nothing in history";
                if(isnum(infix[i+1])) infix.insert(infix.begin()+i+1, '*');
                if(i)
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    } 
                infix.replace(i, 1, d2s(ans));
                continue;
            case '.': continue;

            case '(':
                if(i){
                    if(isnum(infix[i-1])){
                        infix.insert(infix.begin()+i, '*');
                        continue;
                    }
                    if(isunary(infix, i-1)){
                        infix.insert(infix.begin()+i, '1');
                        continue;
                    }
                }
                brackets++; continue;
            case ')': brackets--; continue;

            default: if(issym(infix[i])) continue;
                throw "Unexpected symbols present";
        }
    }
    if(brackets) brackets>0?throw "unmatching '('":throw "unmatching ')'";
}

double s2d(string str){
    stringstream stream(str);
    double number;
    stream>>number;
    return number;
}

int s2i(string str){
    double dnum=s2d(str)+0.5;
    stringstream stream;
    stream<<dnum;
    int number;
    stream>>number;
    return number;
}

string d2s(double d){
    if(d==INFINITY) throw "the expression deals with very large numbers";
    stringstream stream;
    stream<<fixed<<d;
    string str;
    stream>>str;
    return str;
}

void prtstv(vector<string> vec){
    for(unsigned i=0; i<vec.size(); i++)
        cout<<vec[i]<<" ";
    cout<<endl;
}

vector<string> intovec(string infix){
    vector<string> infixvector;
    string tmp;
    for(unsigned i=0; i<infix.size(); i++){
        tmp.push_back(infix[i]);
        while(isnum(infix[i]) || isunary(infix, i))
            if(i+1<infix.size())
                if(isnum(infix[i+1]))tmp.push_back(infix[++i]);
                else break;
            else break;
        infixvector.push_back(tmp);
        tmp.clear();
    }
    return infixvector;
}

double solve(vector<string> infixvector){
    vector<string> stack, ans;

    for(unsigned i=0; i<infixvector.size(); i++){
        if(issym(infixvector[i])){

            if(infixvector[i]==")"){
                // if(stack.empty()) throw "Unmatching ')'";
                while(stack.back()!="("){
                    string oprtr=stack.back();
                    stack.pop_back();
                    // if(stack.empty()) throw "Unmatching ')'";
                    if(ans.empty()) throw "insufficient operands";
                    string operand2=ans.back();
                    ans.pop_back();
                    if(oprtr=="!"){
                        ans.push_back(d2s(factorial(s2i(operand2))));
                        cout<<" <"<<operand2<<oprtr<<"="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="s"){ 
                        double operand;
                        if(degree==true) operand=s2d(operand2)*pi/180;
                        else operand=s2d(operand2);
                        ans.push_back(d2s(sin(operand)));
                        cout<<" <sin("<<operand<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="S"){ 
                        double inv = asin(s2d(operand2));
                        if(inv!=inv) throw "invalid parameter for sin inv";
                        if(degree==true) inv*=180/pi;
                        ans.push_back(d2s(inv));
                        cout<<" <sin inv("<<operand2<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="c"){ 
                        double operand;
                        if(degree==true) operand=s2d(operand2)*pi/180;
                        else operand=s2d(operand2);
                        ans.push_back(d2s(cos(operand)));
                        cout<<" <cos("<<operand<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="D"){ 
                        double inv = acos(s2d(operand2));
                        if(inv!=inv) throw "invalid parameter for cos inv";
                        if(degree==true) inv*=180/pi;
                        ans.push_back(d2s(inv));
                        cout<<" <cos inv("<<operand2<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="t"){ 
                        double operand;
                        if(degree==true) operand=s2d(operand2)*pi/180;
                        else operand=s2d(operand2);
                        ans.push_back(d2s(tan(operand)));
                        cout<<" <tan("<<operand<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="T"){ 
                        double inv = atan(s2d(operand2));
                        if(inv!=inv) throw "invalid parameter for tan inv";
                        if(degree==true) inv*=180/pi;
                        ans.push_back(d2s(inv));
                        cout<<" <tan inv("<<operand2<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(oprtr=="l"){
                        ans.push_back(d2s(log(s2d(operand2))));
                        cout<<" <log("<<operand2<<")="<<ans.back()<<"> ";
                        continue;
                    }
                    if(ans.empty()) throw "insufficient operands";
                    string operand1=ans.back();
                    ans.pop_back();
                    ans.push_back(evaluate(operand1, oprtr, operand2));
                    cout<<" <"<<operand1<<oprtr<<operand2<<"="<<ans.back()<<"> ";
                }
                stack.pop_back();
            }

            else if(stack.empty() || stack.back()=="(") stack.push_back(infixvector[i]);
            else if(presedance(infixvector[i][0]) > presedance(stack.back()[0])) stack.push_back(infixvector[i]);
            else{
                while(!stack.empty() && presedance(infixvector[i][0]) <= presedance(stack.back()[0]) && stack.back()!="("){
                string oprtr=stack.back();
                stack.pop_back();
                if(ans.empty()) throw "insufficient operands";          
                string operand2=ans.back();
                ans.pop_back();
                if(oprtr=="!"){
                    ans.push_back(d2s(factorial(s2i(operand2))));
                    cout<<" <"<<operand2<<oprtr<<"="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="s"){ 
                    double operand;
                    if(degree==true) operand=s2d(operand2)*pi/180;
                    else operand=s2d(operand2);
                    ans.push_back(d2s(sin(operand)));
                    cout<<" <sin("<<operand<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="S"){ 
                    double inv = asin(s2d(operand2));
                    if(inv!=inv) throw "invalid parameter for sin inv";
                    if(degree==true) inv*=180/pi;
                    ans.push_back(d2s(inv));
                    cout<<" <sin inv("<<operand2<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="c"){ 
                    double operand;
                    if(degree==true) operand=s2d(operand2)*pi/180;
                    else operand=s2d(operand2);
                    ans.push_back(d2s(cos(operand)));
                    cout<<" <cos("<<operand<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="D"){ 
                    double inv = acos(s2d(operand2));
                    if(inv!=inv) throw "invalid parameter for cos inv";
                    if(degree==true) inv*=180/pi;
                    ans.push_back(d2s(inv));
                    cout<<" <cos inv("<<operand2<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="t"){ 
                    double operand;
                    if(degree==true) operand=s2d(operand2)*pi/180;
                    else operand=s2d(operand2);
                    ans.push_back(d2s(tan(operand)));
                    cout<<" <tan("<<operand<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="T"){ 
                    double inv = atan(s2d(operand2));
                    if(inv!=inv) throw "invalid parameter for tan inv";
                    if(degree==true) inv*=180/pi;
                    ans.push_back(d2s(inv));
                    cout<<" <tan inv("<<operand2<<")="<<ans.back()<<"> ";
                    continue;
                }
                if(oprtr=="l"){
                    ans.push_back(d2s(log(s2d(operand2))));
                    cout<<" <"<<operand2<<oprtr<<"="<<ans.back()<<"> ";
                    continue;
                }
                if(ans.empty()) throw "insufficient operands";
                string operand1=ans.back();
                ans.pop_back();
                ans.push_back(evaluate(operand1, oprtr, operand2));
                cout<<" <"<<operand1<<oprtr<<operand2<<"="<<ans.back()<<"> ";
                }
                stack.push_back(infixvector[i]);
            }
        }
        else ans.push_back(infixvector[i]);
    }


    while(!stack.empty()){
        string oprtr=stack.back();
        stack.pop_back();
        if(ans.empty()) throw "insufficient operands";                
        string operand2=ans.back();
        ans.pop_back();
        if(oprtr=="!"){
            ans.push_back(d2s(factorial(s2i(operand2))));
            cout<<" <"<<operand2<<oprtr<<"="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="s"){ 
            double operand;
            if(degree==true) operand=s2d(operand2)*pi/180;
            else operand=s2d(operand2);
            ans.push_back(d2s(sin(operand)));
            cout<<" <sin("<<operand<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="S"){ 
            double inv = asin(s2d(operand2));
            if(inv!=inv) throw "invalid parameter for sin inv";
            if(degree==true) inv*=180/pi;
            ans.push_back(d2s(inv));
            cout<<" <sin inv("<<operand2<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="c"){ 
            double operand;
            if(degree==true) operand=s2d(operand2)*pi/180;
            else operand=s2d(operand2);
            ans.push_back(d2s(cos(operand)));
            cout<<" <cos("<<operand<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="D"){ 
            double inv = acos(s2d(operand2));
            if(inv!=inv) throw "invalid parameter for cos inv";
            if(degree==true) inv*=180/pi;
            ans.push_back(d2s(inv));
            cout<<" <cos inv("<<operand2<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="t"){ 
            double operand;
            if(degree==true) operand=s2d(operand2)*pi/180;
            else operand=s2d(operand2);
            ans.push_back(d2s(tan(operand)));
            cout<<" <tan("<<operand<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="T"){ 
            double inv = atan(s2d(operand2));
            if(inv!=inv) throw "invalid parameter for tan inv";
            if(degree==true) inv*=180/pi;
            ans.push_back(d2s(inv));
            cout<<" <tan inv("<<operand2<<")="<<ans.back()<<"> ";
            continue;
        }
        if(oprtr=="l"){
            ans.push_back(d2s(log(s2d(operand2))));
            cout<<" <"<<operand2<<oprtr<<"="<<ans.back()<<"> ";
            continue;
        }
        if(ans.empty()) throw "insufficient operands";                
        string operand1=ans.back();
        ans.pop_back();
        ans.push_back(evaluate(operand1, oprtr, operand2));
        cout<<" <"<<operand1<<oprtr<<operand2<<"="<<ans.back()<<"> ";
    }
    if(ans.size()!=1) throw "there's something wrong with the expression";
    return s2d(ans.back());
}

int main(){
    string infix;
    system("cls");

    do{
        cout<<"\n-----------------------------------------------------------------------------------------------------------";
        cout<<"\nBinary operators: + - * / ^ %(reminder) P(permutation) C(combination) L(aLb = base-b log of a)";
        cout<<"\nUnary operators: + - !(factorial) s(sin) S(sin inverse) c(cos) D(cos inverse) t(tan) T(tan inverse) l(natural log)";
        cout<<"\nConstants: e P(pi)";
        cout<<"\nOther: Round brackets '(' and ')'  A(switch angle units)   X/Y/Z(save last answer in respective variable) ";

        cout<<"\n\nVariables: a(last answer) = "<<ans<<", x = "<<x<<", y = "<<y<<", z = "<<z<<", Angle unit: "<<(degree?"deg":"rad");
        cout<<"\n*you can enter 'X', 'Y' or 'Z' (in CAPITAL) to store answer under respactive variable name ('a' always holds last answer)";
        cout<<"\n-------------------------------------------input 'Q'/'q' to Quit-------------------------------------------";
        cout<<"\n\ninput>> ";
        cin>>infix;
        system("cls");
        try{
            check(infix);
            vector<string> infixvector=intovec(infix);
            cout<<"expression>> "; prtstv(infixvector);
            cout<<"solution>> ";
            ans = solve(infixvector);
            cout<<"\n\nANSWER>> "<<ans<<endl;
        }
        catch (const char* msg) {
            cerr << msg << endl;
        }
    }while(infix[0]!='q' && infix[0]!='Q');
    return 0;
}
