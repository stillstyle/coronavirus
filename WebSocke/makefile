#FileName: Makefile  
#Compile cmd: make  
  
CC  = gcc  
CPP = g++  
CXX = gcc  
EXECUTABLE = websocket  
  
all:$(EXECUTABLE)
	rm -f *.o  
  
clean:
	rm -f *.o $(EXECUTABLE)  
  
$(EXECUTABLE):iot_string.o iot_sha1.o iot_config.o iot_websocket.o iot_websocket_unittest.o
	$(CC) -o $@ $^ -lm -lpthread  
  
%.o:%.c  
	$(CC)  -c $< -o $@  
