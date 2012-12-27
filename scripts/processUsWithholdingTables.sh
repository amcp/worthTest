#!/bin/bash
# Copyright 2012 Alexander Patrikalakis
#
# This file is part of the Worth project.
#
# Worth is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Worth is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Worth. If not, see http://www.gnu.org/licenses/.

cat $1 | sed -e '/^(a/d' -e '/^If/d' -e '/^subtracting/d' -e '/^is:/d' -e '/^divided/d' -e '/^payroll/d' -e 's/—/-/g' -e 's/,//g' -e 's/\.\ /@/g' -e "s/[@]\{1,\}/@ /g" -e "s/\-\$[0-9]\{1,\}\(.[0-9]\{1,2\}\)\{0,\}//g" -e "s/[ ]\{1,\}/ /g" -e "s/@ \$[0-9]\{1,\}.[0-9]\{2,2\} plus //g" -e 's/Not\ over.*/\$0\ 0\%\ \$0\ 0\%/' -e '/Over-/d' -e "s/TABLE [1-9]\{1,\}-//" -e 's/DAILY\ or\ MISCELLANEOUS/DAILY/' -e "s/ Payroll Period[ ]\{0,\}//" -e 's/\$//g' -e 's/\%//g' -e 's/
//' -e 's/[ 	]*$//' -e 's/\ /:/g' -e '/[A-Z]/s/^/@/' | tr "\n" " " | tr "@" "\n" | sed -e 's/\ $//' -e 's/\ /:/g' -e '/^$/d' | cut -d: -f 1,2,3,6,7,10,11,14,15,18,19,22,23,26,27 | tr ":" " " | sed -e "s/ /:/" >> $2_SINGLE.txt.dat

cat $1 | sed -e '/^(a/d' -e '/^If/d' -e '/^subtracting/d' -e '/^is:/d' -e '/^divided/d' -e '/^payroll/d' -e 's/—/-/g' -e 's/,//g' -e 's/\.\ /@/g' -e "s/[@]\{1,\}/@ /g" -e "s/\-\$[0-9]\{1,\}\(.[0-9]\{1,2\}\)\{0,\}//g" -e "s/[ ]\{1,\}/ /g" -e "s/@ \$[0-9]\{1,\}.[0-9]\{2,2\} plus //g" -e 's/Not\ over.*/\$0\ 0\%\ \$0\ 0\%/' -e '/Over-/d' -e "s/TABLE [1-9]\{1,\}-//" -e 's/DAILY\ or\ MISCELLANEOUS/DAILY/' -e "s/ Payroll Period[ ]\{0,\}//" -e 's/\$//g' -e 's/\%//g' -e 's/
//' -e 's/[ 	]*$//' -e 's/\ /:/g' -e '/[A-Z]/s/^/@/' | tr "\n" " " | tr "@" "\n" | sed -e 's/\ $//' -e 's/\ /:/g' -e '/^$/d' | cut -d: -f 1,4,5,8,9,12,13,16,17,20,21,24,25,28,29 | tr ":" " " | sed -e "s/ /:/" >> $2_MARRIED.txt.dat