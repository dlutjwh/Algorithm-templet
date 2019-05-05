//大顶堆

//向下调整，下标从0开始 节点i的左儿子为i*2+1，右儿子为2*i+2，从x节点需要调整，n为要调整的范围
void adjust_down(int array[], int x, int n) {
	while (x * 2 + 1 < n) {
		int cnt = x * 2 + 1;
		if (cnt + 1 < n&&array[cnt + 1] > array[cnt])
			cnt++;  //cnt为左右孩子较大的
		if (array[x] >= array[cnt])  //父亲比左右孩子都大，不需要再向下调整
			return;
		else {
			swap(array[x], array[cnt]);
			x = cnt;
		}
	}
	
}
//array为待排序的数组，n为数组大小，
void heap_sort(int array[], int n) { 
	//初始化，从第一个非叶子节点开始调整
	for (int i = n / 2 - 1;i >= 0;i--) {
		int cnt = i * 2 + 1;
		if (cnt + 1 < n&&array[cnt + 1] > array[cnt])
			cnt++;  //cnt为左右孩子较大的
		if (array[cnt] > array[i]) {
			swap(array[cnt], array[i]);
			adjust_down(array, cnt, n);  //父亲和谁交换就调整谁
		}
	}
	
	for (int i = n - 1;i > 0;i--) {  
		swap(array[i], array[0]);  //把最大的数（堆顶）放到最后
		adjust_down(array, 0, i);  //堆顶需要调整，i之后的数是有序的了（升序）
	}
}

int main() {
	srand(time(NULL));
	for (int t = 1;t <= 100000;t++) {
		int array[20];

		for (int i = 0;i <= 19;i++)
			array[i] = rand() % 100;
		/*
		for (int i = 0;i <= 19;i++)
			cout << array[i] << " ";
		cout << endl;
		*/
		heap_sort(array, 20); 
/*
		for (int i = 0;i <= 19;i++)
			cout << array[i] << " ";
		cout << endl;
	*/	
		for (int i = 1;i <= 19;i++)
			if (array[i] < array[i - 1])
				cout << -1 ;
	
	}
}
