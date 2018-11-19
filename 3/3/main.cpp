#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const int MASS[] = { 57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186 };
const string TS = "G 057 A 071 S 087 P 097 V 099 T 101 C 103 I 113 L 113 N 114 D 115 K 128 Q 128 E 129 M 131 H 137 F 147 R 156 Y 163 W 186";

bool isconsist(vector<int> sp, int spsize, vector<int> ppt, int psize)
{
	bool res = true;
	for (int i = 0; i < psize; i++)
	{
		vector<int> ps;
		for (int j = 0; j < psize - i; j++)
		{
			int s = 0;
			for (int k = j; k < j + i + 1; k++)
				s += ppt[k];
			ps.push_back(s);
		}
		for (int j = 0; j < spsize; j++)
		{
			for (int k = 0; k < ps.size(); k++)
			{
				if (sp[j] == ps[k])
				{
					ps.erase(ps.begin() + k);
					break;
				}
			}
		}
		if (ps.size() != 0)
		{
			res = false;
			break;
		}
	}
	return res;
}

void expand(vector<vector<int>>& pept)
{
	int old = 1;
	if (pept.size() != 0)
	{
		old = pept.size();
	}
	pept.resize(old * 18);
	for (int i = 1; i < 18; i++)
	{
		for (int j = 0; j < old; j++)
		{
			pept[i*old + j] = pept[j];
		}
	}
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < old; j++)
		{
			pept[i*old + j].push_back(MASS[i]);
		}
	}
}

int mas(vector<int>& pept)
{
	int res = 0;
	for (int i = 0; i < pept.size(); i++)
		res += pept[i];
	return res;
}
void CyclopeptideSequencing(string str)
{
	vector<vector<int>> peptides;   // Вектор пептидов
	vector<int> spectrum;           // Вектор спектра

									// Перевод строки со спектром в вектор
	str.erase(0, 2);
	str += ' ';
	int n = count(str.begin(), str.end(), ' ');
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		spectrum.push_back(stoi(str.substr(0, str.find(' '))));
		str.erase(0, str.find(' ') + 1);
	}

	// Добавление подходящих по спектру 1-меров в пептиды
	peptides.resize(18);
	for (int i = 0; i < 18; i++)
		peptides[i].push_back(MASS[i]);
	int i = 0;
	while (i < peptides.size())
	{
		if (!isconsist(spectrum, spectrum.size(), peptides[i], peptides[i].size()))
			peptides.erase(peptides.begin() + i);
		else i++;
	}



	while (peptides.size() != 0)
	{
		expand(peptides);

		int  i = 0;
		while (i < peptides.size())
		{
			if (mas(peptides[i]) == spectrum[n - 1])
			{
				if (isconsist(spectrum, spectrum.size(), peptides[i], peptides[i].size()))
				{
					for (int j = 0; j < peptides[i].size()-1; j++)
						cout << peptides[i][j] << "-";
					cout << peptides[i][peptides[i].size() - 1] << ' ';					
				}
				peptides.erase(peptides.begin() + i);
			}

			else if (!isconsist(spectrum, spectrum.size(), peptides[i], peptides[i].size()))
			{
				peptides.erase(peptides.begin() + i);
			}
			else i++;
		}
	}
}

int CyclopeptideScoring(string str, string spec)
{
	int sizeres = str.length()*(str.length() - 1) + 2;
	int *res = new int[sizeres];
	string str2 = str + str;

	for (int i = 0; i < sizeres; i++)
		res[i] = 0;

	for (int i = 0; i < str.length(); i++)
		res[1] += stoi(TS.substr(TS.find(str[i]) + 2, 3));

	int j = 2, m;

	for (int i = 0; i < str.length(); i++)
		for (int k = 1; k < str.length(); k++)
		{
			m = k;
			while (m > 0)
			{
				res[j] += stoi(TS.substr(TS.find(str2[i + m - 1]) + 2, 3));
				m--;
			}
			j++;
		}
	sort(res, res + sizeres);
	
	spec += ' ';
	int n = count(spec.begin(), spec.end(), ' ');
	int * a=new int[n];

	for (int i = 0; i < n; i++) {
		a[i] = stoi(spec.substr(0, spec.find(' ')));
		spec.erase(0, spec.find(' ') + 1);
	}

	int score=0;	
	j = 0;

	for (int i = 0; i < sizeres; i++) {		
		while ((j < n) && (res[i] > a[j]))
			j++;
		if ((j < n) && (res[i] == a[j]))
		{			
			score++;
			j++;
		}
	}
	
	return score;
}

