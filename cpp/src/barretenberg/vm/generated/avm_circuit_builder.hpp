

// AUTOGENERATED FILE
#pragma once

#include "barretenberg/common/constexpr_utils.hpp"
#include "barretenberg/common/throw_or_abort.hpp"
#include "barretenberg/ecc/curves/bn254/fr.hpp"
#include "barretenberg/honk/proof_system/logderivative_library.hpp"
#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"
#include "barretenberg/relations/generic_permutation/generic_permutation_relation.hpp"
#include "barretenberg/stdlib_circuit_builders/circuit_builder_base.hpp"

#include "barretenberg/relations/generated/avm/avm_alu.hpp"
#include "barretenberg/relations/generated/avm/avm_binary.hpp"
#include "barretenberg/relations/generated/avm/avm_main.hpp"
#include "barretenberg/relations/generated/avm/avm_mem.hpp"
#include "barretenberg/relations/generated/avm/incl_main_tag_err.hpp"
#include "barretenberg/relations/generated/avm/incl_mem_tag_err.hpp"
#include "barretenberg/relations/generated/avm/lookup_byte_lengths.hpp"
#include "barretenberg/relations/generated/avm/lookup_byte_operations.hpp"
#include "barretenberg/relations/generated/avm/lookup_pow_2_0.hpp"
#include "barretenberg/relations/generated/avm/lookup_pow_2_1.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_0.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_1.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_10.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_11.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_12.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_13.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_14.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_2.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_3.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_4.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_5.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_6.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_7.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_8.hpp"
#include "barretenberg/relations/generated/avm/lookup_u16_9.hpp"
#include "barretenberg/relations/generated/avm/lookup_u8_0.hpp"
#include "barretenberg/relations/generated/avm/lookup_u8_1.hpp"
#include "barretenberg/relations/generated/avm/perm_main_alu.hpp"
#include "barretenberg/relations/generated/avm/perm_main_bin.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_a.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_b.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_c.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_d.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_ind_a.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_ind_b.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_ind_c.hpp"
#include "barretenberg/relations/generated/avm/perm_main_mem_ind_d.hpp"
#include "barretenberg/vm/generated/avm_flavor.hpp"

