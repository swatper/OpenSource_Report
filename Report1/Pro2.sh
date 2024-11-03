#실습문제 2번
#C 스타일로 작성
for ((i = 1; i < 10; i++))
do
    for ((j = 1; j < 10; j++))
    do
        echo  "$i * $j = $((i * j))"
    done
done