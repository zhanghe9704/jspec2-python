#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>

#include "../jspec2/include/ecooling.h"

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;

void init_ecooling(py::module& m) {
    py::enum_<IonSample>(m, "IonSample", py::arithmetic())
        .value("SINGLE_PARTICLE", IonSample::SINGLE_PARTICLE)
        .value("MONTE_CARLO", IonSample::MONTE_CARLO);

    py::enum_<ECoolRateScratch>(m, "ECoolRateScratch", py::arithmetic())
        .value("XP_BET", ECoolRateScratch::XP_BET)
        .value("YP_BET", ECoolRateScratch::YP_BET)
        .value("XP", ECoolRateScratch::XP)
        .value("YP", ECoolRateScratch::YP)
        .value("DP_P", ECoolRateScratch::DP_P)
        .value("V_TR", ECoolRateScratch::V_TR)
        .value("V_LONG", ECoolRateScratch::V_LONG)
        .value("FORCE_X", ECoolRateScratch::FORCE_X)
        .value("FORCE_Y", ECoolRateScratch::FORCE_Y)
        .value("FORCE_Z", ECoolRateScratch::FORCE_Z);

    py::class_<ECoolRate>(m, "ECool")
        .def(py::init<>())
        .def("set_save_force", &ECoolRate::set_save_force)
        .def("set_dual_force_solver", &ECoolRate::set_dual_force_solver)
        .def("set_second_force_solver", &ECoolRate::set_second_force_solver)
        .def("adjust_rate", &ECoolRate::adjust_rate)
        .def("scratch", &ECoolRate::scratch)
        .def("t_cooler", &ECoolRate::t_cooler)
        .def("set_n_long_sample", &ECoolRate::set_n_long_sample)
        .def("ecool_rate", &ECoolRate::ecool_rate)
        .def("rate", (std::tuple<double,double,double>(ECoolRate::*)(FrictionForceSolver&, Beam&, int, Cooler&, EBeam&,Ring&))
             &ECoolRate::rate, "force"_a, "ion"_a, "n_sample"_a, "cooler"_a, "ebeam"_a, "ring"_a)
        .def("rate", (std::tuple<double,double,double>(ECoolRate::*)(FrictionForceSolver&, Beam&, Ions&, Cooler&, EBeam&,Ring&))
             &ECoolRate::rate, "force"_a, "ion"_a, "ion_sample"_a, "cooler"_a, "ebeam"_a, "ring"_a);

    py::class_<ForceCurve, ECoolRate>(m, "ForceCurve")
        .def("set_n_tr", &ForceCurve::set_n_tr)
        .def("set_electron_density", &ForceCurve::set_electron_density)
        .def("set_dp_p", &ForceCurve::set_dp_p)
        .def("set_angle", &ForceCurve::set_angle)
        .def("force_to_file", &ForceCurve::force_to_file);
}
