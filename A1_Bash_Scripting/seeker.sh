#!/bin/bash

c_present=0
a_present=0
path_present=`pwd`
pattern=$'\0'

if [ $# -eq 0 ]
then
        echo -e "Error missing the Pattern argument. \n Usage ./seeker.sh [-c] [-a] pattern [path]"
        exit 1
elif [ $# -gt 4 ]
then
        echo -e "Error, too many arguments."
        exit 1
fi

while [[ -n $1 ]]
do
        case "$1" in
                -c )
                        c_present=1
                        ;;
                -a )
                        a_present=1
                        ;;
                * )
                        if [ -d $1 ]
                        then
                                if [ -z "$pattern" ]
                                then
                                        echo -e "Error missing the Pattern argument. \n Usage ./seeker.sh [-c] [-a] pattern [path]"
                                        exit 1
                                else
                                        path_present=$1
                                fi
                        else
                                if [ -z "$pattern" ]
                                then
                                        pattern=$1
                                else
                                        echo "Error $1 is not a valid directory"
                                        exit 1
                                fi
                        fi
                        ;;
                esac
                shift
done


if [ -z "$pattern" ]
then
        echo -e "Error missing the Pattern argument. \n Usage ./seeker.sh [-c] [-a] pattern [path]"
        exit 1
fi

if [ $c_present -eq 1 ]
then
        if [ $a_present -eq 1 ]
        then
                files="`ls "$path_present" | grep "$pattern"`"
                if ( test -z "$files" )
                then
                        echo "Unable to locate any files that has the pattern "$pattern" in its name in "$path_present"."       
                        exit 1
                fi
                for file in $files
                do
                        echo -e "==== Contents of: "$path_present"/"$file" ===="
                        cat "$path_present"/"$file"
                done
        else
                files=`ls "$path_present" | grep -m 1 "$pattern"`
                if ( test -z "$files" )
                then
                        echo "Unable to locate any files that has the pattern "$pattern" in its name in "$path_present"."  
                        exit 1
                fi
                echo -e "==== Contents of: "$path_present"/"$files" ===="
                cat "$path_present"/"$files"

        fi
else
        if [ $a_present -eq 1 ]
        then
                files="`ls "$path_present" | grep "$pattern"`"
                if ( test -z "$files" )
                then
                        echo "Unable to locate any files that has the pattern "$pattern" in its name in "$path_present"."  
                        exit 1
                fi
                for file in $files
                do
                        echo "$path_present"/"$file"
                done
        else
                files=`ls "$path_present" | grep -m 1 "$pattern"`
                if ( test -z "$files" )
                then
                        echo "Unable to locate any files that has the pattern "$pattern" in its name in "$path_present"."  
                        exit 1
                fi
                echo "$path_present"/"$files"

        fi
fi
