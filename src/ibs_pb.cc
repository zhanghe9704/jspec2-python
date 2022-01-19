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
        .def("log_c", &IBSSolver_Martini::log_c)
        .def("k", &IBSSolver_Martini::k)
        .def("set_log_c", &IBSSolver_Martini::set_log_c)
        .def("set_k", &IBSSolver_Martini::set_k)
        .def("set_ibs_by_element", &IBSSolver_Martini::set_ibs_by_element)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_Martini::rate));

    py::class_<IBSSolver_BM, IBSSolver>(m, "IBSSolver_BM")
        .def(py::init<double, double>(), py::arg("log_c"), py::arg("k") = 0)
        .def("log_c", &IBSSolver_BM::log_c)
        .def("k", &IBSSolver_BM::k)
        .def("set_log_c", &IBSSolver_BM::set_log_c)
        .def("set_k", &IBSSolver_BM::set_k)
        .def("set_ibs_by_element", &IBSSolver_BM::set_ibs_by_element)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_BM::rate));

    py::class_<IBSSolver_BMZ, IBSSolver>(m, "IBSSolver_BMZ")
        .def(py::init<int, double, double>(), py::arg("nt"), py::arg("log_c"), py::arg("k") = 0)
        .def("set_factor", &IBSSolver_BMZ::set_factor)
        .def("log_c", &IBSSolver_BMZ::log_c)
        .def("k", &IBSSolver_BMZ::k)
        .def("set_log_c", &IBSSolver_BMZ::set_log_c)
        .def("set_k", &IBSSolver_BMZ::set_k)
        .def("set_ibs_by_element", &IBSSolver_BMZ::set_ibs_by_element)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_BMZ::rate));

    py::class_<IBSSolver_BM_Complete, IBSSolver>(m, "IBSSolver_BMC")
        .def(py::init<int, double, double>(), py::arg("nt"), py::arg("log_c"), py::arg("k") = 0)
        .def("set_factor", &IBSSolver_BM_Complete::set_factor)
        .def("log_c", &IBSSolver_BM_Complete::log_c)
        .def("k", &IBSSolver_BM_Complete::k)
        .def("set_log_c", &IBSSolver_BM_Complete::set_log_c)
        .def("set_k", &IBSSolver_BM_Complete::set_k)
        .def("set_ibs_by_element", &IBSSolver_BM_Complete::set_ibs_by_element)
        .def("rate", py::overload_cast<const Lattice&, const Beam&>(&IBSSolver_BM_Complete::rate));

}
