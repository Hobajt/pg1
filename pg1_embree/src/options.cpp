#include "stdafx.h"
#include "options.h"

#include <iostream>
#include <fstream>

Options Options::instance = Options::Load("res/optsions.cfg");

Options Options::Load(std::string_view path) {
	Options opts = {};

	std::ifstream file(path.data());
	if (file.is_open()) {
		try {
			std::string line;
			while (std::getline(file, line)) {
				std::string_view value = std::string_view(line.c_str() + line.find_first_of(' ') + 1);
				std::string_view tmp;
				if (line._Starts_with("width ")) {
					opts.width = atoi(value.data());
				}
				else if (line._Starts_with("height ")) {
					opts.height = atoi(value.data());
				}
				else if (line._Starts_with("sampleCount ")) {
					opts.sampleCount = atoi(value.data());
				}
				else if (line._Starts_with("maxDepth ")) {
					opts.maxDepth = atoi(value.data());
				}
				else if (line._Starts_with("path ")) {
					tmp = std::string_view(line.c_str() + 5);
					value = std::string_view(tmp.data() + tmp.find_first_of(' ') + 1);
					if (tmp._Starts_with("model ")) {
						opts.path_model = std::string(value);
					}
					else if (tmp._Starts_with("background ")) {
						opts.path_background = std::string(value);
					}
				}
			}
			printf("Loaded options from '%s'\n", path.data());
		}
		catch (std::exception&) {
			printf("Failed during options parsing, loading default options.\n");
			opts = Options();
		}
	}
	else {
		printf("Failed to load options, using default ones.\n");
	}

	return opts;
}