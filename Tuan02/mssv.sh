#!/bin/bash
# Chương trình kiểm tra MSSV

# MSSV của bạn
MY_ID="24521190"

# Nhập họ tên
echo "Nhập họ tên của bạn:"
read name

# Vòng lặp yêu cầu nhập MSSV đến khi đúng
while true; do
    echo "Nhập MSSV của bạn:"
    read id

    if [ "$id" = "$MY_ID" ]; then
        echo "MSSV hợp lệ."
        break
    else
        echo "MSSV không khớp! Vui lòng nhập lại."
    fi
done

# In kết quả
echo "---------------------------------"
echo "Họ tên: $name"
echo "MSSV: $id"
echo "---------------------------------"
exit 0

