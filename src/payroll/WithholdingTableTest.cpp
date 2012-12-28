/*
 * WithholderTest.cpp
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
 */

#include <ql/currency.hpp>
#include <ql/currencies/america.hpp>
#include "worth/tax/TieredTaxer.h"
#include "worth/payroll/PayrollPeriods.h"
#include "worth/payroll/WithholdingTable.h"
#include "worth/Utility.h"
#include "gtest/gtest.h"

TEST(WithholdingTable, Empty) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::WithholdingTable holder;
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Daily,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Weekly,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Biweekly,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Semimonthly,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Monthly,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Quarterly,1 * USD), ".*");
  EXPECT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Semiannual,1 * USD), ".*");
  ASSERT_DEATH_IF_SUPPORTED(holder.getTax(Worth::Annual,1 * USD), ".*");
}

TEST(WithholdingTable, CaSingleBiweekly) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer* taxer = new Worth::TieredTaxer(USD);
  taxer->addTier(0 * USD, 0.011);
  taxer->addTier(286 * USD, 0.022);
  taxer->addTier(680 * USD, 0.044);
  taxer->addTier(1072 * USD, 0.066);
  taxer->addTier(1490 * USD, 0.088);
  taxer->addTier(1882 * USD, 0.1023);
  taxer->addTier(9616 * USD, 0.1133);
  taxer->addTier(11538 * USD, 0.1243);
  taxer->addTier(19230 * USD, 0.1353);
  taxer->addTier(38462 * USD, 0.1463);

  Worth::WithholdingTable holder;
  holder.addFrequency(Worth::Biweekly, taxer);
  QuantLib::Money tax = holder.getTax(Worth::Biweekly, 2466 * USD);
  tax == tax;
}

TEST(WithholdingTable, FactoryMethod) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::Utility* util = Worth::Utility::getInstance();

  //2013 numbers - single
  Worth::WithholdingTable* caSingle =
      Worth::WithholdingTable::generateWithholdingTable(
          util->readLines("data/2013_CA_SINGLE.txt.dat"), USD, 0.01);

  //2013 numbers - married
  Worth::WithholdingTable* caMarried =
      Worth::WithholdingTable::generateWithholdingTable(
          util->readLines("data/2013_CA_MARRIED.txt.dat"), USD, 0.01);

  //2013 numbers - hoh
  Worth::WithholdingTable* caHeadOfHousehold =
      Worth::WithholdingTable::generateWithholdingTable(
          util->readLines("data/2013_CA_HEADOFHOUSEHOLD.txt.dat"), USD, 0.01);

  delete caSingle;
  delete caMarried;
  delete caHeadOfHousehold;
}
