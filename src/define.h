#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "utils/DboInstence.h"

#include <cpr/cpr.h>
#include <plog/Log.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <string>
#include <chrono>

class User;
class UserInfo;
class Article;
class Category;
class SystemLog;

namespace dbo = Wt::Dbo;

using Users = dbo::collection<dbo::ptr<User> >;
using UserInfos = dbo::collection<dbo::ptr<UserInfo> >;
using Categorys = dbo::collection<dbo::ptr<Category> >;
using Articles = dbo::collection<dbo::ptr<Article> >;
using Logs = dbo::collection< dbo::ptr<SystemLog> >;

enum class UserStatus
{

};

enum class UserRole
{

};

static std::string GenerateUUID()
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	std::string uuid_string = boost::uuids::to_string(a_uuid);
	return std::move(boost::to_upper_copy<std::string>(uuid_string));
}

#define DISABLE_DEFAULT_KEY(model) \
namespace Wt \
{ \
    namespace Dbo \
    { \
        template<> struct dbo_traits<model> : public dbo_default_traits \
        { \
            typedef std::string IdType; \
            static IdType invalidId() { return std::string(); } \
            static const char* surrogateIdField() { return 0; } \
            static const char* versionField() { return 0; } \
        }; \
        template<> struct dbo_traits<const model> : dbo_traits<model> {}; \
    } \
}

#endif