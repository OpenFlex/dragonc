double asd(int b)
{
// 	int d__r = b + 3;
// 		int a = 4 - d__r;
// 		printf(b);
// 		printf(a);
}

int main(int c)
{
	
	int i = 3;
	int a =  i & 2;
	a++;
	a = ++a + 2 | 100;
	a = a--;
	a = --a;
	printf(a);
	--a;
	printf(a);
	int d__r =  (a - 1) + --a / 2 + (a + a ++ * 2) - --a;
	d__r = --d__r + ++a % 2;
	printf(d__r);
	printf(a);
}
