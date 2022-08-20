// permutations
#include <iostream>
using namespace std;
int main(){
	int count=1, I=65, J=66, K=67, L=68, M=69;
	cout << "Permutation:\n";
	for (int i=5; i>0; i--){

		for (int j=4; j>0; j--){

			for (int k=3; k>0; k--){
				do{
					if (K>69){
						K=65;
					}
					if (K==I){
						K+=2;
					}
					if (K==J){
						K++;
					}
					if (K>69){
						K=65;
					}
				} while (K==I || K==J);

				for (int l=2; l>0; l--){
					do{
						if (L==I){
							L++;
						}
						if (L==J){
							L++;
						}
						if (L==K){
							L++;
						}
						if (L>69){
							L=65;
						}
					}while(L==I || L==J || L==K);

					for (int m=1; m>0; m--){
						do{
							if (M==I){
								M++;
							}
							if (M==J){
								M++;
							}
							if (M==K){
								M++;
							}
							if (M==L){
								M++;
							}
							if (M>69){
								M=65;
							}
						} while (M==I || M==J || M==K || M==L);

						cout << count << ". ";
						cout << char(I);
						cout << char(J);
						cout << char(K);
						cout << char(L);
						cout << char(M);
						cout << endl;
						count++;

						M++;
						if (M>69){
							M=65;
						}
					}
					L++;
					if (L>69){
						L=65;
					}
				}
				K++;
			}
			J++;
			if (I==J){
				J++;
			}
			if (J>69){
				J=65;
			}
		}
		I++;
	}

	return 0;
}

