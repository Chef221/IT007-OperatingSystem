#!/bin/bash
# Script: thu_muc_monhoc.sh

# a. Nhap ho va ten (khong dau, vien lien)
echo "Nhap ho va ten cua ban (khong dau, viet lien):"
read hoten

# Kiem tra rong
if [ -z "$hoten" ];then
    echo "Ban chua nhap ten. Thoat chuong trinh"
    exit 1
fi

# Tao thu muc sinh vien
mkdir -p "$hoten"
echo "Da tao thu muc sinh vien: $hoten"

# b. Kiem tra file monhoc.txt
if [ ! -f monhoc.txt ]; then
    echo "Khong tim thay file monhoc.txt trong thu muc hien tai."
    exit 1
fi
# Doc tung dong trong monhoc.txt
while IFS= read -r monhoc
do
    # Bo qua dong trong
    if [ -n "$monhoc" ];then
        mkdir -p "$hoten/$monhoc"
        echo "Da tao thu muc: $hoten/$monhoc"
    fi
done < monhoc.txt

echo "----------------------------"
echo "Da tao thuc muc cho sinh vien '$hoten' voi cac mon hoc trong file monhoc.txt"
echo "----------------------------"
exit 0