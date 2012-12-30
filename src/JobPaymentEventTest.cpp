/*
 * JobPaymentEventTest.cpp
 *
 * Created on: Dec 27, 2012
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

#include "worth/MyEvent.h"
#include "worth/JobPaymentEvent.h"
#include "gtest/gtest.h"

TEST(JobPaymentEvent, Empty) {
  Worth::JobPaymentEvent* evPtr = NULL;
  QuantLib::Date today = QuantLib::Date::todaysDate();
  EXPECT_DEATH_IF_SUPPORTED(new Worth::JobPaymentEvent(today, NULL), ".*");
}

TEST(JobPaymentEvent, ApplySequencerToEmptyJobPaymentEvent) {
  Worth::JobPaymentEvent* evPtr = NULL;
  QuantLib::Date today = QuantLib::Date::todaysDate();
  Worth::Sequencer* seq = new Worth::Sequencer(
      QuantLib::Date(1, QuantLib::January, 2011), today);
  // Worth::Job* job = new Worth::Job(NULL,)
  EXPECT_DEATH_IF_SUPPORTED(new Worth::JobPaymentEvent(today, NULL), ".*");
  seq->addEvent(evPtr);
  seq->run();
}
