# Nombre del ejecutable
TARGET = main.exe

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra -w

# Flags de linkeo (Raylib en Windows)
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -static 

# Directorio de fuentes
SRC_DIR = src

# Buscar todos los .cpp de forma recursiva (válido en MSYS2)
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Cómo generar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Cómo compilar cada archivo .cpp a .o
%.o: %.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa (recompila limpio antes)
run: clean all
	./$(TARGET)
	rm -f $(OBJ)

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(TARGET)

# Formatear código con clang-format
format:
	clang-format -i $(SRC)
