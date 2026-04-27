#include "database.h"
#include "Config.h"

int main() {
    DBConfig cfg;

    if (!LoadConfig("config.ini", cfg)) {
        return 1;
    }

    qube::db::Database db;

    if (!db.connect(cfg)) {
        return 1;
    }

    // later: pass db to other modules

    return 0;
}