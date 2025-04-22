#ifndef _EDIT_METADATA_MENU_CONTROLLER_HPP_
#define _EDIT_METADATA_MENU_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"

class EditMetadataMenuController {
    public:
        static void editTitle(Application& _app);
        static void editArtist(Application& _app);
        static void editYear(Application& _app);
        static void editGenre(Application& _app);
};

#endif //_EDIT_METADATA_CONTROLLER_HPP_