#include <iostream>
using namespace std;

int main()
{
    cout << "// welcome //\n";
    bool run = true;
    while (run)
    {
        int input;
        cout << "please select an option: \n";
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
            cout << "have a nice day!\n";
            run = false;
            break;
        default:
            cout << "please enter a valid input!\n";
            break;
        }
    }
}