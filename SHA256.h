#ifndef SHA256_H
#define SHA256_H

#include <string>

std::string stringToBinary(const std::string str);

std::string pad(std::string message, int n = 1);

#endif
