#pragma once

#include <drogon/HttpController.h>
#include "service/AccountService.h"
#include "service/AddressService.h"
#include "service/ProfileService.h"

using namespace drogon;
using namespace service;

namespace demo
{
namespace v1
{
class User : public HttpController<User>
{
	private:
		AccountService accountService;
		AddressService addressService;
		ProfileService profileService;

	public:
		METHOD_LIST_BEGIN
		METHOD_ADD(User::signUp, "/signup?username={1}&passwd={2}&email={3}&fullName={4}&fone={5}", Post);
		METHOD_ADD(User::login, "/login?username={1}&passwd={2}", Post);
		METHOD_ADD(User::getUserInfo, "/{1}/info?token={2}", Get);
		METHOD_ADD(User::addAddress, "/address?country={1}&city={2}&zipcode={3}", Post);
		METHOD_LIST_END

		void signUp(
			const HttpRequestPtr &req,
			std::function<void(const HttpResponsePtr&)>&& callback,
			const std::string userName,
			const std::string passwd,
			const std::string email,
			const std::string fullName,
			const std::string fone
		);

		void login(
			const HttpRequestPtr &req,
			std::function<void(const HttpResponsePtr&)>&& callback,
			const std::string userName,
			const std::string passwd
		);

		void getUserInfo(
			const HttpRequestPtr &req,
			std::function<void(const HttpResponsePtr&)>&& callback,
			long id,
			const std::string token
		) const;

		void addAddress(
			const HttpRequestPtr &req,
			std::function<void(const HttpResponsePtr&)>&& callback,
			std::string country,
			std::string city,
			std::string zipCode
		);
};
}
}
