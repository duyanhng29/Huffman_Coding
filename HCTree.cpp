#include <queue>
#include <vector>
#include <fstream>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <queue>
#include <stack>
#include <cmath>
#include <iostream>
using namespace std;

void clear(HCNode* node){
    if(node != nullptr){
        clear(node->c0);
        clear(node->c1);
    }
    delete(node);
}

HCTree::~HCTree(){
    clear(this->root);
}
void HCTree::build(const vector<int> & freq){
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    for(int i = 0; i < freq.size(); i++){
        if(freq[i] != 0){
                    HCNode* node = new HCNode(freq[i], i);
                    pq.push(node);
                    this->leaves[i] = node;
        }       
    }
    int n = pq.size();
    while(pq.size() > 1){

        HCNode* a = pq.top();
        pq.pop();
        int aCount = a->count;
        HCNode* b = pq.top();
        pq.pop();
        int bCount = b->count;
        HCNode* next = new HCNode(aCount+bCount, a->symbol);
        next->c0 = a;
        next->c1 = b;

        a->p = next;
        b->p = next;
        pq.push(next);

        if(pq.size() == 1){
            this->root = next;
        }
    }
}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    stack<int> st;
    HCNode* temp = this->leaves[symbol];
    while(temp != this->root){
        if(temp->p->c0 == temp){
            st.push(0);
            temp = temp->p;
        }
        else{
            st.push(1);
            temp = temp->p;
        }
    }
    while(st.size() > 0){
        out.write_bit(st.top());
        st.pop();
    }
}


void HCTree::decode(FancyInputStream & in, FancyOutputStream & out) const{
    int a = 0;
    HCNode* node = this->root;
    unsigned char result;
    while(a != -1){
        int a = in.read_bit();
            if(a == -1){
                break;
            }
            if(a == 0){
                node = node->c0;

            }
            else if(a == 1){
                node = node->c1;
            }
            if(node->c0 == nullptr && node->c1 == nullptr){
                result = node->symbol;
                out.write_byte(result);
                node = this->root;

            }
    }
    
}
