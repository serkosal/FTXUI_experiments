#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/app.hpp"
#include <ftxui/component/component.hpp>


int main() { 
    using namespace ftxui;
    std::string name = "name";
    ftxui::Component input_name = ftxui::Input(&name, "name");
    auto container = Container::Vertical({
        input_name
    });
    auto renderer = Renderer(container, [&]{
        return vbox({
            hbox(text("First name: "), input_name->Render()),
        }) | border;
    });
    auto main = renderer | CatchEvent( [&](Event event) {
        if (event == Event::Character('q')) {
            name += "\nYou've pressed Q!";
            return true;
        }
        return false;
    });

    auto screen = App::FullscreenAlternateScreen();
    screen.Loop(main);
    
    return 0;
}