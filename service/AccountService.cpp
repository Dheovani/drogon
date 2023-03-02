#include "AccountService.h"

using namespace drogon;
using namespace service;

Json::Value AccountService::get(const long id) {
	return mapper.findByPrimaryKey(id).toJson();
}

long AccountService::createAccount(Account &account) {
	const long id = *account.getId().get();

	if (AccountService::get(id)) return 0;
			
	mapper.insert(account);
	return id;
}

void AccountService::deleteAccount(const long id) {
	mapper.deleteByPrimaryKey(id);
}

bool AccountService::updateUserName(const long id, const std::string newUserName) {
	Json::Value accountData = AccountService::get(id);

	if (accountData) {
		accountData["userName"] = newUserName;
		Account account(accountData);
		mapper.update(account);

		return TRUE;
	}

	return FALSE;
}

bool AccountService::changePasswd(const long id, const std::string newPasswd) {
	Json::Value accountData = AccountService::get(id);

	if (accountData) {
		accountData["passwd"] = newPasswd;
		Account account(accountData);
		mapper.update(account);

		return TRUE;
	}

	return FALSE;
}
