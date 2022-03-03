class pri_q{
    private:
        int len;
        vector<int> pq;

    public:
        pri_q(){
            len=1;
            pq= vector<int>(1, NULL);
        }

        bool empty(){
            if(len== 1) return true;
            return false;
        }

        insert(int a){
        	pq.push_back(a);
        	int i= len;
            while(i > 1 && pq[i] > pq[i/2]){
                swap(i ,i/2);
                i= i/2;
            }
            len= len+1;
        }

        int top(){
            if(pq.size()==1) return NULL;
            return pq[1];
        }

        int pop(){
            if(pq.size()==1) return NULL;
            ans= pq[1];
            pq[1]= pq[len];
            len= len-1;
            max_heapify(1);
            return ans;
        }

        void max_heapify(int i){
            int left= 2*i;
            int right= 2*i+1;
            int largest= i;

            if(left<=len && pq[left] > pq[largest])
                largest= left;
            if(right<=len && pq[right] > pq[largest])
                largest= right;
            
            if(largest != i){
                swap(largest, i);
                max_heapify(largest);
            }
        }

        void swap(int i, int j){
            int temp= pq[i];
            pq[i]= pq[j];
            pq[j]=temp;
        }
};