#include "Helper.hpp"
#include "HCTree.hpp"
#include<iostream>
#include<vector>

int main(int argc, char*argv[]){
    HCTree hTree;
    vector<int> frequency(256, 0);
    int num = 0;
    if(argc != 3){
        error("Wrong number of arguments");
    }

    FancyInputStream input(argv[1]);
    FancyOutputStream output(argv[2]);
    unsigned char letter;

    int temp = 0;
    if(input.filesize() != 0){
        while(temp != -1){
            temp = input.read_byte();
            if(temp == -1){
                break;
            }
            frequency[temp]+=1;
        }
        for(int i = 0; i < frequency.size(); i++){
            if(frequency[i] != 0){
                num+=1;

            }
        }
        hTree.build(frequency);
        output.write_int(num);
        for(int i = 0; i < frequency.size(); i++){
            if(frequency[i] != 0){
                letter = i;
                output.write_byte(letter);
                output.write_int(frequency[i]);  
            }
        }
    }
    input.reset();

    int temp2 = 0;
    while(temp2 != -1){
        temp2 = input.read_byte();
        if(temp2 == -1){
            break;
        }
        hTree.encode(temp2, output);
    }    
    return 0;

}
