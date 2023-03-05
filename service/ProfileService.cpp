#include "ProfileService.h"

using namespace drogon;
using namespace service;

Json::Value ProfileService::get(const __int64& id) {
	try {
		return mapper.findByPrimaryKey(id).toJson();
	}
	catch (const std::exception& ex) {
		return NULL;
	}
}

Json::Value ProfileService::getByAccount(const __int64& id) {
	try {
		orm::Criteria criteria("account_id", orm::CompareOperator::EQ, id);
		return mapper.findOne(criteria).toJson();
	}
	catch (const std::exception& ex) {
		return NULL;
	}
}

Json::Value ProfileService::createProfile(Profile& profile) {
	mapper.insert(profile);
	return profile.toJson();
}

void ProfileService::deleteProfile(const __int64& id) {
	mapper.deleteByPrimaryKey(id);
}

bool ProfileService::updateProfile(Profile& profile, const __int64& id) {
	if (!ProfileService::get(id)) return FALSE;

	mapper.update(profile);
	return TRUE;
}