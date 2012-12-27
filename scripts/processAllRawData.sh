#!/usr/bin/env bash
#
# First argument is base path, second argument is year.
#
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

if [ ! -d "$1/data" ]; then
    mkdir -p $1/data
else
    rm -f data/$2*
fi

if [ -e "$1/raw/$2_CA_ESTIMATED_DEDUCTION.txt" ]; then
    $1/scripts/processCaEstimatedDeductions.sh $1/raw/$2_CA_ESTIMATED_DEDUCTION.txt $1/data/$2_CA_ESTIMATED_DEDUCTION.txt.dat
else
    echo "$1/raw/$2_CA_ESTIMATED_DEDUCTION.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_EXEMPTION_ALLOWANCE.txt" ]; then
    $1/scripts/processCaExemptionAllowances.sh $1/raw/$2_CA_EXEMPTION_ALLOWANCE.txt $1/data/$2_CA_EXEMPTION_ALLOWANCE.txt.dat
else
    echo "$1/raw/$2_CA_EXEMPTION_ALLOWANCE.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_LOW_INCOME.txt" ]; then
    $1/scripts/processCaFilingStatusFrequencyTable.sh $1/raw/$2_CA_LOW_INCOME.txt $1/data/$2_CA_LOW_INCOME.txt.dat
else
    echo "$1/raw/$2_CA_LOW_INCOME.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_STANDARD_DEDUCTION.txt" ]; then
    $1/scripts/processCaFilingStatusFrequencyTable.sh $1/raw/$2_CA_STANDARD_DEDUCTION.txt $1/data/$2_CA_STANDARD_DEDUCTION.txt.dat
else
    echo "$1/raw/$2_CA_STANDARD_DEDUCTION.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_HEADOFHOUSEHOLD.txt" ]; then
    $1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_HEADOFHOUSEHOLD.txt $1/data/$2_CA_HEADOFHOUSEHOLD.txt.dat
else
    echo "$1/raw/$2_CA_HEADOFHOUSEHOLD.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_SINGLE.txt" ]; then
    $1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_SINGLE.txt $1/data/$2_CA_SINGLE.txt.dat
else
    echo "$1/raw/$2_CA_SINGLE.txt does not exist."
fi

if [ -e "$1/raw/$2_CA_MARRIED.txt" ]; then
    $1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_MARRIED.txt $1/data/$2_CA_MARRIED.txt.dat
else
    echo "$1/raw/$2_CA_MARRIED.txt does not exist."
fi

if [ -e "$1/raw/$2_US_SINGLE_MARRIED.txt" ]; then
    $1/scripts/processUsWithholdingTables.sh $1/raw/$2_US_SINGLE_MARRIED.txt $1/data/$2_US
else
    echo "$1/raw/$2_US_SINGLE_MARRIED.txt does not exist."
fi

if [ -e "$1/raw/$2_US_WITHHOLDING_ALLOWANCE.txt" ]; then
    $1/scripts/processUsWithholdingAllowances.sh $1/raw/$2_US_WITHHOLDING_ALLOWANCE.txt $1/data/$2_US_WITHHOLDING_ALLOWANCE.txt.dat
else
    echo "$1/raw/$2_US_WITHHOLDING_ALLOWANCE.txt does not exist."
fi

