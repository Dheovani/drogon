#include "ControllerTest.h"
#include <DrogonTest.h>

using namespace drogon_model::postgres;

void ControllerTest::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
    Json::Value response, columns;

    std::string date = std::format("{:%Y-%m-%d %X}", std::chrono::system_clock::now());
    columns["msg_date"] = date;
    columns["message"] = req->body().data();
    columns["errors"] = NULL;
    
    drogon::orm::Mapper<DrogonTest> mapper(drogon::app().getDbClient());
    DrogonTest drogonTest(columns);
    try {
        mapper.insert(drogonTest);

        response["success"] = TRUE;
        response["message"] = "Succesfully isnerted into database";
        response["dbContent"] = "result";
    }
    catch (const std::exception& ex) {
        columns["errors"] = ex.what();
        mapper.insert(drogonTest);

        // Tratamento de error não devolve os dados do banco
        response["success"] = FALSE;
        response["message"] = ex.what();
    }

    HttpResponsePtr resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    callback(resp);
}
