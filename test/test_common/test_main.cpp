#include <unity.h>
#include <Arduino.h>


void setUp(void) {
    // Optional: Code to run before each test
}

void tearDown(void) {
    // Optional: Code to run after each test
}

/*
void test_addition(void) {
    TEST_ASSERT_EQUAL(3, addi.add(1, 2));  // Test if 1 + 2 equals 3
    TEST_ASSERT_EQUAL(0, addi.add(-1, 1)); // Test if -1 + 1 equals 0
    TEST_ASSERT_EQUAL(-2, addi.add(-1, -1)); // Test if -1 + -1 equals -2
}
*/

void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    //RUN_TEST(test_addition);
    UNITY_END();
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    RUN_UNITY_TESTS();
}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}
