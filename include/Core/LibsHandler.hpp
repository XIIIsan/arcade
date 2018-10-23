//
// EPITECH PROJECT, 2018
// arcade
// File description:
// LibsHandler
//

#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include "FileManager.hpp"
#include "Core/DLLoader.hpp"

namespace Arcade {
	template<typename T>
	class LibsHandler {
	public:
		LibsHandler(const std::string &path)
			: _libsNames(Arcade::FileManager::fileList(path)),
			  _lib(nullptr)
		{
		}
		~LibsHandler() = default;

		// returns the name of the lib to load
		std::string rightLib()
		{
			std::string ret("None");
			if (_libsNames->size() <= 1)
				return ret;
			const std::string &path = _lib->getPath();
			auto it = std::find(_libsNames->begin(),
					    _libsNames->end(), path);
			if (it < _libsNames->end() - 1)
				ret = *(it + 1);
			else if (it == _libsNames->end() - 1)
				ret = *_libsNames->begin();
			return ret;
		}

		std::string leftLib()
		{
			std::string ret("None");
			if (_libsNames->size() <= 1)
				return ret;
			const std::string &path = _lib->getPath();
			auto it = std::find(_libsNames->begin(),
					    _libsNames->end(), path);
			if (it < _libsNames->end() && it > _libsNames->begin())
				ret = *(it - 1);
			else if (it == _libsNames->begin())
				ret = *(_libsNames->end() - 1);
			return ret;
		}

		void unloadLib()
		{
			this->_lib = nullptr;
		}

		bool loadLib(const std::string &name)
		{
			auto &tmp = *this->_libsNames;
			auto it = std::find(tmp.begin(), tmp.end(), name);
			bool ret(false);
			if (it != this->_libsNames->end()) {
				delete this->_lib;
				this->_lib = new Arcade::DLLoader<T>(name);
				if (this->_lib != nullptr)
					ret = true;
			}
			return ret;
		}

		std::vector<std::string> &getNames() const
		{
			return *this->_libsNames;
		}

		T *getInstance()
		{
			if (this->_lib == nullptr)
				return nullptr;
			return this->_lib->getInstance();
		}
	private:
		std::unique_ptr<std::vector<std::string>> _libsNames;
		Arcade::DLLoader<T> *_lib;
	};
}