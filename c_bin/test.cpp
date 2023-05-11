#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <emscripten/bind.h>

using namespace emscripten;

bool contained(std::string &in, std::unordered_map<wchar_t, int> cifre, std::size_t size){
    std::size_t current_size=in.size();
    for(int i=0;i<in.size();i++){
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
val find_all(std::string search_input, uint32_t search_size, bool is_english){
    
    std::size_t size;
    std::unordered_map<wchar_t, int> cifre;
    std::ifstream dict;
    if(is_english){
        dict=std::ifstream ("english_dict.txt");
    }else{
        dict=std::ifstream ("romanian_dict.txt");
    }
    std::string in;
    in=search_input;
    size=search_size;

    std::transform(in.begin(),in.end(),in.begin(),
              [](wchar_t i){return ::tolower(i);});

    for(int i=0;i<in.size();i++){
        cifre[in[i]]++;
    }

    val result = val::array();

    while(dict>>in){
        std::transform(in.begin(),in.end(),in.begin(),
          [](wchar_t i){return ::tolower(i);});

        if(in=="casă"){
            std::cout<<"found"<<std::endl;
        }

        if(contained(in,cifre,size)){
            result.call<void>("push", in);
        }
    }
    return result;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("find_all", &find_all);
}
