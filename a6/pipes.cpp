#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    int pfd[2];

    pipe(pfd);

    char op = 'y';
    char cmdn1[10][20] = {0}; // saparate it
    char cmdn2[10][20] = {0}; // saparate it
    char* argv1[10] ; // give it to argv
    char* argv2[10] ; // give it to argv

    int i, j = 0, k = 0;

    char a[20] = {0};

    int wordc1 = 0;

    int wordc2 = 0;

    string quit;

    while (quit[0] != 'Q' || quit[0] != 'q')
    {
        string string1, string2;

        cout << "command 1? ";

        getline(cin, string1);

        cout << "command 2? ";

        getline(cin, string2);

        for( i = 0; i < 10; i++)
        {
            argv1[i] = NULL; // in the starting null all pointer
        }
        k = 0, j = 0, i = 0;

        for(i = 0; i <= string1.size(); i++)
        {
            if(string1[i] == ' ' || string1[i] == '\0') // saparate command
            {
                a[j] = '\0';

                strcpy(cmdn1[k++],a);

                argv1[k-1] = cmdn1[k-1]; // allocate each saparate argument to argv

                j = 0;

                wordc1++;

                memset(a, 0, sizeof(a));
            }

            else
            {
                a[j++] = string1[i];
            }
        }
        for( i = 0 ; i < 10; i++)
        {
            argv2[i] = NULL; // in the starting null all pointer
        }

        k = 0, j = 0 , i = 0;

        for(i = 0; i <= string2.size(); i++)
        {
            if(string2[i] == ' ' || string2[i] == '\0') // saparate command
            {  
                a[j] = '\0';

                strcpy(cmdn2[k++], a);

                argv2[k - 1] = cmdn2[k - 1]; // allocate each saparate argument to argv

                wordc2++;

                j = 0;

                memset(a, 0, sizeof(a));
            }
            else
            {
                a[j++] = string2[i];
            }

        }
        
        if (fork() == 0)
        {
            // child gets here and handles "grep Villanova"

            // replace standard input with input part of pipe

            dup2(pfd[0], 0);

            // close unused hald of pipe

            close(pfd[1]);

            // execute grep

            execvp(argv2[0], argv2);
        }
        else
        {
            // parent gets here and handles "cat scores"
            // replace standard output with output part of pipe
            dup2(pfd[1], 1);

            // close unused unput half of pipe

            close(pfd[0]);

            // execute cat

            execvp(argv1[0], argv1);
        }

        cin.clear();

        cin.ignore(255, '\n');

        cout << "Do you want to quit (quit/no)? "; //this part not working .

        cin >> quit;
    }
}