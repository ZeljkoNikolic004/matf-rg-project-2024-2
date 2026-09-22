#include "MyApp.hpp"
#include "MainController.hpp"


namespace app {

void MyApp::app_setup() {
    auto main_controller = register_controller<MainController>();

    main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
}

}// namespace app