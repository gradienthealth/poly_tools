CXX=g++
CXXFLAGS=-std=c++17 -Wall -I h -I /usr/local/include/gtest/ -I .

run_test: /build/test_main.o /build/test_vec3.o
    $(CXX) -o $@ test_main.cpp

./build/test_main.o: test/test_main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

./build/test_main.o: test/test_vec3.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) $(BUILD_DIR) $
