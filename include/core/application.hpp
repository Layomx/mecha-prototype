#pragma once

#include <string_view>

namespace mecha::core {

[[nodiscard]] constexpr std::string_view project_name() noexcept { return "mecha-prototype"; }

} // namespace mecha::core
