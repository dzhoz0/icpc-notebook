#include <bits/stdc++.h>
using namespace std;
const string NAME = "template";
const int NTEST = 100;

static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rando(l, r) uniform_int_distribution<int> (l, r)(rng)

void sinh(){
    ofstream fout("inp.txt");
    fout << rando(1, 8) << '\n';
    fout.close();
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        sinh();

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
    cout << "Cubu\n";
    return 0;
}
