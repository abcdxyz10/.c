#include<bits/stdc++.h>
using namespace std;

string xorStrings(string a,string b){
    string res="";
    for(int i=1;i<b.size();i++){
        res+=(a[i]==b[i])?'0':'1';
    }
    return res;
}

string mod2div(string dividend,string divisor){
    int pick=divisor.size();
    string temp=dividend.substr(0,pick);
    while(pick<dividend.size()){
        if(temp[0]=='1')
            temp=xorStrings(divisor,temp)+dividend[pick];
        else
            temp=temp.substr(1)+dividend[pick];
        pick++;
    }
    if(temp[0]=='1')
        temp=xorStrings(divisor,temp);
    else
        temp=temp.substr(1);
    return temp;
}

string encodeData(string data,string key){
    int keySize=key.size();
    string appendedData=data+string(keySize-1,'0');
    string remainder=mod2div(appendedData,key);
    return data+remainder;
}

int main(){
    string data,key;
    cout<<"Enter the dataword (binary): ";
    cin>>data;
    cout<<"Enter the divisor (binary): ";
    cin>>key;

    string codeword=encodeData(data,key);
    cout<<"\nGenerated Codeword: "<<codeword<<endl;

    string recvCodeword;
    cout<<"\nEnter the received codeword (binary): ";
    cin>>recvCodeword;

    string remainder=mod2div(recvCodeword,key);

    bool error=false;
    for(char c:remainder){
        if(c=='1'){
            error=true;
            break;
        }
    }

    if(error)
        cout<<"\nError detected in received codeword!"<<endl;
    else
        cout<<"\nNo error in received codeword!"<<endl;

    return 0;
}
