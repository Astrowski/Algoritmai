#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// structure to represent a vertex
struct Virsunes
{
    int spalva; // virsunes spalva
    vector<int> neighbors; // pazymi virsunes kaimyne
};

// function to generate a random graph
void generuok(vector<Virsunes>& virsune, int n, int m)
{
    // skaiciu generavimas (pasitelkta interneto pagalba)
    mt19937 rng(random_device{}());
    uniform_real_distribution<double> dist(0.0, 1.0);

    virsune.resize(n);
    for (int i = 0; i < n; i++)
    {
        virsune[i].spalva = -1;
        virsune[i].neighbors.clear();
    }

    // add random edges
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (dist(rng) < (double)m / (n * (n - 1) / 2))
            {
                virsune[i].neighbors.push_back(j);
                virsune[j].neighbors.push_back(i);
            }
        }
    }
}

bool spalvink(vector<Virsunes>& virsune)
{
    // virsuniu spalvinimas po viena
    for (int i = 0; i < virsune.size(); i++)
    {
        // pirmos pasitaikiusios spalvos 
        for (int c = 0; c < virsune.size(); c++)
        {
            bool available = true; // tikrinam ar spalva yra galima
            for (int j : virsune[i].neighbors) // tikrinam virsunes kaimynus
            {
                if (virsune[j].spalva == c) // jeigu spalva yra priskirta kaimynui, spalvos nebegalim naudoti
                {
                    available = false;
                    break;
                }
            }
            if (available)
            {
                virsune[i].spalva = c;
                break;
            }
        }
    }

    return true;
}

int main()
{
    string apskritys[] =
    {
          "Kauno", "Vilniaus", "Alytaus", "Marijampoles", "Taurages", "Siauliu", "Panevezio", "Telsiu", "Klaipedos", "Utenos"
    };
    vector<Virsunes> virsune = {
        {-1, {1, 2, 3, 4, 5, 6}},
        {-1, {0, 2, 9}},
        {-1, {0, 1, 3}},
        {-1, {0, 2, 4}},
        {-1, {0, 3, 5, 7, 8}},
        {-1, {0, 4, 6, 7}},
        {-1, {0, 5, 9}},
        {-1, {4, 8, 5}},
        {-1, {4, 7}},
        {-1, {1, 6}}
    };

    // get the input method from the user
    cout << "Generuoti briaunas? (y/n): ";
    char method;
    cin >> method;

    if (method == 'n')
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        if (spalvink(virsune))
        {
            for (int i = 0; i < virsune.size(); i++)
            {
                cout << apskritys[i] << " apskrities" << " spalva: " << virsune[i].spalva << endl;
            }
        }
        std::cout << "Spalvu priskyrimas uztruko: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() / 1000. << " s." << std::endl;
    
    }
    else if (method == 'y')
    {
        cout << "Iveskite virsuniu skaiciu: ";
        int n;
        cin >> n;
        cout << "Iveskite briaunu skaiciu: ";
        int m;
        cin >> m;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        generuok(virsune, n, m);
        if (spalvink(virsune))
        {
            for (int i = 0; i < virsune.size(); i++)
            {
                cout << "Virsunes " << i << ": spalva " << virsune[i].spalva << endl;
            }
        }
        std::cout << ": "
            << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() / 1000. << " s." << std::endl;
    
    }
    else
    {
        cout << "Bolgas ivedimas" << endl;
        return 1;
    }
    int sk = -1;
    for (int i = 0; i < virsune.size(); i++)
    {
        sk = max(sk, virsune[i].spalva);
    }

    cout << "Panaudotu spalvu skaiciu: " << sk + 1 << endl;
   

   

    return 0;
}