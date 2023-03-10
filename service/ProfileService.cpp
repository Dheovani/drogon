#include "ProfileService.h"

using namespace service;
using drogon::orm::Criteria;
using drogon::orm::CompareOperator;

Json::Value ProfileService::get(const __int64& id) {
	try {
		return mapper.findByPrimaryKey(id).toJson();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return NULL;
	}
}

Json::Value ProfileService::getByAccount(const __int64& id) {
	try {
		Criteria criteria("account_id", CompareOperator::EQ, id);
		return mapper.findOne(criteria).toJson();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
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

bool ProfileService::updateProfile(Profile& profile, __int64 addressId) {
	if (!ProfileService::get(*profile.getId().get())) {
		return FALSE;
	}

	if (addressId != NULL) {
		profile.setAddressId(addressId);
	}

	mapper.update(profile);
	return TRUE;
}