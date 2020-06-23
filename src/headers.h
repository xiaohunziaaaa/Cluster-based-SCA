#include <iostream>
#include <time.h>
#include <cmath>
#include <string.h>
#include <vector>
#include <fstream>
#include <random>

//fixed parameters
#define I_MAX 1.0
#define I_MIN 0.0
#define W_MAX 0.27600992
#define W_MIN -0.24774256
#define W_NUMBER 432
#define O_MAX 1.1292133
#define O_MIN -1.9577422
#define Q_MAX 127
#define Q_MIN -128
#define UQ_MAX 256

using namespace std;

float randomleakage[256]={1,3,6,4,1,4,6,6,2,0,1,1,1,3,1,3,3,6,3,4,7,4,6,1,4,6,5,4,6,7,7,6,
                        3,2,5,0,3,3,3,6,7,3,2,5,1,0,5,7,5,4,3,4,6,5,5,3,3,5,1,2,4,3,6,2,
                        0,2,0,6,0,0,6,5,2,1,2,6,6,5,1,4,5,7,4,2,4,0,6,0,3,4,0,7,2,3,1,2,
                        6,2,1,5,1,3,7,2,0,2,1,2,1,2,5,1,4,0,6,5,1,5,1,0,2,2,1,4,3,7,7,6,
                        7,4,6,6,5,4,6,6,3,7,7,1,1,7,1,7,1,5,1,6,5,4,6,2,2,6,5,0,4,7,2,7,
                        2,7,0,1,4,3,3,1,2,6,3,4,6,4,4,5,4,7,4,4,1,6,5,7,2,2,4,4,7,3,0,5,
                        0,3,7,5,6,1,5,2,5,0,7,3,0,1,7,4,6,7,0,0,4,1,5,6,3,5,5,7,3,3,2,7,
                        0,0,2,2,4,4,6,1,5,6,1,5,0,6,2,4,6,3,6,1,6,7,7,0,4,7,2,2,0,7,0,6};
float rleakage2[256]={9,3,14,4,1,12,6,14,2,0,9,1,1,11,9,11,3,6,11,12,7,12,14,9,4,14,13,12,6,7,7,14,3,2,13,8,3,11,11,6,15,3,10,13,9,8,5,15,13,4,11,12,6,5,5,11,3,13,9,10,12,11,14,2,0,10,0,14,0,8,6,13,2,9,2,6,14,13,9,12,13,15,4,2,4,0,6,0,11,4,0,7,2,11,1,2,6,2,1,13,1,11,15,10,0,10,9,2,9,2,13,9,12,0,14,5,9,5,9,0,2,10,9,12,3,15,7,6,15,4,6,14,13,12,14,6,3,15,7,9,1,15,9,15,1,13,1,14,13,12,6,2,2,6,13,0,4,15,10,7,2,7,8,9,12,3,11,9,2,14,3,4,14,12,4,5,4,15,4,4,9,14,5,15,2,2,4,12,15,3,0,13,8,3,15,5,6,9,13,10,5,0,7,11,8,1,7,4,14,15,0,0,4,1,13,14,11,5,5,7,11,3,2,15,8,0,2,10,4,4,14,1,5,14,9,5,8,6,10,4,6,3,14,9,6,15,7,8,4,7,10,10,0,7,8,6};
float rleakage3[256]={26,22,27,17,13,14,4,8,25,30,18,27,5,3,5,28,20,5,19,24,8,14,11,21,5,0,25,29,23,7,10,25,22,13,16,2,9,13,8,20,9,10,25,5,8,1,0,20,17,27,10,5,17,8,1,12,22,9,11,7,23,12,15,17,21,29,26,21,1,27,1,0,30,9,8,26,7,6,2,21,20,31,26,7,25,3,17,21,16,24,8,17,25,12,1,6,30,14,1,16,28,30,25,17,31,2,5,2,12,27,20,7,5,24,10,6,9,9,2,25,26,22,24,2,3,17,6,31,26,9,13,30,2,0,22,18,20,31,25,6,31,9,30,17,13,14,3,12,8,1,30,0,29,11,2,3,31,1,7,4,15,20,5,5,27,8,1,9,5,7,12,14,6,22,8,28,19,8,13,30,30,18,11,17,31,0,16,27,21,6,12,30,7,24,19,13,16,30,2,30,27,2,6,1,11,12,26,16,31,16,16,7,20,6,18,21,10,27,8,19,11,6,28,21,10,30,29,31,9,10,1,27,29,24,15,8,22,18,27,20,25,13,19,13,16,4,26,20,6,6,19,19,11,11,1,16};
float rleakage4[256]={30,12,44,3,12,51,38,5,52,49,14,42,45,15,21,48,10,39,63,24,29,20,13,52,57,39,25,2,60,28,1,56,13,12,7,32,35,36,56,38,7,21,12,48,26,13,14,45,25,39,61,49,32,30,49,0,45,8,1,41,39,1,37,21,31,36,24,31,21,2,0,38,62,12,17,33,4,19,47,51,15,51,19,0,3,10,47,62,10,47,21,15,19,33,21,14,26,62,37,39,42,54,7,45,33,62,37,38,52,9,0,41,50,52,9,44,13,1,15,23,22,6,27,29,8,38,24,11,8,1,56,33,43,40,18,34,57,20,16,39,49,23,8,56,13,18,41,29,6,41,25,50,27,52,28,58,15,55,56,53,48,21,23,53,31,0,44,45,13,52,25,11,3,37,17,8,37,54,57,61,55,43,21,56,32,33,32,15,46,60,59,52,27,34,10,10,15,39,28,55,37,7,10,59,50,27,33,0,4,6,3,49,39,48,10,16,46,53,47,3,47,30,42,47,16,16,27,8,1,3,41,40,10,54,41,30,7,33,1,8,49,44,13,36,30,30,1,35,12,24,16,63,26,3,13,15};

