#include <assert.h>
#include <bounds.h>
#include <byte_buf_helper.h>
#include <proof_allocators.h>
#include <utils.h>

void initialize_byte_buf(struct aws_byte_buf *const buf) {
  size_t max_size = sea_max_buffer_size();
  size_t len = nd_size_t();
  size_t cap = nd_size_t();
  // cap <= max_size
  cap %= max_size;
  // len <= cap
  cap = cap == 0 ? 1 : cap;
  len %= cap;

  buf->len = len;
  buf->capacity = cap;
  buf->buffer = can_fail_malloc(cap * sizeof(*(buf->buffer)));
  if (buf->buffer) {
    memhavoc(buf->buffer, cap * sizeof(*(buf->buffer)));
  }
  buf->allocator = sea_allocator();
}

void initialize_byte_cursor(struct aws_byte_cursor *const cursor) {
  size_t max_buffer_size = sea_max_buffer_size();
  cursor->len = nd_size_t();
  // cursor->len <= max_buffer_size
  cursor->len %= max_buffer_size;
  cursor->ptr = can_fail_malloc(sizeof(*(cursor->ptr)) * max_buffer_size);
}

bool aws_byte_buf_is_bounded(const struct aws_byte_buf *const buf,
                             const size_t max_size) {
  return (buf->capacity <= max_size);
}

bool aws_byte_cursor_is_bounded(const struct aws_byte_cursor *const cursor,
                                const size_t max_size) {
  return cursor->len <= max_size;
}

void ensure_byte_buf_has_allocated_buffer_member(
    struct aws_byte_buf *const buf) {
  buf->allocator = sea_allocator();
  buf->buffer = bounded_malloc(sizeof(*(buf->buffer)) * buf->capacity);
  size_t len = nd_size_t();
  // assume(len <= buf->capacity);
  FUZZ_ASSUME_LT(len, buf->capacity + 1);
  buf->len = len;
}

bool byte_bufs_are_equal(struct aws_byte_buf *b1, struct aws_byte_buf *b2) {
  if (!b1 || !b2)
    return b1 == b2;

  return b1->len == b2->len && b1->buffer == b2->buffer &&
         b1->capacity == b2->capacity && b1->allocator == b2->allocator;
}
