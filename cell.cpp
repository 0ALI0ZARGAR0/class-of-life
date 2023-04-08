#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
string complementary(string a);
string reverseStr(string s, int a, int b);
string replaceStr(int pos1, int len1, string s, int pos2, int len2);
class genome
{
public:
    string RNA, DNA[2];
    genome(string rna, string dna1, string dna2)
    {
        RNA = rna;
        DNA[0] = dna1;
        DNA[1] = dna2;
    }
    void smallMutation(string A, string C, int n);
    void greatMutation(string S1, string S2);
    void reverseMutation(string S1);
    void createDNA() { cout << complementary(RNA) << endl; }
};

class cell : genome
{
    vector<genome> chromosome;
    cell(string rna, string dna1, string dna2) : genome(NULL, NULL, NULL) // since a cell is not a genome but it has to inherit, those properties have to be empty
    {
        genome gen = genome(rna, dna1, dna2);
        chromosome.push_back(gen);
    }
    void addGenome(genome gen)
    {
        chromosome.push_back(gen);
    }
    void smallMutation(string A, string C, int n, int m);
    void greatMutation(string S1, int n, string S2, int m);
    void reverseMutation(string S1, int n);
    void palindrome();
    void death();
};

int main()
{

    return 0;
}

// functions:
string complementary(string a)
{
    string m = "";
    for (int i = 0; i < a.length(); i++)
    {
        switch (a[i])
        {

        case 'A':

            m += 'T';
            break;

        case 'T':

            m += 'A';
            break;

        case 'C':

            m += 'G';
            break;

        case 'G':

            m += 'C';
            break;
        }
    }
    return m;
}
string reverseStr(string s, int a, int b)
{
    string rev = "";
    for (int i = 0; i < a; i++)
    {
        rev += s[i];
    }
    for (int i = b; i >= a; i--)
    {
        rev += s[i];
    }
    for (int i = b + 1; i < s.length(); i++)
    {
        rev += s[i];
    }
    return rev;
}
string replaceStr(string main, int pos1, int len1, string insert, int pos2 = 0, int len2 = -1)
{
    string newStr;
    if (len2 == -1)
    {
        len2 = insert.length();
    }

    for (int i = 0; i < pos1; i++)
    {
        newStr += main[i];
    }
    for (int i = pos2; i < pos2 + len2; i++)
    {
        newStr += insert[i];
    }
    for (int i = pos1 + len1; i < main.length(); i++)
    {
        newStr += main[i];
    }
    return newStr;
};

