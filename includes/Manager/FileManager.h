
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../includes/json.hpp"

namespace Game::Manager {


    class FileManager{
        
    private:

        std::ifstream m_readFile; 
        std::ofstream m_writeFile; 

        void openReadFile(const char* pathFile);
        void closeReadFile();
        
        void openWriteFile(const char* pathFile);
        void closeWriteFile();

    public:
        
        FileManager();
        ~FileManager();

        nlohmann::ordered_json readFile(const char* pathFile);
        std::vector<std::string> readFileText(const char* pathFile);
        
        void writeContent(const char* pathFile, nlohmann::ordered_json json);
        
        void removeFile(const char* pathFile);
    };
}