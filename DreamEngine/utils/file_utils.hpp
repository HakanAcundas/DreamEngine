#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace dream { namespace utils {

	class FileUtils
	{
	public:
		static std::string read_file(const std::string& path)
    {
      std::ifstream f(path);
      std::stringstream ss;
      ss << f.rdbuf();
      return ss.str();
    }
}}
