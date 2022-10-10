#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int pfd[2];

    pid_t rs = pipe(pfd);

    char cmd1[10][20] = {0};
    char cmd2[10][20] = {0};
    char* argv1[10];
    char* argv2[10]; 

    int i, j = 0, k = 0;

    char a[20] = {0};

    if (rs < 0)
    {
        cerr << "Pipe" << endl;
        return 1;
    }
    //while ()
    //{
        string string1, string2;

        cout << "command 1? ";
        getline(cin, string1);
        if(string1 == "END" )
        {
            cout << "Ending" << endl;
            return 2;
        }

        cout << "command 2? ";
        getline(cin, string2);
        if(string2 == "END" )
        {
            cout << "Ending" << endl;
            return 3;
        }

        if(string1 == "" || string2 == "")
        {
            cout << "Ending1" << endl;
            return 4;
        }
        if(string1.size() < 1 || string2.size() < 1)
        {
            cerr << "ERROR" << endl;
            return 5;
        }

        for (i = 0; i < 10; i++)
        {
            argv1[i] = NULL;
        }
        
        k = 0, j = 0, i = 0;

        for (i = 0; i <= string1.size(); i++)
        {
            if(string1[i] == ' ' || string1[i] == '\0')
            {
                a[j] = '\0';

                strcpy(cmd1[k++], a);

                argv1[k - 1] = cmd1[k - 1];
                j = 0;

                memset(a, 0, sizeof(a));
            }
            else
            {
                a[j++] = string1[i];
            }
        }
        for(i = 0; i < 10; i++)
        {
            argv2[i] = NULL;
        }

        k = 0, j = 0, i = 0;

        for(i = 0; i <= string2.size(); i++)
        {
            if(string2[i] == ' ' || string2[i] == '\0')
            {  
                a[j] = '\0';

                strcpy(cmd2[k++], a);

                argv2[k - 1] = cmd2[k - 1];
                j = 0;

                memset(a, 0, sizeof(a));
            }
            else
            {
                a[j++] = string2[i];
            }
        }

        rs = fork();
        if (rs < 0)
        {
            cerr << "Fork" << endl;
            return 2;
        }
        else if (rs == 0)
        {
            dup2(pfd[0], 0);

            close(pfd[1]);

            execvp(argv2[0], argv2);
        }
        else
        {
            dup2(pfd[1], 1);

            close(pfd[0]);

            execvp(argv1[0], argv1);
        }

        cin.clear();

        cin.ignore(255, '\n');

    //}
    return 0;
}
