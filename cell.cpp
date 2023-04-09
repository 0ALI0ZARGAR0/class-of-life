#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
string complementary(string a);
string reverseStr(string s, int a, int b);
string replaceStr(int pos1, int len1, string s, int pos2, int len2);
int findSubstr(string main, string find);
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
int findSubstr(string main, string find)
{
    bool similar = true;
    int i;
    for (i = 0; i <= main.length() - find.length(); i++)
    {
        similar = true;
        for (int j = 0; j < find.length(); j++)
        {
            if (main[i + j] != find[j])
            {
                similar = false;
                break;
            }
        }
        if (similar)
        {
            break;
        }
    }
    if (similar)
        return i;
    else
        return -1;
}

// genome class functions:
void genome::smallMutation(string A, string C, int n)
{
    for (int i = 0; i < n; i++)
    {

        if (findSubstr(DNA[0], A) < findSubstr(DNA[1], A))
        {
            int p = findSubstr(DNA[0], A);
            DNA[0] = replaceStr(DNA[0], p, A.length(), C);
            DNA[1] = replaceStr(DNA[1], p, A.length(), complementary(C));
        }
        else
        {
            int p = findSubstr(DNA[1], A);
            DNA[0] = replaceStr(DNA[0], p, A.length(), C);
            DNA[1] = replaceStr(DNA[1], p, A.length(), complementary(C));
        }
    }
}
void genome::greatMutation(string S1, string S2)
{
    if (findSubstr(DNA[0], S1) < findSubstr(DNA[1], S1))
    {
        int p1 = findSubstr(DNA[0], S1);
        int p2 = findSubstr(DNA[0], S2);
        string temp = DNA[0].substr(p1, S1.length());
        DNA[0] = replaceStr(DNA[0], p1, S1.length(), DNA[0], p2, S2.length());
        DNA[0] = replaceStr(DNA[0], p2, S2.length(), temp);
        temp = DNA[1].substr(p1, S1.length());
        DNA[1] = replaceStr(DNA[1], p1, S1.length(), DNA[1], p2, S2.length());
        DNA[1] = replaceStr(DNA[1], p2, S2.length(), temp);
    }
    else
    {
        int p1 = findSubstr(DNA[1], S1);
        int p2 = findSubstr(DNA[1], S2);
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
    if (findSubstr(DNA[0], S1) < findSubstr(DNA[1], S1))
    {
        int p = findSubstr(DNA[0], S1);
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    else
    {
        int p = findSubstr(DNA[1], S1);
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    int p = findSubstr(RNA, S1);
    RNA = reverseStr(RNA, p, p + S1.length());
    RNA = reverseStr(RNA, p, p + S1.length());
}

// cell functions:
void cell::smallMutation(string A, string C, int n, int m)
{
    for (int i = 0; i < n; i++)
    {

        if (findSubstr(chromosome[m].DNA[0], A) < findSubstr(chromosome[m].DNA[1], A))
        {
            int p = findSubstr(chromosome[m].DNA[0], A);
            chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p, A.length(), C);
            chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p, A.length(), complementary(C));
        }
        else
        {
            int p = findSubstr(chromosome[m].DNA[1], A);
            chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p, A.length(), C);
            chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p, A.length(), complementary(C));
        }
    }
}
void cell::greatMutation(string S1, int n, string S2, int m)
{
    if (findSubstr(chromosome[n].DNA[0], S1) < findSubstr(chromosome[n].DNA[1], S1))
    {
        int p1 = findSubstr(chromosome[n].DNA[0], S1);
        int p2 = findSubstr(chromosome[m].DNA[0], S2);
        string temp = chromosome[n].DNA[0].substr(p1, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], p1, S1.length(), chromosome[m].DNA[0], p2, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], p2, S2.length(), temp);
        temp = chromosome[n].DNA[1].substr(p1, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], p1, S1.length(), chromosome[m].DNA[1], p2, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], p2, S2.length(), temp);
    }
    else
    {
        int p1 = findSubstr(chromosome[n].DNA[1], S1);
        int p2 = findSubstr(chromosome[m].DNA[1], S2);
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
    if (findSubstr(chromosome[n].DNA[0], S1) < findSubstr(chromosome[n].DNA[1], S1))
    {
        int p = findSubstr(chromosome[n].DNA[0], S1);
        chromosome[n].DNA[0] = reverseStr(chromosome[n].DNA[0], p, p + S1.length());
        chromosome[n].DNA[1] = reverseStr(chromosome[n].DNA[1], p, p + S1.length());
    }
    else
    {
        int p = findSubstr(chromosome[n].DNA[1], S1);
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
