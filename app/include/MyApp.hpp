#ifndef MYAPP_HPP
#define MYAPP_HPP

#include <engine/core/Engine.hpp>

namespace app {
class MyApp final : public engine::core::App {
    void app_setup() override;
};
}// namespace app

#endif MYAPP_HPP