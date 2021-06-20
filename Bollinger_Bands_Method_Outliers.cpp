#include <bits/stdc++.h>
using namespace std;

#define N 10000 // Total Number of points in textfile.txt, dont change it!

float *get_my_file() // Function to read textfile.txt
{
	float *a;
	a = new float[N];
	fstream newfile;
	newfile.open("testfile.txt", ios::in);

	if (newfile.is_open())
	{
		string tp;
		int i = 0;
		while (getline(newfile, tp))
		{
			a[i] = stof(tp);
			i++;
		}
		newfile.close();
	}
	else
	{
		cout << "File not read!!\n";
	}

	return a;
}
float findMean(vector<float> v, int n)
{
	float s = 0;
	for (int i = n-50; i < n; i++)
	{
		s += v[i];
	}
	return float(s / 50);
}
float findStd(vector<float> v, int n)
{
	float m = findMean(v, n);
	float s = 0;
	for (int i=n-50 ; i < n; i++)
	{
		s += (v[i] - m) * (v[i] - m);
	}
	s = s / (49);
	s = sqrt(s);
	return s;
}
int main()
{
	float *input = get_my_file();
	// Uncomment the code below to check if the file is successfully printed to the console
	auto temp = input;

	vector<float> value;
	for (int i = 0; i < N; i++)
	{
		// cout<<*temp<<endl;
		value.push_back(*temp);

		temp++;
	}
	float mean[10000];
	float sd[10000];
	vector<int> anomalyindex;
	vector<float> anomalyvalue;
	int k = 0;
	for (int i = 50; i < value.size(); i++)
	{
		mean[i] = findMean(value, i);
		sd[i] = findStd(value, i);
		if((value[i]>mean[i]+(5*sd[i])) || (value[i]<mean[i]-(5*sd[i])))
		{
			anomalyindex.push_back(i + 1);
			anomalyvalue.push_back(value[i]);
			// auto it=lower_bound(value.begin(),value.end(),value[i]);
            // value.erase(it);
			// value.erase(value.begin() + i);
			k++;
		}
	}
	cout << "Outlier values with Index " << endl
		 << "Index\t\t"
		 << "Value" << endl;
	for (int i = 0; i < k; i++)
	{
		cout << anomalyindex[i] << "\t\t" << anomalyvalue[i] << endl;
	}
}