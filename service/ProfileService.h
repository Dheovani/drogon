#pragma once

#include <drogon/HttpAppFramework.h>
#include "Profile.h"

using namespace drogon;
using namespace drogon_model::postgres;

namespace service
{
class ProfileService
{
	private:
		orm::Mapper<Profile> profileMapper{ app().getDbClient() };

	public:
		ProfileService() = default;

		Json::Value get(const long id);

		Json::Value createProfile(const Profile& profile);

		void deleteProfile(const long id);

		bool updateProfile(const Profile& profile, long id);
};
}