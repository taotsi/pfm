#include "pfm.hpp"
#include <iostream>

int main()
{
    std::string path = "1.pfm";
    pfm::PFM pfm_file(path);
    pfm_file.SaveAsPpm("1");
    std::cout << "exit!\n"; 
    return 0;
}