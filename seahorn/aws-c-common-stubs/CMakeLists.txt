add_library(priority_queue
  ${AWS_C_COMMON_ROOT}/source/priority_queue.c)
sea_attach_bc(priority_queue)

# Change linkage to all functions that start with 's_' to external
# This is necessary so that they can be called directly from verification harness
set(LLVMIR_OPT ${SEA_PP})
llvmir_attach_opt_pass_target(TARGET priority_queue.opt.ir DEPENDS priority_queue.ir
  "--externalize-function=^s_*" "-externalize-functions-delete=false" "--externalize-fns")
