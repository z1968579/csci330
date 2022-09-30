#
# PROGRAM:    Assignment 3
# PROGRAMMER: Jacob Rudawski
# LOGON ID:   z1968579
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
        
# Rule to link object code files to create executable file
cat: cat.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pseudo-target to remove object code and executable files
clean:
	rm -f cat *.o
