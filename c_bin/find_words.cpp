#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

#include <emscripten/bind.h>

using namespace emscripten;

bool contained(std::string &in, std::unordered_map<wchar_t, int> cifre, std::size_t size){

    
    std::size_t current_size=in.size();
    for(int i=0;i<in.size();i++){
        //std::cout<<in[i]<<std::endl;
        if(in[i]==("ă"[0])||
           in[i]==("Ă"[0])||
           in[i]==("ă"[0])||
           in[i]==("Â"[0])||
           in[i]==("â"[0])||
           in[i]==("Î"[0])||
           in[i]==("î"[0])||
           in[i]==("Ș"[0])||
           in[i]==("ș"[0])||
           in[i]==("Ț"[0])||
           in[i]==("ț"[0])){
            current_size--;
        }
    }



    if(current_size!=size){
        return 0;
    }
    for(int i=0;i<in.size();i++){
        cifre[in[i]]--;
        if(cifre[in[i]]<0){
            return 0;
        }
    }
    return 1;
}

//EMSCRIPTEN_KEEPALIVE
void find_all(std::string search_input, std::size_t search_size, int is_english){
    //std::cout<<"fuck"<<std::endl;
    std::vector<std::string> out;
    std::size_t size;
    std::unordered_map<wchar_t, int> cifre;
    if(is_english==1){
        std::ifstream dict("english_dict.txt")
    }else if(is_english==0){
        std::ifstream dict("romanian_dict.txt");
    }else{
        std::ifstream dict("oxford_dict.txt");
    }
    std::ofstream ofile("out.txt");
    std::string in;
    in=search_input;
    size=search_size;
    
//    std::cout<<size<<'\n';


    std::transform(in.begin(),in.end(),in.begin(),
              [](wchar_t i){return ::tolower(i);});


    for(int i=0;i<in.size();i++){
        cifre[in[i]]++;
    }

    while(dict>>in){
        std::transform(in.begin(),in.end(),in.begin(),
              [](wchar_t i){return ::tolower(i);});

        
        //std::cout<<in<<std::endl;
        //if(in=="mare"){std::cout<<"FOUND MARE"<<std::endl;}
        
        if(contained(in,cifre,size)){
            std::cout<<in<<std::endl;
        }
    }
}



EMSCRIPTEN_BINDINGS(my_module) {
    function("find_all", &find_all);
}

/*int main(){
    std::ifstream ifile("input.txt");
    std::string in;
    std::size_t size;
    std::cin>>in>>size;
    find_all(in,size);
}*/