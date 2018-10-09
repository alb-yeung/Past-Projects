all:	CA5 Tester

CA5:	CA5.o CourseMap.o Course.o Student.o Reqs.o ReqsNode.o
	g++ CA5.o CourseMap.o Course.o Student.o Reqs.o ReqsNode.o -o CA5

CA5.o:	CA5.cpp Student.h
	g++ -c CA5.cpp Student.h

Tester:	Tester.o CourseMap.o Course.o Student.o Reqs.o ReqsNode.o
	g++ Tester.o CourseMap.o Course.o Student.o Reqs.o ReqsNode.o -o Tester

Tester.o:	Tester.cpp Student.h Reqs.h
	g++ -c Tester.cpp Student.h Reqs.h

Student.o:	Student.cpp Student.h
	g++ -c Student.cpp Student.h

CourseMap.o:	CourseMap.cpp CourseMap.h
	g++ -c CourseMap.cpp CourseMap.h

Course.o:	Course.cpp Course.h
	g++ -c Course.cpp Course.h

Reqs.o:	Reqs.cpp Reqs.h
	g++ -c Reqs.cpp Reqs.h

ReqsNode.o:	ReqsNode.cpp ReqsNode.h
	g++ -c ReqsNode.cpp ReqsNode.h

clean:
	rm -f *o *.gch Tester CA5
