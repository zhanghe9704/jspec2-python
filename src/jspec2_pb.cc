#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>

#ifdef _OPENMP
    #include <omp.h>
#endif // _OPENMP

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;


void init_beam(py::module &);
void init_ring(py::module &);
void init_ibs(py::module &);
void init_cooler(py::module &);
void init_ecooling(py::module &);
void init_force(py::module &);
void init_ions(py::module &);
void init_luminosity(py::module &);
void init_simulators(py::module &);

PYBIND11_MODULE(jspec, m) {
    m.doc() = "JSPEC lib";
    m.def("set_n_thread", [](int n){
        int res = -1;
        #ifdef _OPENMP
        omp_set_num_threads(n);
        #pragma omp parallel
        {
            res = 0;
            if(omp_get_thread_num() == 0) {
                res = omp_get_num_threads();
                std::cout<<"OPENMP thread number set to be: "<<res<<std::endl;
            }
        }
        #else
        std::cout<<std::endl<<"<<< WARNING: OPENMP NOT SUPPORTED! PLEASE RECOMPILE! >>>"<<std::endl<<std::endl;
        #endif
        return res;
      })
      .def("get_n_thread", [](){
        int n = -1;
        #ifdef _OPENMP
        #pragma omp parallel
        {
            n = 0;
            if(omp_get_thread_num() == 0) {
                n = omp_get_num_threads();
                std::cout<<"OPENMP thread number set to be: "<<n<<std::endl;
            }
        }
        #else
        std::cout<<std::endl<<"<<< WARNING: OPENMP NOT SUPPORTED! PLEASE RECOMPILE! >>>"<<std::endl<<std::endl;
        #endif
        return n;
      });
    init_beam(m);
    init_ring(m);
    init_ibs(m);
    init_cooler(m);
    init_ecooling(m);
    init_force(m);
    init_ions(m);
    init_luminosity(m);
    init_simulators(m);
}