vector<int> GeneratingTheoreticalSpectrum(vector<int> ppt)
{
	int sizeres = ppt.size()*(ppt.size() - 1) + 2;
	vector<int> res;	
	res.resize(sizeres);
	vector<int> pt=ppt;
	pt.resize (2 * pt.size());

	for (int i = ppt.size(); i < pt.size(); i++)
		pt[i] = pt[i-ppt.size()];

	for (int i = 0; i < sizeres; i++)
		res[i] = 0;	

	for (int i = 0; i < ppt.size(); i++)		
		res[1] += pt[i];
	
	int j = 2, m;

	for (int i = 0; i < ppt.size(); i++)
		for (int k = 1; k < ppt.size(); k++)
		{
			m = k;
			while (m > 0)
			{
				res[j] += pt[i+m-1];
				m--;
			}
			j++;
		}
	sort(res.rbegin(), res.rend(), isgreater<int,int>);

	return res;
}

int Score(vector<int>& pt, vector<int>& sp)				
{
	vector<int> spt = GeneratingTheoreticalSpectrum(pt);
	int i=0,j = 0,res=0;
	while (i < sp.size() && j < spt.size())
	{
		if (sp[i] < spt[j])
			i++;
		else if (sp[i] > spt[j])
			j++;
		else {
			i++; j++; res++;
		}
	}

	return res;
}

void LeaderPeptide(vector<vector<int>>& lb, vector<int>& spectrum) {

	vector<int> score;

	score.resize(lb.size());
	for (int i = 0; i < score.size(); i++)
		score[i] = 0;

	int j,temps;
	vector<int> temp;

	for (int i = 0; i < lb.size(); i++)
	{
		
		score[i] = Score(lb[i],spectrum);
		j = 0;
		while (j < i)
			if (score[i] <= score[j])
				j++;
			else
			{
				temp = lb[i];
				temps = score[i];
				for (int g = i; g > j; g--)
				{
					lb[g] = lb[g - 1];
					score[g] = score[g - 1];
				}
				lb[j] = temp;
				score[j] = temps;
			}
	}


}

void Trim(vector<vector<int>>& lb, vector<int>& spct, int n)
{
	int i = n;
	if (n < lb.size())
	{
		while (i<lb.size() && Score(lb[n-1], spct) == Score(lb[i], spct))
			i++;
		if(i!= lb.size())
		lb.erase(lb.begin() + i,lb.end());
	}
}

vector<int> LeaderboardCyclopeptideSequencing(int n, string sp)
{
	vector<vector<int>> leaderboard;
	vector<int> spectrum;           // Вектор спектра
									
	sp += ' ';   // Перевод строки со спектром в вектор
	int spsize = count(sp.begin(), sp.end(), ' ');	


	for (int i = 0; i < spsize; i++) {
		spectrum.push_back(stoi(sp.substr(0, sp.find(' '))));
		sp.erase(0, sp.find(' ') + 1);
	}
	vector<int> leaderpeptide;
	do
	{
		expand(leaderboard);
		LeaderPeptide(leaderboard, spectrum);
		int i = 0;
		while(i<leaderboard.size())
		{
			if (mas(leaderboard[i]) == spectrum[spsize - 1])
			{
				if (Score(leaderboard[i], spectrum) > Score(leaderpeptide, spectrum))
				{
					leaderpeptide = leaderboard[i];
				}
				leaderboard.erase(leaderboard.begin() + i);
			}
			else if (mas(leaderboard[i]) > spectrum[spsize - 1])
			{
				leaderboard.erase(leaderboard.begin() + i);
			}
			else
			i++;
		}
		Trim(leaderboard,spectrum,n);
	} while (leaderboard.size()!=0);

	return leaderpeptide;
}

int main() {
	//string str = "0 97 97 99 101 103 196 198 198 200 202 295 297 299 299 301 394 396 398 400 400 497";
		//"0 113 113 128 186 241 241 299 299 354 412 427 427 540";
	//"0 113 128 186 241 299 314 427";
	//getline(cin, str);
	//CyclopeptideSequencing(str);

	//string str = "NQEL", spec="0 99 113 114 128 227 257 299 355 356 370 371 484";
	//getline(cin, str);
	//getline(cin, spec);
	//cout << CyclopeptideScoring(str, spec)<<endl;

	//string str = "0 71 101 103 113 114 128 131 156 156 172 199 232 242 259 269 270 287 300 303 313 372 372 373 388 398 400 414 431 459 469 486 501 501 503 528 545 570 572 572 587 604 614 642 659 673 675 685 700 701 701 760 770 773 786 803 804 814 831 841 857 874 901 917 917 942 945 959 960 970 972 1002 1073";
	//int n=9;
	//vector<int> res = LeaderboardCyclopeptideSequencing(n,str);
	//for (int i = 0; i < res.size() - 1; i++)
	//	cout << res[i] << "-";
	//cout << res[res.size() - 1];

	system("pause");
	return 0;
}
