#include <iostream>
#include <vector>
#include "cell.h"
#include "animal.h"
using namespace std;

void list_genomes(vector<genome> genomes)
{
    for (int i = 0; i < genomes.size(); i++)
    {
        cout << i << "- genome is:";
        genomes[i].print();
        cout << endl;
    }
}
void list_cells(vector<cell> cells)
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
void list_animals(vector<Animal> animals)
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
    vector<genome> genomes;
    vector<cell> cells;
    vector<Animal> animals;
    cout << "// welcome //\n";
    bool run = true;
    while (run)
    {
        // system("clear");
        cout << "1- create a genome\n"
             << "2- create a cell\n"
             << "3- create an animal"
             << "4- choose a genome\n"
             << "5- choose a cell\n"
             << "6- choose an animal\n";
        int input;
        cout << "please select an option(by choosing a number): \n";
        cin >> input;
        switch (input)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            cout << "have a nice day.\n";
            run = false;
            break;
        default:
            cout << "please enter a valid input!\n";
            break;
        }
    }
}