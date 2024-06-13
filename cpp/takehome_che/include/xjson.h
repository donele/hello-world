
#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
#include "xtime.h"
#include <sstream>

std::vector<std::string_view> splitString(std::string_view in, char sep);

template<typename T>
void fromStr(const std::string&, T& value)
{
}

inline void fromStr(const std::string& s, double& value)
{
	value = std::stod(s);
}

inline void fromStr(const std::string& s, float& value)
{
	value = std::stof(s);
}

template<>
inline void fromStr(const std::string& s, int64_t& value)
{
	value = std::stoll(s);
}

template<>
inline void fromStr(const std::string& s, long& value)
{
	value = std::stol(s);
}

template<>
inline void fromStr(const std::string& s, int& value)
{
	value = std::stoi(s);
}

template<>
inline void fromStr(const std::string& s, std::string& value)
{
	value = s;
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
inline void fromStr(const std::string& s, std::vector<T>& value)
{
	auto strVec = splitString(s, ',');

	for (auto& e : strVec)
		value.push_back(stod(std::string(e)));

}

template<typename T, typename std::enable_if_t<std::is_integral<T>::value, bool> = true>
inline void fromStr(const std::string& s, std::vector<T>& value)
{

	auto strVec = splitString(s, ',');
	for (auto& e : strVec)
		value.push_back(stoll(std::string(e)));
}

template<>
inline void fromStr(const std::string& s, std::vector<std::string>& value)
{

	auto strVec = splitString(s, ',');
	for (auto& e : strVec)
	{
		auto estr = std::string(e);
		estr.erase(remove(estr.begin(), estr.end(), '\"'), estr.end());
		value.push_back(estr);
	}
}


template<typename T>
inline std::string toStr(const T& value)
{
	return std::to_string(value);
}

template<>
inline std::string toStr(const std::string& value)
{
	return "\"" + value + "\"";
}

template<typename T, typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
inline std::string toStr(const std::vector<T>& value)
{
	std::string res = "[";
	for (auto& s : value)
		res += std::to_string(s) + ",";
	if (!value.empty())
		res.erase(res.end() - 1);
	res += "]";
	return res;
}

template<>
inline std::string toStr(const std::vector<std::string>& value)
{
	std::string res = "[";
	for (auto& s : value)
		res += "\"" + s + "\",";
	if (!value.empty())
		res.erase(res.end() - 1);
	res += "]";
	return res;
}


// from json string to any data structure, which follows certain protocol

template <typename T>
void str2obj(const std::string& input, T& obj)
{

	auto pos = input.find_first_not_of(" \t\n\r");
	if (pos == std::string::npos or input[pos] != '{')
		throw std::runtime_error("wrong format of json");

	while (pos < input.size())
	{
		auto keyStartPos = input.find_first_of('"', pos);
		auto keyEndPos = input.find_first_of('"', keyStartPos+1);
		auto key = input.substr(keyStartPos+1, keyEndPos-keyStartPos-1);

		pos = input.find_first_of(':', keyEndPos);
		auto valueStartPos = input.find_first_not_of(" \t\n\r", pos+1);
		size_t valueEndPos;

		if (input[valueStartPos] == '[') // it is an array
		{
			valueEndPos = input.find_first_of(']', valueStartPos + 1);
			valueStartPos++;
		}
		else if (input[valueStartPos] == '"') // string
		{
			valueEndPos = input.find_first_of('"', valueStartPos + 1);
			valueStartPos++;
		}
		else // numbers: double or integer
		{
			valueEndPos = input.find_first_not_of("-1234567890.", valueStartPos + 1);
		}

		auto value = input.substr(valueStartPos, valueEndPos-valueStartPos);
		obj.fromString(key, value);
		pos = input.find_first_of(",}", valueEndPos);

		if (input[pos] == '}')
			break;
		pos++;

	}
}

// from a data structure to json string
template <typename T>
std::string obj2str(const T& obj)
{
	return obj.toString();
}

// base class of data structure that can convert to or from json string
class JsonObj
{
public:
	void fromString(const std::string& field, const std::string& value);
	std::string toString() const;

protected:
	std::unordered_map<std::string, std::function<void(const std::string&)>> mem2fromStr_;
	std::unordered_map<std::string, std::function<std::string(void)>> mem2toStr_;
};