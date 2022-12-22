#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std::chrono;
using namespace std;


struct Virsunes
{
    int spalva; 
};

// function to generate a random graph
void generuok(vector<Virsunes>& virsune, vector<vector<int>>& matrica, int n, int m)
{
    // matricos generavimas (pasitelkta interneto pagalba)
    mt19937 rng(random_device{}());
    uniform_real_distribution<double> dist(0.0, 1.0);


    virsune.resize(n);
    for (int i = 0; i < n; i++)
    {
        virsune[i].spalva = -1; 
    }

    matrica.resize(n);
    for (int i = 0; i < n; i++)
    {
        matrica[i].resize(n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist(rng) < (double)m / (n * (n - 1) / 2))
            {
                matrica[i][j] = 1;
                matrica[j][i] = 1;
            }
            else
            {
                matrica[i][j] = 0;
                matrica[j][i] = 0;
            }
        }
    }
}

// tikrinam, ar spalva yra galima
bool tikrink(vector<Virsunes>& virsune, vector<vector<int>>& matrica, int V, int spalva)
{
    // tikrinam, ar kaimynai yra su ta pacia spalva
    for (int i = 0; i < virsune.size(); i++)
    {
        if (matrica[V][i] == 1 && virsune[i].spalva == spalva)
        {
            return false;
        }
    }

    return true;
}

// spalvos priskyrimas naudojant grizimo atgal algoritma
bool spalvink(vector<Virsunes>& virsune, vector<vector<int>>& matrica, int V)
{
    // visoms virsunems priskiriamos spalvos
    if (V == virsune.size())
    {
        return true;
    }

    for (int c = 0; c < virsune.size(); c++)
    {
        if (tikrink(virsune, matrica, V, c))
        {
            // priskiria spalva ir naudoja rekursija
            virsune[V].spalva = c;
            if (spalvink(virsune, matrica, V + 1))
            {
                return true;
            }

            // grizimas atgal: virsunes spalvos panaikinimas
            virsune[V].spalva = -1;
        }
    }

    return false;
}
int main()
{
    vector<Virsunes> virsune;
    vector<vector<int>> matrica;

    cout << "Generuoti atsitiktine matrica? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y')
    {
        int n, m;
        cout << "Iveskite virsuniu skaiciu: ";
        cin >> n;
        cout << "Iveskite briaunu skaiciu: ";
        cin >> m;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        generuok(virsune, matrica, n, m);
    }
    else
    {
        virsune = {
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
            {-1},
        };

        matrica = {
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
            { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            { 1, 0, 0, 1, 0, 1, 0, 1, 1, 0},
            { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
            { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        };
    }

    if (spalvink(virsune, matrica, 0))
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        cout << "Nuspalvintos virsunes: " << endl;
        for (int i = 0; i < virsune.size(); i++)
        {
            cout << "Virsunes " << i+1 << " spalva: " << virsune[i].spalva + 1 << endl;
        }
        std::cout << "Spalvu priskyrimas uztruko: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() / 1000. << " s." << std::endl;

    }
    else
    {
        cout << "Nera galimu spalvu!" << endl;
    }
    int sk = -1;
    for (int i = 0; i < virsune.size(); i++)
    {
        sk = max(sk, virsune[i].spalva);
    }

    cout << "Panaudotu spalvu skaicius: " << sk + 1 << endl;

    return 0;
}