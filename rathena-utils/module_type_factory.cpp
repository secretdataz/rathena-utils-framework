#include "module_type_factory.hpp"

#include <iostream>

#include "module.hpp"

namespace rathena {
	namespace utils {
		class null_module : public module {
		public:
			null_module(const std::string &module_name) : module() {
				this->module_name = module_name;
			}
			void initialize() { 
				std::cout << "Module `" << this->module_name << "` cannot be found." << std::endl; 
			}
		private:
			std::string module_name;
		};

		void module_type_factory::register_module_factory(const std::string& module_name, module_factory* factory) {
			this->modules[module_name] = factory;
		}

		module* module_type_factory::create_module(const std::string &type, std::unordered_map<std::string, std::string> args) {
			if (this->modules.find(type) == this->modules.end()) {
				return new null_module(type);
			}
			else {
				return this->modules[type]->create_module(args);
			}
		}

		arg_info module_type_factory::get_required_args_for(const std::string &type) {
			if (this->modules.find(type) == this->modules.end()) {
				arg_info empty = { 0 , "" };
				return empty;
			}
			else {
				const char* args = this->modules[type]->get_required_args();
				int argc = this->modules[type]->get_required_args_count();
				arg_info result = { argc, args };
				return result;
			}
		}

		std::vector<std::string> module_type_factory::get_module_list() {
			std::vector<std::string> module_list;
			module_list.reserve(this->modules.size());
			for (const auto &it : this->modules) {
				module_list.push_back(it.first);
			}
			return module_list;
		}

		void module_type_factory::display_help_for(const std::string &type) {
			if (this->modules.find(type) != this->modules.end()) {
				return this->modules[type]->display_help();
			}
		}
	}
}