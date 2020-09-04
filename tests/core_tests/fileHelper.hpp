#pragma once

#include "romfs/utils.hpp"
#include <string>
#include <vector>

std::vector<u8> readFileToMemory(std::string fileName);
