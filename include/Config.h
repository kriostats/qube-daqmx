//Config.h
#pragma once

#include <string>

// Holds database configuration
struct DBConfig
{
    std::string host = "localhost";
    unsigned int port = 3306;  
    std::string user = "";
    std::string password = "";
    std::string database = "";
};

// INI keys/constants (centralized to avoid typos)
namespace ConfigKeys
{
    constexpr const char* SectionDatabase = "database";

    constexpr const char* Host = "host";
    constexpr const char* Port = "port";
    constexpr const char* User = "user";
    constexpr const char* Password = "password";
    constexpr const char* Database = "database";
}

// Returns true if config loaded successfully
bool LoadConfig(const std::string& filename, DBConfig& config);
