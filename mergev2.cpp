#include <iostream>
#include <ctime>
#include <vector>

void print(std::vector<int> &mass) {
	for (int i = 0;i<mass.size();i++)
	{
		std::cout << mass[i] << " ";
	}
	std::cout << "\n";
}

std::vector<int> Mmerge(std::vector<int> &m1,std::vector<int> &m2) {
          std::vector<int> res;
          int i = 0,j=0;
          while (i<m1.size() && j<m2.size())
          {
                  if (m1[i]<m2[j])
                          res.push_back(m1[i++]);
                  else
                          res.push_back(m2[j++]);
          }
          while (i<m1.size())
                  res.push_back(m1[i++]);
          while (j<m2.size())
                  res.push_back(m2[j++]);
          return res;
  }

void mergeSort(std::vector<int> &mass) {
	if (mass.size() == 1)
		return;
	int mid = mass.size()/2;
	std::vector<int> left(mass.begin(),mass.begin()+mid);
	std::vector<int> right(mass.begin()+mid,mass.end());
	mergeSort(left);
	mergeSort(right);
	mass = Mmerge(left,right);
}

int main(int argc,char **argv) {
	srand(time(NULL));
	std::vector<int> mass(atoi(argv[1]));
	for (int i = 0;i<atoi(argv[1]);i++)
	{
		mass[i] = rand()%(atoi(argv[3])-atoi(argv[2]))+atoi(argv[1]);
	}
	print(mass);
	mergeSort(mass);
	print(mass);
	return 0;
}	