namespace bb {

template <typename FF> struct AvmFullRow {
    FF avm_main_clk{};
    FF avm_main_first{};
    FF avm_alu_a_hi{};
    FF avm_alu_a_lo{};
    FF avm_alu_alu_sel{};
    FF avm_alu_b_hi{};
    FF avm_alu_b_lo{};
    FF avm_alu_borrow{};
    FF avm_alu_cf{};
    FF avm_alu_clk{};
    FF avm_alu_cmp_rng_ctr{};
    FF avm_alu_cmp_sel{};
    FF avm_alu_ff_tag{};
    FF avm_alu_ia{};
    FF avm_alu_ib{};
    FF avm_alu_ic{};
    FF avm_alu_in_tag{};
    FF avm_alu_op_add{};
    FF avm_alu_op_cast{};
    FF avm_alu_op_cast_prev{};
    FF avm_alu_op_div{};
    FF avm_alu_op_eq{};
    FF avm_alu_op_eq_diff_inv{};
    FF avm_alu_op_lt{};
    FF avm_alu_op_lte{};
    FF avm_alu_op_mul{};
    FF avm_alu_op_not{};
    FF avm_alu_op_shl{};
    FF avm_alu_op_shr{};
    FF avm_alu_op_sub{};
    FF avm_alu_p_a_borrow{};
    FF avm_alu_p_b_borrow{};
    FF avm_alu_p_sub_a_hi{};
    FF avm_alu_p_sub_a_lo{};
    FF avm_alu_p_sub_b_hi{};
    FF avm_alu_p_sub_b_lo{};
    FF avm_alu_res_hi{};
    FF avm_alu_res_lo{};
    FF avm_alu_rng_chk_lookup_selector{};
    FF avm_alu_rng_chk_sel{};
    FF avm_alu_shift_lt_bit_len{};
    FF avm_alu_shift_sel{};
    FF avm_alu_t_sub_s_bits{};
    FF avm_alu_two_pow_s{};
    FF avm_alu_two_pow_t_sub_s{};
    FF avm_alu_u128_tag{};
    FF avm_alu_u16_r0{};
    FF avm_alu_u16_r1{};
    FF avm_alu_u16_r10{};
    FF avm_alu_u16_r11{};
    FF avm_alu_u16_r12{};
    FF avm_alu_u16_r13{};
    FF avm_alu_u16_r14{};
    FF avm_alu_u16_r2{};
    FF avm_alu_u16_r3{};
    FF avm_alu_u16_r4{};
    FF avm_alu_u16_r5{};
    FF avm_alu_u16_r6{};
    FF avm_alu_u16_r7{};
    FF avm_alu_u16_r8{};
    FF avm_alu_u16_r9{};
    FF avm_alu_u16_tag{};
    FF avm_alu_u32_tag{};
    FF avm_alu_u64_tag{};
    FF avm_alu_u8_r0{};
    FF avm_alu_u8_r1{};
    FF avm_alu_u8_tag{};
    FF avm_binary_acc_ia{};
    FF avm_binary_acc_ib{};
    FF avm_binary_acc_ic{};
    FF avm_binary_bin_sel{};
    FF avm_binary_clk{};
    FF avm_binary_ia_bytes{};
    FF avm_binary_ib_bytes{};
    FF avm_binary_ic_bytes{};
    FF avm_binary_in_tag{};
    FF avm_binary_mem_tag_ctr{};
    FF avm_binary_mem_tag_ctr_inv{};
    FF avm_binary_op_id{};
    FF avm_binary_start{};
    FF avm_byte_lookup_bin_sel{};
    FF avm_byte_lookup_table_byte_lengths{};
    FF avm_byte_lookup_table_in_tags{};
    FF avm_byte_lookup_table_input_a{};
    FF avm_byte_lookup_table_input_b{};
    FF avm_byte_lookup_table_op_id{};
    FF avm_byte_lookup_table_output{};
    FF avm_main_alu_in_tag{};
    FF avm_main_alu_sel{};
    FF avm_main_bin_op_id{};
    FF avm_main_bin_sel{};
    FF avm_main_ia{};
    FF avm_main_ib{};
    FF avm_main_ic{};
    FF avm_main_id{};
    FF avm_main_id_zero{};
    FF avm_main_ind_a{};
    FF avm_main_ind_b{};
    FF avm_main_ind_c{};
    FF avm_main_ind_d{};
    FF avm_main_ind_op_a{};
    FF avm_main_ind_op_b{};
    FF avm_main_ind_op_c{};
    FF avm_main_ind_op_d{};
    FF avm_main_internal_return_ptr{};
    FF avm_main_inv{};
    FF avm_main_last{};
    FF avm_main_mem_idx_a{};
    FF avm_main_mem_idx_b{};
    FF avm_main_mem_idx_c{};
    FF avm_main_mem_idx_d{};
    FF avm_main_mem_op_a{};
    FF avm_main_mem_op_b{};
    FF avm_main_mem_op_c{};
    FF avm_main_mem_op_d{};
    FF avm_main_op_err{};
    FF avm_main_pc{};
    FF avm_main_r_in_tag{};
    FF avm_main_rwa{};
    FF avm_main_rwb{};
    FF avm_main_rwc{};
    FF avm_main_rwd{};
    FF avm_main_sel_cmov{};
    FF avm_main_sel_halt{};
    FF avm_main_sel_internal_call{};
    FF avm_main_sel_internal_return{};
    FF avm_main_sel_jump{};
    FF avm_main_sel_mov{};
    FF avm_main_sel_mov_a{};
    FF avm_main_sel_mov_b{};
    FF avm_main_sel_op_add{};
    FF avm_main_sel_op_and{};
    FF avm_main_sel_op_cast{};
    FF avm_main_sel_op_div{};
    FF avm_main_sel_op_eq{};
    FF avm_main_sel_op_fdiv{};
    FF avm_main_sel_op_lt{};
    FF avm_main_sel_op_lte{};
    FF avm_main_sel_op_mul{};
    FF avm_main_sel_op_not{};
    FF avm_main_sel_op_or{};
    FF avm_main_sel_op_shl{};
    FF avm_main_sel_op_shr{};
    FF avm_main_sel_op_sub{};
    FF avm_main_sel_op_xor{};
    FF avm_main_sel_rng_16{};
    FF avm_main_sel_rng_8{};
    FF avm_main_table_pow_2{};
    FF avm_main_tag_err{};
    FF avm_main_w_in_tag{};
    FF avm_mem_addr{};
    FF avm_mem_clk{};
    FF avm_mem_ind_op_a{};
    FF avm_mem_ind_op_b{};
    FF avm_mem_ind_op_c{};
    FF avm_mem_ind_op_d{};
    FF avm_mem_last{};
    FF avm_mem_lastAccess{};
    FF avm_mem_one_min_inv{};
    FF avm_mem_op_a{};
    FF avm_mem_op_b{};
    FF avm_mem_op_c{};
    FF avm_mem_op_d{};
    FF avm_mem_r_in_tag{};
    FF avm_mem_rw{};
    FF avm_mem_sel_cmov{};
    FF avm_mem_sel_mov_a{};
    FF avm_mem_sel_mov_b{};
    FF avm_mem_skip_check_tag{};
    FF avm_mem_sub_clk{};
    FF avm_mem_tag{};
    FF avm_mem_tag_err{};
    FF avm_mem_val{};
    FF avm_mem_w_in_tag{};
    FF perm_main_alu{};
    FF perm_main_bin{};
    FF perm_main_mem_a{};
    FF perm_main_mem_b{};
    FF perm_main_mem_c{};
    FF perm_main_mem_d{};
    FF perm_main_mem_ind_a{};
    FF perm_main_mem_ind_b{};
    FF perm_main_mem_ind_c{};
    FF perm_main_mem_ind_d{};
    FF lookup_byte_lengths{};
    FF lookup_byte_operations{};
    FF incl_main_tag_err{};
    FF incl_mem_tag_err{};
    FF lookup_pow_2_0{};
    FF lookup_pow_2_1{};
    FF lookup_u8_0{};
    FF lookup_u8_1{};
    FF lookup_u16_0{};
    FF lookup_u16_1{};
    FF lookup_u16_2{};
    FF lookup_u16_3{};
    FF lookup_u16_4{};
    FF lookup_u16_5{};
    FF lookup_u16_6{};
    FF lookup_u16_7{};
    FF lookup_u16_8{};
    FF lookup_u16_9{};
    FF lookup_u16_10{};
    FF lookup_u16_11{};
    FF lookup_u16_12{};
    FF lookup_u16_13{};
    FF lookup_u16_14{};
    FF lookup_byte_lengths_counts{};
    FF lookup_byte_operations_counts{};
    FF incl_main_tag_err_counts{};
    FF incl_mem_tag_err_counts{};
    FF lookup_pow_2_0_counts{};
    FF lookup_pow_2_1_counts{};
    FF lookup_u8_0_counts{};
    FF lookup_u8_1_counts{};
    FF lookup_u16_0_counts{};
    FF lookup_u16_1_counts{};
    FF lookup_u16_2_counts{};
    FF lookup_u16_3_counts{};
    FF lookup_u16_4_counts{};
    FF lookup_u16_5_counts{};
    FF lookup_u16_6_counts{};
    FF lookup_u16_7_counts{};
    FF lookup_u16_8_counts{};
    FF lookup_u16_9_counts{};
    FF lookup_u16_10_counts{};
    FF lookup_u16_11_counts{};
    FF lookup_u16_12_counts{};
    FF lookup_u16_13_counts{};
    FF lookup_u16_14_counts{};
    FF avm_alu_a_hi_shift{};
    FF avm_alu_a_lo_shift{};
    FF avm_alu_alu_sel_shift{};
    FF avm_alu_b_hi_shift{};
    FF avm_alu_b_lo_shift{};
    FF avm_alu_cmp_rng_ctr_shift{};
    FF avm_alu_cmp_sel_shift{};
    FF avm_alu_op_add_shift{};
    FF avm_alu_op_cast_prev_shift{};
    FF avm_alu_op_cast_shift{};
    FF avm_alu_op_mul_shift{};
    FF avm_alu_op_shl_shift{};
    FF avm_alu_op_shr_shift{};
    FF avm_alu_op_sub_shift{};
    FF avm_alu_p_sub_a_hi_shift{};
    FF avm_alu_p_sub_a_lo_shift{};
    FF avm_alu_p_sub_b_hi_shift{};
    FF avm_alu_p_sub_b_lo_shift{};
    FF avm_alu_rng_chk_lookup_selector_shift{};
    FF avm_alu_rng_chk_sel_shift{};
    FF avm_alu_u16_r0_shift{};
    FF avm_alu_u16_r1_shift{};
    FF avm_alu_u16_r2_shift{};
    FF avm_alu_u16_r3_shift{};
    FF avm_alu_u16_r4_shift{};
    FF avm_alu_u16_r5_shift{};
    FF avm_alu_u16_r6_shift{};
    FF avm_alu_u8_r0_shift{};
    FF avm_alu_u8_r1_shift{};
    FF avm_binary_acc_ia_shift{};
    FF avm_binary_acc_ib_shift{};
    FF avm_binary_acc_ic_shift{};
    FF avm_binary_mem_tag_ctr_shift{};
    FF avm_binary_op_id_shift{};
    FF avm_main_internal_return_ptr_shift{};
    FF avm_main_pc_shift{};
    FF avm_mem_addr_shift{};
    FF avm_mem_rw_shift{};
    FF avm_mem_tag_shift{};
    FF avm_mem_val_shift{};
};

class AvmCircuitBuilder {
  public:
    using Flavor = bb::AvmFlavor;
    using FF = Flavor::FF;
    using Row = AvmFullRow<FF>;

