SERVER=server

SERVER_SOURCES=server.cpp tcpserver.cpp ccsocket.cpp MultimediaObject.cpp Film.cpp Group.cpp Administrator.cpp
SERVER_OBJETS=${SERVER_SOURCES:%.cpp=%.o}

CXX=c++
CXXFLAGS = -std=c++11 -Wall -g -I/usr/local/qt/include -I/usr/include -I/usr/local/include
LDLIBS= -lpthread

all: ${SERVER}

run: ${SERVER}
	./${SERVER}

${SERVER}: depend-${SERVER} ${SERVER_OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${SERVER_OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o depend-${SERVER} server core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${SERVER} 1>/dev/null 2>&1

depend-${SERVER}:
	${CXX} ${CXXFLAGS} -MM ${SERVER_SOURCES} > depend-${SERVER}

# Règles implicites
.SUFFIXES: .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Inclusion des dépendances
-include depend-${SERVER}
