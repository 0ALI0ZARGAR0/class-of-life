#include <iostream>
#include <vector>
#include <cstdlib>
#include "cell.h"
#include <set>
#include <math.h>
using namespace std;

class Animal : public cell
{
public:
    Animal(){}
    Animal(vector<genome> r){
        chromosome = r;
    }
    bool health = true;
    double Genetic_similarity(Animal animal1)
    {
        double sum2 = 0;
        for (int j = 0; j < min(chromosome.size(), animal1.chromosome.size()); j++)
        {
            int sum = 0;
            int l1 = chromosome[j].DNA[0].length();
            int l2 = animal1.chromosome[j].DNA[0].length();
            for (int i = 0; i < min(l1, l2); i++)
            {
                if (chromosome[j].DNA[0][i] != animal1.chromosome[j].DNA[0][i])
                {
                    sum += 1;
                }
            }
            sum += abs(l2 - l1);
            sum2 += 100 - (sum / max(l1, l2)) * 100;
        }
        return double(sum2 / min(chromosome.size(), animal1.chromosome.size()));
    }
    bool operator==(Animal animal1)
    {
        if (Genetic_similarity(animal1) >= 70)
            return true;
        return false;
    }
    Animal asexual()
    {
        int n = chromosome.size();
        set<int> fixed;
        Animal New_animal;
        while (fixed.size() <= ceil(0.7 * n))
        {
            fixed.insert(rand() % (n + 1));
        }
        for (int i = 0; i < n; i++)
        {
            if (fixed.count(i))
            {
                New_animal.addGenome(chromosome[i]);
            }
            else
            {
                New_animal.addGenome(chromosome[rand() % (n + 1)]);
            }
        }
        return New_animal;
    }
    Animal operator+(Animal animal2)
    {
        // if (chromosome.size() % 2 == 1 and animal2.chromosome.size() % 2 == 1)
        // {
        //     cout << "error!\n";
        //     return;
        // }
        Animal asexual1 = asexual();
        Animal asexual2 = animal2.asexual();
        int n = asexual1.chromosome.size();
        int m = asexual2.chromosome.size();
        Animal New_animal;
        set<int> set11, set12, set21, set22;
        for (int i = 0; i < 500; i++)
        {
            while (set11.size() == n / 2)
            {
                set11.insert(rand() % (n + 1));
            }
            while (set12.size() == n / 2)
            {
                set12.insert(rand() % (n + 1));
            }
            while (set22.size() == m / 2)
            {
                set22.insert(rand() % (m + 1));
            }
            while (set21.size() == m / 2)
            {
                set21.insert(rand() % (m + 1));
            }
            for (int i = 0; i < n / 2; i++)
            {
                New_animal.addGenome(asexual1.chromosome[i]);
            }
            for (int i = 0; i < m; i++)
            {
                New_animal.addGenome(asexual2.chromosome[i]);
            }
            if (Genetic_similarity(New_animal) >= 70 and animal2.Genetic_similarity(New_animal) >= 70)
            {
                return New_animal;
            }
        }
    }
    void death()
    {
        for (int j = 0; j < chromosome.size(); j++)
        {
            int n = 0, at = 0, cg = 0;
            for (int i = 0; i < chromosome[j].DNA[0].length(); i++)
            {
                string x = string(1, chromosome[j].DNA[1][i]);
                if (x != complementary(string(1, chromosome[j].DNA[0][i])))
                {
                    n++;
                }
                if (chromosome[j].DNA[0][i] == 'A' or chromosome[j].DNA[0][i] == 'T')
                {
                    at++;
                }
                else
                {
                    cg++;
                }
            }
            if (n >= 5 or at >= 3 * cg)
            {
                // delete chromosome[j];
                cout << "Your chromosome" << j + 1 << " died\n";
                return;
            }
        }
    }
    friend class virus;
};

int main()
{
    return 0;
}
string biggestCommonSubstr(Animal animal)
{
    int n = animal.chromosome.size();

    // Takes first DNA from array as reference
    string s = animal.chromosome[0].DNA[0];
    int len = s.length();

    string ans = "";

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j <= len; j++)
        {
            // creating every possible substrings
            string sub = s.substr(i, j);
            int k = 1;
            for (k = 1; k < n; k++)
            {
                // checks if the generated string(sub) is in common to all DNAs
                if (findSubstr(animal.chromosome[k].DNA[0], sub) == -1)
                    break;
            }
            if (j == len - 2)
            {
                //
            }
            if (k == n && ans.length() < sub.length())
                ans = sub;
        }
    }

    return ans;
}
class virus : public genome
{
public:
    virus(string rna) : genome(rna, "", "") {}
    void harm(Animal &animal)
    {
        string bcs = biggestCommonSubstr(animal);
        if (RNA.find(bcs) != -1 or RNA.find(complementary(bcs)) != -1)
        {
            animal.health = false;
            cout << "the virus and animal had \"" << bcs << "\" in common\n"
                 << "harm applied to your animal\n";
        }
    }
};
