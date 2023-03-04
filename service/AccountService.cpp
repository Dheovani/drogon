#include "AccountService.h"

using namespace drogon;
using namespace service;

Json::Value AccountService::get(const __int64 id) {
	return mapper.findByPrimaryKey(id).toJson();
}

Json::Value AccountService::getByUsername(const std::string username) {
	orm::Criteria criteria("username", orm::CompareOperator::EQ, username);
	return mapper.findOne(criteria).toJson();
}

Json::Value AccountService::createAccount(Account account) {
	Json::Value response;

	try {
		mapper.insert(account);

		response["success"] = TRUE;
		response["message"] = "Registro inserido com sucesso";
		response["object"] = account.toJson();
	}
	catch (std::exception &ex) {
		response["success"] = FALSE;
		response["message"] = ex.what();
		response["object"] = NULL;
	}

	return response;
}

void AccountService::deleteAccount(const __int64 id) {
	mapper.deleteByPrimaryKey(id);
}

bool AccountService::updateUserName(const __int64 id, const std::string newUserName) {
	Json::Value accountData = AccountService::get(id);

	if (accountData) {
		accountData["userName"] = newUserName;
		Account account(accountData);
		mapper.update(account);

		return TRUE;
	}

	return FALSE;
}

bool AccountService::changePasswd(const __int64 id, const std::string newPasswd) {
	Json::Value accountData = AccountService::get(id);

	if (accountData) {
		accountData["passwd"] = newPasswd;
		Account account(accountData);
		mapper.update(account);

		return TRUE;
	}

	return FALSE;
}
