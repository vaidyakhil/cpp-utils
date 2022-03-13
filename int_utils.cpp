class IntUtils {
	public:
		int minm(int a, int b) {
			return a < b ? a : b;
		}

		int maxm(int a, int b) {
			return a < b ? b : a;
		}

		/*
		**	GCD(a, b, c) -> GCD (GCD(a, b), c);
		**	
		**	LCM (a, b) -> (a * b) / gcd(a, b);
		**	
		**	LCM (a, b, c) -> (LCM(a,b) * c)/ (GCD(a,b) * c)
		*/
		int gcd(int a, int b) {
	        if (a < b) {
	            return gcd(b, a);
	        }
	        
	        if (b == 0) {
	            return a;
	        }
	        return gcd(b, a%b);
		}


		/*
		**	Input string contains only digits
		*/
		int getInt(string s) {
	        int res;
	        for (char ch: s) {
	        	res = 10 * res + (ch - '0');
	        }
	        return res;
		}

};