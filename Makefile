all:
	$(CXX) $(CXXFLAGS) -pg hves_logger.c can.c time_ms.c file.c canlog.c candata.c -g -o hves_logger.bin
	
	