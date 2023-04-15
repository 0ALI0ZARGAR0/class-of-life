#include <iostream>
#include <vector>
#include "cell.h"
#include "animal.h"
using namespace std;

vector<Animal> Animals;
vector<genome> genomes;
vector<cell> cells;
vector<Animal> animals;
void list_genomes()
{
    for (int i = 0; i < genomes.size(); i++)
    {
        cout << i << "- genome is:";
        genomes[i].print();
        cout << endl;
    }
}
void list_cells()
{
    for (int i = 0; i < cells.size(); i++)
    {
        cout << i << "- cell is:";
        for (int j = 0; j < cells[i].chromosome.size(); j++)
        {
            cells[i].print(j);
            cout << endl;
        }
    }
}
void list_animals()
{
    for (int i = 0; i < animals.size(); i++)
    {
        cout << i << "- animal is:";
        for (int j = 0; j < animals[i].chromosome.size(); j++)
        {
            animals[i].print(j);
            cout << endl;
        }
    }
}
int main()
{
    cout << "// welcome //\n";
    bool run = true;
    while (run)
    {
        // system("clear");
        cout << "please select an option(by choosing a number):\n"
             << "'1' for Genomes" << endl
             << "'2' for Cells" << endl
             << "'3' for Animals" << endl
             << "'0' for exit" << endl;
        int input;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            int action;
            cout << "What do you wish to do?" << endl
                 << "'1' create a new Genome" << endl
                 << "'2' create a DNA by an RNA" << endl
                 << "'3' small Mutation (replace n nucleotides)" << endl
                 << "'4' great Mutation (replace a series of nucleotides)" << endl
                 << "'5' reverse Mutation(reverse a series of nucleotides)" << endl;
            cin >> action;

            switch (action)
            {
            case 1:
            {
                string rna, dna1, dna2;
                cout << "Make the RNA : " << endl;
                cin >> rna;
                cout << "\nMake the DNA : " << endl;
                cin >> dna1;
                cout << "\nmake the DNA complement : " << endl;
                cin >> dna2;
                genome genome(rna, dna1, dna2);
                genomes.push_back(genome);
                cout << "genome created successfully\n";
                break;
            }
            case 2:
            {
                int Selected_genome;
                cout << "Which genome? from 1 to " << genomes.size() << endl;
                cin >> Selected_genome;
                cout << "your DNA is:\n";
                genomes[Selected_genome - 1].createDNA();
                break;
            }
            case 3:
            {
                string A, C;
                int n, Selected_genome;
                cout << "Which genome? from 1 to " << genomes.size() << endl;
                cin >> Selected_genome;
                cout << "Enter the old nucleotide: " << endl;
                cin >> A;
                cout << "\nEnter the new nucleotide: " << endl;
                cin >> C;
                cout << "\nhow many replacement? " << endl;
                cin >> n;
                genomes[Selected_genome - 1].smallMutation(A, C, n);
                cout << "Mutation applied\nyour genome" << Selected_genome << " is:\n";
                genomes[Selected_genome - 1].print();
                break;
            }
            case 4:
            {
                string s1, s2;
                int Selected_genome;
                cout << "Which genome? from 1 to " << genomes.size() << endl;
                cin >> Selected_genome;
                cout << "\nEnter the old series: ";
                cin >> s1;
                cout << "\nEnter the new series: ";
                cin >> s2;
                genomes[Selected_genome - 1].greatMutation(s1, s2);
                cout << "Mutation applied\nyour genome" << Selected_genome << " is:\n";
                genomes[Selected_genome - 1].print();
                break;
            }
            case 5:
            {
                string s1;
                int Selected_genome;
                cout << "Which genome? from 1 to " << genomes.size() << endl;
                cin >> Selected_genome;
                cout << "Enter s1 :";
                cin >> s1;
                genomes[Selected_genome - 1].reverseMutation(s1);
                cout << "Mutation applied\nyour genome" << Selected_genome << " is:\n";
                genomes[Selected_genome - 1].print();
                break;
            }
            }

            break;
        }
        case 2:
        {
            int action2;
            cout << "What do you wish to do?" << endl
                 << "'1' Create a cell" << endl
                 << "'2' Add genome to an existing cell" << endl
                 << "'3' Check cell's health" << endl
                 << "'4' Small Mutation in chromosome" << endl
                 << "'5' Great Mutation in chromosome" << endl
                 << "'6' Reverse Mutation in chromosome" << endl
                 << "'7' Palindrome in chromosome" << endl;
            cin >> action2;
            switch (action2)
            {
            case 1:
            {
                cell c;
                int n;
                cout << "How many chromosome you want to add now? " << endl;
                cin >> n;
                for (int i = 0; i <= n; i++)
                {
                    string dna1;
                    string dna2;
                    cout << "Enter your " << i + 1 << " DNA1: \n";
                    cin >> dna1;
                    cout << "Enter your " << i + 1 << " DNA2: \n";
                    cin >> dna2;
                    genome tmp(NULL, dna1, dna2);
                    c.addGenome(tmp);
                }
                cells.push_back(c);
                break;
            }
            case 2:
            {
                int n;
                int selected;
                cout << "to which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                cout << "How many new chromosome you want to add? " << endl;
                cin >> n;
                for (int i = 0; i < n; i++)
                {
                    string dna1;
                    string dna2;
                    cout << "Enter your " << i + 1 << " DNA1: \n";
                    cin >> dna1;
                    cout << "Enter your " << i + 1 << " DNA2: \n";
                    cin >> dna2;
                    genome tmp(NULL, dna1, dna2);
                    cells[selected - 1].addGenome(tmp);
                }
                cout << "How many existing chromosome you want to add? " << endl;
                cin >> n;
                for (int i = 0; i < n; i++)
                {
                    cout << "select your " << i + 1 << " genome: \n";
                    int k;
                    cin >> k;
                    cells[selected - 1].addGenome(genomes[k - 1]);
                }
                break;
            }
            case 3:
            {
                int selected;
                cout << "Which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                cells[selected - 1].death();
                break;
            }
            case 4:
            {
                int selected;
                cout << "Which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                string A, C;
                int n, m;
                cout << "Enter nucleotide to replace: " << endl;
                cin >> A;
                cout << "Enter nucleotides that are gonna be replace with: " << endl;
                cin >> C;
                cout << "Enter number of first chromosome: " << endl;
                cin >> n;
                cout << "Enter times: " << endl;
                cin >> m;
                cells[selected - 1].smallMutation(A, C, n - 1, m);
                cout << "your chromosome" << n << " is:\n";
                cells[selected - 1].print(n - 1);
                break;
            }
            case 5:
            {
                int selected;
                cout << "Which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                string S1, S2;
                int n, m;
                cout << "Enter nucleotides to replace: " << endl;
                cin >> S1;
                cout << "Enter nucleotides to be replace with: " << endl;
                cin >> S2;
                cout << "Enter number of first chromosome: " << endl;
                cin >> n;
                cout << "Enter number of second chromosome: " << endl;
                cin >> m;
                cells[selected].greatMutation(S1, n - 1, S2, m - 1);
                cout << "your chromosome" << n << " is:\n";
                cells[selected].print(n - 1);
                cout << "your chromosome" << m << " is:\n";
                cells[selected].print(m - 1);
                break;
            }
            case 6:
            {
                int selected;
                cout << "Which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                string A;
                int n;
                cout << "Enter nucleotide to reverse: " << endl;
                cin >> A;
                cout << "select you chromosome: " << endl;
                cin >> n;
                cells[selected - 1].reverseMutation(A, n - 1);
                cout << "your chromosome" << n << " is:\n";
                cells[selected - 1].print(n - 1);
                break;
            }
            case 7:
            {
                int selected;
                cout << "Which cell? from 1 to " << cells.size() << endl;
                cin >> selected;
                int n;
                cout << "select you chromosome: " << endl;
                cin >> n;
                cells[selected - 1].palindrome(n - 1);
                break;
            }
            }

            break;
        }
        case 3:
        {
            int action3;
            cout << "what do you want to do?" << endl;
            cout << "5 create an Animal" << endl;
            cout << "'1' genetics similarity" << endl;
            cout << "'2' Same animal " << endl;
            cout << "'3' asexual reproduction " << endl;
            cout << "'4' sexual reproduction " << endl;
            cin >> action3;

            switch (action3)
            {

            case 1:
            {
                Animal animal2;
                Animal animal1;
                animal1.Genetic_similarity(animal2);
                break;
            }
            case 2:
            {
                Animal animal1;
                cout << "Enter the chromosome of animal1 :";
                // cin>>;
                cout << "Enter the chromosome of aniaml2 :";
                // cin>>
                if (Animals[m - 1].operator==(Animals[n - 1]))
                {
                    cout << "they are in a same group! " << endl;
                }
                else
                {
                    cout << "They are not the same!" << endl;
                }
                break;
            }
            case 3:
            {
                string chromosome;
                cout << "Enter the chromosome :" << endl;
                cin >> chromosome;
                cout << "the cromosome of a new animal is:" << endl;
                animal1.asexual();
                break;
            }
            case 4:
            {
                string chromosome;
                cout << "Enter the chromosome of aniaml2 :" << endl;
                cin >> chromosome;
                animal2.operator+(chromosome);
                new_aniaml.print();
            }
            case 5:
            {
                int cC, aC;
                cout << "how many animals do you want to create?" << endl;
                cin >> aC;
                for (int j = 0; j < aC; j++)
                {
                    cout << "for animal " << j + 1 << ":" << endl;
                    cout << "enter cell size of the Animal(count of chromosomes)" << endl;
                    cin >> cC;
                    vector<genome> r;
                    for (int i = 0; i < cC; i++)
                    {
                        string dn1, dn2;
                        cout << "enter number " << i + 1 << "'s chromosomes DNA part 1:" << endl;
                        cin >> dn1;
                        cout << "enter number " << i + 1 << "'s chromosomes DNA part 2:" << endl;
                        cin >> dn2;
                        genome tmp(NULL, dn1, dn2);
                        r.push_back(tmp);
                    }
                    Animal a1(r);
                    Animals.push_back(a1);
                }
            }
            }

            break;
        }
        case 0:
        {
            run = false;
        }
        default:
        {
            cout << "please enter a valid input!\n";
            break;
        }
        }
    }
}