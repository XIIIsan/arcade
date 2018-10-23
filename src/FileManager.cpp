//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// FileManager.cpp
//

#include <dirent.h>
#include <stdexcept>
#include <iostream>
#include <regex>
#include <memory>
#include <cstring>
#include <sys/stat.h>
#include "Core/FileManager.hpp"

static int filter_files(const struct dirent *e)
{
	std::regex expr(R"(.*lib_arcade_[\d\w_]+\.so)");
	struct stat st;
	memset(&st, 0, sizeof(st));
	stat(e->d_name, &st);
	int ret = 0;
	if (std::regex_match(e->d_name, expr))
		ret = 1;
	return ret;
}

std::unique_ptr<std::vector<std::string>> Arcade::FileManager::fileList(const std::string &path)
{
	std::unique_ptr<std::vector<std::string>> ret(new std::vector<std::string>);
	struct dirent **files;
	int retValue = scandir(path.c_str(), &files, nullptr, alphasort);
	if (retValue == -1)
		throw std::invalid_argument(strerror(errno));
	for (int i = 0; i < retValue; i++) {
		if (filter_files(files[i]) == 1)
			ret->emplace_back(path + "/" + files[i]->d_name);
		free(files[i]);
	}
	free(files);
	return ret;
}