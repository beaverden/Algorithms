struct matrix {
	unsigned int len;
	int values[10][10];

    matrix& operator *(const matrix& a)
    {
        matrix result;
        result.len = a.len;

        for (int i = 0; i<a.len; i++)
            for (int j = 0; j<a.len; j++) {
                result.values[i][j] = 0;
                for (int k = 0; k<a.len; k++)
                    result.values[i][j] += this->values[i][k] * a.values[k][j];
                }

        for (int i = 0; i<a.len; i++)
            for (int j = 0; j<a.len; j++)
                this->values[i][j] = result.values[i][j];

        return *this;
    }

    void print() {
        for (int i = 0; i<this->len; i++) {
            for (int j = 0; j<this->len; j++) {
                cout << this->values[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
matrix matrixExp(matrix a, int n) {
    matrix res;
    res.len = a.len;
    for (int i = 0; i<a.len; i++)
        for (int j = 0; j<a.len; j++)
            res.values[i][j] = (i==j);

    while (n) {
        if (n&1) {
            res = res*a;
        }
        n>>=1;
        a = a*a;
    }
    return res;
}