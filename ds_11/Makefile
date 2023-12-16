CXX=g++
TARGET=main1

run: $(TARGET)
	./$(TARGET)

$(TARGET): main1.cpp
	$(CXX) main1.cpp -o $(TARGET) -pthread

clean:
	rm -f $(TARGET)
