#include <drogon/drogon.h>
#include <fstream>

int main() {
    // Arquivo de configuração deve ficar no diretório out/build/x64-RelWithDebInfo
    std::ifstream dbconf("dbconf.json");
    Json::Value connData;
    dbconf >> connData;

    const std::string dbType = connData["dbType"].asString();
    const std::string host = connData["host"].asString();
    const unsigned short port = connData["port"].asInt();
    const std::string databaseName = connData["databaseName"].asString();
    const std::string userName = connData["userName"].asString();
    const std::string password = connData["password"].asString();

    drogon::app().addListener("localhost", 8080);
    drogon::app().createDbClient(
        dbType,
        host,
        port,
        databaseName,
        userName,
        password
    );

    drogon::app().run();
    return 0;
}