// genome class functions:
void genome::smallMutation(string A, string C, int n)
{
    for (int i = 0; i < n; i++)
    {

        if (DNA[0].find(A) < DNA[1].find(A))
        {
            int p = DNA[0].find(A);
            DNA[0] = replaceStr(DNA[0], p, A.length(), C);
            DNA[1] = replaceStr(DNA[1], p, A.length(), complementary(C));
        }
        else
        {
            int p = DNA[1].find(A);
            DNA[0] = replaceStr(DNA[0], p, A.length(), C);
            DNA[1] = replaceStr(DNA[1], p, A.length(), complementary(C));
        }
    }
}
void genome::greatMutation(string S1, string S2)
{
    if (DNA[0].find(S1) < DNA[1].find(S1))
    {
        int p1 = DNA[0].find(S1);
        int p2 = DNA[0].find(S2);
        string temp = DNA[0].substr(p1, S1.length());
        DNA[0] = replaceStr(DNA[0], p1, S1.length(), DNA[0], p2, S2.length());
        DNA[0] = replaceStr(DNA[0], p2, S2.length(), temp);
        temp = DNA[1].substr(p1, S1.length());
        DNA[1] = replaceStr(DNA[1], p1, S1.length(), DNA[1], p2, S2.length());
        DNA[1] = replaceStr(DNA[1], p2, S2.length(), temp);
    }
    else
    {
        int p1 = DNA[1].find(S1);
        int p2 = DNA[1].find(S2);
        string temp = DNA[1].substr(p1, S1.length());
        DNA[1] = replaceStr(DNA[1], p1, S1.length(), DNA[1], p2, S2.length());
        DNA[1] = replaceStr(DNA[1], p2, S2.length(), temp);
        temp = DNA[0].substr(p1, S1.length());
        DNA[0] = replaceStr(DNA[0], p1, S1.length(), DNA[0], p2, S2.length());
        DNA[0] = replaceStr(DNA[0], p2, S2.length(), temp);
    }
}
void genome::reverseMutation(string S1)
{
    if (DNA[0].find(S1) < DNA[1].find(S1))
    {
        int p = DNA[0].find(S1);
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    else
    {
        int p = DNA[1].find(S1);
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    int p = RNA.find(S1);
    RNA = reverseStr(RNA, p, p + S1.length());
    RNA = reverseStr(RNA, p, p + S1.length());
}

// cell functions:
void cell::smallMutation(string A, string C, int n, int m)
{
    for (int i = 0; i < n; i++)
    {

        if (chromosome[m].DNA[0].find(A) < chromosome[m].DNA[1].find(A))
        {
            int p = chromosome[m].DNA[0].find(A);
            chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p, A.length(), C);
            chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p, A.length(), complementary(C));
        }
        else
        {
            int p = chromosome[m].DNA[1].find(A);
            chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p, A.length(), C);
            chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p, A.length(), complementary(C));
        }
    }
}
void cell::greatMutation(string S1, int n, string S2, int m)
{
    if (chromosome[n].DNA[0].find(S1) < chromosome[n].DNA[1].find(S1))
    {
        int p1 = chromosome[n].DNA[0].find(S1);
        int p2 = chromosome[m].DNA[0].find(S2);
        string temp = chromosome[n].DNA[0].substr(p1, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], p1, S1.length(), chromosome[m].DNA[0], p2, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p2, S2.length(), temp);
        temp = chromosome[n].DNA[1].substr(p1, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], p1, S1.length(), chromosome[m].DNA[1], p2, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p2, S2.length(), temp);
    }
    else
    {
        int p1 = chromosome[n].DNA[1].find(S1);
        int p2 = chromosome[m].DNA[1].find(S2);
        string temp = chromosome[n].DNA[1].substr(p1, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], p1, S1.length(), chromosome[m].DNA[1], p2, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p2, S2.length(), temp);
        temp = chromosome[n].DNA[0].substr(p1, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], p1, S1.length(), chromosome[m].DNA[0], p2, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p2, S2.length(), temp);
    }
}
void cell::reverseMutation(string S1, int n)
{
    if (chromosome[n].DNA[0].find(S1) < chromosome[n].DNA[1].find(S1))
    {
        int p = chromosome[n].DNA[0].find(S1);
        chromosome[n].DNA[0] = reverseStr(chromosome[n].DNA[0], p, p + S1.length());
        chromosome[n].DNA[1] = reverseStr(chromosome[n].DNA[1], p, p + S1.length());
    }
    else
    {
        int p = chromosome[n].DNA[1].find(S1);
        chromosome[n].DNA[0] = reverseStr(chromosome[n].DNA[0], p, p + S1.length());
        chromosome[n].DNA[1] = reverseStr(chromosome[n].DNA[1], p, p + S1.length());
    }
}
void cell::palindrome()
{
    for (int i = 2; i <= DNA[0].length() / 2; i++)
    {
        for (int j = 0; j < DNA[0].length() - 2 * i; j++)
        {
            string temp = DNA[0].substr(j, i);
            reverse(temp.begin(), temp.end());
            if (complementary(temp) == DNA[0].substr(j + i, i))
            {
                cout << DNA[0].substr(j, 2 * i) << endl;
            }
        }
    }
}
void cell::death()
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
            // del
        }
    }
}