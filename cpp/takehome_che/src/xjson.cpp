
#include "xjson.h"
#include <iostream>
#include <regex>

using namespace std;


std::vector<std::string_view> splitString(std::string_view in, char sep) {
    std::vector<std::string_view> r;
    for (auto p = in.begin();; ++p) {
        auto q = p;
        p = std::find(p, in.end(), sep);
        r.emplace_back(q, std::distance(q,p));
        if (p == in.end())
            return r;
    }
}

void JsonObj::fromString(const std::string& field, const std::string& value)
{
	auto it = mem2fromStr_.find(field);

	if (it != mem2fromStr_.end())
	{
		it->second(value);
	}

}

string JsonObj::toString() const
{
	std::string res = "{";
	for (auto& [member, func] : mem2toStr_)
	{
		res.push_back('\"');
		res += member;
		res += "\" :" + func() + ",";
	}
	if (!mem2toStr_.empty())
		res.erase(res.end() - 1);
	
	res += "}";
	return res;
}
