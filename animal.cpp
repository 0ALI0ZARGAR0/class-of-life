#include<iostream>
#include<vector>
#include <cstdlib>
using namespace std;
class Animal
{
   void Genetic_similarity(cell cell1,cell2)
    {
        int sum=0;
        for(int i=0;i <max(cell2.size(),cell1.size());i++)
        {
          if(cell1[i] !=cell2[i])
          {
              sum+=1;
          }

        }
       double Percent=100-(sum/max(cell1.size(),cell2.size()))*100;
       cout<<"darsad tashaboh is:"<<Percent;

    }
    bool Same_Species()
    {
        if(Percent>=70)return true;return false;
    }
    void asexual()
    {
        strcpy(cell);

        for (int i = 0; i <(0.7)cell.size ; i++)
        {
            rand() 
        }

        
       


    }

};

int main(){
   
}
