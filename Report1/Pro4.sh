#실습문제 3번
read A B C
min=$A 
max=$A 
#작은 수 찾기
if [ $B -lt $min ]
then
    min=$B
fi
if [ $C -lt $min ]
then 
    min=$C
fi
echo "가장 작은 수 : $min"
#큰 수 찾기
if [ $B -gt $max ]
then
    max=$B
fi
if [ $C -gt $max ]
then
    max=$C
fi
echo "가장 큰 수: $max"