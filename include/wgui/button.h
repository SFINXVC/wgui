#ifndef WGUI__BUTTON_H
#define WGUI__BUTTON_H

#include "control.h"

#include <string_view>

namespace wgui
{
    class button : public control
    {
    public:
        button(control* parent, std::string_view text);

        void set_text(std::string_view text);
        std::string get_text() const;
    
        bool create(control* parent, std::string_view text);
    };
}

#endif // WGUI__BUTTON_H