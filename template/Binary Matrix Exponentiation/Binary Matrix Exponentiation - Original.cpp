/*
    Template created by Alexandru Olteanu {AlexandruINV}
*/
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Binary%20Matrix%20Exponentiation/Binary%20Matrix%20Exponentiation%20-%20Original.cpp
const ll matrix_mod = 1e9 + 7;

template<typename T>
vector<vector<T> > mul(vector<vector<T> > a, vector<vector<T> > b)
{
	vector<vector<T> > res;
	res = a;
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res.size(); j++)
		{
			res[i][j] = 0;
		}
	}
	for (int k = 0; k < res.size(); k++)
	{
		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res.size(); j++)
			{
				res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % matrix_mod;
			}
		}
	}
	return res;
}

template<typename T>
vector<vector<T> > matrix_power(vector<vector<T> > a, long long b)
{
	if (b == 1)
		return a;
	if (b == 0)
	{
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < a.size(); j++)
			{
				a[i][j] = (i == j);
			}
		}
		return a;
	}
 
	if (b % 2)
		return mul(a, matrix_power(a, b - 1));
	return matrix_power(mul(a,a), b / 2);
}
