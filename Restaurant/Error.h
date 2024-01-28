#ifndef ERRORS_H
#define ERRORS_H

// Types of errors when exceptions are raised
enum class error {
	OUT_OF_MEMORY,  // Procedure was unable to allocated enough memory
	FILE_NOT_FOUND,  // Procedure could not open the requested file
	OUT_OF_RANGE // User passed invalid index
};

#endif
