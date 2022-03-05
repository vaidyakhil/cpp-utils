class IntUtils {
	public:
		int minm(int a, int b) {
			return a < b ? a : b;
		}

		int maxm(int a, int b) {
			return a < b ? b : a;
		}

		  //GCD
		int gcd(int a, int b) {
			if(a < b){
			    int temp= b;
			    b=a;
			    a=temp;
			}
			return (a % b==0 ? b: gcd(b, a % b));
		}
};