#ifndef MODULE_TYPE_FACTORY_H
#define MODULE_TYPE_FACTORY_H

#include <string>
#include <unordered_map>

#include "module.hpp"

namespace rathena {
	namespace utils {
		struct arg_info {
			int count;
			const char* args;
		};

		class module_type_factory {
		public:
			void register_module_factory(const std::string& module_name, module_factory* factory);
			module* create_module(const std::string &type, std::unordered_map<std::string, std::string> args);
			arg_info get_required_args_for(const std::string &type);
			void display_help_for(const std::string &type);
			std::vector<std::string> get_module_list();
		private:
			std::unordered_map<std::string, module_factory*> modules;
		};
	}
}

#endif