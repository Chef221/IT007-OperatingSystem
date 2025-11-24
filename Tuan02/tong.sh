#!/bin/sh

n=0
while [ "$n" -lt 10 ]
do
	echo "Nhập vào một số n (>=10):"
	read n
	
	if [ "$n" -lt 10 ]
	then
		echo "Số bạn nhập không hợp lệ. Vui lòng nhập lại."
	fi
done

tong=0
i=1
while [ "$i" -le "$n" ]
do
	tong=$((tong + i))
	i=$((i + 1))
done
echo "Tổng các số từ 1 đến $n là: $tong"
