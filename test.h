#define TEST_EPSILON 0.1

typedef struct  {
	char** str;
	float answer;
}test_pair;

inline float test(test_pair test_case, float result) {
	return result - test_case.answer;
}

