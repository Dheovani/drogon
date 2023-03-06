#pragma once

#include <drogon/HttpAppFramework.h>
#include "Database.h"
#include "Address.h"

using namespace drogon_model::postgres;

namespace service
{
	class AddressService
	{
		private:
			drogon::orm::Mapper<Address> mapper{ Database::getDbClient() };

		public:
			AddressService() = default;

			Json::Value get(const __int64& id);

			__int64 addAddress(Address &address);

			bool changeAddress(const __int64& id, const Address &address);

			void deleteAddress(const __int64& id);
	};
}