OBJ = import.o dl.o repo.o
TARGET = import

CXXFLAGS += -g -I simpleini -I/usr/include/libxml2
LDFLAGS += -lxml2 -lz -lm -l curl

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ -o $(TARGET) $(OBJ) $(LDFLAGS)
# -L simpleini -lini

clean:
	rm -f $(TARGET) $(OBJ)
