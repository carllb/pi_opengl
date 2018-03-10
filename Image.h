#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <string>
#include <vector>

int read_image( std::string& filename, int& width, int& height,
    std::vector& pixels);



#endif
