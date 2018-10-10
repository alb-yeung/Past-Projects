#ifndef DEQUE_HPP
#define DEQUE_HPP

/*
#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <typeinfo>

#define xyzzy_check(e) do {                                                    \
    if (!(e)) {                                                                \
        const char s[] = #e "\n";                                              \
        write(2, s, sizeof s);                                                 \
        abort();                                                               \
    }                                                                          \
} while (0)

size_t alloc_call_count;
size_t total_bytes_allocated;

namespace {
    bool initialized;
    void *(*default_malloc)(size_t);
    void *(*default_realloc)(void *, size_t);
    void *(*default_calloc)(size_t, size_t);
    void
    alloc_init() {
        if (!initialized) {
            // Cast through int to avoid warnings on some versions of g++.
            default_malloc = (void*(*)(size_t)) (uintptr_t) dlsym(RTLD_NEXT, "malloc"); xyzzy_check(default_malloc != nullptr);
            default_realloc = (void*(*)(void*,size_t)) (uintptr_t) dlsym(RTLD_NEXT, "realloc"); xyzzy_check(default_realloc != nullptr);
            default_calloc = (void*(*)(size_t,size_t)) (uintptr_t) dlsym(RTLD_NEXT, "calloc"); xyzzy_check(default_calloc != nullptr);
            initialized = true;
        }
    }
}

void *
malloc(size_t size) {
    alloc_init();
    void *ptr = default_malloc(size);
    alloc_call_count++;
    total_bytes_allocated += size;
    return ptr;
}
*/
/*
 * Implement your functionality here without changing test.cpp
 */

