#!/bin/bash


#if the a3config file isn't present, the script exits with error 1
if [[ ! -e "a3config" ]]
then
        echo "Error cannot find a3config"
        exit 1
fi

#runs a3config to get the variables, knowing that it exists
. a3config

#if the directory or extension weren't specified then the program gives error message and exits
if [[ -z "$DIRNAME" ]] || [[ -z "$EXTENSION" ]]
then
        echo "Error DIRNAME and EXTENSION must be set"
        exit 2
fi

#checks if the directory exits, code executes if it doesn't
if [[ ! -d "$DIRNAME" ]]
then
        echo "Error directory $DIRNAME does not exist"
        exit 3
fi

#go into the desired directory
cd $DIRNAME

#checks if there are no files found with the specified extension
if [[ $(find . -type f -name "*.$EXTENSION" | wc -l) -le 0 ]]
then
        echo "Unable to locate any files with the extension $EXTENSION in $DIRNAME"
        exit 0
fi

#saves the files it found as a list
list_of_files=`ls | grep "*.$EXTENSION"`

#iterates through the files in the list
for file in $list_of_files
do
        #prints the name directory and name of the file
        echo "$DIRNAME/$file"

        #if show is true it shows the rest of the file
        if [[ $SHOW ="true" ]]
        then
                cat $file
        fi
done

#exits with code 0
exit 0 
