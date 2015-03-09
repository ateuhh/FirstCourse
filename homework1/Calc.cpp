#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
	vector <int> a;                             // numbers  
	vector <char> b;                            // signs
	int i = 0 , j = 0 , m = 0, res;             // i = a.length, j = b.length, 'm' is error flag , 'res' is result  
	char c = cin.get ();                        // 'c' is  current character 
	while ((c != '\n') && (m == 0)){            // this loop separates data to numbers and signs 
		if ((i-j) == 1 || i == j){
			int q = 0;                          //'q' is auxiliary variable; if q == 1 , then 'w' push back in vector 'a'  
			int w = 0;                          //'w' is auxiliary variable
			while (c >= '0' && c <= '9'){
				w = 10 * w + c - '0';
				c = cin.get();
				q = 1;				
			}
			if (q == 1){
				a.push_back(w);
				i++;
			}
			if (c == ' ' || (c >= '0' && c <= '9') || c == '+' || c == '*' || c == '/' || c == '\n'|| c == '-' || c == '%')
                {
					if (c == '+' || c == '*' || c == '/' || c == '-'||  c == '%'){
						char e = c;
						b.push_back(e);
						c = cin.get();
						j++;
					}else{
						c = cin.get();
						continue;
					}
				}else{
				m = 1;
				break;
				}	 
        }else{
			m = 1 ;
			break;                               
		}
	}
	if ((i-j)!=1){                               // if a.length != b.length +1 , then it's error.
		m = 1;
	}
	i--;
	if (m == 0 && i >0){						 // if a.length > 0 , then multiply and divide , next  add and subtract 
	int q = i;
	int w = 0;
	while ( w < i && m == 0){                    // this loop multiply and devide
		if (b[w] == '*' || b[w] == '/' || b[w] =='%'){
			if ((b[w]=='/' || b[w]=='%')&& (a[w+1])== 0){
				m = 2;
				continue;
			}else{
                if (b[w] == '*') a[w] *= a[w+1];
				if (b[w] == '/') a[w] /= a[w+1];  
			    if (b[w] == '%') a[w] %= a[w+1];
				for (int l = w; l < q-1 ; l++){
					b[l] = b[l+1];
					a[l+1] = a[l+2];
				}
				b[q-1] = 'a';
				q--;
				w--;
			}
		}
	w++;
	}
	w=0;
	res = a[w];
	for (w ; w<q; w++){                                 // this loop add and subtract
		if (b[w]=='+')	res +=a[w+1];
		if (b[w]=='-')	res -=a[w+1];		
	}
	}
		if (i== 0) res = a[0];
	    if(m == 0 ) cout<<res<<endl;
        if(m == 1) cout<<"Wrong input format"<<endl;
		if(m == 2) cout<<"Wrong operation"<<endl;
}



