#include "AccountService.h"

using namespace drogon;
using namespace service;

Json::Value AccountService::get(const __int64 id) {
	try {
		return mapper.findByPrimaryKey(id).toJson();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return NULL;
	}
}

Json::Value AccountService::getByUsername(const std::string username) {
	try {
		orm::Criteria criteria("username", orm::CompareOperator::EQ, username);
		return mapper.findOne(criteria).toJson();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return NULL;
	}
}

Json::Value AccountService::createAccount(Account account) {
	Json::Value response;

	try {
		Json::Value object = this->getByUsername(*account.getUsername().get());

		if (object != NULL) {
			throw std::invalid_argument("Nome de usuario invalido");
		}

		mapper.insert(account);

		response["success"] = TRUE;
		response["message"] = "Registro inserido com sucesso";
		response["object"] = account.toJson();
	}
	catch (std::exception &ex) {
		response["success"] = FALSE;
		response["message"] = ex.what();
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
