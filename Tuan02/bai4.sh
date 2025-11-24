#!/bin/sh

echo "Nhập chuỗi cần tìm:"
read string

for file in *
do
    if [ -f "$file" ]; then
        if grep -l "$string" "$file"
        then
            echo "----- Nội dung file: $file -----"
            more "$file"
        fi
    fi
done

exit 0

