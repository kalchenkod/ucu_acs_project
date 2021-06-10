#ifndef VIDEO_WRITE_TO_FILE_H
#define VIDEO_WRITE_TO_FILE_H

#include <string>
#include <tbb/concurrent_hash_map.h>

void write_to_file (const tbb::concurrent_hash_map<std::string, double> &map);

#endif //VIDEO_WRITE_TO_FILE_H
