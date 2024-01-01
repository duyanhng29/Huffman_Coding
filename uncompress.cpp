#include "Helper.hpp"
#include "HCTree.hpp"
#include<iostream>
#include <unordered_map>

int main(int argc, char*argv[]){
    HCTree hTree;
    vector<int> header(256, 0);
    if(argc != 3){
        error("Wrong number of arguments");
    }

    FancyInputStream compressedFile(argv[1]);
    FancyOutputStream uncompressedFile(argv[2]);

    unordered_map<int, int> map;
    if(compressedFile.filesize() != 0){
        int num = compressedFile.read_int();

        for(int i = 0; i < num; i++){
            int a = compressedFile.read_byte();
            map[a] = compressedFile.read_int();
        }

        for(auto pair : map){
            header[pair.first] = pair.second;
        }

        hTree.build(header);
        hTree.decode(compressedFile, uncompressedFile);
    }
    else{
        hTree.decode(compressedFile, uncompressedFile);  
    }
    return 0;

}
