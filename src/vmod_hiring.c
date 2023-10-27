#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache.h"

#include "vtim.h"
#include "vcc_hiring_if.h"

const size_t infosz = 64;
char	     *info;

/*
 * handle vmod internal state, vmod init/fini and/or varnish callback
 * (un)registration here.
 *
 * malloc'ing the info buffer is only indended as a demonstration, for any
 * real-world vmod, a fixed-sized buffer should be a global variable
 */

int v_matchproto_(vmod_event_f)
vmod_event_function(VRT_CTX, struct vmod_priv *priv, enum vcl_event_e e)
{
	char	   ts[VTIM_FORMAT_SIZE];
	const char *event = NULL;

	(void) ctx;
	(void) priv;

	switch (e) {
	case VCL_EVENT_LOAD:
		info = malloc(infosz);
		if (! info)
			return (-1);
		event = "loaded";
		break;
	case VCL_EVENT_WARM:
		event = "warmed";
		break;
	case VCL_EVENT_COLD:
		event = "cooled";
		break;
	case VCL_EVENT_DISCARD:
		free(info);
		return (0);
		break;
	default:
		return (0);
	}
	AN(event);
	VTIM_format(VTIM_real(), ts);
	snprintf(info, infosz, "vmod_hiring %s at %s", event, ts);

	return (0);
}

VCL_STRING
vmod_info(VRT_CTX)
{
	(void) ctx;

	return (info);
}

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
