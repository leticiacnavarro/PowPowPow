TARGET=trabalhocg
CXX=g++
LD=g++
OBJS=main.cpp iniciacao.cpp lutador.cpp menu.cpp
LIBS=tinyxml/tinyxml.cpp tinyxml/tinystr.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp
nomedoprograma:$(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LIBS) -lGL -lGLU -lglut
clean:
	rm -f *.o *~

