#include "headers.h"
#include <algorithm>

bool compare(pair<float,int> a,pair<float,int> b);
vector<pair<float,int>> getW(int* q_input,float* hm,int num,float M);

int main(int argc, char *argv[]){


    //set your parameters
    //曲线条数
    int INPUT_NUM=10000;
    //功耗模型噪声
    float noise=0.5;
    int partnumber=atoi(argv[1]);



    //code blew should not be modified.
    float S1=(I_MAX-I_MIN)/UQ_MAX;
    float S2=(W_MAX-W_MIN)/UQ_MAX;
    float S3=(O_MAX-O_MIN)/UQ_MAX;
    float M=S1*S2/S3;
    //generate random input
    int* input_vec=new int[INPUT_NUM];
    geninput(input_vec,INPUT_NUM);
    string suffix="_differW_part"+to_string(partnumber)+"_"+to_string(INPUT_NUM)+"_"+to_string(noise)+".txt";
    //write input back to txt file
    //每行一个值
    ofstream input_writer;
    input_writer.open("../data/input/input_"+suffix);
    for(int i=0;i<INPUT_NUM;i++){
        input_writer<<input_vec[i]<<endl;
    }
    input_writer.flush();input_writer.close();
    
    //read INT8 weights and generate true output
    int* weight_vec=new int[2560*3];
    for(int i=0;i<2560*3;i++){
        weight_vec[i]=((int) (i/30)-128);
    }
    //每行对应于一个权重值的真实激活值序列，INPUT_NUM个
    ofstream act_writer,hm_writer,random_writer,hm_guess_writer,random_guess_writer;
    act_writer.open("../data/act/act"+suffix);
    hm_writer.open("../data/power/hm"+suffix);
    random_writer.open("../data/power/random"+suffix);
    hm_guess_writer.open("../result/hm"+suffix);
    random_guess_writer.open("../result/random"+suffix);
    for(int i=0;i<2560*3;i++){
        printf("Total weights are %d,now guessing weight No.%d\r",2560*3,i+1);
        int* act_vec=new int[INPUT_NUM];
        float* power_hm_vec=new float[INPUT_NUM];
        float* power_random_vec=new float[INPUT_NUM];
        genactivation(act_vec,input_vec,INPUT_NUM,weight_vec[i],M);
        //生成实际功耗值
        for(int j=0;j<INPUT_NUM;j++){
            act_writer<<act_vec[j]<<" ";
            power_hm_vec[j]=hmming(act_vec[j],0.5);
            power_random_vec[j]=randomleak(act_vec[j],0.5);
            hm_writer<<power_hm_vec[j]<<" ";
            random_writer<<power_random_vec[j]<<" ";
        }
        act_writer<<endl;act_writer.flush();
        hm_writer<<endl;hm_writer.flush();
        random_writer<<endl;random_writer.flush();

        //猜测
        vector<pair<float,int>> hm_guess_vec=getW(input_vec,power_hm_vec,INPUT_NUM,M);
        vector<pair<float,int>> random_guess_vec=getW(input_vec,power_random_vec,INPUT_NUM,M);

        //结果写回
        for(int k=0;k<hm_guess_vec.size();k++){
            hm_guess_writer<<hm_guess_vec[k].second<<" "<<hm_guess_vec[k].first<<" ";
            random_guess_writer<<random_guess_vec[k].second<<" "<<random_guess_vec[k].first<<" ";
        }
        hm_guess_writer<<endl;random_guess_writer<<endl;
        hm_guess_writer.flush();random_guess_writer.flush();
        delete act_vec;delete power_hm_vec;delete power_random_vec;
    }

    //关闭结果文件,中间值文件，功耗文件
    act_writer.close();hm_writer.close();random_writer.close();hm_guess_writer.close();random_guess_writer.close();

}


vector<pair<float,int>> getW(int* q_input,float* hm,int num,float M){
    float** SETS=new float*[UQ_MAX];
    for(int i=0;i<UQ_MAX;i++){
        SETS[i]=new float[num+1];
    }
    initmatrix(SETS,UQ_MAX,num+1);
    vector<pair<float,int>> indexdiv;
    for(int i=0;i<256;i++){
        int guess_w=i-128;
        int* guess_act=new int[num];
        memset(guess_act,0,num*sizeof(int));
        genactivation(guess_act,q_input,num,guess_w,M);
        pair<float,int> div;
        div.first=clusterandeval(SETS,UQ_MAX,num+1,guess_act,hm,num);
        //cout<<div.first<<endl;
        div.second=guess_w;
        indexdiv.push_back(div);
        delete guess_act;
        initmatrix(SETS,UQ_MAX,num+1);
    }
    deletematrix(SETS,UQ_MAX,num+1);
    sort(indexdiv.begin(),indexdiv.end(),compare);
    return indexdiv;
}

bool compare(pair<float,int> a,pair<float,int> b)
{
  return a.first<b.first; 
}
