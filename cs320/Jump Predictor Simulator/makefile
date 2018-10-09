all: Tester

Tester:	Predictor.o Predict.o
	g++ Predictor.o Predict.o -o predictors

Predict.o:	Predict.cpp
	g++ -c Predict.cpp

Predictor.o:	Predictor.cpp Predictor.h
	g++ -c Predictor.cpp Predictor.h

clean:
	rm predictors
