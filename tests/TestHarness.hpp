/*
TestHarness.hpp - Mini framework for testing (without extern dependencies).
Every test executable includes this file.
 */

#pragma once

#include <cmath>
#include <cstdio>
#include <vector>

namespace test {

// A registered test case and the function that executes it.
struct Case {
    const char* name;
    void (*fn)();
};

// Stores all test cases registered during static initialization.
inline std::vector<Case>& Registry() {
    static std::vector<Case> registry;
    return registry;
}

// Stores the total number of failed checks across the test run.
inline int& FailureCount() {
    static int failures = 0;
    return failures;
}

// Registers a test case before main() starts.
struct Registrar {
    Registrar(const char* name, void (*fn)()) { Registry().push_back({name, fn}); }
};

// Reports a failed check with its source location.
inline void Fail(const char* file, int line, const char* message) {
    std::printf("    FAIL %s:%d  %s\n", file, line, message);
    ++FailureCount();
}

// Runs every registered test case and returns a process exit status.
inline int RunAll() {
    int failedCases = 0;
    for (const Case& c : Registry()) {
        const int before = FailureCount();
        c.fn();
        if (FailureCount() == before) {
            std::printf("[  OK  ] %s\n", c.name);
        } else {
            std::printf("  [ FAIL ] %s\n", c.name);
            ++failedCases;
        }
    }
    std::printf("%zu cases, %d failed\n", Registry().size(), failedCases);
    return failedCases == 0 ? 0 : 1;
}

} // namespace test

#define TEST_CASE(name)                                                                            \
    static void name();                                                                            \
    static ::test::Registrar registrar_##name(#name, &name);                                       \
    static void name()

#define CHECK(expr)                                                                                \
    do {                                                                                           \
        if (!(expr))                                                                               \
            ::test::Fail(__FILE__, __LINE__, "CHECK(" #expr ")");                                  \
    } while (0)

#define CHECK_NEAR(actual, expected, eps)                                                          \
    do {                                                                                           \
        const double check_a = static_cast<double>(actual);                                        \
        const double check_b = static_cast<double>(expected);                                      \
        const double check_e = static_cast<double>(eps);                                           \
        if (!(std::fabs(check_a - check_b) <= check_e)) {                                          \
            char check_buf[256];                                                                   \
            std::snprintf(check_buf, sizeof check_buf,                                             \
                          "CHECK_NEAR(%s, %s): %.6f vs %.6f (eps %.6g)", #actual, #expected,       \
                          check_a, check_b, check_e);                                              \
            ::test::Fail(__FILE__, __LINE__, check_buf);                                           \
        }                                                                                          \
    } while (0)
