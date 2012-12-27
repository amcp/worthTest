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

rm -rf $1/data

$1/scripts/processCaEstimatedDeductions.sh $1/raw/$2_CA_ESTIMATED_DEDUCTION.txt $1/data/$2_CA_ESTIMATED_DEDUCTION.txt.dat
$1/scripts/processCaExemptionAllowances.sh $1/raw/$2_CA_EXEMPTION_ALLOWANCE.txt $1/data/$2_CA_EXEMPTION_ALLOWANCE.txt.dat
$1/scripts/processCaFilingStatusFrequencyTable.sh $1/raw/$2_CA_LOW_INCOME.txt $1/data/$2_CA_LOW_INCOME.txt.dat
$1/scripts/processCaFilingStatusFrequencyTable.sh $1/raw/$2_CA_STANDARD_DEDUCTION.txt $1/data/$2_CA_STANDARD_DEDUCTION.txt.dat
$1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_HEADOFHOUSEHOLD.txt $1/data/$2_CA_HEADOFHOUSEHOLD.txt.dat
$1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_SINGLE.txt $1/data/$2_CA_SINGLE.txt.dat
$1/scripts/processCaWithholdingTable.sh $1/raw/$2_CA_MARRIED.txt $1/data/$2_CA_MARRIED.txt.dat

$1/scripts/processUsWithholdingTables.sh $1/raw/$2_US_SINGLE_MARRIED.txt $1/data/$2_US
$1/scripts/processUsWithholdingAllowances.sh $1/raw/$2_US_WITHHOLDING_ALLOWANCE.txt $1/data/$2_US_WITHHOLDING_ALLOWANCE.txt.dat