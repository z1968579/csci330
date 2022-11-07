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
        employeecount++;
        id[$2] = $2;
        name[$2] = $3;
        title[$2] = $4;
        salary[$2] = $5;
        totalsal += $5 * 1.0;
    }
    else if ($1 == "P")
    {
        projectcount++;
        projid[$2] = $2;
        projectname[$2] = $3;
        manager[$2] = $4;
    }
    else if ($1 == "W")
    {
        if (projid[$4] == 1)
        {
            SpiceEmployees[$3] = $3;
        }
        else if (projid[$4] == 2)
        {
            BeneEmployees[$3] = $3;
        }
        else if (projid[$4] == 3)
        {
            JihadEmployees[$3] = $3;
        }
        else if (projid[$4] == 4)
        {
            SecurityEmployees[$3] = $3;
        }
    } 
}
END {
    print "|= Spice Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|";
    for (i in SpiceEmployees)
    {
        printf ("| %-26s | %-20s | %-10.0f |\n", name[i], title[i], salary[i]) | "sort -nr -k 3";
        #print i, name[i];
        #printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
        close("sort -nr -k 3");
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 6");
    #print closing stuff
    print "Employees: ", employeecount, " Projects: ", projectcount;
    printf ("Total Salary: %.2f ", totalsal);
    printf ("\nEmployee Average Salary:  %.2f ", totalsal / employeecount);
    print "";
    #print more closing stuff
}
