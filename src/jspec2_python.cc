#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;


void init_beam(py::module &);
void init_ring(py::module &);
void init_ibs(py::module &);
void init_cooler(py::module &);
void init_ecooling(py::module &);

PYBIND11_MODULE(jspec, m) {
    m.doc() = "JSPEC lib";
    init_beam(m);
    init_ring(m);
    init_ibs(m);
    init_cooler(m);
    init_ecooling(m);

}
