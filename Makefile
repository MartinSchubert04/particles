# Nombre del ejecutable
TARGET = main.exe

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# Flags de linkeo (Raylib en Windows)
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Archivos fuente
SRCS = src/main.cpp

# Archivos objeto
OBJS = src/main.o

# Regla por defecto
all: $(TARGET)

# Cómo generar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Cómo compilar cada archivo .cpp a .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa (recompila limpio antes)
run:
	$(MAKE) $(TARGET)
	./$(TARGET)

# Limpiar archivos generados
clean:
	del /Q $(OBJS) $(TARGET) 2>nul || true

# Formatear código con clang-format
format:
	clang-format -i $(SRCS)
