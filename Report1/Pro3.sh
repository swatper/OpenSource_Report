#실습문제 3번
read num #값 입력 받기
fibo0=1
fibo1=1
temp=0
for((i = 1; i <= num; i++))
do
    if [ $i -gt 2 ]
    then
        temp=$fibo1
        fibo1=$(expr $fibo0 + $fibo1)
        let fibo0=$temp
    fi
    echo $fibo1
done