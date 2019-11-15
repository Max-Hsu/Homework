#include <iostream>
#include <vector>

using namespace std;
struct tree{
    int value;
    tree * left;
    tree * right;
};
void delete_tree(tree * deleting , tree * upper , bool direction , tree * &top){
    if(deleting->left == nullptr && deleting->right == nullptr){
        if(deleting == top){
            top == nullptr;
        }
        if(!direction){
            upper->left = nullptr;
        }
        else{
            upper->right = nullptr;
        }
        delete deleting;
    }
    else if(deleting->left == nullptr ^ deleting->right == nullptr){
        if(deleting == top){
            if(deleting->left != nullptr){
                top = deleting->left;
            }
            else{
                top = deleting->right;
            }
        }
        if(deleting->left != nullptr){
            if(!direction){
                upper->left = deleting->left;
            }
            else{
                upper->right = deleting->left;
            }
        }
        else{
            if(!direction){
                upper->left = deleting->right;
            }
            else{
                upper->right = deleting->right;
            }
        }
        delete deleting;
    }
    else{
        tree * travel_to_left = deleting->right;
        tree * before_travel_to_left = deleting;
        bool 
        while(1){
            if(travel_to_left->left == nullptr){
                break;
            }
            before_travel_to_left = travel_to_left;
            travel_to_left = travel_to_left->left;
        }
        deleting->value = travel_to_left->value;
        delete_tree(travel_to_left,before_travel_to_left,0,top);
    }
    
}
void adding(tree * &top , int add_value){
    tree * before;
    tree * adding;
    tree * running = top;
    bool direction; //0 for left , 1 for right
    if(top == nullptr){
        adding = new tree;
        adding->left = nullptr;
        adding->right = nullptr;
        adding->value = add_value;
        top = adding;
        return ;
    }
    while(running != nullptr){
        before = running;
        if(running->value > add_value){
            running = running->left;
            direction = 0;
        }
        else if(running->value < add_value){
            running = running->right;
            direction = 1;
        }
        if(running != nullptr && running->value == add_value){
            if(top->left == nullptr && top->right == nullptr && running == top){
                cout<<"no";
                top = nullptr;
            }
            delete_tree(running , before , direction , top);

            return ; 
        }
    }
    adding = new tree;
    adding->left = nullptr;
    adding->right = nullptr;
    adding->value = add_value;
    if(!direction){
        before->left = adding;
    }
    else{
        before->right = adding;
    }

}
void travel(tree * top , vector<int> & out_vec1 , vector<int> & out_vec2 , vector<int> & out_vec3){
    if(top == nullptr){
        cout<<"EMPTY\n";
        return ; 
    }
    if(top->left!=nullptr){
        travel(top->left , out_vec1 , out_vec2 , out_vec3);
        out_vec2.push_back(top->left->value);
    }
    else{
        out_vec2.push_back(0);
    }
    out_vec1.push_back(top->value);
    if(top->right!=nullptr){
        out_vec3.push_back(top->right->value);
        travel(top->right , out_vec1 , out_vec2 , out_vec3);
    }
    else{
        out_vec3.push_back(0);
    }
}
int main(){
    int num;
    tree * root = nullptr;
    vector<int> every0;
    vector<int> every1;
    vector<int> every2;
    while(cin>>num){
        if(num == -1){
            break;
        }
        adding(root,num);
        travel(root,every0 , every1 ,every2);
        for(vector<int>::iterator e0 = every0.begin();e0!=every0.end();e0++){
            cout<<*e0<<" ";
        }
        cout<<"\n";
        for(vector<int>::iterator e1 = every1.begin();e1!=every1.end();e1++){
            cout<<*e1<<" ";
        }
        cout<<"\n";
        for(vector<int>::iterator e2 = every2.begin();e2!=every2.end();e2++){
            cout<<*e2<<" ";
        }
        cout<<"\n";
    }


}