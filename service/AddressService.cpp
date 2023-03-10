#include "AddressService.h"

using namespace service;

Json::Value AddressService::get(const __int64& id) {
	try {
		return mapper.findByPrimaryKey(id).toJson();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return NULL;
	}
}

__int64 AddressService::addAddress(Address& address) {
	mapper.insert(address);
	return *address.getId().get();
}

void AddressService::deleteAddress(const __int64& id) {
	mapper.deleteByPrimaryKey(id);
}

bool AddressService::changeAddress(const __int64& id, const Address &address) {
	if (!AddressService::get(id)) return FALSE;

	mapper.update(address);
	return TRUE;
}