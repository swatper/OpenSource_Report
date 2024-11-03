#실습문제 1번
for file in *
do
    if test -f $file
    then
        echo "$file"
    fi
done