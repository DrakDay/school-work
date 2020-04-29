#include "MaxHeap.h"


MaxHeap::MaxHeap() {

}

void MaxHeap::buildMaxHeap(storm_event *x, int n, string choice) {

	if (choice == "damage_property") {
		for (int i = n / 2 - 1; i>=0; i--) {
			MaxHeapify_property(x, n, i);
		}

		//sort the max heap
		for (int i = n - 1; i >= 0; i--) {

			swap(x[0], x[i]);

			MaxHeapify_property(x, i, 0);
		}
	}
	else {
		for (int k = n / 2 - 1; k >= 0; k--) {
			MaxHeapify_crops(x, k, n);
		}
		//sort the max heap
		for (int i = n - 1; i >= 0; i--) {

			swap(x[0], x[i]);

			MaxHeapify_crops(x, i, 0);
		}
	}
}

void MaxHeap::buildMaxHeap_fatality(storm_event* x, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		MaxHeapify_fatality(x, n, i);
	}

	//sort the max heap
	for (int i = n - 1; i >= 0; i--) {

		swap(x[0], x[i]);

		MaxHeapify_fatality(x, i, 0);
	}
}

void MaxHeap::MaxHeapify_property(storm_event *x, int n, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && x[l].damage_property > x[largest].damage_property)
		largest = l;

	if (r < n && x[r].damage_property > x[largest].damage_property)
		largest = r;

	if (largest != i) {
		swap(x[i], x[largest]);

		MaxHeapify_property(x, n, largest);
	}
}

void MaxHeap::MaxHeapify_crops(storm_event *x, int n, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && x[l].damage_crops > x[largest].damage_crops)
		largest = l;

	if (r < n && x[r].damage_crops > x[largest].damage_crops)
		largest = r;

	if (largest != i) {
		swap(x[i], x[largest]);

		MaxHeapify_property(x, n, largest);
	}
}

void MaxHeap::MaxHeapify_fatality(storm_event*x, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && x[l].numoffatality > x[largest].numoffatality)
		largest = l;

	if (r < n && x[r].numoffatality > x[largest].numoffatality)
		largest = r;

	if (largest != i) {
		swap(x[i], x[largest]);

		MaxHeapify_property(x, n, largest);
	}
}


