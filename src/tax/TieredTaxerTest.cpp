/*
 * TieredTaxerTest.cpp
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
#include "gtest/gtest.h"

TEST(TieredTaxer, Empty) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer taxer(USD);

  //test compute tax
  EXPECT_EQ(0*USD, taxer.computeTax(0 * USD));
  EXPECT_EQ(0*USD, taxer.computeTax(1 * USD));

  //test compute marginal rate
  EXPECT_EQ(0, taxer.computeMarginalRate(0*USD));
  EXPECT_EQ(0, taxer.computeMarginalRate(1*USD));

  //test compute effective rate
  EXPECT_EQ(0, taxer.computeEffectiveRate(0 * USD));
  EXPECT_EQ(0, taxer.computeEffectiveRate(1 * USD));
}

TEST(TieredTaxer, NoUpperBound) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer taxer(USD);
  taxer.addTier(0 * USD, 0.1);

  //test compute tax
  EXPECT_EQ(0*USD, taxer.computeTax(0 * USD));
  EXPECT_EQ(0.1*USD, taxer.computeTax(1 * USD));

  //test compute marginal rate
  EXPECT_EQ(0.1, taxer.computeMarginalRate(0*USD));
  double rate = 0.0;
  QuantLib::Money oneDollar = 1*USD;
  rate = taxer.computeMarginalRate(oneDollar);
  EXPECT_EQ(0.1, rate);

  //test compute effective rate
  EXPECT_EQ(0, taxer.computeEffectiveRate(0 * USD));
  EXPECT_EQ(0.1, taxer.computeEffectiveRate(1 * USD));
}

TEST(TieredTaxer, WithUpperBound) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer taxer(USD);
  taxer.addTier(0 * USD, 0.1);
  taxer.addTier(10 * USD, 0.0);

  //test compute tax
  EXPECT_EQ(0*USD, taxer.computeTax(0 * USD));
  EXPECT_EQ(0.1*USD, taxer.computeTax(1 * USD));

  //test compute marginal rate
  EXPECT_EQ(0.1, taxer.computeMarginalRate(0*USD));
  double rate = taxer.computeMarginalRate(1*USD);
  EXPECT_EQ(0.1, rate);

  //test compute effective rate
  EXPECT_EQ(0, taxer.computeEffectiveRate(0 * USD));
  EXPECT_EQ(0.1, taxer.computeEffectiveRate(1 * USD));
}

TEST(TieredTaxer, FactoryMethod) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer* taxer = Worth::TieredTaxer::generateTieredTaxer("0 1.100 286 2.200 680 4.400 1072 6.600 1490 8.800 1882 10.230 9616 11.330 11538 12.430 19230 13.530 38462 14.630", USD, 0.01);

  //test compute marginal rate
  EXPECT_NEAR(0.011, taxer->computeMarginalRate(0*USD), 0.001);
  EXPECT_NEAR(0.011, taxer->computeMarginalRate(100*USD), 0.001);

  EXPECT_NEAR(0.022, taxer->computeMarginalRate(286*USD), 0.001);
  EXPECT_NEAR(0.022, taxer->computeMarginalRate(300*USD), 0.001);

  EXPECT_NEAR(0.044, taxer->computeMarginalRate(680*USD), 0.001);
  EXPECT_NEAR(0.044, taxer->computeMarginalRate(700*USD), 0.001);

  EXPECT_NEAR(0.066, taxer->computeMarginalRate(1072*USD), 0.001);
  EXPECT_NEAR(0.066, taxer->computeMarginalRate(1100*USD), 0.001);

  EXPECT_NEAR(0.088, taxer->computeMarginalRate(1490*USD), 0.001);
  EXPECT_NEAR(0.088, taxer->computeMarginalRate(1500*USD), 0.001);

  EXPECT_EQ(0.1023, taxer->computeMarginalRate(1882*USD));
  EXPECT_EQ(0.1023, taxer->computeMarginalRate(1900*USD));

  EXPECT_EQ(0.1133, taxer->computeMarginalRate(9616*USD));
  EXPECT_EQ(0.1133, taxer->computeMarginalRate(9700*USD));

  EXPECT_EQ(0.1243, taxer->computeMarginalRate(11538*USD));
  EXPECT_EQ(0.1243, taxer->computeMarginalRate(11600*USD));

  EXPECT_EQ(0.1353, taxer->computeMarginalRate(19230*USD));
  EXPECT_EQ(0.1353, taxer->computeMarginalRate(19300*USD));

  EXPECT_EQ(0.1463, taxer->computeMarginalRate(38462*USD));
  EXPECT_EQ(0.1463, taxer->computeMarginalRate(38500*USD));

  delete taxer;
}

TEST(TieredTaxer, FullTiers) {
  QuantLib::Currency USD = QuantLib::USDCurrency();
  Worth::TieredTaxer taxer(USD);
  taxer.addTier(0 * USD, 0.011);
  taxer.addTier(286 * USD, 0.022);
  taxer.addTier(680 * USD, 0.044);
  taxer.addTier(1072 * USD, 0.066);
  taxer.addTier(1490 * USD, 0.088);
  taxer.addTier(1882 * USD, 0.1023);
  taxer.addTier(9616 * USD, 0.1133);
  taxer.addTier(11538 * USD, 0.1243);
  taxer.addTier(19230 * USD, 0.1353);
  taxer.addTier(38462 * USD, 0.1463);

  //test compute marginal rate
  EXPECT_EQ(0.011, taxer.computeMarginalRate(0*USD));
  EXPECT_EQ(0.011, taxer.computeMarginalRate(100*USD));

  EXPECT_EQ(0.022, taxer.computeMarginalRate(286*USD));
  EXPECT_EQ(0.022, taxer.computeMarginalRate(300*USD));

  EXPECT_EQ(0.044, taxer.computeMarginalRate(680*USD));
  EXPECT_EQ(0.044, taxer.computeMarginalRate(700*USD));

  EXPECT_EQ(0.066, taxer.computeMarginalRate(1072*USD));
  EXPECT_EQ(0.066, taxer.computeMarginalRate(1100*USD));

  EXPECT_EQ(0.088, taxer.computeMarginalRate(1490*USD));
  EXPECT_EQ(0.088, taxer.computeMarginalRate(1500*USD));

  EXPECT_EQ(0.1023, taxer.computeMarginalRate(1882*USD));
  EXPECT_EQ(0.1023, taxer.computeMarginalRate(1900*USD));

  EXPECT_EQ(0.1133, taxer.computeMarginalRate(9616*USD));
  EXPECT_EQ(0.1133, taxer.computeMarginalRate(9700*USD));

  EXPECT_EQ(0.1243, taxer.computeMarginalRate(11538*USD));
  EXPECT_EQ(0.1243, taxer.computeMarginalRate(11600*USD));

  EXPECT_EQ(0.1353, taxer.computeMarginalRate(19230*USD));
  EXPECT_EQ(0.1353, taxer.computeMarginalRate(19300*USD));

  EXPECT_EQ(0.1463, taxer.computeMarginalRate(38462*USD));
  EXPECT_EQ(0.1463, taxer.computeMarginalRate(38500*USD));
}
