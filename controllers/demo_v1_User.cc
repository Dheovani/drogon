#include "demo_v1_User.h"

using namespace drogon;
using namespace demo::v1;
using namespace drogon_model::postgres;

void User::signUp(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& userName,
    const std::string& passwd,
    const std::string& fullName,
    std::string email,
    std::string fone
) {
    Json::Value data;

    try {
        Json::Value accountData;
        accountData["username"] = userName;
        accountData["passwd"] = passwd;
        Account account(accountData);
        accountData = accountService.createAccount(account);

        Json::Value profileData;
        profileData["fullname"] = fullName;
        profileData["email"] = email;
        profileData["fone"] = fone;
        profileData["accountId"] = accountData["object"]["id"];
        profileData["email"] = email;
        Profile profile(profileData);
        Json::Value createdProfile = profileService.createProfile(profile);

        data["success"] = TRUE;
        data["message"] = "Inserido com sucesso";
        data["object"] = createdProfile;
    }
    catch (const std::exception& ex) {
        data["success"] = FALSE;
        data["message"] = ex.what();
    }

    auto resp = HttpResponse::newHttpJsonResponse(data);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    callback(resp);
}

void User::login(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& userName,
    const std::string& passwd
) {}

void User::getUserInfo(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const __int64& id,
    const std::string& token
) {
    Json::Value response;
    response["object"] = NULL;
    response["success"] = FALSE;

    try {
        if (token == mToken) {
            response["object"] = profileService.get(id);
            response["success"] = TRUE;
        }
    }
    catch (const std::exception& ex) {
        response["message"] = ex.what();
    }

    auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    callback(resp);
}

void User::addAddress(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const __int64& profile,
    const std::string& country,
    const std::string& city,
    const std::string& zipCode
) {}