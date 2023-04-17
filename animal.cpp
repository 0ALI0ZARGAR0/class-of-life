#include <iostream>
#include <vector>
#include <cstdlib>
#include "cell.h"
#include <set>
using namespace std;

class Animal : public cell // animal inherits from cell and contains a series of cells
{
public:
    bool health = true; // indicates the animal health infected with a virus

    double Genetic_similarity(Animal animal1) // an algorithm which determine the similarity of two animal
                                              // based on their chromosomes number and chromosomes data
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

    bool operator==(Animal animal1) // indicates if two animal are of a same kind
    {
        if (Genetic_similarity(animal1) >= 70)
            return true;
        return false;
    }

    Animal asexual() // creates another animal
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

    Animal operator+(Animal animal2) // creates another animal
    {
        if (chromosome.size() % 2 == 0 and animal2.chromosome.size() % 2 == 0)
        {
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
    }

    void death() // this may result in an animal genome deletion if certain conditions be met
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

    void printf() // prints whole data of the animal
    {
        cout << "your animal chromosomes are:\n";
        for (int i = 0; i < chromosome.size(); i++)
        {
            cout << "Your chromosome" << i + 1 << "'s DNA is: " << chromosome[i].DNA[0] << " | " << chromosome[i].DNA[1] << endl;
        }
    }

    friend class virus; // virus needs access to animal data
};

string biggestCommonSubstr(Animal animal) // finds the biggest common series of nucleotides in an animal's genomes
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
            if (k == n && ans.length() < sub.length())
            {
                ans = sub;
            }
        }
    }

    return ans;
}
class virus : public genome // virus will harm the inflicted animal if it contains
                            // the biggest common sub nucleotides of the animal genomes
{
public:
    virus(string rna) : genome(rna, "", "") {}
    void harm(Animal &animal)
    {
        string bcs = biggestCommonSubstr(animal);
        if (findSubstr(RNA, bcs) != -1 or findSubstr(RNA, complementary(bcs)) != -1)
        {
            animal.health = false;
            cout << "the virus and animal had \"" << bcs << "\" in common\n"
                 << "harm applied to your animal\n";
            return;
        }
        cout << "harm did not apply";
    }
    void print() // prints virus RNA
    {
        cout << "your virus RNA: " << RNA << endl;
    };
};

int main()
{

    return 0;
}