#pragma once

#include <drogon/HttpAppFramework.h>
#include "Database.h"
#include "Account.h"

using namespace drogon;
using namespace drogon_model::postgres;

namespace service
{
	class AccountService
	{
		private:
			orm::Mapper<Account> mapper{ Database::getDbClient() };

		public:
			Json::Value get(const __int64 id);

			Json::Value getByUsername(const std::string username);

			Json::Value createAccount(Account account) noexcept(false);

			void deleteAccount(const __int64 id);

			bool updateUserName(const __int64 id, const std::string newUserName);

			bool changePasswd(const __int64 id, const std::string newPasswd);
	};
}