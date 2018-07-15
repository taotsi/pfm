#ifndef PFM_HPP_
#define PFM_HPP_

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include "nlohmann/json.hpp"

namespace pfm {

using json = nlohmann::json;

class PFM{
    template <typename T>
    using Grid2D = std::vector< std::vector<T> >;
    template <typename T>
    using Grid3D = std::vector< std::vector< std::vector<T> > >;
    
private:
    Grid2D<float> Image_;
    int height_ = 0;
    int width_ = 0;
    float endianness_ = -1.0;
    
public:
    
    PFM() {
        
    }
    PFM(std::string path) {
        Image_ = *ReadPfmFile(path);
    }
    PFM(float* data) {
        
    }
    
    ~PFM() {
        
    }
    
    Grid2D<float>* GetImage() {
        return &Image_;
    }
    
    bool isLittleEndian()
    {
        int intval = 1;
        unsigned char *uval = reinterpret_cast<unsigned char *>(&intval);
        return uval[0] == 1;
    }
    
    Grid2D<float>* ReadPfmFile(std::string path) {
        std::fstream file(path, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            // get information
            std::string line;
            getline(file, line);
            if (!(line == "Pf" | line == "PF")) {
                std::cout << "NOT pfm format!!!" <<std::endl;
                file.close();
            } else {
                getline(file, line);
                std::istringstream iss_wd(line);
                iss_wd >> width_ >> height_;
                getline(file, line);
                std::istringstream iss_e(line);
                iss_e >> endianness_;
                
                // get data buffer
                file.seekg(0, file.end);
                int length = file.tellg();
                int pos = length - width_ * height_ * sizeof(float);
                file.seekg(pos);
                std::vector<char> buffer((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
                file.close();
                
                //get chars back into float
                union {
                    float f;
                    char u8[sizeof(float)];
                } pixel;
                std::vector<float> temp;
                std::cout << height_ << " " << width_;
                if (endianness_ == -1.0f) {
                    for (int h = 0; h < height_; h++) {
                        Image_.push_back(temp);
                        for (int w = 0; w < width_; w++) {
                            for (int s = 0; s < sizeof(float); s++) {
                                pixel.u8[s] = buffer[(h * width_ + w) * sizeof(float) + s];
                            }
                            Image_[h].push_back(pixel.f);
                            // BUG: up side down!!!
                            std::cout << pixel.f << std::endl;
                        }
                    }
                    
                } else {
                    std::cout << "TODO: NOT little endian!!!" << std::endl;
                }    
            }
        } else {
            std::cout << "ReadPfmFile() NOT opened!!!" <<std::endl;
        }
        
        return nullptr;
    }
    
    void SaveAsPng(std::string path) {
        
    }
}; // class PFM
} // namespace pfm

#endif //PFM_HPP_