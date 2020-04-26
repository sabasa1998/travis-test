CXX = g++
CXXFLAGS = -std=c++17 -Wall -c
LXXFLAGS = -std=c++17 
OBJECTS = main.o Matrix.o dataset.o neuralnet.o result.o aphw3.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.cpp Matrix.h dataset.h neuralnet.h result.h aphw3.h
	$(CXX) $(CXXFLAGS) main.cpp 
Matrix.o: Matrix.cpp 
	$(CXX) $(CXXFLAGS) Matrix.cpp 
dataset.o: dataset.cpp 
	$(CXX) $(CXXFLAGS) dataset.cpp 
neuralnet.o: neuralnet.cpp 
	$(CXX) $(CXXFLAGS) neuralnet.cpp 
result.o: result.cpp 
	$(CXX) $(CXXFLAGS) result.cpp 
aphw3.o: aphw3.cpp 
	$(CXX) $(CXXFLAGS) aphw3.cpp 
clean:
	rm -f $(TARGET) $(OBJECTS)
