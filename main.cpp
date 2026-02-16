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

void radix(int *mass,int len,int k,int min) {
	int *outp = new int[len];
	int count[10] = {0};
	for (int i = 0;i<len;i++)
		count[(mass[i]/k)%10]++;
	for (int i = 1;i<10;i++)
		count[i]+=count[i-1];
	for (int i = len-1;i>=0;i--)
	{
		int dig = (mass[i]/k)%10;
		outp[count[dig]-1] = mass[i];
	       	count[dig]--;
	}
	for (int i = 0;i<len;i++)
	{
		mass[i] = outp[i];
	}
	delete [] outp;
}	

void radixSort(int *mass,int len) {
	int min = mass[0];
	for (int i = 1;i<len;i++)
	{
		if (min > mass[i])
			min = mass[i];
	}
	if (min<0)
		min *= -1;
	int max = mass[0];
	for (int i = 0;i<len;i++)
	{
		mass[i]+=min;
		if (max<mass[i])
			max= mass[i];
	}
	for (int k = 1;max>0;k*=10)
	{
		radix(mass,len,k,min);
		max /= 10;
	}
	for (int i = 0;i<len;i++)
	{
		mass[i]-=min;
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
	radixSort(mass,len);
	print(mass,len);
	delete [] mass;
	return 0;
}
