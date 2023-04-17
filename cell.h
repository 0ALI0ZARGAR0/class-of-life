#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <string>

using namespace std;
string complementary(string a);                                      // creates the complementary series of nucleotides
string reverseStr(string s, int a, int b);                           // creates a string with reverse nucleotides of between indexes
string replaceStr(int pos1, int len1, string s, int pos2, int len2); // replace a substring of an string with a substring of another
int findSubstr(string main, string find);                            // finds the starting index of a pattern in an string

class genome // It's our genome class which contains two DNA,
             // an RNA (each are a series of nucleotide) and few functionalities
{
public:
    string RNA, DNA[2];
    genome(string rna, string dna1, string dna2) // the constructor
    {
        RNA = rna;
        DNA[0] = dna1;
        DNA[1] = dna2;
    }
    // each function will be performed both on DNA and RNA
    void smallMutation(string A, string C, int n); // replaces nucleotide A with nucleotide C for n times
    void greatMutation(string S1, string S2);      // replaces the first series of nucleotides A with nucleotides C
    void reverseMutation(string S1);               // reverse the order of first series of nucleotides S1
    void createDNA()                               // prints the complementary version of RNA (known as how DNA should be)
    {
        cout << RNA << " | " << complementary(RNA) << endl;
    }
    void print() // prints cell data
    {
        cout << "RNA: " << RNA << endl
             << "DNA: " << DNA[0] << " | "
             << DNA[1] << endl;
    }
};

class cell : public genome // our cell class inherits from genome class and contains a series of genomes
{
public:
    vector<genome> chromosome;
    cell() : genome("", "", "") // since a cell is not a genome but it has to inherit,
                                // those properties have to be empty
    {
    }
    void addGenome(genome gen) // adds genome to cell series of genomes
    {
        gen.RNA = "";
        chromosome.push_back(gen);
    }
    void smallMutation(string A, string C, int n, int m);   // replaces nucleotide A with nucleotide C for n times in genome m
    void greatMutation(string S1, int n, string S2, int m); // replaces the first series of nucleotides S1 from genome n with nucleotides S2 from genome m
    void reverseMutation(string S1, int n);                 // reverse the order of first series of nucleotides S1 from genome n
    void palindrome(int n);                                 // prints the existing palindromes of genome n DNA
    void death();                                           // this may result in cell deletion if certain conditions be met
    void print(int n)                                       // prints the genome n data
    {
        cout << "Your chromosome" << n + 1 << "'s DNA is: " << chromosome[n].DNA[0] << " | " << chromosome[n].DNA[1] << endl;
    }
    void printf() // prints whole data of the cell
    {
        cout << "your cell chromosomes are:\n";
        for (int i = 0; i < chromosome.size(); i++)
        {
            cout << "Your chromosome" << i + 1 << "'s DNA is: " << chromosome[i].DNA[0] << " | " << chromosome[i].DNA[1] << endl;
        }
    }
};

