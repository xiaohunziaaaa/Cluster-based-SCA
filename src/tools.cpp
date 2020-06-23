#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
vector<string> split(const string &s, const string &seperator);


int main(){
    /*
    ifstream p1,p2,p3;
    p1.open("../result/AGT/AGT_hm_differW_part1_10000_0.500000.txt");
    p2.open("../result/AGT/AGT_hm_differW_part2_10000_0.500000.txt");
    p3.open("../result/AGT/AGT_hm_differW_part3_10000_0.500000.txt");

    ofstream writer;
    writer.open("../result/AGT/AGT_hm_differW_10000_0.500000.txt");

    string temp1,temp2,temp3;
    while(getline(p1,temp1)){
        getline(p2,temp2);
        getline(p3,temp3);
        writer<<temp1<<temp2<<temp3<<endl;
        writer.flush();
    }
    writer.close();
    */
   int range[3]={16,32,64};
   int a[3]={1324,84,96443};
   ofstream writer;
   writer.open("../data/radommodel.txt");
   for(int i=0;i<3;i++){
        for(int j=0;j<256;j++){
            int value=rand()%range[i];
            writer<<value<<",";
       }
       writer<<endl;
   }
}














vector<string> split(const string &s, const string &seperator){
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;
  
    while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
        flag = 1;
    for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
        ++i;
        flag = 0;
        break;
        }
    }
    
    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;   
    string_size j = i;
    while(j != s.size() && flag == 0){
        for(string_size x = 0; x < seperator.size(); ++x)
            if(s[j] == seperator[x]){
                flag = 1;
                break;
            }
            if(flag == 0) 
            ++j;
        }
        if(i != j){
            result.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return result;
}