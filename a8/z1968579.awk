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
        id[$1] = $2;
        name[$1] = $3;
        title[$1] = $4;
        salary[$1] = $5;
    }
    else if ($1 == "P")
    {
        projectcount++;
        projectname[$1] = $3;
        manager[$1] = $4;
    }
    else if ($1 == "W")
    {
        for (i in id)
        {
            if (id[i] == $3)
            {       
                #workingon[$2] = $4; I am not sure how to do this part
            }
        }
    } 
}
END {
    for (j = 0; j <= 3; j++) # I do not think this works
    {
        print "|= ",projectname[j], "=============|======================|============|";
        printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
        print "\n|============================|======================|============|\n";
        for (i in )
        {
            #printf print variables then pipe to sort | "sort -nr -k 4";
            
        }
        # close before printing anymore to avoid incorrect order due to sort still being open
        #close("sort -nr -k 4");
        #print closing stuff
    }
    #print more closing stuff
}
