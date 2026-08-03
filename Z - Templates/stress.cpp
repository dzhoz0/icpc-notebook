#include <bits/stdc++.h>
using namespace std;
const string NAME = "template";
const int NTEST = 100;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd


long long Rand(long long L, long long R) {
    assert(L <= R);
    return L + rd() % (R - L + 1);
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        // Test gen code here
        inp.close();

        // Change to "./" for Linux
        system((NAME + ".exe").c_str());
        system((NAME + "_trau.exe").c_str());

        // Use diff instead of fc for Linux
        if (system(("fc " + NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