    // TODO: template
    using Polynomial = Flavor::Polynomial;
    using ProverPolynomials = Flavor::ProverPolynomials;

    static constexpr size_t num_fixed_columns = 270;
    static constexpr size_t num_polys = 230;
    std::vector<Row> rows;

    void set_trace(std::vector<Row>&& trace) { rows = std::move(trace); }

    ProverPolynomials compute_polynomials()
    {
        const auto num_rows = get_circuit_subgroup_size();
        ProverPolynomials polys;

        // Allocate mem for each column
        for (auto& poly : polys.get_all()) {
            poly = Polynomial(num_rows);
        }

        for (size_t i = 0; i < rows.size(); i++) {
            polys.avm_main_clk[i] = rows[i].avm_main_clk;
            polys.avm_main_first[i] = rows[i].avm_main_first;
            polys.avm_alu_a_hi[i] = rows[i].avm_alu_a_hi;
            polys.avm_alu_a_lo[i] = rows[i].avm_alu_a_lo;
            polys.avm_alu_alu_sel[i] = rows[i].avm_alu_alu_sel;
            polys.avm_alu_b_hi[i] = rows[i].avm_alu_b_hi;
            polys.avm_alu_b_lo[i] = rows[i].avm_alu_b_lo;
            polys.avm_alu_borrow[i] = rows[i].avm_alu_borrow;
            polys.avm_alu_cf[i] = rows[i].avm_alu_cf;
            polys.avm_alu_clk[i] = rows[i].avm_alu_clk;
            polys.avm_alu_cmp_rng_ctr[i] = rows[i].avm_alu_cmp_rng_ctr;
            polys.avm_alu_cmp_sel[i] = rows[i].avm_alu_cmp_sel;
            polys.avm_alu_ff_tag[i] = rows[i].avm_alu_ff_tag;
            polys.avm_alu_ia[i] = rows[i].avm_alu_ia;
            polys.avm_alu_ib[i] = rows[i].avm_alu_ib;
            polys.avm_alu_ic[i] = rows[i].avm_alu_ic;
            polys.avm_alu_in_tag[i] = rows[i].avm_alu_in_tag;
            polys.avm_alu_op_add[i] = rows[i].avm_alu_op_add;
            polys.avm_alu_op_cast[i] = rows[i].avm_alu_op_cast;
            polys.avm_alu_op_cast_prev[i] = rows[i].avm_alu_op_cast_prev;
            polys.avm_alu_op_div[i] = rows[i].avm_alu_op_div;
            polys.avm_alu_op_eq[i] = rows[i].avm_alu_op_eq;
            polys.avm_alu_op_eq_diff_inv[i] = rows[i].avm_alu_op_eq_diff_inv;
            polys.avm_alu_op_lt[i] = rows[i].avm_alu_op_lt;
            polys.avm_alu_op_lte[i] = rows[i].avm_alu_op_lte;
            polys.avm_alu_op_mul[i] = rows[i].avm_alu_op_mul;
            polys.avm_alu_op_not[i] = rows[i].avm_alu_op_not;
            polys.avm_alu_op_shl[i] = rows[i].avm_alu_op_shl;
            polys.avm_alu_op_shr[i] = rows[i].avm_alu_op_shr;
            polys.avm_alu_op_sub[i] = rows[i].avm_alu_op_sub;
            polys.avm_alu_p_a_borrow[i] = rows[i].avm_alu_p_a_borrow;
            polys.avm_alu_p_b_borrow[i] = rows[i].avm_alu_p_b_borrow;
            polys.avm_alu_p_sub_a_hi[i] = rows[i].avm_alu_p_sub_a_hi;
            polys.avm_alu_p_sub_a_lo[i] = rows[i].avm_alu_p_sub_a_lo;
            polys.avm_alu_p_sub_b_hi[i] = rows[i].avm_alu_p_sub_b_hi;
            polys.avm_alu_p_sub_b_lo[i] = rows[i].avm_alu_p_sub_b_lo;
            polys.avm_alu_res_hi[i] = rows[i].avm_alu_res_hi;
            polys.avm_alu_res_lo[i] = rows[i].avm_alu_res_lo;
            polys.avm_alu_rng_chk_lookup_selector[i] = rows[i].avm_alu_rng_chk_lookup_selector;
            polys.avm_alu_rng_chk_sel[i] = rows[i].avm_alu_rng_chk_sel;
            polys.avm_alu_shift_lt_bit_len[i] = rows[i].avm_alu_shift_lt_bit_len;
            polys.avm_alu_shift_sel[i] = rows[i].avm_alu_shift_sel;
            polys.avm_alu_t_sub_s_bits[i] = rows[i].avm_alu_t_sub_s_bits;
            polys.avm_alu_two_pow_s[i] = rows[i].avm_alu_two_pow_s;
            polys.avm_alu_two_pow_t_sub_s[i] = rows[i].avm_alu_two_pow_t_sub_s;
            polys.avm_alu_u128_tag[i] = rows[i].avm_alu_u128_tag;
            polys.avm_alu_u16_r0[i] = rows[i].avm_alu_u16_r0;
            polys.avm_alu_u16_r1[i] = rows[i].avm_alu_u16_r1;
            polys.avm_alu_u16_r10[i] = rows[i].avm_alu_u16_r10;
            polys.avm_alu_u16_r11[i] = rows[i].avm_alu_u16_r11;
            polys.avm_alu_u16_r12[i] = rows[i].avm_alu_u16_r12;
            polys.avm_alu_u16_r13[i] = rows[i].avm_alu_u16_r13;
            polys.avm_alu_u16_r14[i] = rows[i].avm_alu_u16_r14;
            polys.avm_alu_u16_r2[i] = rows[i].avm_alu_u16_r2;
            polys.avm_alu_u16_r3[i] = rows[i].avm_alu_u16_r3;
            polys.avm_alu_u16_r4[i] = rows[i].avm_alu_u16_r4;
            polys.avm_alu_u16_r5[i] = rows[i].avm_alu_u16_r5;
            polys.avm_alu_u16_r6[i] = rows[i].avm_alu_u16_r6;
            polys.avm_alu_u16_r7[i] = rows[i].avm_alu_u16_r7;
            polys.avm_alu_u16_r8[i] = rows[i].avm_alu_u16_r8;
            polys.avm_alu_u16_r9[i] = rows[i].avm_alu_u16_r9;
            polys.avm_alu_u16_tag[i] = rows[i].avm_alu_u16_tag;
            polys.avm_alu_u32_tag[i] = rows[i].avm_alu_u32_tag;
            polys.avm_alu_u64_tag[i] = rows[i].avm_alu_u64_tag;
            polys.avm_alu_u8_r0[i] = rows[i].avm_alu_u8_r0;
            polys.avm_alu_u8_r1[i] = rows[i].avm_alu_u8_r1;
            polys.avm_alu_u8_tag[i] = rows[i].avm_alu_u8_tag;
            polys.avm_binary_acc_ia[i] = rows[i].avm_binary_acc_ia;
            polys.avm_binary_acc_ib[i] = rows[i].avm_binary_acc_ib;
            polys.avm_binary_acc_ic[i] = rows[i].avm_binary_acc_ic;
            polys.avm_binary_bin_sel[i] = rows[i].avm_binary_bin_sel;
            polys.avm_binary_clk[i] = rows[i].avm_binary_clk;
            polys.avm_binary_ia_bytes[i] = rows[i].avm_binary_ia_bytes;
            polys.avm_binary_ib_bytes[i] = rows[i].avm_binary_ib_bytes;
            polys.avm_binary_ic_bytes[i] = rows[i].avm_binary_ic_bytes;
            polys.avm_binary_in_tag[i] = rows[i].avm_binary_in_tag;
            polys.avm_binary_mem_tag_ctr[i] = rows[i].avm_binary_mem_tag_ctr;
            polys.avm_binary_mem_tag_ctr_inv[i] = rows[i].avm_binary_mem_tag_ctr_inv;
            polys.avm_binary_op_id[i] = rows[i].avm_binary_op_id;
            polys.avm_binary_start[i] = rows[i].avm_binary_start;
            polys.avm_byte_lookup_bin_sel[i] = rows[i].avm_byte_lookup_bin_sel;
            polys.avm_byte_lookup_table_byte_lengths[i] = rows[i].avm_byte_lookup_table_byte_lengths;
            polys.avm_byte_lookup_table_in_tags[i] = rows[i].avm_byte_lookup_table_in_tags;
            polys.avm_byte_lookup_table_input_a[i] = rows[i].avm_byte_lookup_table_input_a;
            polys.avm_byte_lookup_table_input_b[i] = rows[i].avm_byte_lookup_table_input_b;
            polys.avm_byte_lookup_table_op_id[i] = rows[i].avm_byte_lookup_table_op_id;
            polys.avm_byte_lookup_table_output[i] = rows[i].avm_byte_lookup_table_output;
            polys.avm_main_alu_in_tag[i] = rows[i].avm_main_alu_in_tag;
            polys.avm_main_alu_sel[i] = rows[i].avm_main_alu_sel;
            polys.avm_main_bin_op_id[i] = rows[i].avm_main_bin_op_id;
            polys.avm_main_bin_sel[i] = rows[i].avm_main_bin_sel;
            polys.avm_main_ia[i] = rows[i].avm_main_ia;
            polys.avm_main_ib[i] = rows[i].avm_main_ib;
            polys.avm_main_ic[i] = rows[i].avm_main_ic;
            polys.avm_main_id[i] = rows[i].avm_main_id;
            polys.avm_main_id_zero[i] = rows[i].avm_main_id_zero;
            polys.avm_main_ind_a[i] = rows[i].avm_main_ind_a;
            polys.avm_main_ind_b[i] = rows[i].avm_main_ind_b;
            polys.avm_main_ind_c[i] = rows[i].avm_main_ind_c;
            polys.avm_main_ind_d[i] = rows[i].avm_main_ind_d;
            polys.avm_main_ind_op_a[i] = rows[i].avm_main_ind_op_a;
            polys.avm_main_ind_op_b[i] = rows[i].avm_main_ind_op_b;
            polys.avm_main_ind_op_c[i] = rows[i].avm_main_ind_op_c;
            polys.avm_main_ind_op_d[i] = rows[i].avm_main_ind_op_d;
            polys.avm_main_internal_return_ptr[i] = rows[i].avm_main_internal_return_ptr;
            polys.avm_main_inv[i] = rows[i].avm_main_inv;
            polys.avm_main_last[i] = rows[i].avm_main_last;
            polys.avm_main_mem_idx_a[i] = rows[i].avm_main_mem_idx_a;
            polys.avm_main_mem_idx_b[i] = rows[i].avm_main_mem_idx_b;
            polys.avm_main_mem_idx_c[i] = rows[i].avm_main_mem_idx_c;
            polys.avm_main_mem_idx_d[i] = rows[i].avm_main_mem_idx_d;
            polys.avm_main_mem_op_a[i] = rows[i].avm_main_mem_op_a;
            polys.avm_main_mem_op_b[i] = rows[i].avm_main_mem_op_b;
            polys.avm_main_mem_op_c[i] = rows[i].avm_main_mem_op_c;
            polys.avm_main_mem_op_d[i] = rows[i].avm_main_mem_op_d;
            polys.avm_main_op_err[i] = rows[i].avm_main_op_err;
            polys.avm_main_pc[i] = rows[i].avm_main_pc;
            polys.avm_main_r_in_tag[i] = rows[i].avm_main_r_in_tag;
            polys.avm_main_rwa[i] = rows[i].avm_main_rwa;
            polys.avm_main_rwb[i] = rows[i].avm_main_rwb;
            polys.avm_main_rwc[i] = rows[i].avm_main_rwc;
            polys.avm_main_rwd[i] = rows[i].avm_main_rwd;
            polys.avm_main_sel_cmov[i] = rows[i].avm_main_sel_cmov;
            polys.avm_main_sel_halt[i] = rows[i].avm_main_sel_halt;
            polys.avm_main_sel_internal_call[i] = rows[i].avm_main_sel_internal_call;
            polys.avm_main_sel_internal_return[i] = rows[i].avm_main_sel_internal_return;
            polys.avm_main_sel_jump[i] = rows[i].avm_main_sel_jump;
            polys.avm_main_sel_mov[i] = rows[i].avm_main_sel_mov;
            polys.avm_main_sel_mov_a[i] = rows[i].avm_main_sel_mov_a;
            polys.avm_main_sel_mov_b[i] = rows[i].avm_main_sel_mov_b;
            polys.avm_main_sel_op_add[i] = rows[i].avm_main_sel_op_add;
            polys.avm_main_sel_op_and[i] = rows[i].avm_main_sel_op_and;
            polys.avm_main_sel_op_cast[i] = rows[i].avm_main_sel_op_cast;
            polys.avm_main_sel_op_div[i] = rows[i].avm_main_sel_op_div;
            polys.avm_main_sel_op_eq[i] = rows[i].avm_main_sel_op_eq;
            polys.avm_main_sel_op_fdiv[i] = rows[i].avm_main_sel_op_fdiv;
            polys.avm_main_sel_op_lt[i] = rows[i].avm_main_sel_op_lt;
            polys.avm_main_sel_op_lte[i] = rows[i].avm_main_sel_op_lte;
            polys.avm_main_sel_op_mul[i] = rows[i].avm_main_sel_op_mul;
            polys.avm_main_sel_op_not[i] = rows[i].avm_main_sel_op_not;
            polys.avm_main_sel_op_or[i] = rows[i].avm_main_sel_op_or;
            polys.avm_main_sel_op_shl[i] = rows[i].avm_main_sel_op_shl;
            polys.avm_main_sel_op_shr[i] = rows[i].avm_main_sel_op_shr;
            polys.avm_main_sel_op_sub[i] = rows[i].avm_main_sel_op_sub;
            polys.avm_main_sel_op_xor[i] = rows[i].avm_main_sel_op_xor;
            polys.avm_main_sel_rng_16[i] = rows[i].avm_main_sel_rng_16;
            polys.avm_main_sel_rng_8[i] = rows[i].avm_main_sel_rng_8;
            polys.avm_main_table_pow_2[i] = rows[i].avm_main_table_pow_2;
            polys.avm_main_tag_err[i] = rows[i].avm_main_tag_err;
            polys.avm_main_w_in_tag[i] = rows[i].avm_main_w_in_tag;
            polys.avm_mem_addr[i] = rows[i].avm_mem_addr;
            polys.avm_mem_clk[i] = rows[i].avm_mem_clk;
            polys.avm_mem_ind_op_a[i] = rows[i].avm_mem_ind_op_a;
            polys.avm_mem_ind_op_b[i] = rows[i].avm_mem_ind_op_b;
            polys.avm_mem_ind_op_c[i] = rows[i].avm_mem_ind_op_c;
            polys.avm_mem_ind_op_d[i] = rows[i].avm_mem_ind_op_d;
            polys.avm_mem_last[i] = rows[i].avm_mem_last;
            polys.avm_mem_lastAccess[i] = rows[i].avm_mem_lastAccess;
            polys.avm_mem_one_min_inv[i] = rows[i].avm_mem_one_min_inv;
            polys.avm_mem_op_a[i] = rows[i].avm_mem_op_a;
            polys.avm_mem_op_b[i] = rows[i].avm_mem_op_b;
            polys.avm_mem_op_c[i] = rows[i].avm_mem_op_c;
            polys.avm_mem_op_d[i] = rows[i].avm_mem_op_d;
            polys.avm_mem_r_in_tag[i] = rows[i].avm_mem_r_in_tag;
            polys.avm_mem_rw[i] = rows[i].avm_mem_rw;
            polys.avm_mem_sel_cmov[i] = rows[i].avm_mem_sel_cmov;
            polys.avm_mem_sel_mov_a[i] = rows[i].avm_mem_sel_mov_a;
            polys.avm_mem_sel_mov_b[i] = rows[i].avm_mem_sel_mov_b;
            polys.avm_mem_skip_check_tag[i] = rows[i].avm_mem_skip_check_tag;
            polys.avm_mem_sub_clk[i] = rows[i].avm_mem_sub_clk;
            polys.avm_mem_tag[i] = rows[i].avm_mem_tag;
            polys.avm_mem_tag_err[i] = rows[i].avm_mem_tag_err;
            polys.avm_mem_val[i] = rows[i].avm_mem_val;
            polys.avm_mem_w_in_tag[i] = rows[i].avm_mem_w_in_tag;
            polys.lookup_byte_lengths_counts[i] = rows[i].lookup_byte_lengths_counts;
            polys.lookup_byte_operations_counts[i] = rows[i].lookup_byte_operations_counts;
            polys.incl_main_tag_err_counts[i] = rows[i].incl_main_tag_err_counts;
            polys.incl_mem_tag_err_counts[i] = rows[i].incl_mem_tag_err_counts;
            polys.lookup_pow_2_0_counts[i] = rows[i].lookup_pow_2_0_counts;
            polys.lookup_pow_2_1_counts[i] = rows[i].lookup_pow_2_1_counts;
            polys.lookup_u8_0_counts[i] = rows[i].lookup_u8_0_counts;
            polys.lookup_u8_1_counts[i] = rows[i].lookup_u8_1_counts;
            polys.lookup_u16_0_counts[i] = rows[i].lookup_u16_0_counts;
            polys.lookup_u16_1_counts[i] = rows[i].lookup_u16_1_counts;
            polys.lookup_u16_2_counts[i] = rows[i].lookup_u16_2_counts;
            polys.lookup_u16_3_counts[i] = rows[i].lookup_u16_3_counts;
            polys.lookup_u16_4_counts[i] = rows[i].lookup_u16_4_counts;
            polys.lookup_u16_5_counts[i] = rows[i].lookup_u16_5_counts;
            polys.lookup_u16_6_counts[i] = rows[i].lookup_u16_6_counts;
            polys.lookup_u16_7_counts[i] = rows[i].lookup_u16_7_counts;
            polys.lookup_u16_8_counts[i] = rows[i].lookup_u16_8_counts;
            polys.lookup_u16_9_counts[i] = rows[i].lookup_u16_9_counts;
            polys.lookup_u16_10_counts[i] = rows[i].lookup_u16_10_counts;
            polys.lookup_u16_11_counts[i] = rows[i].lookup_u16_11_counts;
            polys.lookup_u16_12_counts[i] = rows[i].lookup_u16_12_counts;
            polys.lookup_u16_13_counts[i] = rows[i].lookup_u16_13_counts;
            polys.lookup_u16_14_counts[i] = rows[i].lookup_u16_14_counts;
        }

        polys.avm_alu_a_hi_shift = Polynomial(polys.avm_alu_a_hi.shifted());
        polys.avm_alu_a_lo_shift = Polynomial(polys.avm_alu_a_lo.shifted());
        polys.avm_alu_alu_sel_shift = Polynomial(polys.avm_alu_alu_sel.shifted());
        polys.avm_alu_b_hi_shift = Polynomial(polys.avm_alu_b_hi.shifted());
        polys.avm_alu_b_lo_shift = Polynomial(polys.avm_alu_b_lo.shifted());
        polys.avm_alu_cmp_rng_ctr_shift = Polynomial(polys.avm_alu_cmp_rng_ctr.shifted());
        polys.avm_alu_cmp_sel_shift = Polynomial(polys.avm_alu_cmp_sel.shifted());
        polys.avm_alu_op_add_shift = Polynomial(polys.avm_alu_op_add.shifted());
        polys.avm_alu_op_cast_prev_shift = Polynomial(polys.avm_alu_op_cast_prev.shifted());
        polys.avm_alu_op_cast_shift = Polynomial(polys.avm_alu_op_cast.shifted());
        polys.avm_alu_op_mul_shift = Polynomial(polys.avm_alu_op_mul.shifted());
        polys.avm_alu_op_shl_shift = Polynomial(polys.avm_alu_op_shl.shifted());
        polys.avm_alu_op_shr_shift = Polynomial(polys.avm_alu_op_shr.shifted());
        polys.avm_alu_op_sub_shift = Polynomial(polys.avm_alu_op_sub.shifted());
        polys.avm_alu_p_sub_a_hi_shift = Polynomial(polys.avm_alu_p_sub_a_hi.shifted());
        polys.avm_alu_p_sub_a_lo_shift = Polynomial(polys.avm_alu_p_sub_a_lo.shifted());
        polys.avm_alu_p_sub_b_hi_shift = Polynomial(polys.avm_alu_p_sub_b_hi.shifted());
        polys.avm_alu_p_sub_b_lo_shift = Polynomial(polys.avm_alu_p_sub_b_lo.shifted());
        polys.avm_alu_rng_chk_lookup_selector_shift = Polynomial(polys.avm_alu_rng_chk_lookup_selector.shifted());
        polys.avm_alu_rng_chk_sel_shift = Polynomial(polys.avm_alu_rng_chk_sel.shifted());
        polys.avm_alu_u16_r0_shift = Polynomial(polys.avm_alu_u16_r0.shifted());
        polys.avm_alu_u16_r1_shift = Polynomial(polys.avm_alu_u16_r1.shifted());
        polys.avm_alu_u16_r2_shift = Polynomial(polys.avm_alu_u16_r2.shifted());
        polys.avm_alu_u16_r3_shift = Polynomial(polys.avm_alu_u16_r3.shifted());
        polys.avm_alu_u16_r4_shift = Polynomial(polys.avm_alu_u16_r4.shifted());
        polys.avm_alu_u16_r5_shift = Polynomial(polys.avm_alu_u16_r5.shifted());
        polys.avm_alu_u16_r6_shift = Polynomial(polys.avm_alu_u16_r6.shifted());
        polys.avm_alu_u8_r0_shift = Polynomial(polys.avm_alu_u8_r0.shifted());
        polys.avm_alu_u8_r1_shift = Polynomial(polys.avm_alu_u8_r1.shifted());
        polys.avm_binary_acc_ia_shift = Polynomial(polys.avm_binary_acc_ia.shifted());
        polys.avm_binary_acc_ib_shift = Polynomial(polys.avm_binary_acc_ib.shifted());
        polys.avm_binary_acc_ic_shift = Polynomial(polys.avm_binary_acc_ic.shifted());
        polys.avm_binary_mem_tag_ctr_shift = Polynomial(polys.avm_binary_mem_tag_ctr.shifted());
        polys.avm_binary_op_id_shift = Polynomial(polys.avm_binary_op_id.shifted());
        polys.avm_main_internal_return_ptr_shift = Polynomial(polys.avm_main_internal_return_ptr.shifted());
        polys.avm_main_pc_shift = Polynomial(polys.avm_main_pc.shifted());
        polys.avm_mem_addr_shift = Polynomial(polys.avm_mem_addr.shifted());
        polys.avm_mem_rw_shift = Polynomial(polys.avm_mem_rw.shifted());
        polys.avm_mem_tag_shift = Polynomial(polys.avm_mem_tag.shifted());
        polys.avm_mem_val_shift = Polynomial(polys.avm_mem_val.shifted());

        return polys;
    }

