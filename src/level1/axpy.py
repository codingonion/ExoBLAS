from __future__ import annotations

from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.syntax import *
from exo.stdlib.scheduling import *
import exo.API_cursors as pc

import exo_blas_config as C
from composed_schedules import (
    vectorize,
    interleave_execution,
    apply_to_block,
    hoist_stmt,
)


### EXO_LOC ALGORITHM START ###
@proc
def axpy_template(n: size, alpha: R, x: [R][n], y: [R][n]):
    for i in seq(0, n):
        y[i] += alpha * x[i]


@proc
def axpy_template_alpha_1(n: size, x: [R][n], y: [R][n]):
    for i in seq(0, n):
        y[i] += x[i]
### EXO_LOC ALGORITHM END ###


### EXO_LOC SCHEDULE START ###
def specialize_axpy(precision, alpha):
    prefix = "s" if precision == "f32" else "d"
    specialized_axpy = axpy_template if alpha != 1 else axpy_template_alpha_1
    axpy_template_name = specialized_axpy.name()
    axpy_template_name = axpy_template_name.replace("_template", "")
    specialized_axpy = rename(specialized_axpy, "exo_" + prefix + axpy_template_name)

    args = ["x", "y"]
    if alpha != 1:
        args.append("alpha")

    for arg in args:
        specialized_axpy = set_precision(specialized_axpy, arg, precision)
    return specialized_axpy


def schedule_interleave_axpy_stride_1(
    VEC_W, INTERLEAVE_FACTOR, memory, instructions, precision, alpha
):
    simple_stride_1 = specialize_axpy(precision, alpha)
    simple_stride_1 = rename(simple_stride_1, simple_stride_1.name() + "_stride_1")
    simple_stride_1 = simple_stride_1.add_assertion("stride(x, 0) == 1")
    simple_stride_1 = simple_stride_1.add_assertion("stride(y, 0) == 1")

    main_loop = simple_stride_1.find_loop("i")
    simple_stride_1 = vectorize(simple_stride_1, main_loop, VEC_W, memory, precision)
    simple_stride_1 = interleave_execution(
        simple_stride_1, simple_stride_1.find_loop("io"), INTERLEAVE_FACTOR
    )
    simple_stride_1 = apply_to_block(
        simple_stride_1, simple_stride_1.find_loop("ioo").body(), hoist_stmt
    )
    simple_stride_1 = replace_all(simple_stride_1, instructions)
    return simplify(simple_stride_1)


#################################################
# Generate specialized kernels for f32 precision
#################################################

INTERLEAVE_FACTOR = C.Machine.vec_units * 2

exo_saxpy_stride_any = specialize_axpy("f32", None)
exo_saxpy_stride_any = rename(
    exo_saxpy_stride_any, exo_saxpy_stride_any.name() + "_stride_any"
)

f32_instructions = [
    C.Machine.load_instr_f32,
    C.Machine.store_instr_f32,
    C.Machine.broadcast_scalar_instr_f32,
    C.Machine.fmadd_instr_f32,
    C.Machine.reduce_add_wide_instr_f32,
]
if None not in f32_instructions:
    exo_saxpy_stride_1 = schedule_interleave_axpy_stride_1(
        C.Machine.vec_width,
        INTERLEAVE_FACTOR,
        C.Machine.mem_type,
        f32_instructions,
        "f32",
        None,
    )
    exo_saxpy_alpha_1_stride_1 = schedule_interleave_axpy_stride_1(
        C.Machine.vec_width,
        INTERLEAVE_FACTOR,
        C.Machine.mem_type,
        f32_instructions,
        "f32",
        1,
    )
else:
    exo_saxpy_stride_1 = specialize_axpy("f32", None)
    exo_saxpy_stride_1 = rename(
        exo_saxpy_stride_1, exo_saxpy_stride_1.name() + "_stride_1"
    )
    exo_saxpy_alpha_1_stride_1 = specialize_axpy("f32", 1)
    exo_saxpy_alpha_1_stride_1 = rename(
        exo_saxpy_alpha_1_stride_1, exo_saxpy_alpha_1_stride_1.name() + "_stride_1"
    )

#################################################
# Generate specialized kernels for f64 precision
#################################################

exo_daxpy_stride_any = specialize_axpy("f64", None)
exo_daxpy_stride_any = rename(
    exo_daxpy_stride_any, exo_daxpy_stride_any.name() + "_stride_any"
)

f64_instructions = [
    C.Machine.load_instr_f64,
    C.Machine.store_instr_f64,
    C.Machine.broadcast_scalar_instr_f64,
    C.Machine.fmadd_instr_f64,
    C.Machine.reduce_add_wide_instr_f64,
]

if None not in f64_instructions:
    exo_daxpy_stride_1 = schedule_interleave_axpy_stride_1(
        C.Machine.vec_width // 2,
        INTERLEAVE_FACTOR,
        C.Machine.mem_type,
        f64_instructions,
        "f64",
        None,
    )
    exo_daxpy_alpha_1_stride_1 = schedule_interleave_axpy_stride_1(
        C.Machine.vec_width // 2,
        INTERLEAVE_FACTOR,
        C.Machine.mem_type,
        f64_instructions,
        "f64",
        1,
    )
else:
    exo_daxpy_stride_1 = specialize_axpy("f64", None)
    exo_daxpy_stride_1 = rename(
        exo_daxpy_stride_1, exo_daxpy_stride_1.name() + "_stride_1"
    )
    exo_daxpy_alpha_1_stride_1 = specialize_axpy("f64", 1)
    exo_daxpy_alpha_1_stride_1 = rename(
        exo_daxpy_alpha_1_stride_1, exo_daxpy_alpha_1_stride_1.name() + "_stride_1"
    )
### EXO_LOC SCHEDULE END ###

entry_points = [
    exo_saxpy_stride_any,
    exo_saxpy_stride_1,
    exo_saxpy_alpha_1_stride_1,
    exo_daxpy_stride_any,
    exo_daxpy_stride_1,
    exo_daxpy_alpha_1_stride_1,
]

if __name__ == "__main__":
    for p in entry_points:
        print(p)

__all__ = [p.name() for p in entry_points]
