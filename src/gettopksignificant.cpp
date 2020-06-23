#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define W_NUMBER 432
#define WPOOL_SIZE 256
#define MAX_K 10

using namespace std;

void restoreWandDiv(string filepath,int** w_pool,float** div_pool);
vector<string> split(const string &s, const string &seperator);
bool iscontain(int* topkw,int K,int golden_w);
float TOPK(int** w_pools,int K,int* golden_w);
int guessnumber(int* w_pool,int golden_w);

int main(int argc, char *argv[]){
    int glodenw[W_NUMBER]={0};
    string glodenwpath="../data/weights_q.txt";
    string glodenw_str;
    ifstream glodenwreader;
    glodenwreader.open(glodenwpath);
    int w_counter=0;
    while(getline(glodenwreader,glodenw_str)){
        glodenw[w_counter++]=atoi(glodenw_str.c_str());
        //cout<<glodenw[w_counter-1]<<endl;
    }

    string restore_path=argv[1];
    vector<string> str_vec=split(restore_path,"/");
    int** w_pools=new int*[W_NUMBER];
    for(int i=0;i<W_NUMBER;i++){
        w_pools[i]=new int[WPOOL_SIZE];
    }

    float** div_pools=new float*[W_NUMBER];
    for(int i=0;i<W_NUMBER;i++){
        div_pools[i]=new float[WPOOL_SIZE];
    }
    for(int i=0;i<W_NUMBER;i++){
        for(int j=0;j<WPOOL_SIZE;j++){
            w_pools[i][j]=0;
            div_pools[i][j]=0;
        }
    }

    restoreWandDiv(restore_path,w_pools,div_pools);
    //ofstream div_writer;
    //div_writer.open("./result/div_random.txt");
    //for(int i=0;i<W_NUMBER;i++){
    ///    for(int j=0;j<WPOOL_SIZE;j++){
    //        cout<<div_pools[i][j]<<" ";
    //    }
    //    cout<<endl;
    //}
    //div_writer.close();
    ofstream TOPK_writer;
    TOPK_writer.open("../result/TOPK/TOPK_accuracy_"+str_vec[str_vec.size()-1]);
    float TOPK_result[MAX_K]={0};
    for(int i=0;i<MAX_K;i++){
        printf("Now processing TOP%d\r",i+1);
        TOPK_result[i]=TOPK(w_pools,i+1,glodenw);
        TOPK_writer<<TOPK_result[i]<<" ";
    }
    TOPK_writer.close();

    for(int i=0;i<W_NUMBER;i++){
        delete w_pools[i];
        delete div_pools[i];
    }
    delete[] w_pools;
    delete[] div_pools;
}

void restoreWandDiv(string path,int** w_pools,float** div_pools){
    string guessw_str;
    ifstream reader;
    reader.open(path);
    int w_counter;
    while(getline(reader,guessw_str)){
        vector<string> wanddiv=split(guessw_str," ");
        //cout<<(int)wanddiv.size()/2<<endl;
        for(int j=0;j<(int)wanddiv.size()/2;j++){
            w_pools[w_counter][j]=atoi(wanddiv[2*j].c_str());
            //cout<< w_pool[w_counter][j]<<endl;
            div_pools[w_counter][j]=atof(wanddiv[2*j+1].c_str());
        }
        w_counter++;
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

float TOPK(int** w_pools,int K,int* golden_w){
    int right_counter=0;
    int no_significat=0;
    for(int i=0;i<W_NUMBER;i++){
        if((golden_w[i]<=42)&&(golden_w[i]>=-42)){
            no_significat++;
            continue;
        }
        if(iscontain(w_pools[i],K,golden_w[i])){
            right_counter++;
            //cout<<right_counter;
            //cout<<right_counter<<endl;
            continue;
        }
    }
    return right_counter/(W_NUMBER+0.0-no_significat);
}

bool iscontain(int* topkw,int K,int golden_w){
    for(int i=0;i<K;i++){
        if(topkw[i]==golden_w){
            return true;
        }
    }
    return false;
}

int guessnumber(int* w_pool,int golden_w){
    int guessnumber=0;
    for(int i=0;i<WPOOL_SIZE;i++){
        guessnumber++;
        if(w_pool[i]==golden_w){
            break;
        }
    }
    return guessnumber;
}
