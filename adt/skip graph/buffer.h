/*
 *
 *
 */

inline void buf_add_char(char *buffer, int *buf_pos, const char value) {
	int *loc = (char*)&buffer[*buf_pos];
	*loc = value;
	*buf_pos += sizeof(char);
}

inline void buf_add_int(char *buffer, int *buf_pos, const int value) {
	int *loc = (int*)&buffer[*buf_pos];
	*loc = value;
	*buf_pos += sizeof(int);
}

inline void buf_add_short(char *buffer, int *buf_pos, const short value) {
  	short *loc = (short*)&buffer[*buf_pos];
  	*loc = value;
  	*buf_pos += sizeof(short);
}

inline void buf_add_long(char *buffer, int *buf_pos, const long value) {
  	long *loc = (long*)&buffer[*buf_pos];
 	*loc = value;
  	*buf_pos += sizeof(long);
}

inline void buf_add_llong(char *buffer, int *buf_pos, const long long value) {
  	long long *loc = (long long*)&buffer[*buf_pos];
  	*loc = value;
  	*buf_pos += sizeof(long long);
}

void buf_read_char(const char *buffer, int *buf_pos, char *value) {
	int fpos = *buf_pos+sizeof(char);
	*value = 0;
	while(*buf_pos!=fpos) {
		*value = *value<<8;
		*value+= buffer[*buf_pos];
		*buf_pos++;
	}
}

void buf_read_int(const char *buffer, int *buf_pos, int *value) {
	int fpos = *buf_pos+sizeof(int);
	*value = 0;
	while(*buf_pos!=fpos) {
		*value = *value<<8;
		*value+= buffer[*buf_pos];
		*buf_pos++;
	}
}

void buf_read_short(const char *buffer, int *buf_pos, short *value) {
	int fpos = *buf_pos+sizeof(short);
	*value = 0;
	while(*buf_pos!=fpos) {
		*value = *value<<8;
		*value+= buffer[*buf_pos];
		*buf_pos++;
	}
}

void buf_read_long(const char *buffer, int *buf_pos, long *value) {
	int fpos = *buf_pos+sizeof(long);
	*value = 0;
	while(*buf_pos!=fpos) {
		*value = *value<<8;
		*value+= buffer[*buf_pos];
		*buf_pos++;
	}
}

void buf_read_llong(const char *buffer, int *buf_pos, long long *value) {
	int fpos = *buf_pos+sizeof(long long);
	*value = 0;
	while(*buf_pos!=fpos) {
		*value = *value<<8;
		*value+= buffer[*buf_pos];
		*buf_pos++;
	}
}

void buf_read_string_len(const char *buffer, int *buf_pos, const int *len, char *start) {
	int i=0;
	while(i!=*len) {
		start[i] = buffer[*buf_pos+i];
		i++;
	}
	*buf_pos += *len;
}

