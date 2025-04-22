#ifndef _EDIT_METADATA_CONTROLLER_HPP_
#define _EDIT_METADATA_CONTROLLER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../model/application.hpp"
#include "../view/edit_metadata_view.hpp"

class EditMetadataController {
    public:
        static void chooseMusicFile(Application& _app);
};

#endif //_EDIT_METADATA_CONTROLLER_HPP_