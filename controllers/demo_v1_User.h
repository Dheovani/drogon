#pragma once

#include <drogon/HttpController.h>
#include "service/AccountService.h"
#include "service/AddressService.h"
#include "service/ProfileService.h"
#include <sstream>

using namespace drogon;
using namespace service;

namespace demo
{
	namespace v1
	{
		inline std::string generateToken(std::string hashMsg = "Token generation message") {
			const unsigned int magicNumber = rand() * rand();
			unsigned int hash;

			for (int i = 0; i < hashMsg.length(); i ++) {
				hash = (hash ^ hashMsg[i]) * magicNumber;
			}

			std::stringstream hexStream;
			hexStream << std::hex << std::uppercase << hash;

			return hexStream.str();
		}

		class User : public HttpController<User>
		{
			private:
				AccountService accountService;
				AddressService addressService;
				ProfileService profileService;

				// Token retornado após o login
				std::string mToken = generateToken();

			public:
				METHOD_LIST_BEGIN
				METHOD_ADD(User::signUp, "/signup?username={1}&passwd={2}&fullName={3}&email={4}&fone={5}", Get, Post);
				METHOD_ADD(User::login, "/login?username={1}&passwd={2}", Get, Post);
				METHOD_ADD(User::getUserInfo, "/{1}/info?token={2}", Get);
				METHOD_ADD(User::addAddress, "/address?country={1}&city={2}&zipcode={3}", Get, Post);
				METHOD_ADD(User::deleteProfile, "/delete?id={1}&username={2}", Get, Post);
				METHOD_LIST_END

				void signUp(
					const HttpRequestPtr& req,
					std::function<void(const HttpResponsePtr&)>&& callback,
					const std::string& userName,
					const std::string& passwd,
					const std::string& fullName,
					const std::string& email,
					std::string fone = NULL
				);

				void login(
					const HttpRequestPtr &req,
					std::function<void(const HttpResponsePtr&)>&& callback,
					const std::string &userName,
					const std::string &passwd
				);

				void getUserInfo(
					const HttpRequestPtr& req,
					std::function<void(const HttpResponsePtr&)>&& callback,
					const __int64& id,
					const std::string& token
				);

				void addAddress(
					const HttpRequestPtr &req,
					std::function<void(const HttpResponsePtr&)>&& callback,
					const __int64& profile,
					const std::string& country,
					const std::string& city,
					const std::string& zipCode
				);

				void deleteProfile(
					const HttpRequestPtr& req,
					std::function<void(const HttpResponsePtr&)>&& callback,
					__int64 id = NULL,
					std::string userName = ""
				);
		};
	}
}
