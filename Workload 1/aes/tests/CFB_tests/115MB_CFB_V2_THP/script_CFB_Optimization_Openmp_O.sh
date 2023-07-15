#!/bin/bash

#This is all done on the SE_array.txt HEX File which is 300 MB

# First Case 128 Encryption and Decryption
g++ -O2 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 128ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 128_OpenMP_O2.txt ./a.out;
g++ -O3 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 128ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 128_OpenMP_O3.txt ./a.out;

#Second Case 192 Encryption and Decryption
g++ -O2 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 192ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 192_OpenMP_O2.txt ./a.out;
g++ -O3 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 192ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 192_OpenMP_O3.txt ./a.out;

#Third Case 256 Encryption and Decryption
g++ -O2 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 256ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 256_OpenMP_O2.txt ./a.out;
g++ -O3 -Wall -Wextra -g -pthread -fopenmp ../../../src/AES_CBC_and_CFB_Decryption_Optimizations.cpp 256ENC_DEC_CFB_new.cpp;perf stat -e task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,br_mis_pred,br_pred,bus_access,bus_cycles,cid_write_retired,cpu_cycles,exc_return,exc_taken,inst_retired,inst_spec,l1d_cache,L1-dcache-loads,L1-dcache-load-misses,l1d_cache_refill,l1d_cache_wb,l1d_tlb_refill,l1i_cache,L1-icache-loads,L1-icache-load-misses,cache-misses,l1i_cache_refill,l1i_tlb_refill,l2d_cache,l2d_cache_refill,l2d_cache_wb,mem_access,memory_error,sw_incr,ttbr_write_retired,dTLB-loads,dTLB-load-misses,dTLB-stores,dTLB-store-misses,ase_spec,br_immed_spec,br_indirect_spec,br_return_spec,bus_access_normal,bus_access_not_shared,bus_access_periph,bus_access_rd,bus_access_shared,bus_access_wr,crypto_spec,dmb_spec,dp_spec,dsb_spec,exc_dabort,exc_fiq,exc_hvc,exc_irq,exc_pabort,exc_smc,exc_svc,exc_trap_dabort,exc_trap_fiq,exc_trap_irq,exc_trap_other,exc_trap_pabort,exc_undef,isb_spec,l1d_cache_inval,l1d_cache_rd,l1d_cache_refill_rd,l1d_cache_refill_wr,l1d_cache_wb_clean,l1d_cache_wb_victim,l1d_cache_wr,l1d_tlb_refill_rd,l1d_tlb_refill_wr,l2d_cache_inval,l2d_cache_rd,l2d_cache_refill_rd,l2d_cache_refill_wr,l2d_cache_wb_clean,l2d_cache_wb_victim,l2d_cache_wr,ld_spec,ldrex_spec,ldst_spec,mem_access_rd,mem_access_wr,pc_write_spec,rc_ld_spec,rc_st_spec,st_spec,strex_fail_spec,strex_pass_spec,unaligned_ld_spec,unaligned_ldst_spec,unaligned_st_spec,vfp_spec -o 256_OpenMP_O3.txt ./a.out;
