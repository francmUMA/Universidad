#! /bin/bash
if [ ! -d $2 ]
then mkdir $2
fi
for file in $(ls $1)
do
    author=$(cat $1/$file | grep "autor" $info_file | cut -f 2 -d ":")
    titulo=$(cat $1/$file | grep "titulo" $info_file | cut -f 2 -d ":")
    if [ ! -d $2/$author ]
    then mkdir $2/$author
    fi
    cp $1/$file $2/$author/"${titulo}.mp3"
done


