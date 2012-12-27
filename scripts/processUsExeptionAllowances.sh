#!/bin/bash

echo "ALLOWANCES WEEKLY BIWEEKLY SEMIMONTHLY MONTHLY QUARTERLY SEMIANNUAL ANNUAL DAILY" >> $2
cat $1 | sed 's/,//g' | egrep -o [0-9]+.[0-9][0-9] | tr "\n" " " | xargs | sed 's/^/1\ /' >> $2
