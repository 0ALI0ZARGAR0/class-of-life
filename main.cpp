#include <iostream>
#include <vector>
#include "cell.h"
#include "animal.h"
using namespace std;

vector<Animal> Animals;
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
        cout<<"'1' is for Genome"<<endl<<"'2' is for Cell"<<endl;
        cout<<"'3'is for animal"<<endl;
        cout<<"'4'is for exit";
        int input;
        cout << "please select an option(by choosing a number): \n";
        cin >> input;
        switch (input)
        {
        case 1:{
            int action;
            cout<<"What do you want to do?"<<endl<<"'1' create a new Genome"<<endl<<"'2' make DNA by RNA"<<endl;
            cout<<"'3' small Mutation (A,C,n)"<<endl<<"'4' great Mutation"<<endl<<"'5' reverse Mutation"<<endl;
            cin>>action;

            switch (action)
             {
               case 1:
               string rna,dna1,dna2;
               cout<<"Make the RNA :"<<endl;
               cin>>rna;
               cout<<"Make the DNA :"<<endl;
               cin>>dna1;
               cout<<"make the DNA complement :"<<endl;
               cin>>dna2;
               genome genome(rna,dna1,dna2);
               break;
               case 2:
               genome.createDNA();

               int Selected_genome;
               cout << "Which genome? from 0 to " << genomes.size()-1 << endl;
               cin >>Selected_genome;
               break;
               case 3:
               string A,C;
               int n;
               cout<<"Enter the 'A' :"<<endl;
               cin>>A;
               cout<<"Enter the 'C' :"<<endl;
               cin>>C;
               cout<<"Enter the 'n' :"<<endl;
               cin>>n;
               genomes[Selected_genome].smallMutation(A, C, n);
               genomes[Selected_genome].print();
               break;

               case 4:
               string s1,s2;
               cout<<"Enter s1 :";
               cin>>s1;
               cout<<"Enter s2 :";
               cin>>s2;
               genomes[Selected_genome].greatMutation(s1, s2);
               genomes[Selected_genome].print();
               break;

              case 5 :
              string s1;
              cout<<"Enter s1 :";
              cin>>s1;
              genomes[Selected_genome].reverseMutation(s1);
              genomes[Selected_genome].print();
              break;
            }
        }
            break;
        case 2:
            int action2;
            cout<<"What do you want to do?"<<endl<<"'1'Create a cell"<<endl<<"'2'Save chromosome and DNAs"<<endl;
            cout<<"'3'Delete cell"<<endl<<"'4'Great Mutation in chromosome"<<endl<<"'5'Small Mutation in chromosome"<<endl;
            cout<<"'6'Reverse Mutation in chromosome"<<endl<<"'7'Palindrome in chromosome"<<endl;
            cin>>action2;
            switch(action2)
            {
              case 1:
              cell c;
              int n;
              cout<<"Enter the number of chromosome of cell"<<endl;
              cin>>n;
              for (int i=0;i<=n;i++)
              { 
                string dna1;
                string dna2;
                cin>>dna1;
                cin>>dna2;
               genome tmp(NULL,dna1,dna2);
               c.addGenome(tmp);
              }
              break;
               case 2:
                break;
               case 3:
               cell c;
               c.death();
               break;

               case 4:
               string S1 ,S2;
               int n,m;
               cout << "Enter S1 (somethig to replace): "<< endl;
                cin >> S1;
                cout << "Enter S2 (something that is gonna be replace with): "<< endl;
                cin >> S2;
                cout << "Enter n (number of first chromosome): "<< endl;
                cin >> n;
                cout << "Enter m (number of second chromosome): "<< endl;
                cin >> m;
                cells[m].greatMutation(S1,n,S2,m);

               break;
               case 5:
               cell c;
               string A ,C;
               int n,m;
               cout << "Enter A (somethig to replace): "<< endl;
                cin >> S1;
                cout << "Enter C (something that is gonna be replace with): "<< endl;
                cin >> S2;
                cout << "Enter n (number of first chromosome): "<< endl;
                cin >> n;
                cout << "Enter m (number of second chromosome): "<< endl;
                cin >> m;
                c.smallMutation(A,C,n,m);
                c.print();
               break;
               case 6:
               string S1;
               cout<<"Enter the chromosome you want to reverse it"<<endl;
               cin>>S1;
               int n;
               cout<<"Enter the number of chromosome"<<endl;
               cin>>n;
               c.reverseMutation(S1,n);
               break;
               case 7:
               int n;
               cin>>n;
               break;
              
            }

            break;
        case 3:
               int action3;
            cout << "what do you want to do?"<< endl;
            cout << "5 create an Animal" << endl;
            cout << "'1' genetics similarity" << endl;
            cout << "'2' Same animal " << endl;
            cout << "'3' asexual reproduction " << endl;
            cout << "'4' sexual reproduction " << endl;
            cin >>action3;

             switch(action3)
             {  
                
                case 1 :
                Animal animal2;
                Animal animal1;
                animal1.Genetic_similarity(animal2);
                break;
                case 2:
                Animal animal1;
                cout<<"Enter the chromosome of animal1 :";
                //cin>>;
                cout<<"Enter the chromosome of aniaml2 :";
                //cin>>
                if(Animals[m - 1].operator==(Animals[n - 1]))
                {
                    cout<<"they are in a same group! "<<endl;
                }
                else{
                    cout << "They are not the same!" << endl;
                }
                break;
                case 3:
                string chromosome;
                cout<<"Enter the chromosome :"<<endl;
                cin>>chromosome;
                cout<<"the cromosome of a new animal is:"<<endl;
                animal1.asexual();
                break;
                case 4:
                string chromosome;
                cout<<"Enter the chromosome of aniaml2 :"<<endl;
                cin>>chromosome;
                animal2.operator+(chromosome);
                new_aniaml.print();
                case 5:
                int cC, aC;
                cout << "how many animals do you want to create?" << endl;
                cin >> aC;
                for(int j = 0; j < aC; j++){
                    cout << "for animal " << j+1 << ":" << endl;
                    cout << "enter cell size of the Animal(count of chromosomes)" << endl;
                    cin >> cC;
                    vector<genome> r;
                    for(int i = 0; i < cC; i++){
                        string dn1, dn2;
                        cout << "enter number " << i+1 << "'s chromosomes DNA part 1:" << endl;
                        cin >> dn1;
                        cout << "enter number " << i+1 << "'s chromosomes DNA part 2:" << endl;
                        cin >> dn2;
                        genome tmp(NULL, dn1, dn2);
                        r.push_back(tmp);
                    }
                    Animal a1(r);
                    Animals.push_back(a1);
                }
             }

            break;
        default:
            cout << "please enter a valid input!\n";
            break;
        }
    }
}