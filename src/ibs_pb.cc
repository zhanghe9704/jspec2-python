#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>

#include "../jspec2/include/ibs.h"
#include "../jspec2/include/ring.h"

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;

void init_ibs(py::module& m) {
    py::enum_<IBSModel>(m, "IBSModel", py::arithmetic())
        .value("MARTINI", IBSModel::MARTINI)
        .value("BM", IBSModel::BM);

    py::class_<IBSSolver>(m, "IBSSolver");

    py::class_<IBSSolver_Martini, IBSSolver>(m, "IBSSolver_Martini")
        .def(py::init<int, int, int, double, double>(), py::arg("nu"), py::arg("nv"), py::arg("nz"), py::arg("log_c")=0, py::arg("k") = 0)
        .def("nu", &IBSSolver_Martini::nu)
        .def("nv", &IBSSolver_Martini::nv)
        .def("nz", &IBSSolver_Martini::nz)
        .def("set_nu", &IBSSolver_Martini::set_nu)
        .def("set_nv", &IBSSolver_Martini::set_nv)
        .def("set_nz", &IBSSolver_Martini::set_nz)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_Martini::rate));
//        .def("rate", &IBSSolver_Martini::rate);

    py::class_<IBSSolver_BM, IBSSolver>(m, "IBSSolver_BM")
        .def(py::init<double, double>(), py::arg("log_c"), py::arg("k") = 0)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_BM::rate));
//        .def("rate", &IBSSolver_BM::rate);

}
