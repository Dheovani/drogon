#pragma once

#include <drogon/HttpAppFramework.h>

namespace drogon
{
	namespace orm
	{
		class DbClient;
		using DbClientPtr = std::shared_ptr<DbClient>;
	}
}

namespace drogon_model
{
	namespace postgres
	{
		class Database
		{
			private:
				static drogon::orm::DbClientPtr client;

				Database() = default;

				static void generateConnection();

			public:
				static void initialize();

				static drogon::orm::DbClientPtr getDbClient() noexcept(false);
		};
	}
}