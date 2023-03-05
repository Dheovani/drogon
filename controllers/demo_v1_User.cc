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
    const std::string& email,
    std::string fone
) {
    Json::Value response;

    try {
        Json::Value accountData;
        accountData["username"] = userName;
        accountData["passwd"] = passwd;
        Account account(accountData);
        accountData = accountService.createAccount(account);

        if (accountData["object"].isNull()) {
            throw std::invalid_argument(accountData["message"].asString());
        }

        Json::Value profileData;
        profileData["fullname"] = fullName;
        profileData["email"] = email;
        profileData["fone"] = fone;
        profileData["accountId"] = accountData["object"]["id"];
        profileData["email"] = email;
        Profile profile(profileData);
        Json::Value createdProfile = profileService.createProfile(profile);

        response["success"] = TRUE;
        response["message"] = "Inserido com sucesso";
        response["object"] = createdProfile;
    }
    catch (const std::exception& ex) {
        response["success"] = FALSE;
        response["message"] = ex.what();
    }

    auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    callback(resp);
}

void User::login(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    const std::string& userName,
    const std::string& passwd
) {
    Json::Value response;
    response["token"] = NULL;
    response["success"] = FALSE;

    try {
        mToken = generateToken(passwd);
        auto user = accountService.getByUsername(userName);

        const __int64 id = user["id"].asInt64();
        auto profile = profileService.getByAccount(id);

        if (user && user["passwd"] == passwd) {
            response["token"] = mToken;
            response["success"] = TRUE;
            response["profileId"] = profile["id"].asInt64();
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

void User::deleteProfile(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    __int64 id,
    std::string userName
) {
    Json::Value profile, response;
    response["success"] = FALSE;

    try {
        if (!id && !userName.empty()) {
            Json::Value account = accountService.getByUsername(userName);
            id = account["id"].asInt64();
        }
        profile = profileService.getByAccount(id);

        const __int64 profileId = profile["id"].asInt64();
        const __int64 addressId = profile["addressId"].asInt64();

        profileService.deleteProfile(profileId);
        accountService.deleteAccount(id);

        if (addressService.get(addressId)) {
            addressService.deleteAddress(addressId);
        }

        response["success"] = TRUE;
        response["message"] = "Registro excluido com sucesso";
    }
    catch (const std::exception& ex) {
        response["message"] = ex.what();
    }

    auto resp = HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);

    callback(resp);
}