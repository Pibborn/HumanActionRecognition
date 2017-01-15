#include <iostream>
#include <fstream>
#include <mex.h>
#include "Eigen/Cholesky"
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

// mahalanobis distance between observations in the x matrix
VectorXd mah(MatrixXd& x){
    MatrixXd xs = x;
    int ps = xs.cols(), ns=xs.rows();
    RowVectorXd xs_mean=xs.colwise().sum()/ns;
    MatrixXd xs_cen = (xs.rowwise()-xs_mean);
    MatrixXd x_cen = (x.rowwise()-xs_mean);
    MatrixXd w = xs_cen.transpose()*xs_cen/(ns-1);
    MatrixXd b = MatrixXd::Identity(ps,ps);
    w.ldlt().solveInPlace(b);
    x_cen = (x_cen*b).cwiseProduct(x_cen);
    return x_cen.rowwise().sum();
}

// pairwise mahalanobis distance between observations in the x and xs matrix
VectorXd mah_2(MatrixXd& x, MatrixXd& xs){
    int ps = xs.cols(), ns=xs.rows();
    RowVectorXd xs_mean=xs.colwise().sum()/ns;
    MatrixXd xs_cen = (xs.rowwise()-xs_mean);
    MatrixXd x_cen = (x.rowwise()-xs_mean);
    MatrixXd w = xs_cen.transpose()*xs_cen/(ns-1);
    MatrixXd b = MatrixXd::Identity(ps,ps);
    w.ldlt().solveInPlace(b);
    x_cen = (x_cen*b).cwiseProduct(x_cen);
    return x_cen.rowwise().sum();
}

// gateway function
void mexFunction(int num_inputs, const mxArray *inputs[],
                 int num_outputs, mxArray *outputs[]) {
    if (num_inputs != 2 || num_inputs != 1) {
        throw std::invalid_argument("Two inputs (or one) are required.");
    }

    if (num_outputs != 1) {
        throw std::invalid_argument("One output is required.");
    }

    Mex::ConstMatrix<double, Eigen::Dynamic, Eigen::Dynamic> in_mat(inputs[0]);

    if (num_inputs == 2) {
        Mex::ConstMatrix<double, Eigen::Dynamic, Eigen::Dynamic> in_mat_2(inputs[1]);
        VectorXd result = mah_2(in_mat, in_mat2);
    } else {
        VectorXd result = mah(in_mat);
    }

    Mex::OutputMatrix<double, Eigen::Dynamic, Eigen::Dynamic> out_mat = result;
    outputs[0] = out_mat;
}

MatrixXd sub(MatrixXd&  x, VectorXi& s){
    int p = x.cols();
    MatrixXd xs(p+1,p);
    for(int i=0;i<s.size();i++){
        xs.row(i)=x.row(s(i));
    }
    return xs;
}

int main() {
    MatrixXd x = MatrixXd::Random(3,3);
    MatrixXd y = x;
    x(0, 0) += 1;
    cout << x << endl;
    cout << y << endl;
}
/*int main(){
    int n = 2;
    int p = 1;
    MatrixXd x = MatrixXd::Random(30,3);
    VectorXi s = VectorXd::Random(p+1)*n;
    MatrixXd xs = sub(x,s);
    ofstream file("test1.txt");
    if (file.is_open()){
            file <<  x << '\n';
    }
    cout << "m" << endl <<  mah(x,xs) << endl;
    cout << "s" << endl <<  s << endl;
    return 0;
}*/
