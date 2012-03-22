#include "stdafx.h"
#include <vector>
#include <map>

using namespace std;

struct Custom
{
   double key[3];
};

struct strcomparator {
	size_t idx;
    strcomparator(size_t i) : idx(i) {}
    bool operator()(string const& a, string const& b) const {
		int res = a.compare(b);
        return (res >= 0) ? 1 : 0;
    }
};

struct CustomLess {
    size_t idx;
    CustomLess(size_t i) : idx(i) {}
    bool operator()(Custom const& a, Custom const& b) const {
        return a.key[idx] < b.key[idx];
    }
};

/*
std::sort(myvec.begin(), myvec.end(), CustomLess(0));   (this sorts by the first key entry)
std::sort(myvec.begin(), myvec.end(), CustomLess(1));	(this sorts by the second key entry)

vector<Custom> myvec;
vector<string> strVector;
map<string, string> kingsmap;
*/