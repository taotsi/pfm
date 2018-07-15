#include "pfm.hpp"
#include <iostream>

int main()
{
    std::string path = "1.pfm";
    pfm::PFM pfm_file(path);
    return 0;
}