/*
	.size()
	.push_back()
	.push_front()
	.front()
	.back()
	.pop_front()
	.pop_back()
	.begin()


	name_print
	Deque_name_Iterator
	Deque_name_Iterator_equal



struct MyClass {
    int id;
    char name[10];
};
*/
#define Deque_DEFINE(t)														\
	struct Deque_##t##_Iterator;											\
	struct Deque_##t {														\
		int max;															\
		int sizeV;															\
		int frontV;															\
		int backV;															\
		t * deque;															\
		bool (*less_than) (const t &o1, const t &o2);						\
		size_t (*size) (Deque_##t * deq);									\
		bool (*empty) (Deque_##t * deq);									\
		const char* type_name;												\
		void (*push_back) (Deque_##t * deq, t a);							\
		void (*push_front) (Deque_##t * deq, t a);							\
		t & (*front) (Deque_##t * deq);										\
		t & (*back) (Deque_##t * deq);										\
		t & (*at) (Deque_##t * deq, int i);									\
		void (*pop_front) (Deque_##t * deq);								\
		void (*pop_back) (Deque_##t * deq);									\
		Deque_##t##_Iterator & (*begin) (Deque_##t * deq);					\
		Deque_##t##_Iterator & (*end) (Deque_##t * deq);					\
		void (*clear) (Deque_##t * deq);									\
		void (*dtor) (Deque_##t * deq);										\
	};																		\
																			\
	struct Deque_##t##_Iterator{											\
		int frontV;															\
		int backV;															\
		int max;															\
		t ** deque;															\
		int atV;															\
		void (*inc)(Deque_##t##_Iterator * it);								\
		void (*dec)(Deque_##t##_Iterator * it);								\
		t & (*deref) (Deque_##t##_Iterator * it);							\
	};																		\
																			\
	size_t t##_Deque_size(Deque_##t * deq){									\
		return (size_t)deq->sizeV;											\
	}																		\
																			\
	bool t##_empty(Deque_##t * deq){										\
		return deq->sizeV == 0;												\
	}																		\
																			\
	void t##_push_front(Deque_##t * deq, t a){								\
		if (deq->sizeV == 0){												\
			deq->deque[deq->frontV] = a;									\
			deq->sizeV++;													\
			return;															\
		}																	\
		if (deq->sizeV < deq->max){											\
			deq->frontV = (deq->frontV-1);									\
			if (deq->frontV == -1) deq->frontV = deq->max - 1;				\
			deq->deque[deq->frontV] = a;									\
			deq->sizeV++;													\
		}else{																\
			if (deq->frontV < deq->backV){									\
				t * temp = deq->deque;										\
				deq->deque = ( t *)realloc((void *)temp, (deq->max * 10)*sizeof( t ));						\
				deq->max *= 10;																				\
			}else{																							\
				t * temp = deq->deque;																		\
				int j = deq->max - deq->frontV;																\
				deq->deque = ( t *)malloc((deq->max*10)*sizeof( t ));										\
				deq->max *= 10;																				\
																											\
				for(int i = 0; i < deq->backV + 1; i++){													\
					deq->deque[i] = temp[i];																\
				}																							\
				for(int i = 0; i < j + 1; i++){																\
					deq->deque[deq->max - (i + 1)] = temp[(deq->max/10) - (i + 1)];							\
				}																							\
				deq->frontV = deq->max - j;																	\
				delete [] temp;																				\
			}																								\
			deq->frontV = (deq->frontV - 1)%deq->max;														\
			if (deq->frontV == -1) deq->frontV = deq->max - 1;												\
			deq->deque[deq->frontV] = a;																	\
			deq->sizeV++;																					\
		}																									\
	}																										\
																											\
	void t##_push_back(Deque_##t * deq, t a){																\
		if (deq->sizeV == 0){																				\
			deq->deque[deq->backV] = a;																		\
			deq->sizeV++;																					\
			return;																							\
		}																									\
		if (deq->sizeV < deq->max){																			\
			deq->backV = (deq->backV+1)%deq->max;															\
			deq->deque[deq->backV] = a;																		\
			deq->sizeV++;																					\
		}else{																								\
			if (deq->frontV < deq->backV){																	\
				t * temp = deq->deque;																		\
				deq->deque = ( t  *)realloc((void *)temp, (deq->max * 10)*sizeof( t ));						\
				deq->max *= 10;																				\
			}else{																							\
				t * temp = deq->deque;																		\
				int j = deq->max - deq->frontV;																\
				deq->deque = ( t  *)malloc((deq->max*10)*sizeof( t ));										\
				deq->max *= 10;																				\
																											\
				for(int i = 0; i < deq->backV + 1; i++){													\
					deq->deque[i] = temp[i];																\
				}																							\
				for(int i = 0; i < j; i++){																	\
					deq->deque[deq->max - (i + 1)] = temp[(deq->max/10) - (i + 1)];							\
				}																							\
				deq->frontV = deq->max - j;																	\
				delete [] temp;																				\
			}																								\
			deq->backV = (deq->backV+1)%deq->max;															\
			deq->deque[deq->backV] = a;																		\
			deq->sizeV++;																					\
		}																									\
	}																										\
												\
	t & t##_front(Deque_##t * deq){				\
		return deq->deque[deq->frontV];			\
	}											\
	t & t##_back(Deque_##t * deq){				\
		return deq->deque[deq->backV];			\
	}											\
															\
	t & t##_at(Deque_##t* deq, int i){						\
		return deq->deque[(deq->frontV + i)%deq->max];		\
	}														\
															\
	void t##_pop_front(Deque_##t * deq){					\
		if (deq->sizeV == 0) return;						\
		deq->frontV = (deq->frontV + 1)%deq->max;			\
		deq->sizeV--;										\
	}														\
															\
	void t##_pop_back(Deque_##t * deq){					\
		if (deq->sizeV == 0) return;						\
		deq->backV = deq->backV - 1;						\
		if (deq->backV == -1) deq->backV = deq->max - 1;	\
		deq->sizeV--;										\
	}														\
															\
	void t##_Iterator_inc(Deque_##t##_Iterator* it){		\
		it->atV = (it->atV + 1)%it->max;					\
	}														\
															\
	void t##_Iterator_dec(Deque_##t##_Iterator* it){		\
		it->atV = (it->atV + -1);							\
		if (it->atV == -1) it->atV = it->max - 1;			\
	}														\
															\
	t & t##_Iterator_deref(Deque_##t##_Iterator* it){	\
		return (*(it->deque))[it->atV];						\
	}														\
																									\
	Deque_##t##_Iterator& t##_begin(Deque_##t * deq){												\
		Deque_##t##_Iterator* it = (Deque_##t##_Iterator *)malloc(sizeof(Deque_##t##_Iterator));	\
		it->frontV = deq->frontV;																	\
		it->backV = deq->backV;																		\
		it->atV = deq->frontV;																		\
		it->deque = &(deq->deque);																	\
		it->max = deq->max;																			\
		it->inc = t##_Iterator_inc;																	\
		it->dec = t##_Iterator_dec;																	\
		it->deref = t##_Iterator_deref;																\
		return *it;																					\
	}																								\
																									\
	Deque_##t##_Iterator& t##_end(Deque_##t * deq){													\
		Deque_##t##_Iterator* it = (Deque_##t##_Iterator *)malloc(sizeof(Deque_##t##_Iterator));	\
		it->frontV = deq->frontV;																	\
		it->backV = deq->backV;																		\
		it->atV = (deq->backV + 1)%deq->max;														\
		it->deque = &(deq->deque);																	\
		it->max = deq->max;																			\
		it->inc = t##_Iterator_inc;																	\
		it->dec = t##_Iterator_dec;																	\
		it->deref = t##_Iterator_deref;																\
		return *it;																					\
	}																								\
	void t##_clear(Deque_##t * deq){		\
		deq->sizeV = 0;						\
		deq->frontV = deq->backV = 0;		\
	}										\
	void t##_dtor(Deque_##t * deq){			\
		delete[] deq->deque;				\
	}										\
																						\
																						\
	void Deque_##t##_ctor(Deque_##t * deq, bool (*f)(const t &o1, const t &o2)){		\
		deq->sizeV = 0;																	\
		deq->max = 10;																	\
		deq->frontV = 0;																\
		deq->backV = 0;																	\
		deq->deque = (t *) malloc(deq->max*sizeof( t ));								\
		deq->type_name = "Deque_" #t;													\
		deq->less_than = f;																\
		deq->size = t##_Deque_size;														\
		deq->empty = t##_empty;															\
		deq->push_back = t##_push_back;													\
		deq->push_front = t##_push_front;												\
		deq->front = t##_front;															\
		deq->back = t##_back;															\
		deq->at = t##_at;																\
		deq->pop_front = t##_pop_front;													\
		deq->pop_back = t##_pop_back;													\
		deq->begin = t##_begin;															\
		deq->end = t##_end;																\
		deq->clear = t##_clear;															\
		deq->dtor = t##_dtor;															\
	}																					\
																						\
	bool Deque_##t##_Iterator_equal (Deque_##t##_Iterator it, Deque_##t##_Iterator it2){\
		if (it.frontV != it2.frontV) return false;										\
		if (it.backV != it2.backV) return false;										\
		if (it.atV != it2.atV) return false;											\
		if (it.deque != it2.deque) return false;										\
		if (it.max != it2.max) return false;											\
		return true;																	\
	}																					\
																						\

