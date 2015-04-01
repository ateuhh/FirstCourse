#include <iostream>
#include <cstdlib>

using namespace std;
int** field;
int born = 0 ;
int death = 0;
int popul ;
int step = 0;
int length;
int high;
int no_change_popul = 0;

int get (){
	char input [256];
  	cin >> input;
	int x = atoi(input);
	return x;
}

void statistic_ten (){
	if (death !=0){
	double q = 1;
	q *= born;
	q /=death;
	cout << "Relationship born/death after "<<step<<" steps: "<<q<<endl;
	}
	else{
		cout << "Born after "<<step<<" steps "<<born<<endl;
		cout << "Died after "<<step<<" steps "<<death<<endl;
	}
	cout << "Population after "<<step<<" steps "<<popul<<endl;
	born = 0;
	death = 0 ;
}

void increase_field(int l, int h) {
    field[l][h] += 0x01;
    field[l+1][h+1] += 0x10;
    field[l][h+1] += 0x10;
    field[l+1][h] += 0x10;
    field[l-1][h+1] += 0x10;
    field[l+1][h-1] += 0x10;
    field[l][h-1] += 0x10;
    field[l-1][h] += 0x10;
    field[l-1][h-1] += 0x10;
}
void new_field(){
	field = new int*[length];
    for (int i = 0; i < length; i++) {
        field[i] = new int[high]();
	}
}

void  fill (){
	new_field();
	int c = 0 ;
		for (int i=1; i< length-1;i++){
			for (int j=1; j< high-1;j++){
			 	field[i][j] = rand()%2;
			 	if (field[i][j]==1) c++;
				 if (c==popul) break;
			}
			if (c==popul) break;
		}
	if (c != popul){
		for (int i=1; i< length-1;i++){
			for (int j=1; j< high-1;j++){
			 	if (field[i][j]==0) field[i][j]=1; 
			 	if (field[i][j]==1) c++;
				 if (c==popul) break;
			}
		}
	}
} 

void realization_step(){
	int pre_popul = popul;
	popul = 0;
	int pre_length;
	int pre_high;
	int length_removal = 0;
	int high_removal = 0;
	
    for (int i = 0; i < pre_high; i++) {
        if (field[0][i]) {
            length_removal = 1;
            length += 1;
            break;
        }
    }
    for (int i = 0; i < pre_high; i++) {
        if (field[pre_length - 1][i]) {
            length += 1;
            break;
        }
    }
    for (int i = 0; i < pre_length; i++) {
        if (field[i][0]) {
            high_removal = 1;
            high += 1;
            break;
        }
    }
    for (int i = 0; i < pre_length; i++) {
        if (field[i][pre_high - 1]) {
            high += 1;
            break;
        }
    }
    int** pre_field = field;
    new_field();

    for (int l = 0; l < pre_length; l++) {
        for (int h = 0; h < pre_high; h++) {
            if (pre_field[l][h]) {
                switch (pre_field[l][h] >> 4) {
                    case 3:
                        increase_field(l + length_removal, h + high_removal);
                        popul++;
                        if (!(pre_field[l][h] & 0x01))
                            born++;
                        break;
                    case 2:
                        if (pre_field[l][h] & 0x01) {
                            increase_field(l + length_removal, h + high_removal);
                            popul++;
                        }
                        break;
                    default:
                        if (pre_field[l][h] & 0x01)
                            death++;
                }
            }
        }
    }

    for (int i = 0; i < pre_length; i++) {
        delete [] pre_field[i];
    }
    delete [] pre_field;

    step++;
	if (step % 10 == 0) {
		statistic_ten();
	}      

    if (popul == pre_popul)
        no_change_popul++;
    else
        no_change_popul = 0;
}	


int main(){
	cout << "Input length field" <<endl;
	length = get();
	cout << "Input high field" <<endl;
	high = get();
	cout << "Input population" <<endl;
	int population = get();
	popul = population;
	cout << "Input steps" <<endl;
	int steps = get();
	int flag = 0;
	if (length*high < population || length < 1 || high < 1 || population <0 || steps < 0){
		cout << "Incorrect data" << endl;
        flag = 1;
	}
	length += 2;
	high += 2;
	if (flag == 0) {
		fill();
	    	while (step < steps) {
        		realization_step();
    		}
    	cout << "Gain population : "<< popul - population << endl;
		if (no_change_popul == 1){
			cout << "Population have change for "<< no_change_popul << " steps"<< endl;
		}  
	}
	return 0;
}


