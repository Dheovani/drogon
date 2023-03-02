#pragma once

#include <drogon/HttpAppFramework.h>
#include "Address.h"

using namespace drogon;
using namespace drogon_model::postgres;

namespace service
{
class AddressService
{
	private:
		orm::Mapper<Address> addressMapper{ app().getDbClient() };

	public:
		AddressService() = default;

		Json::Value get(const long id);

		long addAddress(const Address& address);

		bool changeAddress(const long id, const Address& address);

		void deleteAddress(const long id);
};
}