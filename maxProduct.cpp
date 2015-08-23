����һ��double���͵�����arr�����е�Ԫ�ؿ����ɸ���0�������������۳˵����˻�������arr=[-2.5��4��0��3��0.5��8��-1]��
������[3��0.5��8]�۳˿��Ի�����ĳ˻�12�����Է���12��
class Solution {
public:
    double maxProduct(vector<double> arr) {
        if (arr.size()<1)
            return 0;
        if (arr.size()==1)
            return arr[0];
        
        int n=arr.size();
        double* max_tbl=new double[n];
        double* min_tbl=new double[n];
        max_tbl[0]=min_tbl[0]=arr[0];
        for(int i=1;i<n;i++) {
            double val=arr[i];
            max_tbl[i]=max(val,max(val*max_tbl[i-1],val*min_tbl[i-1]));
            min_tbl[i]=min(val,min(val*max_tbl[i-1],val*min_tbl[i-1]));
                   
        }
        double res=max_tbl[0];
        for(int i=0;i<n;i++) {
            if(res<max_tbl[i])
                res=max_tbl[i];
        }
        return res;

    }
};