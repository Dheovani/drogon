#include "ProfileService.h"

using namespace drogon;
using namespace service;

Json::Value ProfileService::get(const __int64 id) {
	return mapper.findByPrimaryKey(id).toJson();
}

Json::Value ProfileService::createProfile(Profile& profile) {
	const __int64 id = *profile.getId().get();

	if (ProfileService::get(id)) return 0;

	mapper.insert(profile);
	return id;
}

void ProfileService::deleteProfile(const __int64 id) {
	mapper.deleteByPrimaryKey(id);
}

bool ProfileService::updateProfile(const Profile& profile, __int64 id) {
	if (!ProfileService::get(id)) return FALSE;

	mapper.update(profile);
	return TRUE;
}