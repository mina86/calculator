#include <stdlib.h>

#include <iostream>
#include <fstream>


#if 1
#  if __GNUC__
	__extension__
#  endif
	typedef long double real;
#else
	typedef double real;
#endif


static inline real abs(real x) {
	return x < 0 ? -x : x;
}


static inline bool differ(real v1, real v2, real pct) {
	/* If both v1 and v2 are *very* small it's likelly that due to
	   rounding they will differ so ignore such situations. */
	return (v1 >= 1e-10 || v2 >= 1e-10) && abs((v1 - v2) / v1) >= pct;
}


int main(int argc, char *argv[]) {
	real pct = 0.1;
	if (argc < 3) {
		std::cout << "usage: " << argv[0] << " <file1> <file2> [<pct>]\n"
			"  pct - difference (in %) allowed in compared values";
		return 0;
	}
	if (argc >= 4) {
		pct = strtod(argv[3], 0);
	}

	std::ifstream file1(argv[1]), file2(argv[2]);

	bool foundDiff = false;
	unsigned lineCount = 0;
	real var1, var2;
	while (file1 >> var1 && file2 >> var2) {
		++lineCount;
		if (differ(var1, var2, pct)) {
			std::cout << lineCount << ": found difference (" << var1
			          << " - " << var2 << " = " << (var1 - var2) << ")\n";
			foundDiff = true;
		}
	}

	return foundDiff;
}

