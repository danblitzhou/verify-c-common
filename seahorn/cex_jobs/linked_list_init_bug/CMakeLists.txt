# add head and tail to list size.
add_executable(linked_list_init_bug
  aws_linked_list_init_bug_harness.c
  ${SEA_LIB}/proof_allocators.c
  ${SEA_LIB}/linked_list_helper.c)
target_compile_definitions(linked_list_init_bug
  # We will use our own function for is_valid check hence AWS_DEEP_CHECK is off
  PUBLIC SEA_DEEP_CHECKS=0
  MAX_LINKED_LIST_ITEM_ALLOCATION=${MAX_LINKED_LIST_ITEM_ALLOCATION_SIZE})
sea_attach_bc(linked_list_init_bug)