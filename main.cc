#include <drogon/drogon.h>
#include "Database.h"

int main() {
    drogon::app().addListener("localhost", 8080);

    // Inicializar a conexão com o banco
    drogon_model::postgres::Database::initialize();

    drogon::app().run();
    return 0;
}
