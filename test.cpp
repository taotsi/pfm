#include "pfm.hpp"
#include <iostream>

int main()
{
    
    std::string path = "data/1.pfm";
    pfm::PFM pfm_file(path);
    pfm_file.SaveAsPpm("1");
    
    std::vector<int> v = {{1, 2}, {3, 4}};
    std::cout << v[1][0] << std::endl;
    return 0;
}