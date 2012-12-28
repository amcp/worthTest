/*
 * StateTest.cpp
 *
 * Created on: Dec 21, 2012
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
 *
 */

#include <vector>
#include <string>
#include <ql/currency.hpp>
#include <ql/currencies/america.hpp>
#include "worth/tax/TieredTaxer.h"
#include "worth/payroll/WithholdingTable.h"
#include "worth/payroll/Withholder.h"
#include "worth/payroll/PayrollPeriods.h"
#include "worth/jurisdiction/State.h"
#include "worth/Utility.h"
#include "gtest/gtest.h"

TEST(State, Load2013EstimatedDeductionTable) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::Utility* util = Worth::Utility::getInstance();

  Worth::State::AllowanceFrequencyTable estimatedTable =
      Worth::State::generateAllowanceFrequencyTable(
          util->readLines("data/2013_CA_ESTIMATED_DEDUCTION.txt.dat"), USD);

  Worth::State CA("CA", 2013, USD);
  CA.addEstimatedDeductions(estimatedTable.begin(), estimatedTable.end());
}

TEST(State, Load2013ExemptionAllowanceTable) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::Utility* util = Worth::Utility::getInstance();

  Worth::State::AllowanceFrequencyTable exemptionTable =
      Worth::State::generateAllowanceFrequencyTable(
          util->readLines("data/2013_CA_EXEMPTION_ALLOWANCE.txt.dat"), USD);

  Worth::State CA("CA", 2013, USD);
  CA.addExemptionAllowances(exemptionTable.begin(), exemptionTable.end());
}

TEST(State, Load2013LowIncomeTable) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::Utility* util = Worth::Utility::getInstance();
  Worth::State::StatusFrequencyTable lowIncomeTable =
      Worth::State::generateStatusFrequencyTable(
          util->readLines("data/2013_CA_LOW_INCOME.txt.dat"), USD);

  Worth::State CA("CA", 2013, USD);
  CA.addLowIncomeExemptions(lowIncomeTable.begin(), lowIncomeTable.end());
}

TEST(State, Load2013StandardDeductionTable) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::Utility* util = Worth::Utility::getInstance();
  Worth::State::StatusFrequencyTable standardDeductionTable =
      Worth::State::generateStatusFrequencyTable(
          util->readLines("data/2013_CA_STANDARD_DEDUCTION.txt.dat"), USD);

  Worth::State CA("CA", 2013, USD);
  CA.addStandardDeductions(standardDeductionTable.begin(), standardDeductionTable.end());
}

TEST(State, EmptyState) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::State CA("CA", 2012, USD);

  EXPECT_EQ(USD, CA.getCurrency());
  EXPECT_EQ("CA", CA.getName());
  EXPECT_FALSE(CA.hasLowIncomeExemptionForStatus(""));
  EXPECT_DEATH(CA.getExemptionAllowance(0, Worth::Daily), ".*");
  EXPECT_DEATH(CA.getLowIncomeExemption("SINGLE", Worth::Daily), ".*");
  EXPECT_DEATH(CA.getStandardDeduction("SINGLE", Worth::Daily), ".*");
  EXPECT_DEATH(CA.getWithholder("SINGLE"), ".*");
}

TEST(State, SingleCA2013) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::State* CA = new Worth::State("CA", 2012, USD);
  Worth::TieredTaxer* taxer = new Worth::TieredTaxer(USD);
  taxer->addTier(0 * USD, 0.011);
  taxer->addTier(282 * USD, 0.022);
  taxer->addTier(688 * USD, 0.044);
  taxer->addTier(1052 * USD, 0.066);
  taxer->addTier(1462 * USD, 0.088);
  taxer->addTier(1848 * USD, 0.1023);
  taxer->addTier(9616 * USD, 0.1133);
  taxer->addTier(11538 * USD, 0.1243);
  taxer->addTier(19230 * USD, 0.1353);
  taxer->addTier(38462 * USD, 0.1463);

  Worth::WithholdingTable* holder = new Worth::WithholdingTable();
  holder->addFrequency(Worth::Biweekly, taxer);

  CA->addWithholder("SINGLE", holder);
  CA->addExemptionAllowance(1, Worth::Biweekly, 4.4 * USD);
  CA->addEstimatedDeduction(1, Worth::Biweekly, 38 * USD);
  CA->addLowIncomeExemption("SINGLE", Worth::Biweekly, 491 * USD);
  CA->addStandardDeduction("SINGLE", Worth::Biweekly, 148 * USD);

  EXPECT_DEATH(CA->getWithholder("MARRIED"), ".*");
  EXPECT_DEATH(CA->getExemptionAllowance(0, Worth::Daily), ".*");
  EXPECT_DEATH(CA->getLowIncomeExemption("SINGLE", Worth::Daily), ".*");
  EXPECT_DEATH(CA->getStandardDeduction("SINGLE", Worth::Daily), ".*");

  EXPECT_EQ(holder, CA->getWithholder("SINGLE"));
  EXPECT_EQ(4.4 * USD, CA->getExemptionAllowance(1, Worth::Biweekly));
  EXPECT_EQ(491 * USD, CA->getLowIncomeExemption("SINGLE", Worth::Biweekly));
  EXPECT_EQ(148 * USD, CA->getStandardDeduction("SINGLE", Worth::Biweekly));

  delete CA;
  CA = NULL;
}