    [[maybe_unused]] bool check_circuit()
    {

        const FF gamma = FF::random_element();
        const FF beta = FF::random_element();
        bb::RelationParameters<typename Flavor::FF> params{
            .eta = 0,
            .beta = beta,
            .gamma = gamma,
            .public_input_delta = 0,
            .lookup_grand_product_delta = 0,
            .beta_sqr = 0,
            .beta_cube = 0,
            .eccvm_set_permutation_delta = 0,
        };

        auto polys = compute_polynomials();
        const size_t num_rows = polys.get_polynomial_size();

        const auto evaluate_relation = [&]<typename Relation>(const std::string& relation_name,
                                                              std::string (*debug_label)(int)) {
            typename Relation::SumcheckArrayOfValuesOverSubrelations result;
            for (auto& r : result) {
                r = 0;
            }
            constexpr size_t NUM_SUBRELATIONS = result.size();

            for (size_t i = 0; i < num_rows; ++i) {
                Relation::accumulate(result, polys.get_row(i), {}, 1);

                bool x = true;
                for (size_t j = 0; j < NUM_SUBRELATIONS; ++j) {
                    if (result[j] != 0) {
                        std::string row_name = debug_label(static_cast<int>(j));
                        throw_or_abort(
                            format("Relation ", relation_name, ", subrelation index ", row_name, " failed at row ", i));
                        x = false;
                    }
                }
                if (!x) {
                    return false;
                }
            }
            return true;
        };

        const auto evaluate_logderivative = [&]<typename LogDerivativeSettings>(const std::string& lookup_name) {
            // Check the logderivative relation
            bb::compute_logderivative_inverse<Flavor, LogDerivativeSettings>(polys, params, num_rows);

            typename LogDerivativeSettings::SumcheckArrayOfValuesOverSubrelations lookup_result;

            for (auto& r : lookup_result) {
                r = 0;
            }
            for (size_t i = 0; i < num_rows; ++i) {
                LogDerivativeSettings::accumulate(lookup_result, polys.get_row(i), params, 1);
            }
            for (auto r : lookup_result) {
                if (r != 0) {
                    throw_or_abort(format("Lookup ", lookup_name, " failed."));
                    return false;
                }
            }
            return true;
        };

        if (!evaluate_relation.template operator()<Avm_vm::avm_alu<FF>>("avm_alu",
                                                                        Avm_vm::get_relation_label_avm_alu)) {
            return false;
        }
        if (!evaluate_relation.template operator()<Avm_vm::avm_binary<FF>>("avm_binary",
                                                                           Avm_vm::get_relation_label_avm_binary)) {
            return false;
        }
        if (!evaluate_relation.template operator()<Avm_vm::avm_main<FF>>("avm_main",
                                                                         Avm_vm::get_relation_label_avm_main)) {
            return false;
        }
        if (!evaluate_relation.template operator()<Avm_vm::avm_mem<FF>>("avm_mem",
                                                                        Avm_vm::get_relation_label_avm_mem)) {
            return false;
        }

        if (!evaluate_logderivative.template operator()<perm_main_alu_relation<FF>>("PERM_MAIN_ALU")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_bin_relation<FF>>("PERM_MAIN_BIN")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_a_relation<FF>>("PERM_MAIN_MEM_A")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_b_relation<FF>>("PERM_MAIN_MEM_B")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_c_relation<FF>>("PERM_MAIN_MEM_C")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_d_relation<FF>>("PERM_MAIN_MEM_D")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_ind_a_relation<FF>>("PERM_MAIN_MEM_IND_A")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_ind_b_relation<FF>>("PERM_MAIN_MEM_IND_B")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_ind_c_relation<FF>>("PERM_MAIN_MEM_IND_C")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<perm_main_mem_ind_d_relation<FF>>("PERM_MAIN_MEM_IND_D")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_byte_lengths_relation<FF>>("LOOKUP_BYTE_LENGTHS")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_byte_operations_relation<FF>>(
                "LOOKUP_BYTE_OPERATIONS")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<incl_main_tag_err_relation<FF>>("INCL_MAIN_TAG_ERR")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<incl_mem_tag_err_relation<FF>>("INCL_MEM_TAG_ERR")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_pow_2_0_relation<FF>>("LOOKUP_POW_2_0")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_pow_2_1_relation<FF>>("LOOKUP_POW_2_1")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u8_0_relation<FF>>("LOOKUP_U8_0")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u8_1_relation<FF>>("LOOKUP_U8_1")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_0_relation<FF>>("LOOKUP_U16_0")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_1_relation<FF>>("LOOKUP_U16_1")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_2_relation<FF>>("LOOKUP_U16_2")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_3_relation<FF>>("LOOKUP_U16_3")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_4_relation<FF>>("LOOKUP_U16_4")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_5_relation<FF>>("LOOKUP_U16_5")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_6_relation<FF>>("LOOKUP_U16_6")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_7_relation<FF>>("LOOKUP_U16_7")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_8_relation<FF>>("LOOKUP_U16_8")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_9_relation<FF>>("LOOKUP_U16_9")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_10_relation<FF>>("LOOKUP_U16_10")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_11_relation<FF>>("LOOKUP_U16_11")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_12_relation<FF>>("LOOKUP_U16_12")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_13_relation<FF>>("LOOKUP_U16_13")) {
            return false;
        }
        if (!evaluate_logderivative.template operator()<lookup_u16_14_relation<FF>>("LOOKUP_U16_14")) {
            return false;
        }

        return true;
    }

    [[nodiscard]] size_t get_num_gates() const { return rows.size(); }

    [[nodiscard]] size_t get_circuit_subgroup_size() const
    {
        const size_t num_rows = get_num_gates();
        const auto num_rows_log2 = static_cast<size_t>(numeric::get_msb64(num_rows));
        size_t num_rows_pow2 = 1UL << (num_rows_log2 + (1UL << num_rows_log2 == num_rows ? 0 : 1));
        return num_rows_pow2;
    }
};
} // namespace bb
