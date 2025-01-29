CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = program

OBJECTS = main.o Student.o Teacher.o Course.o

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

Student.o: Student.cpp Student.h
	$(CXX) $(CXXFLAGS) -c Student.cpp

Teacher.o: Teacher.cpp Teacher.h
	$(CXX) $(CXXFLAGS) -c Teacher.cpp

Course.o: Course.cpp Course.h
	$(CXX) $(CXXFLAGS) -c Course.cpp

main.o: main.cpp Student.h Teacher.h Course.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)
