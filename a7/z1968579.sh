# Jacob Rudawski
# z198579
# CSCI 330
# 10/28/22

#!/bin/bash

#creates database
create() 
{
    printf "%s\n" "$2" > "$1"
    printf "new database created\n"
}

#displays the database
display() 
{
    if [ $# = 1 ]; 
    then
        printf "ERROR no arguement\n"
        exit 1
    fi

    if [ "$2" = "all" ]; 
    then
        cat "$1"

    elif [ "$2" = "single" ]; 
    then
        sed -n $(($3 + 1))p "$1"

    elif [ "$2" = "range" ]; 
    then
        sed -n $(($3 + 1)),$(($4 + 1))p "$1"
        printf "\n"

    else
        printf "ERROR invalid display argument: %s\n" "$2"
        exit 1
    fi
}

#inserts a record into the database
insert() 
{
    if [[ "$4" -gt 1921 && "$4" -lt 2029 ]]; 
    then
        if [[ ! -z "$2" && ! -z "$3" && ! -z "$5" ]]; 
        then
            printf "%s, %s, %s, %s\n" "$2" "$3" "$4" "$5" >> "$1"
            printf "Successfully added a record to the database\n"

        else
            printf "ERROR make, model, and color are not strings\n"
            exit 1
        fi

    else
        printf "ERROR year of car must be between 1921 and 2029\n"
        exit 1
    fi
}

#delete records from an existing database
delete() 
{
    #check if they dont specify
    if [ $# = 1 ]; 
    then
        printf "ERROR no arguement\n"
        exit 1
    fi

    if  [ "$2" = "all" ]; 
    then
        sed -i '1!d' "$1"
        printf "All records deleted\n"

    elif [ "$2" = "single" ]; 
    then
        sed -i $(($3 + 1))d "$1"
        printf "1 record deleted\n"

    elif [ "$2" = "range" ]; 
    then
        sed -i $(($3 + 1)),$(($4 + 1))d "$1"
        printf "$(($4 - $3 + 1)) records deleted\n"

    else
        printf "ERROR invalid delete argument: %s\n" "$2"
        exit 1
    fi
}

#prints out the count in the database
count()
{
    if [ -f "$1" ]; 
    then
        count=$(wc -l < "$1")
        printf "$(($count))\n\n"

    else
        printf "ERROR %s does not exist\n" "$1"
        exit 1
    fi
}

#checks for interactive mode
if [ ! $# = 0 ]; 
then
    #not interactive mode
    if [ $# = 1 ]; 
    then
        printf "ERROR please specify a command and a database\n"
        exit 1
    fi

    if [ $2 = "create" ]; 
    then 
        if [ $# = 2 ]; 
        then

            create "$1" "$3"
        fi

    elif [[ $2 = "insert" ]]; 
    then
        #checks for all the arguements then inserts them
        if [ $# = 6 ]; 
        then
            insert "$1" "$3" "$4" "$5" "$6"

        else
            printf "ERROR Insert requires 5 parameters\n"
            exit 1
        fi

    elif [ "$2" = "display" ]; 
    then
        display "$1" "$3" "$4" "$5"

    elif [ "$2" = "delete" ]; 
    then
        delete "$1" "$3" "$4" "$5"

    elif [ "$2" = "count" ]; 
    then
        count "$1"

    else
        printf "ERROR invalid command %s\n" "$2"
        exit 1
    fi

#interactive mode
else 

    #looping until loop != y
    loop="y"
    while [ $loop = "y" ]; 
    do
        read -p "Name of database to use: " db
        while [ -z "$db" ]; 
        do
            read -p "Need a name of database to use: " db
        done

        read -p "Enter a command (create, display, count, insert, delete): " cmd

        if [ "$cmd" = "create" ]; 
        then 
            read -p "Header for the database: " header
            create "$db" "$header"

        elif [[ $cmd = "insert" || $cmd = "add" ]]; 
        then 
            read -p "Make: " make
            read -p "Model: " model
            read -p "Year: " year
            read -p "Color: " color
            insert "$db" "$make" "$model" "$year" "$color"

        elif [ $cmd = "display" ]; 
        then
            read -p "How many to show (all, single, or range): " option
            if [ $option = "single" ]; 
            then
                read -p "Which single: " single
                display "$db" "$option" "$single"

            elif [ $option = "range" ]; 
            then
                read -p "Beginingining of range: " start
                read -p "End of range: " end
                display "$db" "$option" "$start" "$end"

            elif [ $option = "all" ]; 
            then
                display "$db" "$option"

            else
                printf "ERROR %s is not valid\n" "$option"

            fi

        elif [ $cmd = "count" ]; 
        then 
            count "$db"

        elif [ $cmd = "delete" ]; 
        then 
            read -p "How many to delete (all, single, or range): " option
            if [ $option = "single" ]; 
            then
                read -p "Which single: " single
                delete "$db" "$option" "$single"

            elif [ $option = "range" ]; 
            then
                read -p "Start of range: " start
                read -p "End of range: " end
                delete "$db" "$option" "$start" "$end"

            elif [ $option = "all" ]; 
            then
                delete "$db" "$option"

            else
                printf "ERROR %s is not valid\n" "$option"
            fi

        else
            printf "ERROR invalid command: %s\n" "$cmd"
            exit 1       
        fi
        #asks for loop
        read -p "Do you want to continue? (y/n): " loop
    done
fi

exit 0