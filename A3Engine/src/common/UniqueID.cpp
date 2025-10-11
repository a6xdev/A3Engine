#include "UniqueID.h"

namespace UniqueID {
	uint64_t g_uniqueID = 1;

	uint64_t getNext() {
		return g_uniqueID++;
	}
}