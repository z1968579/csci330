# Jacob Rudawski
# z198579
# CSCI 330
# 11/07/22

BEGIN {
    FS = ":";
}
{
    if ($1 == "E")
    {
        EmpCount++;
        id[$2] = $2;
        name[$2] = $3;
        title[$2] = $4;
        salary[$2] = $5;
        TotalSal += $5 * 1.0;
    }
    else if ($1 == "P")
    {
        ProjCount++;
        ProjId[$2] = $2;
        ProjectName[$2] = $3;
        #manager[$4] = $4;
    }
    else if ($1 == "W")
    {

        if (ProjId[$4] == 1)
        {
            #print ProjId[$];
            #print manager[$4];
            SpiceEmployees[$3] = $3;
            TotalSpice += salary[$3] * 1.0;
            SpiceCount++;
        }
        else if (ProjId[$4] == 2)
        {
            BeneEmployees[$3] = $3;
            TotalBene += salary[$3] * 1.0;
            BeneCount++;
        }
        else if (ProjId[$4] == 3)
        {
            JihadEmployees[$3] = $3;
            TotalJihad += salary[$3] * 1.0;
            JihadCount++;
        }
        else if (ProjId[$4] == 4)
        {
            SecurityEmployees[$3] = $3;
            TotalSec += salary[$3] * 1.0;
            SecurityCount++;
        }
    } 
}
END {
    print "|= Spice Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";
    for (i in SpiceEmployees)
    {
        if (i == 140)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10i |\n", name[i], title[i], salary[i]) | "sort -rn -t '|' -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -rn -t '|' -k 4");
    print "|============================|======================|============|";
    printf "   employed on project: %i", SpiceCount;
    printf "\taverage salary: %.2f", TotalSpice / SpiceCount;
}
END {
    print "\n\n|= Bene Gesserit Schemes ====|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";
    for (i in BeneEmployees)
    {
        if (i == 192)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10i |\n", name[i], title[i], salary[i]) | "sort -rn -t '|' -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -rn -t '|' -k 4");
    print "|============================|======================|============|";
    printf "   employed on project: %i", BeneCount;
    printf "\taverage salary: %.2f", TotalBene / BeneCount;
}
END {
    print "\n\n|= Muad'Dib's Jihad =========|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";
    for (i in JihadEmployees)
    {
        if (i == 110)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10i |\n", name[i], title[i], salary[i]) | "sort -rn -t '|' -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -rn -t '|' -k 4");
    print "|============================|======================|============|";
    printf "   employed on project: %i", JihadCount;
    printf "\taverage salary: %.2f", TotalJihad / JihadCount;
}
END {
    print "\n\n|= Security =================|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";
    for (i in SecurityEmployees)
    {
        if (i == 130)
        {
            name[i]= "*" name[i];
        }
        printf ("| %-26s | %-20s | %-10i |\n", name[i], title[i], salary[i]) | "sort -rn -t '|' -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -rn -t '|' -k 4");
    print "|============================|======================|============|";
    printf "   employed on project: %i", SecurityCount;
    printf "\taverage salary: %.2f", TotalSec / SecurityCount;



    print "\n\nEmployees: ", EmpCount, " Projects: ", ProjCount;
    printf ("Total Salary: %25.2f ", TotalSal);
    printf ("\nEmployee Average Salary:  %13.2f ", TotalSal / EmpCount);
    print "";
}