from __future__ import annotations

from exo.platforms.x86 import *

from .machine import MachineParameters

Machine = MachineParameters(
    name="avx512",
    mem_type=AVX512,
    n_vec_registers=32,
    vec_width=16,
    vec_units=2,
    l1_cache=None,
    l2_cache=None,
    l3_cache=None,
    load_instr_f32=mm512_loadu_ps,
    load_instr_f32_str="mm512_loadu_ps(_)",
    store_instr_f32=mm512_storeu_ps,
    broadcast_instr_f32=mm512_set1_ps,
    broadcast_instr_f32_str="mm512_set1_ps(_)",
    broadcast_scalar_instr_f32=None,
    fmadd_instr_f32=mm512_fmadd_ps,
    zpad_ld_instr=None,
    zpad_fmadd_instr=None,
    zpad_broadcast_instr=None,
    zpad_store_instr=None,
    set_zero_instr_f32=None,
    assoc_reduce_add_instr_f32=None,
    mul_instr_f32=None,
    add_instr_f32=None,
    reduce_add_wide_instr_f32=None,
    reg_copy_instr_f32=None,
    sign_instr_f32=None,
    select_instr_f32=None,
    
    load_instr_f64=None,
    store_instr_f64=None,
    broadcast_instr_f64=None,
    broadcast_scalar_instr_f64=None,
    fmadd_instr_f64=None,
    set_zero_instr_f64=None,
    assoc_reduce_add_instr_f64=None,
    mul_instr_f64=None,
    add_instr_f64=None,
    reduce_add_wide_instr_f64=None,
    reg_copy_instr_f64=None,
    sign_instr_f64=None,
    select_instr_f64=None,
)
