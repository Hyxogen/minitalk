#ifndef BUFFER_H
#define BUFFER_H

#ifndef STREAM_BUFFER_SIZE
#define STREAM_BUFFER_SIZE 4
#endif

# include <sys/types.h>

typedef struct s_io_stream
{
	char *m_ptr_begin;
	size_t m_write_offset;
	size_t m_buffersize;
}	t_io_stream;

int stream_flush(t_io_stream *stream, int fd);
int stream_write(t_io_stream *stream, const char *str, size_t len);
int stream_init(t_io_stream *stream, size_t buffersize);

#endif
