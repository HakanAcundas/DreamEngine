#pragma once
#include <string>

namespace dream { namespace utils {

	class FileUtils
	{
	public:
		static std::string read_file(const char* filePath)
		{
			//Open the file
			FILE* file = fopen(filePath, "rt");

			// Go to end of the file
			fseek(file, 0, SEEK_END);
			unsigned long lenght = ftell(file);
			char* data = new char[lenght + 1];
			memset(data, 0, lenght + 1);
			// Go back to the begining of the file.
			fseek(file, 0, SEEK_SET);
			fread(data, 1, lenght, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
	};
}}