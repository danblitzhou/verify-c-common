add_executable(
  priority_queue_push_ref
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  aws_priority_queue_push_ref_harness.c
)
sea_link_libraries(priority_queue_push_ref priority_queue.opt.ir)
sea_overlink_libraries(priority_queue_push_ref sift_up_override.ir)
sea_attach_bc_link(priority_queue_push_ref)
configure_file(sea.yaml sea.yaml @ONLY)
sea_add_unsat_test(priority_queue_push_ref)

# klee
sea_add_klee(priority_queue_push_ref
  ${AWS_C_COMMON_ROOT}/source/array_list.c
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c
  aws_priority_queue_push_ref_harness.c)