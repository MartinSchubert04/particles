# Nombre del ejecutable
TARGET = main

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# Flags de linkeo
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

# Archivos fuente
SRCS = src/main.cpp

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Cómo generar el ejecutable a partir de los objetos
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Cómo compilar cada .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	rm -f $(OBJS) $(TARGET)
	$(MAKE) $(TARGET)
	./$(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Formatear código con clang-format
format:
	clang-format -i $(SRCS) utils.h

