/*
 *
 *
 */

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

inline void buf_add_int(char *buffer, int *buf_pos, const long value) {
  long *loc = (long*)&buffer[*buf_pos];
  *loc = value;
  *buf_pos += sizeof(long);
}

inline void buf_add_int(char *buffer, int *buf_pos, const long long value) {
  long long *loc = (long long*)&buffer[*buf_pos];
  *loc = value;
  *buf_pos += sizeof(long long);
}
