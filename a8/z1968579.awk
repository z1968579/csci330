# Jacob Rudawski
# z198579
# CSCI 330
# 11/07/22

BEGIN {
    # prints the header for name tile salary
    FS = ":";
}
{
    if ($1 == "E")
    {
        employeecount++;
        name[$1] = $3;
    }
    else if ($1 == "P")
    {
        projectcount++;
        
    }
    else if ($1 == "W")
    {

    }

    if (NF == 3)
    {
        # This is an associate
        associatescount++;
        split($2,name, " ");
        associates[$1] = name[2] ", " name[1];
    }
    else if (NF == 4)
    {
        # This is a product
        productcount++;
        #print cost[$1];
        cost[$1] = $4;

    }
    else if (NF == 5)
    {
        # This is a tranaction
        transcount++;
        # Update the total sales for that associate
        sales[$3] += cost[$2] * ($5 * 1.0);
    }
}
END {
        print "|= Spice Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|\n";
    for (i in sales)
    {
        #printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
        print (name[$1]);
        
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 4");

    print "===================================";
    printf ("%22d Associates\n", associatescount);
    printf ("%22d Products\n", productcount);
    printf ("%22d Transactions\n", transcount);
}
END {
        print "|= Spice2 Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|\n";
    for (i in sales)
    {
        printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 4");

    print "===================================";
    printf ("%22d Associates\n", associatescount);
    printf ("%22d Products\n", productcount);
    printf ("%22d Transactions\n", transcount);
}
END {
        print "|= Spice3 Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|\n";
    for (i in sales)
    {
        printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 4");

    print "===================================";
    printf ("%22d Associates\n", associatescount);
    printf ("%22d Products\n", productcount);
    printf ("%22d Transactions\n", transcount);
}
END {
        print "|= Spice3 Mining =============|======================|============|";
    printf "| %-26s | %-20s | %-10s |", "   Name", "Title", "Salary";
    print "\n|============================|======================|============|\n";
    for (i in sales)
    {
        printf ("%-22s %s %10.2f\n",associates[i],i,sales[i]) | "sort -nr -k 4";
    }
    # close before printing anymore to avoid incorrect order due to sort still being open
    close("sort -nr -k 4");

    print "===================================";
    printf ("%22d Associates\n", associatescount);
    printf ("%22d Products\n", productcount);
    printf ("%22d Transactions\n", transcount);
}