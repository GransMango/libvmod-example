#include "config.h"
#include <string.h>
#include "cache/cache.h"

#include "vcc_hiring_if.h"

VCL_INT
vmod_count(VRT_CTX, VCL_STRING haystack, VCL_STRING needle)
{
	if (haystack == NULL || needle == NULL)
		return (-1);

	int haystack_len = strlen(haystack);
	int needle_len = strlen(needle);
	
	if (haystack_len == 0 || needle_len == 0 || needle_len > haystack_len)
		return 0;

	int occurrences = 0;

	for (int i = 0; i <= haystack_len - needle_len; i++) {
		int match = 1;
		for (int j = 0; j < needle_len; j++) {
			if (haystack[i+j] != needle[j]) {
				match = 0;
				break;
			}
		}
		if (match)
			occurrences++;
	}
	return occurrences;
}
