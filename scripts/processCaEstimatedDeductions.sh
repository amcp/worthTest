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

echo "ALLOWANCES:WEEKLY BIWEEKLY SEMIMONTHLY MONTHLY QUARTERLY SEMIANNUAL ANNUAL DAILY" >> $2
cat $1 | sed -e "s/ \{1,\}/ /g" -e 's/\*//g' -e 's/\ \$/:\$/' -e 's/\$//g' -e 's/,//g' >> $2