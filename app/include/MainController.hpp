#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <engine/core/Engine.hpp>
#include <glm/glm.hpp>

namespace app {

enum class State {
    Idle,
    WaitingForEventA,
    WaitingForEventB,
    Finished
};

class MainController final : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::MainController";
        }

    private:
        static const float A_SECONDS;
        static const float B_SECONDS;

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

        glm::vec3 m_dir_light_direction{-1.0f, -1.0f, -1.0f};
        glm::vec3 m_dir_light_color{0.0f, 1.0f, 0.0f};
        bool m_dir_light_enabled{true};

        glm::vec3 m_point_light_position{1.0f, 1.0f, 1.0f};
        glm::vec3 m_point_light_color{1.0f, 0.0f, 0.0f};
        bool m_point_light_enabled{true};

        bool m_scene_visible{true};

        State m_state{State::Idle};
        float m_event_a_time{0.0f};
        float m_event_b_time{0.0f};
};

}

#endif MAINCONTROLLER_HPP
