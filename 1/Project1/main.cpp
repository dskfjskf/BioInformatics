#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int PatternCount(string pattern, string genome) 
{
	int res = 0;
	string str = genome;
	while (str.find(pattern)!= string::npos)
	{
		res++;
		str.erase(0,str.find(pattern)+1);
	}
	return res;
}

void FrequentWords(string str, int k)
{
	map<string, int> res;
	int max=0;

	for (int i = 0; i < str.length()-k+1; i++)
	{
		res[str.substr(i, k)]++;
		if (res[str.substr(i, k)] > max)
			max = res[str.substr(i, k)];
	}

	for (auto i = res.begin(); i != res.end(); ++i)
		if (i->second == max)
			cout << i->first << " ";
}

string ReverseComplement(string str)
{
	const string agct = "AGCT";
	int k = agct.length();

	string res="";

	for (int i = str.length() - 1; i > -1; i--)
		res += agct[k - agct.find(str[i]) - 1];

	return res;
}

int main()
{
	ifstream in;
	in.open("C:\\Users\\user\\Desktop\\bio\\in.txt");

	string p, g;	
	
	getline(in, p);
	getline(in, g);
	
//	cout << PatternCount(p, g)<<endl;
	
//	FrequentWords(gen, k);

//	cout << ReverseComplement(gen) << endl;

	in.close();
	system("pause");
	return 0;
}