/*
	bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){								\
		if (deq1.sizeV != deq2.sizeV) return false;										\
		for (int i = 0; i < deq1.sizeV; i++){											\
			if (deq1.at(&deq1, i) == deq2.at(&deq2, i)){								\
																						\
			}else return false;															\
		}																				\
		return true;																	\
	}
*/ 


/*
struct Deque_MyClass_Iterator;

struct Deque_MyClass{
	int max;
	int sizeV;
	int frontV;
	int backV;
	MyClass* deque;
	bool (*less_by_id) (const MyClass &o1, const MyClass &o2);
	size_t (*size)(Deque_MyClass* deq);
	bool (*empty)(Deque_MyClass* deq);
	const char* type_name = "Deque_MyClass";
	void (*push_back)(Deque_MyClass* deq, MyClass a);
	void (*push_front)(Deque_MyClass* deq, MyClass a);
	MyClass& (*front)(Deque_MyClass* deq);
	MyClass& (*back)(Deque_MyClass* deq);
	MyClass& (*at)(Deque_MyClass* deq, int i);
	void (*pop_front)(Deque_MyClass* deq);
	void (*pop_back)(Deque_MyClass* deq);
	Deque_MyClass_Iterator& (*begin)(Deque_MyClass* deq);
	Deque_MyClass_Iterator& (*end)(Deque_MyClass* deq);
};

struct Deque_MyClass_Iterator{
	int frontV;
	int backV;
	int max;
	MyClass** deque;
	int atV;
	void (*inc)(Deque_MyClass_Iterator* it);
	void (*dec)(Deque_MyClass_Iterator* it);
	MyClass& (*deref)(Deque_MyClass_Iterator* it);
};

size_t Deque_size(Deque_MyClass* deq){
	return (size_t)deq->sizeV;
}

bool Deque_empty(Deque_MyClass* deq){
	return deq->sizeV == 0;
}

void Deque_push_front(Deque_MyClass* deq, MyClass a){
	if (deq->sizeV == 0){
		deq->deque[deq->frontV] = a;
		deq->sizeV++;
		return;
	}
	if (deq->sizeV < deq->max){
		deq->frontV = (deq->frontV-1);
		if (deq->frontV == -1) deq->frontV = deq->max - 1;
		deq->deque[deq->frontV] = a;
		deq->sizeV++;
	}else{
		//Resize
		//if front is < back = in order just copy over in order
		if (deq->frontV < deq->backV){
			MyClass* temp = deq->deque;
			deq->deque = (MyClass *)realloc((void *)temp, (deq->max * 10)*sizeof(MyClass));
			deq->max *= 10;
			//delete [] temp;
		}else{ //Else copy front to front, back to back
			printf("Old front -- %d, max -- %d, back --%d\n", deq->frontV, deq->max, deq->backV);
			MyClass* temp = deq->deque;
			int j = deq->max - deq->frontV;
			deq->deque = (MyClass *)malloc((deq->max*10)*sizeof(MyClass));
			deq->max *= 10;
			
			for(int i = 0; i < deq->backV + 1; i++){
				deq->deque[i] = temp[i];
			}
			for(int i = 0; i < j + 1; i++){
				deq->deque[deq->max - (i + 1)] = temp[(deq->max/10) - (i + 1)];
			}
			deq->frontV = deq->max - j;
			printf("New front -- %d, max -- %d, back --%d\n", deq->frontV, deq->max, deq->backV);
			delete [] temp;
		}
		deq->frontV = (deq->frontV - 1)%deq->max;
		if (deq->frontV == -1) deq->frontV = deq->max - 1;
		deq->deque[deq->frontV] = a;
		deq->sizeV++;
	}
}

void Deque_push_back(Deque_MyClass* deq, MyClass a){
	if (deq->sizeV == 0){
		deq->deque[deq->backV] = a;
		deq->sizeV++;
		return;
	}
	if (deq->sizeV < deq->max){
		deq->backV = (deq->backV+1)%deq->max;
		deq->deque[deq->backV] = a;
		deq->sizeV++;
	}else{
		//Resize
		//if front is < back = in order just copy over in order
		if (deq->frontV < deq->backV){
			MyClass* temp = deq->deque;
			deq->deque = (MyClass *)realloc((void *)temp, (deq->max * 10)*sizeof(MyClass));
			deq->max *= 10;
		}else{ //Else copy front to front, back to back
			printf("Old front -- %d, max -- %d, back --%d\n", deq->frontV, deq->max, deq->backV);
			MyClass* temp = deq->deque;
			int j = deq->max - deq->frontV;
			deq->deque = (MyClass *)malloc((deq->max*10)*sizeof(MyClass));
			deq->max *= 10;
			
			for(int i = 0; i < deq->backV + 1; i++){
				deq->deque[i] = temp[i];
			}
			for(int i = 0; i < j; i++){
				deq->deque[deq->max - (i + 1)] = temp[(deq->max/10) - (i + 1)];
			}
			deq->frontV = deq->max - j;
			printf("New front -- %d, max -- %d, back --%d\n", deq->frontV, deq->max, deq->backV);
			delete [] temp;
		}
		deq->backV = (deq->backV+1)%deq->max;
		deq->deque[deq->backV] = a;
		deq->sizeV++;
	}
}

void MyClass_print(Deque_MyClass* deq){
	for (int i = 0; i < deq->sizeV; i++){
		printf("%s --- %d --- \n", (deq->deque)[(deq->frontV+i)%deq->max].name, (deq->deque)[(deq->frontV+i)%deq->max].id);
	}
}

MyClass& MyClass_front(Deque_MyClass* deq){
	return deq->deque[deq->frontV];
}

MyClass& MyClass_back(Deque_MyClass* deq){
	return deq->deque[deq->backV];
}

MyClass& MyClass_at(Deque_MyClass* deq, int i){
	return deq->deque[(deq->frontV + i)%deq->max];
}

void MyClass_pop_front(Deque_MyClass* deq){
	if (deq->sizeV == 0) return;
	deq->frontV = (deq->frontV + 1)%deq->max;
	deq->sizeV--;
}

void MyClass_pop_back(Deque_MyClass* deq){
	if (deq->sizeV == 0) return;
	deq->backV = deq->backV - 1;
	if (deq->backV == -1) deq->backV = deq->max - 1;
	deq->sizeV--;
}

void MyClass_Iterator_inc(Deque_MyClass_Iterator* it){
	it->atV = (it->atV + 1)%it->max;
}

void MyClass_Iterator_dec(Deque_MyClass_Iterator* it){
	it->atV = (it->atV + -1);
	if (it->atV == -1) it->atV = it->max - 1;
}

MyClass& MyClass_Iterator_deref(Deque_MyClass_Iterator* it){
	return (*(it->deque))[it->atV];
}

Deque_MyClass_Iterator& MyClass_begin(Deque_MyClass* deq){
	Deque_MyClass_Iterator* it = (Deque_MyClass_Iterator *)malloc(sizeof(Deque_MyClass_Iterator));
	it->frontV = deq->frontV;
	it->backV = deq->backV;
	it->atV = deq->frontV;
	it->deque = &(deq->deque);
	it->max = deq->max;
	it->inc = MyClass_Iterator_inc;
	it->dec = MyClass_Iterator_dec;
	it->deref = MyClass_Iterator_deref;
	return *it;
}

Deque_MyClass_Iterator& MyClass_end(Deque_MyClass* deq){
	Deque_MyClass_Iterator* it = (Deque_MyClass_Iterator *)malloc(sizeof(Deque_MyClass_Iterator));
	it->frontV = deq->frontV;
	it->backV = deq->backV;
	it->atV = (deq->backV + 1)%deq->max;
	it->deque = &(deq->deque);
	it->max = deq->max;
	it->inc = MyClass_Iterator_inc;
	it->dec = MyClass_Iterator_dec;
	it->deref = MyClass_Iterator_deref;
	return *it;
}

void Deque_MyClass_ctor(Deque_MyClass* deq, bool (*f)(const MyClass&o1, const MyClass&o2)){
	deq->sizeV = 0;
	deq->max = 10;
	deq->frontV = 0;
	deq->backV = 0;
	deq->deque = (MyClass *) malloc(deq->max*sizeof(MyClass));
	deq->less_by_id = f;
	deq->size = Deque_size;
	deq->empty = Deque_empty;
	//deq->type_name = new char[sizeof("Deque_MyClass")];
	//deq->type_name = "Deque_MyClass";
	deq->push_back = Deque_push_back;
	deq->push_front = Deque_push_front;
	deq->front = MyClass_front;
	deq->back = MyClass_back;
	deq->at = MyClass_at;
	deq->pop_front = MyClass_pop_front;
	deq->pop_back = MyClass_pop_back;
	deq->begin = MyClass_begin;
	deq->end = MyClass_end;
}

bool Deque_MyClass_Iterator_equal (Deque_MyClass_Iterator it, Deque_MyClass_Iterator it2){
	if (it.frontV != it2.frontV) return false;
	if (it.backV != it2.backV) return false;
	if (it.atV != it2.atV) return false;
	if (it.deque != it2.deque) return false;
	if (it.max != it2.max) return false;
	return true;
}
*/
#endif