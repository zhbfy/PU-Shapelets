#pragma once

template <class T>
int sign(T x) {
	int ret;
	if (x > 0)
		ret = 1;
	else if (x == 0)
		ret = 0;
	else
		ret = -1;
	return ret;
}

template <class T>
T min(T x, T y){
	if (x < y)
		return x;
	return y;
}

template <class T>
T max(T x, T y){
	if (x > y)
		return x;
	return y;
}

template <class T>
T min(T* x, int numElm, int stride = 1){
	T val, ret = x[0];
	for (int i = 1; i < numElm; i++){
		val = x[i * stride];
		if (val < ret)
			ret = val;
	}
	return ret;
}

template <class T>
T max(T* x, int numElm, int stride = 1){
	T val, ret = x[0];
	for (int i = 1; i < numElm; i++){
		val = x[i * stride];
		if (val > ret)
			ret = val;
	}
	return ret;
}

template <class T>
void min(T &minVal, int &minIdx, T* x, int numElm, int stride = 1) {
	T val;
	minVal = x[0];
	minIdx = 0;
	for (int i = 1; i < numElm; i++) {
		val = x[i * stride];
		if (val < minVal) {
			minVal = val;
			minIdx = i;
		}
	}
}

template <class T>
void max(T &maxVal, int &maxIdx, T* x, int numElm, int stride = 1) {
	T val;
	maxVal = x[0];
	maxIdx = 0;
	for (int i = 1; i < numElm; i++) {
		val = x[i * stride];
		if (val > maxVal) {
			maxVal = val;
			maxIdx = i;
		}
	}
}

template <class T>
void minWithTies(T &minVal, int *minIdxes, int &numMin, T* x, int numElm, int stride = 1) {
	T val;
	minVal = x[0];
	minIdxes[0] = 0;
	numMin = 1;
	for (int i = 1; i < numElm; i++) {
		val = x[i * stride];
		if (val < minVal) {
			minVal = val;
			minIdxes[0] = i;
			numMin = 1;
		}
		else if (val == minVal) {
			minIdxes[numMin] = i;
			numMin++;
		}
	}
}

template <class T>
void maxWithTies(T &maxVal, int *maxIdxes, int &numMax, T* x, int numElm, int stride = 1) {
	T val;
	maxVal = x[0];
	maxIdxes[0] = 0;
	numMax = 1;
	for (int i = 1; i < numElm; i++) {
		val = x[i * stride];
		if (val > maxVal) {
			maxVal = val;
			maxIdxes[0] = i;
			numMax = 1;
		}
		else if (val == maxVal) {
			maxIdxes[numMax] = i;
			numMax++;
		}
	}
}

template <class T>
T sum(T *x, int numElm, int stride = 1){
	T total = 0;
	for (int i = 0; i < numElm; i++) {
		total += x[i * stride];
	}
	return total;
}

template <class T>
T sum2(T *x, int numElm, int stride = 1){
	T val, total2 = 0;
	for (int i = 0; i < numElm; i++){
		val = x[i * stride];
		total2 += val * val;
	}
	return total2;
}

template <class T>
T mean(T* x, int numElm, int stride = 1){
	return sum(x, numElm, stride) / numElm;
}

template <class T>
T var(T* x, int numElm, int stride = 1){
	T total2 = sum2(x, numElm, stride);
	T avg = mean(x, numElm, stride);
	T varVal = total2 / numElm - avg * avg;
	if (varVal < 0)
		varVal = 0;
	return varVal;
}

template <class T>
T stdv(T* x, int numElm, int stride = 1){
	return sqrt(var(x, numElm, stride));
}

template <class T>
void zscore(T *zx, T *x, int numElm, int zstride = 1, int stride = 1){
	T avg = mean(x, numElm, stride);
	T stdev = stdv(x, numElm, stride);
	if (!stdev)
		stdev = 1;
	for (int i = 0; i < numElm; i++)
		zx[i * zstride] = (x[i * stride] - avg) / stdev;
}

template <class T>
void transposeMtx(T *transposed, T *original, int numRowsOri, int numColsOri) {
	for (int i = 0; i < numRowsOri; i++) {
		for (int j = 0; j < numColsOri; j++)
			transposed[j * numRowsOri + i] = original[i * numColsOri + j];
	}
}

template <class T>
void reorderMtx(T *reordered, T *original, int *ranks, int numRows, int numCols) {
	int next;
	for (int i = 0; i < numRows; i++) {
		next = ranks[i];
		memcpy(reordered + i * numCols, original + next * numCols, numCols * sizeof(T));
	}
}

template <class T>
void dotProduct(T *mtx_out, T *mtx1, T *mtx2, int numElm) {
	for (int i = 0; i < numElm; i++) {
		mtx_out[i] = mtx1[i] * mtx2[i];
	}
}

template <class T>
void cumsum(T *cumsum_out, T *vec, int numElm) {
	T s = 0;
	for (int i = 0; i < numElm; i++) {
		s += vec[i];
		cumsum_out[i] = s;
	}
}

template <class T>
void cumsum(T *cumsum_out, T *vec, int *argOrder, int numElm) {
	T s = 0;
	for (int i = 0; i < numElm; i++) {
		s += vec[argOrder[i]];
		cumsum_out[i] = s;
	}
}