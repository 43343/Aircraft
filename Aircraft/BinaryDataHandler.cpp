#include "BinaryDataHandler.h"
#include "Utility.h"
#include <iostream>

BinaryDataHandler::BinaryDataHandler(KeyBinding& key1, KeyBinding& key2) :
     out("data.save", std::ios::binary | std::ios::app)
   , in("data.save", std::ios::binary | std::ios::app)
   , key1(&key1)
   , key2(&key2)
{
  
}

void BinaryDataHandler::write(const std::map<unsigned int, std::string>& data) {
    for (const auto& pair : data) {
   
        out.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));

        unsigned int length = pair.second.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length));

        out.write(pair.second.c_str(), length);
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    out.close();
}
void BinaryDataHandler::read() {
    while (in.peek() != EOF) {
        unsigned int key;
        unsigned int length;

        // Читаем ключ
        in.read(reinterpret_cast<char*>(&key), sizeof(key));
        if (in.eof()) break; 

        
        in.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (in.eof()) break; 

        std::string value(length, '\0');
        in.read(&value[0], length);
        std::cout << "key:" << key << " value:" << value <<  std::endl;
        if (key < PlayerAction::Count) {
            key1->assignKey(static_cast<PlayerAction::Type>(key), stringToKey(value));
        }
        else {
            key2->assignKey(static_cast<PlayerAction::Type>(key - PlayerAction::Count), stringToKey(value));
        }
    }
    in.close();
}