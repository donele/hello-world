#include "xjson.h"
#include <gtest/gtest.h>

class XJsonTest : public ::testing::Test
{
protected:
	struct TestJson : public JsonObj
	{
		double dvalue_;
		float fvalue_;
		int ivalue_;
		long lvalue_;
		std::string svalue_;
		std::vector<std::string> vsvalue_;
		std::vector<double> vdvalue_;
		std::vector<long> vlvalue_;

		TestJson()
		{
			mem2fromStr_["dvalue"] = [this](const std::string& v){fromStr(v, this->dvalue_);};
			mem2fromStr_["fvalue"] = [this](const std::string& v){fromStr(v, this->fvalue_);};
			mem2fromStr_["ivalue"] = [this](const std::string& v){fromStr(v, this->ivalue_);};
			mem2fromStr_["lvalue"] = [this](const std::string& v){fromStr(v, this->lvalue_);};
			mem2fromStr_["svalue"] = [this](const std::string& v){fromStr(v, this->svalue_);};
			mem2fromStr_["vsvalue"] = [this](const std::string& v){fromStr(v, this->vsvalue_);};
			mem2fromStr_["vdvalue"] = [this](const std::string& v){fromStr(v, this->vdvalue_);};
			mem2fromStr_["vlvalue"] = [this](const std::string& v){fromStr(v, this->vlvalue_);};

			mem2toStr_["dvalue"] = [this](){return toStr(dvalue_);};
			mem2toStr_["fvalue"] = [this](){return toStr(fvalue_);};
			mem2toStr_["ivalue"] = [this](){return toStr(ivalue_);};
			mem2toStr_["lvalue"] = [this](){return toStr(lvalue_);};
			mem2toStr_["svalue"] = [this](){return toStr(svalue_);};
			mem2toStr_["vsvalue"] = [this](){return toStr(vsvalue_);};
			mem2toStr_["vdvalue"] = [this](){return toStr(vdvalue_);};
			mem2toStr_["vlvalue"] = [this](){return toStr(vlvalue_);};
		}
	};

	void SetUp() override {
		jsonStr = "{\"dvalue\" : -12.345,  \
                    \"fvalue\" : 1.234, \
                    \"ivalue\" : 42, \
                    \"lvalue\" : -142, \
                    \"svalue\" : \"abc\", \
					\"vsvalue\" : [\"abc\",\"def\"], \
					\"vdvalue\": [-23.4, 56.7, 8.9], \
					\"vlvalue\": [0, -10, 100] \
					}";

	  }

  	std::string jsonStr;
};

TEST_F(XJsonTest, TestFromString)
{
	TestJson jobj;
	str2obj(jsonStr, jobj);
	ASSERT_DOUBLE_EQ(jobj.dvalue_, -12.345);
	ASSERT_FLOAT_EQ(jobj.fvalue_, 1.234);
	EXPECT_EQ(jobj.ivalue_, 42);
	EXPECT_EQ(jobj.lvalue_, -142);
	EXPECT_EQ(jobj.svalue_, "abc");

	EXPECT_EQ(jobj.vsvalue_.size(), 2);
	EXPECT_EQ(jobj.vsvalue_[0], "abc");
	EXPECT_EQ(jobj.vsvalue_[1], "def");

	EXPECT_EQ(jobj.vdvalue_.size(), 3);
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[0], -23.4);
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[1], 56.7);
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[2], 8.9);

	EXPECT_EQ(jobj.vlvalue_.size(), 3);
	EXPECT_EQ(jobj.vlvalue_[0], 0);
	EXPECT_EQ(jobj.vlvalue_[1], -10);
	EXPECT_EQ(jobj.vlvalue_[2], 100);

}

TEST_F(XJsonTest, TestToStringFromString)
{
	TestJson jobj;
	str2obj(jsonStr, jobj);
	auto jstr = obj2str(jobj);
	// std::cout << jstr << std::endl;
	TestJson newjobj;
	str2obj(jstr, newjobj);

	ASSERT_DOUBLE_EQ(jobj.dvalue_, newjobj.dvalue_);
	ASSERT_FLOAT_EQ(jobj.fvalue_, newjobj.fvalue_);
	EXPECT_EQ(jobj.ivalue_, newjobj.ivalue_);
	EXPECT_EQ(jobj.lvalue_, newjobj.lvalue_);
	EXPECT_EQ(jobj.svalue_, newjobj.svalue_);

	EXPECT_EQ(jobj.vsvalue_.size(), newjobj.vsvalue_.size());
	EXPECT_EQ(jobj.vsvalue_[0], newjobj.vsvalue_[0]);
	EXPECT_EQ(jobj.vsvalue_[1], newjobj.vsvalue_[1]);

	EXPECT_EQ(jobj.vdvalue_.size(), newjobj.vdvalue_.size());
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[0], newjobj.vdvalue_[0]);
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[1], newjobj.vdvalue_[1]);
	ASSERT_DOUBLE_EQ(jobj.vdvalue_[2], newjobj.vdvalue_[2]);

	EXPECT_EQ(jobj.vlvalue_.size(), newjobj.vlvalue_.size());
	EXPECT_EQ(jobj.vlvalue_[0], newjobj.vlvalue_[0]);
	EXPECT_EQ(jobj.vlvalue_[1], newjobj.vlvalue_[1]);
	EXPECT_EQ(jobj.vlvalue_[2], newjobj.vlvalue_[2]);

}


