CXX = g++
SOURCE = main.cpp
TARGET = $(basename $(SOURCE)).exe
FLAGS = -Iinclude -Llib -lraylib -lgdi32 -lwinmm -lopengl32

$(TARGET): $(SOURCE)
	$(CXX) -o $@ $< $(FLAGS)

clean:
	rm $(TARGET)

run: $(TARGET)
	./$(TARGET)