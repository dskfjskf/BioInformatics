#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const string test = "ACGT";

void change(vector<string>& res, string cur, int ind, map<int, int> wtf, int mism, int d)
{
	wtf[ind] = 1;
	mism++;
	char old = cur[ind];
	for (int i = 0; i < 4; i++)
		if (old != test[i])
		{
			cur[ind] = test[i];
			res.push_back(cur);

			if (mism<d)
				for (auto j = wtf.begin(); j != wtf.end(); ++j)
					if (j->second != 1)
						change(res, cur, j->first, wtf, mism, d);
		}
}

bool kmerinstr(string cur, string str, int d) {
	bool res = false;
	int mismatch = d;
	string temp;

	for (int i = 0; i < str.length() - cur.length() + 1 && (!res); i++)
	{
		mismatch = d;
		temp = str.substr(i, cur.length());
		for (int j = 0; j < cur.length() && mismatch>-1; j++)
			if (temp[j] != cur[j])
				mismatch--;
		if (mismatch > -1)
			res = true;
	}
	return res;
}


bool Motif(string cur, vector<string>& str, int d) {
	bool res = false;
	int j = 1;
	while (j < str.size() && kmerinstr(cur, str[j], d))
		j++;
	if (j >= str.size())
		res = true;
	return res;
}


void MotifEnumeration(int k, int d) {
	vector<string> str;
	map<string, int> res;
	string cur = " ";
	int n, j;

	while (!cin.eof()) {
		cin >> cur;
		str.push_back(cur);
	}


	n = str[0].length();

	for (int i = 0; i < n - k + 1; i++)
	{
		cur = str[0].substr(i, k);
		map<int, int> wtf;
		vector<string> patterns;
		patterns.push_back(cur);
		for (int j = 0; j < k; j++)
			change(patterns, cur, j, wtf, 0, d);
		for (int j = 0; j < patterns.size(); j++)
			if (Motif(patterns[j], str, d))
				res[patterns[j]] = 1;
	}

	for (auto i = res.begin(); i != res.end(); ++i)
		if (i->second == 1)
			cout << i->first << " ";
}



int main() {
	//int k, d;
	//cin >> k >> d;
	//MotifEnumeration(k, d);


	return 0;
}