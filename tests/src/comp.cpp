#include <stdlib.h>

#include <iostream>
#include <fstream>

using namespace std;

static inline double abs(double x) {
	return x < 0 ? -x : x;
}

static inline bool compare(double v1, double v2, double pct) {
	return abs((v1 - v2) / v1) > pct;
}

int main(int argc, char *argv[])
{
	double pct = 0.1;
	if(argc < 3)
	{
		cout << "usage: ./comp file1 file2 [pct]\n"
			"pct - difference (in %) allowed in compared values";
		return 0;
	}
	if(argc >= 4)
	{
	    pct = strtod(argv[3], 0);
	}

	ifstream file1(argv[1]);
	ifstream file2(argv[2]);

	cout << fixed;

	bool foundDiff = false;
	int lineCount = 0;
	double var1, var2;
	while (file1 >> var1 && file2 >> var2) {
		++lineCount;
		if(compare(var1, var2, pct))
		{
			cerr << "Found difference at line: " << lineCount
			     << " values: " << var1 << " != " << var2
			     << " Diff: " << var1-var2 << endl;
			foundDiff = true;
		}
	}

	return foundDiff;
}

