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
    int pfd[2], rs, status;

    rs = pipe(pfd);

    char cmd1[10][15] = {0};
    char cmd2[10][15] = {0};
    char* argv1[255];
    char* argv2[255]; 

    int i = 0, j = 0, k = 0;

    char temp[15] = {0};

    if (rs < 0)
    {
        cerr << "Pipe" << endl;
        return 1;
    }
    bool flag = true
    //while (flag)
    //{
        string command1, command2;

        cout << "command 1? ";
        getline(cin, command1);
        if(command1 == "END" )
        {
            cout << "Ending" << endl;
            flag = false
            return 2;
        }

        cout << "command 2? ";
        getline(cin, command2);
        if(command2 == "END" )
        {
            cout << "Ending" << endl;
            flag = false
            return 3;
        }

        if(command1 == "" || command2 == "")
        {
            cout << "Ending1" << endl;
            return 4;
        }
        if(command1.size() < 1 || command2.size() < 1)
        {
            cerr << "ERROR" << endl;
            return 5;
        }

        for (i = 0; i < 10; i++)
        {
            argv1[i] = NULL;
            argv2[i] = NULL;
        } 

        j = 0, i = 0, k = 0;

        for (i = 0; i <= command1.size(); i++)
        {
            if(command1[i] == ' ' || command1[i] == '\0')
            {
                temp[j] = '\0';

                strcpy(cmd1[k++], temp);

                argv1[k - 1] = cmd1[k - 1];
                j = 0;

                memset(temp, 0, sizeof(temp));
            }
            else
            {
                temp[j++] = command1[i];
            }
        }

        j = 0, i = 0, k = 0;
        
        for(i = 0; i <= command2.size(); i++)
        {
            if(command2[i] == ' ' || command2[i] == '\0')
            {  
                
                temp[j] = '\0';

                strcpy(cmd2[k++], temp);

                argv2[k - 1] = cmd2[k - 1];
                j = 0;

                memset(temp, 0, sizeof(temp));
            }
            else
            {
                temp[j++] = command2[i];
            }
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Fork" << endl;
            return 2;
        }
        else if (pid == 0)
        {
            dup2(pfd[0], 0); 

            close(pfd[1]);

            rs = execvp(argv2[0], argv2);
            if (rs < 0)
            {
                cerr << "CHILD ERROR execvp" << endl;
                exit(rs);
            }
        }
        else //parent 1
        {
            //pid_t pid2 = fork();
            if (pid < 0)
            {
                cerr << "Fork" << endl;
                return 2;
            }
            //else if (pid2 == 0)
            //{
                
            //}
            //else //parent 2
            //{
                
                dup2(pfd[1], 1);

                close(pfd[0]);
                rs = execvp(argv1[0], argv1);
                if (rs < 0)
                {
                    cerr << "PARENT ERROR execvp" << endl;
                    exit(rs);
                }
            //}
            //dup2(pfd[1], 1);
            close(pfd[0]);
            close(pfd[1]);
            wait(&status);
        }
    //}
    cin.clear();

    cin.ignore(255, '\n');
    return 0;
}
