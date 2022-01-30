//
// Created by cleve on 1/30/2022.
//

#include "buffer/clock_replacer.h"
#include <gtest/gtest.h>

// Test cases from CMU BusTub

TEST(ClockReplacerTest, ClockReplacerTest)
{
	barrel::buffer::clock_replacer clock_replacer(7);

	// Scenario: unpin six elements, i.e. add them to the replacer.
	clock_replacer.unpin(1);
	clock_replacer.unpin(2);
	clock_replacer.unpin(3);
	clock_replacer.unpin(4);
	clock_replacer.unpin(5);
	clock_replacer.unpin(6);
	clock_replacer.unpin(1);
	EXPECT_EQ(6, clock_replacer.size());

	// Scenario: get three victims from the clock.

	auto val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 1);

	val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 2);

	val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 3);

	// Scenario: pin elements in the replacer.
	// Note that 3 has already been victimized, so pinning 3 should have no effect.
	clock_replacer.pin(3);
	clock_replacer.pin(4);
	EXPECT_EQ(2, clock_replacer.size());

	// Scenario: unpin 4. We expect that the reference bit of 4 will be set to 1.
	clock_replacer.unpin(4);
	EXPECT_EQ(clock_replacer.reference(4), 1);

	// Scenario: continue looking for victims. We expect these victims.
	val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 5);

	val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 6);

	val = clock_replacer.victim();
	EXPECT_EQ(val.has_value(), true);
	EXPECT_EQ(val.value(), 4);
}