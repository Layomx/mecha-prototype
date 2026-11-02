#include "core/application.hpp"

#include <cassert>

// Keeps the project identity stable while the application layer is being built.
int main() {
    assert(mecha::core::project_name() == "mecha-prototype");
    return 0;
}