// main functions:
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
    for (int i = b - 1; i >= a; i--)
    {
        rev += s[i];
    }
    for (int i = b; i < s.length(); i++)
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
    // simple search:
    // bool similar = true;
    // int i;
    // for (i = 0; i <= main.length() - find.length(); i++)
    // {
    //     similar = true;
    //     for (int j = 0; j < find.length(); j++)
    //     {
    //         if (main[i + j] != find[j])
    //         {
    //             similar = false;
    //             break;
    //         }
    //     }
    //     if (similar)
    //     {
    //         break;
    //     }
    // }
    // if (similar)
    //     return i;
    // else
    //     return -1;

    // KMP algorithm
    int M = find.length();
    int N = main.length();
    int lps[M];

    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M)
    {
        if (find[i] == find[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;     // main index
    int j = 0; // find index
    while ((N - i) >= (M - j))
    {
        if (find[j] == main[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            return i - j;
            j = lps[j - 1];
        }
        else if (i < N && find[j] != main[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

// genome class functions:
void genome::smallMutation(string A, string C, int n)
{
    int j = n;
    for (int i = 0; i < DNA[0].length(); i++)
    {
        if (j == 0)
        {
            break;
        }
        if (string(1, DNA[0][i]) == A)
        {
            string(1, DNA[0][i]) = C;
            string(1, DNA[1][i]) = complementary(C);
            j--;
        }
        else if (string(1, DNA[1][i]) == A)
        {
            string(1, DNA[0][i]) = complementary(C);
            string(1, DNA[1][i]) = A;
            j--;
        }
    }
    j = n;
    for (int i = 0; i < RNA.length(); i++)
    {
        if (j == 0)
        {
            break;
        }
        if (string(1, RNA[i]) == A)
        {
            string(1, RNA[i]) = C;
            j--;
        }
    }
}
void genome::greatMutation(string S1, string S2)
{
    int posInDNA0 = findSubstr(DNA[0], S1);
    int posInDNA1 = findSubstr(DNA[1], S1);
    if (posInDNA0 == -1 and posInDNA1 == -1)
    {
        cout << "This DNA doesn't have string \"" << S1 << "\"\n";
    }
    else if ((posInDNA0 < posInDNA1 or posInDNA1 == -1) and posInDNA0 != -1)
    {
        DNA[0] = replaceStr(DNA[0], posInDNA0, S1.length(), S2);
        DNA[1] = replaceStr(DNA[1], posInDNA0, S1.length(), complementary(S2));
    }
    else
    {
        DNA[1] = replaceStr(DNA[1], posInDNA1, S1.length(), S2);
        DNA[0] = replaceStr(DNA[0], posInDNA1, S1.length(), complementary(S2));
    }
    int posInRna = findSubstr(RNA, S1);
    if (posInRna != -1)
        RNA = replaceStr(RNA, posInRna, S1.length(), S2);
    else
        cout << "This RNA doesn't have string \"" << S1 << "\"\n";
}
void genome::reverseMutation(string S1)
{
    int pos0 = findSubstr(DNA[0], S1);
    int pos1 = findSubstr(DNA[1], S1);
    if ((pos0 < pos1 or pos1 == -1) and pos0 != -1)
    {
        int p = pos0;
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    else
    {
        int p = pos1;
        DNA[0] = reverseStr(DNA[0], p, p + S1.length());
        DNA[1] = reverseStr(DNA[1], p, p + S1.length());
    }
    int p = findSubstr(RNA, S1);
    RNA = reverseStr(RNA, p, p + S1.length());
}

// cell functions:
void cell::smallMutation(string A, string C, int j, int m)
{
    for (int i = 0; i < chromosome[m].DNA[0].length(); i++)
    {
        if (j == 0)
        {
            break;
        }
        if (string(1, chromosome[m].DNA[0][i]) == A)
        {
            string(1, chromosome[m].DNA[0][i]) = C;
            string(1, chromosome[m].DNA[1][i]) = complementary(C);
            j--;
        }
        else if (string(1, chromosome[m].DNA[1][i]) == A)
        {
            string(1, chromosome[m].DNA[0][i]) = complementary(C);
            string(1, chromosome[m].DNA[1][i]) = A;
            j--;
        }
    }
}
void cell::greatMutation(string S1, int n, string S2, int m)
{
    int pn0 = findSubstr(chromosome[n].DNA[0], S1);
    int pn1 = findSubstr(chromosome[n].DNA[1], S1);
    int pm0 = findSubstr(chromosome[m].DNA[0], S2);
    int pm1 = findSubstr(chromosome[m].DNA[1], S2);
    if ((pn0 == -1 and pn1 == -1))
    {
        cout << "DNA" << n << " doesn't have string \"" << S1 << "\"\n";
        return;
    }
    else if ((pm0 == -1 and pm1 == -1))
    {
        cout << "DNA" << m << " doesn't have string \"" << S2 << "\"\n";
        return;
    }
    else if (((pn0 < pn1 or pn1 == -1) and pn0 != -1) and ((pm0 < pm1 or pm1 == -1) and pm0 != -1))
    {
        string temp = chromosome[n].DNA[0].substr(pn0, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], pn0, S1.length(), chromosome[m].DNA[0], pm0, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], pm0, S2.length(), temp);
        temp = chromosome[n].DNA[1].substr(pn0, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], pn0, S1.length(), chromosome[m].DNA[1], pm0, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], pm0, S2.length(), temp);
        return;
    }
    else if (!((pn0 < pn1 or pn1 == -1) and pn0 != -1) and ((pm0 < pm1 or pm1 == -1) and pm0 != -1))
    {
        string temp = chromosome[n].DNA[1].substr(pn1, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], pn1, S1.length(), chromosome[m].DNA[0], pm0, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], pm0, S2.length(), temp);
        temp = chromosome[n].DNA[0].substr(pn1, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], pn1, S1.length(), chromosome[m].DNA[1], pm0, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], pm0, S2.length(), temp);
        return;
    }
    else if (((pn0 < pn1 or pn1 == -1) and pn0 != -1) and !((pm0 < pm1 or pm1 == -1) and pm0 != -1))
    {
        string temp = chromosome[n].DNA[0].substr(pn0, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], pn0, S1.length(), chromosome[m].DNA[1], pm1, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], pm1, S2.length(), temp);
        temp = chromosome[n].DNA[1].substr(pn0, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], pn0, S1.length(), chromosome[m].DNA[0], pm1, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], pm1, S2.length(), temp);
        return;
    }
    else if (!((pn0 < pn1 or pn1 == -1) and pn0 != -1) and !((pm0 < pm1 or pm1 == -1) and pm0 != -1))
    {
        string temp = chromosome[n].DNA[1].substr(pn1, S1.length());
        chromosome[n].DNA[1] = replaceStr(chromosome[n].DNA[1], pn1, S1.length(), chromosome[m].DNA[1], pm1, S2.length());
        chromosome[m].DNA[1] = replaceStr(chromosome[m].DNA[1], pm1, S2.length(), temp);
        temp = chromosome[n].DNA[0].substr(pn1, S1.length());
        chromosome[n].DNA[0] = replaceStr(chromosome[n].DNA[0], pn1, S1.length(), chromosome[m].DNA[0], pm1, S2.length());
        chromosome[m].DNA[0] = replaceStr(chromosome[m].DNA[0], pm1, S2.length(), temp);
        return;
    }
}
void cell::reverseMutation(string S1, int n)
{
    int pos0 = findSubstr(chromosome[n].DNA[0], S1);
    int pos1 = findSubstr(chromosome[n].DNA[1], S1);
    if ((pos0 < pos1 or pos1 == -1) and pos0 != -1)
    {
        int p = pos0;
        chromosome[n].DNA[0] = reverseStr(chromosome[n].DNA[0], p, p + S1.length());
        chromosome[n].DNA[1] = reverseStr(chromosome[n].DNA[1], p, p + S1.length());
    }
    else
    {
        int p = pos1;
        chromosome[n].DNA[0] = reverseStr(chromosome[n].DNA[0], p, p + S1.length());
        chromosome[n].DNA[1] = reverseStr(chromosome[n].DNA[1], p, p + S1.length());
    }
}
void cell::palindrome(int n)
{
    bool exist = false;
    cout << "your palindromes are:\n";
    for (int i = 2; i <= chromosome[n].DNA[0].length() / 2; i++)
    {
        for (int j = 0; j <= chromosome[n].DNA[0].length() - 2 * i; j++)
        {
            string temp = chromosome[n].DNA[0].substr(j, i);
            reverse(temp.begin(), temp.end());
            if (complementary(temp) == chromosome[n].DNA[0].substr(j + i, i))
            {
                cout << chromosome[n].DNA[0].substr(j, 2 * i) << endl;
                exist = true;
            }
        }
    }
    if (!exist)
    {
        cout << "Your DNA didn't have any palindrome\n";
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
            // delete this;
            cout << "Your cell died\n";
            return;
        }
        cout << "Your cell is healthy\n";
    }
}