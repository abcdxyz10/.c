#include<bits/stdc++.h>
using namespace std;
int main(){
    string data;
    int frameSize;
    cout<<"Enter Packet: ";
    cin>>data;
    cout<<"Enter Frame Size: ";
    cin>>frameSize;
    string stuffed="";
    int count=0;
    for(char bit:data){
        stuffed+=bit;
        if(bit=='1')count++;else count=0;
        if(count==5){
            stuffed+='0';
            count=0;
        }
    }
    cout<<"\nAfter Bit Stuffing:\n"<<stuffed<<endl;
    string flag="01111110";
    vector<string>frames;
    string temp="";
    for(int i=0;i<stuffed.size();i++){
        temp+=stuffed[i];
        if(temp.size()==frameSize){
            frames.push_back(temp);
            temp="";
        }
    }
    if(!temp.empty())frames.push_back(temp);
    cout<<"\nFrames:\n";
    for(int i=0;i<frames.size();i++){
        cout<<"Frame "<<i+1<<":"<<flag<<frames[i]<<flag<<endl;
    }
    string destuffed="";
    count=0;
    for(auto frame:frames){
        for(int i=0;i<frame.size();i++){
            destuffed+=frame[i];
            if(frame[i]=='1')count++;else count=0;
            if(count==5&&i+1<frame.size()&&frame[i+1]=='0'){
                i++;
                count=0;
            }
        }
    }
    cout<<"\nAfter Bit Destuffing:\n"<<destuffed<<endl;
    return 0;
}
