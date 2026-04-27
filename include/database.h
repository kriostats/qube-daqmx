// include/database.h
#pragma once

#include <mysql.h>
#include <string>
#include "Config.h"

namespace qube::db {

    class Database {
    public:
        Database() = default;
        ~Database();

        bool connect(const DBConfig& config);
        void disconnect();

        bool is_connected() const;

        MYSQL* handle(); // low-level access (needed for now)

        // disable copy (same reasoning you had before)
        Database(const Database&) = delete;
        Database& operator=(const Database&) = delete;

    private:
        MYSQL* conn_ = nullptr;
    };

}