#!/bin/bash

cat $1 | sed -e 's/-//' -e 's/DAILY\/MISCELLANEOUS/DAILY/' -e 's/\$//g' -e 's/,//g' >> $2
