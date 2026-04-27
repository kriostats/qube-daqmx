#include "Config.h"
#include "INIReader.h"  // from inih
#include <iostream>
#include <fstream>

// Create default config file using DBConfig defaults
static bool CreateDefaultConfig(const std::string& filename, const DBConfig& defaults)
{
    std::ofstream f(filename);
    if (!f) {
        return false;
    }

    using namespace ConfigKeys;

    f << "[" << SectionDatabase << "]\n";
    f << Host << "=" << defaults.host << "\n";
    f << Port << "=" << defaults.port << "\n";
    f << User << "=" << defaults.user << "\n";
    f << Password << "=" << defaults.password << "\n";
    f << Database << "=" << defaults.database << "\n";

    return true;
}

bool LoadConfig(const std::string& filename, DBConfig& config)
{
    INIReader reader(filename);

    if (reader.ParseError() < 0) {
        std::cerr << "Config file not found: " << filename << "\n";

        DBConfig defaults;
        if (CreateDefaultConfig(filename, defaults)) {
            std::cerr << "A default config file has been created.\n";
            std::cerr << "Please edit '" << filename << "' and restart the application.\n";
        }
        else {
            std::cerr << "Failed to create default config file.\n";
        }

        return false;
    }

    using namespace ConfigKeys;

    // Read values from [database] section
    config.host = reader.Get(SectionDatabase, Host, config.host);
    config.port = reader.GetInteger(SectionDatabase, Port, config.port);
    config.user = reader.Get(SectionDatabase, User, config.user);
    config.password = reader.Get(SectionDatabase, Password, config.password);
    config.database = reader.Get(SectionDatabase, Database, config.database);

    // Basic validation
    if (config.user.empty() || config.database.empty()) {
        std::cerr << "Invalid config: 'user' and 'database' must not be empty.\n";
        return false;
    }

    return true;
}