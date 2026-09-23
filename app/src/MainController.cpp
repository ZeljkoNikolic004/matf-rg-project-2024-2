#include "MainController.hpp"
#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <spdlog/spdlog.h>

namespace app {

void MainController::initialize() {
    engine::graphics::OpenGL::enable_depth_testing();
}

bool MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if (platform->key(engine::platform::KEY_ESCAPE).state() == engine::platform::Key::State::JustPressed) {
        return false;
    }

    return true;
}

void MainController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if (platform->key(engine::platform::KEY_F1).state() == engine::platform::Key::State::JustPressed) {
        m_cursor_enabled = !m_cursor_enabled;
        platform->set_enable_cursor(m_cursor_enabled);
    }

    if (platform->key(engine::platform::KEY_SPACE).state() == engine::platform::Key::State::JustPressed &&
        m_state == State::Idle) {
        m_event_a_time = platform->frame_time().current;
        m_state = State::WaitingForEventA;

        spdlog::info("ACTION_X: event started, EVENT_A in {} seconds", A_SECONDS);
    }

    if (platform->key(engine::platform::KEY_R).state() == engine::platform::Key::State::JustPressed) {
        m_state = State::Idle;
        m_scene_visible = true;
        m_point_light_color = glm::vec3{1.0f};

        spdlog::info("Event chain reset");
    }
}

void MainController::update() {
    update_camera();
    update_event();
}

void MainController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

void MainController::draw() {
    if (m_scene_visible) {
        draw_scene();
    }
}

void MainController::end_draw() {
    engine::core::Controller::get<engine::platform::PlatformController>()->swap_buffers();
}

void MainController::update_camera() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    float dt = platform->dt();

    if (platform->key(engine::platform::KEY_W).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
    }
    if (platform->key(engine::platform::KEY_S).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
    }
    if (platform->key(engine::platform::KEY_A).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
    }
    if (platform->key(engine::platform::KEY_D).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
    }

    auto mouse = platform->mouse();
    camera->rotate_camera(mouse.dx, mouse.dy);
    camera->zoom(mouse.scroll);
}

void MainController::draw_scene() {
    auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto shader = resources->shader("scene");
    auto scene = resources->model("scene");

    shader->use();
    shader->set_mat4("model", glm::mat4(1.0f));
    shader->set_mat4("view", graphics->camera()->view_matrix());
    shader->set_mat4("projection", graphics->projection_matrix());

    shader->set_vec3("viewPos", graphics->camera()->Position);

    shader->set_bool("dirLight.enabled", m_dir_light_enabled);
    shader->set_vec3("dirLight.direction", m_dir_light_direction);
    shader->set_vec3("dirLight.color", m_dir_light_color);

    shader->set_bool("pointLight.enabled", m_point_light_enabled);
    shader->set_vec3("pointLight.position", m_point_light_position);
    shader->set_vec3("pointLight.color", m_point_light_color);

    scene->draw(shader);
}

void MainController::update_event() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    float now = platform->frame_time().current;

    if (m_state == State::WaitingForEventA && now - m_event_a_time >= A_SECONDS) {
        m_point_light_color = glm::vec3{1.0f, 0.0f, 0.0f};
        m_event_b_time = now;
        m_state = State::WaitingForEventB;

        spdlog::info("EVENT_A: point light color changed to red, EVENT_B in {} seconds", B_SECONDS);
    }

    if (m_state == State::WaitingForEventB && now - m_event_b_time >= B_SECONDS) {
        m_scene_visible = false;
        m_state = State::Finished;

        spdlog::info("EVENT_B: scene model hidden");
    }
}

}// namespace app