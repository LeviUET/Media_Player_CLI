# Compiler
CXX = g++
# Compiler flags: using C++17, show all warnings, and include the model and view directories
CXXFLAGS = -std=c++17 -Wall -I./model -I./view
# Linker flags: link SDL2, SDL2_mixer, and TagLib libraries
LDFLAGS = -lSDL2 -lSDL2_mixer -lSDL2_ttf -ltag

# List all source files
SRCS = main.cpp \
       model/application.cpp \
	   model/mediafile.cpp \
	   model/metadata.cpp \
	   model/playlist.cpp \
	   controller/general_controller.cpp \
	   controller/playmusic_controller.cpp \
	   controller/media_player_controller.cpp \
	   controller/playlist_controller.cpp \
	   controller/edit_metadata_controller.cpp \
	   controller/edit_metadata_menu_controller.cpp \
	   controller/hardware_controller.cpp \
	   view/general_view.cpp \
	   view/playmusic_view.cpp \
	   view/home_view.cpp \
	   view/display_song_view.cpp \
	   view/media_player_view.cpp \
	   view/playlist_view.cpp \
	   view/edit_metadata_view.cpp \
	   view/edit_metadata_menu_view.cpp \
	   view/hardware_view.cpp \
	   

# Convert source file names to object file names
OBJS = $(SRCS:.cpp=.o)

# Name of the final executable
TARGET = main

# Default rule
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
