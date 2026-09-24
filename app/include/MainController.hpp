#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <engine/core/Engine.hpp>
#include <glm/glm.hpp>

namespace app {

enum class State {
    Idle,
    ChangingPointLightColor,
    RemovingScene,
    Finished
};

struct DirLight {
    bool enabled{true};
    glm::vec3 direction{-1.0f, -1.0f, -1.0f};
    glm::vec3 ambient{0.06f, 0.06f, 0.06f};
    glm::vec3 diffuse{0.6f, 0.6f, 0.6f};
    glm::vec3 specular{0.2f, 0.2f, 0.2f};

    void set_color(const glm::vec3 &color) {
        diffuse = color;
        ambient = color * 0.1f;
        specular = color * 0.3f;
    }
};

struct PointLight {
    bool enabled{true};
    glm::vec3 position{1.0f, 3.0f, 0.0f};
    glm::vec3 ambient{0.05f, 0.05f, 0.05f};
    glm::vec3 diffuse{1.0f, 1.0f, 1.0f};
    glm::vec3 specular{0.3f, 0.3f, 0.3f};

    void set_color(const glm::vec3 &color) {
        diffuse = color;
        ambient = color * 0.05f;
        specular = color * 0.3f;
    }
};

class MainController final : public engine::core::Controller {
    friend class GUIController;

public:
    std::string_view name() const override {
        return "app::MainController";
    }

private:
    inline static const float A_SECONDS = 2.0f;
    inline static const float B_SECONDS = 3.0f;

    void initialize() override;
    bool loop() override;
    void poll_events() override;
    void update() override;
    void begin_draw() override;
    void draw() override;
    void end_draw() override;

    void update_camera();
    void draw_scene();

    void update_event();

    bool m_cursor_enabled{true};

    DirLight m_dir_light{};
    PointLight m_point_light{};

    bool m_scene_visible{true};

    State m_state{State::Idle};
    float m_event_a_time{0.0f};
    float m_event_b_time{0.0f};
};

}// namespace app

#endif MAINCONTROLLER_HPP
