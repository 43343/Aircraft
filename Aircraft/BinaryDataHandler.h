#pragma once
#include "KeyBinding.h"
#include <fstream>
#include <string>
#include <map>




class BinaryDataHandler
{
public:


public:
    BinaryDataHandler(KeyBinding& key1, KeyBinding& key2);
    void write(const std::map<unsigned int, std::string>& data);
    void read();
private:
    std::ofstream out;
    std::ifstream in;
    KeyBinding* key1;
    KeyBinding* key2;
};
