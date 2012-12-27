/*
 * WithholderTest.cpp
 *
 * Created on: Dec 22, 2012
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

#include <gtest/gtest.h>
#include <ql/currency.hpp>
#include <ql/money.hpp>
#include <ql/currencies/america.hpp>
#include "worth/tax/TieredTaxer.h"
#include "worth/payroll/WithholdingTable.h"
#include "worth/payroll/Withholder.h"
#include "worth/payroll/PayrollPeriods.h"
#include "worth/jurisdiction/State.h"
#include "worth/Utility.h"

class WithholderTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    Worth::State* CA12 = new Worth::State("CA", 2012, USD);
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

    Worth::WithholdingTable* singleholder = new Worth::WithholdingTable();
    singleholder->addFrequency(Worth::Biweekly, taxer);

    CA12->addWithholder("SINGLE", singleholder);

    CA12->addExemptionAllowance(1, Worth::Weekly, 2.16 * USD);
    CA12->addEstimatedDeduction(1, Worth::Weekly, 19 * USD);
    CA12->addLowIncomeExemption("SINGLE", Worth::Weekly, 241 * USD);
    CA12->addStandardDeduction("SINGLE", Worth::Weekly, 72 * USD);

    CA12->addExemptionAllowance(1, Worth::Biweekly, 4.32 * USD);
    CA12->addEstimatedDeduction(1, Worth::Biweekly, 38 * USD);
    CA12->addLowIncomeExemption("SINGLE", Worth::Biweekly, 482 * USD);
    CA12->addStandardDeduction("SINGLE", Worth::Biweekly, 145 * USD);

    withholderTwelve = new Worth::Withholder(CA12);

    Worth::State* CA13 = new Worth::State("CA", 2013, USD);
    Worth::Utility* util = Worth::Utility::getInstance();
    CA13->addWithholder(
        "SINGLE",
        Worth::WithholdingTable::generateWithholdingTable(
            util->readLines("data/2013_CA_SINGLE.txt.dat"), USD, 0.01));
    CA13->addWithholder(
        "MARRIED",
        Worth::WithholdingTable::generateWithholdingTable(
            util->readLines("data/2013_CA_MARRIED.txt.dat"), USD, 0.01));
    CA13->addWithholder(
        "HEADOFHOUSEHOLD",
        Worth::WithholdingTable::generateWithholdingTable(
            util->readLines("data/2013_CA_HEADOFHOUSEHOLD.txt.dat"), USD, 0.01));

    Worth::State::AllowanceFrequencyTable estimatedTable =
          Worth::State::generateAllowanceFrequencyTable(
              util->readLines("data/2013_CA_ESTIMATED_DEDUCTION.txt.dat"), USD);
    CA13->addEstimatedDeductions(estimatedTable.begin(), estimatedTable.end());

    Worth::State::AllowanceFrequencyTable exemptionTable =
        Worth::State::generateAllowanceFrequencyTable(
            util->readLines("data/2013_CA_EXEMPTION_ALLOWANCE.txt.dat"), USD);
    CA13->addExemptionAllowances(exemptionTable.begin(), exemptionTable.end());

    Worth::State::StatusFrequencyTable lowIncomeTable =
        Worth::State::generateStatusFrequencyTable(
            util->readLines("data/2013_CA_LOW_INCOME.txt.dat"), USD);
    CA13->addLowIncomeExemptions(lowIncomeTable.begin(), lowIncomeTable.end());

    Worth::State::StatusFrequencyTable standardDeductionTable =
          Worth::State::generateStatusFrequencyTable(
              util->readLines("data/2013_CA_STANDARD_DEDUCTION.txt.dat"), USD);
    CA13->addStandardDeductions(standardDeductionTable.begin(), standardDeductionTable.end());

    withholderThirteen = new Worth::Withholder(CA13);

    Worth::State* US = new Worth::State("US", 2012, USD);

    US->addWithholder(
        "SINGLE",
        Worth::WithholdingTable::generateWithholdingTable(
            util->readLines("data/2012_US_SINGLE.txt.dat"), USD, 0.01));
    US->addWithholder(
        "MARRIED",
        Worth::WithholdingTable::generateWithholdingTable(
            util->readLines("data/2012_US_MARRIED.txt.dat"), USD, 0.01));
    Worth::State::AllowanceFrequencyTable exemptionTableUS =
        Worth::State::generateAllowanceFrequencyTable(
            util->readLines("data/2012_US_WITHHOLDING_ALLOWANCE.txt.dat"), USD);
    US->addWithholdingAllowances(exemptionTableUS.begin(), exemptionTableUS.end());

    usWithhold = new Worth::Withholder(US);
  }

  virtual void TearDown() {
    delete withholderTwelve;
    withholderTwelve = NULL;
    delete withholderThirteen;
    withholderThirteen = NULL;
    delete usWithhold;
    usWithhold = NULL;
  }

  Worth::Withholder* withholderTwelve;
  Worth::Withholder* withholderThirteen;
  Worth::Withholder* usWithhold;
  QuantLib::USDCurrency USD;
};

TEST_F(WithholderTest, SingleCA2012) {
  QuantLib::Money actual = 0 * USD;
  QuantLib::Money wages = 2466 * USD;
  Worth::FilingStatus status("SINGLE");
  actual = withholderTwelve->computeWithholding(wages, Worth::Biweekly, status, 1, 4, 0);
  double actualValue = actual.value();

  //stub said 117.88
  EXPECT_NEAR(
      117.60,
      actualValue,
      0.005);
}

TEST_F(WithholderTest, SingleCA2013LowIncome) {
  //below low income limit so zero withholdings
  EXPECT_NEAR(
      0.00,
      withholderThirteen->computeWithholding(210 * USD, Worth::Biweekly, "SINGLE", 1, 4, 0).value(),
      0.005);
}

TEST_F(WithholderTest, MySingleCA2013) {
  EXPECT_NEAR(
      115.59,
      withholderThirteen->computeWithholding(2466 * USD, Worth::Biweekly, "SINGLE", 1, 4, 0).value(),
      0.005);
}

TEST_F(WithholderTest, MarriedMonthly2013) {
  EXPECT_NEAR(
      12.83,
      withholderThirteen->computeWithholding(3800 * USD, Worth::Monthly, "MARRIED", 5, 0, 0).value(),
      0.005);
}

TEST_F(WithholderTest, HeadOfHouseholdWeekly2013) {
  EXPECT_NEAR(
      4.59,
      withholderThirteen->computeWithholding(800 * USD, Worth::Weekly, "HEADOFHOUSEHOLD", 3, 0, 0).value(),
      0.005);
}

TEST_F(WithholderTest, MarriedSemimonthly2013) {
  EXPECT_NEAR(
      6.81,
      withholderThirteen->computeWithholding(1800 * USD, Worth::Semimonthly, "MARRIED", 4, 0, 0).value(),
      0.03);
}

TEST_F(WithholderTest, SingleWeeklyUs2012) {
  EXPECT_NEAR(
      53.53,
      usWithhold->computeWithholding(600 * USD, Worth::Weekly, "SINGLE", 0, 0, 2).value(),
      0.01);
}

TEST_F(WithholderTest, MarriedWeeklyUs2012Annual) {
  EXPECT_NEAR(
      66.02,
      usWithhold->computeWithholding(1000 * USD, Worth::Weekly, "MARRIED", 0, 0, 4, true).value(),
      0.04);
}

TEST_F(WithholderTest, MarriedAnnualMonthly2013) {
  EXPECT_NEAR(
      20.22,
      withholderThirteen->computeWithholding(3750 * USD, Worth::Monthly, "MARRIED", 4, 0, 0, true).value(),
      0.01);
}
