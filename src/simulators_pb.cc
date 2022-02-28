#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>
#include <string>


#include "../jspec2/include/simulator.h"
#include "../jspec2/include/particle_model.h"
#include "../jspec2/include/rms_dynamic.h"
#include "../jspec2/include/turn_by_turn.h"

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;

void init_simulators(py::module& m) {
    py::class_<Simulator>(m, "Simulator");

    py::class_<ParticleModel, Simulator>(m, "ParticleModel")
        .def(py::init<double, int>(),py::arg("time"),py::arg("n_step"))
        .def("set_ibs", &ParticleModel::set_ibs)
        .def("set_ecool", &ParticleModel::set_ecool)
        .def("set_ion_save", &ParticleModel::set_ion_save)
        .def("set_output_file", &ParticleModel::set_output_file)
        .def("set_output_intvl", &ParticleModel::set_output_intvl)
        .def("set_fixed_bunch_length", &ParticleModel::set_fixed_bunch_length)
        .def("set_ini_time", &ParticleModel::set_ini_time)
        .def("set_reset_time", &ParticleModel::set_reset_time)
        .def("set_overwrite", &ParticleModel::set_overwrite)
        .def("set_calc_lum", &ParticleModel::set_calc_lum)
        .def("run", &ParticleModel::run)
        .def("resize_rdn", &ParticleModel::resize_rdn);

    py::class_<RMSModel, Simulator>(m, "RMSModel")
        .def(py::init<double, int>(),py::arg("time"),py::arg("n_step"))
        .def("set_ibs", &RMSModel::set_ibs)
        .def("set_ecool", &RMSModel::set_ecool)
        .def("set_ion_save", &RMSModel::set_ion_save)
        .def("set_output_file", &RMSModel::set_output_file)
        .def("set_output_intvl", &RMSModel::set_output_intvl)
        .def("set_fixed_bunch_length", &RMSModel::set_fixed_bunch_length)
        .def("set_ini_time", &RMSModel::set_ini_time)
        .def("set_reset_time", &RMSModel::set_reset_time)
        .def("set_overwrite", &RMSModel::set_overwrite)
        .def("set_calc_lum", &RMSModel::set_calc_lum)
        .def("run", &RMSModel::run);

    py::class_<TurnByTurnModel, ParticleModel>(m, "TurnByTurnModel")
        .def(py::init<double, int>(),py::arg("time"),py::arg("n_step"))
        .def("set_ibs", &TurnByTurnModel::set_ibs)
        .def("set_ecool", &TurnByTurnModel::set_ecool)
        .def("set_ion_save", &TurnByTurnModel::set_ion_save)
        .def("set_output_file", &TurnByTurnModel::set_output_file)
        .def("set_output_intvl", &TurnByTurnModel::set_output_intvl)
        .def("set_fixed_bunch_length", &TurnByTurnModel::set_fixed_bunch_length)
        .def("set_ini_time", &TurnByTurnModel::set_ini_time)
        .def("set_reset_time", &TurnByTurnModel::set_reset_time)
        .def("set_overwrite", &TurnByTurnModel::set_overwrite)
        .def("set_calc_lum", &TurnByTurnModel::set_calc_lum)
        .def("run", &TurnByTurnModel::run);
}
