all:
	$(CXX) $(CXXFLAGS) -Og hves_logger.c can.c time_ms.c -g -o hves_logger.bin
	