#!/bin/bash
  
if [ $# -ne 2 ]
then
        echo -e "Usage ./tarzan.sh filename tarfile"
elif [ ! -f $2 ]
then
        echo -e "Error cannot find tar file $2"
else
        if [[ `tar -tf $2 | grep "$1"` ]]
        then
                echo -e "$1 exists in $2"
        else
                echo -e  "$1 does not exist in $2"
        fi
fi
