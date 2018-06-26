#ifndef MODULE_H
#define MODULE_H

#include <unordered_map>

namespace rathena {
	namespace utils {
		class module{
		public:
			virtual void initialize() = 0;
			virtual ~module() {}
		};

		class module_factory {
		public:
			virtual module* create_module(std::unordered_map<std::string, std::string> args) = 0;
			virtual const char* get_required_args() = 0;
			virtual int get_required_args_count() = 0;
			virtual void display_help() = 0;
			virtual ~module_factory() {}
		};
	}
}

#endif