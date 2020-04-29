#pragma once
#include <iostream>
#include "defn.h"

using namespace std;

class MaxHeap {
	storm_event* harr;

public:
	MaxHeap();

	void buildMaxHeap(storm_event* x, int n,  string choice);

	void buildMaxHeap_fatality(storm_event* x, int n);

	void MaxHeapify_property(storm_event *x, int n, int i);

	void MaxHeapify_crops(storm_event *x, int n, int i);

	void MaxHeapify_fatality(storm_event *x, int n, int i);
	
};