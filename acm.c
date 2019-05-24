
#include <vector>
#include <iostream>

typedef struct {
	void(*callback)(std::vector<int>*, void*);
	void* arg;
	int i;
} com_callback_arg;

void com_callback1(std::vector<int>* result, void* _arg) {
	com_callback_arg* arg = (com_callback_arg*)_arg;
	result->push_back(arg->i);
	arg->callback(result, arg->arg);
}

void com_callback2(std::vector<int>* result, void* _arg) {
	com_callback_arg* arg = (com_callback_arg*)_arg;
	arg->callback(result, arg->arg);
}

void com(int k, int n, void(*callback)(std::vector<int>*, void*), void* arg) {
	if (k > n || k < 0) {
		return;
	}
	if (k == 0) {
		std::vector<int> arr;
		callback(&arr, arg);
		return;
	}
	com_callback_arg arg1;
	arg1.callback = callback;
	arg1.arg = arg;
	arg1.i = n;
	com(k - 1, n - 1, com_callback1, &arg1);
	com(k, n - 1, com_callback2, &arg1);
}

typedef struct {
	void(*callback)(std::vector<int>*, void*);
	void* arg;
	int i;
} per_callback_arg;

void per_callback1(std::vector<int>* result, void* _arg) {
	per_callback_arg* arg = (per_callback_arg*)_arg;
	result->push_back(arg->i);
	for (int i = result->size() - 1; i > 0; --i) {
		arg->callback(result, arg->arg);
		int temp = (*result)[i];
		(*result)[i] = (*result)[i - 1];
		(*result)[i - 1] = temp;
	}
	arg->callback(result, arg->arg);
	result->erase(result->begin());
}

void per_callback2(std::vector<int>* result, void* _arg) {
	per_callback_arg* arg = (per_callback_arg*)_arg;
	arg->callback(result, arg->arg);
}

void per(int k, int n, void(*callback)(std::vector<int>*, void*), void* arg) {
	if (k > n || k < 0) {
		return;
	}
	if (k == 0) {
		std::vector<int> arr;
		callback(&arr, arg);
		return;
	}
	per_callback_arg arg1;
	arg1.callback = callback;
	arg1.arg = arg;
	arg1.i = n;
	per(k - 1, n - 1, per_callback1, &arg1);
	per(k, n - 1, per_callback2, &arg1);
}

typedef struct {
	void(*callback)(std::vector<int>* result, void* _arg);
	void* arg;
	int i;
} subset_callback_arg;

void subset_callback(std::vector<int>* result, void* _arg) {
	subset_callback_arg* arg = (subset_callback_arg*)_arg;
	result->push_back(arg->i);
	arg->callback(result, arg->arg);
	result->erase(result->begin() + (result->size() - 1));
	arg->callback(result, arg->arg);
}

void subset(int n, void(*callback)(std::vector<int>*, void*), void* arg) {
	if (n < 0) {
		return;
	}
	if (n == 0) {
		std::vector<int> arr;
		callback(&arr, arg);
		return;
	}
	subset_callback_arg arg1;
	arg1.callback = callback;
	arg1.arg = arg;
	arg1.i = n;
	subset(n - 1, subset_callback, &arg1);
}

void output(std::vector<int>* result, void* arg) {
	if (arg != NULL) {
		const char* p = (const char*)arg;
		std::cout << p;
	}
	for (int i = 0; i < result->size(); ++i) {
		std::cout << (*result)[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	//遍历在四个元素里面选三个元素的所有组合
	com(3, 4, output, (void*)"com: ");
	//遍历在四个元素里面选三个元素的所有排列
	per(3, 4, output, (void*)"per: ");
	//遍历在三个元素里面所有子集
	subset(3, output, (void*)"subset: ");
}