#include <thread>
#include <condition_variable>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/app.hpp"
#include <ftxui/component/component.hpp>


void work_for_thread(ftxui::App& screen) {
    while (true) {
        screen.PostEvent(ftxui::Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(450));
    }
}

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
        if (event == Event::Custom) {
            if (!name.empty())
                name.pop_back();
            return true;
        }

        return false;
    });

    auto screen = App::FullscreenAlternateScreen();
    std::jthread my_thread(work_for_thread, std::ref(screen));
    screen.Loop(main);
    
    return 0;
}