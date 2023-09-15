#pragma once
#include <string>
#include <cmath>

namespace sutils {
	inline void split_convert(int* ptr, int size, const std::string& input, const char seperator);
	inline int to_number(const std::string& input);
	inline std::string lowercase(std::string input);
	inline std::string uppercase(std::string input);
	inline bool all_number(const std::string& input);
	inline bool find_char(const std::string& String, const char Char);
	inline bool contains(const std::string& string, char charToFind);
	inline int how_many(const std::string& string, char charToFind);

	inline void split_convert(int* ptr, int size, const std::string& input, const char seperator) {
		std::string buffer;
		int index = 0;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] >= '0' && input[i] <= '9')
				buffer += input[i];
			else if (input[i] == seperator) {
				ptr[index] = to_number(buffer);
				buffer = "";
				index = index < size ? ++index : index = 0;
			}
			if (i == input.size() - 1) {
				ptr[index] = to_number(buffer);
				buffer = "";
				index = index < size ? ++index : index = 0;
			}
		}
	}
	inline int to_number(const std::string& input) {
		using namespace std;
		int result = 0;
		bool negative = input[0] == '-';
		for (int i = (int) input.size(); i > -1; --i) {
			for (int j = '0'; j < '0' + 10; j++) {
				if (input[i] == j) {
					result += (int) (pow(10, ((input.size() - 1) - i)) * (j - '0'));
				}
			}
		}
		if (negative) result *= -1;
		return result;
	}

	inline std::string lowercase(std::string input) {
		for (auto c : input) {
			if (c >= 'A' && c <= 'Z')
				c += 32;
		}
		return input;
	}

	inline std::string uppercase(std::string input) {
		for (auto c : input) {
			if (c >= 'a' && c <= 'z')
				c -= 32;
		}
		return input;
	}
	inline bool all_number(const std::string& input) {
		bool flag;
		for (int i = 0; i < input.size(); ++i) {
			flag = false;
			if ((input[i] >= '0' && input[i] <= '9') || input[0] == '-')
				flag = true;
			if (!flag)
				return false;
		}
		return true;
	}
	inline bool all_number_float(const std::string& input) {
		if (how_many(input, '.') > 1)
			return false;
		bool flag;
		for (int i = 0; i < input.size(); ++i) {
			flag = false;
			if ((input[i] >= '0' && input[i] <= '9') || input[0] == '-' || input[i] == '.')
				flag = true;
			if (!flag)
				return false;
		}
		return true;
	}
	inline bool find_char(const std::string& String, const char Char) {
		for (auto c : String)
			if (c == Char)
				return true;
		return false;
	}
	inline int how_many(const std::string& string, char charToCount) {
		int count = 0;
		for (auto c : string)
			if (c == charToCount)
				count++;
		return count;
	}
	inline bool contains(const std::string& string, char charToFind) {
		for (auto c : string)
			if (c == charToFind)
				return true;
		return false;
	}
	inline int is_lowercase(const std::string& string) {
		for (auto c : string)
			if (c < 'a' || c > 'z')
				return false;
		return true;
	}
	inline bool contains_a_number(const std::string& string) {
		for (auto c : string)
			if (c >= '0' && c <= '9')
				return true;
		return false;
	}
	inline int is_uppercase(const std::string& string) {
		for (const auto c : string)
			if (c <= 'A' || c >= 'Z')
				return false;
		return true;
	}
	inline int has_uppercase_letter(const std::string& string) {
		for (const auto c : string)
			if (c >= 'A' && c <= 'Z')
				return true;
		return false;
	}
	inline int has_lowercase_letter(const std::string& string) {
		for (const auto c : string)
			if (c >= 'a' && c <= 'z')
				return true;
		return false;
	}

	//inline double close_to(const std::string& input, const std::string& close_to_what) {
	  //  for (auto c : input) {
	  //  }
	//}
}