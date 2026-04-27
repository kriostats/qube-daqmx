// src/database.cpp
#include "database.h"
#include <iostream>

namespace qube::db {

    Database::~Database() {
        disconnect();
    }

    bool Database::connect(const DBConfig& cfg) {
        MYSQL* temp = mysql_init(nullptr);
        if (!temp) {
            std::cerr << "mysql_init() failed\n";
            return false;
        }

        if (!mysql_real_connect(
            temp,
            cfg.host.c_str(),
            cfg.user.c_str(),
            cfg.password.c_str(),
            cfg.database.c_str(),
            cfg.port,
            nullptr,
            0))
        {
            std::cerr << "Connection failed: "
                << mysql_error(temp) << "\n";
            mysql_close(temp);
            return false;
        }

        // replace existing connection safely
        disconnect();
        conn_ = temp;

        std::cout << "MySQL connected\n";
        return true;
    }

    void Database::disconnect() {
        if (conn_) {
            mysql_close(conn_);
            conn_ = nullptr;
        }
    }

    bool Database::is_connected() const {
        return conn_ != nullptr;
    }

    MYSQL* Database::handle() {
        return conn_;
    }

}