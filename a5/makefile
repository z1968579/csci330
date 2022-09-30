#
# PROGRAM:    Assignment 5
# PROGRAMMER: Jacob Rudawski
# LOGON ID:   z1968579
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
        
# Rule to link object code files to create executable file
dog: main.o dog.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rules to compile source code file to object code
main.o: main.cpp dog.h
	$(CXX) $(CXXFLAGS) -o $@ $^

dog.o: dog.cpp dog.h
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pseudo-target to remove object code and executable files
clean:
	rm -f dog *.o
