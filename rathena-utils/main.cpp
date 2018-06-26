#include <cstring>
#include <iostream>
#include <vector>

#include "module.hpp"
#include "module_type_factory.hpp"
#include "getopt.h"
#include "modules/echo/echo.hpp"

using namespace rathena::utils;

int main(int argc, char** argv) {
	module_type_factory factory;
	
	// Modules
	secret::echo_module_creator	echo_factory;
	factory.register_module_factory("echo", &echo_factory);

#ifdef _DEBUG
	auto list = factory.get_module_list();

	std::cout << "Found module: ";
	for (const auto &it : list) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
#endif

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <module name> <parameters>" << std::endl;
		exit(0);
	}
	else {
		std::unordered_map<std::string, std::string> args;
		std::string module_name(argv[1]);
		arg_info required_args = factory.get_required_args_for(module_name);
		int parsed_arg_count = 0;
		if (required_args.count > 0) {
			char c;
			while ((c = getopt(argc - 1, &argv[1], required_args.args)) != -1) {
				switch (c) {
				case ':':
				case '?':
					return 1;
				default:
					args[std::string(1, c)] = optarg;
					++parsed_arg_count;
				}
			}
		}
		if (parsed_arg_count < required_args.count) {
			std::cerr << "Not enough arguments for module `" << module_name << "`." << std::endl;
			factory.display_help_for(module_name);
			exit(1);
		}
		module* module_obj = factory.create_module(module_name, args);
		module_obj->initialize();
	}

	return 0;
}