#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cout<<"Enter String:"<<endl;
    cin>>s;

    string stuffed="";
    for(int i=0;i<(int)s.size();){
        if(i+4<=(int)s.size()&&s.substr(i,4)=="flag"){
            stuffed+="escflag";
            i+=4;
        }
        else if(i+3<=(int)s.size()&&s.substr(i,3)=="esc"){
            stuffed+="escesc";
            i+=3;
        }
        else{
            stuffed+=s[i];
            i++;
        }
    }

    cout<<"\nStuffed String:\nflag"<<stuffed<<"flag\n";

    string destuffed="";
    for(int i=0;i<(int)stuffed.size();){
        if(i+3<=(int)stuffed.size()&&stuffed.substr(i,3)=="esc"){
            if(i+7<=(int)stuffed.size()&&stuffed.substr(i+3,4)=="flag"){
                destuffed+="flag";
                i+=7;
            }
            else if(i+6<=(int)stuffed.size()&&stuffed.substr(i+3,3)=="esc"){
                destuffed+="esc";
                i+=6;
            }
            else{
                destuffed+=stuffed[i];
                i++;
            }
        }
        else{
            destuffed+=stuffed[i];
            i++;
        }
    }

    cout<<"\nDe-stuffed String:\n"<<destuffed<<endl;

    return 0;
}
