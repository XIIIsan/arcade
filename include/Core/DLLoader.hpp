//
// EPITECH PROJECT, 2018
// arcade
// File description:
// DLLoader
//

#pragma once

#include <dlfcn.h>
#include <string>
#include <iostream>

namespace Arcade {
	template<typename T>
	class DLLoader {
	public:
		DLLoader(const std::string &path)
			: _path(path), _dynamicLib(dlopen(path.c_str(), RTLD_LAZY))
		{
			if (this->_dynamicLib == nullptr)
				std::cerr << "Error: " << dlerror() << std::endl;
		}

		~DLLoader()
		{
			dlclose(_dynamicLib);
		}

		const std::string &getPath() const
		{
			return _path;
		}

		T *getInstance()
		{
			T *(*entry)();
			entry = (T *(*)()) dlsym(_dynamicLib, "entryPoint");
			if (entry == nullptr) {
				std::cerr << "Error" << dlerror() << std::endl;
			}
			auto ret = entry();
			return ret;
		}
	private:
		const std::string _path;
		void *_dynamicLib;
	};
}
