#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int TimeTest[] = {100,500,1000,5000,10000,50000,100000,500000};
void insertSort(vector<int> &in){
    vector<int>sortOne;
    for(vector<int>::iterator run=in.begin();run!=in.end();run++){
        int pos = 0;
        for(int run_one = 0;run_one<sortOne.size();run_one++){
            if(*(run)<sortOne[pos]){
                break;
            }
            pos++;
        }
        sortOne.insert(sortOne.begin()+pos,*(run));
    }
    in = sortOne;
}
static vector<int> DEFAULT_VECTOR;
void mergeSort(vector<int> &left , vector<int> &right = DEFAULT_VECTOR){
    bool combineF = 0;
    if (right.size()==0)
    {
        combineF = 1;
        right.assign(left.begin()+int(left.size()/2),left.end());
        left.assign(left.begin(),left.begin()+int(left.size()/2));
        mergeSort(left,right);
    }
    vector<int>combineL;
    vector<int>combineR;
    if(left.size()==1){
        combineL.push_back(left[0]);
    }
    if(right.size()==1){
        combineR.push_back(right[0]);
    }
    if(left.size()>1 && right.size()>=1){
        vector<int>LSpLeft;
        vector<int>LSpRight;
        LSpLeft.assign(left.begin(),left.begin()+int(left.size()/2));
        LSpRight.assign(left.begin()+int(left.size()/2),left.end());
        mergeSort(LSpLeft,LSpRight);
        int counter_LSpL=0,counter_LspR=0;
        int Edge_LSpL=LSpLeft.size(),Edge_LSpR=LSpRight.size();
        while((Edge_LSpL>counter_LSpL)&&(Edge_LSpR>counter_LspR)){
            if(LSpLeft[counter_LSpL]<LSpRight[counter_LspR]){
                combineL.push_back(LSpLeft[counter_LSpL]);
                counter_LSpL++;
            }
            else{
                combineL.push_back(LSpRight[counter_LspR]);
                counter_LspR++;
            }
        }
        if(Edge_LSpL==counter_LSpL){
            for(;counter_LspR<Edge_LSpR;counter_LspR++){
                combineL.push_back(LSpRight[counter_LspR]);
            }
        }
        else{
            for(;counter_LSpL<Edge_LSpL;counter_LSpL++){
                combineL.push_back(LSpLeft[counter_LSpL]);
            }
        }
    }
    if(right.size()>1 && left.size()>=1){
        vector<int>RSpLeft;
        vector<int>RSpRight;
        RSpLeft.assign(right.begin(),right.begin()+int(right.size()/2));
        RSpRight.assign(right.begin()+int(right.size()/2),right.end());
        mergeSort(RSpLeft,RSpRight);
        int counter_RSpL=0,counter_RspR=0;
        int Edge_RSpL=RSpLeft.size(),Edge_RSpR=RSpRight.size();
        while((Edge_RSpL>counter_RSpL)&&(Edge_RSpR>counter_RspR)){
            if(RSpLeft[counter_RSpL]<RSpRight[counter_RspR]){
                combineR.push_back(RSpLeft[counter_RSpL]);
                counter_RSpL++;
            }
            else{
                combineR.push_back(RSpRight[counter_RspR]);
                counter_RspR++;
            }
        }
        if(Edge_RSpL==counter_RSpL){
            for(;counter_RspR<Edge_RSpR;counter_RspR++){
                combineR.push_back(RSpRight[counter_RspR]);
            }
        }
        else{
            for(;counter_RSpL<Edge_RSpL;counter_RSpL++){
                combineR.push_back(RSpLeft[counter_RSpL]);
            }
        }
    }    
    if(right.size()==1 && left.size()==1){
        return;
    }
    left = combineL;
    right = combineR;
    if(combineF){
        vector<int>combine;
        int counter_R=0,counter_L=0;
        int Edge_R=combineR.size(),Edge_L=combineL.size();
        while((Edge_R>counter_R)&&(Edge_L>counter_L)){
            if(combineL[counter_L]<combineR[counter_R]){
                combine.push_back(combineL[counter_L]);
                counter_L++;
            }
            else{
                combine.push_back(combineR[counter_R]);
                counter_R++;
            }
        }
        if(Edge_L==counter_L){
            for(;counter_R<Edge_R;counter_R++){
                combine.push_back(combineR[counter_R]);
            }
        }
        else{
            for(;counter_L<Edge_L;counter_L++){
                combine.push_back(combineL[counter_L]);
            }
        }
        left = combine;
    }
}

void quickSort(vector<int> &left){
    if(left.size()>1){
        int pivot = left[left.size()-1];
        vector<int>SL;
        vector<int>SR;
        for(vector<int>::iterator run = left.begin();run!=left.end()-1;run++){
            if(*(run)<pivot){
                SL.push_back(*(run));
            }
            else{
                SR.push_back(*(run));
            }
        }
        quickSort(SL);
        quickSort(SR);
        vector<int>combine;
        combine.insert(combine.end(),SL.begin(),SL.end());
        combine.push_back(pivot);
        combine.insert(combine.end(),SR.begin(),SR.end());
        left = combine;
    }
}
int main(){
    fstream In,oA,oB,oC,oD,oE;
    In.open("input.txt",fstream::in);
    oA.open("outputA.txt",fstream::out);
    oB.open("outputB.txt",fstream::out);
    oC.open("outputC.txt",fstream::out);
    oD.open("outputD.txt",fstream::out);
    oE.open("outputE.txt",fstream::out);
    oA<<"insertSort\n";
    oB<<"mergeSort\n";
    oC<<"quickSort\n";
    oD<<"qSort\n";
    oE<<"Sort\n";
    
    for(int i = 0; i < 1;i++){
        for(int j = 0 ; j < 10 ; j++){
            int * all;
            all = new int[TimeTest[i]];
            for(int re = 0 ; re < TimeTest[i] ; re++){
                In>>all[re];
            }
            vector<int>all_inVec;
            vector<int>forA;
            vector<int>forB;
            vector<int>forC;
            vector<int>forE;
            all_inVec.assign(all , all+(TimeTest[i]-1));
            forA.assign(all_inVec.begin(),all_inVec.end());
            forB.assign(all_inVec.begin(),all_inVec.end());
            forC.assign(all_inVec.begin(),all_inVec.end());
            forE.assign(all_inVec.begin(),all_inVec.end());

        }
    }
    
}