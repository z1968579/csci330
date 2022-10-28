# Jacob Rudawski
# z198579
# CSCI 330
# Due 10/28/22

#!/bin/bash

# creates database
create() 
{
    printf "%s\n" "$2" > "$1"
    printf "new database created\n"
}

insert() 
{
    if [[ "$4" -gt 1921 && "$4" -lt 2029 ]]; 
    then
        if [[ ! -z "$2" && ! -z "$3" && ! -z "$5" ]]; 
        then
            printf "%s, %s, %s, %s\n" "$2" "$3" "$4" "$5" >> "$1"
            printf "Successfully added a record to the database\n"

        else
            printf "ERROR: make, model, and color must be strings >0\n"
            exit 1
        fi

    else
        printf "ERROR: year of car must be between 1921 and 2029\n"
        exit 1
    fi
}

display() 
{
    if [ $# = 1 ]; 
    then
        printf "ERROR: specify all, single #, or range # #\n"
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
        printf "ERROR: invalid display argument: %s\n" "$2"
        exit 1
    fi
}

# delete records from an existing database.
delete() 
{
    # check if they dont specify
    if [ $# = 1 ]; 
    then
        printf "ERROR: specify all, single #, or range # #\n"
        exit 1
    fi
    # check against all, single, and range and sed to delete lines
    if  ["$2" = "all" ]; 
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
        # catching if they have an incorrect arg
        printf "ERROR: invalid delete argument: %s\n" "$2"
        exit 1
    fi
}


count()
{
    if [ -f "$1" ]; 
    then
        count=$(wc -l < "$1")
        printf "$(($count - 1))\n\n"

    else
        printf "ERROR: %s does not exist\n" "$1"
        exit 1
    fi
}


#checks for interactive mode
if [ ! $# = 0 ]; 
then
    #not interactive mode
    if [ $# = 1 ]; 
    then
        printf "ERROR: please specify a command and a database\n"
        exit 1
    fi

    if [ $2 = "create" ]; 
    then # create
        if [ $# = 2 ]; 
        then
            # if no name specified
            create "$1" "Untitled Database"

        else
            create "$1" "$3"
        fi

    elif [[ $2 = "insert" || $2 = "add" ]]; 
    then
        # if they have all of the params
        if [ $# = 6 ]; 
        then
            insert "$1" "$3" "$4" "$5" "$6"

        else
            printf "ERROR: Insert requires 5 parameters.\n"
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
        printf "ERROR: invalid command %s\n" "$2"
        exit 1
    fi

else # interactive mode
    # looping until loop != y
    loop="y"
    while [ $loop = "y" ]; 
    do
        # get the database name MUST BE SPECIFIED!
        read -p "Name of database to use: " db
        while [ -z "$db" ]; 
        do
            read -p "Need name of database to use: " db
        done

        # now get the cmd
        read -p "Enter command: create, insert, display, delete, count: " cmd

        if [ "$cmd" = "create" ]; 
        then # create
            # read the params needed for create
            read -p "Header for the db: " header
            # check if they specified a header or just hit enter
            if [ -z "$header" ]; 
            then
                header = "Untitled Database"
            fi

            create "$db" "$header"

        elif [[ $cmd = "insert" || $cmd = "add" ]]; 
        then # insert
            # read in all of the params
            read -p "Make: " make
            read -p "Model: " model
            read -p "Year (1922-2028): " year
            read -p "Color: " color
            # call insert with params
            insert "$db" "$make" "$model" "$year" "$color"

        elif [ $cmd = "display" ]; 
        then # display
            # read in the display param
            read -p "How many to show (one of all, single, or range): " option
            # check which display mode they want, for each mode read the needed params and call display
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
                # invalid mode
                printf "ERROR: %s  is not valid\n" "$option"

            fi

        elif [ $cmd = "count" ]; 
        then # count
            count "$db"

        elif [ $cmd = "delete" ]; 
        then # delete
            # read the params for delete
            read -p "How many to delete (one of all, single, or range): " option
            # same logic as display but calling delte with the params gotten instead
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
                printf "ERROR: %s  is not valid\n" "$option"
            fi

        else
            printf "ERROR: invalid command: %s\n" "$cmd"
            exit 1       
        fi

        read -p "Do you want to continue? (y/n): " loop
    done
fi

exit 0