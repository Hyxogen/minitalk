#include "stream.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int _stream_grow(t_io_stream *stream, size_t new_size)
{
	return (realloc(stream->m_ptr_begin, new_size) == 0);
}

int stream_flush(t_io_stream *stream, int fd)
{
	int ret;

	ret = write(1, stream->m_ptr_begin, stream->m_write_offset);
	stream->m_write_offset = 0;
	return (ret);
}

int stream_write(t_io_stream *stream, const char *str, size_t len)
{
	if (len + stream->m_write_offset >= stream->m_buffersize)
		_stream_grow(stream, stream->m_buffersize * 2); /*To fast grow*/
	memcpy(&stream->m_ptr_begin[stream->m_write_offset], str, len);
	stream->m_write_offset += len;
	return (1);
}

int stream_init(t_io_stream *stream, size_t buffersize)
{
	stream->m_ptr_begin = malloc(buffersize);
	stream->m_write_offset = 0;
	stream->m_buffersize = buffersize;
	return (1);
}
