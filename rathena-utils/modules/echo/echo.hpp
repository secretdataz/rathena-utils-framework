/**
 * This file serves as an example module
 */
#ifndef MODULE_ECHO_H
#define MODULE_ECHO_H

#include <iostream>
#include <string>

#include "../../module.hpp"

namespace secret {
	class echo_module : public rathena::utils::module {
	public:
		echo_module(const std::string &arg) {
			this->to_echo = arg;
		}
		virtual void initialize() {
			std::cout << "Echo module: " << to_echo << std::endl;
		}
	private:
		std::string to_echo;
	};

	class echo_module_creator : public rathena::utils::module_factory {
	public:
		virtual rathena::utils::module* create_module(std::unordered_map<std::string, std::string> args) {
			return new echo_module(args["e"]);
		}

		virtual void display_help() {
			std::cout << "Usage: rathena-utils echo -e <message to echo>" << std::endl;
		}
		
		virtual const char* get_required_args() {
			return "e:";
		}

		virtual int get_required_args_count() {
			return 1;
		}
	};
}

#endif