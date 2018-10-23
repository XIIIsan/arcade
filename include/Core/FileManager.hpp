//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// FileManager.hpp
//

#pragma once

#include <string>
#include <vector>

namespace Arcade {
	class FileManager {
	public:
		static std::unique_ptr<std::vector<std::string>> fileList(const std::string &path);
	};
}


