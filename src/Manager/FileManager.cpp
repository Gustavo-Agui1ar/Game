
#include "../includes/Manager/FileManager.h"

namespace Game::Manager{

    FileManager::FileManager():
    m_readFile(), m_writeFile()
    {

    }
    
    FileManager::~FileManager()
    {
        if(m_writeFile.is_open())
            m_writeFile.close();

        if(m_readFile.is_open())
            m_readFile.close();
    }

    void FileManager::openReadFile(const char* pathFile)
    {
        m_readFile.open(pathFile);

        if(!m_readFile.is_open())
        {
            std::cout<<"FileManager::not possible to open the file "<< pathFile << std::endl;
            exit(1);
        }
    }

    void FileManager::closeReadFile()
    {
        m_readFile.close();
    }

    void FileManager::openWriteFile(const char* pathFile)
    {
        m_writeFile.open(pathFile, std::ios::app);

        if(!m_writeFile.is_open())
        {
            std::cout << "FileManager:: not possible to open file " << pathFile << std::endl;
            exit(1);
        }
    }

    void FileManager::closeWriteFile()
    {
        m_writeFile.close();
    }

    nlohmann::ordered_json  FileManager::readFile(const char* pathFile)
    {
        openReadFile(pathFile);
        
        nlohmann::ordered_json json;

        json = nlohmann::ordered_json::parse(m_readFile);

        closeReadFile();

        return json;
    }
    
    std::vector<std::string>  FileManager::readFileText(const char* pathFile)
    {
        openReadFile(pathFile);
        
        std::vector<std::string> talks;

        std::string talk = "";

        while(std::getline(m_readFile, talk))
            talks.push_back(talk);

        closeReadFile();

        return talks;
    }

    void FileManager::writeContent(const char* pathFile, nlohmann::ordered_json json)
    {
        openWriteFile(pathFile);

        m_writeFile << std::setw(2) << json;

        closeWriteFile();
    }

    void FileManager::removeFile(const char* pathFile)
    {
        remove(pathFile);
    }
}