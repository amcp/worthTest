#!/bin/bash

echo "ALLOWANCES WEEKLY BIWEEKLY SEMIMONTHLY MONTHLY QUARTERLY SEMIANNUAL ANNUAL DAILY" >> $2
cat $1 | sed -e "s/ \{1,\}/ /g" -e 's/\*//g' -e 's/\$//g' -e 's/,//g' >> $2