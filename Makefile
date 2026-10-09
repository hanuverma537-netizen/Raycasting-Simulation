CXX = g++
SOURCE = main.cpp Player/Player.cpp Arena/Arena.cpp Arena/Wall.cpp
TARGET = $(basename $(firstword $(SOURCE))).exe
FLAGS = -Iinclude -Llib -lraylib -lgdi32 -lwinmm -lopengl32

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $^ $(FLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)