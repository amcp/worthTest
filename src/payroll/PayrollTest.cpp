/*
 * PayrollTest.cpp
 *
 * Created on: Dec 23, 2012
 * Copyright 2012 Alexander Patrikalakis
 *
 * This file is part of the Worth project.
 *
 * Worth is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Worth is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Worth. If not, see http://www.gnu.org/licenses/.
 */

#include <string>
#include "worth/payroll/PayrollPeriods.h"
#include "gtest/gtest.h"

TEST(PayrollPeriods, Caps) {
  ASSERT_EQ(Worth::Daily, Worth::convertStringToPayrollFrequency("DAILY"));
  ASSERT_EQ(Worth::Weekly, Worth::convertStringToPayrollFrequency("WEEKLY"));
  ASSERT_EQ(Worth::Biweekly,
            Worth::convertStringToPayrollFrequency("BIWEEKLY"));
  ASSERT_EQ(Worth::Semimonthly,
            Worth::convertStringToPayrollFrequency("SEMIMONTHLY"));
  ASSERT_EQ(Worth::Monthly, Worth::convertStringToPayrollFrequency("MONTHLY"));
  ASSERT_EQ(Worth::Quarterly,
            Worth::convertStringToPayrollFrequency("QUARTERLY"));
  ASSERT_EQ(Worth::Semiannual,
            Worth::convertStringToPayrollFrequency("SEMIANNUAL"));
  ASSERT_EQ(Worth::Annual, Worth::convertStringToPayrollFrequency("ANNUAL"));
  ASSERT_EQ(Worth::Unknown, Worth::convertStringToPayrollFrequency("FOOBAR"));
}

TEST(PayrollPeriods, MixedCase) {
  ASSERT_EQ(Worth::Daily, Worth::convertStringToPayrollFrequency("Daily"));
  ASSERT_EQ(Worth::Weekly, Worth::convertStringToPayrollFrequency("Weekly"));
  ASSERT_EQ(Worth::Biweekly,
            Worth::convertStringToPayrollFrequency("Biweekly"));
  ASSERT_EQ(Worth::Semimonthly,
            Worth::convertStringToPayrollFrequency("Semimonthly"));
  ASSERT_EQ(Worth::Monthly, Worth::convertStringToPayrollFrequency("Monthly"));
  ASSERT_EQ(Worth::Quarterly,
            Worth::convertStringToPayrollFrequency("Quarterly"));
  ASSERT_EQ(Worth::Semiannual,
            Worth::convertStringToPayrollFrequency("Semiannual"));
  ASSERT_EQ(Worth::Annual, Worth::convertStringToPayrollFrequency("Annual"));
  ASSERT_EQ(Worth::Unknown, Worth::convertStringToPayrollFrequency("Unknown"));
}
