#!/bin/bash
# This script downloads photos from server, tries to recognize QR-codes and calls AutoHotKey script which pushes values to NXT.


WGET="/c/Program Files (x86)/GnuWin32/bin/wget.exe"
ZBARIMG="/c/Program Files (x86)/ZBar/bin/zbarimg.exe"
AUTOHOTKEY="/c/Program Files/Autohotkey/Autohotkey.exe"
URL="http://192.168.2.3:80/"

sleep 2
shopt -s nullglob

echo ./*/*.$EXT

while true
do

  "$WGET" -r -np "$URL" 2> /dev/null

  for IMAGE in ./*/*.{jpg,JPG,img,IMG,png,PNG,bmp,BMP,gif,GIF}
  do
    #if [ ! -f $IMAGE.bak ]
    #then
      echo "Processing ${IMAGE}..."
      RESULT=$("$ZBARIMG" $IMAGE 2>/dev/null)
      NUMBER=${RESULT:8}
      echo $NUMBER
      "$AUTOHOTKEY" automator.ahk $NUMBER
      mv $IMAGE $IMAGE.bak
      #sleep 1
    #fi
  done

done