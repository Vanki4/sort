#include <iostream>
#include <ctime>
#include <cstdlib>

void print(int *mass,int len) {
	for (int i = 0;i<len;i++)
	{
		std::cout << mass[i] << " ";
	}
	std::cout << "\n";
}

void bubble(int *mass,int len) {
	for (int i = 0;i<len;i++)
	{
		bool flag = false;
		for (int j = 0;j<len-i-1;j++)
		{
			if (mass[j]>mass[j+1])
			{
				std::swap(mass[j],mass[j+1]);
				flag = true;
			}
		}
		if (!flag)
		{
			break;
		}
	}
}

void choice(int *mass,int len) {
	for (int i = 0; i<len;i++)
	{
		int mini = i;
		for (int j = i+1;j<len;j++)
		{
			if (mass[mini] > mass[j])
			{
				mini = j;
			}
		}
		std::swap(mass[i],mass[mini]);
	}
}

void past(int *mass,int len) {
	for (int i = 1;i<len;i++)
	{
		int key = mass[i];
		int j = i-1;
		while (j>=0 && mass[j]>key)
		{
			mass[j+1] = mass[j];
			j--;
		}
		mass[j+1] = key;	
	}
}

void merge(int *mass,int left,int mid,int right) {
	int n = right-left+1;
	int *tmp = new int[n];
	int i = left;
	int j = mid+1;
	int k = 0;
	while (i<=mid && j<=right)
	{
		if (mass[i]<mass[j])
		{
			tmp[k++] = mass[i++];
		}
		else
		{
			tmp[k++] = mass[j++];
		}
	}
	while (i<=mid)
	{
		tmp[k++] = mass[i++];
	}
	while (j<=right)
	{
		tmp[k++] = mass[j++];
	}
	for (int t = 0;t<n;t++)
	{
		mass[left+t]=tmp[t];
	}
	delete [] tmp;
}	

int quick(int *mass,int left,int right) {
	int ran = rand()%(right-left+1)+left;
	std::swap(mass[ran],mass[right]);
	int pavot = mass[right];
	int i = left-1;
	for (int j = left;j<right;j++)
	{
		if (mass[j]<pavot)
		{
			i++;
			std::swap(mass[j],mass[i]);
		}
	}
	std::swap(mass[i+1],mass[right]);
	return i+1;
}
void mergesort(int *mass,int left,int right) {
	if (left>=right) {return;}
	int mid = left + (right-left)/2;
	mergesort(mass,left,mid);
	mergesort(mass,mid+1,right);
	merge(mass,left,mid,right);
}

void quickSort(int *mass,int left,int right) {
	if (left<right)
	{
		int tmp = quick(mass,left,right);
		quickSort(mass,left,tmp-1);
		quickSort(mass,tmp+1,right);
	}
}


int main(int argc,char **argv) {
	srand(time(NULL));
	if (argc!=4)
	{
		std::cout << "Некоректное число аргументов" << std::endl;
		return -1;
	}
	int len = atoi(argv[1]);
	int *mass = new int[len];
	for (int i = 0;i<len;i++)
	{
		mass[i] = rand()%(atoi(argv[3])-atoi(argv[2]))+atoi(argv[2]);
	}
	print(mass,len);
	quickSort(mass,0,len-1);
	print(mass,len);
	delete [] mass;
	return 0;
}
