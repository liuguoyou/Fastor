#include <Fastor.h>

using namespace Fastor;


#define Tol 1e-12
#define BigTol 1e-5


template<typename T>
void test_linalg() {

    // 2D 
    {
        Tensor<T,2,2> t1; t1.iota(5);
        assert(std::abs(determinant(t1)+2.0)< BigTol);
        assert(std::abs(trace(t1)-13)< Tol);
        assert(std::abs(norm(matmul(t1,t1)) - 173.4646938) < BigTol);
        assert(std::abs(norm(cofactor(t1)) - 13.1909059) < BigTol);
        assert(std::abs(norm(transpose(adjoint(t1))) - 13.1909059) < BigTol);

        assert(std::abs(norm(static_cast<Tensor<T>>(ldeterminant(t1)))+2.)< Tol);
        assert(std::abs(norm(static_cast<Tensor<T>>(ltrace(t1))) - 13)< Tol);
        assert(std::abs(norm(static_cast<Tensor<T,2,2>>(lmatmul(t1,t1))) - 173.4646938)< BigTol);
        assert(std::abs(norm(static_cast<Tensor<T,2,2>>(lcofactor(t1))) - 13.1909059)< BigTol);
        assert(std::abs(norm(static_cast<Tensor<T,2,2>>(ltranspose(ladjoint(t1)))) - 13.1909059)< BigTol);

        Tensor<T,2> t2; t2.iota(102);
        assert(std::abs(norm(outer(t2,t2)) - 21013.0) < Tol);
        assert(std::abs(inner(t2,t2) - 21013.0) < Tol);
    }

    // 3D
    {
        Tensor<T,3,3> t1; t1.iota(0);
        assert(std::abs(determinant(t1))< Tol);
        assert(std::abs(trace(t1)-12)< Tol);
        assert(std::abs(norm(matmul(t1,t1)) - 187.637949) < BigTol);
        assert(std::abs(norm(cofactor(t1)) - 18) < BigTol);
        assert(std::abs(norm(transpose(adjoint(t1))) - 18) < BigTol);

        assert(std::abs(norm(static_cast<Tensor<T>>(ldeterminant(t1))))< Tol);
        assert(std::abs(norm(static_cast<Tensor<T>>(ltrace(t1))) - 12)< Tol);
        assert(std::abs(norm(static_cast<Tensor<T,3,3>>(lmatmul(t1,t1))) - 187.637949)< BigTol);
        assert(std::abs(norm(static_cast<Tensor<T,3,3>>(lcofactor(t1))) - 18)< BigTol);
        assert(std::abs(norm(static_cast<Tensor<T,3,3>>(ltranspose(ladjoint(t1)))) - 18)< BigTol);

        Tensor<T,3> t2; t2.iota(102);
        assert(std::abs(norm(outer(t2,t2)) - 31829.0) < Tol);
        assert(std::abs(inner(t2,t2) - 31829.0) < Tol);
    }

    print(FGRN(BOLD("All tests passed successfully")));

}

int main() {

    print(FBLU(BOLD("Testing tensor algebra routines: single precision")));
    test_linalg<float>();
    print(FBLU(BOLD("Testing tensor algebra routines: double precision")));
    test_linalg<double>();

    return 0;
}

