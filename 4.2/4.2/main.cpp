#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

const string ACGT = "ACGT";

int d(string pattern, vector<string>& dna) {
	int d=0;
	vector<int> distance;
	distance.resize(dna.size());
	for (int i = 0; i < distance.size(); i++)
		distance[i] = pattern.length();

	int temp;

	for (int i = 0; i < dna.size(); i++)
		for (int j = 0; j < dna[i].size() - pattern.length() + 1; j++)
		{
			temp = pattern.length();
			for (int g = j; g < j + pattern.length(); g++)
				if (dna[i][g] == pattern[g - j])
					temp--;
			if (temp < distance[i])
				distance[i] = temp;
		}

	for (int i = 0; i < dna.size(); i++)
		d += distance[i];

	return d;
}

string nextchange(string pattern) {
	string res="";
	int temp = 1, sum = 0;
	bool f = true;

	for (int i = 0; i < pattern.length(); i++)
		if (pattern[i] != 'T')
			f = false;
	if (!f)
	{
		for (int i = pattern.length() - 1; i > -1; i--)
		{
			sum += ACGT.find(pattern[i])*temp;
			temp *= 4;
		}

		sum++;
		vector<int> next;

		while (4 <= sum) {
			next.push_back(sum % 4);
			sum /= 4;
		}
		next.push_back(sum);

		while (next.size()<pattern.length())
			next.push_back(0);

		for (int i = next.size() - 1; i > -1; i--)
			res += ACGT[next[i]];		
	}

	return res;
}

string MedianString(int n) {
	vector<string> dna;
	string curr = "";

	while (!cin.eof()) 
	{
		cin >> curr;
		dna.push_back(curr);
	}

	string pattern = "";
	string Median;
	int distance;

	for (int i = 0; i < n; i++)
		pattern += "A";
	distance = d(pattern, dna);
	Median = pattern;

	for (float i = 0; i < pow(4, n)-1; i += 1)
	{
		pattern = nextchange(pattern);
		if (d(pattern, dna) < distance)
		{
			distance = d(pattern, dna);
			Median = pattern;
		}
	}

	return Median;
}

int main() {
	int n;
	cin >> n;
	cout << MedianString(n);
	system("pause");
	return 0;
}