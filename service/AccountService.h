#pragma once

#include <drogon/HttpAppFramework.h>
#include "Account.h"

using namespace drogon;
using namespace drogon_model::postgres;

namespace service
{
class AccountService
{
	private:
		orm::Mapper<Account> mapper{ app().getDbClient() };

	public:
		AccountService() = default;

		Json::Value get(const long id);

		long createAccount(Account &account);

		void deleteAccount(const long id);

		bool updateUserName(const long id, const std::string newUserName);

		bool changePasswd(const long id, const std::string newPasswd);
};
}