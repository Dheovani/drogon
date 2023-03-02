#include "demo_v1_User.h"

using namespace drogon;
using namespace demo::v1;
using namespace drogon_model::postgres;

void User::signUp(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string userName,
    const std::string passwd,
    const std::string email,
    const std::string fullName,
    const std::string fone
) {
    Json::Value data;

    try {
        Json::Value accountData;
        accountData["userName"] = userName;
        accountData["passwd"] = passwd;
        Account account(accountData);
        __int64 accountId = accountService.createAccount(account);

        Json::Value profileData;
        profileData["fullName"] = fullName;
        profileData["email"] = email;
        profileData["fone"] = fone;
        profileData["accountId"] = accountId;
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
    const std::string userName,
    const std::string passwd
) {}

void User::getUserInfo(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    long id,
    const std::string token
) const {}

void User::addAddress(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    std::string country,
    std::string city,
    std::string zipCode
) {}