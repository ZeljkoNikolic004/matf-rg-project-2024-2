#include "MyApp.hpp"
#include "MainController.hpp"
#include "GUIController.hpp"


namespace app {

void MyApp::app_setup() {
    auto main_controller = register_controller<MainController>();
    auto gui_controller = register_controller<GUIController>();

    main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    gui_controller->after(main_controller);
}

}// namespace app