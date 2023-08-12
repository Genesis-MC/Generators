#pragma once
#include <string>
#include <cmath>

namespace sutils {
  inline void split_convert(int* ptr, int size, const std::string& input, const char seperator);
  inline int to_number(const std::string& input);
  inline void lowercase(std::string& input);
  inline void uppercase(std::string& input);
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
	  if (input[i] >= '0' && input[i] <= '9' || input[0] == '-')
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
	  if (input[i] >= '0' && input[i] <= '9' || input[0] == '-' || input[i] == '.')
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
  inline int how_many(const std::string& string, char charToCount) {
	int count = 0;
	for (int i = 0; i < string.length(); i++)
	  if (string[i] == charToCount)
		count++;
	return count;
  }
  inline bool contains(const std::string& string, char charToFind) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] == charToFind)
		return true;
	return false;
  }
  inline int is_lowercase(const std::string& string) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] < 'a' || string[i] > 'z')
		return false;
	return true;
  }
  inline bool contains_a_number(const std::string& string) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] >= '0' && string[i] <= '9')
		return true;
	return false;
  }
  inline int is_uppercase(const std::string& string) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] < 'A' || string[i] > 'Z')
		return false;
	return true;
  }
  inline int has_uppercase_letter(const std::string& string) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] >= 'A' && string[i] <= 'Z')
		return true;
	return false;
  }
  inline int has_lowercase_letter(const std::string& string) {
	for (int i = 0; i < string.length(); i++)
	  if (string[i] >= 'a' && string[i] <= 'z')
		return true;
	return false;
  }
}