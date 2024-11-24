




SERVER_SOURCES=server.cpp tcpserver.cpp ccsocket.cpp MultimediaObject.cpp Film.cpp Group.cpp Administrator.cpp

SERVER_OBJETS=${SERVER_SOURCES:%.cpp=%.o}

CXX=c++

CXXFLAGS = -std=c++11 -Wall -g -I/usr/local/qt/include -I/usr/include -I/usr/local/include

LDLIBS= -lpthread

all: ${CLIENT} ${SERVER}

run: ${SERVER}
	./${SERVER}


${SERVER}: depend-${SERVER} ${SERVER_OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${SERVER_OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o depend-${SERVER} core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) -${SERVER} 1>/dev/null 2>&1


depend-${SERVER}:
	${CXX} ${CXXFLAGS} -MM ${SERVER_SOURCES} > depend-${SERVER}

###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${SERVER}