float hmming(int act,float noise){
    
    int abs_act=abs(act);
    float hm=0;
    while(abs_act)
    {
        hm++;
        abs_act &=abs_act-1;
    }

    if(act<0){
        hm++;
    }
    unsigned seed = rand();
    std::default_random_engine gen(seed);
    normal_distribution<float> dis(hm,noise);
    return  dis(gen);
}

float randomleak(int act,float noise){
    
    float leak=0;
    leak=randomleakage[act+128];
    unsigned seed = rand();
    std::default_random_engine gen(seed);
    normal_distribution<float> dis(leak,noise);
    return  dis(gen);
    //return leak;
    
}

void geninput(int* q_input,int num){
    srand(time(NULL));
    for(int i=0;i<num;i++){
        q_input[i]=rand()%(Q_MAX-Q_MIN+1)-128;
    }
}

void genactivation(int* q_act,int* q_input,int num,int q_w,float M){
    for(int i=0;i<num;i++){
        q_act[i]=round(M*q_input[i]*q_w);
        q_act[i]=q_act[i]>Q_MAX?Q_MAX:q_act[i];
        q_act[i]=q_act[i]<Q_MIN?Q_MIN:q_act[i];
    }
}

void initmatrix(float** matrix,int row,int col){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=0;
        }
    }
}

void deletematrix(float** matrix,int row,int col){
    for(int i=0;i<row;i++){
        delete matrix[i];
    }
    delete[] matrix;
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

float var(float* array,int len){
    float avarage=0;
    for(int i=0;i<len;i++){
        avarage+=array[i];
    }
    avarage/=len;

    float var=0;
    for(int i=0;i<len;i++){
        var+=(array[i]-avarage)*(array[i]-avarage);
    }
    var/=len;
    return sqrt(var);
}
float clusterandeval(float** matrix,int row,int col,int* guess_act,float* g_hm,int len){
    //clustering
    //for(int i=0;i<256;i++){
    //    cout<<matrix[guess_act[i]+Q_MAX+1][col]<<endl;
    //}
    for(int i=0;i<len;i++){
        //cout<<guess_act[i]+Q_MAX+1<<" "<<col<<endl;
        matrix[guess_act[i]+Q_MAX+1][(int)matrix[guess_act[i]+Q_MAX+1][col-1]]=g_hm[i];
        matrix[guess_act[i]+Q_MAX+1][col-1]++;
    }

    

    //evaluation
    int clusters=0;
    float culvar=0;
     for(int i=0;i<row;i++){
        if(matrix[i][col-1]!=0){
            clusters++;
        }
    }
    float critial=len/clusters;
    //critial=critial<100?critial:100;
    int used_clusters=0;
    for(int i=0;i<row;i++){
        if(matrix[i][col-1]>=critial){
            float variance=var(matrix[i],matrix[i][col-1]);
            //cout<<variance<<" "; 
            culvar+=variance;
            used_clusters++;
        }
    }

    //cout<<clusters<<" ";
    return culvar/used_clusters;
}