#pragma once
#include <string>
#include <cmath>
#include <iostream>
namespace sutils {
	inline void split_convert(int* ptr, int size, const std::string& input, const char seperator);
	inline int convert_to_number(const char*& input);
	inline int convert_to_number(const std::string& input);
	inline void lowercase(std::string& input);
	inline void uppercase(std::string& input);
	inline bool all_number(const std::string& input);
	inline bool find_char(const std::string& String, const char Char);

	inline void split_convert(int* ptr, int size, const std::string& input, const char seperator) {
		std::string buffer;
		int index = 0;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] >= '0' && input[i] <= '9')
				buffer += input[i];
			else if (input[i] == seperator) {
				ptr[index] = convert_to_number(buffer);
				buffer = "";
				index = index < size ? ++index : index = 0;
			}
			if (i == input.size() - 1) {
				ptr[index] = convert_to_number(buffer);
				buffer = "";
				index = index < size ? ++index : index = 0;
			}
		}
	}
	inline int convert_to_number(const char*& input) {
		using namespace std;
		int result = 0;
		int inputSize = 0;
		bool negative = input[0] == '-';
		for (int i = 0; input[i] != '\0'; i++)
			inputSize++;
		for (int i = (int)inputSize; i > -1; --i) {
			for (int j = '0'; j < '0' + 10; j++) {
				if (input[i] == j) {
					result += (int)(pow(10, ((inputSize - 1) - i)) * (j - '0'));
				}
			}
		}
		if (negative) result *= -1;
		return result;
	}

	inline int convert_to_number(const std::string& input) {
		using namespace std;
		int result = 0;
		bool negative = input[0] == '-';
		for (int i = (int)input.size(); i > -1; --i) {
			for (int j = '0'; j < '0' + 10; j++) {
				if (input[i] == j) {
					result += (int)(pow(10, ((input.size() - 1) - i)) * (j - '0'));
				}
			}
		}
		if (negative) result *= -1;
		return result;
	}

	inline void lowercase(std::string& input) {
		using namespace std;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] >= 'A' && input[i] <= 'Z')
				input[i] += 32;
		}
	}

	inline void uppercase(std::string& input) {
		using namespace std;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] >= 'a' && input[i] <= 'z')
				input[i] -= 32;
		}
	}
	inline bool all_number(const std::string& input) {
		bool flag;
		for (int i = 0; i < input.size(); ++i) {
			flag = false;
			if (input[i] >= '0' && input[i] <= '9' || input[i] == '-')
				flag = true;
			if (!flag)
				return false;
		}
		return true;
	}
	inline bool find_char(const std::string& String, const char Char) {
		for (int i = 0; i < String.size(); ++i)
			if (String[i] == Char)
				return true;
		return false;
	}
}
// 1s23 