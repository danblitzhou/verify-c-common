add_executable(array_list_erase
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_erase_harness.c)
sea_attach_bc_link(array_list_erase)
sea_add_unsat_test(array_list_erase)

# klee
sea_add_klee(array_list_erase ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_array_list_erase_harness.c)

sea_add_fuzz(array_list_erase aws_array_list_erase_harness.c)