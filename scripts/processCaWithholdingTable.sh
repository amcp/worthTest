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

cat $1 | sed -e "/%/s/[ \t]\{1,\}/ /g" -e 's/\ /:/g' | cut -d: -f 1,4  | sed -e '/[A-Z]$/s/$/:/' -e '/^\$.*/s/:/\ /' -e '/^\$.*/s/%//' -e 's/,//g' -e 's/\$//' -e '/.*:$/s/^/@/' | tr "\n" " " | sed -e 's/\ @/@/g' -e 's/$/@/' -e 's/:\ /:/g' | tr "@" "\n" | sed -e '/^$/d' >> $2
cat $1 | sed -e "/%/s/[ \t]\{1,\}/ /g" -e 's/\ /:/g' | cut -d: -f 7,10 | sed -e '/[A-Z]$/s/$/:/' -e '/^\$.*/s/:/\ /' -e '/^\$.*/s/%//' -e 's/,//g' -e 's/\$//' -e '/.*:$/s/^/@/' | tr "\n" " " | sed -e 's/\ @/@/g' -e 's/$/@/' -e 's/:\ /:/g' | tr "@" "\n" | sed -e '/^$/d' >> $2
