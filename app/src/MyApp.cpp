#include <MyApp.hpp>

#include "MainController.hpp"

#include <app/MainController.hpp>

namespace app {

void MyApp::app_setup() {
    uto main_controller = register_controller<MainController>();

    main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
}

}// namespace app