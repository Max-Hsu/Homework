#include <iostream>
#include <vector>
using namespace std;

int main(){
    int inputa;
    while(true){
        cin>>inputa;
        if(inputa<1){
            break;
        }
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
                
                vector<int>line(run,0);
                
                vector<int>::iterator line_runner=line.begin();
                for(vector<int>::iterator it = numwq.end()-1;it>=numwq.begin();it--){
                    (*line_runner)=(*it)*i;
                    if(in!=-1){
                        (*it)+=in;
                        in=-1;
                    }
                    if((*line_runner)>=10){
                        line.insert(line.begin(),0);
                        in = (*line_runner)/10;
                        it = line.begin()+1;
                        (*it)%=10;
                    }
                    else {
                        in = -1;
                    }
                }
                adder.push_back(line);
            }
            /*cout<<i<<"!=";
            for(vector<int>::iterator itw = num.begin();itw<num.end();itw++){
            cout<<*(itw);
            }
            cout<<"\n";
            */
            for(vector<vector<int>>::iterator rinaa = adder.begin();rinaa<adder.end();rinaa++){
                for(vector<int>::iterator tais = rinaa->begin();tais<rinaa->end();tais++){
                    cout<<*tais;
                }
                cout<<"\n";
            }
        }
        cout<<"\n";

    }
}