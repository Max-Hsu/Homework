#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
int calc_percision(int ii,int per){
    char ii_char[20];
    sprintf(ii_char,"%20d",ii);
    return int(ii_char[19-per])-48;
}
int main(){
    int inputa;
    while(true){
        cin>>inputa;
        if(inputa<1){
            break;
        }
        cout<<"1!=1\n";
        vector <int> numwq(1,1);
        int in = -1;
        for(int i=2 ; i<=inputa ; i++){
            int log_of_i=-1;

            for(int run = 1 ; run<=10000 ; run*=10){
                if(i/run>=1){
                    log_of_i++;
                }
                else{
                    break;
                }
            }

            vector<vector<int>> adder;
            for(int run = 0 ; run<=log_of_i ; run++){
                int multiply= calc_percision(i,run);
                vector<int>line(run,0);

                vector<int>::iterator line_runner=line.begin();
                for(vector<int>::iterator it = numwq.end()-1;it>=numwq.begin();it--){
                    line.insert(line_runner,(*it)*multiply);
                    line_runner = line.begin();
                    if(in!=-1){
                        (*line_runner)+=in;
                        //cout<<(*line_runner)<<"line_runner\n";
                        in=-1;
                    }
                    if((*line_runner)>=10){
                        in = (*line_runner)/10;
                        //cout<<i<<" "<<in<<"\n";
                        (*line_runner)%=10;
                    }
                    else {
                        in = -1;
                    }
                }
                if(in!=-1){
                    line.insert(line.begin(),in);
                    in=-1;
                }
                adder.push_back(line);
            }
            vector<int> adding;
            vector<int>::iterator adding_run=adding.begin();
            int runner=0;
            int in2=0;
            for(runner = 0; runner <(*(adder.end()-1)).size();runner++){
                for(vector<vector<int>>::iterator rinaa = adder.begin();rinaa<adder.end();rinaa++){
                    vector<int>::iterator rinaa_run=(*rinaa).end()-1-runner;
                    if(rinaa_run>=(*rinaa).begin()&&rinaa_run<(*rinaa).end()){
                        if(adding.size()==runner){
                                adding.insert(adding.begin(),0);
                        }
                        adding_run=adding.begin();
                        (*adding_run)+=(*rinaa_run);
                        //cout<<runner<<" at "<<*adding_run<<"\n";
                    }
                    //cout<<"\n";
                }
            }
            for(adding_run=adding.end()-1;adding_run>=adding.begin();adding_run--){
                if(in2>0){
                    //cout<<"new in2 for "<<in2 <<"\n";
                    (*adding_run)+=in2%10;
                    in2/=10;
                }
                if(*adding_run>=10){
                    //cout<<*adding_run<<" as now \n";
                    in2 += (*adding_run)/10;
                    (*adding_run)%=10;
                }
                if(in2>0&&adding_run == adding.begin()){
                    adding.insert(adding.begin(),in2%10);
                    in2/=10;
                    adding_run = adding.begin();
                }
            }
            numwq = adding;
            cout<<i<<"!=";
            for(vector<int>::iterator run_adding = adding.begin();run_adding<adding.end();run_adding++){
                cout<<*run_adding;
            }
            cout<<"\n";
        }
        cout<<"\n";

    }
}
