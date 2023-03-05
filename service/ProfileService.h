#pragma once

#include <drogon/HttpAppFramework.h>
#include "Database.h"
#include "Profile.h"

using namespace drogon;
using namespace drogon_model::postgres;

namespace service
{
	class ProfileService
	{
		private:
			orm::Mapper<Profile> mapper{ Database::getDbClient() };

		public:
			ProfileService() = default;

			Json::Value get(const __int64& id);

			Json::Value getByAccount(const __int64& id);

			Json::Value createProfile(Profile& profile);

			void deleteProfile(const __int64& id);

			bool updateProfile(Profile& profile, const __int64& id);
	};
}