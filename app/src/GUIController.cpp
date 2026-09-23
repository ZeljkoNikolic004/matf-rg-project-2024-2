#include "GUIController.hpp"
#include "MainController.hpp"
#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <imgui.h>

namespace app {

void GUIController::initialize() {
    set_enable(false);
}

void GUIController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if (platform->key(engine::platform::KEY_F2).state() == engine::platform::Key::State::JustPressed) {
        set_enable(!is_enabled());
    }
}

void GUIController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto main = engine::core::Controller::get<MainController>();

    graphics->begin_gui();

    ImGui::Begin("Lighting");

    ImGui::Text("Directional light");
    ImGui::Checkbox("Directional enabled", &main->m_dir_light_enabled);
    ImGui::ColorEdit3("Directional color", &main->m_dir_light_color[0]);
    ImGui::DragFloat3("Directional direction", &main->m_dir_light_direction[0],
                      0.05f, -1.0f, 1.0f);

    ImGui::Separator();

    ImGui::Text("Point light");
    ImGui::Checkbox("Point enabled", &main->m_point_light_enabled);
    ImGui::ColorEdit3("Point color", &main->m_point_light_color[0]);
    ImGui::DragFloat3("Point position", &main->m_point_light_position[0], 0.1f);

    ImGui::Separator();
    ImGui::Text("Event (SPACE = start, R = reset)");
    if (main->m_scene_visible) {
        ImGui::Text("Scene visible: yes");
    } else {
        ImGui::Text("Scene visible: no");
    }


    ImGui::End();
    graphics->end_gui();
}

}// namespace app