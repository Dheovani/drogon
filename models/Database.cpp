#include "Database.h"
#include <fstream>

using namespace drogon_model::postgres;

drogon::orm::DbClientPtr Database::client;

void Database::generateConnection() {
    // Arquivo de configuração deve ficar no diretório out/build/x64-RelWithDebInfo
    std::ifstream dbconf("dbconf.json");

    if (!dbconf) {
        throw std::invalid_argument("Nao foi possivel encontrar o arquivo de configuracao da conexao com o banco de dados");
    }

    Json::Value connData;
    dbconf >> connData;

    const std::string dbType = connData["dbType"].asString();
    const std::string host = connData["host"].asString();
    const unsigned short port = connData["port"].asInt();
    const std::string databaseName = connData["databaseName"].asString();
    const std::string userName = connData["userName"].asString();
    const std::string password = connData["password"].asString();

    drogon::app().createDbClient(
        dbType,
        host,
        port,
        databaseName,
        userName,
        password
    );
}

void Database::initialize() {
    generateConnection();

    // Singleton simples pra manter sempre a mesma instância de conexão com o banco de dados
    if (Database::client == NULL) {
        Database::client = drogon::app().getDbClient();
    }
}

drogon::orm::DbClientPtr Database::getDbClient() {
    if (Database::client == NULL) {
        initialize();
    }
        
    return Database::client;
}
