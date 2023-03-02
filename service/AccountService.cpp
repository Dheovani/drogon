#include "AccountService.h"

using namespace drogon;
using namespace service;

Json::Value AccountService::get(const __int64 id) {
	return mapper.findByPrimaryKey(id).toJson();
}

__int64 AccountService::createAccount(Account &account) {
	const __int64 id = *account.getId().get();

	if (AccountService::get(id)) return 0;
			
	mapper.insert(account);
	return id;
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
