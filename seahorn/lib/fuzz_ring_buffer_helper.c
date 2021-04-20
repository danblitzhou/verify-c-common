#include <nondet.h>
#include <proof_allocators.h>
#include <ring_buffer_helper.h>
#include <seahorn/seahorn.h>

#include <aws/common/byte_buf.h>

void initialize_ring_buffer(struct aws_ring_buffer *ring_buf,
                            const size_t size) {
  ring_buf->allocator = sea_allocator();
  /* The `aws_ring_buffer_init` function requires size > 0. */
  assume(0 < size);
  ring_buf->allocation = bounded_malloc(size);
  size_t position_head = nd_size_t();
  size_t position_tail = nd_size_t();
  assume(position_head < size);
  assume(position_tail < size);
  aws_atomic_store_ptr(&ring_buf->head, (ring_buf->allocation + position_head));
  aws_atomic_store_ptr(&ring_buf->tail, (ring_buf->allocation + position_tail));
  ring_buf->allocation_end = ring_buf->allocation + size;
}

void ensure_byte_buf_has_allocated_buffer_member_in_ring_buf(
    struct aws_byte_buf *buf, struct aws_ring_buffer *ring_buf) {
  buf->allocator = nd_bool() ? NULL : sea_allocator();
  uint8_t *head = aws_atomic_load_ptr(&ring_buf->head);
  uint8_t *tail = aws_atomic_load_ptr(&ring_buf->tail);
  if (head < tail) { /* [....H    T....] */
    if (nd_bool()) {
      assume(tail < ring_buf->allocation_end);
      ensure_byte_buf_has_allocated_buffer_member_in_range(
          buf, tail, ring_buf->allocation_end);
    } else {
      assume(ring_buf->allocation < head);
      ensure_byte_buf_has_allocated_buffer_member_in_range(
          buf, ring_buf->allocation, head);
    }
  } else { /* [    T....H    ] */
    ensure_byte_buf_has_allocated_buffer_member_in_range(buf, tail, head);
  }
}
