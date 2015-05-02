#include <iostream>
#include <cstdlib>

using namespace std;

int** field;
int step = 0;
int born = 0;
int death = 0;	
int no_change_popul = 0;
int length;
int high;
int popul;

int get (){									//This function gets numbers
	char input [256];
  	cin >> input;
	int x = atoi(input);
	return x;
}

void new_field() {							// This function makes new gamefield
    field = new int*[length];
    for (int i = 0; i < length; i++) {
        field[i] = new int[high]();
    }
}

bool exist(int l, int h) {					// This function inspects exsistence cell
    return (field[l][h] & 0x01) != 0;
}

void increase_field(int l, int h) {			// This function  automatically appends new cell
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
void  fill (){								// This function automatically fill gamefield
	new_field();
	int c = 0 ;
        while (c < popul) {
            int y = rand() % (high - 2) + 1;
            int x = rand() % (length - 2) + 1;
            if (!exist(x, y)) {
                increase_field(x, y);
                c++;
            }
        }
}
void your_fill (){							// This function correctly process your handmade fill
	int x;
    int y;
    cout << "Enter " << popul << " pairs of coordinates (x y) "<< endl;
	for (int i = 0; i < popul; i++) {
        cin >> x;
        cin >> y;
        if (!exist(y, x)) {
            increase_field(y, x);
        } else {
            cout << "Cell already exists" << endl;
            i--;
        }
    }
} 
void statistic_ten (){						// This function prints statistic
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

void realization_step() {					// This function implements step
    int pre_popul = popul;
    popul = 0;
    int length_removal = 0;
    int high_removal = 0;
    int pre_length = length;
    int pre_high = high;

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
    int** old_field = field;
    new_field();

    for (int l = 0; l < pre_length; l++) {
        for (int h = 0; h < pre_high; h++) {
            if (old_field[l][h]) {
                switch (old_field[l][h] >> 4) {
                    case 3:
                        increase_field(l + length_removal, h + high_removal);
                        popul++;
                        if (!(old_field[l][h] & 0x01))
                            born++;
                        break;
                    case 2:
                        if (old_field[l][h] & 0x01) {
                            increase_field(l + length_removal, h + high_removal);
                            popul++;
                        }
                        break;
                    default:
                        if (old_field[l][h] & 0x01)
                            death++;
                }
            }
        }
    }

    for (int i = 0; i < pre_length; i++) {
        delete [] old_field[i];
    }
    delete [] old_field;

    step++;
    if (step % 10 == 0) {
        statistic_ten();
    }

    if (pre_popul == popul)
        no_change_popul++;
    else
        no_change_popul = 0;
}

void print_field() {							// This function prints final field
    for (int l = 1; l < length - 1; l++) {
        for (int h = 1; h < high - 1; h++) {
            cout << (field[l][h] & 0x01) << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    cout << "Input length field" <<endl;
	length = get();
	cout << "Input high field" <<endl;
	high = get();
    new_field();
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
	high += 2;
    length += 2;
	if (flag == 0){
		cout << "Do you want to enter start of the field by yourself? (Y/N)" << endl;
    	char a;
    	cin >> a;
    	if (a == 'y' || a== 'Y') {
        	your_fill();
    	} else {
			fill();		
    	}
		while (step < steps) {
        	realization_step();
    	}
    	cout << "Gain population : "<< popul - population << endl;
		if (no_change_popul){
			cout << "Population have change for "<< no_change_popul << " steps"<< endl;
		} 
		cout << "Would you like to view the field? (y/n)" << endl;
		cin >> a;
		if (a == 'y' || a == 'Y'){
			print_field();
    	} 
	}
    return 0;
}

