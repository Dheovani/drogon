#pragma once

#include <drogon/HttpAppFramework.h>
#include "Database.h"
#include "Profile.h"

using namespace drogon_model::postgres;

namespace service
{
	class ProfileService
	{
		private:
			drogon::orm::Mapper<Profile> mapper{ Database::getDbClient() };

		public:
			ProfileService() = default;

			Json::Value get(const __int64& id);

			Json::Value getByAccount(const __int64& id);

			Json::Value createProfile(Profile& profile);

			void deleteProfile(const __int64& id);

			bool updateProfile(Profile& profile, __int64 addressId = NULL);
	};
}