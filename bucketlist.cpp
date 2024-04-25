//Marley Schneider
//CECS 325-02
//Prog 5 - Bucket List
//
//4/23/2024
//
//I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int globalSwapCount = 0;

class Bucket{
	private:
		vector<int> v;
	public:
		Bucket();
		void generate(int size, int min1, int max1);
		void sort();
		int size();
		int atIndex(int index);
		void merge(Bucket b);
};

Bucket::Bucket(){
	vector<int> v;
}

void Bucket::generate(int size, int min1, int max1){
  int count = size;
  int min = min1;
  int max = max1;

  srand(time(0));
  for (int i = 0; i < count; i++){
    v.push_back(rand() % (max - min  + 1) + min);
  }
}

void Bucket::sort(){
  int swaps = 1;
  // number of swaps we need to check for
  int iterations = v.size();
  for (int j=0; j < v.size() - 1; j++){
    swaps = 0;
    for (int i = 1; i < iterations; i++){
      if (v.at(i) < v.at(i - 1)){
        swap(v[i], v[i - 1]);
        swaps += 1;
	globalSwapCount += 1;
      }
    }
    if (swaps == 0)
      break;
    iterations -= 1;
  }
}

int Bucket::size(){
	return v.size();
}

int Bucket::atIndex(int index){
	return v.at(index);
}

void Bucket::merge(Bucket b){
	int bucket_b_index = 0;
	for (int i = 0;i < v.size();i++){	
		if (v[i] > b.atIndex(bucket_b_index)){
			v.insert((v.begin() + i), b.atIndex(bucket_b_index));
			bucket_b_index++;
		}
	}
	
		while ((b.size() - 2) > bucket_b_index){
			v.push_back(b.atIndex(bucket_b_index));
			bucket_b_index++;
		}
}

int main(int arc, char *argv[]){
	srand(time(0));
	
	int bucketCount = stoi(argv[1]);
	int bucketSize = stoi(argv[2]);
	int bucketMin = stoi(argv[3]);
	int bucketMax = stoi(argv[4]);
	cout << "Bucket Count: " << bucketCount << endl;
	cout << "Bucket size : " << bucketSize << endl;
	cout << "Bucket Min Value: " << bucketMin << endl;
	cout << "Bucket Max Value: " << bucketMax << endl;
	
	vector<Bucket> list;

	Bucket *bptr;

	for(int i=0; i<bucketCount; i++){
		bptr = new Bucket;
		bptr->generate(bucketSize, bucketMin, bucketMax);
		list.push_back(*bptr);
	}


	for (auto it = list.begin(); it != list.end(); it++)
		it->sort();

	Bucket endGame;
	
	while (list.size() > 0){
		endGame.merge(list[0]);
		list.erase(list.begin());
	}

	
	fstream out("bucketList.out", ios::out);
	for(int i=0;i<endGame.size();i++)
		out << endGame.atIndex(i) << endl;

	cout << "Global Swap Count: " << globalSwapCount << endl;
	cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";

	return 0;
}
